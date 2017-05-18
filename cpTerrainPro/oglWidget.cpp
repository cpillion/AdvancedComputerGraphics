
#include "oglWidget.h"
#include "particles.h"
#include "skybox.h"
#include "cube.h"
#include "sphere.h"
#include "Noise.h"
#include <iostream>

// Constructor
oglWidget::oglWidget(QWidget *parent)
    : CUgl(parent),
      crateShader(0)
{
    cube_size=36;
    MAP_SCALE = 750.0;
    H_SCALE = 50.0;
}

oglWidget::~oglWidget()
{
    cleanup();
}

QSize oglWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize oglWidget::sizeHint() const
{
    return QSize(600, 600);
}

// Called by the destructor
void oglWidget::cleanup()
{
    makeCurrent();
    skyboxBuff.destroy();
    cubeBuff.destroy();
    sphereBuff.destroy();
    snowBuff.destroy();
    terrainBuff.destroy();
    delete skyboxShader;
    delete crateShader;
    delete passShader;
    delete snowShader;
    delete terrainShader;
    doneCurrent();
}


//  Set mode for frag shader
void oglWidget::setMode(int m)
{
   mode = m;
   //  Request redisplay
   update();
}

//  Set terrain XZ size
void oglWidget::setMsize(int s)
{
   MAP_SCALE = s;
   //  Request redisplay
   update();
}

//  Set peak size
void oglWidget::setHsize(int s)
{
   H_SCALE = s;
   //  Request redisplay
   update();
}


// Initialize the scene
void oglWidget::initializeGL()
{
    initializeOpenGLFunctions();
    // Clear Color Black - blocked by skybox anyways
    glClearColor(0.0, 0.0, 0.0, 1);

    setFocusPolicy(Qt::StrongFocus);
    // Load Shaders (0th element in the shader list is NULL)
    addShader(":/shaders/cube.vert", ":/shaders/cube.frag", "Vertex,Color,Normal,Texture");
    crateShader = shader[1];
    addShader(":/shaders/pass.vert", ":/shaders/pass.frag", "Vertex,Color,Normal");
    passShader = shader[2];
    addShader(":/shaders/snow.vert", ":/shaders/snow.frag", "Vertex,Color,Normal,Texture,Vel,Start");
    snowShader = shader[3];
    addShaderTess(":/shaders/terraintessellation.vert", ":/shaders/terraintessellation.tcs", ":/shaders/terraintessellation.tes",
                  ":/shaders/terraintessellation.geom", ":/shaders/terraintessellation.frag", "Vertex");
    terrainShader = shader[4];
    addShader(":/shaders/skybox.vert", ":/shaders/skybox.frag", "Vertex,Color,Normal,Texture");
    skyboxShader = shader[5];



    // Load Textures

    // Skybox Images (6 sides for each side of the cube map)
    const QImage posx = QImage(":/textures/nightsky_ft.jpg").convertToFormat(QImage::Format_RGBA8888);
    const QImage posy = QImage(":/textures/nightsky_up.jpg").convertToFormat(QImage::Format_RGBA8888);
    const QImage posz = QImage(":/textures/nightsky_rt.jpg").convertToFormat(QImage::Format_RGBA8888);
    const QImage negx = QImage(":/textures/nightsky_bk.jpg").convertToFormat(QImage::Format_RGBA8888);
    const QImage negy = QImage(":/textures/nightsky_dn.jpg").convertToFormat(QImage::Format_RGBA8888);
    const QImage negz = QImage(":/textures/nightsky_lf.jpg").convertToFormat(QImage::Format_RGBA8888);

    // Tell Qt that the texture is going to be a cube map and allocate space
    skyboxTex = new QOpenGLTexture(QOpenGLTexture::TargetCubeMap);
    skyboxTex->create();
    skyboxTex->setSize(posx.width(), posx.height(), posx.depth());
    skyboxTex->setFormat(QOpenGLTexture::RGBA8_UNorm);
    skyboxTex->allocateStorage();
    // Load each side of the cube map
    skyboxTex->setData(0, 0, QOpenGLTexture::CubeMapPositiveX,
                            QOpenGLTexture::RGBA, QOpenGLTexture::UInt8,
                            (const void*)posx.constBits());
    skyboxTex->setData(0, 0, QOpenGLTexture::CubeMapPositiveY,
                            QOpenGLTexture::RGBA, QOpenGLTexture::UInt8,
                            (const void*)posy.constBits());
    skyboxTex->setData(0, 0, QOpenGLTexture::CubeMapPositiveZ,
                            QOpenGLTexture::RGBA, QOpenGLTexture::UInt8,
                            (const void*)posz.constBits());
    skyboxTex->setData(0, 0, QOpenGLTexture::CubeMapNegativeX,
                            QOpenGLTexture::RGBA, QOpenGLTexture::UInt8,
                            (const void*)negx.constBits());
    skyboxTex->setData(0, 0, QOpenGLTexture::CubeMapNegativeY,
                            QOpenGLTexture::RGBA, QOpenGLTexture::UInt8,
                            (const void*)negy.constBits());
    skyboxTex->setData(0, 0, QOpenGLTexture::CubeMapNegativeZ,
                            QOpenGLTexture::RGBA, QOpenGLTexture::UInt8,
                            (const void*)negz.constBits());
    // Set options for texture behavior
    skyboxTex->setWrapMode(QOpenGLTexture::ClampToEdge);
    skyboxTex->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    skyboxTex->setMagnificationFilter(QOpenGLTexture::LinearMipMapLinear);

    // Load all other textures as 2D
    crateTex = new QOpenGLTexture(QImage(":/textures/crate.png").mirrored());
    snowflakeTex = new QOpenGLTexture(QImage(":/textures/snowflake.png").mirrored());
    grassTexture = new QOpenGLTexture(QImage(":/textures/grass.jpg").mirrored());
    rockTexture = new QOpenGLTexture(QImage(":/textures/rock.jpg").mirrored());
    snowTexture = new QOpenGLTexture(QImage(":/textures/snow.jpg").mirrored());

    // Load the height map texture and grab its size
    heightMap = new QOpenGLTexture(QImage(":/textures/heightmap1024.png"));
    heightMap->setMinificationFilter(QOpenGLTexture::Linear);
    heightMap->setMagnificationFilter(QOpenGLTexture::Linear);
    heightMap->setWrapMode(QOpenGLTexture::ClampToEdge);
    heightMapSize = QImage(":/textures/heightmap1024.png").size();

    //  Load random texture to generate noise for snowflake movement
    CreateNoise3D(GL_TEXTURE1);

    // Create a VAO and VBO for the skybox
    skyboxVAO.create();
    QOpenGLVertexArrayObject::Binder skyboxBinder(&skyboxVAO);
    skybox skybox1;
    skyboxBuff = skybox1.getBuffer();


    // Create a VAO and VBO for the cube
    cubeVAO.create();
    QOpenGLVertexArrayObject::Binder cubeBinder(&cubeVAO);
    cube cube1;
    cubeBuff = cube1.getBuffer();


    // Create a VAO and VBO for the sphere
    sphereVAO.create();
    QOpenGLVertexArrayObject::Binder sphereBinder(&sphereVAO);
    sphere sphere1;
    sphereBuff = sphere1.getBuffer();

    // Create a VAO and VBO for the snow
    snowVAO.create();
    QOpenGLVertexArrayObject::Binder snowBinder(&snowVAO);
    particles snow;
    snowBuff = snow.getBuffer();

    // Create a VAO and VBO for the terrain
    terrainVAO.create();
    QOpenGLVertexArrayObject::Binder terrainBinder(&terrainVAO);

    // Note: Probably want to move this into its own class akin to the objects above.
    const int maxTessellationLevel = 64;
    const int trianglesPerHeightSample = 10;
    // Create a square map of the terrain assuming all vertices are in the XZ plane (no vertical height)
    const int xDivisions = trianglesPerHeightSample * heightMapSize.width() / maxTessellationLevel;
    const int zDivisions = trianglesPerHeightSample * heightMapSize.height() / maxTessellationLevel;
    patchCount = xDivisions * zDivisions;
    QVector<float> positionData( 2 * patchCount ); // 2 XZ floats per vertex

    const float dx = 1.0f / static_cast<float>( xDivisions );
    const float dz = 1.0f / static_cast<float>( zDivisions );

    for ( int j = 0; j < 2 * zDivisions; j += 2 )
    {
        float z = static_cast<float>( j ) * dz * 0.5;
        for ( int i = 0; i < 2 * xDivisions; i += 2 )
        {
            float x = static_cast<float>( i ) * dx * 0.5;
            const int index = xDivisions * j + i;
            positionData[index]     = x;
            positionData[index + 1] = z;
        }
    }

    terrainBuff.create();
    terrainBuff.setUsagePattern( QOpenGLBuffer::StaticDraw );
    terrainBuff.bind();
    terrainBuff.allocate( positionData.data(), positionData.size() * sizeof( GLfloat ) );
    glEnableVertexAttribArray(0);
    // Only passing vertex data in 2D for patch generation - all other attritubes will be determined by GLSL
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
    terrainBuff.release();

}

// Draw the Scene
void oglWidget::paintGL()
{
    float t = 0.001*time.elapsed();

    // Clear Buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    // Set Projection (for this project, perspective is the intended projection)
    doProjection(); // CUgl code modified for OGL4
    // Determine the light position and attributes
    QVector4D lpos = doLight(); // CUgl code modified for OGL4

    // Set the view matrix
    QMatrix4x4 view = doView(); // CUgl code modified for OGL4

    //  Initialize other transformation matricies
    QMatrix4x4 model;
    QMatrix4x4 mv;
    QMatrix3x3 normalMatrix;


    // Draw Skybox
    // Skybox drawn first with depth mask disabled so it is always in the far distance
    glDepthMask(GL_FALSE);
    model.setToIdentity();
    model.scale(1.5); // Scale of skybox doesnt matter, since the vertex shader removes translation in the modelview matrix
    mv = view*model;
    QOpenGLVertexArrayObject::Binder skyboxBinder(&skyboxVAO);
    skyboxShader->bind();
    skyboxShader->setUniformValue("tex", 0);
    skyboxShader->setUniformValue("ProjectionMatrix", proj);
    skyboxShader->setUniformValue("ModelViewMatrix", mv);
    skyboxTex->bind(0);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    skyboxTex->release(0);
    skyboxShader->release();
    // Reenable the depth mask for other objects being drawn
    glDepthMask(GL_TRUE);


    // Draw Crate (used for OGL4 and Qt5 setup initially)
    model.setToIdentity();
    model.translate(-2, 5, 0);
    mv = view*model;
    normalMatrix = mv.normalMatrix();
    QOpenGLVertexArrayObject::Binder cubeBinder(&cubeVAO);
    crateShader->bind();
    crateShader->setUniformValue("tex", 0);
    crateShader->setUniformValue("ProjectionMatrix", proj);
    crateShader->setUniformValue("ModelViewMatrix", mv);
    crateShader->setUniformValue("NormalMatrix", normalMatrix);
    crateShader->setUniformValue("ViewMatrix", view);
    crateShader->setUniformValue("Position", lpos);
    crateTex->bind(0);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    crateTex->release(0);
    crateShader->release();

    // Draw Sphere (used for OGL4 and Qt5 setup initially)
    model.setToIdentity();
    model.translate(2, 5, 0);
    mv = view*model;
    normalMatrix = mv.normalMatrix();
    QOpenGLVertexArrayObject::Binder sphereBinder(&sphereVAO);
    passShader->bind();
    passShader->setUniformValue("ProjectionMatrix", proj);
    passShader->setUniformValue("ModelViewMatrix", mv);
    passShader->setUniformValue("NormalMatrix", normalMatrix);
    passShader->setUniformValue("ViewMatrix", view);
    passShader->setUniformValue("Position", lpos);
    glDrawArrays(GL_TRIANGLES, 0, 5256);
    passShader->release();

    // Draw Terrain
    model.setToIdentity();
    // Translate the mode so the center is at the world origin
    model.translate(-MAP_SCALE/2, -10, -MAP_SCALE/2);
    mv = view*model;
    normalMatrix = mv.normalMatrix();
    QOpenGLVertexArrayObject::Binder terrainBinder(&terrainVAO);
    terrainShader->bind();
    // Set up uniform values for use in the 5 shader stages
    terrainShader->setUniformValue("mode", mode);
    terrainShader->setUniformValue("heightMap", 0);
    heightMap->bind(0);
    terrainShader->setUniformValue("ProjectionMatrix", proj);
    terrainShader->setUniformValue("ModelViewMatrix", mv);
    terrainShader->setUniformValue("NormalMatrix", normalMatrix);
    terrainShader->setUniformValue("ViewMatrix", view);
    terrainShader->setUniformValue("ModelMatrix", model);
    QMatrix3x3 worldMat = model.normalMatrix();
    terrainShader->setUniformValue("WorldNormalMatrix", worldMat);
    terrainShader->setUniformValue("Position", lpos);
    terrainShader->setUniformValue("viewportSize", QVector2D(float(width()), float(height())));
    terrainShader->setUniformValue("viewportMatrix", viewPortMat);
    terrainShader->setUniformValue( "line.width", 0.5f);
    terrainShader->setUniformValue( "line.color", QVector4D(1.0f, 0.0f, 0.0f, 1.0f));
    terrainShader->setUniformValue("horizontalScale", MAP_SCALE);
    terrainShader->setUniformValue("verticalScale", H_SCALE);
    terrainShader->setUniformValue( "light.position", lpos);
    terrainShader->setUniformValue( "light.intensity", QVector3D(0.5f, 0.5f, 0.5f));
    terrainShader->setUniformValue( "material.Ka", QVector3D( 0.3f, 0.3f, 0.3f));
    terrainShader->setUniformValue( "material.Kd", QVector3D( 1.0f, 1.0f, 1.0f));
    terrainShader->setUniformValue( "material.Ks", QVector3D( 0.3f, 0.3f, 0.3f));
    terrainShader->setUniformValue( "material.shininess", 1.0f);
    // Bind Textures to different values for multitexturing use
    terrainShader->setUniformValue("grassTexture", 1);
    grassTexture->bind(1);
    terrainShader->setUniformValue("rockTexture", 2);
    rockTexture->bind(2);
    terrainShader->setUniformValue("snowTexture", 3);
    snowTexture->bind(3);
    terrainShader->setPatchVertexCount(1);
    // Need to use GL_PATCHES for use of the tessellation shaders
    glDrawArrays(GL_PATCHES, 0, patchCount);
    heightMap->release(0);
    grassTexture->release(1);
    rockTexture->release(2);
    snowTexture->release(3);
    terrainShader->release();


    // Draw Snow
    model.setToIdentity();
    // Spread the snow over the viewing area
    model.scale(dim, 0.5*dim, dim);
    // Move the snow from the camera so it is in front
    model.translate(0, 0, -dim);
    mv = view*model;
    QOpenGLVertexArrayObject::Binder snowBinder(&snowVAO);
    snowShader->bind();
    snowShader->setUniformValue("tex", 0);
    snowShader->setUniformValue("ProjectionMatrix", proj);
    snowShader->setUniformValue("ModelViewMatrix", mv);
    snowShader->setUniformValue("time",t);
    snowShader->setUniformValue("dim",dim);
    snowShader->setUniformValue("Noise3D",1);
    //  Set particle size
    glPointSize(6);
    glEnable(GL_POINT_SPRITE);
    glTexEnvi(GL_POINT_SPRITE,GL_COORD_REPLACE,GL_TRUE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    glDepthMask(0);
    //  Draw arrays
    snowflakeTex->bind(0);
    glDrawArrays(GL_POINTS,0,1600);
    glDisable(GL_POINT_SPRITE);
    glDisable(GL_BLEND);
    glDepthMask(1);
    snowflakeTex->release(0);
    passShader->release();

}





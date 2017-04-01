//
//  Utah Teapot
//
#include <Teapot.h>
#include <math.h>

#define MAXN 64

//  Rim, body, lid, and bottom data must be reflected in x and y;
//  Handle and spout data reflected across the y axis only.
static int teapot[][4][4] =
{

   {{102,103,104,105},{  4,  5,  6,  7},{  8,  9, 10, 11},{ 12, 13, 14, 15}},  //  Rim
   {{ 12, 13, 14, 15},{ 16, 17, 18, 19},{ 20, 21, 22, 23},{ 24, 25, 26, 27}},  //  Upper body
   {{ 24, 25, 26, 27},{ 29, 30, 31, 32},{ 33, 34, 35, 36},{ 37, 38, 39, 40}},  //  Lower body
   {{118,118,118,118},{124,122,119,121},{123,126,125,120},{ 40, 39, 38, 37}},  //  Bottom
   {{ 96, 96, 96, 96},{ 97, 98, 99,100},{101,101,101,101},{  0,  1,  2,  3}},  //  Lid handle
   {{  0,  1,  2,  3},{106,107,108,109},{110,111,112,113},{114,115,116,117}},  //  Lid
   {{ 41, 42, 43, 44},{ 45, 46, 47, 48},{ 49, 50, 51, 52},{ 53, 54, 55, 56}},  //  Upper handle
   {{ 53, 54, 55, 56},{ 57, 58, 59, 60},{ 61, 62, 63, 64},{ 28, 65, 66, 67}},  //  Lower handle
   {{ 68, 69, 70, 71},{ 72, 73, 74, 75},{ 76, 77, 78, 79},{ 80, 81, 82, 83}},  //  Spout body
   {{ 80, 81, 82, 83},{ 84, 85, 86, 87},{ 88, 89, 90, 91},{ 92, 93, 94, 95}},  //  Spout tip
};

//  Data points
typedef struct {float x,y,z;} Point;

static Point data[] =
{
   { 0.2   ,  0     , 2.7    },
   { 0.2   , -0.112 , 2.7    },
   { 0.112 , -0.2   , 2.7    },
   { 0     , -0.2   , 2.7    },
   { 1.3375,  0     , 2.53125},
   { 1.3375, -0.749 , 2.53125},
   { 0.749 , -1.3375, 2.53125},
   { 0     , -1.3375, 2.53125},
   { 1.4375,  0     , 2.53125},
   { 1.4375, -0.805 , 2.53125},
   { 0.805 , -1.4375, 2.53125},
   { 0     , -1.4375, 2.53125},
   { 1.5   ,  0     , 2.4    },
   { 1.5   , -0.84  , 2.4    },
   { 0.84  , -1.5   , 2.4    },
   { 0     , -1.5   , 2.4    },
   { 1.75  ,  0     , 1.875  },
   { 1.75  , -0.98  , 1.875  },
   { 0.98  , -1.75  , 1.875  },
   { 0     , -1.75  , 1.875  },
   { 2     ,  0     , 1.35   },
   { 2     , -1.12  , 1.35   },
   { 1.12  , -2     , 1.35   },
   { 0     , -2     , 1.35   },
   { 2     ,  0     , 0.9    },
   { 2     , -1.12  , 0.9    },
   { 1.12  , -2     , 0.9    },
   { 0     , -2     , 0.9    },
   { -2    ,  0     , 0.9    },
   { 2     ,  0     , 0.45   },
   { 2     , -1.12  , 0.45   },
   { 1.12  , -2     , 0.45   },
   { 0     , -2     , 0.45   },
   { 1.5   ,  0     , 0.225  },
   { 1.5   , -0.84  , 0.225  },
   { 0.84  , -1.5   , 0.225  },
   { 0     , -1.5   , 0.225  },
   { 1.5   ,  0     , 0.15   },
   { 1.5   , -0.84  , 0.15   },
   { 0.84  , -1.5   , 0.15   },
   { 0     , -1.5   , 0.15   },
   {-1.6   ,  0     , 2.025  },
   {-1.6   , -0.3   , 2.025  },
   {-1.5   , -0.3   , 2.25   },
   {-1.5   ,  0     , 2.25   },
   {-2.3   ,  0     , 2.025  },
   {-2.3   , -0.3   , 2.025  },
   {-2.5   , -0.3   , 2.25   },
   {-2.5   ,  0     , 2.25   },
   {-2.7   ,  0     , 2.025  },
   {-2.7   , -0.3   , 2.025  },
   {-3     , -0.3   , 2.25   },
   {-3     ,  0     , 2.25   },
   {-2.7   ,  0     , 1.8    },
   {-2.7   , -0.3   , 1.8    },
   {-3     , -0.3   , 1.8    },
   {-3     ,  0     , 1.8    },
   {-2.7   ,  0     , 1.575  },
   {-2.7   , -0.3   , 1.575  },
   {-3     , -0.3   , 1.35   },
   {-3     ,  0     , 1.35   },
   {-2.5   ,  0     , 1.125  },
   {-2.5   , -0.3   , 1.125  },
   {-2.65  , -0.3   , 0.9375 },
   {-2.65  ,  0     , 0.9375 },
   {-2     , -0.3   , 0.9    },
   {-1.9   , -0.3   , 0.6    },
   {-1.9   ,  0     , 0.6    },
   { 1.7   ,  0     , 1.425  },
   { 1.7   , -0.66  , 1.425  },
   { 1.7   , -0.66  , 0.6    },
   { 1.7   ,  0     , 0.6    },
   { 2.6   ,  0     , 1.425  },
   { 2.6   , -0.66  , 1.425  },
   { 3.1   , -0.66  , 0.825  },
   { 3.1   ,  0     , 0.825  },
   { 2.3   ,  0     , 2.1    },
   { 2.3   , -0.25  , 2.1    },
   { 2.4   , -0.25  , 2.025  },
   { 2.4   ,  0     , 2.025  },
   { 2.7   ,  0     , 2.4    },
   { 2.7   , -0.25  , 2.4    },
   { 3.3   , -0.25  , 2.4    },
   { 3.3   ,  0     , 2.4    },
   { 2.8   ,  0     , 2.475  },
   { 2.8   , -0.25  , 2.475  },
   { 3.525 , -0.25  , 2.49375},
   { 3.525 ,  0     , 2.49375},
   { 2.9   ,  0     , 2.475  },
   { 2.9   , -0.15  , 2.475  },
   { 3.45  , -0.15  , 2.5125 },
   { 3.45  ,  0     , 2.5125 },
   { 2.8   ,  0     , 2.4    },
   { 2.8   , -0.15  , 2.4    },
   { 3.2   , -0.15  , 2.4    },
   { 3.2   ,  0     , 2.4    },
   { 0     ,  0     , 3.15   },
   { 0.8   ,  0     , 3.15   },
   { 0.8   , -0.45  , 3.15   },
   { 0.45  , -0.8   , 3.15   },
   { 0     , -0.8   , 3.15   },
   { 0     ,  0     , 2.85   },
   { 1.4   ,  0     , 2.4    },
   { 1.4   , -0.784 , 2.4    },
   { 0.784 , -1.4   , 2.4    },
   { 0     , -1.4   , 2.4    },
   { 0.4   ,  0     , 2.55   },
   { 0.4   , -0.224 , 2.55   },
   { 0.224 , -0.4   , 2.55   },
   { 0     , -0.4   , 2.55   },
   { 1.3   ,  0     , 2.55   },
   { 1.3   , -0.728 , 2.55   },
   { 0.728 , -1.3   , 2.55   },
   { 0     , -1.3   , 2.55   },
   { 1.3   ,  0     , 2.4    },
   { 1.3   , -0.728 , 2.4    },
   { 0.728 , -1.3   , 2.4    },
   { 0     , -1.3   , 2.4    },
   { 0     ,  0     , 0      },
   { 1.425 , -0.798 , 0      },
   { 1.5   ,  0     , 0.075  },
   { 1.425 ,  0     , 0      },
   { 0.798 , -1.425 , 0      },
   { 0     , -1.5   , 0.075  },
   { 0     , -1.425 , 0      },
   { 1.5   , -0.84  , 0.075  },
   { 0.84  , -1.5   , 0.075  },
};

#define Bezier(x)  V*V*V*(U*U*U*p[0][0].x + 3*U*U*u*p[0][1].x + 3*U*u*u*p[0][2].x + u*u*u*p[0][3].x) \
               + 3*V*V*v*(U*U*U*p[1][0].x + 3*U*U*u*p[1][1].x + 3*U*u*u*p[1][2].x + u*u*u*p[1][3].x) \
               + 3*V*v*v*(U*U*U*p[2][0].x + 3*U*U*u*p[2][1].x + 3*U*u*u*p[2][2].x + u*u*u*p[2][3].x) \
               +   v*v*v*(U*U*U*p[3][0].x + 3*U*U*u*p[3][1].x + 3*U*u*u*p[3][2].x + u*u*u*p[3][3].x)
/*
 *  Evaluate 2D Bezier surface
 */
Point Bezier2D(Point p[4][4],float u,float v)
{
   float U = 1-u;
   float V = 1-v;
   Point P;
   P.x = Bezier(x);
   P.y = Bezier(y);
   P.z = Bezier(z);
   return P;
}

#define ddu(x)  -U*U*(V*V*V*p[0][0].x + 3*V*V*v*p[1][0].x + 3*V*v*v*p[2][0].x + v*v*v*p[3][0].x) \
         + (1-3*u)*U*(V*V*V*p[0][1].x + 3*V*V*v*p[1][1].x + 3*V*v*v*p[2][1].x + v*v*v*p[3][1].x) \
         + u*(2-3*u)*(V*V*V*p[0][2].x + 3*V*V*v*p[1][2].x + 3*V*v*v*p[2][2].x + v*v*v*p[3][2].x) \
         +       u*u*(V*V*V*p[0][3].x + 3*V*V*v*p[1][3].x + 3*V*v*v*p[2][3].x + v*v*v*p[3][3].x)
#define ddv(x)  -V*V*(U*U*U*p[0][0].x + 3*U*U*u*p[0][1].x + 3*U*u*u*p[0][2].x + u*u*u*p[0][3].x) \
         + (1-3*v)*V*(U*U*U*p[1][0].x + 3*U*U*u*p[1][1].x + 3*U*u*u*p[1][2].x + u*u*u*p[1][3].x) \
         + v*(2-3*v)*(U*U*U*p[2][0].x + 3*U*U*u*p[2][1].x + 3*U*u*u*p[2][2].x + u*u*u*p[2][3].x) \
         +       v*v*(U*U*U*p[3][0].x + 3*U*U*u*p[3][1].x + 3*U*u*u*p[3][2].x + u*u*u*p[3][3].x)

/*
 *  Evaluate 2D Bezier normal
 */
Point Normal2D(Point p[4][4],float u,float v)
{
   float tiny=1e-6;
   float U = 1-u;
   float V = 1-v;
   float D,Du,Dv;
   Point P,Pu,Pv;
   //  1/3 of derivative in the u direction
   Pu.x = ddu(x);
   Pu.y = ddu(y);
   Pu.z = ddu(z);
   Du = sqrt(Pu.x*Pu.x+Pu.y*Pu.y+Pu.z*Pu.z);
   //  1/3 of derivative in the v direction
   Pv.x = ddv(x);
   Pv.y = ddv(y);
   Pv.z = ddv(z);
   Dv = sqrt(Pv.x*Pv.x+Pv.y*Pv.y+Pv.z*Pv.z);
   //  Du=0
   if (Du<tiny && Dv>tiny)
   {
      u += 0.001;
      U -= 0.001;
      Pu.x = ddv(x);
      Pu.y = ddv(y);
      Pu.z = ddv(z);
   }
   //  Dv=0
   else if (Dv<tiny && Du>tiny)
   {
      v += 0.001;
      V -= 0.001;
      Pv.x = ddu(x);
      Pv.y = ddu(y);
      Pv.z = ddu(z);
   }
   //  Cross product
   P.x = Pu.y*Pv.z - Pu.z*Pv.y;
   P.y = Pu.z*Pv.x - Pu.x*Pv.z;
   P.z = Pu.x*Pv.y - Pu.y*Pv.x;
   //  Normalize
   D = sqrt(P.x*P.x+P.y*P.y+P.z*P.z);
   if (D>tiny)
   {
      P.x /= D;
      P.y /= D;
      P.z /= D;
   }
   return P;
}

/*
 *  Draw patch
 */
static void Patch(int patch[4][4],float Sx,float Sy,int n)
{
   Point p[4][4],P[MAXN+1][MAXN+1],N[MAXN+1][MAXN+1],T[MAXN+1][MAXN+1];

   //  Copy data with reflection
   for (int k=0;k<4;k++)
   {
      int K = Sx*Sy<0 ? 3-k : k;
      for (int j=0;j<4;j++)
      {
         int l = patch[j][K];
         p[j][k].x = Sx*data[l].x;
         p[j][k].y = Sy*data[l].y;
         p[j][k].z =    data[l].z;
      }
   }

   //  Evaluate grid points
   for (int i=0;i<=n;i++)
      for (int j=0;j<=n;j++)
      {
         float u = (float)i/n;
         float v = (float)j/n;
         P[i][j] = Bezier2D(p,u,v);
         N[i][j] = Normal2D(p,u,v);
         T[i][j].x = 1-u;
         T[i][j].y = 1-v;
         T[i][j].z = 0;
      }

   //  Draw quads
   for (int i=0;i<n;i++)
   {
      glBegin(GL_QUAD_STRIP);
      for (int j=0;j<=n;j++)
      {
         //  Draw normals and vertexes
         glNormal3fv((float*)&N[i  ][j]); glTexCoord2fv((float*)&T[i  ][j]); glVertex3fv((float*)&P[i  ][j]);
         glNormal3fv((float*)&N[i+1][j]); glTexCoord2fv((float*)&T[i+1][j]); glVertex3fv((float*)&P[i+1][j]);
      }
      glEnd();
   }
}

//
//  Draw teapot
//
Teapot::Teapot(int N,const QString tex,const float size,const Color col)
{
   n = N;
   sr = 1;
   if (tex.length()>0) setTexture(tex);
   setScale(size);
   setColor(col);
}

//
//  Set scale
//
void Teapot::setScale(float r)
{
   sr = r;
}

//
//  Draw teapot
//
void Teapot::display()
{
   //  Set transform
   glPushMatrix();
   useTransform(sr,sr,sr);
   glRotated(-90,1,0,0);
   glTranslatef(0,0,-1.5);
   //  Set colors and textures
   useColor();
   EnableTex();
   //  Draw parts of teapot
   for (int i=0;i<10;i++)
      //  Draw patches reflected to 4 quadrants
      if (i<6)
      {
         Patch(teapot[i],+1,+1,n);
         Patch(teapot[i],+1,-1,n);
         Patch(teapot[i],-1,+1,n);
         Patch(teapot[i],-1,-1,n);
      }
      //  Draw patch reflected to 2 hemispheres
      else
      {
         Patch(teapot[i],+1,+1,n);
         Patch(teapot[i],+1,-1,n);
      }

   //  Undo textures
   DisableTex();
   //  Undo transformations
   glPopMatrix();
}

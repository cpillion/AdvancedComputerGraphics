/****************************************************************************
** Meta object code from reading C++ file 'hw01opengl.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "hw01opengl.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'hw01opengl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Hw01opengl_t {
    QByteArrayData data[18];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Hw01opengl_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Hw01opengl_t qt_meta_stringdata_Hw01opengl = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Hw01opengl"
QT_MOC_LITERAL(1, 11, 6), // "angles"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 4), // "text"
QT_MOC_LITERAL(4, 24, 6), // "center"
QT_MOC_LITERAL(5, 31, 9), // "setShader"
QT_MOC_LITERAL(6, 41, 2), // "on"
QT_MOC_LITERAL(7, 44, 14), // "setPerspective"
QT_MOC_LITERAL(8, 59, 9), // "setObject"
QT_MOC_LITERAL(9, 69, 4), // "type"
QT_MOC_LITERAL(10, 74, 11), // "setLighting"
QT_MOC_LITERAL(11, 86, 4), // "setX"
QT_MOC_LITERAL(12, 91, 1), // "X"
QT_MOC_LITERAL(13, 93, 4), // "setY"
QT_MOC_LITERAL(14, 98, 1), // "Y"
QT_MOC_LITERAL(15, 100, 4), // "setZ"
QT_MOC_LITERAL(16, 105, 1), // "Z"
QT_MOC_LITERAL(17, 107, 7) // "setMove"

    },
    "Hw01opengl\0angles\0\0text\0center\0setShader\0"
    "on\0setPerspective\0setObject\0type\0"
    "setLighting\0setX\0X\0setY\0Y\0setZ\0Z\0"
    "setMove"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Hw01opengl[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       4,    1,   67,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   70,    2, 0x0a /* Public */,
       7,    1,   73,    2, 0x0a /* Public */,
       8,    1,   76,    2, 0x0a /* Public */,
      10,    1,   79,    2, 0x0a /* Public */,
      11,    1,   82,    2, 0x0a /* Public */,
      13,    1,   85,    2, 0x0a /* Public */,
      15,    1,   88,    2, 0x0a /* Public */,
      17,    1,   91,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::Int,    6,

       0        // eod
};

void Hw01opengl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Hw01opengl *_t = static_cast<Hw01opengl *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->angles((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->center((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->setShader((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setPerspective((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setObject((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->setLighting((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->setX((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->setY((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->setZ((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->setMove((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Hw01opengl::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Hw01opengl::angles)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Hw01opengl::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Hw01opengl::center)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject Hw01opengl::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_Hw01opengl.data,
      qt_meta_data_Hw01opengl,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Hw01opengl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Hw01opengl::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Hw01opengl.stringdata0))
        return static_cast<void*>(const_cast< Hw01opengl*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int Hw01opengl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void Hw01opengl::angles(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Hw01opengl::center(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE

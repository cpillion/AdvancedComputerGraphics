/****************************************************************************
** Meta object code from reading C++ file 'oglWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "oglWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'oglWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_oglWidget_t {
    QByteArrayData data[10];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_oglWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_oglWidget_t qt_meta_stringdata_oglWidget = {
    {
QT_MOC_LITERAL(0, 0, 9), // "oglWidget"
QT_MOC_LITERAL(1, 10, 16), // "xRotationChanged"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 5), // "angle"
QT_MOC_LITERAL(4, 34, 16), // "yRotationChanged"
QT_MOC_LITERAL(5, 51, 16), // "zRotationChanged"
QT_MOC_LITERAL(6, 68, 12), // "setXRotation"
QT_MOC_LITERAL(7, 81, 12), // "setYRotation"
QT_MOC_LITERAL(8, 94, 12), // "setZRotation"
QT_MOC_LITERAL(9, 107, 7) // "cleanup"

    },
    "oglWidget\0xRotationChanged\0\0angle\0"
    "yRotationChanged\0zRotationChanged\0"
    "setXRotation\0setYRotation\0setZRotation\0"
    "cleanup"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_oglWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    1,   52,    2, 0x06 /* Public */,
       5,    1,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   58,    2, 0x0a /* Public */,
       7,    1,   61,    2, 0x0a /* Public */,
       8,    1,   64,    2, 0x0a /* Public */,
       9,    0,   67,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,

       0        // eod
};

void oglWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        oglWidget *_t = static_cast<oglWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->xRotationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->yRotationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->zRotationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setXRotation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setYRotation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->setZRotation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->cleanup(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (oglWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&oglWidget::xRotationChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (oglWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&oglWidget::yRotationChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (oglWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&oglWidget::zRotationChanged)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject oglWidget::staticMetaObject = {
    { &CUgl::staticMetaObject, qt_meta_stringdata_oglWidget.data,
      qt_meta_data_oglWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *oglWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *oglWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_oglWidget.stringdata0))
        return static_cast<void*>(const_cast< oglWidget*>(this));
    if (!strcmp(_clname, "QOpenGLFunctions"))
        return static_cast< QOpenGLFunctions*>(const_cast< oglWidget*>(this));
    return CUgl::qt_metacast(_clname);
}

int oglWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CUgl::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void oglWidget::xRotationChanged(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void oglWidget::yRotationChanged(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void oglWidget::zRotationChanged(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

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
    QByteArrayData data[8];
    char stringdata0[51];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_oglWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_oglWidget_t qt_meta_stringdata_oglWidget = {
    {
QT_MOC_LITERAL(0, 0, 9), // "oglWidget"
QT_MOC_LITERAL(1, 10, 7), // "setMode"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 1), // "m"
QT_MOC_LITERAL(4, 21, 8), // "setMsize"
QT_MOC_LITERAL(5, 30, 3), // "pct"
QT_MOC_LITERAL(6, 34, 8), // "setHsize"
QT_MOC_LITERAL(7, 43, 7) // "cleanup"

    },
    "oglWidget\0setMode\0\0m\0setMsize\0pct\0"
    "setHsize\0cleanup"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_oglWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x0a /* Public */,
       4,    1,   37,    2, 0x0a /* Public */,
       6,    1,   40,    2, 0x0a /* Public */,
       7,    0,   43,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,

       0        // eod
};

void oglWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        oglWidget *_t = static_cast<oglWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->setMsize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setHsize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->cleanup(); break;
        default: ;
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
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'Pause.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/Pause.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Pause.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Pause_t {
    QByteArrayData data[5];
    char stringdata0[25];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Pause_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Pause_t qt_meta_stringdata_Pause = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Pause"
QT_MOC_LITERAL(1, 6, 4), // "exit"
QT_MOC_LITERAL(2, 11, 0), // ""
QT_MOC_LITERAL(3, 12, 7), // "restart"
QT_MOC_LITERAL(4, 20, 4) // "kill"

    },
    "Pause\0exit\0\0restart\0kill"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Pause[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a /* Public */,
       3,    0,   30,    2, 0x0a /* Public */,
       4,    0,   31,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Pause::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Pause *_t = static_cast<Pause *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->exit(); break;
        case 1: _t->restart(); break;
        case 2: _t->kill(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Pause::staticMetaObject = {
    { &QGraphicsProxyWidget::staticMetaObject, qt_meta_stringdata_Pause.data,
      qt_meta_data_Pause,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Pause::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Pause::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Pause.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsProxyWidget::qt_metacast(_clname);
}

int Pause::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsProxyWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'formsimulator.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/gui/formsimulator.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'formsimulator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FormSimulator_t {
    QByteArrayData data[14];
    char stringdata[178];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_FormSimulator_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_FormSimulator_t qt_meta_stringdata_FormSimulator = {
    {
QT_MOC_LITERAL(0, 0, 13),
QT_MOC_LITERAL(1, 14, 6),
QT_MOC_LITERAL(2, 21, 0),
QT_MOC_LITERAL(3, 22, 17),
QT_MOC_LITERAL(4, 40, 7),
QT_MOC_LITERAL(5, 48, 6),
QT_MOC_LITERAL(6, 55, 15),
QT_MOC_LITERAL(7, 71, 14),
QT_MOC_LITERAL(8, 86, 27),
QT_MOC_LITERAL(9, 114, 14),
QT_MOC_LITERAL(10, 129, 18),
QT_MOC_LITERAL(11, 148, 12),
QT_MOC_LITERAL(12, 161, 10),
QT_MOC_LITERAL(13, 172, 4)
    },
    "FormSimulator\0closed\0\0stopEnableChanged\0"
    "enabled\0goBack\0startSimulation\0"
    "stopSimulation\0conditionallyAttachToParent\0"
    "attachToParent\0unAttachFromParent\0"
    "setIsSticked\0is_sticked\0show\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FormSimulator[] = {

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
       1,    0,   64,    2, 0x06,
       3,    1,   65,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       5,    0,   68,    2, 0x0a,
       6,    0,   69,    2, 0x0a,
       7,    0,   70,    2, 0x0a,
       8,    0,   71,    2, 0x0a,
       9,    0,   72,    2, 0x0a,
      10,    0,   73,    2, 0x0a,
      11,    1,   74,    2, 0x0a,
      13,    0,   77,    2, 0x0a,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void,

       0        // eod
};

void FormSimulator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FormSimulator *_t = static_cast<FormSimulator *>(_o);
        switch (_id) {
        case 0: _t->closed(); break;
        case 1: _t->stopEnableChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->goBack(); break;
        case 3: _t->startSimulation(); break;
        case 4: _t->stopSimulation(); break;
        case 5: _t->conditionallyAttachToParent(); break;
        case 6: _t->attachToParent(); break;
        case 7: _t->unAttachFromParent(); break;
        case 8: _t->setIsSticked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->show(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FormSimulator::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FormSimulator::closed)) {
                *result = 0;
            }
        }
        {
            typedef void (FormSimulator::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FormSimulator::stopEnableChanged)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject FormSimulator::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FormSimulator.data,
      qt_meta_data_FormSimulator,  qt_static_metacall, 0, 0}
};


const QMetaObject *FormSimulator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FormSimulator::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FormSimulator.stringdata))
        return static_cast<void*>(const_cast< FormSimulator*>(this));
    return QDialog::qt_metacast(_clname);
}

int FormSimulator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void FormSimulator::closed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void FormSimulator::stopEnableChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE

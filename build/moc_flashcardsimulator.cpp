/****************************************************************************
** Meta object code from reading C++ file 'flashcardsimulator.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/templates/flashcard/flashcardsimulator.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'flashcardsimulator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FlashCardSimulator_t {
    QByteArrayData data[9];
    char stringdata[107];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_FlashCardSimulator_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_FlashCardSimulator_t qt_meta_stringdata_FlashCardSimulator = {
    {
QT_MOC_LITERAL(0, 0, 18),
QT_MOC_LITERAL(1, 19, 15),
QT_MOC_LITERAL(2, 35, 0),
QT_MOC_LITERAL(3, 36, 14),
QT_MOC_LITERAL(4, 51, 6),
QT_MOC_LITERAL(5, 58, 5),
QT_MOC_LITERAL(6, 64, 7),
QT_MOC_LITERAL(7, 72, 14),
QT_MOC_LITERAL(8, 87, 18)
    },
    "FlashCardSimulator\0startSimulation\0\0"
    "stopSimulation\0goBack\0start\0restart\0"
    "moveToNextCard\0moveToPreviousCard\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FlashCardSimulator[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a,
       3,    0,   50,    2, 0x0a,
       4,    0,   51,    2, 0x0a,
       5,    0,   52,    2, 0x08,
       6,    0,   53,    2, 0x08,
       7,    0,   54,    2, 0x08,
       8,    0,   55,    2, 0x08,

 // slots: parameters
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void FlashCardSimulator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FlashCardSimulator *_t = static_cast<FlashCardSimulator *>(_o);
        switch (_id) {
        case 0: { bool _r = _t->startSimulation();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 1: { bool _r = _t->stopSimulation();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: { bool _r = _t->goBack();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: _t->start(); break;
        case 4: _t->restart(); break;
        case 5: _t->moveToNextCard(); break;
        case 6: _t->moveToPreviousCard(); break;
        default: ;
        }
    }
}

const QMetaObject FlashCardSimulator::staticMetaObject = {
    { &TemplateSimulator::staticMetaObject, qt_meta_stringdata_FlashCardSimulator.data,
      qt_meta_data_FlashCardSimulator,  qt_static_metacall, 0, 0}
};


const QMetaObject *FlashCardSimulator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FlashCardSimulator::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FlashCardSimulator.stringdata))
        return static_cast<void*>(const_cast< FlashCardSimulator*>(this));
    return TemplateSimulator::qt_metacast(_clname);
}

int FlashCardSimulator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TemplateSimulator::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE

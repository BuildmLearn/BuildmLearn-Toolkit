/****************************************************************************
** Meta object code from reading C++ file 'learnspellingssimulator.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/templates/learnspellings/learnspellingssimulator.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'learnspellingssimulator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_LearnSpellingsSimulator_t {
    QByteArrayData data[12];
    char stringdata[132];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_LearnSpellingsSimulator_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_LearnSpellingsSimulator_t qt_meta_stringdata_LearnSpellingsSimulator = {
    {
QT_MOC_LITERAL(0, 0, 23),
QT_MOC_LITERAL(1, 24, 15),
QT_MOC_LITERAL(2, 40, 0),
QT_MOC_LITERAL(3, 41, 14),
QT_MOC_LITERAL(4, 56, 6),
QT_MOC_LITERAL(5, 63, 5),
QT_MOC_LITERAL(6, 69, 7),
QT_MOC_LITERAL(7, 77, 4),
QT_MOC_LITERAL(8, 82, 8),
QT_MOC_LITERAL(9, 91, 12),
QT_MOC_LITERAL(10, 104, 13),
QT_MOC_LITERAL(11, 118, 12)
    },
    "LearnSpellingsSimulator\0startSimulation\0"
    "\0stopSimulation\0goBack\0start\0restart\0"
    "exit\0playWord\0skipThisWord\0spellThisWord\0"
    "loadNextWord\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LearnSpellingsSimulator[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x0a,
       3,    0,   65,    2, 0x0a,
       4,    0,   66,    2, 0x0a,
       5,    0,   67,    2, 0x08,
       6,    0,   68,    2, 0x08,
       7,    0,   69,    2, 0x08,
       8,    0,   70,    2, 0x08,
       9,    0,   71,    2, 0x08,
      10,    0,   72,    2, 0x08,
      11,    0,   73,    2, 0x08,

 // slots: parameters
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void LearnSpellingsSimulator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LearnSpellingsSimulator *_t = static_cast<LearnSpellingsSimulator *>(_o);
        switch (_id) {
        case 0: { bool _r = _t->startSimulation();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 1: { bool _r = _t->stopSimulation();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: { bool _r = _t->goBack();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: _t->start(); break;
        case 4: _t->restart(); break;
        case 5: _t->exit(); break;
        case 6: _t->playWord(); break;
        case 7: _t->skipThisWord(); break;
        case 8: _t->spellThisWord(); break;
        case 9: _t->loadNextWord(); break;
        default: ;
        }
    }
}

const QMetaObject LearnSpellingsSimulator::staticMetaObject = {
    { &TemplateSimulator::staticMetaObject, qt_meta_stringdata_LearnSpellingsSimulator.data,
      qt_meta_data_LearnSpellingsSimulator,  qt_static_metacall, 0, 0}
};


const QMetaObject *LearnSpellingsSimulator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LearnSpellingsSimulator::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LearnSpellingsSimulator.stringdata))
        return static_cast<void*>(const_cast< LearnSpellingsSimulator*>(this));
    return TemplateSimulator::qt_metacast(_clname);
}

int LearnSpellingsSimulator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TemplateSimulator::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE

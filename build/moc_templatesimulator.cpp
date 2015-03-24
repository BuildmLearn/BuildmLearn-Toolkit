/****************************************************************************
** Meta object code from reading C++ file 'templatesimulator.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/core/templatesimulator.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'templatesimulator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TemplateSimulator_t {
    QByteArrayData data[8];
    char stringdata[111];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_TemplateSimulator_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_TemplateSimulator_t qt_meta_stringdata_TemplateSimulator = {
    {
QT_MOC_LITERAL(0, 0, 17),
QT_MOC_LITERAL(1, 18, 16),
QT_MOC_LITERAL(2, 35, 0),
QT_MOC_LITERAL(3, 36, 11),
QT_MOC_LITERAL(4, 48, 23),
QT_MOC_LITERAL(5, 72, 15),
QT_MOC_LITERAL(6, 88, 14),
QT_MOC_LITERAL(7, 103, 6)
    },
    "TemplateSimulator\0canGoBackChanged\0\0"
    "can_go_back\0simulationStopRequested\0"
    "startSimulation\0stopSimulation\0goBack\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TemplateSimulator[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06,
       4,    0,   42,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       5,    0,   43,    2, 0x0a,
       6,    0,   44,    2, 0x0a,
       7,    0,   45,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,

       0        // eod
};

void TemplateSimulator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TemplateSimulator *_t = static_cast<TemplateSimulator *>(_o);
        switch (_id) {
        case 0: _t->canGoBackChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->simulationStopRequested(); break;
        case 2: { bool _r = _t->startSimulation();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: { bool _r = _t->stopSimulation();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: { bool _r = _t->goBack();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TemplateSimulator::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TemplateSimulator::canGoBackChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (TemplateSimulator::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TemplateSimulator::simulationStopRequested)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject TemplateSimulator::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TemplateSimulator.data,
      qt_meta_data_TemplateSimulator,  qt_static_metacall, 0, 0}
};


const QMetaObject *TemplateSimulator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TemplateSimulator::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TemplateSimulator.stringdata))
        return static_cast<void*>(const_cast< TemplateSimulator*>(this));
    return QWidget::qt_metacast(_clname);
}

int TemplateSimulator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void TemplateSimulator::canGoBackChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TemplateSimulator::simulationStopRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE

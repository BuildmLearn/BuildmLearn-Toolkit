/****************************************************************************
** Meta object code from reading C++ file 'templatefactory.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/core/templatefactory.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'templatefactory.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TemplateFactory_t {
    QByteArrayData data[13];
    char stringdata[181];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TemplateFactory_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TemplateFactory_t qt_meta_stringdata_TemplateFactory = {
    {
QT_MOC_LITERAL(0, 0, 15), // "TemplateFactory"
QT_MOC_LITERAL(1, 16, 22), // "newTemplateCoreCreated"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 13), // "TemplateCore*"
QT_MOC_LITERAL(4, 54, 4), // "core"
QT_MOC_LITERAL(5, 59, 4), // "quit"
QT_MOC_LITERAL(6, 64, 15), // "startNewProject"
QT_MOC_LITERAL(7, 80, 19), // "TemplateEntryPoint*"
QT_MOC_LITERAL(8, 100, 11), // "entry_point"
QT_MOC_LITERAL(9, 112, 11), // "loadProject"
QT_MOC_LITERAL(10, 124, 16), // "bundle_file_name"
QT_MOC_LITERAL(11, 141, 20), // "saveCurrentProjectAs"
QT_MOC_LITERAL(12, 162, 18) // "saveCurrentProject"

    },
    "TemplateFactory\0newTemplateCoreCreated\0"
    "\0TemplateCore*\0core\0quit\0startNewProject\0"
    "TemplateEntryPoint*\0entry_point\0"
    "loadProject\0bundle_file_name\0"
    "saveCurrentProjectAs\0saveCurrentProject"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TemplateFactory[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   47,    2, 0x0a /* Public */,
       6,    1,   48,    2, 0x0a /* Public */,
       9,    1,   51,    2, 0x0a /* Public */,
      11,    1,   54,    2, 0x0a /* Public */,
      12,    0,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Bool, 0x80000000 | 7,    8,
    QMetaType::Bool, QMetaType::QString,   10,
    QMetaType::Bool, QMetaType::QString,   10,
    QMetaType::Bool,

       0        // eod
};

void TemplateFactory::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TemplateFactory *_t = static_cast<TemplateFactory *>(_o);
        switch (_id) {
        case 0: _t->newTemplateCoreCreated((*reinterpret_cast< TemplateCore*(*)>(_a[1]))); break;
        case 1: _t->quit(); break;
        case 2: { bool _r = _t->startNewProject((*reinterpret_cast< TemplateEntryPoint*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: { bool _r = _t->loadProject((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: { bool _r = _t->saveCurrentProjectAs((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: { bool _r = _t->saveCurrentProject();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TemplateFactory::*_t)(TemplateCore * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TemplateFactory::newTemplateCoreCreated)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject TemplateFactory::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TemplateFactory.data,
      qt_meta_data_TemplateFactory,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TemplateFactory::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TemplateFactory::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TemplateFactory.stringdata))
        return static_cast<void*>(const_cast< TemplateFactory*>(this));
    return QObject::qt_metacast(_clname);
}

int TemplateFactory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void TemplateFactory::newTemplateCoreCreated(TemplateCore * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

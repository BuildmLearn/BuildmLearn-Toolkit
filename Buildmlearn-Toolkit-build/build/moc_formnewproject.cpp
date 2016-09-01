/****************************************************************************
** Meta object code from reading C++ file 'formnewproject.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/gui/formnewproject.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'formnewproject.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FormNewProject_t {
    QByteArrayData data[6];
    char stringdata[76];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FormNewProject_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FormNewProject_t qt_meta_stringdata_FormNewProject = {
    {
QT_MOC_LITERAL(0, 0, 14), // "FormNewProject"
QT_MOC_LITERAL(1, 15, 16), // "startNewTemplate"
QT_MOC_LITERAL(2, 32, 19), // "TemplateEntryPoint*"
QT_MOC_LITERAL(3, 52, 0), // ""
QT_MOC_LITERAL(4, 53, 16), // "templateSelected"
QT_MOC_LITERAL(5, 70, 5) // "index"

    },
    "FormNewProject\0startNewTemplate\0"
    "TemplateEntryPoint*\0\0templateSelected\0"
    "index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FormNewProject[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    3, 0x0a /* Public */,
       4,    1,   25,    3, 0x08 /* Private */,

 // slots: parameters
    0x80000000 | 2,
    QMetaType::Void, QMetaType::Int,    5,

       0        // eod
};

void FormNewProject::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FormNewProject *_t = static_cast<FormNewProject *>(_o);
        switch (_id) {
        case 0: { TemplateEntryPoint* _r = _t->startNewTemplate();
            if (_a[0]) *reinterpret_cast< TemplateEntryPoint**>(_a[0]) = _r; }  break;
        case 1: _t->templateSelected((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject FormNewProject::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FormNewProject.data,
      qt_meta_data_FormNewProject,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FormNewProject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FormNewProject::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FormNewProject.stringdata))
        return static_cast<void*>(const_cast< FormNewProject*>(this));
    return QDialog::qt_metacast(_clname);
}

int FormNewProject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

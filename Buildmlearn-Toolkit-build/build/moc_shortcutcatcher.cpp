/****************************************************************************
** Meta object code from reading C++ file 'shortcutcatcher.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/dynamic-shortcuts/shortcutcatcher.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'shortcutcatcher.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ShortcutCatcher_t {
    QByteArrayData data[8];
    char stringdata[99];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ShortcutCatcher_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ShortcutCatcher_t qt_meta_stringdata_ShortcutCatcher = {
    {
QT_MOC_LITERAL(0, 0, 15), // "ShortcutCatcher"
QT_MOC_LITERAL(1, 16, 15), // "shortcutChanged"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 8), // "seguence"
QT_MOC_LITERAL(4, 42, 13), // "resetShortcut"
QT_MOC_LITERAL(5, 56, 13), // "clearShortcut"
QT_MOC_LITERAL(6, 70, 14), // "startRecording"
QT_MOC_LITERAL(7, 85, 13) // "doneRecording"

    },
    "ShortcutCatcher\0shortcutChanged\0\0"
    "seguence\0resetShortcut\0clearShortcut\0"
    "startRecording\0doneRecording"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ShortcutCatcher[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   42,    2, 0x0a /* Public */,
       5,    0,   43,    2, 0x0a /* Public */,
       6,    0,   44,    2, 0x09 /* Protected */,
       7,    0,   45,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::QKeySequence,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ShortcutCatcher::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ShortcutCatcher *_t = static_cast<ShortcutCatcher *>(_o);
        switch (_id) {
        case 0: _t->shortcutChanged((*reinterpret_cast< const QKeySequence(*)>(_a[1]))); break;
        case 1: _t->resetShortcut(); break;
        case 2: _t->clearShortcut(); break;
        case 3: _t->startRecording(); break;
        case 4: _t->doneRecording(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ShortcutCatcher::*_t)(const QKeySequence & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ShortcutCatcher::shortcutChanged)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject ShortcutCatcher::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ShortcutCatcher.data,
      qt_meta_data_ShortcutCatcher,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ShortcutCatcher::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ShortcutCatcher::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ShortcutCatcher.stringdata))
        return static_cast<void*>(const_cast< ShortcutCatcher*>(this));
    return QWidget::qt_metacast(_clname);
}

int ShortcutCatcher::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void ShortcutCatcher::shortcutChanged(const QKeySequence & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

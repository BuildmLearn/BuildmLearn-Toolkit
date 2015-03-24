/****************************************************************************
** Meta object code from reading C++ file 'flashcarditem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/templates/flashcard/flashcarditem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'flashcarditem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FlashCardItem_t {
    QByteArrayData data[6];
    char stringdata[72];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FlashCardItem_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FlashCardItem_t qt_meta_stringdata_FlashCardItem = {
    {
QT_MOC_LITERAL(0, 0, 13), // "FlashCardItem"
QT_MOC_LITERAL(1, 14, 17), // "nextCardRequested"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 21), // "previousCardRequested"
QT_MOC_LITERAL(4, 55, 4), // "flip"
QT_MOC_LITERAL(5, 60, 11) // "target_side"

    },
    "FlashCardItem\0nextCardRequested\0\0"
    "previousCardRequested\0flip\0target_side"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FlashCardItem[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   36,    2, 0x08 /* Private */,
       4,    0,   39,    2, 0x28 /* Private | MethodCloned */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,

       0        // eod
};

void FlashCardItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FlashCardItem *_t = static_cast<FlashCardItem *>(_o);
        switch (_id) {
        case 0: _t->nextCardRequested(); break;
        case 1: _t->previousCardRequested(); break;
        case 2: _t->flip((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->flip(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FlashCardItem::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FlashCardItem::nextCardRequested)) {
                *result = 0;
            }
        }
        {
            typedef void (FlashCardItem::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FlashCardItem::previousCardRequested)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject FlashCardItem::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FlashCardItem.data,
      qt_meta_data_FlashCardItem,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FlashCardItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FlashCardItem::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FlashCardItem.stringdata))
        return static_cast<void*>(const_cast< FlashCardItem*>(this));
    return QWidget::qt_metacast(_clname);
}

int FlashCardItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void FlashCardItem::nextCardRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void FlashCardItem::previousCardRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'comprehensionquestionitem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/templates/comprehension/comprehensionquestionitem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'comprehensionquestionitem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ComprehensionQuestionItem_t {
    QByteArrayData data[6];
    char stringdata[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ComprehensionQuestionItem_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ComprehensionQuestionItem_t qt_meta_stringdata_ComprehensionQuestionItem = {
    {
QT_MOC_LITERAL(0, 0, 25), // "ComprehensionQuestionItem"
QT_MOC_LITERAL(1, 26, 17), // "questionSubmitted"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 5), // "reset"
QT_MOC_LITERAL(4, 51, 13), // "onNextClicked"
QT_MOC_LITERAL(5, 65, 15) // "onSubmitClicked"

    },
    "ComprehensionQuestionItem\0questionSubmitted\0"
    "\0reset\0onNextClicked\0onSubmitClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ComprehensionQuestionItem[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   35,    2, 0x0a /* Public */,
       4,    0,   36,    2, 0x08 /* Private */,
       5,    0,   37,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ComprehensionQuestionItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ComprehensionQuestionItem *_t = static_cast<ComprehensionQuestionItem *>(_o);
        switch (_id) {
        case 0: _t->questionSubmitted(); break;
        case 1: _t->reset(); break;
        case 2: _t->onNextClicked(); break;
        case 3: _t->onSubmitClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ComprehensionQuestionItem::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ComprehensionQuestionItem::questionSubmitted)) {
                *result = 0;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ComprehensionQuestionItem::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ComprehensionQuestionItem.data,
      qt_meta_data_ComprehensionQuestionItem,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ComprehensionQuestionItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ComprehensionQuestionItem::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ComprehensionQuestionItem.stringdata))
        return static_cast<void*>(const_cast< ComprehensionQuestionItem*>(this));
    return QWidget::qt_metacast(_clname);
}

int ComprehensionQuestionItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void ComprehensionQuestionItem::questionSubmitted()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE

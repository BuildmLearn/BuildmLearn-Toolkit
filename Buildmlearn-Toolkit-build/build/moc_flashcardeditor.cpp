/****************************************************************************
** Meta object code from reading C++ file 'flashcardeditor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/templates/flashcard/flashcardeditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'flashcardeditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FlashCardEditor_t {
    QByteArrayData data[27];
    char stringdata[330];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FlashCardEditor_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FlashCardEditor_t qt_meta_stringdata_FlashCardEditor = {
    {
QT_MOC_LITERAL(0, 0, 15), // "FlashCardEditor"
QT_MOC_LITERAL(1, 16, 11), // "loadPicture"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 12), // "picture_path"
QT_MOC_LITERAL(4, 42, 17), // "setEditorsEnabled"
QT_MOC_LITERAL(5, 60, 7), // "enabled"
QT_MOC_LITERAL(6, 68, 19), // "updateQuestionCount"
QT_MOC_LITERAL(7, 88, 11), // "addQuestion"
QT_MOC_LITERAL(8, 100, 12), // "loadQuestion"
QT_MOC_LITERAL(9, 113, 5), // "index"
QT_MOC_LITERAL(10, 119, 12), // "saveQuestion"
QT_MOC_LITERAL(11, 132, 14), // "removeQuestion"
QT_MOC_LITERAL(12, 147, 15), // "onAnswerChanged"
QT_MOC_LITERAL(13, 163, 10), // "new_answer"
QT_MOC_LITERAL(14, 174, 13), // "onHintChanged"
QT_MOC_LITERAL(15, 188, 8), // "new_hint"
QT_MOC_LITERAL(16, 197, 15), // "onAuthorChanged"
QT_MOC_LITERAL(17, 213, 10), // "new_author"
QT_MOC_LITERAL(18, 224, 13), // "onNameChanged"
QT_MOC_LITERAL(19, 238, 8), // "new_name"
QT_MOC_LITERAL(20, 247, 13), // "selectPicture"
QT_MOC_LITERAL(21, 261, 15), // "configureUpDown"
QT_MOC_LITERAL(22, 277, 14), // "moveQuestionUp"
QT_MOC_LITERAL(23, 292, 16), // "moveQuestionDown"
QT_MOC_LITERAL(24, 309, 8), // "question"
QT_MOC_LITERAL(25, 318, 6), // "answer"
QT_MOC_LITERAL(26, 325, 4) // "hint"

    },
    "FlashCardEditor\0loadPicture\0\0picture_path\0"
    "setEditorsEnabled\0enabled\0updateQuestionCount\0"
    "addQuestion\0loadQuestion\0index\0"
    "saveQuestion\0removeQuestion\0onAnswerChanged\0"
    "new_answer\0onHintChanged\0new_hint\0"
    "onAuthorChanged\0new_author\0onNameChanged\0"
    "new_name\0selectPicture\0configureUpDown\0"
    "moveQuestionUp\0moveQuestionDown\0"
    "question\0answer\0hint"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FlashCardEditor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x08 /* Private */,
       4,    1,   97,    2, 0x08 /* Private */,
       6,    0,  100,    2, 0x08 /* Private */,
       7,    0,  101,    2, 0x08 /* Private */,
       8,    1,  102,    2, 0x08 /* Private */,
      10,    0,  105,    2, 0x08 /* Private */,
      11,    0,  106,    2, 0x08 /* Private */,
      12,    1,  107,    2, 0x08 /* Private */,
      14,    1,  110,    2, 0x08 /* Private */,
      16,    1,  113,    2, 0x08 /* Private */,
      18,    1,  116,    2, 0x08 /* Private */,
      20,    0,  119,    2, 0x08 /* Private */,
      21,    0,  120,    2, 0x08 /* Private */,
      22,    0,  121,    2, 0x08 /* Private */,
      23,    0,  122,    2, 0x08 /* Private */,
       7,    4,  123,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void, QMetaType::QString,   19,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   24,   25,   26,    3,

       0        // eod
};

void FlashCardEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FlashCardEditor *_t = static_cast<FlashCardEditor *>(_o);
        switch (_id) {
        case 0: _t->loadPicture((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->setEditorsEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->updateQuestionCount(); break;
        case 3: _t->addQuestion(); break;
        case 4: _t->loadQuestion((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->saveQuestion(); break;
        case 6: _t->removeQuestion(); break;
        case 7: _t->onAnswerChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->onHintChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->onAuthorChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->onNameChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->selectPicture(); break;
        case 12: _t->configureUpDown(); break;
        case 13: _t->moveQuestionUp(); break;
        case 14: _t->moveQuestionDown(); break;
        case 15: _t->addQuestion((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        default: ;
        }
    }
}

const QMetaObject FlashCardEditor::staticMetaObject = {
    { &TemplateEditor::staticMetaObject, qt_meta_stringdata_FlashCardEditor.data,
      qt_meta_data_FlashCardEditor,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FlashCardEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FlashCardEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FlashCardEditor.stringdata))
        return static_cast<void*>(const_cast< FlashCardEditor*>(this));
    return TemplateEditor::qt_metacast(_clname);
}

int FlashCardEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TemplateEditor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

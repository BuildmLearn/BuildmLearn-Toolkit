/****************************************************************************
** Meta object code from reading C++ file 'quizeditor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/templates/quiz/quizeditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'quizeditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QuizEditor_t {
    QByteArrayData data[20];
    char stringdata[255];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QuizEditor_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QuizEditor_t qt_meta_stringdata_QuizEditor = {
    {
QT_MOC_LITERAL(0, 0, 10), // "QuizEditor"
QT_MOC_LITERAL(1, 11, 19), // "updateQuestionCount"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 11), // "addQuestion"
QT_MOC_LITERAL(4, 44, 8), // "question"
QT_MOC_LITERAL(5, 53, 7), // "answers"
QT_MOC_LITERAL(6, 61, 14), // "correct_answer"
QT_MOC_LITERAL(7, 76, 12), // "loadQuestion"
QT_MOC_LITERAL(8, 89, 5), // "index"
QT_MOC_LITERAL(9, 95, 14), // "removeQuestion"
QT_MOC_LITERAL(10, 110, 12), // "saveQuestion"
QT_MOC_LITERAL(11, 123, 14), // "moveQuestionUp"
QT_MOC_LITERAL(12, 138, 16), // "moveQuestionDown"
QT_MOC_LITERAL(13, 155, 15), // "configureUpDown"
QT_MOC_LITERAL(14, 171, 17), // "setEditorsEnabled"
QT_MOC_LITERAL(15, 189, 7), // "enabled"
QT_MOC_LITERAL(16, 197, 9), // "checkName"
QT_MOC_LITERAL(17, 207, 11), // "checkAuthor"
QT_MOC_LITERAL(18, 219, 16), // "updateNameStatus"
QT_MOC_LITERAL(19, 236, 18) // "updateAuthorStatus"

    },
    "QuizEditor\0updateQuestionCount\0\0"
    "addQuestion\0question\0answers\0"
    "correct_answer\0loadQuestion\0index\0"
    "removeQuestion\0saveQuestion\0moveQuestionUp\0"
    "moveQuestionDown\0configureUpDown\0"
    "setEditorsEnabled\0enabled\0checkName\0"
    "checkAuthor\0updateNameStatus\0"
    "updateAuthorStatus"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QuizEditor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    3,   85,    2, 0x08 /* Private */,
       3,    0,   92,    2, 0x08 /* Private */,
       7,    1,   93,    2, 0x08 /* Private */,
       9,    0,   96,    2, 0x08 /* Private */,
      10,    0,   97,    2, 0x08 /* Private */,
      11,    0,   98,    2, 0x08 /* Private */,
      12,    0,   99,    2, 0x08 /* Private */,
      13,    0,  100,    2, 0x08 /* Private */,
      14,    1,  101,    2, 0x08 /* Private */,
      16,    0,  104,    2, 0x08 /* Private */,
      17,    0,  105,    2, 0x08 /* Private */,
      18,    0,  106,    2, 0x08 /* Private */,
      19,    0,  107,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QStringList, QMetaType::Int,    4,    5,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QuizEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QuizEditor *_t = static_cast<QuizEditor *>(_o);
        switch (_id) {
        case 0: _t->updateQuestionCount(); break;
        case 1: _t->addQuestion((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QStringList(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->addQuestion(); break;
        case 3: _t->loadQuestion((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->removeQuestion(); break;
        case 5: _t->saveQuestion(); break;
        case 6: _t->moveQuestionUp(); break;
        case 7: _t->moveQuestionDown(); break;
        case 8: _t->configureUpDown(); break;
        case 9: _t->setEditorsEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->checkName(); break;
        case 11: _t->checkAuthor(); break;
        case 12: _t->updateNameStatus(); break;
        case 13: _t->updateAuthorStatus(); break;
        default: ;
        }
    }
}

const QMetaObject QuizEditor::staticMetaObject = {
    { &TemplateEditor::staticMetaObject, qt_meta_stringdata_QuizEditor.data,
      qt_meta_data_QuizEditor,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QuizEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QuizEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QuizEditor.stringdata))
        return static_cast<void*>(const_cast< QuizEditor*>(this));
    return TemplateEditor::qt_metacast(_clname);
}

int QuizEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TemplateEditor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

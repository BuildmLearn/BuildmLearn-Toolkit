/****************************************************************************
** Meta object code from reading C++ file 'learnspellingseditor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/templates/learnspellings/learnspellingseditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'learnspellingseditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_LearnSpellingsEditor_t {
    QByteArrayData data[21];
    char stringdata[256];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LearnSpellingsEditor_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LearnSpellingsEditor_t qt_meta_stringdata_LearnSpellingsEditor = {
    {
QT_MOC_LITERAL(0, 0, 20), // "LearnSpellingsEditor"
QT_MOC_LITERAL(1, 21, 13), // "addSampleWord"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 5), // "title"
QT_MOC_LITERAL(4, 42, 11), // "description"
QT_MOC_LITERAL(5, 54, 18), // "removeSelectedWord"
QT_MOC_LITERAL(6, 73, 8), // "saveWord"
QT_MOC_LITERAL(7, 82, 11), // "displayWord"
QT_MOC_LITERAL(8, 94, 5), // "index"
QT_MOC_LITERAL(9, 100, 10), // "checkTitle"
QT_MOC_LITERAL(10, 111, 16), // "checkDescription"
QT_MOC_LITERAL(11, 128, 10), // "moveWordUp"
QT_MOC_LITERAL(12, 139, 12), // "moveWordDown"
QT_MOC_LITERAL(13, 152, 15), // "configureUpDown"
QT_MOC_LITERAL(14, 168, 15), // "updateItemCount"
QT_MOC_LITERAL(15, 184, 11), // "checkAuthor"
QT_MOC_LITERAL(16, 196, 9), // "checkName"
QT_MOC_LITERAL(17, 206, 15), // "onAuthorChanged"
QT_MOC_LITERAL(18, 222, 10), // "new_author"
QT_MOC_LITERAL(19, 233, 13), // "onNameChanged"
QT_MOC_LITERAL(20, 247, 8) // "new_name"

    },
    "LearnSpellingsEditor\0addSampleWord\0\0"
    "title\0description\0removeSelectedWord\0"
    "saveWord\0displayWord\0index\0checkTitle\0"
    "checkDescription\0moveWordUp\0moveWordDown\0"
    "configureUpDown\0updateItemCount\0"
    "checkAuthor\0checkName\0onAuthorChanged\0"
    "new_author\0onNameChanged\0new_name"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LearnSpellingsEditor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   89,    2, 0x08 /* Private */,
       1,    0,   94,    2, 0x08 /* Private */,
       5,    0,   95,    2, 0x08 /* Private */,
       6,    0,   96,    2, 0x08 /* Private */,
       7,    1,   97,    2, 0x08 /* Private */,
       9,    1,  100,    2, 0x08 /* Private */,
      10,    1,  103,    2, 0x08 /* Private */,
      11,    0,  106,    2, 0x08 /* Private */,
      12,    0,  107,    2, 0x08 /* Private */,
      13,    0,  108,    2, 0x08 /* Private */,
      14,    0,  109,    2, 0x08 /* Private */,
      15,    0,  110,    2, 0x08 /* Private */,
      16,    0,  111,    2, 0x08 /* Private */,
      17,    1,  112,    2, 0x08 /* Private */,
      19,    1,  115,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::Void, QMetaType::QString,   20,

       0        // eod
};

void LearnSpellingsEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LearnSpellingsEditor *_t = static_cast<LearnSpellingsEditor *>(_o);
        switch (_id) {
        case 0: _t->addSampleWord((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->addSampleWord(); break;
        case 2: _t->removeSelectedWord(); break;
        case 3: _t->saveWord(); break;
        case 4: _t->displayWord((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->checkTitle((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->checkDescription((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->moveWordUp(); break;
        case 8: _t->moveWordDown(); break;
        case 9: _t->configureUpDown(); break;
        case 10: _t->updateItemCount(); break;
        case 11: _t->checkAuthor(); break;
        case 12: _t->checkName(); break;
        case 13: _t->onAuthorChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 14: _t->onNameChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject LearnSpellingsEditor::staticMetaObject = {
    { &TemplateEditor::staticMetaObject, qt_meta_stringdata_LearnSpellingsEditor.data,
      qt_meta_data_LearnSpellingsEditor,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *LearnSpellingsEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LearnSpellingsEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_LearnSpellingsEditor.stringdata))
        return static_cast<void*>(const_cast< LearnSpellingsEditor*>(this));
    return TemplateEditor::qt_metacast(_clname);
}

int LearnSpellingsEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TemplateEditor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

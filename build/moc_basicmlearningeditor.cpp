/****************************************************************************
** Meta object code from reading C++ file 'basicmlearningeditor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/templates/mlearning/basicmlearningeditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'basicmlearningeditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_BasicmLearningEditor_t {
    QByteArrayData data[20];
    char stringdata[237];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_BasicmLearningEditor_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_BasicmLearningEditor_t qt_meta_stringdata_BasicmLearningEditor = {
    {
QT_MOC_LITERAL(0, 0, 20),
QT_MOC_LITERAL(1, 21, 10),
QT_MOC_LITERAL(2, 32, 0),
QT_MOC_LITERAL(3, 33, 5),
QT_MOC_LITERAL(4, 39, 11),
QT_MOC_LITERAL(5, 51, 18),
QT_MOC_LITERAL(6, 70, 8),
QT_MOC_LITERAL(7, 79, 11),
QT_MOC_LITERAL(8, 91, 5),
QT_MOC_LITERAL(9, 97, 10),
QT_MOC_LITERAL(10, 108, 10),
QT_MOC_LITERAL(11, 119, 12),
QT_MOC_LITERAL(12, 132, 15),
QT_MOC_LITERAL(13, 148, 15),
QT_MOC_LITERAL(14, 164, 11),
QT_MOC_LITERAL(15, 176, 9),
QT_MOC_LITERAL(16, 186, 15),
QT_MOC_LITERAL(17, 202, 10),
QT_MOC_LITERAL(18, 213, 13),
QT_MOC_LITERAL(19, 227, 8)
    },
    "BasicmLearningEditor\0addNewItem\0\0title\0"
    "description\0removeSelectedItem\0saveItem\0"
    "displayItem\0index\0checkTitle\0moveItemUp\0"
    "moveItemDown\0configureUpDown\0"
    "updateItemCount\0checkAuthor\0checkName\0"
    "onAuthorChanged\0new_author\0onNameChanged\0"
    "new_name\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BasicmLearningEditor[] = {

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
       1,    2,   84,    2, 0x08,
       1,    0,   89,    2, 0x08,
       5,    0,   90,    2, 0x08,
       6,    0,   91,    2, 0x08,
       7,    1,   92,    2, 0x08,
       9,    1,   95,    2, 0x08,
      10,    0,   98,    2, 0x08,
      11,    0,   99,    2, 0x08,
      12,    0,  100,    2, 0x08,
      13,    0,  101,    2, 0x08,
      14,    0,  102,    2, 0x08,
      15,    0,  103,    2, 0x08,
      16,    1,  104,    2, 0x08,
      18,    1,  107,    2, 0x08,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void, QMetaType::QString,   19,

       0        // eod
};

void BasicmLearningEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BasicmLearningEditor *_t = static_cast<BasicmLearningEditor *>(_o);
        switch (_id) {
        case 0: _t->addNewItem((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->addNewItem(); break;
        case 2: _t->removeSelectedItem(); break;
        case 3: _t->saveItem(); break;
        case 4: _t->displayItem((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->checkTitle((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->moveItemUp(); break;
        case 7: _t->moveItemDown(); break;
        case 8: _t->configureUpDown(); break;
        case 9: _t->updateItemCount(); break;
        case 10: _t->checkAuthor(); break;
        case 11: _t->checkName(); break;
        case 12: _t->onAuthorChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 13: _t->onNameChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject BasicmLearningEditor::staticMetaObject = {
    { &TemplateEditor::staticMetaObject, qt_meta_stringdata_BasicmLearningEditor.data,
      qt_meta_data_BasicmLearningEditor,  qt_static_metacall, 0, 0}
};


const QMetaObject *BasicmLearningEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BasicmLearningEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BasicmLearningEditor.stringdata))
        return static_cast<void*>(const_cast< BasicmLearningEditor*>(this));
    return TemplateEditor::qt_metacast(_clname);
}

int BasicmLearningEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

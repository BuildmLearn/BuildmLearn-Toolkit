/****************************************************************************
** Meta object code from reading C++ file 'formupdate.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/gui/formupdate.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'formupdate.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FormUpdate_t {
    QByteArrayData data[13];
    char stringdata[172];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_FormUpdate_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_FormUpdate_t qt_meta_stringdata_FormUpdate = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 15),
QT_MOC_LITERAL(2, 27, 0),
QT_MOC_LITERAL(3, 28, 11),
QT_MOC_LITERAL(4, 40, 14),
QT_MOC_LITERAL(5, 55, 14),
QT_MOC_LITERAL(6, 70, 11),
QT_MOC_LITERAL(7, 82, 15),
QT_MOC_LITERAL(8, 98, 27),
QT_MOC_LITERAL(9, 126, 6),
QT_MOC_LITERAL(10, 133, 8),
QT_MOC_LITERAL(11, 142, 14),
QT_MOC_LITERAL(12, 157, 13)
    },
    "FormUpdate\0checkForUpdates\0\0startUpdate\0"
    "updateProgress\0bytes_received\0bytes_total\0"
    "updateCompleted\0QNetworkReply::NetworkError\0"
    "status\0contents\0saveUpdateFile\0"
    "file_contents\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FormUpdate[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x09,
       3,    0,   40,    2, 0x09,
       4,    2,   41,    2, 0x09,
       7,    2,   46,    2, 0x09,
      11,    1,   51,    2, 0x09,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    5,    6,
    QMetaType::Void, 0x80000000 | 8, QMetaType::QByteArray,    9,   10,
    QMetaType::Void, QMetaType::QByteArray,   12,

       0        // eod
};

void FormUpdate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FormUpdate *_t = static_cast<FormUpdate *>(_o);
        switch (_id) {
        case 0: _t->checkForUpdates(); break;
        case 1: _t->startUpdate(); break;
        case 2: _t->updateProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 3: _t->updateCompleted((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 4: _t->saveUpdateFile((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply::NetworkError >(); break;
            }
            break;
        }
    }
}

const QMetaObject FormUpdate::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FormUpdate.data,
      qt_meta_data_FormUpdate,  qt_static_metacall, 0, 0}
};


const QMetaObject *FormUpdate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FormUpdate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FormUpdate.stringdata))
        return static_cast<void*>(const_cast< FormUpdate*>(this));
    return QDialog::qt_metacast(_clname);
}

int FormUpdate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

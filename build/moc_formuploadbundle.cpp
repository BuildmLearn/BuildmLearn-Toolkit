/****************************************************************************
** Meta object code from reading C++ file 'formuploadbundle.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/gui/formuploadbundle.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'formuploadbundle.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FormUploadBundle_t {
    QByteArrayData data[21];
    char stringdata[305];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_FormUploadBundle_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_FormUploadBundle_t qt_meta_stringdata_FormUploadBundle = {
    {
QT_MOC_LITERAL(0, 0, 16),
QT_MOC_LITERAL(1, 17, 15),
QT_MOC_LITERAL(2, 33, 0),
QT_MOC_LITERAL(3, 34, 15),
QT_MOC_LITERAL(4, 50, 11),
QT_MOC_LITERAL(5, 62, 16),
QT_MOC_LITERAL(6, 79, 12),
QT_MOC_LITERAL(7, 92, 20),
QT_MOC_LITERAL(8, 113, 16),
QT_MOC_LITERAL(9, 130, 13),
QT_MOC_LITERAL(10, 144, 21),
QT_MOC_LITERAL(11, 166, 20),
QT_MOC_LITERAL(12, 187, 9),
QT_MOC_LITERAL(13, 197, 11),
QT_MOC_LITERAL(14, 209, 14),
QT_MOC_LITERAL(15, 224, 10),
QT_MOC_LITERAL(16, 235, 11),
QT_MOC_LITERAL(17, 247, 15),
QT_MOC_LITERAL(18, 263, 27),
QT_MOC_LITERAL(19, 291, 5),
QT_MOC_LITERAL(20, 297, 6)
    },
    "FormUploadBundle\0metadataChanged\0\0"
    "checkAuthorName\0author_name\0"
    "checkAuthorEmail\0author_email\0"
    "checkApplicationName\0application_name\0"
    "checkMetadata\0selectApplicationIcon\0"
    "checkApplicationIcon\0icon_path\0"
    "startUpload\0uploadProgress\0bytes_sent\0"
    "bytes_total\0uploadCompleted\0"
    "QNetworkReply::NetworkError\0error\0"
    "output\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FormUploadBundle[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       3,    1,   65,    2, 0x08,
       5,    1,   68,    2, 0x08,
       7,    1,   71,    2, 0x08,
       9,    0,   74,    2, 0x08,
      10,    0,   75,    2, 0x08,
      11,    1,   76,    2, 0x08,
      13,    0,   79,    2, 0x08,
      14,    2,   80,    2, 0x08,
      17,    2,   85,    2, 0x08,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,   15,   16,
    QMetaType::Void, 0x80000000 | 18, QMetaType::QByteArray,   19,   20,

       0        // eod
};

void FormUploadBundle::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FormUploadBundle *_t = static_cast<FormUploadBundle *>(_o);
        switch (_id) {
        case 0: _t->metadataChanged(); break;
        case 1: _t->checkAuthorName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->checkAuthorEmail((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->checkApplicationName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->checkMetadata(); break;
        case 5: _t->selectApplicationIcon(); break;
        case 6: _t->checkApplicationIcon((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->startUpload(); break;
        case 8: _t->uploadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 9: _t->uploadCompleted((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply::NetworkError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FormUploadBundle::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FormUploadBundle::metadataChanged)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject FormUploadBundle::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FormUploadBundle.data,
      qt_meta_data_FormUploadBundle,  qt_static_metacall, 0, 0}
};


const QMetaObject *FormUploadBundle::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FormUploadBundle::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FormUploadBundle.stringdata))
        return static_cast<void*>(const_cast< FormUploadBundle*>(this));
    return QDialog::qt_metacast(_clname);
}

int FormUploadBundle::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void FormUploadBundle::metadataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE

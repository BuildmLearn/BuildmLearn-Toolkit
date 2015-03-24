/****************************************************************************
** Meta object code from reading C++ file 'silentnetworkaccessmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/network-web/silentnetworkaccessmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'silentnetworkaccessmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SilentNetworkAccessManager_t {
    QByteArrayData data[7];
    char stringdata[105];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_SilentNetworkAccessManager_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_SilentNetworkAccessManager_t qt_meta_stringdata_SilentNetworkAccessManager = {
    {
QT_MOC_LITERAL(0, 0, 26),
QT_MOC_LITERAL(1, 27, 24),
QT_MOC_LITERAL(2, 52, 0),
QT_MOC_LITERAL(3, 53, 14),
QT_MOC_LITERAL(4, 68, 5),
QT_MOC_LITERAL(5, 74, 15),
QT_MOC_LITERAL(6, 90, 13)
    },
    "SilentNetworkAccessManager\0"
    "onAuthenticationRequired\0\0QNetworkReply*\0"
    "reply\0QAuthenticator*\0authenticator\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SilentNetworkAccessManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   19,    2, 0x09,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,

       0        // eod
};

void SilentNetworkAccessManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SilentNetworkAccessManager *_t = static_cast<SilentNetworkAccessManager *>(_o);
        switch (_id) {
        case 0: _t->onAuthenticationRequired((*reinterpret_cast< QNetworkReply*(*)>(_a[1])),(*reinterpret_cast< QAuthenticator*(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject SilentNetworkAccessManager::staticMetaObject = {
    { &BaseNetworkAccessManager::staticMetaObject, qt_meta_stringdata_SilentNetworkAccessManager.data,
      qt_meta_data_SilentNetworkAccessManager,  qt_static_metacall, 0, 0}
};


const QMetaObject *SilentNetworkAccessManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SilentNetworkAccessManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SilentNetworkAccessManager.stringdata))
        return static_cast<void*>(const_cast< SilentNetworkAccessManager*>(this));
    return BaseNetworkAccessManager::qt_metacast(_clname);
}

int SilentNetworkAccessManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseNetworkAccessManager::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

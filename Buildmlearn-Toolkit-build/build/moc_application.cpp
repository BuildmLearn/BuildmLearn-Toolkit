/****************************************************************************
** Meta object code from reading C++ file 'application.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/miscellaneous/application.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'application.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Application_t {
    QByteArrayData data[10];
    char stringdata[164];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Application_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Application_t qt_meta_stringdata_Application = {
    {
QT_MOC_LITERAL(0, 0, 11), // "Application"
QT_MOC_LITERAL(1, 12, 29), // "externalApplicationsRechecked"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 27), // "checkForUpdatesOnBackground"
QT_MOC_LITERAL(4, 71, 13), // "onAboutToQuit"
QT_MOC_LITERAL(5, 85, 12), // "onCommitData"
QT_MOC_LITERAL(6, 98, 16), // "QSessionManager&"
QT_MOC_LITERAL(7, 115, 7), // "manager"
QT_MOC_LITERAL(8, 123, 11), // "onSaveState"
QT_MOC_LITERAL(9, 135, 28) // "handleBackgroundUpdatesCheck"

    },
    "Application\0externalApplicationsRechecked\0"
    "\0checkForUpdatesOnBackground\0onAboutToQuit\0"
    "onCommitData\0QSessionManager&\0manager\0"
    "onSaveState\0handleBackgroundUpdatesCheck"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Application[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   45,    2, 0x0a /* Public */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    1,   47,    2, 0x08 /* Private */,
       8,    1,   50,    2, 0x08 /* Private */,
       9,    0,   53,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,

       0        // eod
};

void Application::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Application *_t = static_cast<Application *>(_o);
        switch (_id) {
        case 0: _t->externalApplicationsRechecked(); break;
        case 1: _t->checkForUpdatesOnBackground(); break;
        case 2: _t->onAboutToQuit(); break;
        case 3: _t->onCommitData((*reinterpret_cast< QSessionManager(*)>(_a[1]))); break;
        case 4: _t->onSaveState((*reinterpret_cast< QSessionManager(*)>(_a[1]))); break;
        case 5: _t->handleBackgroundUpdatesCheck(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Application::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Application::externalApplicationsRechecked)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject Application::staticMetaObject = {
    { &QApplication::staticMetaObject, qt_meta_stringdata_Application.data,
      qt_meta_data_Application,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Application::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Application::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Application.stringdata))
        return static_cast<void*>(const_cast< Application*>(this));
    return QApplication::qt_metacast(_clname);
}

int Application::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QApplication::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void Application::externalApplicationsRechecked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE

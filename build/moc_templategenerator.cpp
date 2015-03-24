/****************************************************************************
** Meta object code from reading C++ file 'templategenerator.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/core/templategenerator.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'templategenerator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TemplateGenerator_t {
    QByteArrayData data[15];
    char stringdata[225];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_TemplateGenerator_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_TemplateGenerator_t qt_meta_stringdata_TemplateGenerator = {
    {
QT_MOC_LITERAL(0, 0, 17),
QT_MOC_LITERAL(1, 18, 17),
QT_MOC_LITERAL(2, 36, 0),
QT_MOC_LITERAL(3, 37, 18),
QT_MOC_LITERAL(4, 56, 30),
QT_MOC_LITERAL(5, 87, 11),
QT_MOC_LITERAL(6, 99, 11),
QT_MOC_LITERAL(7, 111, 18),
QT_MOC_LITERAL(8, 130, 8),
QT_MOC_LITERAL(9, 139, 7),
QT_MOC_LITERAL(10, 147, 25),
QT_MOC_LITERAL(11, 173, 13),
QT_MOC_LITERAL(12, 187, 4),
QT_MOC_LITERAL(13, 192, 14),
QT_MOC_LITERAL(14, 207, 16)
    },
    "TemplateGenerator\0generationStarted\0"
    "\0generationFinished\0TemplateCore::GenerationResult\0"
    "result_code\0output_file\0generationProgress\0"
    "progress\0message\0generateMobileApplication\0"
    "TemplateCore*\0core\0cleanWorkspace\0"
    "refreshWorkspace\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TemplateGenerator[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06,
       3,    2,   50,    2, 0x06,
       3,    1,   55,    2, 0x26,
       7,    2,   58,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
      10,    1,   63,    2, 0x0a,
      13,    0,   66,    2, 0x0a,
      14,    0,   67,    2, 0x0a,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, QMetaType::QString,    5,    6,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    8,    9,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TemplateGenerator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TemplateGenerator *_t = static_cast<TemplateGenerator *>(_o);
        switch (_id) {
        case 0: _t->generationStarted(); break;
        case 1: _t->generationFinished((*reinterpret_cast< TemplateCore::GenerationResult(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->generationFinished((*reinterpret_cast< TemplateCore::GenerationResult(*)>(_a[1]))); break;
        case 3: _t->generationProgress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 4: _t->generateMobileApplication((*reinterpret_cast< TemplateCore*(*)>(_a[1]))); break;
        case 5: _t->cleanWorkspace(); break;
        case 6: _t->refreshWorkspace(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TemplateCore* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TemplateGenerator::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TemplateGenerator::generationStarted)) {
                *result = 0;
            }
        }
        {
            typedef void (TemplateGenerator::*_t)(TemplateCore::GenerationResult , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TemplateGenerator::generationFinished)) {
                *result = 1;
            }
        }
        {
            typedef void (TemplateGenerator::*_t)(int , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TemplateGenerator::generationProgress)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject TemplateGenerator::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TemplateGenerator.data,
      qt_meta_data_TemplateGenerator,  qt_static_metacall, 0, 0}
};


const QMetaObject *TemplateGenerator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TemplateGenerator::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TemplateGenerator.stringdata))
        return static_cast<void*>(const_cast< TemplateGenerator*>(this));
    return QObject::qt_metacast(_clname);
}

int TemplateGenerator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void TemplateGenerator::generationStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void TemplateGenerator::generationFinished(TemplateCore::GenerationResult _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 3
void TemplateGenerator::generationProgress(int _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'torprocess.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "torprocess.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'torprocess.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TorProcessThread_t {
    QByteArrayData data[9];
    char stringdata0[109];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TorProcessThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TorProcessThread_t qt_meta_stringdata_TorProcessThread = {
    {
QT_MOC_LITERAL(0, 0, 16), // "TorProcessThread"
QT_MOC_LITERAL(1, 17, 16), // "torProcessSignal"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 1), // "s"
QT_MOC_LITERAL(4, 37, 14), // "torProcessDone"
QT_MOC_LITERAL(5, 52, 15), // "finishedHandler"
QT_MOC_LITERAL(6, 68, 8), // "exitcode"
QT_MOC_LITERAL(7, 77, 20), // "QProcess::ExitStatus"
QT_MOC_LITERAL(8, 98, 10) // "exitstatus"

    },
    "TorProcessThread\0torProcessSignal\0\0s\0"
    "torProcessDone\0finishedHandler\0exitcode\0"
    "QProcess::ExitStatus\0exitstatus"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TorProcessThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    0,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    2,   33,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7,    6,    8,

       0        // eod
};

void TorProcessThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TorProcessThread *_t = static_cast<TorProcessThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->torProcessSignal((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->torProcessDone(); break;
        case 2: _t->finishedHandler((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (TorProcessThread::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TorProcessThread::torProcessSignal)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TorProcessThread::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TorProcessThread::torProcessDone)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject TorProcessThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_TorProcessThread.data,
      qt_meta_data_TorProcessThread,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *TorProcessThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TorProcessThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TorProcessThread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int TorProcessThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void TorProcessThread::torProcessSignal(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TorProcessThread::torProcessDone()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

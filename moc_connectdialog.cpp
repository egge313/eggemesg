/****************************************************************************
** Meta object code from reading C++ file 'connectdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "connectdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'connectdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ConnectDialog_t {
    QByteArrayData data[12];
    char stringdata0[205];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConnectDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConnectDialog_t qt_meta_stringdata_ConnectDialog = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ConnectDialog"
QT_MOC_LITERAL(1, 14, 6), // "accept"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 6), // "reject"
QT_MOC_LITERAL(4, 29, 24), // "onPushButtonLaunchServer"
QT_MOC_LITERAL(5, 54, 26), // "onPushButtonConnect2Server"
QT_MOC_LITERAL(6, 81, 28), // "onPushButtonTorClientConnect"
QT_MOC_LITERAL(7, 110, 12), // "displayError"
QT_MOC_LITERAL(8, 123, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(9, 152, 11), // "socketError"
QT_MOC_LITERAL(10, 164, 13), // "sessionOpened"
QT_MOC_LITERAL(11, 178, 26) // "tabTorControlUpdateHandler"

    },
    "ConnectDialog\0accept\0\0reject\0"
    "onPushButtonLaunchServer\0"
    "onPushButtonConnect2Server\0"
    "onPushButtonTorClientConnect\0displayError\0"
    "QAbstractSocket::SocketError\0socketError\0"
    "sessionOpened\0tabTorControlUpdateHandler"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConnectDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x0a /* Public */,
       3,    0,   55,    2, 0x0a /* Public */,
       4,    0,   56,    2, 0x0a /* Public */,
       5,    0,   57,    2, 0x0a /* Public */,
       6,    0,   58,    2, 0x0a /* Public */,
       7,    1,   59,    2, 0x0a /* Public */,
      10,    0,   62,    2, 0x0a /* Public */,
      11,    0,   63,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ConnectDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ConnectDialog *_t = static_cast<ConnectDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->accept(); break;
        case 1: _t->reject(); break;
        case 2: _t->onPushButtonLaunchServer(); break;
        case 3: _t->onPushButtonConnect2Server(); break;
        case 4: _t->onPushButtonTorClientConnect(); break;
        case 5: _t->displayError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 6: _t->sessionOpened(); break;
        case 7: _t->tabTorControlUpdateHandler(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    }
}

const QMetaObject ConnectDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ConnectDialog.data,
      qt_meta_data_ConnectDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ConnectDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConnectDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ConnectDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int ConnectDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[22];
    char stringdata0[234];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 4), // "done"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 9), // "addToList"
QT_MOC_LITERAL(4, 27, 8), // "QUrlInfo"
QT_MOC_LITERAL(5, 36, 4), // "file"
QT_MOC_LITERAL(6, 41, 7), // "ftpDone"
QT_MOC_LITERAL(7, 49, 5), // "error"
QT_MOC_LITERAL(8, 55, 15), // "showLoginDialog"
QT_MOC_LITERAL(9, 71, 5), // "state"
QT_MOC_LITERAL(10, 77, 5), // "login"
QT_MOC_LITERAL(11, 83, 12), // "InputDialog*"
QT_MOC_LITERAL(12, 96, 4), // "diag"
QT_MOC_LITERAL(13, 101, 10), // "afterLogin"
QT_MOC_LITERAL(14, 112, 8), // "listDone"
QT_MOC_LITERAL(15, 121, 9), // "listFiles"
QT_MOC_LITERAL(16, 131, 8), // "fileName"
QT_MOC_LITERAL(17, 140, 10), // "fileSystem"
QT_MOC_LITERAL(18, 151, 23), // "QHash<QString,QUrlInfo>"
QT_MOC_LITERAL(19, 175, 5), // "files"
QT_MOC_LITERAL(20, 181, 24), // "on_connectButton_clicked"
QT_MOC_LITERAL(21, 206, 27) // "on_disconnectButton_clicked"

    },
    "MainWindow\0done\0\0addToList\0QUrlInfo\0"
    "file\0ftpDone\0error\0showLoginDialog\0"
    "state\0login\0InputDialog*\0diag\0afterLogin\0"
    "listDone\0listFiles\0fileName\0fileSystem\0"
    "QHash<QString,QUrlInfo>\0files\0"
    "on_connectButton_clicked\0"
    "on_disconnectButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   70,    2, 0x0a /* Public */,
       6,    1,   73,    2, 0x0a /* Public */,
       8,    1,   76,    2, 0x0a /* Public */,
      10,    1,   79,    2, 0x0a /* Public */,
      13,    1,   82,    2, 0x0a /* Public */,
      14,    1,   85,    2, 0x0a /* Public */,
      15,    1,   88,    2, 0x0a /* Public */,
      17,    1,   91,    2, 0x0a /* Public */,
      20,    0,   94,    2, 0x08 /* Private */,
      21,    0,   95,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->done(); break;
        case 1: _t->addToList((*reinterpret_cast< const QUrlInfo(*)>(_a[1]))); break;
        case 2: _t->ftpDone((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->showLoginDialog((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->login((*reinterpret_cast< InputDialog*(*)>(_a[1]))); break;
        case 5: _t->afterLogin((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->listDone((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->listFiles((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->fileSystem((*reinterpret_cast< QHash<QString,QUrlInfo>(*)>(_a[1]))); break;
        case 9: _t->on_connectButton_clicked(); break;
        case 10: _t->on_disconnectButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< InputDialog* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::done)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::done()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

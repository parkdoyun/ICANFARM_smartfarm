/****************************************************************************
** Meta object code from reading C++ file 'login_dialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "login_dialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'login_dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_login_dialog_t {
    QByteArrayData data[19];
    char stringdata0[226];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_login_dialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_login_dialog_t qt_meta_stringdata_login_dialog = {
    {
QT_MOC_LITERAL(0, 0, 12), // "login_dialog"
QT_MOC_LITERAL(1, 13, 15), // "sendLogInResult"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 4), // "flag"
QT_MOC_LITERAL(4, 35, 10), // "closeEvent"
QT_MOC_LITERAL(5, 46, 12), // "QCloseEvent*"
QT_MOC_LITERAL(6, 59, 1), // "e"
QT_MOC_LITERAL(7, 61, 12), // "btn0_clicked"
QT_MOC_LITERAL(8, 74, 12), // "btn1_clicked"
QT_MOC_LITERAL(9, 87, 12), // "btn2_clicked"
QT_MOC_LITERAL(10, 100, 12), // "btn3_clicked"
QT_MOC_LITERAL(11, 113, 12), // "btn4_clicked"
QT_MOC_LITERAL(12, 126, 12), // "btn5_clicked"
QT_MOC_LITERAL(13, 139, 12), // "btn6_clicked"
QT_MOC_LITERAL(14, 152, 12), // "btn7_clicked"
QT_MOC_LITERAL(15, 165, 12), // "btn8_clicked"
QT_MOC_LITERAL(16, 178, 12), // "btn9_clicked"
QT_MOC_LITERAL(17, 191, 17), // "btnDelete_clicked"
QT_MOC_LITERAL(18, 209, 16) // "btnEnter_clicked"

    },
    "login_dialog\0sendLogInResult\0\0flag\0"
    "closeEvent\0QCloseEvent*\0e\0btn0_clicked\0"
    "btn1_clicked\0btn2_clicked\0btn3_clicked\0"
    "btn4_clicked\0btn5_clicked\0btn6_clicked\0"
    "btn7_clicked\0btn8_clicked\0btn9_clicked\0"
    "btnDelete_clicked\0btnEnter_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_login_dialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   87,    2, 0x08 /* Private */,
       7,    0,   90,    2, 0x08 /* Private */,
       8,    0,   91,    2, 0x08 /* Private */,
       9,    0,   92,    2, 0x08 /* Private */,
      10,    0,   93,    2, 0x08 /* Private */,
      11,    0,   94,    2, 0x08 /* Private */,
      12,    0,   95,    2, 0x08 /* Private */,
      13,    0,   96,    2, 0x08 /* Private */,
      14,    0,   97,    2, 0x08 /* Private */,
      15,    0,   98,    2, 0x08 /* Private */,
      16,    0,   99,    2, 0x08 /* Private */,
      17,    0,  100,    2, 0x08 /* Private */,
      18,    0,  101,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void login_dialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<login_dialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendLogInResult((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 2: _t->btn0_clicked(); break;
        case 3: _t->btn1_clicked(); break;
        case 4: _t->btn2_clicked(); break;
        case 5: _t->btn3_clicked(); break;
        case 6: _t->btn4_clicked(); break;
        case 7: _t->btn5_clicked(); break;
        case 8: _t->btn6_clicked(); break;
        case 9: _t->btn7_clicked(); break;
        case 10: _t->btn8_clicked(); break;
        case 11: _t->btn9_clicked(); break;
        case 12: _t->btnDelete_clicked(); break;
        case 13: _t->btnEnter_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (login_dialog::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&login_dialog::sendLogInResult)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject login_dialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_login_dialog.data,
    qt_meta_data_login_dialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *login_dialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *login_dialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_login_dialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int login_dialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void login_dialog::sendLogInResult(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

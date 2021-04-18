/****************************************************************************
** Meta object code from reading C++ file 'UI.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../UI.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UI_t {
    const uint offsetsAndSize[20];
    char stringdata0[240];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_UI_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_UI_t qt_meta_stringdata_UI = {
    {
QT_MOC_LITERAL(0, 2), // "UI"
QT_MOC_LITERAL(3, 28), // "Bouton_Accueil_Jouer_Clicked"
QT_MOC_LITERAL(32, 0), // ""
QT_MOC_LITERAL(33, 30), // "Bouton_Accueil_Charger_Clicked"
QT_MOC_LITERAL(64, 28), // "Bouton_Accueil_Stats_Clicked"
QT_MOC_LITERAL(93, 29), // "Bouton_Accueil_Record_Clicked"
QT_MOC_LITERAL(123, 30), // "Bouton_Accueil_Quitter_Clicked"
QT_MOC_LITERAL(154, 26), // "Bouton_Jeu_Quitter_Clicked"
QT_MOC_LITERAL(181, 28), // "Bouton_Stats_Quitter_Clicked"
QT_MOC_LITERAL(210, 29) // "Bouton_Record_Quitter_Clicked"

    },
    "UI\0Bouton_Accueil_Jouer_Clicked\0\0"
    "Bouton_Accueil_Charger_Clicked\0"
    "Bouton_Accueil_Stats_Clicked\0"
    "Bouton_Accueil_Record_Clicked\0"
    "Bouton_Accueil_Quitter_Clicked\0"
    "Bouton_Jeu_Quitter_Clicked\0"
    "Bouton_Stats_Quitter_Clicked\0"
    "Bouton_Record_Quitter_Clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UI[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   62,    2, 0x08,    0 /* Private */,
       3,    0,   63,    2, 0x08,    1 /* Private */,
       4,    0,   64,    2, 0x08,    2 /* Private */,
       5,    0,   65,    2, 0x08,    3 /* Private */,
       6,    0,   66,    2, 0x08,    4 /* Private */,
       7,    0,   67,    2, 0x08,    5 /* Private */,
       8,    0,   68,    2, 0x08,    6 /* Private */,
       9,    0,   69,    2, 0x08,    7 /* Private */,

 // slots: parameters
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

void UI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UI *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->Bouton_Accueil_Jouer_Clicked(); break;
        case 1: _t->Bouton_Accueil_Charger_Clicked(); break;
        case 2: _t->Bouton_Accueil_Stats_Clicked(); break;
        case 3: _t->Bouton_Accueil_Record_Clicked(); break;
        case 4: _t->Bouton_Accueil_Quitter_Clicked(); break;
        case 5: _t->Bouton_Jeu_Quitter_Clicked(); break;
        case 6: _t->Bouton_Stats_Quitter_Clicked(); break;
        case 7: _t->Bouton_Record_Quitter_Clicked(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject UI::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_UI.offsetsAndSize,
    qt_meta_data_UI,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_UI_t

, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *UI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UI.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int UI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

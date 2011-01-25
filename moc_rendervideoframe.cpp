/****************************************************************************
** Meta object code from reading C++ file 'rendervideoframe.h'
**
** Created: Tue Jan 25 13:50:40 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "rendervideoframe.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rendervideoframe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RenderVideoFrame[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x0a,
      34,   17,   17,   17, 0x0a,
      52,   17,   47,   17, 0x0a,
      66,   17,   17,   17, 0x0a,
      84,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_RenderVideoFrame[] = {
    "RenderVideoFrame\0\0setCapture(int)\0"
    "queryFrame()\0bool\0drawCircles()\0"
    "drawCircles(bool)\0toggleCapturing()\0"
};

const QMetaObject RenderVideoFrame::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_RenderVideoFrame,
      qt_meta_data_RenderVideoFrame, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RenderVideoFrame::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RenderVideoFrame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RenderVideoFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RenderVideoFrame))
        return static_cast<void*>(const_cast< RenderVideoFrame*>(this));
    return QWidget::qt_metacast(_clname);
}

int RenderVideoFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setCapture((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: queryFrame(); break;
        case 2: { bool _r = drawCircles();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: drawCircles((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: toggleCapturing(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

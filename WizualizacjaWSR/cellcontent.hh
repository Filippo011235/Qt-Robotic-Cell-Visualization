#ifndef CELLCONTENT_HH
#define CELLCONTENT_HH

#include <QWidget>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QForwardRenderer>
#include <QSize>
#include <QScreen>
#include <Qt3DRender/qmesh.h>
#include <Qt3DRender/qpointlight.h>
#include <Qt3DRender/QCamera>
#include <Qt3DCore/qtransform.h>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DRender/qrenderaspect.h>
#include <Qt3DExtras/qforwardrenderer.h>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/qt3dwindow.h>
#include <Qt3DExtras/qfirstpersoncameracontroller.h>
#include <QPropertyAnimation>

namespace Ui {
class CellContent;
}

class CellContent : public Qt3DExtras::Qt3DWindow
{
    Q_OBJECT

public:
    explicit CellContent(Qt3DExtras::Qt3DWindow *parent = nullptr);
    ~CellContent();

private:
    Ui::CellContent *ui;
};

#endif // CELLCONTENT_HH

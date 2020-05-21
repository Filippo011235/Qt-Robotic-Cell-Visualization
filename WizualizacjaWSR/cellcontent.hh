#ifndef CELLCONTENT_HH
#define CELLCONTENT_HH

#include <QGLWidget>
#include <GL/glut.h>
#include <QTimer>

class CellContent : public QGLWidget
{
public:
    CellContent(QWidget *parent = nullptr);
    ~CellContent();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

private:
    QTimer *_SpeedTimer;
    void ConvBeltMovement() {_SpeedTimer->start();}
    void ConvBeltStop() {_SpeedTimer->stop();}
    float WasteZCoord;
    void DrawConvBelt();

//    double alpha;
//    double beta;
//    double distance;
};

#endif // CELLCONTENT_HH

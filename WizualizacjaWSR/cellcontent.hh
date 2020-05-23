#ifndef CELLCONTENT_HH
#define CELLCONTENT_HH

#include <QGLWidget>
#include <GL/glut.h>
#include <QTimer>
#include "waste.hh"
#include <vector>

using namespace std;

class CellContent : public QGLWidget
{
public:
    CellContent(QWidget *parent = nullptr);
    ~CellContent();

    void AddWaste(Waste NewOne);
    void setConvSpeed(int NewInterval){_SpeedTimer->setInterval(NewInterval);};
    void ConvBeltMovement() {_SpeedTimer->start();}
    void ConvBeltStop() {_SpeedTimer->stop();}

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

private:
    QTimer *_SpeedTimer;
    Waste *Kokos;
    qreal rgb[3]; // Stores Waste colour
    float ConvSpeed;
    float WasteZCoord;
    void DrawConvBelt();

    const float _BeforeRecognition = 0.5;

    // Keeps all the Waste on the scene
    vector<Waste> WasteStream;

//    double alpha;
//    double beta;
//    double distance;
};

#endif // CELLCONTENT_HH

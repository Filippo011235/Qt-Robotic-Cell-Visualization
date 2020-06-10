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
    Q_OBJECT

    void SetScene(); // resets transformations and creates isometric view
    const float CameraDistance = 5;
    QTimer *SpeedTimer;
    float ConvSpeed;

    // Waste related attributes
    vector<Waste> MaterialStreams[5]; // Keeps track of all the Waste on the scene
    const float RecognitionThreshold = 2.5;
    qreal rgb[3]; // buffer for storing given Waste colour
    const float BeforeRecognition = 0.5; // Colour value corresponding to dark gray

    // CB and Containers related attributes
    void DrawConvBelt();
    void DrawContainer(float X_coord, float Z_coord, QColor Colour);
    // Containers data
    const float ContainerDistances_X[5] = {-3, -3, 1, 1, -1};
    const float ContainerDistances_Z[5] = {-3,-5.3,-3,-5.3,-7.5};
    QColor MaterialsColours[5] = {Qt::green, Qt::blue, Qt::yellow, Qt::magenta, Qt::red};

public:
    CellContent(QWidget *parent = nullptr);
    ~CellContent();

    void AddWaste(Waste NewOne);

    void setConvSpeed(float NewSpeed){ConvSpeed = NewSpeed;};
    void ConvBeltMovement() {SpeedTimer->start();}
    void ConvBeltStop() {SpeedTimer->stop();}

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

signals:
    void WasteSorted(int);
};

#endif // CELLCONTENT_HH

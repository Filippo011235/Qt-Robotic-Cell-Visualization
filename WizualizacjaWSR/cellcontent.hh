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
//    void setConvSpeed(int NewInterval){_SpeedTimer->setInterval(NewInterval);};
    void setConvSpeed(float NewSpeed){ConvSpeed = NewSpeed;};
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
    void DrawContainer(float X_coord, float Z_coord, float R_colour, float G_colour, float B_colour);
//    void DrawBox();
    void SetScene();
    const float CameraDistance = 5;

    void Sort(int idx);


    const float _BeforeRecognition = 0.5;

    // Keeps all the Waste on the scene
    vector<Waste> WasteStream;

    vector<Waste> PETStream;
    vector<Waste> KartonStream;
    vector<Waste> HDPEStream;
    vector<Waste> AlumStream;
    vector<Waste> NieznaneStream;

//    double alpha;
//    double beta;
//    double distance;
};

#endif // CELLCONTENT_HH

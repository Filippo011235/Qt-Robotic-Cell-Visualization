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

signals:
    void WasteSorted(int);

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
    vector<Waste> MaterialStreams[5];
    float ContainerDistances_X[5] = {-3, -3, 1, 1, -1};
    float ContainerDistances_Z[5] = {-3,-5.3,-3,-5.3,-7.5};

    vector<Waste> WasteStream;

    vector<Waste> PETStream;
    vector<Waste> KartonStream;
    vector<Waste> HDPEStream;
    vector<Waste> AlumStream;
    vector<Waste> NieznaneStream;

    // Sorting
    typedef void (*SortingFunctions) ();
    void PETSort();
    void KartonSort();
    void HDPESort();
    void AlumSort();
    void NieznaneSort();
    SortingFunctions MaterialSorting[5];
//    SortingFunctions MaterialSorting[5] = {
//        this->PETSort,
//        KartonSort,
//        HDPESort,
//        AlumSort,
//        NieznaneSort
//    };



};

#endif // CELLCONTENT_HH

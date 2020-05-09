#ifndef CAMERACONTENT_HH
#define CAMERACONTENT_HH

#include <QWidget>
#include <QImage>
#include <QTimer>
#include <vector>
#include <waste.hh>
#include <QRect>
#include <QColor>


using namespace std;

class CameraContent : public QWidget
{
    Q_OBJECT

    QTimer *_SpeedTimer;
    QImage _ConvBeltImage;
    QRect WasteTemplate;

    QColor BeforeRecognition;

    int TabMiddle_x = 200;
    int RectMiddle = 220;

    int Halo;
    int Threshold = 280;

    int _ConvSpeed;
    int _TopConvLocation_y;
    int _BottomConvLocation_y;

    int Usun_mnie;
    vector<Waste> CurrentWasteStream;

public:
    explicit CameraContent(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;

    void AddWaste(Waste NewOne);

    void ConvBeltMovement() {_SpeedTimer->start();}
    void ConvBeltStop() {_SpeedTimer->stop();}
    int SetConvSpeed(const int NewValue) {return _ConvSpeed = NewValue;}

signals:
    void FAKEWasteSorted();

public slots:
    void on_Timer_timeout();
//    void GenerateNextWaste(/*vector<MaterialTypes> CurrentMaterials*/);
};

#endif // CAMERACONTENT_HH

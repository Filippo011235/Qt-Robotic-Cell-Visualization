#ifndef CAMERACONTENT_HH
#define CAMERACONTENT_HH

#include <QWidget>
#include <QImage>
#include <QTimer>
#include <QRect>
#include <QColor>

#include <vector>
#include <waste.hh>

using namespace std;

class CameraContent : public QWidget
{
    Q_OBJECT

    QTimer *_SpeedTimer;
    QImage _ConvBeltImage;
    int ConvBeltHeight; // Little optimization for Timer timeout?
    QRect WasteTemplate;

    const QColor _BeforeRecognition = Qt::darkGray; // Colour of unclassified Waste

    const int TabMiddle_x = 200;
    const int RectMiddle = 220;

    const int Threshold = 280;

    int _ConvSpeed;
    int _TopConvLocation_y;
    int _BottomConvLocation_y;

    // Keeps all the Waste on the scene
    vector<Waste> WasteStream;

public:
    explicit CameraContent(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;

    void AddWaste(Waste NewOne);

    int SetConvSpeed(const int NewValue) {return _ConvSpeed = NewValue;}

    void ConvBeltMovement() {_SpeedTimer->start();}
    void ConvBeltStop() {_SpeedTimer->stop();}

signals:
    void FAKEWasteSorted();

public slots:
    void on_Timer_timeout();
};

#endif // CAMERACONTENT_HH

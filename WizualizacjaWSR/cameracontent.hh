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

    QTimer *SpeedTimer;

    // Conveyor Belt related attributes
    QImage ConvBeltImage;
    int ConvBeltHeight;
    int ConvSpeed;
    int CBLocation_y[2]; // stores both CB location in Y axis
    const int ConvBelt_x = 200; // where to draw CB on the X axis

    // Waste related attributes
    vector<Waste> WasteStream; // Keeps track of all the Waste on the scene
    const QColor _BeforeRecognition = Qt::darkGray; // Colour of unclassified Waste
    const int Waste_x = 220; // where to draw Waste on the X axis
    const int ClassificationThreshold = 280; // Point on Y axis where Waste's classified

public:
    explicit CameraContent(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;

    void AddWaste(Waste NewOne);

    int SetConvSpeed(const int NewValue) {return ConvSpeed = NewValue;}
    void ConvBeltMovement() {SpeedTimer->start();}
    void ConvBeltStop() {SpeedTimer->stop();}

public slots:
    void on_Timer_timeout();
};

#endif // CAMERACONTENT_HH

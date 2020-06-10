#include "cameracontent.hh"

#include <QPainter>
#include <QBrush>
#include <QPalette>

#define WASTE_SIZE 50
#define CB_OFFSET 10

CameraContent::CameraContent(QWidget *parent) : QWidget(parent)
{
    SpeedTimer = new QTimer(this);
    SpeedTimer->setInterval(50);
    SpeedTimer->setObjectName("Timer");

    ConvBeltImage.load(":/ConvBelt.jpg");
    ConvSpeed = 5; // Movement step
    ConvBeltHeight = ConvBeltImage.height(); // used in Timer timeout

    // Both CB starting pos
    CBLocation_y[0] = 0; // Top one
    CBLocation_y[1] = ConvBeltHeight; // Bottom

    connect(SpeedTimer, SIGNAL(timeout()),this,SLOT(on_Timer_timeout()));
    ConvBeltMovement();

    QMetaObject::connectSlotsByName(this);
}

void CameraContent::paintEvent(QPaintEvent *){
    QPainter Painter(this);

    // Draw Top and Bottom Conveyor Belts
    for(unsigned int i = 0; i < 2; ++i){
        Painter.drawImage(ConvBelt_x, CBLocation_y[i], ConvBeltImage);
    }

    // Iterate over Waste Stream and draw each Waste
    for(auto CurrentWaste : WasteStream){
        const int _2DLocation = CurrentWaste.get_2DLocation();
        if(_2DLocation < ClassificationThreshold){ // Waste was recognized
            Painter.fillRect(Waste_x, _2DLocation,
                             WASTE_SIZE, WASTE_SIZE, CurrentWaste.getColour());
        } else {    // Yet to be classified
            Painter.fillRect(Waste_x, _2DLocation,
                             WASTE_SIZE, WASTE_SIZE, _BeforeRecognition);
        }
    } // for WasteStream

}

void CameraContent::AddWaste(Waste NewOne) {
    NewOne.set_2DLocation(ConvBeltHeight); // Start beneath the scene
    WasteStream.push_back(NewOne);
}

void CameraContent::on_Timer_timeout()
{
    // Update Conveyor Belts
    for(unsigned int i = 0; i < 2; ++i){
        CBLocation_y[i] -= ConvSpeed;
        if (CBLocation_y[i] < -ConvBeltHeight) // Full CB image is beyond the scene view
                CBLocation_y[i] = ConvBeltHeight-CB_OFFSET; // Loop CB back beneath the scene
    }

    // Update Waste Stream
    if(!WasteStream.empty()){
        for (unsigned int i= 0; i < WasteStream.size(); ++i) {
            WasteStream[i].Advance_2D(ConvSpeed);
        }
        // Whole Waste image is beyond the scene view. Can be checked only for the first one
        if(WasteStream[0].get_2DLocation() < -WASTE_SIZE){
            WasteStream.erase(WasteStream.begin()); // FIFO
        }
    }
    update();
}



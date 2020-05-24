#include "cameracontent.hh"

#include <QPainter>
#include <QBrush>
#include <QPalette>

#define WASTE_SIZE 50

// Temporary includes:
#include <QtDebug>

CameraContent::CameraContent(QWidget *parent) : QWidget(parent)
{
    _SpeedTimer = new QTimer(this);
    _SpeedTimer->setInterval(50);
    _SpeedTimer->setObjectName("Timer");

    _ConvBeltImage.load(":/ConvBelt.jpg");
    ConvBeltHeight = _ConvBeltImage.height(); // used in Timer timeout

    _TopConvLocation_y = 0;
    _BottomConvLocation_y = _ConvBeltImage.height();
    _ConvSpeed = 5;

    connect(_SpeedTimer, SIGNAL(timeout()),this,SLOT(on_Timer_timeout()));
    ConvBeltMovement();

    // WasteTemplate.setRect(TabMiddle_x+17,_BottomConvLocation_y,WASTE_SIZE,WASTE_SIZE);
    WasteTemplate.setRect(RectMiddle,_BottomConvLocation_y,WASTE_SIZE,WASTE_SIZE);

    QMetaObject::connectSlotsByName(this);
}

void CameraContent::paintEvent(QPaintEvent *){
    QPainter Painter(this);

    // Draw Top and Bottom Conveyor Belts
    Painter.drawImage(TabMiddle_x, _TopConvLocation_y, _ConvBeltImage);
    Painter.drawImage(TabMiddle_x, _BottomConvLocation_y, _ConvBeltImage);

    // Iterate over Waste Stream and draw each Waste
    for(auto CurrentWaste : WasteStream){
        if(CurrentWaste.y() < Threshold){ // Waste was recognized
            Painter.fillRect(RectMiddle, CurrentWaste.y(),
                             WASTE_SIZE, WASTE_SIZE, CurrentWaste.getColour());
        } else {    // Yet to be classified
            Painter.fillRect(RectMiddle, CurrentWaste.y(),
                             WASTE_SIZE, WASTE_SIZE, _BeforeRecognition);
        }
    }

}

void CameraContent::AddWaste(Waste NewOne)
{
    NewOne.setY(ConvBeltHeight); // Start beneath the scene
    WasteStream.push_back(NewOne);
}

void CameraContent::on_Timer_timeout()
{
    // Update Conveyor Belts
    _TopConvLocation_y -= _ConvSpeed;
    if (_TopConvLocation_y < -ConvBeltHeight) // Full CB image is beyond the scene view
            _TopConvLocation_y = ConvBeltHeight-10;
    _BottomConvLocation_y -= _ConvSpeed;
    if (_BottomConvLocation_y < -ConvBeltHeight)
            _BottomConvLocation_y = ConvBeltHeight-10;

    // Update Waste Stream
    if(!WasteStream.empty()){
        for (unsigned int i= 0; i < WasteStream.size(); ++i) {
            int Halo = WasteStream[i].y() - _ConvSpeed;
            WasteStream[i].setY(Halo);
        }

        // Full Waste image is beyond the scene view
        if(WasteStream[0].y() < -WASTE_SIZE){
            WasteStream.erase(WasteStream.begin()); // FIFO
        } // Waste beyond scene
    } // if(!WasteStream.empty()
    update();
}



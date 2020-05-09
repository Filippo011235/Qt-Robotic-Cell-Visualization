#include "cameracontent.hh"

#include <QPainter>
#include <QPushButton>
#include <QBrush>
#include <QPalette>
#include <QRect>
#include <QColor>

#define WASTE_SIZE 50

#include <QtDebug>

CameraContent::CameraContent(QWidget *parent) : QWidget(parent)
{
    _SpeedTimer = new QTimer(this);
    _SpeedTimer->setInterval(50);
    _SpeedTimer->setObjectName("Timer");

    BeforeRecognition = Qt::darkGray;

    _ConvBeltImage.load(":/ConvBelt.jpg");

    _TopConvLocation_y = 0;
    _BottomConvLocation_y = _ConvBeltImage.height();
    _ConvSpeed = 5;

    connect(_SpeedTimer, SIGNAL(timeout()),this,SLOT(on_Timer_timeout()));
    ConvBeltMovement();

//    WasteTemplate.setRect(TabMiddle_x+17,_BottomConvLocation_y,WASTE_SIZE,WASTE_SIZE);
    WasteTemplate.setRect(RectMiddle,_BottomConvLocation_y,WASTE_SIZE,WASTE_SIZE);

    QMetaObject::connectSlotsByName(this);
}

void CameraContent::paintEvent(QPaintEvent *)
{

    QPainter Painter(this);

    Painter.drawImage(TabMiddle_x, _TopConvLocation_y, _ConvBeltImage);
    Painter.drawImage(TabMiddle_x, _BottomConvLocation_y, _ConvBeltImage);

    for(unsigned int i=0; i < CurrentWasteStream.size(); i++){
        if(CurrentWasteStream[i].y() < Threshold){
            Painter.fillRect(RectMiddle, CurrentWasteStream[i].y(),
                             WASTE_SIZE, WASTE_SIZE, CurrentWasteStream[i].getColour());
//            Painter.fillRect(RectMiddle, CurrentWasteStream[i].y(),
//                             WASTE_SIZE, WASTE_SIZE, Qt::red);
//            qDebug() << "CC " << CurrentWasteStream[i].getColour();
        } else {
            Painter.fillRect(RectMiddle, CurrentWasteStream[i].y(),
                             WASTE_SIZE, WASTE_SIZE, BeforeRecognition);
        }
    }

//    Painter.drawRect(Szablon2);

}

void CameraContent::AddWaste(Waste NewOne)
{
    CurrentWasteStream.push_back(NewOne);
//    CurrentWasteStream.back().setY(_BottomConvLocation_y);
    CurrentWasteStream.back().setY(WasteTemplate.y());
}

void CameraContent::on_Timer_timeout()
{
    if(!CurrentWasteStream.empty()){
        for (unsigned int i=0; i < CurrentWasteStream.size(); i++) {
            CurrentWasteStream[i].setY(CurrentWasteStream[i].y() - _ConvSpeed);
        }
        if(CurrentWasteStream[0].y() < -WASTE_SIZE){
    //        qDebug() << "juz < 0";
            CurrentWasteStream.erase(CurrentWasteStream.begin());
    //            emit FAKEWasteSorted();
        }
    }

    _TopConvLocation_y -= _ConvSpeed;
    if (_TopConvLocation_y < -_ConvBeltImage.height()) _TopConvLocation_y = _ConvBeltImage.height()-10;

    _BottomConvLocation_y -= _ConvSpeed;
    if (_BottomConvLocation_y < -_ConvBeltImage.height()) _BottomConvLocation_y = _ConvBeltImage.height()-10;

    update();
}

//void CameraContent::GenerateNextWaste(/*vector<MaterialTypes> CurrentMaterials*/){


//}


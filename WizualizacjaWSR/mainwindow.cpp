#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <algorithm>  // remove value from vector
#include <cstdlib>  // srand
#include <ctime>    // time

// Temporary includes:
#include <QtDebug>

#define DEFAULT_SPEED 50
#define GENERATING_CONST 25000

//#include "cameracontent.hh"
//#include "cellcontent.hh"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->checkBoxNieznany->setChecked(true);
    ui->checkBoxPET->setChecked(true);
    ui->horizontalScrollBarSzybTasm->setValue(DEFAULT_SPEED);

    WeightDisplays[0] = ui->lineEdit_PET;
    WeightDisplays[1] = ui->lineEdit_Karton;
    WeightDisplays[2] = ui->lineEdit_HDPE;
    WeightDisplays[3] = ui->lineEdit_Alum;
    WeightDisplays[4] = ui->lineEdit_Nieznany;
//    for (int i=0; i < 4; ++i) {
//        WeightDisplays[i]->setLayoutDirection(Qt::LeftToRight);
//    }

    // Init view from Camera:
    ui->tabWidget->addTab(new CameraContent(this), "&Kamera");
    // For accessing CameraScene methods
    CameraScene = static_cast<CameraContent*>(ui->tabWidget->currentWidget());

    // Init general Waste handling(creating/destroying)
    srand(time(nullptr)); // For generating random Waste Material in Waste.cpp
    _WasteGenerator = new QTimer(this);
    _WasteGenerator->setInterval(GENERATING_CONST/DEFAULT_SPEED);
    connect(_WasteGenerator, SIGNAL(timeout()), this, SLOT(CreateWaste()));
    GeneratingWaste(); // Start creating waste
    connect(CameraScene, SIGNAL(FAKEWasteSorted(int)), this, SLOT(DestroyWaste(int)));

}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::CreateWaste(){
    Waste NewWaste(CurrentMaterials);
    CameraScene->AddWaste(NewWaste);
}

void MainWindow::DestroyWaste(int WasteInformation) {
    if(WasteInformation >= 0){      // Waste was Heavy
        ValuesForLineEdit[WasteInformation] += 1;
        QString NewValue = QString::number(ValuesForLineEdit[WasteInformation]);
        WeightDisplays[WasteInformation]->setText(NewValue);
    }
}

void MainWindow::on_horizontalScrollBarSzybTasm_valueChanged(int value)
{
    CameraScene->SetConvSpeed(value/10);
    if(value){
        _WasteGenerator->setInterval(GENERATING_CONST/value);
    } else {    // value = 0
        _WasteGenerator->setInterval(100000000); // StopGenerating() would require a restart
    }
}

void MainWindow::on_pushButtonESTOP_clicked(){
    StopGenerating();
    CameraScene->ConvBeltStop();
    QMessageBox::critical(this, "E-STOP WYKRYTY", "Upewnij się, że wszystko w porządku i kliknij \"OK\"");
    CameraScene->ConvBeltMovement();
    GeneratingWaste();
}

void MainWindow::on_checkBoxPET_toggled(bool checked)
{
    if(checked) CurrentMaterials.push_back(PET);
    else  // Erase–remove idiom:
        CurrentMaterials.erase(remove(CurrentMaterials.begin(), CurrentMaterials.end(),PET));
}

void MainWindow::on_checkBoxKarton_toggled(bool checked)
{
    if(checked) CurrentMaterials.push_back(Karton);
    else  // Erase–remove idiom:
        CurrentMaterials.erase(remove(CurrentMaterials.begin(), CurrentMaterials.end(),Karton));
}

void MainWindow::on_checkBoxHDPE_toggled(bool checked)
{
    if(checked) CurrentMaterials.push_back(HDPE);
    else  // Erase–remove idiom:
        CurrentMaterials.erase(remove(CurrentMaterials.begin(), CurrentMaterials.end(),HDPE));
}

void MainWindow::on_checkBoxAlum_toggled(bool checked)
{
    if(checked) CurrentMaterials.push_back(Alum);
    else  // Erase–remove idiom:
        CurrentMaterials.erase(remove(CurrentMaterials.begin(), CurrentMaterials.end(),Alum));
}

void MainWindow::on_checkBoxNieznany_toggled(bool checked)
{
    if(checked) CurrentMaterials.push_back(Nieznany);
    else  // Erase–remove idiom:
        CurrentMaterials.erase(remove(CurrentMaterials.begin(), CurrentMaterials.end(),Nieznany));
}

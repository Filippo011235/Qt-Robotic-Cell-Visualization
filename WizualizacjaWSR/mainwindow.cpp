#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <algorithm>  // remove value from vector
#include <cstdlib>  // srand
#include <ctime>    // time

#define DEFAULT_SPEED 50
#define GENERATING_CONST 25000


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->horizontalScrollBarSzybTasm->setValue(DEFAULT_SPEED);
    // PET and Nieznany are set as default materials
    ui->checkBoxNieznany->setChecked(true);
    ui->checkBoxPET->setChecked(true);

    WeightDisplays[0] = ui->lineEdit_PET;
    WeightDisplays[1] = ui->lineEdit_Karton;
    WeightDisplays[2] = ui->lineEdit_HDPE;
    WeightDisplays[3] = ui->lineEdit_Alum;
    WeightDisplays[4] = ui->lineEdit_Nieznany;

    // Init view from Cell
    ui->tabWidget->addTab(new CellContent(this), "&Cela");
    CellScene = static_cast<CellContent*>(ui->tabWidget->widget(0));
    // Init view from Camera
    ui->tabWidget->addTab(new CameraContent(this), "&Kamera");
    CameraScene = static_cast<CameraContent*>(ui->tabWidget->widget(1));

    // Init general Waste handling(creating/destroying)
    srand(time(nullptr)); // For generating random Waste Material and Weight in Waste.cpp
    WasteGenerator = new QTimer(this);
    WasteGenerator->setInterval(GENERATING_CONST/DEFAULT_SPEED); // Some reasonable time...
    connect(WasteGenerator, SIGNAL(timeout()), this, SLOT(CreateWaste()));
    GeneratingWaste(); // Start creating waste
    // CellScene decides when Waste is sorted("destroyed")
    connect(CellScene, SIGNAL(WasteSorted(int)), this, SLOT(DestroyWaste(int)));
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::CreateWaste(){
    Waste NewWaste(CurrentMaterials);
    CameraScene->AddWaste(NewWaste);
    CellScene->AddWaste(NewWaste);
}

void MainWindow::DestroyWaste(int WasteInformation) {
    if(WasteInformation >= 0){      // Waste was Heavy, and of Material => WasteInformation...
        // ... so update corresponding LineEdit
        ValuesForLineEdit[WasteInformation] += 1;
        WeightDisplays[WasteInformation]->setText(QString::number(ValuesForLineEdit[WasteInformation]));
    }
}

void MainWindow::on_horizontalScrollBarSzybTasm_valueChanged(int value) {
    CameraScene->SetConvSpeed(value/10);
    CellScene->setConvSpeed((float)value/200);
    if(value){
        WasteGenerator->setInterval(GENERATING_CONST/value);
    } else {    // value = 0
        WasteGenerator->setInterval(100000000); // StopGenerating() would require a restart
    }
}

void MainWindow::on_pushButtonESTOP_clicked(){
    StopGenerating();
    CameraScene->ConvBeltStop();
    CellScene->ConvBeltStop();
    QMessageBox::critical(this, "E-STOP WYKRYTY", "Upewnij się, że wszystko w porządku i kliknij ,,OK''");
    // ,,OK'' pressed, restart everything:
    CameraScene->ConvBeltMovement();
    CellScene->ConvBeltMovement();
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

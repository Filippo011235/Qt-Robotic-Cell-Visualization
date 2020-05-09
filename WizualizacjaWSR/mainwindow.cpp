#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QtDebug>
#include <algorithm>  // remove in vector by value

//#include "cameracontent.hh"
//#include "cellcontent.hh"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->checkBoxNieznany->setChecked(true);
    ui->checkBoxPET->setChecked(true);


    ui->horizontalScrollBarSzybTasm->setValue(50);

    ui->tabWidget->addTab(new CameraContent(this), "&Kamera");
    CameraScene = static_cast<CameraContent*>(ui->tabWidget->currentWidget());

    CameraScene->AddWaste(Waste(CurrentMaterials));

    connect(CameraScene, SIGNAL(FAKEWasteSorted()), this, SLOT(DestroyWaste()));
//  ui->tabWidget->addTab(new CellContent(), "&Cela");

    eng = new mt19937(rd());
    _WasteGenerator = new QTimer(this);
    _WasteGenerator->setInterval(500);
    connect(_WasteGenerator, SIGNAL(timeout()), this, SLOT(CreateWaste()));
    GeneratingWaste();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CreateWaste()
{
//    uniform_int_distribution<int> MaterialIndices(0,CurrentMaterials.size());
//    int Index = MaterialIndices(generator); // Random index material from current ones
//    Material = CurrentMaterials[Index];
//    randint(2,3);
//    qDebug() << Index;

    Waste NewWaste(CurrentMaterials);
//    qDebug() << "MW " << NewWaste.getColour();
//    Waste Kokos(NewWaste);
//    qDebug() << "MW Kokos " << Kokos.getColour();

    CameraScene->AddWaste(NewWaste);

}

void MainWindow::DestroyWaste()
{
//    if(bool Heavy){
//        switch (WasteList[0].Material) {
//        case XXX:
//            ui->lineEdit_PET ++
//        }
//    }
//    WasteList.DELETEBEGINNING();
}

void MainWindow::on_horizontalScrollBarSzybTasm_valueChanged(int value)
{
    CameraScene->SetConvSpeed(value/10);
}

void MainWindow::on_pushButtonESTOP_clicked()
{
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

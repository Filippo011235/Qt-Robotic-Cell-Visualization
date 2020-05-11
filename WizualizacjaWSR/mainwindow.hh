#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QLineEdit>
#include <vector>
#include <waste.hh>
#include <cameracontent.hh>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void CreateWaste();
    void DestroyWaste(int);

    void on_horizontalScrollBarSzybTasm_valueChanged(int value);
    void on_pushButtonESTOP_clicked();

    void on_checkBoxPET_toggled(bool checked);
    void on_checkBoxKarton_toggled(bool checked);
    void on_checkBoxHDPE_toggled(bool checked);
    void on_checkBoxAlum_toggled(bool checked);
    void on_checkBoxNieznany_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    CameraContent *CameraScene;
    vector<MaterialTypes> CurrentMaterials;
    QTimer *_WasteGenerator;

    int ValuesForLineEdit[5] = {0};
    QLineEdit * WeightDisplays[5];

    void GeneratingWaste() {_WasteGenerator->start();}
    void StopGenerating() {_WasteGenerator->stop();}

};
#endif // MAINWINDOW_HH

#include "mainwindow.hh"
#include <GL/glut.h>

#include <QApplication>
#include <QMessageBox>


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    QApplication a(argc, argv);

    MainWindow w;

    w.show();
    return a.exec();
}

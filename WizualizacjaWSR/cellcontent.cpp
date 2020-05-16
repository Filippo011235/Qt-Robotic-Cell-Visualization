#include "cellcontent.hh"

CellContent::CellContent(QWidget *parent): QGLWidget(parent){
    _SpeedTimer = new QTimer(this);
    _SpeedTimer->setInterval(50);
    _SpeedTimer->setObjectName("Timer");

    connect(_SpeedTimer, SIGNAL(timeout()),this,SLOT(updateGL()));
    ConvBeltMovement();


    QMetaObject::connectSlotsByName(this);
}

CellContent::~CellContent(){
}

void CellContent::initializeGL(){
    glClearColor(0.7, 0.7, 0.7, 0.8);
    static GLfloat lightPosition[4] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    gluPerspective(45.0, 0, 0.01, 100.0);


}

void CellContent::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//    glLoadIdentity();

    glRotatef(0.5, 1, 1, 1);
//    glTranslatef(0.01, 0.01, 0);
//    glutWireTeapot(1);
//    glutSolidCube(2);
//    glMatrixMode(GL_MODELVIEW);

//    gluLookAt(0,0,5, 0,0,0, 0,1,0);
    glColor3f(0,1,0);
//    glutSolidSphere(1,20,20);
    glutSolidCube(2);

}

void CellContent::resizeGL(int w, int h){
//    glViewport(0,0, w,h);
    glViewport(0, 0, (GLint)w, (GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w/h, 0.01, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,5, 0,0,0, 0,1,0);
    updateGL();

}

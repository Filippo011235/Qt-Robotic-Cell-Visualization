#include "cellcontent.hh"

CellContent::CellContent(QWidget *parent): QGLWidget(parent){
    _SpeedTimer = new QTimer(this);
    _SpeedTimer->setInterval(50);
    _SpeedTimer->setObjectName("Timer");

    connect(_SpeedTimer, SIGNAL(timeout()),this,SLOT(updateGL()));
    ConvBeltMovement();

//    alpha = 25;
//    beta = -25;
//    distance = 2.5;

    QMetaObject::connectSlotsByName(this);
}

CellContent::~CellContent(){
}

void CellContent::initializeGL(){
    glClearColor(1,1,1,0); // Background colour
    glEnable(GL_DEPTH_TEST); // For rendering 3D
    glEnable(GL_CULL_FACE); // Display only visible front of the objects

//    static GLfloat lightPosition[4] = { 1.0, 1.0, 1.0, 1.0 };
//    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    glShadeModel(GL_SMOOTH);  // Smooth shading. The shadow smoothes the fine blend of colors through the polygon and smoothes the external light.

//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);


}

void CellContent::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // Isometric view
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); // Resets the current model observation matrix.
    /* use this length so that camera is 1 unit away from origin */
    double dist = 5;
    gluLookAt(dist, dist, dist,  /* position of camera */
              0.0,  0,  0.0,   /* where camera is pointing at */
              0.0,  1.0,  0.0);  /* which direction is up */

//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
    // Coordinate system
/*    glBegin(GL_LINES);
    glColor3d(1.0, 0.0, 0.0);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(1.0, 0.0, 0.0);

    glColor3d(0.0, 1.0, 0.0);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(0.0, 1.0, 0.0);

    glColor3d(0.0, 0.0, 1.0);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(0.0, 0.0, 1.0);
    glEnd();
*/

    glTranslatef(1, 0, 0);
    glColor3f(0.7,0.7,0.7);
    glutSolidCube(1);
//    glFlush();

//    glLoadIdentity();

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

#include "cellcontent.hh"

#define STEP 0.02

#include <QtDebug>

CellContent::CellContent(QWidget *parent): QGLWidget(parent){
    _SpeedTimer = new QTimer(this);
    _SpeedTimer->setInterval(50);
    _SpeedTimer->setObjectName("Timer");

    connect(_SpeedTimer, SIGNAL(timeout()),this,SLOT(updateGL()));
    ConvBeltMovement();

    WasteZCoord = 5;

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

    glLoadIdentity();

    // Isometric view
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity(); // Resets the current model observation matrix.

    double dist = 5;
    gluLookAt(dist, dist, dist,  /* position of camera */
              0.0,  0,  0.0,   /* where camera is pointing at */
              0.0,  1.0,  0.0);  /* which direction is up */


    // Coordinate system
    glBegin(GL_LINES);
    glColor3d(1.0, 0.0, 0.0);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(3.0, 0.0, 0.0);

    glColor3d(0.0, 1.0, 0.0);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(0.0, 3.0, 0.0);

    glColor3d(0.0, 0.0, 1.0);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(0.0, 0.0, 3.0);
    glEnd();


    DrawConvBelt();

    glLoadIdentity();
    gluLookAt(dist, dist, dist,  /* position of camera */
              0.0,  0,  0.0,   /* where camera is pointing at */
              0.0,  1.0,  0.0);  /* which direction is up */

    WasteZCoord -= STEP;
    if(WasteZCoord <= -7){
//        qDebug("kokosik");
    }

    glTranslatef(0, 0, WasteZCoord);
    float UnknownWasteColour = 0.4;
    glColor3f(UnknownWasteColour,UnknownWasteColour,UnknownWasteColour);
    glutSolidCube(1);

//    glFlush();

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

void CellContent::DrawConvBelt(){
    /* ConvBelt is a rectangle in isometric view, made out of 3 sides: front, right side, and a top.
     * General dimensions are: */
    float x = 2;    // length
    float y = 0.5;  // heigth
    float z = 10;   // depth
    // For proper display, there is need for translation
    glTranslatef(-0.5*x,    // In order for middle of CB to be on the X axis
                 -1,        // Waste begins at height -0.5, and CB has 0.5 thickness
                 -5.5);     // Nice constant ;)
    /* Approximate representation using points as vertices
     *               __P4_______
     *        ___----         __P5
     *  ___---           ___--  |
     * P3 ______  ____---       |
     * |        P2              |
     * |         |            __P6
     * |         |       __---
     * P0 ______ |____---
     *          P1
     * Numeration isn't coincidental! For proper display, one need to draw points
     * according to right hand rule for axis
    */
    float Points[7][3] = {{0, 0, z},  // P0
                          {x, 0, z},
                          {x, y, z},  //.
                          {0, y, z},  //.
                          {0, y, 0},  //.
                          {x, y, 0},
                          {x, 0, 0}}; // P6

    // Conv Belt colour
    float CBshade = 0.8;
    glColor3f(CBshade, CBshade, CBshade);

    glPushMatrix();
    //*************************************************

    // Front side   P0-3
    glBegin(GL_QUADS);
    for(int P = 0; P < 4; ++P){
        glVertex3f( Points[P][0], Points[P][1], Points[P][2]);
    }
    glEnd();

    // Right side   P6,5,2,1
    glBegin(GL_QUADS);
        glVertex3f( Points[6][0], Points[6][1], Points[6][2]);
        glVertex3f( Points[5][0], Points[5][1], Points[5][2]);
        glVertex3f( Points[2][0], Points[2][1], Points[2][2]);
        glVertex3f( Points[1][0], Points[1][1], Points[1][2]);
    glEnd();

    // Top side     P5-2
    glBegin(GL_QUADS);
        for(int P = 5; P > 1; --P){ // Iterate high(5) to low(2)
            glVertex3f( Points[P][0], Points[P][1], Points[P][2]);
        }
    glEnd();

    glPopMatrix();
}

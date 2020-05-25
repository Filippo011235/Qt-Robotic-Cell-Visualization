#include "cellcontent.hh"

//#define STEP 0.5

#include <QtDebug>
#include <QColor>

CellContent::CellContent(QWidget *parent): QGLWidget(parent){
    _SpeedTimer = new QTimer(this);
    _SpeedTimer->setInterval(40);
    _SpeedTimer->setObjectName("Timer");

    ConvSpeed = 0.20;

    connect(_SpeedTimer, SIGNAL(timeout()),this,SLOT(updateGL()));
    ConvBeltMovement();

    QMetaObject::connectSlotsByName(this);
}

CellContent::~CellContent(){
}

void CellContent::initializeGL(){
    glClearColor(1,1,1,0); // Background colour
    glEnable(GL_DEPTH_TEST); // For rendering 3D
    glEnable(GL_CULL_FACE); // Display only visible front of the objects
    glShadeModel(GL_SMOOTH);  // Smooth shading. The shadow smoothes the fine blend of colors through the polygon and smoothes the external light.
    glEnable(GL_COLOR_MATERIAL);
}


void CellContent::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    SetScene();     // Isometric view

    // Coordinate system - for debug purposes
//    glBegin(GL_LINES);
//        glColor3d(1.0, 0.0, 0.0);
//        glVertex3d(0.0, 0.0, 0.0);
//        glVertex3d(3.0, 0.0, 0.0);
//        glColor3d(0.0, 1.0, 0.0);
//        glVertex3d(0.0, 0.0, 0.0);
//        glVertex3d(0.0, 3.0, 0.0);
//        glColor3d(0.0, 0.0, 1.0);
//        glVertex3d(0.0, 0.0, 0.0);
//        glVertex3d(0.0, 0.0, 3.0);
//    glEnd();

    DrawConvBelt();
    SetScene();

    for (int i=0; i < 5; ++i) {
        DrawContainer(ContainerDistances_X[i], ContainerDistances_Z[i], MaterialsColours[i]);
    }

    //**********************************************************

    for(int i = 0; i < 5; ++i){
        if(!MaterialStreams[i].empty()){
            for (unsigned int j = 0; j < MaterialStreams[i].size(); ++j) {
                SetScene();
                // Before reaching Container
                if(MaterialStreams[i][j].getZLocation() > ContainerDistances_Z[i]+1){
                    if(MaterialStreams[i][j].getZLocation() <= 2.5){
                        MaterialStreams[i][j].getColour().getRgbF(&rgb[0], &rgb[1], &rgb[2]);
                        glColor3f((float)rgb[0], (float)rgb[1], (float)rgb[2]);
                    } else {
                        glColor3f(_BeforeRecognition,_BeforeRecognition,_BeforeRecognition);
                    }
                    MaterialStreams[i][j].ZAdvance(ConvSpeed);
                    glTranslatef(0, 0, MaterialStreams[i][j].getZLocation());
                    glutSolidCube(1);
                // Waste can be sorted to proper Container
                } else {
                    MaterialStreams[i][j].getColour().getRgbF(&rgb[0], &rgb[1], &rgb[2]);
                    glColor3f((float)rgb[0], (float)rgb[1], (float)rgb[2]);
                    // Depending on which Material Waste Stream it is, different condition apply
                    if(i < 2){ // PET, Karton
                        if(MaterialStreams[i][j].getXLocation() <= ContainerDistances_X[i]+1.25){
                             MaterialStreams[i].erase(MaterialStreams[i].begin()); // FIFO;
                             if(MaterialStreams[i][j].getHeaviness()){
                                 emit WasteSorted(i);
                             }
                         } else {
                             MaterialStreams[i][j].XAdvance(ConvSpeed);
                             glTranslatef(MaterialStreams[i][j].getXLocation(), 0, MaterialStreams[i][j].getZLocation());
                             glutSolidCube(1);
                         }
                    } else if (i >= 2 && i < 4){ // HDPE, Alum
                        if(MaterialStreams[i][j].getXLocation() >= ContainerDistances_X[i]+0.75){
                            MaterialStreams[i].erase(MaterialStreams[i].begin()); // FIFO;
                            if(MaterialStreams[i][j].getHeaviness()){
                                emit WasteSorted(i);
                            }
                        } else {
                            MaterialStreams[i][j].XAdvance(-ConvSpeed);
                            glTranslatef(MaterialStreams[i][j].getXLocation(), 0, MaterialStreams[i][j].getZLocation());
                            glutSolidCube(1);
                        }
                    } else { // Nieznany
                        MaterialStreams[i].erase(MaterialStreams[i].begin()); // FIFO;
                        if(MaterialStreams[i][j].getHeaviness()){
                            emit WasteSorted(i);
                        }
                    }
                }

            } // for Waste in Stream
        } // if(!MaterialStreams)
    } // for( i < 5)

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

void CellContent::AddWaste(Waste NewOne){
    NewOne.setZLocation(5); // Start at the edge of the ConvBelt
    NewOne.setXLocation(0); // Aligned with the X axis
    MaterialStreams[NewOne.getMaterial()].push_back(NewOne);
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
    float CBshade = 0.9;
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

void CellContent::DrawContainer(float X_coord, float Z_coord, QColor Colour){
    /* ConvBelt is a rectangle in isometric view, made out of 3 sides: front, right side, and a top.
     * General dimensions are: */
    float x = 2;    // length
    float y = 3;  // heigth
    float z = 2;   // depth
    // For proper display, there is need for translation
    glTranslatef(X_coord, -0.5, Z_coord);

    qreal rgb_colours[3];
    Colour.getRgbF(&rgb_colours[0], &rgb_colours[1], &rgb_colours[2]);
    glColor3f(rgb_colours[0], rgb_colours[1], rgb_colours[2]);

    /* Approximate representation using points as vertices
     *            _P4_______
     *        __--         _P5
     *  ___---         __--  |
     * P3 ______  __---      |
     * |        P2           |
     * |         |         __P6
     * |         |     __---
     * P0 ______ |__---
     *          P1
     * Numeration isn't coincidental! For proper display, one need to draw points
     * according to right hand rule for axis
    */
    float Points[7][3] = {{0, -y, z},  // P0
                          {x, -y, z},
                          {x, 0, z},  //.
                          {0, 0, z},  //.
                          {0, 0, 0},  //.
                          {x, 0, 0},
                          {x, -y, 0}}; // P6

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

    // Darkness within
    glTranslatef(0.25,0.01,0.25);

    glColor3f(0,0,0);

    glPushMatrix();
    glBegin(GL_QUADS);
        glVertex3f(0,0,0);
        glVertex3f(0,0,1.5);

        glVertex3f(1.5,0,1.5);
        glVertex3f(1.5,0,0);
    glEnd();
    glPopMatrix();

    SetScene();
}

void CellContent::SetScene(){
    glLoadIdentity();
    gluLookAt(CameraDistance, CameraDistance, CameraDistance,  /* position of camera */
              0.0,  0,  0.0,   /* where camera is pointing at */
              0.0,  1.0,  0.0);  /* which direction is up */
}

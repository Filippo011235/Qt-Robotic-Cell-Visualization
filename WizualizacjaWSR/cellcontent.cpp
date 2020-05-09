#include "cellcontent.hh"
#include "ui_cellcontent.h"

//CellContent::CellContent(QWidget *parent) :
//    QWidget(parent)
//CellContent::CellContent(Qt3DExtras::Qt3DWindow *parent)
    //:
//      Qt3DExtras::Qt3DWindow(parent)

  //  ,
//    ui(new Ui::CellContent)
//    {

//    ui->setupUi(this);

//    Qt3DExtras::Qt3DWindow *window = new Qt3DExtras::Qt3DWindow;
//    Qt3DExtras::QForwardRenderer *forward_render = window->defaultFrameGraph();
//    forward_render->setClearColor(QColor("white"));
//    QWidget *window_container = QWidget::createWindowContainer(window);

//    QSize screen_size = window->screen()->size();
//    window_container->setMinimumSize(QSize(200,100));
//    window_container->setMaximumSize(screen_size);

//    Qt3DCore::QEntity *root_entity = new Qt3DCore::QEntity();
//    window->setRootEntity(root_entity);

//    Qt3DRender::QCamera *camera_entity = window->camera();
//    camera_entity->lens()->setPerspectiveProjection(45.0f,16.0f/9.0f,0.1f,100.0f);
//    camera_entity->setPosition(QVector3D(0, 0, 20.0f));
//    camera_entity->setUpVector((QVector3D(0,1,0)));
//    camera_entity->setViewCenter(QVector3D(0,0,0));

//    Qt3DCore::QEntity *light_entity = new Qt3DCore::QEntity(root_entity);
//    Qt3DRender::QPointLight *point_light_component = new Qt3DRender::QPointLight;
//    point_light_component->setColor("white");
//    point_light_component->setIntensity(1);
//    light_entity->addComponent(point_light_component);

//    Qt3DCore::QTransform *light_transform = new Qt3DCore::QTransform();
//    light_transform->setTranslation(camera_entity->position());
//    light_entity->addComponent(light_transform);

//    Qt3DExtras::QFirstPersonCameraController *cam_controller = new Qt3DExtras::QFirstPersonCameraController(root_entity);
//    cam_controller->setCamera(camera_entity);

//    Qt3DCore::QEntity *sphere_entity = new Qt3DCore::QEntity(root_entity);

//    Qt3DExtras::QSphereMesh *mesh = new Qt3DExtras::QSphereMesh();
//    mesh->setRings(30);
//    mesh->setSlices(30);
//    mesh->setRadius(2);
//    sphere_entity->addComponent(mesh);

//    Qt3DExtras::QPhongMaterial *sphere_material = new Qt3DExtras::QPhongMaterial();
//    sphere_material->setDiffuse(QColor("green"));
//    sphere_entity->addComponent(sphere_material);

//    window_container->show();
//    window->show();

//}

//CellContent::~CellContent()
//{
//    delete ui;
//}

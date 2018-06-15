#include "Application.h"

#include "OrthographicCamera.h"
#include "ThirdPersonCamera.h"
#include "FirstPersonCamera.h"
#include "DirectionalLight.h"
#include "EventManager.h"
#include "FlyingCamera.h"
#include "AmbientLight.h"
#include "Landscape.h"
#include "Sphere.h"
#include "Plane.h"
#include "Cube.h"
#include "Node.h"

#include "Building1.h"
#include "Building2.h"
#include "Building3.h"
#include "Shop1.h"
#include "House1.h"
#include "Road1.h"
#include "Road2.h"
#include "Road3.h"
#include "Road4.h"
#include "Road5.h"
#include "Road6.h"
#include "Road7.h"
#include "Grass.h"

namespace ege
{
    Application::Application(const StartUpDescription& desc)
        : CoreApplication(desc)
    {
    }

    Application::~Application()
    {
    }

    void Application::RunMainLoop()
    {
        CoreApplication::RunMainLoop();
    }

    void Application::Update()
    {
        CoreApplication::Update();
    }

    void Application::Draw()
    {
        CoreApplication::Draw();
    }

    void Application::OnStartUp()
    {
        CoreApplication::OnStartUp();
        SceneLoader();
    }

    void Application::OnShutDown()
    {
        CoreApplication::OnShutDown();
    }

    void Application::SceneLoader()
    {
        _scene = ege_shared_ptr_new<Scene>();

        SPtr<Node> node                = ege_shared_ptr_new<Node>();
        SPtr<ThirdPersonCamera> camera = ege_shared_ptr_new<ThirdPersonCamera>();
        SPtr<AmbientLight> ambient     = ege_shared_ptr_new<AmbientLight>();
        SPtr<DirectionalLight> sun     = ege_shared_ptr_new<DirectionalLight>();

        SPtr<Building3> building1_1 = ege_shared_ptr_new<Building3>();
        SPtr<Building2> building2_1 = ege_shared_ptr_new<Building2>();
        SPtr<Building3> building4_1 = ege_shared_ptr_new<Building3>();
        SPtr<Building1> building5_1 = ege_shared_ptr_new<Building1>();
        SPtr<Building2> building6_1 = ege_shared_ptr_new<Building2>();
        SPtr<Building3> building8_1 = ege_shared_ptr_new<Building3>();
        SPtr<Building2> building9_1 = ege_shared_ptr_new<Building2>();

        SPtr<Building2> building1_2 = ege_shared_ptr_new<Building2>();
        SPtr<Building3> building2_2 = ege_shared_ptr_new<Building3>();
        SPtr<Building2> building4_2 = ege_shared_ptr_new<Building2>();
        SPtr<Building1> building5_2 = ege_shared_ptr_new<Building1>();
        SPtr<Building3> building6_2 = ege_shared_ptr_new<Building3>();
        SPtr<Building2> building8_2 = ege_shared_ptr_new<Building2>();
        SPtr<Building3> building9_2 = ege_shared_ptr_new<Building3>();

        SPtr<Building3> building0_4 = ege_shared_ptr_new<Building3>();
        SPtr<Building2> building1_4 = ege_shared_ptr_new<Building2>();
        SPtr<Building3> building7_4 = ege_shared_ptr_new<Building3>();
        SPtr<Building2> building8_4 = ege_shared_ptr_new<Building2>();

        SPtr<Building2> building0_5 = ege_shared_ptr_new<Building2>();
        SPtr<Building3> building1_5 = ege_shared_ptr_new<Building3>();
        SPtr<Building2> building7_5 = ege_shared_ptr_new<Building2>();
        SPtr<Building3> building8_5 = ege_shared_ptr_new<Building3>();

        SPtr<Road1> road0_0 = ege_shared_ptr_new<Road1>();
        SPtr<Road4> road0_1 = ege_shared_ptr_new<Road4>();
        SPtr<Road4> road0_2 = ege_shared_ptr_new<Road4>();
        SPtr<Road1> road0_3 = ege_shared_ptr_new<Road1>();
        SPtr<Road4> road0_4 = ege_shared_ptr_new<Road4>();
        SPtr<Road4> road0_5 = ege_shared_ptr_new<Road4>();
        SPtr<Road4> road0_6 = ege_shared_ptr_new<Road4>();
        SPtr<Road1> road0_7 = ege_shared_ptr_new<Road1>();
        SPtr<Road4> road0_8 = ege_shared_ptr_new<Road4>();
        SPtr<Road4> road0_9 = ege_shared_ptr_new<Road4>();
        SPtr<Road1> road0_10 = ege_shared_ptr_new<Road1>();

        SPtr<Road4> road1_0 = ege_shared_ptr_new<Road4>();
        SPtr<Road6> road1_1 = ege_shared_ptr_new<Road6>();
        SPtr<Road6> road1_2 = ege_shared_ptr_new<Road6>();
        SPtr<Road4> road1_3 = ege_shared_ptr_new<Road4>();
        SPtr<Road6> road1_4 = ege_shared_ptr_new<Road6>();
        SPtr<Road6> road1_5 = ege_shared_ptr_new<Road6>();
        SPtr<Road6> road1_6 = ege_shared_ptr_new<Road6>();
        SPtr<Road4> road1_7 = ege_shared_ptr_new<Road4>();
        SPtr<Road6> road1_8 = ege_shared_ptr_new<Road6>();
        SPtr<Road6> road1_9 = ege_shared_ptr_new<Road6>();
        SPtr<Road4> road1_10 = ege_shared_ptr_new<Road4>();

        SPtr<Road4> road2_0 = ege_shared_ptr_new<Road4>();
        SPtr<Road6> road2_1 = ege_shared_ptr_new<Road6>();
        SPtr<Road6> road2_2 = ege_shared_ptr_new<Road6>();
        SPtr<Road4> road2_3 = ege_shared_ptr_new<Road4>();
        SPtr<Road6> road2_4 = ege_shared_ptr_new<Road6>();
        SPtr<Road6> road2_5 = ege_shared_ptr_new<Road6>();
        SPtr<Road6> road2_6 = ege_shared_ptr_new<Road6>();
        SPtr<Road4> road2_7 = ege_shared_ptr_new<Road4>();
        SPtr<Road6> road2_8 = ege_shared_ptr_new<Road6>();
        SPtr<Road6> road2_9 = ege_shared_ptr_new<Road6>();
        SPtr<Road4> road2_10 = ege_shared_ptr_new<Road4>();

        SPtr<Road1> road3_0 = ege_shared_ptr_new<Road1>();
        SPtr<Road4> road3_1 = ege_shared_ptr_new<Road4>();
        SPtr<Road4> road3_2 = ege_shared_ptr_new<Road4>();
        SPtr<Road1> road3_3 = ege_shared_ptr_new<Road1>();
        SPtr<Road4> road3_4 = ege_shared_ptr_new<Road4>();
        SPtr<Road4> road3_5 = ege_shared_ptr_new<Road4>();
        SPtr<Road4> road3_6 = ege_shared_ptr_new<Road4>();
        SPtr<Road1> road3_7 = ege_shared_ptr_new<Road1>();
        SPtr<Road4> road3_8 = ege_shared_ptr_new<Road4>();
        SPtr<Road4> road3_9 = ege_shared_ptr_new<Road4>();
        SPtr<Road1> road3_10 = ege_shared_ptr_new<Road1>();

        SPtr<Road4> road4_0 = ege_shared_ptr_new<Road4>();
        SPtr<Road6> road4_1 = ege_shared_ptr_new<Road6>();
        SPtr<Road6> road4_2 = ege_shared_ptr_new<Road6>();
        SPtr<Road4> road4_3 = ege_shared_ptr_new<Road4>();
        SPtr<Road4> road4_7 = ege_shared_ptr_new<Road4>();
        SPtr<Road6> road4_8 = ege_shared_ptr_new<Road6>();
        SPtr<Road6> road4_9 = ege_shared_ptr_new<Road6>();
        SPtr<Road4> road4_10 = ege_shared_ptr_new<Road4>();

        SPtr<Road4> road5_0 = ege_shared_ptr_new<Road4>();
        SPtr<Road6> road5_1 = ege_shared_ptr_new<Road6>();
        SPtr<Road6> road5_2 = ege_shared_ptr_new<Road6>();
        SPtr<Road4> road5_3 = ege_shared_ptr_new<Road4>();
        SPtr<Road4> road5_7 = ege_shared_ptr_new<Road4>();
        SPtr<Road6> road5_8 = ege_shared_ptr_new<Road6>();
        SPtr<Road6> road5_9 = ege_shared_ptr_new<Road6>();
        SPtr<Road4> road5_10 = ege_shared_ptr_new<Road4>();

        SPtr<Road1> road6_0 = ege_shared_ptr_new<Road1>();
        SPtr<Road4> road6_1 = ege_shared_ptr_new<Road4>();
        SPtr<Road4> road6_2 = ege_shared_ptr_new<Road4>();
        SPtr<Road7> road6_3 = ege_shared_ptr_new<Road7>();
        SPtr<Road4> road6_4 = ege_shared_ptr_new<Road4>();
        SPtr<Road4> road6_5 = ege_shared_ptr_new<Road4>();
        SPtr<Road4> road6_6 = ege_shared_ptr_new<Road4>();
        SPtr<Road1> road6_7 = ege_shared_ptr_new<Road1>();
        SPtr<Road4> road6_8 = ege_shared_ptr_new<Road4>();
        SPtr<Road4> road6_9 = ege_shared_ptr_new<Road4>();
        SPtr<Road1> road6_10 = ege_shared_ptr_new<Road1>();

        SPtr<Grass> grass4_4 = ege_shared_ptr_new<Grass>();
        SPtr<Grass> grass4_5 = ege_shared_ptr_new<Grass>();
        SPtr<Grass> grass4_6 = ege_shared_ptr_new<Grass>();
        SPtr<Grass> grass5_4 = ege_shared_ptr_new<Grass>();
        SPtr<Grass> grass5_5 = ege_shared_ptr_new<Grass>();
        SPtr<Grass> grass5_6 = ege_shared_ptr_new<Grass>();

        _scene->Initialise();
        camera->Initialise();
        ambient->Initialise();
        sun->Initialise();

        building1_1->Initialise();
        building2_1->Initialise();
        building4_1->Initialise();
        building5_1->Initialise();
        building6_1->Initialise();
        building8_1->Initialise();
        building9_1->Initialise();

        building1_2->Initialise();
        building2_2->Initialise();
        building4_2->Initialise();
        building5_2->Initialise();
        building6_2->Initialise();
        building8_2->Initialise();
        building9_2->Initialise();

        building0_4->Initialise();
        building1_4->Initialise();
        building7_4->Initialise();
        building8_4->Initialise();

        building0_5->Initialise();
        building1_5->Initialise();
        building7_5->Initialise();
        building8_5->Initialise();

        road0_0->Initialise();
        road0_1->Initialise();
        road0_2->Initialise();
        road0_3->Initialise();
        road0_4->Initialise();
        road0_5->Initialise();
        road0_6->Initialise();
        road0_7->Initialise();
        road0_8->Initialise();
        road0_9->Initialise();
        road0_10->Initialise();

        road1_0->Initialise();
        road1_1->Initialise();
        road1_2->Initialise();
        road1_3->Initialise();
        road1_4->Initialise();
        road1_5->Initialise();
        road1_6->Initialise();
        road1_7->Initialise();
        road1_8->Initialise();
        road1_9->Initialise();
        road1_10->Initialise();

        road2_0->Initialise();
        road2_1->Initialise();
        road2_2->Initialise();
        road2_3->Initialise();
        road2_4->Initialise();
        road2_5->Initialise();
        road2_6->Initialise();
        road2_7->Initialise();
        road2_8->Initialise();
        road2_9->Initialise();
        road2_10->Initialise();

        road3_0->Initialise();
        road3_1->Initialise();
        road3_2->Initialise();
        road3_3->Initialise();
        road3_4->Initialise();
        road3_5->Initialise();
        road3_6->Initialise();
        road3_7->Initialise();
        road3_8->Initialise();
        road3_9->Initialise();
        road3_10->Initialise();

        road4_0->Initialise();
        road4_1->Initialise();
        road4_2->Initialise();
        road4_3->Initialise();
        road4_7->Initialise();
        road4_8->Initialise();
        road4_9->Initialise();
        road4_10->Initialise();

        road5_0->Initialise();
        road5_1->Initialise();
        road5_2->Initialise();
        road5_3->Initialise();
        road5_7->Initialise();
        road5_8->Initialise();
        road5_9->Initialise();
        road5_10->Initialise();

        road6_0->Initialise();
        road6_1->Initialise();
        road6_2->Initialise();
        road6_3->Initialise();
        road6_4->Initialise();
        road6_5->Initialise();
        road6_6->Initialise();
        road6_7->Initialise();
        road6_8->Initialise();
        road6_9->Initialise();
        road6_10->Initialise();

        grass4_4->Initialise();
        grass4_5->Initialise();
        grass4_6->Initialise();

        grass5_4->Initialise();
        grass5_5->Initialise();
        grass5_6->Initialise();

        building1_1->RotatePitch(0.0f);
        building2_1->RotatePitch(0.0f);
        building4_1->RotatePitch(0.0f);
        building5_1->RotatePitch(0.0f);
        building6_1->RotatePitch(0.0f);
        building8_1->RotatePitch(0.0f);
        building9_1->RotatePitch(0.0f);

        building1_2->RotatePitch(XM_PI);
        building2_2->RotatePitch(XM_PI);
        building4_2->RotatePitch(XM_PI);
        building5_2->RotatePitch(XM_PI);
        building6_2->RotatePitch(XM_PI);
        building8_2->RotatePitch(XM_PI);
        building9_2->RotatePitch(XM_PI);

        building0_4->RotatePitch(0.0f);
        building1_4->RotatePitch(0.0f);
        building7_4->RotatePitch(0.0f);
        building8_4->RotatePitch(0.0f);

        building0_5->RotatePitch(XM_PI);
        building1_5->RotatePitch(XM_PI);
        building7_5->RotatePitch(XM_PI);
        building8_5->RotatePitch(XM_PI);

        road0_0->RotatePitch(0.0f);
        road0_1->RotatePitch(XM_PIDIV2);
        road0_2->RotatePitch(XM_PIDIV2);
        road0_3->RotatePitch(0.0f);
        road0_4->RotatePitch(XM_PIDIV2);
        road0_5->RotatePitch(XM_PIDIV2);
        road0_6->RotatePitch(XM_PIDIV2);
        road0_7->RotatePitch(0.0f);
        road0_8->RotatePitch(XM_PIDIV2);
        road0_9->RotatePitch(XM_PIDIV2);
        road0_10->RotatePitch(0.0f);

        road1_0->RotatePitch(0.0f);
        road1_1->RotatePitch(0.0f);
        road1_2->RotatePitch(0.0f);
        road1_3->RotatePitch(0.0f);
        road1_4->RotatePitch(0.0f);
        road1_5->RotatePitch(0.0f);
        road1_6->RotatePitch(0.0f);
        road1_7->RotatePitch(0.0f);
        road1_8->RotatePitch(0.0f);
        road1_9->RotatePitch(0.0f);
        road1_10->RotatePitch(0.0f);

        road2_0->RotatePitch(0.0f);
        road2_1->RotatePitch(0.0f);
        road2_2->RotatePitch(0.0f);
        road2_3->RotatePitch(0.0f);
        road2_4->RotatePitch(0.0f);
        road2_5->RotatePitch(0.0f);
        road2_6->RotatePitch(0.0f);
        road2_7->RotatePitch(0.0f);
        road2_8->RotatePitch(0.0f);
        road2_9->RotatePitch(0.0f);
        road2_10->RotatePitch(0.0f);

        road3_0->RotatePitch(0.0f);
        road3_1->RotatePitch(XM_PIDIV2);
        road3_2->RotatePitch(XM_PIDIV2);
        road3_3->RotatePitch(0.0f);
        road3_4->RotatePitch(XM_PIDIV2);
        road3_5->RotatePitch(XM_PIDIV2);
        road3_6->RotatePitch(XM_PIDIV2);
        road3_7->RotatePitch(0.0f);
        road3_8->RotatePitch(XM_PIDIV2);
        road3_9->RotatePitch(XM_PIDIV2);
        road3_10->RotatePitch(0.0f);

        road4_0->RotatePitch(0.0f);
        road4_1->RotatePitch(0.0f);
        road4_2->RotatePitch(0.0f);
        road4_3->RotatePitch(0.0f);
        road4_7->RotatePitch(0.0f);
        road4_8->RotatePitch(0.0f);
        road4_9->RotatePitch(0.0f);
        road4_10->RotatePitch(0.0f);

        road5_0->RotatePitch(0.0f);
        road5_1->RotatePitch(0.0f);
        road5_2->RotatePitch(0.0f);
        road5_3->RotatePitch(0.0f);
        road5_7->RotatePitch(0.0f);
        road5_8->RotatePitch(0.0f);
        road5_9->RotatePitch(0.0f);
        road5_10->RotatePitch(0.0f);

        road6_0->RotatePitch(0.0f);
        road6_1->RotatePitch(XM_PIDIV2);
        road6_2->RotatePitch(XM_PIDIV2);
        road6_3->RotatePitch(0.0f);
        road6_4->RotatePitch(XM_PIDIV2);
        road6_5->RotatePitch(XM_PIDIV2);
        road6_6->RotatePitch(XM_PIDIV2);
        road6_7->RotatePitch(0.0f);
        road6_8->RotatePitch(XM_PIDIV2);
        road6_9->RotatePitch(XM_PIDIV2);
        road6_10->RotatePitch(0.0f);

        building1_1->GoTo(XMFLOAT3(-80.0f, 0.0f, 40.0));
        building2_1->GoTo(XMFLOAT3(-60.0f, 0.0f, 40.0));
        building4_1->GoTo(XMFLOAT3(-20.0f, 0.0f, 40.0));
        building5_1->GoTo(XMFLOAT3(0.0f, 0.0f, 40.0));
        building6_1->GoTo(XMFLOAT3(20.0f, 0.0f, 40.0));
        building8_1->GoTo(XMFLOAT3(60.0f, 0.0f, 40.0));
        building9_1->GoTo(XMFLOAT3(80.0f, 0.0f, 40.0));

        building1_2->GoTo(XMFLOAT3(-80.0f, 0.0f, 20.0));
        building2_2->GoTo(XMFLOAT3(-60.0f, 0.0f, 20.0));
        building4_2->GoTo(XMFLOAT3(-20.0f, 0.0f, 20.0));
        building5_2->GoTo(XMFLOAT3(00.0f, 0.0f, 20.0));
        building6_2->GoTo(XMFLOAT3(20.0f, 0.0f, 20.0));
        building8_2->GoTo(XMFLOAT3(60.0f, 0.0f, 20.0));
        building9_2->GoTo(XMFLOAT3(80.0f, 0.0f, 20.0));

        building0_4->GoTo(XMFLOAT3(-80.0f, 0.0f, -20.0));
        building1_4->GoTo(XMFLOAT3(-60.0f, 0.0f, -20.0));
        building7_4->GoTo(XMFLOAT3(60.0f, 0.0f, -20.0));
        building8_4->GoTo(XMFLOAT3(80.0f, 0.0f, -20.0));

        building0_5->GoTo(XMFLOAT3(-80.0f, 0.0f, -40.0));
        building1_5->GoTo(XMFLOAT3(-60.0f, 0.0f, -40.0));
        building7_5->GoTo(XMFLOAT3(60.0f, 0.0f, -40.0));
        building8_5->GoTo(XMFLOAT3(80.0f, 0.0f, -40.0));

        road0_0->GoTo(XMFLOAT3(-100.0f, 0.0f, 60.0f));
        road0_1->GoTo(XMFLOAT3(-80.0f, 0.0f, 60.0f));
        road0_2->GoTo(XMFLOAT3(-60.0f, 0.0f, 60.0f));
        road0_3->GoTo(XMFLOAT3(-40.0f, 0.0f, 60.0f));
        road0_4->GoTo(XMFLOAT3(-20.0f, 0.0f, 60.0f));
        road0_5->GoTo(XMFLOAT3(0.0f, 0.0f, 60.0f));
        road0_6->GoTo(XMFLOAT3(20.0f, 0.0f, 60.0f));
        road0_7->GoTo(XMFLOAT3(40.0f, 0.0f, 60.0f));
        road0_8->GoTo(XMFLOAT3(60.0f, 0.0f, 60.0f));
        road0_9->GoTo(XMFLOAT3(80.0f, 0.0f, 60.0f));
        road0_10->GoTo(XMFLOAT3(100.0f, 0.0f, 60.0f));

        road1_0->GoTo(XMFLOAT3(-100.0f, 0.0f, 40.0f));
        road1_1->GoTo(XMFLOAT3(-80.0f, 0.0f, 40.0f));
        road1_2->GoTo(XMFLOAT3(-60.0f, 0.0f, 40.0f));
        road1_3->GoTo(XMFLOAT3(-40.0f, 0.0f, 40.0f));
        road1_4->GoTo(XMFLOAT3(-20.0f, 0.0f, 40.0f));
        road1_5->GoTo(XMFLOAT3(0.0f, 0.0f, 40.0f));
        road1_6->GoTo(XMFLOAT3(20.0f, 0.0f, 40.0f));
        road1_7->GoTo(XMFLOAT3(40.0f, 0.0f, 40.0f));
        road1_8->GoTo(XMFLOAT3(60.0f, 0.0f, 40.0f));
        road1_9->GoTo(XMFLOAT3(80.0f, 0.0f, 40.0f));
        road1_10->GoTo(XMFLOAT3(100.0f, 0.0f, 40.0f));

        road2_0->GoTo(XMFLOAT3(-100.0f, 0.0f, 20.0f));
        road2_1->GoTo(XMFLOAT3(-80.0f, 0.0f, 20.0f));
        road2_2->GoTo(XMFLOAT3(-60.0f, 0.0f, 20.0f));
        road2_3->GoTo(XMFLOAT3(-40.0f, 0.0f, 20.0f));
        road2_4->GoTo(XMFLOAT3(-20.0f, 0.0f, 20.0f));
        road2_5->GoTo(XMFLOAT3(0.0f, 0.0f, 20.0f));
        road2_6->GoTo(XMFLOAT3(20.0f, 0.0f, 20.0f));
        road2_7->GoTo(XMFLOAT3(40.0f, 0.0f, 20.0f));
        road2_8->GoTo(XMFLOAT3(60.0f, 0.0f, 20.0f));
        road2_9->GoTo(XMFLOAT3(80.0f, 0.0f, 20.0f));
        road2_10->GoTo(XMFLOAT3(100.0f, 0.0f, 20.0f));

        road3_0->GoTo(XMFLOAT3(-100.0f, 0.0f, 0.0f));
        road3_1->GoTo(XMFLOAT3(-80.0f, 0.0f, 0.0f));
        road3_2->GoTo(XMFLOAT3(-60.0f, 0.0f, 0.0f));
        road3_3->GoTo(XMFLOAT3(-40.0f, 0.0f, 0.0f));
        road3_4->GoTo(XMFLOAT3(-20.0f, 0.0f, 0.0f));
        road3_5->GoTo(XMFLOAT3(0.0f, 0.0f, 0.0f));
        road3_6->GoTo(XMFLOAT3(20.0f, 0.0f, 0.0f));
        road3_7->GoTo(XMFLOAT3(40.0f, 0.0f, 0.0f));
        road3_8->GoTo(XMFLOAT3(60.0f, 0.0f, 0.0f));
        road3_9->GoTo(XMFLOAT3(80.0f, 0.0f, 0.0f));
        road3_10->GoTo(XMFLOAT3(100.0f, 0.0f, 0.0f));

        road4_0->GoTo(XMFLOAT3(-100.0f, 0.0f, -20.0f));
        road4_1->GoTo(XMFLOAT3(-80.0f, 0.0f, -20.0f));
        road4_2->GoTo(XMFLOAT3(-60.0f, 0.0f, -20.0f));
        road4_3->GoTo(XMFLOAT3(-40.0f, 0.0f, -20.0f));
        road4_7->GoTo(XMFLOAT3(40.0f, 0.0f, -20.0f));
        road4_8->GoTo(XMFLOAT3(60.0f, 0.0f, -20.0f));
        road4_9->GoTo(XMFLOAT3(80.0f, 0.0f, -20.0f));
        road4_10->GoTo(XMFLOAT3(100.0f, 0.0f, -20.0f));

        road5_0->GoTo(XMFLOAT3(-100.0f, 0.0f, -40.0f));
        road5_1->GoTo(XMFLOAT3(-80.0f, 0.0f, -40.0f));
        road5_2->GoTo(XMFLOAT3(-60.0f, 0.0f, -40.0f));
        road5_3->GoTo(XMFLOAT3(-40.0f, 0.0f, -40.0f));
        road5_7->GoTo(XMFLOAT3(40.0f, 0.0f, -40.0f));
        road5_8->GoTo(XMFLOAT3(60.0f, 0.0f, -40.0f));
        road5_9->GoTo(XMFLOAT3(80.0f, 0.0f, -40.0f));
        road5_10->GoTo(XMFLOAT3(100.0f, 0.0f, -40.0f));

        road6_0->GoTo(XMFLOAT3(-100.0f, 0.0f, -60.0f));
        road6_1->GoTo(XMFLOAT3(-80.0f, 0.0f, -60.0f));
        road6_2->GoTo(XMFLOAT3(-60.0f, 0.0f, -60.0f));
        road6_3->GoTo(XMFLOAT3(-40.0f, 0.0f, -60.0f));
        road6_4->GoTo(XMFLOAT3(-20.0f, 0.0f, -60.0f));
        road6_5->GoTo(XMFLOAT3(0.0f, 0.0f, -60.0f));
        road6_6->GoTo(XMFLOAT3(20.0f, 0.0f, -60.0f));
        road6_7->GoTo(XMFLOAT3(40.0f, 0.0f, -60.0f));
        road6_8->GoTo(XMFLOAT3(60.0f, 0.0f, -60.0f));
        road6_9->GoTo(XMFLOAT3(80.0f, 0.0f, -60.0f));
        road6_10->GoTo(XMFLOAT3(100.0f, 0.0f, -60.0f));

        grass4_4->GoTo(XMFLOAT3(-20.0f, 0.0f, -20.0f));
        grass4_5->GoTo(XMFLOAT3(0.0f, 0.0f, -20.0f));
        grass4_6->GoTo(XMFLOAT3(20.0f, 0.0f, -20.0f));

        grass5_4->GoTo(XMFLOAT3(-20.0f, 0.0f, -40.0f));
        grass5_5->GoTo(XMFLOAT3(0.0f, 0.0f, -40.0f));
        grass5_6->GoTo(XMFLOAT3(20.0f, 0.0f, -40.0f));

        ambient->SetColor(XMFLOAT4(1.0f, 1.0f, 0.95f, 0.5f));

        sun->SetColor(XMFLOAT4(0.95f, 0.90f, 0.6f, 0.85f));
        sun->SetDirection(XMFLOAT3(-2.5f, -1.0f, 1.0f));

        node->SetScene(_scene);
        node->InsertEntity("camera", camera);
        node->InsertEntity("sun", sun);
        
        node->InsertEntity("building1_1", building1_1);
        node->InsertEntity("building2_1", building2_1);
        node->InsertEntity("building4_1", building4_1);
        node->InsertEntity("building5_1", building5_1);
        node->InsertEntity("building6_1", building6_1);
        node->InsertEntity("building8_1", building8_1);
        node->InsertEntity("building9_1", building9_1);

        node->InsertEntity("building1_2", building1_2);
        node->InsertEntity("building2_2", building2_2);
        node->InsertEntity("building4_2", building4_2);
        node->InsertEntity("building5_2", building5_2);
        node->InsertEntity("building6_2", building6_2);
        node->InsertEntity("building8_2", building8_2);
        node->InsertEntity("building9_2", building9_2);

        node->InsertEntity("building0_4", building0_4);
        node->InsertEntity("building1_4", building1_4);
        node->InsertEntity("building7_4", building7_4);
        node->InsertEntity("building8_4", building8_4);

        node->InsertEntity("building0_5", building0_5);
        node->InsertEntity("building1_5", building1_5);
        node->InsertEntity("building7_5", building7_5);
        node->InsertEntity("building8_5", building8_5);

        node->InsertEntity("road0_0", road0_0);
        node->InsertEntity("road0_1", road0_1);
        node->InsertEntity("road0_2", road0_2);
        node->InsertEntity("road0_3", road0_3);
        node->InsertEntity("road0_4", road0_4);
        node->InsertEntity("road0_5", road0_5);
        node->InsertEntity("road0_6", road0_6);
        node->InsertEntity("road0_7", road0_7);
        node->InsertEntity("road0_8", road0_8);
        node->InsertEntity("road0_9", road0_9);
        node->InsertEntity("road0_10", road0_10);

        node->InsertEntity("road1_0", road1_0);
        node->InsertEntity("road1_1", road1_1);
        node->InsertEntity("road1_2", road1_2);
        node->InsertEntity("road1_3", road1_3);
        node->InsertEntity("road1_4", road1_4);
        node->InsertEntity("road1_5", road1_5);
        node->InsertEntity("road1_6", road1_6);
        node->InsertEntity("road1_7", road1_7);
        node->InsertEntity("road1_8", road1_8);
        node->InsertEntity("road1_9", road1_9);
        node->InsertEntity("road1_10", road1_10);

        node->InsertEntity("road2_0", road2_0);
        node->InsertEntity("road2_1", road2_1);
        node->InsertEntity("road2_2", road2_2);
        node->InsertEntity("road2_3", road2_3);
        node->InsertEntity("road2_4", road2_4);
        node->InsertEntity("road2_5", road2_5);
        node->InsertEntity("road2_6", road2_6);
        node->InsertEntity("road2_7", road2_7);
        node->InsertEntity("road2_8", road2_8);
        node->InsertEntity("road2_9", road2_9);
        node->InsertEntity("road2_10", road2_10);

        node->InsertEntity("road3_0", road3_0);
        node->InsertEntity("road3_1", road3_1);
        node->InsertEntity("road3_2", road3_2);
        node->InsertEntity("road3_3", road3_3);
        node->InsertEntity("road3_4", road3_4);
        node->InsertEntity("road3_5", road3_5);
        node->InsertEntity("road3_6", road3_6);
        node->InsertEntity("road3_7", road3_7);
        node->InsertEntity("road3_8", road3_8);
        node->InsertEntity("road3_9", road3_9);
        node->InsertEntity("road3_10", road3_10);

        node->InsertEntity("road4_0", road4_0);
        node->InsertEntity("road4_1", road4_1);
        node->InsertEntity("road4_2", road4_2);
        node->InsertEntity("road4_3", road4_3);
        node->InsertEntity("road4_7", road4_7);
        node->InsertEntity("road4_8", road4_8);
        node->InsertEntity("road4_9", road4_9);
        node->InsertEntity("road4_10", road4_10);

        node->InsertEntity("road5_0", road5_0);
        node->InsertEntity("road5_1", road5_1);
        node->InsertEntity("road5_2", road5_2);
        node->InsertEntity("road5_3", road5_3);
        node->InsertEntity("road5_7", road5_7);
        node->InsertEntity("road5_8", road5_8);
        node->InsertEntity("road5_9", road5_9);
        node->InsertEntity("road5_10", road5_10);

        node->InsertEntity("road6_0", road6_0);
        node->InsertEntity("road6_1", road6_1);
        node->InsertEntity("road6_2", road6_2);
        node->InsertEntity("road6_3", road6_3);
        node->InsertEntity("road6_4", road6_4);
        node->InsertEntity("road6_5", road6_5);
        node->InsertEntity("road6_6", road6_6);
        node->InsertEntity("road6_7", road6_7);
        node->InsertEntity("road6_8", road6_8);
        node->InsertEntity("road6_9", road6_9);
        node->InsertEntity("road6_10", road6_10);

        node->InsertEntity("grass4_4", grass4_4);
        node->InsertEntity("grass4_5", grass4_5);
        node->InsertEntity("grass4_6", grass4_6);

        node->InsertEntity("grass5_4", grass5_4);
        node->InsertEntity("grass5_5", grass5_5);
        node->InsertEntity("grass5_6", grass5_6);

        _scene->InsertCamera("camera", camera);
        _scene->InsertLight("sun", sun);
        _scene->InsertNode("root", node);

        _scene->SetActiveCamera(camera);
        _scene->SetAmbientLight(ambient);
    }

    Application& gApplication()
    {
        return static_cast<Application&>(Application::Instance());
    }

    Application* gApplicationPtr()
    {
        return static_cast<Application*>(Application::InstancePtr());
    }
}
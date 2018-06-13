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
#include "Road6.h"

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
        SPtr<Building1> building       = ege_shared_ptr_new<Building1>();
        SPtr<Road6> road               = ege_shared_ptr_new<Road6>();

        _scene->Initialise();
        camera->Initialise();
        ambient->Initialise();
        sun->Initialise();
        building->Initialise();
        road->Initialise();

        ambient->SetColor(XMFLOAT4(1.0f, 1.0f, 0.95f, 0.7f));

        sun->SetColor(XMFLOAT4(0.95f, 0.90f, 0.6f, 0.8f));
        sun->SetDirection(XMFLOAT3(-0.5f, -1.0f, -1.0f));

        node->SetScene(_scene);
        node->InsertEntity("camera", camera);
        node->InsertEntity("sun", sun);
        node->InsertEntity("building", building);
        node->InsertEntity("road", road);

        _scene->InsertCamera("camera", camera);
        _scene->InsertLight("sun", sun);
        _scene->InsertNode("root", node);

        _scene->SetActiveCamera(camera);
        _scene->SetAmbientLight(ambient);

        //gWindow().SetShowCursor(false);
        //gWindow().SetClipCursor(true);

        /*_scene                           = ege_shared_ptr_new<Scene>();

        SPtr<Node> node                  = ege_shared_ptr_new<Node>();
        SPtr<FlyingCamera> camera1       = ege_shared_ptr_new<FlyingCamera>();
        SPtr<ThirdPersonCamera> camera2  = ege_shared_ptr_new<ThirdPersonCamera>();
        SPtr<FirstPersonCamera> camera3  = ege_shared_ptr_new<FirstPersonCamera>();
        SPtr<OrthographicCamera> camera4 = ege_shared_ptr_new<OrthographicCamera>();
        SPtr<DirectionalLight> light     = ege_shared_ptr_new<DirectionalLight>();
        SPtr<Sphere> sphere              = ege_shared_ptr_new<Sphere>();
        SPtr<Plane> plane                = ege_shared_ptr_new<Plane>();
        SPtr<Cube> cube                  = ege_shared_ptr_new<Cube>();
        SPtr<Cube> cube2                 = ege_shared_ptr_new<Cube>();
        SPtr<Landscape> landscape        = ege_shared_ptr_new<Landscape>();
        SPtr<AmbientLight> ambient       = ege_shared_ptr_new<AmbientLight>();

        _scene->Initialise();
        camera1->Initialise();
        camera2->Initialise();
        camera3->Initialise();
        camera4->Initialise();
        light->Initialise();
        sphere->Initialise();
        plane->Initialise();
        cube->Initialise();
        cube2->Initialise();
        landscape->Initialise();

        light->SetColor(XMFLOAT4(1.0f, 1.0, 1.0f, 0.8f));
        light->SetDirection(XMFLOAT3(-0.5f, -1.0f, 1.0f));

        ambient->SetColor(XMFLOAT4(0.95f, 0.9f, 0.54f, 0.6f));

        node->SetScene(_scene);
        node->InsertEntity("camera", camera2);
        node->InsertEntity("light", light);
        node->InsertEntity("sphere", sphere);
        node->InsertEntity("plane", plane);
        node->InsertEntity("cube", cube);
        node->InsertEntity("cube2", cube2);
        //node->InsertEntity("landscape", landscape);

        cube->Move(3.0f, 1.0f, -3.0f);
        cube->Scale(cube->GetPosition(), 0.5f, 0.5f, 0.5f);

        cube2->Move(0.0f, 1.0f, -0.0f);

        sphere->Move(-2.0f, 1.0f, 2.0f);

        _scene->InsertCamera("camera", camera2);
        _scene->InsertLight("light", light);
        _scene->InsertNode("root", node);

        _scene->SetActiveCamera(camera2);
        _scene->SetAmbientLight(ambient);*/
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
#include "Application.h"

#include "ThirdPersonCamera.h"
#include "FirstPersonCamera.h"
#include "DirectionalLight.h"
#include "FlyingCamera.h"
#include "AmbientLight.h"
#include "Landscape.h"
#include "Sphere.h"
#include "Plane.h"
#include "Cube.h"
#include "Node.h"

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
        //gWindow().SetShowCursor(false);
        //gWindow().SetClipCursor(true);

        _scene                          = ege_shared_ptr_new<Scene>();

        SPtr<Node> node                 = ege_shared_ptr_new<Node>();
        SPtr<FlyingCamera> camera1      = ege_shared_ptr_new<FlyingCamera>();
        SPtr<ThirdPersonCamera> camera2 = ege_shared_ptr_new<ThirdPersonCamera>();
        SPtr<FirstPersonCamera> camera3 = ege_shared_ptr_new<FirstPersonCamera>();
        SPtr<DirectionalLight> light    = ege_shared_ptr_new<DirectionalLight>();
        SPtr<Sphere> sphere             = ege_shared_ptr_new<Sphere>();
        SPtr<Plane> plane               = ege_shared_ptr_new<Plane>();
        SPtr<Cube> cube                 = ege_shared_ptr_new<Cube>();
        SPtr<Cube> cube2                = ege_shared_ptr_new<Cube>();
        SPtr<Landscape> landscape       = ege_shared_ptr_new<Landscape>();
        SPtr<AmbientLight> ambient      = ege_shared_ptr_new<AmbientLight>();

        _scene->Initialise();
        camera1->Initialise();
        camera2->Initialise();
        camera3->Initialise();
        light->Initialise();
        sphere->Initialise();
        plane->Initialise();
        cube->Initialise();
        cube2->Initialise();
        landscape->Initialise();

        light->SetColor(XMFLOAT4(1.0f, 1.0, 1.0f, 0.8f));
        light->SetDirection(XMFLOAT3(0.5f, -0.5f, 0.5f));

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
        cube->Scale(XMFLOAT3(2.0f, 0.0f, -2.0f), 0.5f, 0.5f, 0.5f);
        //cube->RotatePitch(cube->GetPosition(), 3.0f);

        //cube2->Scale(0.5f, 0.5f, 0.5f);
        //cube2->RotatePitch(cube2->GetPosition(), 3.0f);

        sphere->Move(-2.0f, 1.0f, 2.0f);

        _scene->InsertCamera("camera", camera2);
        _scene->InsertLight("light", light);
        _scene->InsertNode("root", node);

        _scene->SetActiveCamera(camera2);
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
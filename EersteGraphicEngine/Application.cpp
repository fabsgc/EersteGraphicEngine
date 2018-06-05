#include "Application.h"

#include "DirectionalLight.h"
#include "FlyingCamera.h"
#include "AmbientLight.h"
#include "Sphere.h"
#include "Plane.h"
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
        _scene                       = ege_shared_ptr_new<Scene>();

        SPtr<Node> node              = ege_shared_ptr_new<Node>();
        SPtr<FlyingCamera> camera    = ege_shared_ptr_new<FlyingCamera>();
        SPtr<DirectionalLight> light = ege_shared_ptr_new<DirectionalLight>();
        SPtr<Sphere> sphere          = ege_shared_ptr_new<Sphere>();
        SPtr<Plane> plane            = ege_shared_ptr_new<Plane>();
        SPtr<AmbientLight> ambient   = ege_shared_ptr_new<AmbientLight>();

        _scene->Initialise();
        camera->Initialise();
        light->Initialise();
        sphere->Initialise();
        plane->Initialise();

        light->SetColor(XMFLOAT4(1.0f, 1.0, 1.0f, 0.8f));
        light->SetDirection(XMFLOAT3(0.5f, -0.5f, 0.5f));

        ambient->SetColor(XMFLOAT4(0.95f, 0.9f, 0.54f, 0.6f));

        node->SetScene(_scene);
        node->InsertEntity("camera", camera);
        node->InsertEntity("light", light);
        node->InsertEntity("sphere", sphere);
        node->InsertEntity("plane", plane);

        _scene->InsertCamera("camera", camera);
        _scene->InsertLight("light", light);
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
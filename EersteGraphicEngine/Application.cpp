#include "Application.h"

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
        _scene                    = ege_shared_ptr_new<Scene>();
        SPtr<Node> node           = ege_shared_ptr_new<Node>();
        SPtr<FlyingCamera> camera = ege_shared_ptr_new<FlyingCamera>();
        SPtr<PointLight> light    = ege_shared_ptr_new<PointLight>();
        SPtr<Cube> model          = ege_shared_ptr_new<Cube>();

        _scene->Initialise();
        camera->Initialise();
        light->Initialise();
        model->Initialise();

        node->SetScene(_scene);
        node->InsertEntity("camera", camera);
        node->InsertEntity("light", light);
        node->InsertEntity("model", model);

        _scene->InsertCamera("camera", camera);
        _scene->InsertLight("light", light);
        _scene->InsertNode("root", node);

        _scene->SetActiveCamera(camera);
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
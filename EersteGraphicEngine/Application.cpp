#include "Application.h"

#include "OrthographicCamera.h"
#include "ThirdPersonCamera.h"
#include "DirectionalLight.h"
#include "EventManager.h"
#include "AmbientLight.h"
#include "Node.h"

#include "CityModel.h"

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
        SPtr<CityModel> wind = ege_shared_ptr_new<CityModel>("wind-turbine", "wind-turbine-diffuse", "wind-turbine-specular");

        _scene->Initialise();
        camera->Initialise();
        ambient->Initialise();
        sun->Initialise();
        wind->Initialise();

        wind->RotatePitch(XM_PIDIV4);

        ambient->SetColor(XMFLOAT4(1.0f, 1.0f, 0.95f, 0.5f));

        sun->SetColor(XMFLOAT4(0.95f, 0.90f, 0.6f, 0.85f));
        sun->SetDirection(XMFLOAT3(-2.5f, -1.0f, 1.0f));

        node->SetScene(_scene);
        node->InsertEntity("camera", camera);
        node->InsertEntity("sun", sun);
        node->InsertEntity("wind", wind);

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
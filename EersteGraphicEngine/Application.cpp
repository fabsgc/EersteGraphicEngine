#include "Application.h"

#include "OrthographicCamera.h"
#include "ThirdPersonCamera.h"
#include "FirstPersonCamera.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "EventManager.h"
#include "AmbientLight.h"
#include "Node.h"

#include "CityModel.h"
#include "Player.h"

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
        _scene                         = ege_shared_ptr_new<Scene>();

        SPtr<Node> node                = ege_shared_ptr_new<Node>();
        SPtr<ThirdPersonCamera> camera = ege_shared_ptr_new<ThirdPersonCamera>();

        SPtr<AmbientLight> ambient     = ege_shared_ptr_new<AmbientLight>();
        SPtr<DirectionalLight> sun     = ege_shared_ptr_new<DirectionalLight>();
        SPtr<PointLight> lamp          = ege_shared_ptr_new<PointLight>();
        SPtr<SpotLight> spot           = ege_shared_ptr_new<SpotLight>();

        SPtr<Player> player            = ege_shared_ptr_new<Player>();

        SPtr<CityModel> wind           = ege_shared_ptr_new<CityModel>("wind-turbine", "wind-turbine-diffuse", "wind-turbine-specular");
        SPtr<CityModel> wind2          = ege_shared_ptr_new<CityModel>("wind-turbine", "wind-turbine-diffuse", "wind-turbine-specular");
        SPtr<CityModel> building       = ege_shared_ptr_new<CityModel>("building-1", "building-1-diffuse", "building-1-specular");

        sun->SetDrawLightModel(true);
        lamp->SetDrawLightModel(true);
        spot->SetDrawLightModel(true);

        _scene->Initialise();

        camera->Initialise();
        ambient->Initialise();
        sun->Initialise();
        lamp->Initialise();

        player->Initialise();

        wind->Initialise();
        wind2->Initialise();
        building->Initialise();
        wind->RotatePitch(XM_PIDIV4);
        wind2->RotatePitch(XM_PIDIV4);
        building->RotatePitch(XM_PI);

        wind->GoTo(5.0f, 0.0, 0.0f);
        wind2->GoTo(25.0f, 0.0, 5.0f);
        building->GoTo(-30.0f, 0.0, 20.0f);

        player->GoTo(12.0f, 1.0f, 0.0f);
        player->AttachCamera(camera);

        ambient->SetColor(XMFLOAT4(1.0f, 1.0f, 0.95f, 0.3f));
        sun->SetColor(XMFLOAT4(0.95f, 0.90f, 0.8f, 0.4f));
        sun->SetDirection(XMFLOAT3(-2.5f, -1.0f, -1.0f));

        lamp->SetColor(XMFLOAT4(0.95f, 0.90f, 0.8f, 1.0f));
        lamp->Move(XMFLOAT3(0.0f, -4.0f, 0.0f));
        lamp->SetRadius(40.0f);

        spot->SetColor(XMFLOAT4(0.95f, 0.90f, 0.6f, 1.0f));
        spot->SetDirection(XMFLOAT3(1.0f, -1.0f, 0.0f));
        spot->SetRadius(35.0f);

        node->SetScene(_scene);
        node->InsertEntity("camera", camera);
        node->InsertEntity("sun", sun);
        node->InsertEntity("lamp", lamp);
        node->InsertEntity("spot", spot);
        node->InsertEntity("wind", wind);
        node->InsertEntity("wind-2", wind2);
        node->InsertEntity("building", building);
        node->InsertEntity("player", player);

        for (INT8 i = -3; i <= 3; i++)
        {
            for (INT8 j = -3; j <= 3; j++)
            {
                SPtr<CityModel> model = ege_shared_ptr_new<CityModel>("grass", "grass-diffuse", "grass-specular");
                model->Initialise();
                model->GoTo(i * 20.0f, 0.0f, j * 20.0f);
                node->InsertEntity("grass-" + ToString(i) + "-" + ToString(j), model);
            }
        }

        //_scene->InsertCamera("camera", camera);
        _scene->InsertLight("sun", sun);
        _scene->InsertLight("lamp", lamp);
        _scene->InsertLight("spot", spot);
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
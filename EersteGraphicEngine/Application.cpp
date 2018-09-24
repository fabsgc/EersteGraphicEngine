#include "Application.h"

#include "ThirdPersonCamera.h"
#include "DirectionalLight.h"
#include "EventManager.h"
#include "AmbientLight.h"
#include "Player.h"
#include "Node.h"

#include "Plane.h"
#include "Cube.h"
#include "Sphere.h"

#include "MaterialManager.h"
#include "PlaneMaterial.h"
#include "CubeMaterial.h"

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
	}

	void Application::OnShutDown()
	{
		CoreApplication::OnShutDown();
	}

	void Application::SceneLoader()
	{
		_scene = ege_shared_ptr_new<Scene>();

		// ################ CREATE NODES
		//SPtr<Node> node                = ege_shared_ptr_new<Node>();
		SPtr<ThirdPersonCamera> camera = ege_shared_ptr_new<ThirdPersonCamera>();
		//SPtr<Player> player            = ege_shared_ptr_new<Player>();
		SPtr<AmbientLight> ambient     = ege_shared_ptr_new<AmbientLight>();
		SPtr<DirectionalLight> sun     = ege_shared_ptr_new<DirectionalLight>();
		
		// ################ SPECIFY IF WE CAST LIGHTS
		sun->SetDrawLightModel(true);
		
		// ################ INITIALISE SCENE
		_scene->Initialise();

		// ################ INITIALISE NODES
		camera->Initialise();
		//player->Initialise();
		ambient->Initialise();
		sun->Initialise();

		// ################ CHANGE ATTRIBUTES FOR EACH NODE
		//player->GoTo(0.0f, 1.0f, 0.0f);

		ambient->SetColor(XMFLOAT4(1.0f, 1.0f, 0.95f, 0.3f));
		sun->SetColor(XMFLOAT4(0.95f, 0.90f, 0.8f, 0.4f));
		sun->SetDirection(XMFLOAT3(-2.5f, -1.0f, -1.0f));

		// ################ INSERT NODES
		//node->SetScene(_scene);
		//node->InsertNode("camera", camera);
		//node->InsertNode("player", player);
		//node->InsertNode("sun", sun);

		// ################ LOAD MATERIALS

		SPtr<PlaneMaterial> planeMaterial = ege_shared_ptr_new<PlaneMaterial>();
		planeMaterial->Initialise();

		SPtr<CubeMaterial> cubeMaterial = ege_shared_ptr_new<CubeMaterial>();
		cubeMaterial->Initialise();

		gMaterialManager().Insert("plane", planeMaterial);
		gMaterialManager().Insert("cube", cubeMaterial);

		/*SPtr<Sphere> sphere = ege_shared_ptr_new<Sphere>();
		sphere->Initialise();
		sphere->SetMaterial(gMaterialManager().GetPtr("cube"));
		_scene->InsertModel("sphere", sphere);
		*/

		SPtr<Plane> grass = ege_shared_ptr_new<Plane>();
		grass->Initialise();
		grass->SetMaterial(gMaterialManager().GetPtr("plane"));
		grass->SetStatic(true);

		for (INT8 i = -4; i <= 5; i++)
		{
			for (INT8 j = -4; j <= 5; j++)
			{
				grass->GoTo(i * 5.0f, 0.0f, j * 5.0f);
				grass->AddObject(grass);
			}
		}

		_scene->InsertModel("grass", grass);
		
		SPtr<Cube> cube = ege_shared_ptr_new<Cube>();
		cube->Initialise();
		cube->SetMaterial(gMaterialManager().GetPtr("cube"));
		cube->SetStatic(true);

		for (INT8 i = -4; i <= 5; i++)
		{
			for (INT8 j = -4; j <= 5; j++)
			{
				cube->GoTo(i * 5.0f, 1.0f, j * 5.0f);
				cube->AddObject(cube);
			}
		}

		_scene->InsertModel("cube-", cube);

		_scene->InsertCamera("camera", camera);
		_scene->InsertLight("sun", sun);
		//_scene->InsertNode("root", node);

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
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
#include "Road1.h"
#include "Road2.h"
#include "Road3.h"
#include "Road4.h"
#include "Road5.h"
#include "Road6.h"
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
        SPtr<FlyingCamera> camera = ege_shared_ptr_new<FlyingCamera>();
        SPtr<AmbientLight> ambient     = ege_shared_ptr_new<AmbientLight>();
        SPtr<DirectionalLight> sun     = ege_shared_ptr_new<DirectionalLight>();

        SPtr<Building3> building11 = ege_shared_ptr_new<Building3>();
        SPtr<Building2> building21 = ege_shared_ptr_new<Building2>();
        SPtr<Building3> building41 = ege_shared_ptr_new<Building3>();
        SPtr<Building1> building51 = ege_shared_ptr_new<Building1>();
        SPtr<Building2> building61 = ege_shared_ptr_new<Building2>();
        SPtr<Building3> building81 = ege_shared_ptr_new<Building3>();
        SPtr<Building2> building91 = ege_shared_ptr_new<Building2>();

        SPtr<Building2> building12 = ege_shared_ptr_new<Building2>();
        SPtr<Building3> building22 = ege_shared_ptr_new<Building3>();
        SPtr<Building2> building42 = ege_shared_ptr_new<Building2>();
        SPtr<Building1> building52 = ege_shared_ptr_new<Building1>();
        SPtr<Building3> building62 = ege_shared_ptr_new<Building3>();
        SPtr<Building2> building82 = ege_shared_ptr_new<Building2>();
        SPtr<Building3> building92 = ege_shared_ptr_new<Building3>();

        SPtr<Building3> building04 = ege_shared_ptr_new<Building3>();
        SPtr<Building2> building14 = ege_shared_ptr_new<Building2>();
        SPtr<Building3> building74 = ege_shared_ptr_new<Building3>();
        SPtr<Building2> building84 = ege_shared_ptr_new<Building2>();

        SPtr<Building2> building05 = ege_shared_ptr_new<Building2>();
        SPtr<Building3> building15 = ege_shared_ptr_new<Building3>();
        SPtr<Building2> building75 = ege_shared_ptr_new<Building2>();
        SPtr<Building3> building85 = ege_shared_ptr_new<Building3>();

        SPtr<Road1> road00 = ege_shared_ptr_new<Road1>();
        SPtr<Road4> road01 = ege_shared_ptr_new<Road4>();
        SPtr<Road4> road02 = ege_shared_ptr_new<Road4>();
        SPtr<Road1> road03 = ege_shared_ptr_new<Road1>();
        SPtr<Road4> road04 = ege_shared_ptr_new<Road4>();
        SPtr<Road4> road05 = ege_shared_ptr_new<Road4>();
        SPtr<Road4> road06 = ege_shared_ptr_new<Road4>();
        SPtr<Road1> road07 = ege_shared_ptr_new<Road1>();
        SPtr<Road4> road08 = ege_shared_ptr_new<Road4>();
        SPtr<Road4> road09 = ege_shared_ptr_new<Road4>();
        SPtr<Road1> road010 = ege_shared_ptr_new<Road1>();

        SPtr<Road4> road10 = ege_shared_ptr_new<Road4>();
        SPtr<Road6> road11 = ege_shared_ptr_new<Road6>();
        SPtr<Road6> road12 = ege_shared_ptr_new<Road6>();
        SPtr<Road4> road13 = ege_shared_ptr_new<Road4>();
        SPtr<Road6> road14 = ege_shared_ptr_new<Road6>();
        SPtr<Road6> road15 = ege_shared_ptr_new<Road6>();
        SPtr<Road6> road16 = ege_shared_ptr_new<Road6>();
        SPtr<Road4> road17 = ege_shared_ptr_new<Road4>();
        SPtr<Road6> road18 = ege_shared_ptr_new<Road6>();
        SPtr<Road6> road19 = ege_shared_ptr_new<Road6>();
        SPtr<Road4> road110 = ege_shared_ptr_new<Road4>();

        SPtr<Road4> road20 = ege_shared_ptr_new<Road4>();
        SPtr<Road6> road21 = ege_shared_ptr_new<Road6>();
        SPtr<Road6> road22 = ege_shared_ptr_new<Road6>();
        SPtr<Road4> road23 = ege_shared_ptr_new<Road4>();
        SPtr<Road6> road24 = ege_shared_ptr_new<Road6>();
        SPtr<Road6> road25 = ege_shared_ptr_new<Road6>();
        SPtr<Road6> road26 = ege_shared_ptr_new<Road6>();
        SPtr<Road4> road27 = ege_shared_ptr_new<Road4>();
        SPtr<Road6> road28 = ege_shared_ptr_new<Road6>();
        SPtr<Road6> road29 = ege_shared_ptr_new<Road6>();
        SPtr<Road4> road210 = ege_shared_ptr_new<Road4>();

        SPtr<Road1> road30 = ege_shared_ptr_new<Road1>();
        SPtr<Road4> road31 = ege_shared_ptr_new<Road4>();
        SPtr<Road4> road32 = ege_shared_ptr_new<Road4>();
        SPtr<Road1> road33 = ege_shared_ptr_new<Road1>();
        SPtr<Road4> road34 = ege_shared_ptr_new<Road4>();
        SPtr<Road4> road35 = ege_shared_ptr_new<Road4>();
        SPtr<Road4> road36 = ege_shared_ptr_new<Road4>();
        SPtr<Road1> road37 = ege_shared_ptr_new<Road1>();
        SPtr<Road4> road38 = ege_shared_ptr_new<Road4>();
        SPtr<Road4> road39 = ege_shared_ptr_new<Road4>();
        SPtr<Road1> road310 = ege_shared_ptr_new<Road1>();

        SPtr<Road4> road40 = ege_shared_ptr_new<Road4>();
        SPtr<Road6> road41 = ege_shared_ptr_new<Road6>();
        SPtr<Road6> road42 = ege_shared_ptr_new<Road6>();
        SPtr<Road4> road43 = ege_shared_ptr_new<Road4>();
        SPtr<Road4> road47 = ege_shared_ptr_new<Road4>();
        SPtr<Road6> road48 = ege_shared_ptr_new<Road6>();
        SPtr<Road6> road49 = ege_shared_ptr_new<Road6>();
        SPtr<Road4> road410 = ege_shared_ptr_new<Road4>();

        SPtr<Road4> road50 = ege_shared_ptr_new<Road4>();
        SPtr<Road6> road51 = ege_shared_ptr_new<Road6>();
        SPtr<Road6> road52 = ege_shared_ptr_new<Road6>();
        SPtr<Road4> road53 = ege_shared_ptr_new<Road4>();
        SPtr<Road4> road57 = ege_shared_ptr_new<Road4>();
        SPtr<Road6> road58 = ege_shared_ptr_new<Road6>();
        SPtr<Road6> road59 = ege_shared_ptr_new<Road6>();
        SPtr<Road4> road510 = ege_shared_ptr_new<Road4>();

        SPtr<Road1> road60 = ege_shared_ptr_new<Road1>();
        SPtr<Road4> road61 = ege_shared_ptr_new<Road4>();
        SPtr<Road4> road62 = ege_shared_ptr_new<Road4>();
        SPtr<Road1> road63 = ege_shared_ptr_new<Road1>();
        SPtr<Road4> road64 = ege_shared_ptr_new<Road4>();
        SPtr<Road4> road65 = ege_shared_ptr_new<Road4>();
        SPtr<Road4> road66 = ege_shared_ptr_new<Road4>();
        SPtr<Road1> road67 = ege_shared_ptr_new<Road1>();
        SPtr<Road4> road68 = ege_shared_ptr_new<Road4>();
        SPtr<Road4> road69 = ege_shared_ptr_new<Road4>();
        SPtr<Road1> road610 = ege_shared_ptr_new<Road1>();

        SPtr<Grass> grass44 = ege_shared_ptr_new<Grass>();
        SPtr<Grass> grass45 = ege_shared_ptr_new<Grass>();
        SPtr<Grass> grass46 = ege_shared_ptr_new<Grass>();
        SPtr<Grass> grass54 = ege_shared_ptr_new<Grass>();
        SPtr<Grass> grass55 = ege_shared_ptr_new<Grass>();
        SPtr<Grass> grass56 = ege_shared_ptr_new<Grass>();

        _scene->Initialise();
        camera->Initialise();
        ambient->Initialise();
        sun->Initialise();

        building11->Initialise();
        building21->Initialise();
        building41->Initialise();
        building51->Initialise();
        building61->Initialise();
        building81->Initialise();
        building91->Initialise();

        building12->Initialise();
        building22->Initialise();
        building42->Initialise();
        building52->Initialise();
        building62->Initialise();
        building82->Initialise();
        building92->Initialise();

        building04->Initialise();
        building14->Initialise();
        building74->Initialise();
        building84->Initialise();

        building05->Initialise();
        building15->Initialise();
        building75->Initialise();
        building85->Initialise();

        road00->Initialise();
        road01->Initialise();
        road02->Initialise();
        road03->Initialise();
        road04->Initialise();
        road05->Initialise();
        road06->Initialise();
        road07->Initialise();
        road08->Initialise();
        road09->Initialise();
        road010->Initialise();

        road10->Initialise();
        road11->Initialise();
        road12->Initialise();
        road13->Initialise();
        road14->Initialise();
        road15->Initialise();
        road16->Initialise();
        road17->Initialise();
        road18->Initialise();
        road19->Initialise();
        road110->Initialise();

        road20->Initialise();
        road21->Initialise();
        road22->Initialise();
        road23->Initialise();
        road24->Initialise();
        road25->Initialise();
        road26->Initialise();
        road27->Initialise();
        road28->Initialise();
        road29->Initialise();
        road210->Initialise();

        road30->Initialise();
        road31->Initialise();
        road32->Initialise();
        road33->Initialise();
        road34->Initialise();
        road35->Initialise();
        road36->Initialise();
        road37->Initialise();
        road38->Initialise();
        road39->Initialise();
        road310->Initialise();

        road40->Initialise();
        road41->Initialise();
        road42->Initialise();
        road43->Initialise();
        road47->Initialise();
        road48->Initialise();
        road49->Initialise();
        road410->Initialise();

        road50->Initialise();
        road51->Initialise();
        road52->Initialise();
        road53->Initialise();
        road57->Initialise();
        road58->Initialise();
        road59->Initialise();
        road510->Initialise();

        road60->Initialise();
        road61->Initialise();
        road62->Initialise();
        road63->Initialise();
        road64->Initialise();
        road65->Initialise();
        road66->Initialise();
        road67->Initialise();
        road68->Initialise();
        road69->Initialise();
        road610->Initialise();

        grass44->Initialise();
        grass45->Initialise();
        grass46->Initialise();

        grass54->Initialise();
        grass55->Initialise();
        grass56->Initialise();

        building11->RotatePitch(0.0f);
        building21->RotatePitch(0.0f);
        building41->RotatePitch(0.0f);
        building51->RotatePitch(0.0f);
        building61->RotatePitch(0.0f);
        building81->RotatePitch(0.0f);
        building91->RotatePitch(0.0f);

        building12->RotatePitch(XM_PI);
        building22->RotatePitch(XM_PI);
        building42->RotatePitch(XM_PI);
        building52->RotatePitch(XM_PI);
        building62->RotatePitch(XM_PI);
        building82->RotatePitch(XM_PI);
        building92->RotatePitch(XM_PI);

        building04->RotatePitch(0.0f);
        building14->RotatePitch(0.0f);
        building74->RotatePitch(0.0f);
        building84->RotatePitch(0.0f);

        building05->RotatePitch(XM_PI);
        building15->RotatePitch(XM_PI);
        building75->RotatePitch(XM_PI);
        building85->RotatePitch(XM_PI);

        road00->RotatePitch(0.0f);
        road01->RotatePitch(XM_PIDIV2);
        road02->RotatePitch(XM_PIDIV2);
        road03->RotatePitch(0.0f);
        road04->RotatePitch(XM_PIDIV2);
        road05->RotatePitch(XM_PIDIV2);
        road06->RotatePitch(XM_PIDIV2);
        road07->RotatePitch(0.0f);
        road08->RotatePitch(XM_PIDIV2);
        road09->RotatePitch(XM_PIDIV2);
        road010->RotatePitch(0.0f);

        road10->RotatePitch(0.0f);
        road11->RotatePitch(0.0f);
        road12->RotatePitch(0.0f);
        road13->RotatePitch(0.0f);
        road14->RotatePitch(0.0f);
        road15->RotatePitch(0.0f);
        road16->RotatePitch(0.0f);
        road17->RotatePitch(0.0f);
        road18->RotatePitch(0.0f);
        road19->RotatePitch(0.0f);
        road110->RotatePitch(0.0f);

        road20->RotatePitch(0.0f);
        road21->RotatePitch(0.0f);
        road22->RotatePitch(0.0f);
        road23->RotatePitch(0.0f);
        road24->RotatePitch(0.0f);
        road25->RotatePitch(0.0f);
        road26->RotatePitch(0.0f);
        road27->RotatePitch(0.0f);
        road28->RotatePitch(0.0f);
        road29->RotatePitch(0.0f);
        road210->RotatePitch(0.0f);

        road30->RotatePitch(0.0f);
        road31->RotatePitch(XM_PIDIV2);
        road32->RotatePitch(XM_PIDIV2);
        road33->RotatePitch(0.0f);
        road34->RotatePitch(XM_PIDIV2);
        road35->RotatePitch(XM_PIDIV2);
        road36->RotatePitch(XM_PIDIV2);
        road37->RotatePitch(0.0f);
        road38->RotatePitch(XM_PIDIV2);
        road39->RotatePitch(XM_PIDIV2);
        road310->RotatePitch(0.0f);

        road40->RotatePitch(0.0f);
        road41->RotatePitch(0.0f);
        road42->RotatePitch(0.0f);
        road43->RotatePitch(0.0f);
        road47->RotatePitch(0.0f);
        road48->RotatePitch(0.0f);
        road49->RotatePitch(0.0f);
        road410->RotatePitch(0.0f);

        road50->RotatePitch(0.0f);
        road51->RotatePitch(0.0f);
        road52->RotatePitch(0.0f);
        road53->RotatePitch(0.0f);
        road57->RotatePitch(0.0f);
        road58->RotatePitch(0.0f);
        road59->RotatePitch(0.0f);
        road510->RotatePitch(0.0f);

        road60->RotatePitch(0.0f);
        road61->RotatePitch(XM_PIDIV2);
        road62->RotatePitch(XM_PIDIV2);
        road63->RotatePitch(0.0f);
        road64->RotatePitch(XM_PIDIV2);
        road65->RotatePitch(XM_PIDIV2);
        road66->RotatePitch(XM_PIDIV2);
        road67->RotatePitch(0.0f);
        road68->RotatePitch(XM_PIDIV2);
        road69->RotatePitch(XM_PIDIV2);
        road610->RotatePitch(0.0f);

        building11->GoTo(XMFLOAT3(-80.0f, 0.0f, 40.0));
        building21->GoTo(XMFLOAT3(-60.0f, 0.0f, 40.0));
        building41->GoTo(XMFLOAT3(-20.0f, 0.0f, 40.0));
        building51->GoTo(XMFLOAT3(0.0f, 0.0f, 40.0));
        building61->GoTo(XMFLOAT3(20.0f, 0.0f, 40.0));
        building81->GoTo(XMFLOAT3(60.0f, 0.0f, 40.0));
        building91->GoTo(XMFLOAT3(80.0f, 0.0f, 40.0));

        building12->GoTo(XMFLOAT3(-80.0f, 0.0f, 20.0));
        building22->GoTo(XMFLOAT3(-60.0f, 0.0f, 20.0));
        building42->GoTo(XMFLOAT3(-20.0f, 0.0f, 20.0));
        building52->GoTo(XMFLOAT3(00.0f, 0.0f, 20.0));
        building62->GoTo(XMFLOAT3(20.0f, 0.0f, 20.0));
        building82->GoTo(XMFLOAT3(60.0f, 0.0f, 20.0));
        building92->GoTo(XMFLOAT3(80.0f, 0.0f, 20.0));

        building04->GoTo(XMFLOAT3(-80.0f, 0.0f, -20.0));
        building14->GoTo(XMFLOAT3(-60.0f, 0.0f, -20.0));
        building74->GoTo(XMFLOAT3(60.0f, 0.0f, -20.0));
        building84->GoTo(XMFLOAT3(80.0f, 0.0f, -20.0));

        building05->GoTo(XMFLOAT3(-80.0f, 0.0f, -40.0));
        building15->GoTo(XMFLOAT3(-60.0f, 0.0f, -40.0));
        building75->GoTo(XMFLOAT3(60.0f, 0.0f, -40.0));
        building85->GoTo(XMFLOAT3(80.0f, 0.0f, -40.0));

        road00->GoTo(XMFLOAT3(-100.0f, 0.0f, 60.0f));
        road01->GoTo(XMFLOAT3(-80.0f, 0.0f, 60.0f));
        road02->GoTo(XMFLOAT3(-60.0f, 0.0f, 60.0f));
        road03->GoTo(XMFLOAT3(-40.0f, 0.0f, 60.0f));
        road04->GoTo(XMFLOAT3(-20.0f, 0.0f, 60.0f));
        road05->GoTo(XMFLOAT3(0.0f, 0.0f, 60.0f));
        road06->GoTo(XMFLOAT3(20.0f, 0.0f, 60.0f));
        road07->GoTo(XMFLOAT3(40.0f, 0.0f, 60.0f));
        road08->GoTo(XMFLOAT3(60.0f, 0.0f, 60.0f));
        road09->GoTo(XMFLOAT3(80.0f, 0.0f, 60.0f));
        road010->GoTo(XMFLOAT3(100.0f, 0.0f, 60.0f));

        road10->GoTo(XMFLOAT3(-100.0f, 0.0f, 40.0f));
        road11->GoTo(XMFLOAT3(-80.0f, 0.0f, 40.0f));
        road12->GoTo(XMFLOAT3(-60.0f, 0.0f, 40.0f));
        road13->GoTo(XMFLOAT3(-40.0f, 0.0f, 40.0f));
        road14->GoTo(XMFLOAT3(-20.0f, 0.0f, 40.0f));
        road15->GoTo(XMFLOAT3(0.0f, 0.0f, 40.0f));
        road16->GoTo(XMFLOAT3(20.0f, 0.0f, 40.0f));
        road17->GoTo(XMFLOAT3(40.0f, 0.0f, 40.0f));
        road18->GoTo(XMFLOAT3(60.0f, 0.0f, 40.0f));
        road19->GoTo(XMFLOAT3(80.0f, 0.0f, 40.0f));
        road110->GoTo(XMFLOAT3(100.0f, 0.0f, 40.0f));

        road20->GoTo(XMFLOAT3(-100.0f, 0.0f, 20.0f));
        road21->GoTo(XMFLOAT3(-80.0f, 0.0f, 20.0f));
        road22->GoTo(XMFLOAT3(-60.0f, 0.0f, 20.0f));
        road23->GoTo(XMFLOAT3(-40.0f, 0.0f, 20.0f));
        road24->GoTo(XMFLOAT3(-20.0f, 0.0f, 20.0f));
        road25->GoTo(XMFLOAT3(0.0f, 0.0f, 20.0f));
        road26->GoTo(XMFLOAT3(20.0f, 0.0f, 20.0f));
        road27->GoTo(XMFLOAT3(40.0f, 0.0f, 20.0f));
        road28->GoTo(XMFLOAT3(60.0f, 0.0f, 20.0f));
        road29->GoTo(XMFLOAT3(80.0f, 0.0f, 20.0f));
        road210->GoTo(XMFLOAT3(100.0f, 0.0f, 20.0f));

        road30->GoTo(XMFLOAT3(-100.0f, 0.0f, 0.0f));
        road31->GoTo(XMFLOAT3(-80.0f, 0.0f, 0.0f));
        road32->GoTo(XMFLOAT3(-60.0f, 0.0f, 0.0f));
        road33->GoTo(XMFLOAT3(-40.0f, 0.0f, 0.0f));
        road34->GoTo(XMFLOAT3(-20.0f, 0.0f, 0.0f));
        road35->GoTo(XMFLOAT3(0.0f, 0.0f, 0.0f));
        road36->GoTo(XMFLOAT3(20.0f, 0.0f, 0.0f));
        road37->GoTo(XMFLOAT3(40.0f, 0.0f, 0.0f));
        road38->GoTo(XMFLOAT3(60.0f, 0.0f, 0.0f));
        road39->GoTo(XMFLOAT3(80.0f, 0.0f, 0.0f));
        road310->GoTo(XMFLOAT3(100.0f, 0.0f, 0.0f));

        road40->GoTo(XMFLOAT3(-100.0f, 0.0f, -20.0f));
        road41->GoTo(XMFLOAT3(-80.0f, 0.0f, -20.0f));
        road42->GoTo(XMFLOAT3(-60.0f, 0.0f, -20.0f));
        road43->GoTo(XMFLOAT3(-40.0f, 0.0f, -20.0f));
        road47->GoTo(XMFLOAT3(40.0f, 0.0f, -20.0f));
        road48->GoTo(XMFLOAT3(60.0f, 0.0f, -20.0f));
        road49->GoTo(XMFLOAT3(80.0f, 0.0f, -20.0f));
        road410->GoTo(XMFLOAT3(100.0f, 0.0f, -20.0f));

        road50->GoTo(XMFLOAT3(-100.0f, 0.0f, -40.0f));
        road51->GoTo(XMFLOAT3(-80.0f, 0.0f, -40.0f));
        road52->GoTo(XMFLOAT3(-60.0f, 0.0f, -40.0f));
        road53->GoTo(XMFLOAT3(-40.0f, 0.0f, -40.0f));
        road57->GoTo(XMFLOAT3(40.0f, 0.0f, -40.0f));
        road58->GoTo(XMFLOAT3(60.0f, 0.0f, -40.0f));
        road59->GoTo(XMFLOAT3(80.0f, 0.0f, -40.0f));
        road510->GoTo(XMFLOAT3(100.0f, 0.0f, -40.0f));

        road60->GoTo(XMFLOAT3(-100.0f, 0.0f, -60.0f));
        road61->GoTo(XMFLOAT3(-80.0f, 0.0f, -60.0f));
        road62->GoTo(XMFLOAT3(-60.0f, 0.0f, -60.0f));
        road63->GoTo(XMFLOAT3(-40.0f, 0.0f, -60.0f));
        road64->GoTo(XMFLOAT3(-20.0f, 0.0f, -60.0f));
        road65->GoTo(XMFLOAT3(0.0f, 0.0f, -60.0f));
        road66->GoTo(XMFLOAT3(20.0f, 0.0f, -60.0f));
        road67->GoTo(XMFLOAT3(40.0f, 0.0f, -60.0f));
        road68->GoTo(XMFLOAT3(60.0f, 0.0f, -60.0f));
        road69->GoTo(XMFLOAT3(80.0f, 0.0f, -60.0f));
        road610->GoTo(XMFLOAT3(100.0f, 0.0f, -60.0f));

        grass44->GoTo(XMFLOAT3(-20.0f, 0.0f, -20.0f));
        grass45->GoTo(XMFLOAT3(0.0f, 0.0f, -20.0f));
        grass46->GoTo(XMFLOAT3(20.0f, 0.0f, -20.0f));

        grass54->GoTo(XMFLOAT3(-20.0f, 0.0f, -40.0f));
        grass55->GoTo(XMFLOAT3(0.0f, 0.0f, -40.0f));
        grass56->GoTo(XMFLOAT3(20.0f, 0.0f, -40.0f));

        ambient->SetColor(XMFLOAT4(1.0f, 1.0f, 0.95f, 0.7f));

        sun->SetColor(XMFLOAT4(0.95f, 0.90f, 0.6f, 0.8f));
        sun->SetDirection(XMFLOAT3(-0.5f, -1.0f, 1.0f));

        node->SetScene(_scene);
        node->InsertEntity("camera", camera);
        node->InsertEntity("sun", sun);
        
        node->InsertEntity("building11", building11);
        node->InsertEntity("building21", building21);
        node->InsertEntity("building41", building41);
        node->InsertEntity("building51", building51);
        node->InsertEntity("building61", building61);
        node->InsertEntity("building81", building81);
        node->InsertEntity("building91", building91);

        node->InsertEntity("building12", building12);
        node->InsertEntity("building22", building22);
        node->InsertEntity("building42", building42);
        node->InsertEntity("building52", building52);
        node->InsertEntity("building62", building62);
        node->InsertEntity("building82", building82);
        node->InsertEntity("building92", building92);

        node->InsertEntity("building04", building04);
        node->InsertEntity("building14", building14);
        node->InsertEntity("building74", building74);
        node->InsertEntity("building84", building84);

        node->InsertEntity("building05", building05);
        node->InsertEntity("building15", building15);
        node->InsertEntity("building75", building75);
        node->InsertEntity("building85", building85);

        node->InsertEntity("road00", road00);
        node->InsertEntity("road01", road01);
        node->InsertEntity("road02", road02);
        node->InsertEntity("road03", road03);
        node->InsertEntity("road04", road04);
        node->InsertEntity("road05", road05);
        node->InsertEntity("road06", road06);
        node->InsertEntity("road07", road07);
        node->InsertEntity("road08", road08);
        node->InsertEntity("road09", road09);
        node->InsertEntity("road010", road010);

        node->InsertEntity("road10", road10);
        node->InsertEntity("road11", road11);
        node->InsertEntity("road12", road12);
        node->InsertEntity("road13", road13);
        node->InsertEntity("road14", road14);
        node->InsertEntity("road15", road15);
        node->InsertEntity("road16", road16);
        node->InsertEntity("road17", road17);
        node->InsertEntity("road18", road18);
        node->InsertEntity("road19", road19);
        node->InsertEntity("road110", road110);

        node->InsertEntity("road20", road20);
        node->InsertEntity("road21", road21);
        node->InsertEntity("road22", road22);
        node->InsertEntity("road23", road23);
        node->InsertEntity("road24", road24);
        node->InsertEntity("road25", road25);
        node->InsertEntity("road26", road26);
        node->InsertEntity("road27", road27);
        node->InsertEntity("road28", road28);
        node->InsertEntity("road29", road29);
        node->InsertEntity("road210", road210);

        node->InsertEntity("road30", road30);
        node->InsertEntity("road31", road31);
        node->InsertEntity("road32", road32);
        node->InsertEntity("road33", road33);
        node->InsertEntity("road34", road34);
        node->InsertEntity("road35", road35);
        node->InsertEntity("road36", road36);
        node->InsertEntity("road37", road37);
        node->InsertEntity("road38", road38);
        node->InsertEntity("road39", road39);
        node->InsertEntity("road310", road310);

        node->InsertEntity("road40", road40);
        node->InsertEntity("road41", road41);
        node->InsertEntity("road42", road42);
        node->InsertEntity("road43", road43);
        node->InsertEntity("road47", road47);
        node->InsertEntity("road48", road48);
        node->InsertEntity("road49", road49);
        node->InsertEntity("road410", road410);

        node->InsertEntity("road50", road50);
        node->InsertEntity("road51", road51);
        node->InsertEntity("road52", road52);
        node->InsertEntity("road53", road53);
        node->InsertEntity("road57", road57);
        node->InsertEntity("road58", road58);
        node->InsertEntity("road59", road59);
        node->InsertEntity("road510", road510);

        node->InsertEntity("road60", road60);
        node->InsertEntity("road61", road61);
        node->InsertEntity("road62", road62);
        node->InsertEntity("road63", road63);
        node->InsertEntity("road64", road64);
        node->InsertEntity("road65", road65);
        node->InsertEntity("road66", road66);
        node->InsertEntity("road67", road67);
        node->InsertEntity("road68", road68);
        node->InsertEntity("road69", road69);
        node->InsertEntity("road610", road610);

        node->InsertEntity("road44", grass44);
        node->InsertEntity("road45", grass45);
        node->InsertEntity("road46", grass46);

        node->InsertEntity("grass54", grass54);
        node->InsertEntity("grass55", grass55);
        node->InsertEntity("grass56", grass56);

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
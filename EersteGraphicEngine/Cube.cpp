#include "Cube.h"

#include "ModelManager.h"
#include "DefaultMaterial.h"

#include "Keyboard.h"

namespace ege
{
    Cube::Cube()
        : Model()
    {
    }

    Cube::~Cube()
    {
    }

    void Cube::Initialise()
    {
        Build(gModelManager().GetPtr("cube"));

        SPtr<DefaultMaterial> material = ege_shared_ptr_new<DefaultMaterial>();
        material->Initialise();
        SetMaterial(material);
    }

    void Cube::Update()
    {
        Keyboard& keyboard = gKeyboard();

        RotatePitch(XMFLOAT3(1.0f, 0.0f, -1.0f), 0.01f);
        //Scale(XMFLOAT3(0.999f, 0.999f, 0.999f));
        //Scale(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.999f, 0.999f, 0.999f));
        //RotatePitch(XMFLOAT3(0.0f, 0.0f, 0.0f), 0.01f);
        //RotateRoll(GetPosition(), 0.01f);

        if (keyboard.GetKey("G").State == KeyState::TRIGGERED)
            MoveZ(0.05f);

        Model::Update();
    }
}
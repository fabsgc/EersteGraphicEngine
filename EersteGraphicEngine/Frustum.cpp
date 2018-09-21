#include "Frustum.h"
#include "Model.h"
#include "PerspectiveCamera.h"

namespace ege
{
    Frustum::Frustum()
    {
    }

    Frustum::~Frustum()
    {
    }

    void Frustum::Build(PerspectiveCamera* camera)
    {
        XMMATRIX matrix;
        XMFLOAT4X4 projection  = camera->GetProjection();
        const XMFLOAT4X4& view = camera->GetView();
        const float& farZ      = camera->GetFarZ();
        float zMinimum         = 0.0f;
        float r                = 0.0f;
        
        // Calculate the minimum Z distance in the frustum.
        zMinimum = -projection._43 / projection._33;
        r = farZ / (farZ - zMinimum);
        projection._33 = r;
        projection._43 = -r * zMinimum;

        // Create the frustum matrix from the view matrix and updated projection matrix.
        matrix = XMMatrixMultiply(XMLoadFloat4x4(&view), XMLoadFloat4x4(&projection));

        XMFLOAT4X4 matrixFloat;
        XMFLOAT4   planeFloat;

        XMStoreFloat4x4(&matrixFloat, matrix);

        // Calculate near plane of frustum.
        planeFloat.x = matrixFloat._13 + matrixFloat._14;
        planeFloat.y = matrixFloat._23 + matrixFloat._24;
        planeFloat.z = matrixFloat._33 + matrixFloat._34;
        planeFloat.w = matrixFloat._43 + matrixFloat._44;
        _planes[0] = XMVector3Normalize(XMLoadFloat4(&planeFloat));

        // Calculate far plane of frustum.
        planeFloat.x = matrixFloat._14 - matrixFloat._13;
        planeFloat.y = matrixFloat._24 - matrixFloat._23;
        planeFloat.z = matrixFloat._34 - matrixFloat._33;
        planeFloat.w = matrixFloat._44 - matrixFloat._43;
        _planes[1] = XMVector3Normalize(XMLoadFloat4(&planeFloat));

        // Calculate left plane of frustum.
        planeFloat.x = matrixFloat._14 + matrixFloat._11;
        planeFloat.y = matrixFloat._24 + matrixFloat._21;
        planeFloat.z = matrixFloat._34 + matrixFloat._31;
        planeFloat.w = matrixFloat._44 + matrixFloat._41;
        _planes[2] = XMVector3Normalize(XMLoadFloat4(&planeFloat));

        // Calculate right plane of frustum.
        planeFloat.x = matrixFloat._14 - matrixFloat._11;
        planeFloat.y = matrixFloat._24 - matrixFloat._21;
        planeFloat.z = matrixFloat._34 - matrixFloat._31;
        planeFloat.w = matrixFloat._44 - matrixFloat._41;
        _planes[3] = XMVector3Normalize(XMLoadFloat4(&planeFloat));

        // Calculate top plane of frustum.
        planeFloat.x = matrixFloat._14 - matrixFloat._12;
        planeFloat.y = matrixFloat._24 - matrixFloat._22;
        planeFloat.z = matrixFloat._34 - matrixFloat._32;
        planeFloat.w = matrixFloat._44 - matrixFloat._42;
        _planes[4] = XMVector3Normalize(XMLoadFloat4(&planeFloat));

        // Calculate bottom plane of frustum.
        planeFloat.x = matrixFloat._14 + matrixFloat._12;
        planeFloat.y = matrixFloat._24 + matrixFloat._22;
        planeFloat.z = matrixFloat._34 + matrixFloat._32;
        planeFloat.w = matrixFloat._44 + matrixFloat._42;
        _planes[5] = XMVector3Normalize(XMLoadFloat4(&planeFloat));
    }

    const bool Frustum::CheckSphere(PerspectiveCamera* camera, Model* model, const float radius) const
    {
        const XMFLOAT4X4 projection = camera->GetProjection();
        const XMFLOAT3& position    = model->GetPosition();
        const XMFLOAT4X4& view      = camera->GetView();

        // Check if the radius of the sphere is inside the view frustum.
        for (UINT8 i = 0; i<6; i++)
        {
            XMFLOAT4 positionVector;
            XMStoreFloat4(&positionVector, _planes[i]);

            float distance =
                positionVector.x * position.x +
                positionVector.y * position.y +
                positionVector.z * position.z + positionVector.w;

            if (distance + radius <= 0)
            {
                return false;
            }
        }

        return true;
    }

    const XMVECTOR* Frustum::GetPlanes() const
    {
        return _planes;
    }
}
#pragma once

#include "PrerequisitesCore.h"
#include "IComponentHandler.h"

namespace ege
{
    enum D3D11_ERROR_LEVEL
    {
        D3D11ERR_NO_EXCEPTION,
        D3D11ERR_CORRUPTION,
        D3D11ERR_ERROR,
        D3D11ERR_WARNING,
        D3D11ERR_INFO
    };

    class D3D11Device
    {
    public:
        D3D11Device(ID3D11Device* device);
        ~D3D11Device();

        /**	Shuts down the device any releases any internal resources. */
        void Shutdown();

        /**	Returns DX11 immediate context object. */
        ID3D11DeviceContext* GetImmediateContext() const { return _immediateContext; }

        /**	Returns DX11 class linkage object. */
        ID3D11ClassLinkage* GetClassLinkage() const { return _classLinkage; }

        /**	Returns internal DX11 device. */
        ID3D11Device* GetD3D11Device() const { return _D3D11Device; }

        /**	Resets error state & error messages. */
        void ClearErrors();

        /**
        * Query if error occurred at any point since last clearErrors() call. Use getErrorDescription to get a string
        * describing the error.
        */
        bool HasError() const;

        /**	Returns a string describing an error if one occurred. */
        String GetErrorDescription(bool clearErrors = true);

        /**
        * Sets the level for which we want to receive errors for. Errors will be reported for the provided level and any
        * higher priority level.
        */
        void SetExceptionsErrorLevel(const D3D11_ERROR_LEVEL exceptionsErrorLevel);

    private:
        D3D11Device();

    private:
        ID3D11Device* _D3D11Device;
        ID3D11DeviceContext* _immediateContext;
        ID3D11InfoQueue* _infoQueue;
        ID3D11ClassLinkage* _classLinkage;
    };
}
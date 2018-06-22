#pragma once

#include "PrerequisitesCore.h"

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

    class Device
    {
    public:
        Device(ID3D11Device* device);
        ~Device();

        /**	
         * \brief Shuts down the device any releases any internal resources. 
         */
        void Shutdown();

        /**	
         * \brief Returns DX11 immediate context object. 
         */
        ID3D11DeviceContext* GetImmediateContext() const { return _immediateContext; }

        /**	
         * \brief Returns DX11 class linkage object. 
         */
        ID3D11ClassLinkage* GetClassLinkage() const { return _classLinkage; }

        /**	
         * \brief Returns internal DX11 device. 
         */
        ID3D11Device* GetD3D11Device() const { return _D3D11Device; }

        /**	
         * \brief Resets error state & error messages. 
         */
        void ClearErrors();

        /**
         * \brief Query if error occurred at any point since last clearErrors() call. Use getErrorDescription to get 
                  a string describing the error.
        */
        bool HasError() const;

        /**	
         * \brief Returns a string describing an error if one occurred. 
         */
        String GetErrorDescription(bool clearErrors = true);

        /**
         * \brief Sets the level for which we want to receive errors for. Errors will be reported for the provided level and any
         *        higher priority level.
        */
        void SetExceptionsErrorLevel(const D3D11_ERROR_LEVEL exceptionsErrorLevel);

    protected:
        Device();

    protected:
        ID3D11Device* _D3D11Device;
        ID3D11DeviceContext* _immediateContext;
        ID3D11InfoQueue* _infoQueue;
        ID3D11ClassLinkage* _classLinkage;
    };
}
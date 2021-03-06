#include "Device.h"

#include "comdef.h"
#include <iostream>

namespace ege
{
    Device::Device()
        : _D3D11Device(nullptr)
        , _immediateContext(nullptr)
        , _classLinkage(nullptr)
    {}

    Device::Device(ID3D11Device* device)
        : _D3D11Device(device)
        , _immediateContext(nullptr)
        , _infoQueue(nullptr)
        , _classLinkage(nullptr)
    {
        EGE_ASSERT_ERROR_SHORT((device != nullptr));

        if (device)
        {
            device->GetImmediateContext(&_immediateContext);

#if defined(EGE_DEBUG) && defined(EGE_GRAPHIC_DEBUG) 
            // This interface is not available unless we created the device with debug layer
            HRESULT hr = _D3D11Device->QueryInterface(__uuidof(ID3D11InfoQueue), (LPVOID*)&_infoQueue);

            if (FAILED(hr))
            {
                EGE_ASSERT_ERROR(false, "Unable to query D3D11InfoQueue");
            }
#endif

            // If feature level is 11, create class linkage
            SafeReleaseCom(_classLinkage);

            if (_D3D11Device->GetFeatureLevel() == D3D_FEATURE_LEVEL_11_0)
            {
                HRESULT hr = _D3D11Device->CreateClassLinkage(&_classLinkage);

                if (FAILED(hr))
                {
                    EGE_ASSERT_ERROR(false, "Unable to create class linkage.");
                }
            }
        }
    }

    Device::~Device()
    {
        Shutdown();
    }

    void Device::Shutdown()
    {
		//We check potentially memory leaks at shutdown

		ID3D11Debug* debugDevice = nullptr;
		HRESULT result = _D3D11Device->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&debugDevice));

		if (FAILED(result))
		{
			_com_error err(result);
			LPCTSTR errMsg = err.ErrorMessage();
			::std::cout << errMsg << ::std::endl;
		}

		result = debugDevice->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);

		if (FAILED(result))
		{
			_com_error err(result);
			LPCTSTR errMsg = err.ErrorMessage();
			::std::cout << errMsg << ::std::endl;
		}

		SafeReleaseCom(debugDevice);

        if (_immediateContext)
        {
            _immediateContext->Flush();
            _immediateContext->ClearState();
        }

        SafeReleaseCom(_infoQueue);
        SafeReleaseCom(_D3D11Device);
        SafeReleaseCom(_immediateContext);
        SafeReleaseCom(_classLinkage);
    }

    String Device::GetErrorDescription(bool doClearErrors)
    {
        if (_D3D11Device == nullptr)
            return "Null device.";

        String res;

        if (_infoQueue != nullptr)
        {
            UINT64 numStoredMessages = _infoQueue->GetNumStoredMessagesAllowedByRetrievalFilter();
            for (UINT64 i = 0; i < numStoredMessages; i++)
            {
                // Get the size of the message
                SIZE_T messageLength = 0;
                _infoQueue->GetMessage(i, nullptr, &messageLength);
                // Allocate space and get the message
                D3D11_MESSAGE* pMessage = (D3D11_MESSAGE*)malloc(messageLength);
                _infoQueue->GetMessage(i, pMessage, &messageLength);
                res = res + pMessage->pDescription + "\n";
                free(pMessage);
            }
        }

        if (doClearErrors)
        {
            ClearErrors();
        }

        return res;
    }

    bool Device::HasError() const
    {
        if (_infoQueue != nullptr)
        {
            UINT64 numStoredMessages = _infoQueue->GetNumStoredMessagesAllowedByRetrievalFilter();

            if (numStoredMessages > 0)
            {
                return true;
            }

            return false;
        }
        else
        {
            return false;
        }
    }

    void Device::ClearErrors()
    {
        if (_D3D11Device != nullptr && _infoQueue != nullptr)
        {
            _infoQueue->ClearStoredMessages();
        }
    }

    void Device::SetExceptionsErrorLevel(const D3D11_ERROR_LEVEL exceptionsErrorLevel)
    {
        if (_infoQueue == nullptr)
        {
            return;
        }

        _infoQueue->ClearRetrievalFilter();
        _infoQueue->ClearStorageFilter();

        D3D11_INFO_QUEUE_FILTER filter;
        ZeroMemory(&filter, sizeof(D3D11_INFO_QUEUE_FILTER));
        Vector<D3D11_MESSAGE_SEVERITY> severityList;

        switch (exceptionsErrorLevel)
        {
            case D3D11ERR_INFO:
                severityList.push_back(D3D11_MESSAGE_SEVERITY_INFO);
            case D3D11ERR_WARNING:
                severityList.push_back(D3D11_MESSAGE_SEVERITY_WARNING);
            case D3D11ERR_ERROR:
                severityList.push_back(D3D11_MESSAGE_SEVERITY_ERROR);
            case D3D11ERR_CORRUPTION:
                severityList.push_back(D3D11_MESSAGE_SEVERITY_CORRUPTION);
            case D3D11ERR_NO_EXCEPTION:
            default:
                break;
        }

        if (severityList.size() > 0)
        {
            filter.AllowList.NumSeverities = (UINT)severityList.size();
            filter.AllowList.pSeverityList = &severityList[0];
        }

        _infoQueue->AddStorageFilterEntries(&filter);
        _infoQueue->AddRetrievalFilterEntries(&filter);
    }
}
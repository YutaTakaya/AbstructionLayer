#include "CommonResourceManager.h"
#include "D3D11ObjData.h"
#include "D3D12ObjData.h"
#include "OpenGLObjData.h"

int CommonResourceManager::Init(const HWND hWnd, const int width, const int height, const APIType type)
{
    FLOAT3 eye = { 0.0f,0.0f,-50.0f };
    FLOAT3 lookat = { 0.0f,0.0f,0.0f };
    FLOAT3 up = { 0.0f,1.0f,0.0f };

    switch (type)
    {
    case APIType::D3D11:
        D3D11Graphics::CreateInstance();
        D3D11Graphics::GetInstance().D3D11Init(hWnd, width, height);
        D3D11Camera::CreateInstance();
        D3D11Camera::GetInstance().CameraInit(eye, lookat, up);
        break;
    case APIType::D3D12:
        D3D12Graphics::CreateInstance();
        D3D12Graphics::GetInstance().D3D12Init(hWnd, width, height);
        D3D12Camera::CreateInstance();
        D3D12Camera::GetInstance().CameraInit(eye, lookat, up);
        m_render.D3D12RenderInit();
        break;
    case APIType::OPENGL:
        OpenGLGraphics::CreateInstance();
        OpenGLGraphics::GetInstance().OpenGLInit(hWnd, width, height);
        OpenGLCamera::CreateInstance();
        OpenGLCamera::GetInstance().CameraInit(eye, lookat, up);
        break;
    case APIType::VULKAN:
        break;
    default:
        break;
    }
    m_nowType = type;
    return 0;
}

CommonObjData* CommonResourceManager::CreateObject()
{
    switch (m_nowType)
    {
    case APIType::NONE:
        return nullptr;
        break;
    case APIType::D3D11:
        return new D3D11ObjData;
        break;
    case APIType::D3D12:
        return new D3D12ObjData;
        break;
    case APIType::OPENGL:
        return new OpenGLObjData;
        break;
    case APIType::VULKAN:
        return nullptr;
        break;
    default:
        return nullptr;
        break;
    }
}

int CommonResourceManager::BeforeRenderer()
{
    float color[4] = { 0.2f,0.2f,0.2f,1.0f };

    switch (m_nowType)
    {
    case APIType::NONE:
        break;
    case APIType::D3D11:
        D3D11Graphics::GetInstance().getDevContextPtr()->ClearRenderTargetView(
            D3D11Graphics::GetInstance().getBackBufferVierPtr(),
            color);
        D3D11Graphics::GetInstance().getDevContextPtr()->ClearDepthStencilView(
            D3D11Graphics::GetInstance().getDepthStencilVierPtr(),
            D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
            1.0f,
            0);
        break;

    case APIType::D3D12:
        D3D12Graphics::GetInstance().D3D12BeforeRender();
        m_render.D3D12RenderSet();
        break;
        
    case APIType::OPENGL:
        OpenGLGraphics::GetInstance().OpenGLBeforeRender();
        break;
    case APIType::VULKAN:
        break;
    default:
        break;
    }
    return 0;
}

int CommonResourceManager::AfterRenderer()
{
    switch (m_nowType)
    {
    case APIType::NONE:
        break;
    case APIType::D3D11:
        // バックバッファを表示
        D3D11Graphics::GetInstance().getSwapChainPtr()->Present(1, 0);
        break;
    case APIType::D3D12:
        D3D12Graphics::GetInstance().D3D12AfterRender();
        break;
    case APIType::OPENGL:
        OpenGLGraphics::GetInstance().OpenGLAfterRender();
        break;
    case APIType::VULKAN:
        break;
    default:
        break;
    }
    return 0;
}

void CommonResourceManager::CreateInstance()
{
    DeleteInstance();
    s_pInstance = new CommonResourceManager();
    s_pInstance->m_nowType = APIType::NONE;
}

void CommonResourceManager::DeleteInstance()
{
    if (s_pInstance != nullptr)
    {
        delete s_pInstance;
        s_pInstance = nullptr;
    }
}

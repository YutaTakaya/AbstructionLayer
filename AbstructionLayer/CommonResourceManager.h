//==============================================================================
// Filename: CommonResourceManager.h
// Description: 抽象化レイヤー用リソース管理クラス
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#pragma once
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")

#include <d3d11.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <wrl/client.h>
#include <dxgi1_6.h>
#include <vector>
#include <memory>

#include "D3D11Graphics.h"
#include "D3D12Graphics.h"
#include "D3D11Camera.h"
#include "D3D12Camera.h"
#include "D3D12Render.h"
#include "OpenGLGraphics.h"
#include "OpenGLCamera.h"

enum class APIType
{
    NONE,
    D3D11,
    D3D12,
    OPENGL,
    VULKAN
};

class CommonResourceManager
{
public:
    //---------------------------------------------------------------------------
    //---------------------------------------------
    /// 初期化関数
    ///
    /// \param[in] ( hWnd )         ウィンドウハンドル
    /// \param[in] ( width )        ウィンドウの幅
    /// \param[in] ( height )       ウィンドウの高さ
    /// \param[in] ( type )         APIの種類
    ///
    /// \return エラーの場合-1、正常に終了した場合0が返される
    //--------------------------------------------- 
    int Init(
        /*[in]*/	const HWND hWnd,
        /*[in]*/	const int width,
        /*[in]*/	const int height,
        /*[in]*/    const APIType type);

    //---------------------------------------------
    /// 描画前処理関数
    ///
    /// \return void
    //--------------------------------------------- 
    int BeforeRenderer();

    //---------------------------------------------
    /// 描画後処理関数
    ///
    /// \return void
    //--------------------------------------------- 
    int AfterRenderer();

    //---------------------------------------------------------------------------

    //---------------------------------------------
    /// インスタンスの作成
    //--------------------------------------------- 
    static void CreateInstance(APIType type);

    //---------------------------------------------
    /// インスタンスの削除
    //--------------------------------------------- 
    static void DeleteInstance();

    //---------------------------------------------
    /// インスタンスの取得
    /// 
    /// \return インスタンス
    //--------------------------------------------- 
    static CommonResourceManager& GetInstance()
    {
        return *s_pInstance;
    }

    //---------------------------------------------
    /// 使用APIの取得
    /// 
    /// \return APIの種類
    //--------------------------------------------- 
    APIType getAPIType()
    {
        return m_nowType;
    }
protected:

private:
    //---------------------------------------------------------------------------
    APIType m_nowType;
    static inline CommonResourceManager* s_pInstance;
    D3D12Render m_render;
    //---------------------------------------------------------------------------
    /// <summary>
    /// </summary>
};


//==============================================================================
// Filename: D3D12Graphics.h
// Description: DirectX12の描画システム
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#pragma once

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")

#include <d3d12.h>
#include <dxgi1_6.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <wrl/client.h>
#include <vector>
#include <memory>

using Microsoft::WRL::ComPtr;

class D3D12Graphics
{
public:
    //---------------------------------------------------------------------------
    //---------------------------------------------
    /// DirectX12の初期化関数
    ///
    /// \param[in] ( hWnd )         ウィンドウハンドル
    /// \param[in] ( width )        ウィンドウの幅
    /// \param[in] ( height )       ウィンドウの高さ
    ///
    /// \return エラーの場合-1、正常に終了した場合0が返される
    //--------------------------------------------- 
    int D3D12Init(
        /*[in]*/	const HWND hWnd,
        /*[in]*/	const int width,
        /*[in]*/	const int height);

    //---------------------------------------------
    /// DirectX12の描画事前処理
    ///
    /// \return エラーの場合-1、正常に終了した場合0が返される
    //--------------------------------------------- 
    int D3D12BeforeRender();

    //---------------------------------------------
    /// DirectX12の描画事後処理
    ///
    /// \return エラーの場合-1、正常に終了した場合0が返される
    //--------------------------------------------- 
    int D3D12AfterRender();

    //---------------------------------------------
    /// インスタンスの作成
    //--------------------------------------------- 
    static void CreateInstance();

    //---------------------------------------------
    /// インスタンスの削除
    //--------------------------------------------- 
    static void DeleteInstance();

    //---------------------------------------------
    /// インスタンスの取得
    /// 
    /// \return インスタンス
    //--------------------------------------------- 
    static D3D12Graphics& GetInstance()
    {
        return *s_pInstance;
    }

    //---------------------------------------------
    /// デバイスのポインタを取得する
    /// 
    /// \return デバイスのポインタ
    //--------------------------------------------- 
    ID3D12Device* getDevPtr()
    {
        return m_pDevice.Get();
    }

    //---------------------------------------------
    /// スワップチェインのポインタを取得する
    /// 
    /// \return スワップチェインのポインタ
    //--------------------------------------------- 
    IDXGISwapChain4* getSwapChainPtr()
    {
        return m_pSwapChain.Get();
    }

    //---------------------------------------------
    /// コマンドリストのポインタを取得する
    /// 
    /// \return コマンドリストのポインタ
    //--------------------------------------------- 
    ID3D12GraphicsCommandList* getCmdPtr()
    {
        return m_pCommandList.Get();
    }

    //---------------------------------------------
    /// コマンドキューのポインタを取得する
    /// 
    /// \return コマンドキューのポインタ
    //--------------------------------------------- 
    ID3D12CommandQueue* getQueuePtr()
    {
        return m_pCommandQueue.Get();
    }

    //---------------------------------------------
    /// RTVヒープのポインタを取得する
    /// 
    /// \return RTVヒープのポインタ
    //--------------------------------------------- 
    ID3D12DescriptorHeap* getRTVHeapPtr()
    {
        return m_pRtvHeaps.Get();
    }


    //---------------------------------------------
    /// コマンドアロケーターのポインタを取得する
    /// 
    /// \return コマンドアロケーターのポインタ
    //--------------------------------------------- 
    ID3D12CommandAllocator* getAllocatorPtr()
    {
        return m_pCommandAllocator.Get();
    }

    //---------------------------------------------
    /// フェンスのポインタを取得する
    /// 
    /// \return フェンスのポインタ
    //--------------------------------------------- 
    ID3D12Fence* getFencePtr()
    {
        return m_pFence.Get();
    }

    //---------------------------------------------------------------------------

protected:

private:
    //---------------------------------------------------------------------------
    ComPtr<ID3D12Device>    m_pDevice;
    ComPtr<IDXGISwapChain4>  m_pSwapChain;
    ComPtr<ID3D12GraphicsCommandList>   m_pCommandList;
    ComPtr<ID3D12CommandQueue>  m_pCommandQueue;
    ComPtr<ID3D12DescriptorHeap> m_pRtvHeaps;
    std::vector<ID3D12Resource*> m_pBackBuffers;
    ComPtr<ID3D12CommandAllocator>  m_pCommandAllocator;
    ComPtr<ID3D12Fence> m_pFence;
    UINT64 m_fenceVal = 0;
    D3D12_VIEWPORT m_pViewport = {};
    D3D12_RECT m_pScissorRect = {};
    ComPtr<ID3D12Resource>  m_pDepthBuffer;
    ComPtr<ID3D12DescriptorHeap> m_pDepthStencilViewHeap;

	static inline D3D12Graphics* s_pInstance;
	//---------------------------------------------------------------------------
	/// <summary>
	/// m_pDevice   D3D12デバイス
	/// m_pSwapChain    スワップチェイン
	/// m_pCommandList  コマンドリスト
	/// m_pCommandQueue コマンドキュー
	/// m_pRtvHeaps     レンダーターゲットビュー用ヒープ
	/// m_pBackBuffer   バックバッファ配列（フロントとバックの2つ）
	/// m_pCommandAllocator コマンドアロケーター
	/// m_pFence        フェンス
	/// m_fenceVal      フェンス値
	/// m_pViewport     ビューポート
	/// m_pScissorRect  シザー矩形
	/// 
	/// m_pDepthBuffer  深度バッファ
	/// m_pDepthStencilViewHeap 深度ステンシルビュー用ヒープ
	/// 
	/// s_pInstance インスタンス
	/// </summary>

    //---------------------------------------------------------------------------
    //---------------------------------------------
    /// コンストラクタ
    /// 
    /// シングルトンのためprivateにして呼び出せなくする
    //--------------------------------------------- 
    D3D12Graphics() {}
    //---------------------------------------------------------------------------
};

//==============================================================================
// Filename: CommonSystem.cpp
// Description: 抽象化レイヤーのサンプル処理
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#include "CommonSystem.h"
#include "D3D11ObjData.h"
#include "D3D12ObjData.h"
#include "OpenGLObjData.h"

CommonObjData* g_testObj;

int CommonInit()
{
    // 頂点データ
    VertexData v[] = {
        //////          座標           //////  /////        UV        //////  //////          カラー          //////
        // 前面
        {DirectX::XMFLOAT3(-3.0f, 3.0f,-3.0f), DirectX::XMFLOAT2(0.0f,0.0f), DirectX::XMFLOAT4(1.0f,1.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3(3.0f, 3.0f,-3.0f), DirectX::XMFLOAT2(1.0f,0.0f), DirectX::XMFLOAT4(1.0f,1.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3(-3.0f,-3.0f,-3.0f), DirectX::XMFLOAT2(0.0f,1.0f), DirectX::XMFLOAT4(1.0f,1.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3(3.0f,-3.0f,-3.0f), DirectX::XMFLOAT2(1.0f,1.0f), DirectX::XMFLOAT4(1.0f,1.0f,1.0f,1.0f)},

        // 左面
        {DirectX::XMFLOAT3(-3.0f, 3.0f, 3.0f), DirectX::XMFLOAT2(0.0f,0.0f), DirectX::XMFLOAT4(0.0f,1.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3(-3.0f, 3.0f,-3.0f), DirectX::XMFLOAT2(1.0f,0.0f), DirectX::XMFLOAT4(0.0f,1.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3(-3.0f,-3.0f, 3.0f), DirectX::XMFLOAT2(0.0f,1.0f), DirectX::XMFLOAT4(0.0f,1.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3(-3.0f,-3.0f,-3.0f), DirectX::XMFLOAT2(1.0f,1.0f), DirectX::XMFLOAT4(0.0f,1.0f,1.0f,1.0f)},

        // 右面
        {DirectX::XMFLOAT3(3.0f, 3.0f,-3.0f), DirectX::XMFLOAT2(0.0f,0.0f), DirectX::XMFLOAT4(1.0f,0.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3(3.0f, 3.0f, 3.0f), DirectX::XMFLOAT2(1.0f,0.0f), DirectX::XMFLOAT4(1.0f,0.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3(3.0f,-3.0f,-3.0f), DirectX::XMFLOAT2(0.0f,1.0f), DirectX::XMFLOAT4(1.0f,0.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3(3.0f,-3.0f, 3.0f), DirectX::XMFLOAT2(1.0f,1.0f), DirectX::XMFLOAT4(1.0f,0.0f,1.0f,1.0f)},

        // 後面
        {DirectX::XMFLOAT3(3.0f, 3.0f, 3.0f), DirectX::XMFLOAT2(0.0f,0.0f), DirectX::XMFLOAT4(1.0f,1.0f,0.0f,1.0f)},
        {DirectX::XMFLOAT3(-3.0f, 3.0f, 3.0f), DirectX::XMFLOAT2(1.0f,0.0f), DirectX::XMFLOAT4(1.0f,1.0f,0.0f,1.0f)},
        {DirectX::XMFLOAT3(3.0f,-3.0f, 3.0f), DirectX::XMFLOAT2(0.0f,1.0f), DirectX::XMFLOAT4(1.0f,1.0f,0.0f,1.0f)},
        {DirectX::XMFLOAT3(-3.0f,-3.0f, 3.0f), DirectX::XMFLOAT2(1.0f,1.0f), DirectX::XMFLOAT4(1.0f,1.0f,0.0f,1.0f)},

        // 上面
        {DirectX::XMFLOAT3(-3.0f, 3.0f, 3.0f), DirectX::XMFLOAT2(0.0f,0.0f), DirectX::XMFLOAT4(0.0f,1.0f,0.0f,1.0f)},
        {DirectX::XMFLOAT3(3.0f, 3.0f, 3.0f), DirectX::XMFLOAT2(1.0f,0.0f), DirectX::XMFLOAT4(0.0f,1.0f,0.0f,1.0f)},
        {DirectX::XMFLOAT3(-3.0f, 3.0f,-3.0f), DirectX::XMFLOAT2(0.0f,1.0f), DirectX::XMFLOAT4(0.0f,1.0f,0.0f,1.0f)},
        {DirectX::XMFLOAT3(3.0f, 3.0f,-3.0f), DirectX::XMFLOAT2(1.0f,1.0f), DirectX::XMFLOAT4(0.0f,1.0f,0.0f,1.0f)},

        // 下面
        {DirectX::XMFLOAT3(-3.0f,-3.0f,-3.0f), DirectX::XMFLOAT2(0.0f,0.0f), DirectX::XMFLOAT4(0.0f,0.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3(3.0f,-3.0f,-3.0f), DirectX::XMFLOAT2(1.0f,0.0f), DirectX::XMFLOAT4(0.0f,0.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3(-3.0f,-3.0f, 3.0f), DirectX::XMFLOAT2(0.0f,1.0f), DirectX::XMFLOAT4(0.0f,0.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3(3.0f,-3.0f, 3.0f), DirectX::XMFLOAT2(1.0f,1.0f), DirectX::XMFLOAT4(0.0f,0.0f,1.0f,1.0f)},
    };

    // インデックスデータ
    WORD index[] = {
        // 前面
        0,1,2,
        1,3,2,
        // 左面
        4,5,6,
        5,7,6,
        // 右面
        8,9,10,
        9,11,10,
        // 後面
        12,13,14,
        13,15,14,
        // 上面
        16,17,18,
        17,19,18,
        // 下面
        20,21,22,
        21,23,22,
    };

    // 使用API用の型にキャスト
    g_testObj = CommonResourceManager::GetInstance().CreateObject();

    // 頂点、インデックスデータの初期化
    if (g_testObj->ObjInit(
        v, sizeof(v) / sizeof(VertexData),
        index, sizeof(index) / sizeof(WORD)) == -1)
    {
        return -1;
    }
    return 0;
}

int CommonUpdate()
{
    // オブジェクト回転テスト
    g_testObj->ObjRotate(0.01f, 0.01f, 0.01f);

    // カメラ視点移動テスト
    static FLOAT3 eyeh = { 10.0f,-10.0f,-20.0f };
    eyeh.x += 0.02f;
    eyeh.y += 0.02f;
    eyeh.z += 0.02f;
    CommonCamera::GetInstance().SetEye(eyeh);
    CommonCamera::GetInstance().CameraUpdate();

    return 0;
}

int CommonDraw()
{
    CommonResourceManager::GetInstance().BeforeRenderer();

    // オブジェクトごとの描画処理はここに書く
    g_testObj->ObjDraw();
    
    CommonResourceManager::GetInstance().AfterRenderer();
    return 0;
}

int CommonUninit()
{
    delete g_testObj;
    return 0;
}

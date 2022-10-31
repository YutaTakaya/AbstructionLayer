//==============================================================================
// Filename: D3D12System.h
// Description: DirectX12単体でのサンプル処理
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================

#include "D3D12ObjData.h"

//---------------------------------------------
/// オブジェクトデータの初期化処理
///
/// \return 正常に終了した場合0が返される
//--------------------------------------------- 
int D3D12Init();

//---------------------------------------------
/// オブジェクトデータのアップデート処理
///
/// \return void
//--------------------------------------------- 
void D3D12Update();

//---------------------------------------------
/// DirectX12での描画処理
///
/// \return void
//--------------------------------------------- 
void D3D12Draw();

//---------------------------------------------
/// オブジェクトデータの解放処理
///
/// \return void
//--------------------------------------------- 
void D3D12Uninit();
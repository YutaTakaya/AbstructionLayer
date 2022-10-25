//==============================================================================
// Filename: OpenGLSystem.h
// Description: OpenGLの基本処理
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#pragma once

//---------------------------------------------
/// オブジェクトデータの初期化処理
///
/// \return 正常に終了した場合0が返される
//--------------------------------------------- 
int OpenGLInit();

//---------------------------------------------
/// オブジェクトデータのアップデート処理
///
/// \return void
//--------------------------------------------- 
void OpenGLUpdate();

//---------------------------------------------
/// OpenGLでの描画処理
///
/// \return void
//--------------------------------------------- 
void OpenGLDraw();

//---------------------------------------------
/// オブジェクトデータの解放処理
///
/// \return void
//--------------------------------------------- 
void OpenGLUninit();


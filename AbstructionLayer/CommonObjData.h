//==============================================================================
// Filename: CommonObjData.h
// Description: 抽象化レイヤー用共通オブジェクトデータ
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#pragma once
#include "D3D11ObjData.h"
#include "D3D12ObjData.h"

class CommonObjData
{
public:
    //---------------------------------------------------------------------------

    //---------------------------------------------------------------------------

protected:

private:
    //---------------------------------------------------------------------------
    XMMATRIX m_localMtx;
    XMFLOAT3 m_worldPos;
    //---------------------------------------------------------------------------
    /// <summary>
    /// m_localMtx          ローカルでの姿勢情報
    /// m_localPos          ローカル座標
    /// </summary>
};


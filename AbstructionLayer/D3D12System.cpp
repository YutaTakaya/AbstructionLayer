#include "D3D12System.h"
#include "D3D12Graphics.h"

int D3D12Init()
{
    return 0;
}

void D3D12Update()
{
}

// TODO : BeforeRenderとAfterRenderに分割してまとめる
void D3D12Render()
{
    // 描画先のバックバッファの番号を取得する
    auto bbIdx = D3D12Graphics::GetInstance().getSwapChainPtr()->GetCurrentBackBufferIndex();
    // RTVのポインタ取得
    auto rtvH = D3D12Graphics::GetInstance().getRTVHeapPtr()->GetCPUDescriptorHandleForHeapStart();
    rtvH.ptr += bbIdx * D3D12Graphics::GetInstance().getDevPtr()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

    float col[4] = { 1,1,0,1 };
    D3D12Graphics::GetInstance().getCmdPtr()->ClearRenderTargetView(rtvH, col, 0, nullptr);

    //   ここから処理を書く   //



    //  ここまでに処理を書く  //

    D3D12Graphics::GetInstance().getCmdPtr()->Close();

    // コマンドリストの実行
    ID3D12CommandList* cmdLists[] = { D3D12Graphics::GetInstance().getCmdPtr() };
    D3D12Graphics::GetInstance().getQueuePtr()->ExecuteCommandLists(1, cmdLists);

    // 待ち処理
    UINT64 fenceVal = 0;
    if (D3D12Graphics::GetInstance().getFencePtr()->GetCompletedValue() < fenceVal) {
        auto event = CreateEvent(nullptr, false, false, nullptr);
        D3D12Graphics::GetInstance().getFencePtr()->SetEventOnCompletion(fenceVal, event);
        WaitForSingleObject(event, INFINITE);
        CloseHandle(event);
    }

    // 初期化処理
    D3D12Graphics::GetInstance().getAllocatorPtr()->Reset();
    D3D12Graphics::GetInstance().getCmdPtr()->Reset(D3D12Graphics::GetInstance().getAllocatorPtr(), nullptr);
}

void D3D12Uninit()
{
}

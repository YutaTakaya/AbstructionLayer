#include "D3D12System.h"
#include "D3D12Graphics.h"

int D3D12Init()
{
    return 0;
}

void D3D12Update()
{
}

// TODO : BeforeRender��AfterRender�ɕ������Ă܂Ƃ߂�
void D3D12Render()
{
    // �`���̃o�b�N�o�b�t�@�̔ԍ����擾����
    auto bbIdx = D3D12Graphics::GetInstance().getSwapChainPtr()->GetCurrentBackBufferIndex();
    // RTV�̃|�C���^�擾
    auto rtvH = D3D12Graphics::GetInstance().getRTVHeapPtr()->GetCPUDescriptorHandleForHeapStart();
    rtvH.ptr += bbIdx * D3D12Graphics::GetInstance().getDevPtr()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

    float col[4] = { 1,1,0,1 };
    D3D12Graphics::GetInstance().getCmdPtr()->ClearRenderTargetView(rtvH, col, 0, nullptr);

    //   �������珈��������   //



    //  �����܂łɏ���������  //

    D3D12Graphics::GetInstance().getCmdPtr()->Close();

    // �R�}���h���X�g�̎��s
    ID3D12CommandList* cmdLists[] = { D3D12Graphics::GetInstance().getCmdPtr() };
    D3D12Graphics::GetInstance().getQueuePtr()->ExecuteCommandLists(1, cmdLists);

    // �҂�����
    UINT64 fenceVal = 0;
    if (D3D12Graphics::GetInstance().getFencePtr()->GetCompletedValue() < fenceVal) {
        auto event = CreateEvent(nullptr, false, false, nullptr);
        D3D12Graphics::GetInstance().getFencePtr()->SetEventOnCompletion(fenceVal, event);
        WaitForSingleObject(event, INFINITE);
        CloseHandle(event);
    }

    // ����������
    D3D12Graphics::GetInstance().getAllocatorPtr()->Reset();
    D3D12Graphics::GetInstance().getCmdPtr()->Reset(D3D12Graphics::GetInstance().getAllocatorPtr(), nullptr);
}

void D3D12Uninit()
{
}

#include "Main.h"
#include <memory>
#include "DirectX.h"
#include "Geometory.h"
#include "Input.h"
#include "SceneRoot.h"

// ---- �O���[�o���ϐ� ----
std::shared_ptr<SceneRoot> g_pScene;

// �Q�[��������
HRESULT Init(HWND hWnd, UINT width, UINT height)
{
	HRESULT hr;

	// DirectX������
	hr = InitDirectX(hWnd, width, height, false);
	if (FAILED(hr)) { return hr; }

	// �W�I���g��������
	Geometory::Init();

	// ���͏�����
	InitInput();

	// �V�[���쐬
	g_pScene = std::make_shared<SceneRoot>();
	g_pScene->Init();

	// �������\�[�X�쐬
	auto rtv = g_pScene->CreateObj<RenderTarget>("RTV");
	rtv->CreateFromScreen();
	auto dsv = g_pScene->CreateObj<DepthStencil>("DSV");
	hr = dsv->Create(width, height, false);

	// �����_�[�^�[�Q�b�g�ݒ�
	SetRenderTargets(1, &rtv, dsv);

	return hr;
}

// �Q�[���I��
void Uninit()
{
	g_pScene->Uninit();
	g_pScene.reset();

	// ���͏I��
	UninitInput();

	// �W�I���g���I��
	Geometory::Uninit();

	// DirectX�I��
	UninitDirectX();
}

// �X�V
void Update(float tick)
{
	UpdateInput();
	g_pScene->_update(tick);
}

// �`��
void Draw()
{
	auto rtv = g_pScene->GetObj<RenderTarget>("RTV");
	auto dsv = g_pScene->GetObj<DepthStencil>("DSV");
	float color[4] = { 0.8f, 0.9f, 1.0f, 1.0f };

	GetContext()->ClearRenderTargetView(rtv->GetView(), color);
	GetContext()->ClearDepthStencilView(dsv->GetView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	// �V�[���̕`��
	g_pScene->_draw();

	// ��ʂ̃X���b�v���s
	SwapDirectX();
}

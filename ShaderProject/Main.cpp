#include "Main.h"
#include <memory>
#include "DirectX.h"
#include "Geometory.h"
#include "Input.h"
#include "SceneRoot.h"

// ---- グローバル変数 ----
std::shared_ptr<SceneRoot> g_pScene;

// ゲーム初期化
HRESULT Init(HWND hWnd, UINT width, UINT height)
{
	HRESULT hr;

	// DirectX初期化
	hr = InitDirectX(hWnd, width, height, false);
	if (FAILED(hr)) { return hr; }

	// ジオメトリ初期化
	Geometory::Init();

	// 入力初期化
	InitInput();

	// シーン作成
	g_pScene = std::make_shared<SceneRoot>();
	g_pScene->Init();

	// 初期リソース作成
	auto rtv = g_pScene->CreateObj<RenderTarget>("RTV");
	rtv->CreateFromScreen();
	auto dsv = g_pScene->CreateObj<DepthStencil>("DSV");
	hr = dsv->Create(width, height, false);

	// レンダーターゲット設定
	SetRenderTargets(1, &rtv, dsv);

	return hr;
}

// ゲーム終了
void Uninit()
{
	g_pScene->Uninit();
	g_pScene.reset();

	// 入力終了
	UninitInput();

	// ジオメトリ終了
	Geometory::Uninit();

	// DirectX終了
	UninitDirectX();
}

// 更新
void Update(float tick)
{
	UpdateInput();
	g_pScene->_update(tick);
}

// 描画
void Draw()
{
	auto rtv = g_pScene->GetObj<RenderTarget>("RTV");
	auto dsv = g_pScene->GetObj<DepthStencil>("DSV");
	float color[4] = { 0.8f, 0.9f, 1.0f, 1.0f };

	GetContext()->ClearRenderTargetView(rtv->GetView(), color);
	GetContext()->ClearDepthStencilView(dsv->GetView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	// シーンの描画
	g_pScene->_draw();

	// 画面のスワップ実行
	SwapDirectX();
}

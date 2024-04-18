#include "SceneVisual.h"
#include "Model.h"
#include "CameraBase.h"
#include "LightBase.h"
#include "Input.h"

void SceneVisual::Init()
{
	// シェーダー読込
	Shader* shader[] = {
		CreateObj<VertexShader>("VS_Object"),
		CreateObj<PixelShader>("PS_TexColor"),
	};
	const char* filePath[] = {
		"Assets/Shader/VS_Object.cso",
		"Assets/Shader/PS_TexColor.cso",
	};
	static_assert(_countof(shader) == _countof(filePath), "");
	for (int i = 0; i < _countof(shader); ++i)
		shader[i]->Load(filePath[i]);

	m_time = 0.0f;
}
void SceneVisual::Uninit()
{
}
void SceneVisual::Update(float tick)
{
	m_time += tick;
}
void SceneVisual::Draw()
{
	// 描画情報
	Model* pModel = GetObj<Model>("Model");
	CameraBase* pCamera = GetObj<CameraBase>("Camera");
	LightBase* pLight = GetObj<LightBase>("Light");

	// 各種シェーダー取得
	Shader* shader[] = {
		GetObj<Shader>("VS_Object"),
		GetObj<Shader>("PS_TexColor"),
	};
	int shaderPair[][2] = {
		{0, 1},
	};

	// 変換行列設定
	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixIdentity());
	mat[1] = pCamera->GetView();
	mat[2] = pCamera->GetProj();

	// ライト設定
	DirectX::XMFLOAT3 dir = pLight->GetDirection();
	DirectX::XMFLOAT4 light[3] = {
		{dir.x, dir.y, dir.z, 1.0f},
		pLight->GetDiffuse(),
		pLight->GetAmbient()
	};

	// カメラ設定
	DirectX::XMFLOAT3 camPos = pCamera->GetPos();
	DirectX::XMFLOAT4 camera[] = {
		{camPos.x, camPos.y, camPos.z, 0.0f}
	};

	// 描画
	int drawNum = _countof(shaderPair);
	for (int i = 0; i < drawNum; ++i)
	{
		DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(
			DirectX::XMMatrixTranslation(i - (drawNum - 1) * 0.5f, 0.0f, 0.0f)
		));
		shader[shaderPair[i][0]]->WriteBuffer(0, mat);
		shader[shaderPair[i][1]]->WriteBuffer(0, light);
		shader[shaderPair[i][1]]->WriteBuffer(1, camera);
		pModel->SetVertexShader(shader[shaderPair[i][0]]);
		pModel->SetPixelShader(shader[shaderPair[i][1]]);
		pModel->Draw();
	}
}
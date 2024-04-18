#include "MoveLight.h"
#include <utility>
#include "Input.h"
#include <algorithm>

// コンストラクタ
MoveLight::MoveLight()
	: m_radXZ(0.0f)
	, m_radY(DirectX::XM_PIDIV4)
	, m_h(0.0f)
	, m_sv(1.0f)
{
}

// デストラクタ
MoveLight::~MoveLight()
{
}

// 更新
void MoveLight::Update()
{
	if (IsKeyPress('L'))
		UpdateParam();
}

void MoveLight::UpdateParam()
{
	// 回転
	constexpr float rotSpeed = DirectX::XMConvertToRadians(360.0f / (2.0f * 60)); // 2秒で1回転
	if (IsKeyPress('A')) { m_radXZ += rotSpeed; }
	if (IsKeyPress('D')) { m_radXZ -= rotSpeed; }
	if (IsKeyPress('W')) { m_radY += rotSpeed; }
	if (IsKeyPress('S')) { m_radY -= rotSpeed; }
	m_radY = std::min(std::max(m_radY, 0.0f), DirectX::XM_PIDIV2);

	const float lightLength = 5.0f;
	m_direction.x = cosf(m_radY) * sinf(m_radXZ) * lightLength;
	m_direction.y = -sinf(m_radY) * lightLength;
	m_direction.z = cosf(m_radY) * cosf(m_radXZ) * lightLength;

	m_pos.x = -m_direction.x;
	m_pos.y = -m_direction.y;
	m_pos.z = -m_direction.z;
}

// 回転角の設定
void MoveLight::SetRot(float xz, float y)
{
	m_radXZ = xz;
	m_radY = y;
}

// XZ平面角の取得
float MoveLight::GetRotXZ()
{
	return m_radXZ;
}

// Y軸角の取得
float MoveLight::GetRotY()
{
	return m_radY;
}

// HSV色空間の設定
void MoveLight::SetHSV(float h, float sv)
{
	m_h = h;
	m_sv = sv;
}

// Hue(色相)取得
float MoveLight::GetH()
{
	return m_h;
}

// Saturation(彩度),Value(明度)取得
float MoveLight::GetSV()
{
	return m_sv;
}

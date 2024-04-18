#include "MoveLight.h"
#include <utility>
#include "Input.h"
#include <algorithm>

// �R���X�g���N�^
MoveLight::MoveLight()
	: m_radXZ(0.0f)
	, m_radY(DirectX::XM_PIDIV4)
	, m_h(0.0f)
	, m_sv(1.0f)
{
}

// �f�X�g���N�^
MoveLight::~MoveLight()
{
}

// �X�V
void MoveLight::Update()
{
	if (IsKeyPress('L'))
		UpdateParam();
}

void MoveLight::UpdateParam()
{
	// ��]
	constexpr float rotSpeed = DirectX::XMConvertToRadians(360.0f / (2.0f * 60)); // 2�b��1��]
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

// ��]�p�̐ݒ�
void MoveLight::SetRot(float xz, float y)
{
	m_radXZ = xz;
	m_radY = y;
}

// XZ���ʊp�̎擾
float MoveLight::GetRotXZ()
{
	return m_radXZ;
}

// Y���p�̎擾
float MoveLight::GetRotY()
{
	return m_radY;
}

// HSV�F��Ԃ̐ݒ�
void MoveLight::SetHSV(float h, float sv)
{
	m_h = h;
	m_sv = sv;
}

// Hue(�F��)�擾
float MoveLight::GetH()
{
	return m_h;
}

// Saturation(�ʓx),Value(���x)�擾
float MoveLight::GetSV()
{
	return m_sv;
}

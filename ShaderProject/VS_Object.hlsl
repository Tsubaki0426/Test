//���_�V�F�[�_�̓���
struct VS_IN
{
	float3 pos		: POSITION0;	//���_���W
	float3 normal	: NORMAL0;		//�@�����
	float2 uv		: TEXCOORD0;	//�e�N�X�`�����W
};

//���_�V�F�[�_����̏o�́[���s�N�Z���V�F�[�_�[�ɏo��
struct VS_OUT
{
	float4 pos		: SV_POSITION;	//�v���W�F�N�V�����ϊ���̒��_���W
	float3 normal	: NORMAL0;		//���[���h�ϊ���̒��_���W
	float2 uv		: TEXCOORD0;	//�e�N�X�`�����W
};

//�萔�o�b�t�@
cbuffer Matrix : register(b0)
{
	float4x4 world;		//���[���h�s��
	float4x4 view;		//�r���[�s��
	float4x4 proj;		//�v���W�F�N�V�����s��
};
//DirectX11��API�ł���UpdateSubresource()���g���Ē萔�o�b�t�@���Z�b�g����

//���_�V�F�[�_�̃��C������
//���̏����𒸓_���Ƃɂ���
VS_OUT main(VS_IN vin)
{
	VS_OUT vout;

	//���W�ϊ�
	vout.pos = float4(vin.pos, 1.0f);	//���_���W�ix,y,z�j���擾������1.0f�ɂ���
	vout.pos = mul(vout.pos, world);	//���[���h�s��̏�Z
	vout.pos = mul(vout.pos, view);		//�r���[�s��̏�Z
	vout.pos = mul(vout.pos, proj);		//�v���W�F�N�V�����s��̏�Z
	//���̏����Œ��_�̍��W����ʃs�N�Z���̍��W�ɕϊ����܂�

	//�@���x�N�g�������[���h�s��ŕϊ�
	vout.normal = mul(vin.normal, (float3x3)world);

	//���_�f�[�^��UV���W���s�N�Z���V�F�[�_�ւ̏o�̓f�[�^�Ƃ��Đݒ�
	vout.uv = vin.uv;

	//�s�N�Z���V�F�[�_�ɂ���
	return vout;
}

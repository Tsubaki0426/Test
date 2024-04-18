//�s�N�Z���V�F�[�_�̓���
struct PS_IN
{
	float4 pos		: SV_POSITION;	//�s�N�Z���̈ʒu
	float3 normal	: NORMAL;		//�@���x�N�g��
	float2 uv		: TEXCOORD0;	//�e�N�X�`�����W
	float3 worldPos : POSITION0;    //���[���h���W
};

cbuffer Light : register(b0)
{
	float4 lightDir;
	float4 lightDiffuse;
	float4 lightAmbient;
}

cbuffer Camera : register(b1)
{
	float4 camPos;	//	�J�����̈ʒu
};

//register���g�����ƂŃ��\�[�X�������悭�g����
//�e�N�X�`���̃o�C���h�it0 = �e�N�X�`�����\�[�X�������Ă���j
Texture2D tex : register(t0);
//�T���v���[�ւ̃o�C���h(s0 = �T���v���X�e�[�g�������Ă���i�e���Ƃ���ۊǁj)
SamplerState samp : register(s0);

//�s�N�Z���V�F�[�_�̃��C������
//���_�ň͂܂�Ă���s�N�Z�����������s
float4 main(PS_IN pin) : SV_TARGET
{
	float4 color;

//�e�N�X�`�����T���v�����O
color = tex.Sample(samp, pin.uv);

float3 N = normalize(pin.normal);
float3 L = normalize(-lightDir.xyz);
float diffuse = saturate(dot(N,L));

color *= diffuse * lightDiffuse + lightAmbient;

//�����x�N�g���Ɣ��˃x�N�g���̌v�Z
float3 V = normalize(camPos.xyz - pin.worldPos);
float3 R = normalize(reflect(-L,N));

//���ʌ��̌v�Z
float specular = saturate(dot(V,R));

//�J���[�ɋ��ʌ������Z
color += pow(specular,5.0f);

//�A���t�@�l��1.0�ɐݒ�
color.a = 1.0f;

return color;
}

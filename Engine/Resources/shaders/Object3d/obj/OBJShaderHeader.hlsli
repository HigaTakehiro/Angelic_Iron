cbuffer cbuff0 : register(b0)
{
    matrix viewproj;
	matrix world; //�R�c�ϊ��s��
    float3 cameraPos; //�J�������W
};

cbuffer cbuff1 : register(b1)
{
	float3 m_ambient : packoffset(c0); //�A���r�G���g�W��
	float3 m_diffuse : packoffset(c1); //�f�B�t���[�Y�W��
	float3 m_specular : packoffset(c2); //�X�y�L�����[�W��
	float m_alpha : packoffset(c2.w); //�A���t�@
};

static const int DirLightNum = 3;

struct DirLight
{
    float3 lightVec;
    float3 lightColor;
    uint isActive;
};

static const int PointLightNum = 3;

struct PointLight
{
    float3 lightPos;
    float3 lightColor;
    float3 lightAtten;
    uint isActive;
};

static const int SpotLightNum = 3;

struct SpotLight
{
    float3 lightVec;
    float3 lightPos;
    float3 lightColor;
    float3 lightAtten;
    float2 lightAngle;
    uint isActive;
};

cbuffer cbuff2 : register(b2)
{
    float3 ambientColor;
    DirLight dirLights[DirLightNum];
    PointLight pointLights[PointLightNum];
    SpotLight spotLights[SpotLightNum];
}

// ���_�V�F�[�_�[����s�N�Z���V�F�[�_�[�ւ̂����Ɏg�p����\����
struct VSOutput
{
    float4 svpos : SV_POSITION;
    float4 worldpos : POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
};
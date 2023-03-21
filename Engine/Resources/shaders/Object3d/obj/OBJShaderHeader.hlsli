cbuffer cbuff0 : register(b0)
{
    matrix viewproj;
	matrix world; //３Ｄ変換行列
    float4 color; //色
    float3 cameraPos; //カメラ座標
    float time;
};

cbuffer cbuff1 : register(b1)
{
	float3 m_ambient : packoffset(c0); //アンビエント係数
	float3 m_diffuse : packoffset(c1); //ディフューズ係数
	float3 m_specular : packoffset(c2); //スペキュラー係数
	float m_alpha : packoffset(c2.w); //アルファ
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

static const int CircleShadowNum = 1;

struct CircleShadow
{
    float3 dir;
    float3 casterPos;
    float distanceCasterLight;
    float3 atten;
    float2 factorAngle;
    uint isActive;
};

static const int ShadowMapNum = 1;

struct ShadowMap
{
    float3 dir;
    uint isActive;
};

cbuffer cbuff2 : register(b2)
{
    float3 ambientColor;
    DirLight dirLights[DirLightNum];
    PointLight pointLights[PointLightNum];
    SpotLight spotLights[SpotLightNum];
    CircleShadow circleShadows[CircleShadowNum];
    ShadowMap shadowMaps[ShadowMapNum];
}

// 頂点シェーダーからピクセルシェーダーへのやり取りに使用する構造体
struct VSOutput
{
    float4 svpos : SV_POSITION;
    float4 worldpos : POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
};
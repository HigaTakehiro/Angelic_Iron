cbuffer cbuff0 : register(b0)
{
    matrix viewproj;
	matrix world; //３Ｄ変換行列
    float4 color; //色
    float3 cameraPos; //カメラ座標
};

cbuffer cbuff1 : register(b1)
{
	float3 m_ambient : packoffset(c0); //アンビエント係数
	float3 m_diffuse : packoffset(c1); //ディフューズ係数
	float3 m_specular : packoffset(c2); //スペキュラー係数
	float m_alpha : packoffset(c2.w); //アルファ
};

cbuffer cbuff2 : register(b2)
{
    float3 lightVec;
    float3 lightColor;
    float3 lightPos; //ライト座標
}

// 頂点シェーダーからピクセルシェーダーへのやり取りに使用する構造体
struct VSOutput
{
    float4 svpos : SV_POSITION;
    float4 worldpos : POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
};
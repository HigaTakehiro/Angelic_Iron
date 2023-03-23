cbuffer cbuff0 : register(b0)
{
    matrix wvp;
    matrix world;
}

cbuffer cbuff1 : register(b1)
{
    matrix lightVP;
    float4 lightColor;
    float3 lightDir;
}

struct VS_Input
{
    float3 pos : POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
};

struct PS_Input
{
    float4 svPos : SV_POSITION;
    float4 posSM : POSITION_SM;
    float4 normal : NORMAL;
    float2 uv : TEXCOORD;
};
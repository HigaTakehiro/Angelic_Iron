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

struct VSInput
{
    float3 pos : POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
};

struct VSOutput
{
    float4 svPos : SV_POSITION;
    float4 smPos : POSITION;
    float3 smNormal : NORMAL;
    float2 smUv : TEXCOORD;
};
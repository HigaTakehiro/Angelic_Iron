#include "PostEffect.hlsli"

Texture2D<float4> tex0 : register(t0); // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0); // 0番スロットに設定されたサンプラー

float WhiteNoise(float2 coord)
{
    return frac(sin(dot(coord, float2(18.12, 12.72))) * 827.02);
}

float4 main(VSOutput input) : SV_TARGET
{
    float2 uvPoint = input.uv;
    float4 texcolor = tex0.Sample(smp, input.uv);
    float noise = WhiteNoise(input.uv * time) - 0.5f;
    uvPoint.x += 0.01f;
    //texcolor.rgb += float3(noise, noise, noise);
    texcolor.r = tex0.Sample(smp, uvPoint).r;
    
    float vignette = length(float2(0.5, 0.5) - input.uv);
    vignette = clamp(vignette - 0.1 - time, 0, 1);
    texcolor.r += vignette;
    
    return float4(texcolor.rgb, 1);
}
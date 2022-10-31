#include "PostEffect.hlsli"

Texture2D<float4> tex0 : register(t0); // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0); // 0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{
    float2 uvPoint = input.uv;
    float4 texcolor = tex0.Sample(smp, input.uv);
    float vignette = length(float2(0.5, 0.5) - input.uv);
    vignette = clamp(vignette - 0.4, 0, 2);
    texcolor.rgb -= vignette;
    
    return float4(texcolor.rgb, 1);
}
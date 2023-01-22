#include "PostEffect.hlsli"

Texture2D<float4> tex0 : register(t0); // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0); // 0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{
    const float blurPower = 0.5f;
    const float sampleCount = 8.0f;
    
    float4 texcolor = 0;
    float2 symmetryUV = input.uv - 0.5f;
    float distance = length(symmetryUV);
    float factor = blurPower / sampleCount * distance;
    for (int i = 0; i < sampleCount; i++)
    {
        float uvOffset = 1 - factor * i * (time / 20.0f);
        texcolor += tex0.Sample(smp, symmetryUV * uvOffset + 0.5f);
    }
    texcolor /= sampleCount;
    
    return float4(texcolor.rgb, 1);
}
#include "PostEffect.hlsli"

Texture2D<float4> tex0 : register(t0); // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0); // 0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{
    float blurPower = 0.0f;
    const float sampleCount = 8.0f;
    
    blurPower = (time / maxTime);
    if (time >= maxTime / 2.0f)
    {
        blurPower = (maxTime / time) - 1.0f;
    }
    
    float4 texcolor = 0;
    float2 symmetryUV = input.uv - 0.5f;
    float distance = length(symmetryUV);
    float factor = blurPower / sampleCount * distance;
    for (int i = 0; i < sampleCount; i++)
    {
        float uvOffset = 0;
        uvOffset = 1 - factor * i;
        texcolor += tex0.Sample(smp, symmetryUV * uvOffset + 0.5f);
      
    }
    texcolor /= sampleCount;
    
    float vignette = length(float2(0.5, 0.5) - input.uv);
    vignette = clamp(vignette - 0.45, 0, 1);
    texcolor.rgb -= vignette;
    
    return float4(texcolor.rgb, 1);
}
#include "ShadowMapHeader.hlsli"

Texture2D<float4> tex0 : register(t0);
Texture2D<float> shadowMap : register(t1);
SamplerState smp0 : register(s0);
SamplerState smp1 : register(s1);

float4 main(VSOutput input) : SV_TARGET
{
    float sm = shadowMap.Sample(smp1, input.smPos.xy);
    float sma = (input.smPos.z - 0.005f < sm) ? 1.0f : 0.5f;
    
    return tex0.Sample(smp0, input.smUv) * sma;
}
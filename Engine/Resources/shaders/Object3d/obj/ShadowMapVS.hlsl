#include "ShadowMapHeader.hlsli"

VSOutput main(VSInput input)
{
    VSOutput output;
    float4 pos = float4(input.pos, 1.0f);
    float4 normal = float4(input.normal, 0.0f);
    output.svPos = mul(pos, wvp);
    output.smNormal = mul(normal, world);
    output.smUv = input.uv;
    pos = mul(pos, world);
    pos = mul(pos, lightVP);
    pos.xyz = pos.xyz / pos.w;
    output.smPos.x = (1.0f + pos.x) / 2.0f;
    output.smPos.y = (1.0f - pos.y) / 2.0f;
    output.smPos = pos.z;
    return output;
}
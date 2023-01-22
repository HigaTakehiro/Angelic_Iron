#include "OBJShaderHeader.hlsli"

VSOutput main(float4 pos : POSITION, float3 normal : NORMAL, float2 uv : TEXCOORD)
{
    const float pi = 3.141592;
    
    VSOutput output; // ピクセルシェーダーに渡す値
    float4 wnormal = normalize(mul(world, float4(normal, 0)));
    float4 wpos = mul(world, pos);
    
    output.svpos = mul(mul(viewproj, world), pos);
    output.svpos.y += (sin(output.svpos.x + (time * 0.5f) * 100.0f) * pi * -10.0f);
    output.worldpos = wpos;
    output.normal = wnormal.xyz;
    output.uv = uv;

    return output;
}
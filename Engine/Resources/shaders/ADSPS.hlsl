#include "OBJShaderHeader.hlsli"

Texture2D<float4> tex : register(t0); // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0); // 0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{
    float4 wnormal = normalize(mul(world, float4(input.normal, 0)));
    float4 wpos = mul(world, input.svpos);
    float4 texcolor = tex.Sample(smp, input.uv);
    float4 ambient = texcolor / 2;
    float3 eyeDir = normalize(cameraPos - wpos.xyz);
    float3 halfVec = normalize(lightPos + eyeDir);
    float intensity = saturate(dot(normalize(input.normal), halfVec));
    float reflect = pow(intensity, 50);
    float4 diffuse = texcolor * intensity;
    const float4 lightRef = (1, 1, 1, 1);
    float4 specular = lightRef * reflect;
    float4 ads = ambient + diffuse + specular;
    return float4(ads.rgb * color.rgb, texcolor.a * m_alpha);
}
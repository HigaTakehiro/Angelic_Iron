#include "OBJShaderHeader.hlsli"

Texture2D<float4> tex : register(t0); // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0); // 0番スロットに設定されたサンプラー

float4 main(TestVSOutput input) : SV_TARGET
{
    //光沢
    const float shininess = 4.0f;
    float4 shadeColor;
    
    //float4 wnormal = normalize(mul(world, float4(input.normal, 0)));
    //float4 wpos = mul(world, input.svpos);
    
    //float3 ambient = m_ambient;
    //float3 diffuse = dot(-lightVec, wnormal.xyz) * m_diffuse;
    //float3 cameraPos = cameraPos;
    //float3 eyeDir = normalize(cameraPos - wpos.xyz);
    //float3 reflect = normalize(lightVec + 2 * dot(-lightVec, wnormal.xyz) * wnormal.xyz);
    //float3 specular = pow(saturate(dot(reflect, eyeDir)), shininess) * m_specular;
    //shadeColor.rgb = (ambient + diffuse + specular) * lightColor;
    //shadeColor.a = m_alpha;
    
    float4 texColor = tex.Sample(smp, input.uv);
    
    return input.color * texColor;
}
#include "OBJShaderHeader.hlsli"

Texture2D<float4> tex : register(t0); // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0); // 0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{
    //光沢
    const float shininess = 4.0f;
    float4 shadeColor;
    
    float4 texColor = tex.Sample(smp, input.uv);
    float3 eyeDir = normalize(cameraPos - input.worldpos.xyz);
    float3 dotlightnormal = dot(lightVec, input.normal);
    float3 reflect = normalize(-lightVec + 2 * dotlightnormal * input.normal);
    float3 ambient = m_ambient;
    float3 diffuse = dotlightnormal * m_diffuse;
    float3 specular = pow(saturate(dot(reflect, eyeDir)), shininess) * m_specular;
    shadeColor.rgb = (ambient + diffuse + specular) * lightColor;
    shadeColor.a = m_alpha;
    
    return shadeColor * texColor;
}
#include "OBJShaderHeader.hlsli"

Texture2D<float4> tex : register(t0); // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0); // 0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{
    float4 texColor = tex.Sample(smp, input.uv);
    const float shininess = 4.0f;
    float3 eyeDir = normalize(cameraPos - input.worldpos.xyz);
    float3 ambient = m_ambient;
    float4 shadeColor = float4(ambientColor * ambient, m_alpha);
    
    for (int i = 0; i < DirLightNum; i++)
    {
        if (dirLights[i].isActive)
        {
            float3 dotLightNormal = dot(dirLights[i].lightVec, input.normal);
            float3 reflect = normalize(-dirLights[i].lightVec + 2 * dotLightNormal * input.normal);
            float3 diffuse = dotLightNormal * m_diffuse;
            float3 specular = pow(saturate(dot(reflect, eyeDir)), shininess) * m_specular;
            
            shadeColor.rgb += (diffuse + specular) * dirLights[i].lightColor;
        }
    }
    
    for (int i = 0; i < PointLightNum; i++)
    {
        if (pointLights[i].isActive)
        {
            float3 lightVec = pointLights[i].lightPos - input.worldpos.xyz;
            float d = length(lightVec);
            lightVec = normalize(lightVec);
            
            float atten = 1.0f / (pointLights[i].lightAtten.x + pointLights[i].lightAtten.y * d + pointLights[i].lightAtten.z * d * d);
            float3 dotLightNormal = dot(lightVec, input.normal);
            float3 reflect = normalize(-lightVec + 2 * dotLightNormal * input.normal);
            float3 diffuse = dotLightNormal * m_diffuse;
            float3 specular = pow(saturate(dot(reflect, eyeDir)), shininess) * m_specular;
            
            shadeColor.rgb += atten * (diffuse + specular) * pointLights[i].lightColor;
        }
    }
    
    return shadeColor * texColor;
}
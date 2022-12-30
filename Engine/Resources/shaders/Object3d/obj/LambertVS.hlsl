#include "OBJShaderHeader.hlsli"

TestVSOutput main(float4 pos : POSITION, float3 normal : NORMAL, float2 uv : TEXCOORD)
{
    TestVSOutput output; // ピクセルシェーダーに渡す値
    output.svpos = mul(mul(viewproj, world), pos);
    float3 ambient = m_ambient;
    float3 lightDir = float3(1, -1, 1);
    lightDir = normalize(lightDir);
    float3 diffuse = dot(-lightDir, normal) * m_diffuse;
    float3 eye = cameraPos;
    const float shininess = 4.0f;
    float3 eyeDir = normalize(eye - pos.xyz);
    float3 reflect = normalize(lightDir + 2 * dot(-lightDir, normal) * normal);
    float3 specular = pow(saturate(dot(reflect, eyeDir)), shininess) * m_specular;
    float3 lightColor = float3(1, 1, 1);
    output.color.rgb = (ambient + diffuse + specular) * lightColor;
    output.color.a = m_alpha;
    output.uv = uv;
    return output;
}
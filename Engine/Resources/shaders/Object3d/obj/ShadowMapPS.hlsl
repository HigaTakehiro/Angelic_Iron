//#include "ShadowMap.hlsli"

//Texture2D<float4> tex : register(t0); // 0番スロットに設定されたテクスチャ
//Texture2D<float> shadow : register(t1);
//SamplerState smp0 : register(s0); // 0番スロットに設定されたサンプラー
//SamplerState smp1 : register(s1);

//PS_INPUT main(VS_INPUT input) : SV_TARGET
//{
//    PS_INPUT output;
//    float4 pos = float4(input.position, 1.0f);
//    float4 normal = float4(input.normal, 0.0f);
//    output.position = mul(pos, WVP);
//    output.normal = mul(normal, world);
//    output.uv = input.uv;
    
//    pos = mul(pos, world);
//    pos = mul(pos, lightVP);
//    pos.xyz = pos.xyz / pos.w;
//    output.posSM.x = (1.0f + pos.x) / 2.0f;
//    output.posSM.y = (1.0f - pos.y) / 2.0f;
//    output.posSM.z = pos.z;
    
//    return output;
//}

//float4 PSMain(PS_INPUT input) : SV_TARGET
//{
//    float sm = shadow.Sample(smp1, input.posSM.xy);
//    float sma = (input.posSM.z - 0.005f < sm) ? 1.0f : 0.5f;
    
//    return tex.Sample(smp0, input.uv) * sma;
//}
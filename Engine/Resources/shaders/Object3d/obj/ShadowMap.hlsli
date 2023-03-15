//cbuffer cbuff0 : register(b0)
//{
//    matrix world; //３Ｄ変換行列
//    matrix WVP; //ワールドビュープロジェクション合成行列
//    float4 color; //色
//    float3 cameraPos; //カメラ座標
//};

//cbuffer cbLight : register(b1)
//{
//    matrix lightVP; //ライトビュープロジェクション合成行列
//    float4 lightColor; //ライト色
//    float3 lightDir; //ライト方向
//}

//struct VS_INPUT
//{
//    float3 position : POSITION;
//    float3 normal : NORMAL;
//    float2 uv : TEXCOORD;
//};

//struct PS_INPUT
//{
//    float4 position : SV_POSITION;
//    float4 posSM : POSITION_SM;
//    float4 normal : NORMAL;
//    float2 uv : TEXCOORD;
//};
//ピクセルシェーダの入力
struct PS_IN
{
	float4 pos		: SV_POSITION;	//ピクセルの位置
	float3 normal	: NORMAL;		//法線ベクトル
	float2 uv		: TEXCOORD0;	//テクスチャ座標
	float3 worldPos : POSITION0;    //ワールド座標
};

cbuffer Light : register(b0)
{
	float4 lightDir;
	float4 lightDiffuse;
	float4 lightAmbient;
}

cbuffer Camera : register(b1)
{
	float4 camPos;	//	カメラの位置
};

//registerを使うことでリソースを効率よく使える
//テクスチャのバインド（t0 = テクスチャリソースが入っている）
Texture2D tex : register(t0);
//サンプラーへのバインド(s0 = サンプラステートが入っている（粗さとかを保管）)
SamplerState samp : register(s0);

//ピクセルシェーダのメイン処理
//頂点で囲まれているピクセル分だけ実行
float4 main(PS_IN pin) : SV_TARGET
{
	float4 color;

//テクスチャをサンプリング
color = tex.Sample(samp, pin.uv);

float3 N = normalize(pin.normal);
float3 L = normalize(-lightDir.xyz);
float diffuse = saturate(dot(N,L));

color *= diffuse * lightDiffuse + lightAmbient;

//視線ベクトルと反射ベクトルの計算
float3 V = normalize(camPos.xyz - pin.worldPos);
float3 R = normalize(reflect(-L,N));

//鏡面光の計算
float specular = saturate(dot(V,R));

//カラーに鏡面光を加算
color += pow(specular,5.0f);

//アルファ値を1.0に設定
color.a = 1.0f;

return color;
}

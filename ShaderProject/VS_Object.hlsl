//頂点シェーダの入力
struct VS_IN
{
	float3 pos		: POSITION0;	//頂点座標
	float3 normal	: NORMAL0;		//法線情報
	float2 uv		: TEXCOORD0;	//テクスチャ座標
};

//頂点シェーダからの出力ー＞ピクセルシェーダーに出力
struct VS_OUT
{
	float4 pos		: SV_POSITION;	//プロジェクション変換後の頂点座標
	float3 normal	: NORMAL0;		//ワールド変換後の頂点座標
	float2 uv		: TEXCOORD0;	//テクスチャ座標
};

//定数バッファ
cbuffer Matrix : register(b0)
{
	float4x4 world;		//ワールド行列
	float4x4 view;		//ビュー行列
	float4x4 proj;		//プロジェクション行列
};
//DirectX11のAPIであるUpdateSubresource()を使って定数バッファをセットする

//頂点シェーダのメイン処理
//この処理を頂点ごとにする
VS_OUT main(VS_IN vin)
{
	VS_OUT vout;

	//座標変換
	vout.pos = float4(vin.pos, 1.0f);	//頂点座標（x,y,z）を取得しｗを1.0fにする
	vout.pos = mul(vout.pos, world);	//ワールド行列の乗算
	vout.pos = mul(vout.pos, view);		//ビュー行列の乗算
	vout.pos = mul(vout.pos, proj);		//プロジェクション行列の乗算
	//この処理で頂点の座標を画面ピクセルの座標に変換します

	//法線ベクトルをワールド行列で変換
	vout.normal = mul(vin.normal, (float3x3)world);

	//頂点データのUV座標をピクセルシェーダへの出力データとして設定
	vout.uv = vin.uv;

	//ピクセルシェーダにいく
	return vout;
}

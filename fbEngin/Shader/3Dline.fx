/*
 *3DLine描画
 */

float4x4 g_worldMatrix;			//ワールド行列。
float4x4 g_viewMatrix;			//ビュー行列。
float4x4 g_projectionMatrix;	//プロジェクション行列。
float4x4 g_rotationMatrix;		//回転行列。法線を回転させるために必要になる。ライティングするなら必須。

struct VS_IN
{
	float4 pos		: POSITION;
	float4 color	: COLOR0;
	float3	normal	: NORMAL0;
};

struct VS_OUT
{
	float4 pos		: POSITION;
	float4 color	: COLOR0;
	float3	normal	: TEXCOORD1;
};

VS_OUT vs_main(VS_IN In)
{
	VS_OUT Out = (VS_OUT)0;
	float4 pos;
	
	pos = mul(In.pos, g_worldMatrix);		//モデルのローカル空間からワールド空間に変換。
	pos = mul(pos, g_viewMatrix);			//ワールド空間からビュー空間に変換。
	pos = mul(pos, g_projectionMatrix);	//ビュー空間から射影空間に変換。
	Out.pos = pos;
	Out.color = In.color;
	Out.normal = mul(In.normal, g_rotationMatrix);	//法線を回す。

	return Out;
}

float4 ps_main(VS_OUT In) : COLOR0
{
	return In.color;
}

technique Line
{
	pass p0
	{
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 ps_main();
	}
};
/*
 *2D描画shader
 */

struct VS_INPUT
{
	float4 pos		: POSITION;
	float4 color	: COLOR0;
};

struct VS_OUTPUT
{
	float4 pos		: POSITION;
	float4 color	: COLOR0;
};

//頂点シェーダ
VS_OUTPUT vs_main(VS_INPUT In)
{
	//Outを0で初期化
	VS_OUTPUT Out = (VS_OUTPUT)0;
	
	//ポジションをそのまま渡す
	Out.pos = In.pos;
	//色情報もそのまま渡す
	Out.color = In.color;

	return Out;
}

/*!
* @brief	半透明合成用のピクセルシェーダー。
*/
float4 ps_main(VS_OUTPUT In) : COLOR0
{
	return In.color;
}

//2Dプリミティブ描画
technique TestPrimitive
{
	//半透明合成
	pass p0
	{
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 ps_main();
	}
};
/*
 *2D描画shader
 */
//マトリックス
float4x4	g_mWVP;

//UV
float uv_width;
float uv_height;
float uv_left;
float uv_top;

//基点
float pivotx;
float pivoty;

//ブレンドカラー
float4 g_blendColor;
//透過色(仮)
float4 g_killColor;

//テクスチャ。
texture g_texture;
sampler g_textureSampler =
sampler_state
{
	Texture = <g_texture>;
	MipFilter = NONE;
	MinFilter = NONE;
	MagFilter = NONE;
	AddressU = Wrap;
	AddressV = Wrap;
};

struct VS_INPUT
{
	float4 pos		: POSITION;
	float2 uv		: TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 pos		: POSITION;
	float2 uv		: TEXCOORD0;
};

//頂点シェーダ
VS_OUTPUT vs_main(VS_INPUT In)
{
	//Outを0で初期化
	VS_OUTPUT Out = (VS_OUTPUT)0;
	//ピボット調整
	Out.pos = In.pos - float4(pivotx, pivoty, 0.0f, 0.0f);
	Out.pos = mul(Out.pos, g_mWVP);
	
	//UV調整
	Out.uv = In.uv * float2(uv_width, uv_height) + float2(uv_left, uv_top);

	return Out;
}

/*!
* @brief	半透明合成用のピクセルシェーダー。
*/
float4 ps_main(VS_OUTPUT In) : COLOR0
{
	float4 color = tex2D(g_textureSampler, In.uv);

	//透明色と同じカラーならピクセルキル
	if (g_killColor.r == color.r &&
		g_killColor.g == color.g &&
		g_killColor.b == color.b &&
		g_killColor.a == color.a)
	{
		clip(-1);
	}

	color = color * g_blendColor;
	return color;
}

/*!
* @brief	加算合成用のピクセルシェーダー。
*/
float4 PSMainAdd(VS_OUTPUT In) : COLOR0
{
	float4 tex = tex2D(g_textureSampler, In.uv);
	return float4(tex.xyz * g_blendColor.a, 1.0f / 2.5f);
}

//sprite描画テクニック
technique SpriteTech
{
	//半透明合成
	pass p0
	{
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 ps_main();

		//半透明合成
		//AlphaBlendEnable = true;
		//SrcBlend = 5;//SRCALPHA;
		//DestBlend = INVSRCALPHA;
	}
	
	//加算合成
	pass p1
	{
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 PSMainAdd();

		//半透明合成
		/*AlphaBlendEnable = true;
		SrcBlend = ONE;
		DestBlend = ONE;*/
	}
};
/*!
 *@brief	カラーテクスチャプリミティブ。
 */
float4x4	g_mWVP;		//ワールドビュープロジェクション行列。

float g_brightness;
//ブレンドカラー
float4 g_blendColor;
texture g_texture;		//ディフューズテクスチャ。
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

struct VS_INPUT{
	float4	pos		: POSITION;
	float2	uv		: TEXCOORD0;
};

struct VS_OUTPUT{
	float4 pos		: POSITION;
	float2	uv		: TEXCOORD0;
};

VS_OUTPUT VSMain( VS_INPUT In )
{
	//Outを0で初期化
	VS_OUTPUT Out = (VS_OUTPUT)0;
	//座標を中心に
	Out.pos = In.pos - float4(0.5f, 0.5f, 0.0f, 0.0f);

	Out.pos = mul(Out.pos, g_mWVP);
	//uv調整
	Out.uv = In.uv;
	// *float2(uv_width, uv_height) + float2(uv_left, uv_top);
	return Out;
}
/*!
 * @brief	半透明合成用のピクセルシェーダー。
 */
float4 PSMainTrans( VS_OUTPUT In ) : COLOR0
{
	float4 tex = tex2D(g_textureSampler, In.uv);
	tex = tex * g_blendColor;
	return tex;
}
/*!
 * @brief	加算合成用のピクセルシェーダー。
 */
float4 PSMainAdd( VS_OUTPUT In ) : COLOR0
{
	float4 tex = tex2D(g_textureSampler, In.uv);
	tex.xyz *= g_blendColor.xyz;
	return float4(tex.xyz * g_blendColor.a, 1.0f / g_brightness);
}
/*!
 * @brief	半透明合成用のテクニック。
 */
technique ColorTexPrimTrans
{
	pass P0
    {          
        VertexShader = compile vs_2_0 VSMain();
        PixelShader  = compile ps_2_0 PSMainTrans();
    }
}
/*!
 * @brief	加算用テクニック。
 */
technique ColorTexPrimAdd
{
    pass P0
    {          
        VertexShader = compile vs_2_0 VSMain();
        PixelShader  = compile ps_2_0 PSMainAdd();
    }
}
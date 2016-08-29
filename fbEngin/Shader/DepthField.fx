/*!
 * @brief	被写界深度
 */

//WVPマトリックス
float4x4	g_mWVP;

texture g_Depth;//深度のテクスチャ

sampler g_DepthSampler =
sampler_state
{
	Texture = <g_Depth>;
	MipFilter = POINT;
	MinFilter = POINT;
	MagFilter = POINT;
};

texture g_Tex1;	//元のテクスチャ。
texture g_Tex2;	//ぼやけたテクスチャ。
texture g_Tex3;	//さらにぼやけたテクスチャ。

sampler g_Tex1Sampler = 
sampler_state
{
	Texture = <g_Tex1>;
    MipFilter = POINT;
    MinFilter = POINT;
    MagFilter = POINT;
};

sampler g_Tex2Sampler =
sampler_state
{
	Texture = <g_Tex2>;
	MipFilter = POINT;
	MinFilter = POINT;
	MagFilter = POINT;
};

sampler g_Tex3Sampler =
sampler_state
{
	Texture = <g_Tex3>;
	MipFilter = POINT;
	MinFilter = POINT;
	MagFilter = POINT;
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
VS_OUTPUT VS_Main(VS_INPUT In)
{
	//Outを0で初期化
	VS_OUTPUT Out = (VS_OUTPUT)0;
	//ピボット調整
	Out.pos = In.pos - float4(1.0f, 1.0f, 0.0f, 0.0f);
	Out.pos = mul(Out.pos, g_mWVP);

	Out.uv = In.uv;

	return Out;
}

float4 PS_Main(VS_OUTPUT In) : COLOR0
{

	float4 color;
	float4 Depth = tex2D(g_DepthSampler, In.uv);

	if (Depth.a > 0.5)
	{
		//元とボケ
		color = (1 - Depth) * tex2D(g_Tex1Sampler, In.uv) + Depth * tex2D(g_Tex2Sampler, In.uv);
	}
	else
	{
		//ボケとおおぼけ
		color = (1 - Depth) * tex2D(g_Tex3Sampler, In.uv) + Depth * tex2D(g_Tex2Sampler, In.uv);
	}

	return color;
}

/*!
 * @brief	被写界深度
 */
technique DepthField
{
	pass p0
	{
		VertexShader = compile vs_2_0 VS_Main();
		PixelShader = compile ps_2_0 PS_Main();
	}
}
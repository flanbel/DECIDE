/*!
 * @brief	ガウスフィルタ
 */

//マトリックス
float4x4	g_mWVP;


struct VS_INPUT{
	float4	pos : POSITION;
};

struct VS_OUTPUT{
	float4 pos : POSITION;
	float2  tex : TEXCOORD;
};

struct VS_BlurOutput{
	float4 pos	: POSITION;
	float2 tex0	: TEXCOORD0;
	float2 tex1 : TEXCOORD1;
	float2 tex2 : TEXCOORD2;
	float2 tex3 : TEXCOORD3;
	float2 tex4 : TEXCOORD4;
	float2 tex5 : TEXCOORD5;
	float2 tex6 : TEXCOORD6;
	float2 tex7 : TEXCOORD7;
};

texture g_tex;	//ブラーテクスチャ
sampler g_blurSampler = 
sampler_state
{
    Texture = <g_tex>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

float2 g_TexSize;		//テクスチャのサイズ。
float2 g_offset;		//オフセット
float  g_weight[8];		//ガウスフィルタの重み。

/*!
 * @brief	Xブラー頂点シェーダー。
 */
VS_BlurOutput VSXBlur(VS_INPUT In)
{
	VS_BlurOutput Out;
	//Out.pos = In.pos;

	Out.pos = In.pos - float4(0.5f, 0.5f, 0.0f, 0.0f);
	Out.pos = mul(Out.pos, g_mWVP);

	//なんか大きくなる
	float2 tex = (In.pos);// * 0.5f) / 0.5f;
	//tex.y = 1.0f - tex.y;
	tex += float2( 0.5/g_TexSize.x, 0.5/g_TexSize.y);
	Out.tex0 = tex + float2( - 1.0f/g_TexSize.x, 0.0f );
    Out.tex1 = tex + float2( - 3.0f/g_TexSize.x, 0.0f );
    Out.tex2 = tex + float2( - 5.0f/g_TexSize.x, 0.0f );
    Out.tex3 = tex + float2( - 7.0f/g_TexSize.x, 0.0f );
    Out.tex4 = tex + float2( - 9.0f/g_TexSize.x, 0.0f );
    Out.tex5 = tex + float2( -11.0f/g_TexSize.x, 0.0f );
    Out.tex6 = tex + float2( -13.0f/g_TexSize.x, 0.0f );
    Out.tex7 = tex + float2( -15.0f/g_TexSize.x, 0.0f );
    return Out;
}
/*!
 * @brief	Xブラーピクセルシェーダー。
 */
float4 PSXBlur( VS_BlurOutput In ) : COLOR
{
	float4 Color;
	Color  = g_weight[0] * (tex2D( g_blurSampler, In.tex0 )
	                 + tex2D( g_blurSampler, In.tex7 + g_offset ));
	Color += g_weight[1] * (tex2D( g_blurSampler, In.tex1 )
	                 + tex2D( g_blurSampler, In.tex6 + g_offset ));
	Color += g_weight[2] * (tex2D( g_blurSampler, In.tex2 )
	            + tex2D( g_blurSampler, In.tex5 + g_offset ));
	Color += g_weight[3] * (tex2D( g_blurSampler, In.tex3 )
	                 + tex2D( g_blurSampler, In.tex4 + g_offset ));
	Color += g_weight[4] * (tex2D( g_blurSampler, In.tex4 )
	                 + tex2D( g_blurSampler, In.tex3 + g_offset ));
	Color += g_weight[5] * (tex2D( g_blurSampler, In.tex5 )
	                 + tex2D( g_blurSampler, In.tex2 + g_offset ));
	Color += g_weight[6] * (tex2D( g_blurSampler, In.tex6 )
	                 + tex2D( g_blurSampler, In.tex1 + g_offset ));
	Color += g_weight[7] * (tex2D( g_blurSampler, In.tex7 )
	                 + tex2D( g_blurSampler, In.tex0 + g_offset ));
	return Color;
}
/*!
 * @brief	Yブラー頂点シェーダー。
 */
VS_BlurOutput VSYBlur(VS_INPUT In)
{
	VS_BlurOutput Out;
	//Out.pos = In.pos;

	Out.pos = In.pos - float4(0.5f, 0.5f, 0.0f, 0.0f);
	Out.pos = mul(Out.pos, g_mWVP);

	//なんか大きくなる
	float2 tex = (In.pos);// *0.5f) + 0.5f;

	//tex.y = tex.y + 0.1f;
	tex += float2( 0.5/g_TexSize.x, 0.5/g_TexSize.y);
	Out.tex0 = tex + float2( 0.0f,- 1.0f/g_TexSize.y  );
    Out.tex1 = tex + float2( 0.0f,- 3.0f/g_TexSize.y  );
    Out.tex2 = tex + float2( 0.0f,- 5.0f/g_TexSize.y  );
    Out.tex3 = tex + float2( 0.0f,- 7.0f/g_TexSize.y  );
    Out.tex4 = tex + float2( 0.0f,- 9.0f/g_TexSize.y  );
    Out.tex5 = tex + float2( 0.0f,-11.0f/g_TexSize.y  );
    Out.tex6 = tex + float2( 0.0f,-13.0f/g_TexSize.y  );
    Out.tex7 = tex + float2( 0.0f,-15.0f/g_TexSize.y  );
    return Out;
}
/*!
 * @brief	Yブラーピクセルシェーダー。
 */
float4 PSYBlur( VS_BlurOutput In ) : COLOR
{
	float4 Color;
	Color  = g_weight[0] * (tex2D( g_blurSampler, In.tex0 )
	                 + tex2D( g_blurSampler, In.tex7 + g_offset ));
	Color += g_weight[1] * (tex2D( g_blurSampler, In.tex1 )
	                 + tex2D( g_blurSampler, In.tex6 + g_offset ));
	Color += g_weight[2] * (tex2D( g_blurSampler, In.tex2 )
	            + tex2D( g_blurSampler, In.tex5 + g_offset ));
	Color += g_weight[3] * (tex2D( g_blurSampler, In.tex3 )
	                 + tex2D( g_blurSampler, In.tex4 + g_offset ));
	Color += g_weight[4] * (tex2D( g_blurSampler, In.tex4 )
	                 + tex2D( g_blurSampler, In.tex3 + g_offset ));
	Color += g_weight[5] * (tex2D( g_blurSampler, In.tex5 )
	                 + tex2D( g_blurSampler, In.tex2 + g_offset ));
	Color += g_weight[6] * (tex2D( g_blurSampler, In.tex6 )
	                 + tex2D( g_blurSampler, In.tex1 + g_offset ));
	Color += g_weight[7] * (tex2D( g_blurSampler, In.tex7 )
	                 + tex2D( g_blurSampler, In.tex0 + g_offset ));
	return Color;
}
/*!
 * @brief	ファイナル。
 */
VS_OUTPUT VSFinal( VS_INPUT In )
{
	VS_OUTPUT Out;
	//Out.pos = In.pos;		//トランスフォーム済み頂点なのでそのまま
	Out.pos = In.pos - float4(0.5f, 0.5f, 0.0f, 0.0f);
	Out.pos = mul(Out.pos, g_mWVP);

	Out.tex = (In.pos.xy * 0.5f) + 0.5f;
	Out.tex.y = 1.0f - Out.tex.y;
	Out.tex += g_offset;
	return Out;
}

float4 PSFinal( VS_OUTPUT In ) : COLOR
{
	float2 uv = In.tex;
	return tex2D(g_blurSampler, uv );
}

/*!
 * @brief	横ブラー
 */
technique GaussianBlur
{
	//横
	pass p0
	{
		VertexShader = compile vs_2_0 VSXBlur();
		PixelShader = compile ps_2_0 PSXBlur();
	}
	//縦
	pass p1
	{
			VertexShader = compile vs_2_0 VSYBlur();
			PixelShader = compile ps_2_0 PSYBlur();
	}
}

technique Final
{
	pass p0
	{
		VertexShader = compile vs_2_0 VSFinal();
		PixelShader = compile ps_2_0 PSFinal();
	}
}
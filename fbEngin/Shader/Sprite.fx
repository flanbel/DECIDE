/*
 *2D�`��shader
 */
//�}�g���b�N�X
float4x4	g_mWVP;

//UV
float uv_width;
float uv_height;
float uv_left;
float uv_top;

//��_
float pivotx;
float pivoty;

//�u�����h�J���[
float4 g_blendColor;
//���ߐF(��)
float4 g_killColor;

//�e�N�X�`���B
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

//���_�V�F�[�_
VS_OUTPUT vs_main(VS_INPUT In)
{
	//Out��0�ŏ�����
	VS_OUTPUT Out = (VS_OUTPUT)0;
	//�s�{�b�g����
	Out.pos = In.pos - float4(pivotx, pivoty, 0.0f, 0.0f);
	Out.pos = mul(Out.pos, g_mWVP);
	
	//UV����
	Out.uv = In.uv * float2(uv_width, uv_height) + float2(uv_left, uv_top);

	return Out;
}

/*!
* @brief	�����������p�̃s�N�Z���V�F�[�_�[�B
*/
float4 ps_main(VS_OUTPUT In) : COLOR0
{
	float4 color = tex2D(g_textureSampler, In.uv);

	//�����F�Ɠ����J���[�Ȃ�s�N�Z���L��
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
* @brief	���Z�����p�̃s�N�Z���V�F�[�_�[�B
*/
float4 PSMainAdd(VS_OUTPUT In) : COLOR0
{
	float4 tex = tex2D(g_textureSampler, In.uv);
	return float4(tex.xyz * g_blendColor.a, 1.0f / 2.5f);
}

//sprite�`��e�N�j�b�N
technique SpriteTech
{
	//����������
	pass p0
	{
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 ps_main();

		//����������
		//AlphaBlendEnable = true;
		//SrcBlend = 5;//SRCALPHA;
		//DestBlend = INVSRCALPHA;
	}
	
	//���Z����
	pass p1
	{
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 PSMainAdd();

		//����������
		/*AlphaBlendEnable = true;
		SrcBlend = ONE;
		DestBlend = ONE;*/
	}
};
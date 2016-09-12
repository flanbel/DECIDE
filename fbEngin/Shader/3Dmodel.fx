/*!
 *@brief	3D���f���̕`��
 */
bool g_Texflg;							//�e�N�X�`��
bool Toonflg;							//�g�D�[���V�F�[�_
bool Specflg;							//�X�y�L�����[���C�g
bool Fresnelflg;						//�t���l������
bool Shadowflg;							//�V���h�E�t���O

float4x4 g_rotationMatrix;				//��]�s��B�@������]�����邽�߂ɕK�v�ɂȂ�B���C�e�B���O����Ȃ�K�{�B
float4x4 g_worldMatrix;					//���[���h�s��B
float4x4 g_viewMatrix;					//�r���[�s��B
float4x4 g_projectionMatrix;			//�v���W�F�N�V�����s��B

float4x4 g_viewMatrixRotInv;			 //�J�����̉�]�s��̋t�s��

float4	 g_eyePos;						//���_�B
float4x4 g_LVP;							//���C�g�̃r���[�v���W�F�N�V�����s��

texture g_LVPTex;				//�e�N�X�`���B
sampler g_LVPTexSampler =
sampler_state
{
	Texture = <g_LVPTex>;
	MipFilter = NONE;
	MinFilter = NONE;
	MagFilter = NONE;
	AddressU = Clamp;			//�J��Ԃ��Ȃ��悤�ɂ���
	AddressV = Wrap;
};


#define DIFFUSE_LIGHT_NUM	4			//�f�B�t���[�Y���C�g�̐��B
float4	g_diffuseLightDirection[DIFFUSE_LIGHT_NUM];	//�f�B�t���[�Y���C�g�̕����B
float4	g_diffuseLightColor[DIFFUSE_LIGHT_NUM];		//�f�B�t���[�Y���C�g�̃J���[�B
float4	g_ambientLight;								//�����B

float4  g_blendColor;			//������F(�{��)

float4  g_diffuseMaterial;		//�}�e���A���J���[

texture g_Texture;				//�e�N�X�`���B
sampler g_TextureSampler = 
sampler_state
{
	Texture = <g_Texture>;
    MipFilter = NONE;
    MinFilter = NONE;
    MagFilter = NONE;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

float4 g_toonLight;				//toon���C�g
texture g_toonTexture;			//toon�e�N�X�`��
sampler g_toonTextureSampler =
sampler_state
{
	Texture = <g_toonTexture>;
	AddressU = Wrap;
	AddressV = Wrap;
};

//���_���\����

struct VS_INPUT{
	float4	pos		: POSITION;
	float4	color	: COLOR0;
	float3	normal	: NORMAL0;
	float2	uv		: TEXCOORD0;
};

struct VS_OUTPUT{
	float4	pos		: POSITION;
	float4	color	: COLOR0;
	float2	uv		: TEXCOORD0;
	float3	normal	: TEXCOORD1;
	float4	worldPos: TEXCOORD2;	//���[���h��Ԃł̒��_���W�B
	float4  posWVP	: TEXCOORD3;	//�[�x�o�����߂̃|�W�V����,pos���g���Ɠ{��ꂽ���ߎd���Ȃ������
	float4  ZCalcTex : TEXCOORD4;	// Z�l�Z�o�p�e�N�X�`��
};

/*!
 *@brief	���_�V�F�[�_�[�B
 */
VS_OUTPUT VSMain(VS_INPUT In)
{
	VS_OUTPUT Out = (VS_OUTPUT)0;
	float4 pos;
	//���f���̃��[�J����Ԃ��烏�[���h��Ԃɕϊ��B
	pos = mul( In.pos, g_worldMatrix );

	//���[���h���W�̎��̃|�W�V�����ێ�
	Out.worldPos = pos;

	pos = mul( pos, g_viewMatrix );			//���[���h��Ԃ���r���[��Ԃɕϊ��B
	pos = mul( pos, g_projectionMatrix );	//�r���[��Ԃ���ˉe��Ԃɕϊ��B

	if (Shadowflg)
	{
		Out.ZCalcTex = mul(In.pos, g_worldMatrix);	 // ���C�g�̖ڐ��ɂ�郏�[���h�r���[�ˉe�ϊ�������
		Out.ZCalcTex = mul(Out.ZCalcTex, g_LVP);	 // ���C�g�̖ڐ��ɂ�郏�[���h�r���[�ˉe�ϊ�������
	}
	
	Out.pos = pos;
	Out.posWVP = Out.pos;
	Out.color = In.color;
	Out.uv = In.uv;
	Out.normal = mul( In.normal, g_rotationMatrix );	//�@�����񂷁B
	
	return Out;
}

struct PS_OUTPUT
{
	float4 color0 : COLOR0;		//�F
	float4 color1 : COLOR1;		//�[�x
	float4 color2 : COLOR2;		//�[�x(����)
};
/*!
 *@brief	�s�N�Z���V�F�[�_�[�B
 */
PS_OUTPUT PSMain(VS_OUTPUT In)
{
	PS_OUTPUT color = (PS_OUTPUT)0;
	//�e�N�X�`���̗L��
	if (g_Texflg){
		//uv�ɒ���t��
		color.color0 = tex2D(g_TextureSampler, In.uv);
	}
	else
	{
		//�}�e���A���̃J���[�ɂ���B
		color.color0 = g_diffuseMaterial;
	}

	//�f�t���[�Y���C�g���v�Z�B
	{
		float4 dif = 0.0f;
		{
			for (int i = 0; i < DIFFUSE_LIGHT_NUM; i++){
				//0.0f�����Ȃ�0.0f��Ԃ�
				dif.xyz += max(0.0f, dot(In.normal.xyz, -g_diffuseLightDirection[i].xyz))
					* g_diffuseLightColor[i].xyz;
			}
			dif += g_ambientLight;
		}
		color.color0.xyz *= dif.xyz;
	}

	//�X�y�L�����[���C�g
	if (Specflg)
	{
		float3 spec = 0.0f;
			float3 toEyeDir = normalize(g_eyePos.xyz - In.worldPos);
			float3 R = -toEyeDir + 2.0f * dot(In.normal, toEyeDir) * In.normal;
		for (int i = 0; i < DIFFUSE_LIGHT_NUM; i++){
			//�X�y�L�����������v�Z����B
			//���˃x�N�g�����v�Z�B
			float3 L = -g_diffuseLightDirection[i].xyz;
				spec += g_diffuseLightColor[i] * pow(max(0.0f, dot(L, R)), 10) * g_diffuseLightColor[i].w;	//�X�y�L�������x�B
		}
		color.color0.xyz += spec.xyz;
	}

	//�t���l������
	if (Fresnelflg)
	{
		//�t�@�[���C�e�B���O���v�Z�B
		//�@�����J�������W�n�ɕϊ�����B
		float3 normalInCamera = mul(In.normal, g_viewMatrixRotInv);
			float f = 1.0f - abs(dot(normalInCamera, float3(0.0f, 0.0f, 1.0f)));
		//���l���������قǔ��˂���
		f = pow(f, 2.0f);
		color.color0 += f;
	}

	//�g�D�[�������_�����O
	if (Toonflg)
	{
		//�n�[�t�����o�[�g�g�U�Ɩ��ɂ�郉�C�e�B���O�v�Z
		float p = dot(In.normal.xyz, -g_toonLight.xyz);
		p = p * 0.5f + 0.5f;
		p = p * p;

		//****************************************************************
		//�g�D�[���V�F�[�_�[����
		//****************************************************************
		//�F�����e�N�Z���̂t�����Ƃ��A�g�D�[���}�b�v�e�N�X�`���[������̔��˗����擾����
		float4 toon = tex2D(g_toonTextureSampler, float2(p, 0.0f));

			//�F�����i�[����
			color.color0 *= toon;
	}

	color.color0 *= g_blendColor;

	//�f�v�X�V���h�E
	if (Shadowflg)
	{

		// ���C�g�ڐ��ɂ��Z�l�̍ĎZ�o
		float ZValue = In.ZCalcTex.z / In.ZCalcTex.w;

		// �ˉe��Ԃ�XY���W���e�N�X�`�����W�ɕϊ�
		float2 TransTexCoord;
		TransTexCoord.x = (1.0f + In.ZCalcTex.x / In.ZCalcTex.w)*0.5f;
		TransTexCoord.y = (1.0f + (-In.ZCalcTex.y) / In.ZCalcTex.w)*0.5f;

		if (TransTexCoord.x <= 1.0f && TransTexCoord.y <= 1.0f)
		{
			// ���A��Z�l���o
			float SM_Z = tex2D(g_LVPTexSampler, TransTexCoord).x;

			// �Z�o�_���V���h�E�}�b�v��Z�l�����傫����Ήe�Ɣ��f
			if (ZValue > SM_Z + 0.005f){
				color.color0.rgb = color.color0.rgb * 0.5f;
			}
		}
	}

	//�[�x�v�Z(RenderTarget1�ɏo�͂����)
	float Depth = In.posWVP.z / In.posWVP.w;

	color.color1 = Depth;
	color.color1.a = 1.0f;
	//���������[�x
	if (0.0f <= Depth && Depth < 0.25f)
	{
		color.color2.a = 4 *  Depth;
	}
	else if (0.25f < Depth && Depth < 0.75f)
	{
		color.color2.a = 1.0f;
	}
	else if (0.75f < Depth && Depth <= 1.0f)
	{
		color.color2.a = 4 * (1 - Depth);
	}
	
	//if (true){

	//	//���ɋP�x�𖄂ߍ��ށB
	//	float luminance = dot(color.xyz, float3(0.2125f, 0.7154f, 0.0721f));
	//	if (luminance > 1.0f){
	//		luminance = 1.0f / luminance;
	//	}
	//	else{
	//		luminance = 1.0f;
	//	}

	//	color.a = luminance;
	//}
	//else{
	//	color.a = 1.0f;
	//}


	//����������
	return color;
}

PS_OUTPUT PSMainMini(VS_OUTPUT In)
{
	PS_OUTPUT color = (PS_OUTPUT)0;
	//�e�N�X�`���̗L��
	if (g_Texflg){
		//uv�ɒ���t��
		color.color0 = tex2D(g_TextureSampler, In.uv);
	}
	else
	{
		//�}�e���A���̃J���[�ɂ���B
		color.color0 = g_diffuseMaterial;
	}

	//�f�t���[�Y���C�g���v�Z�B
	{
		float4 dif = 0.0f;
		{
			for (int i = 0; i < DIFFUSE_LIGHT_NUM; i++){
				//0.0f�����Ȃ�0.0f��Ԃ�
				dif.xyz += max(0.0f, dot(In.normal.xyz, -g_diffuseLightDirection[i].xyz))
					* g_diffuseLightColor[i].xyz;
			}
			dif += g_ambientLight;
		}
		color.color0.xyz *= dif.xyz;
	}

	//�[�x�v�Z(RenderTarget1�ɏo�͂����)
	float Depth = In.posWVP.z / In.posWVP.w;

	color.color1 = Depth;
	color.color1.a = 1.0f;
	//���������[�x
	if (0.0f <= Depth && Depth < 0.25f)
	{
		color.color2.a = 4 * Depth;
	}
	else if (0.25f < Depth && Depth < 0.75f)
	{
		color.color2.a = 1.0f;
	}
	else if (0.75f < Depth && Depth <= 1.0f)
	{
		color.color2.a = 4 * (1 - Depth);
	}

	//if (true){

	//	//���ɋP�x�𖄂ߍ��ށB
	//	float luminance = dot(color.xyz, float3(0.2125f, 0.7154f, 0.0721f));
	//	if (luminance > 1.0f){
	//		luminance = 1.0f / luminance;
	//	}
	//	else{
	//		luminance = 1.0f;
	//	}

	//	color.a = luminance;
	//}
	//else{
	//	color.a = 1.0f;
	//}


	//����������
	return color;
}

/*!
*@brief	�G�b�W�p���_�V�F�[�_�[�B
*/
float4 VSEdge(VS_INPUT In) : POSITION
{
	float4 pos = In.pos;
	//�@���̕����ɍL����(�G�b�W�̕��ƂȂ�)


	In.normal = mul(In.normal, g_rotationMatrix);	//�@�����񂷁B
	pos.xyz += In.normal.xyz * 1.0f;			//�@�������ɑ傫��

	pos = mul(pos, g_worldMatrix);		//���f���̃��[�J����Ԃ��烏�[���h��Ԃɕϊ��B
	pos = mul(pos, g_viewMatrix);			//���[���h��Ԃ���r���[��Ԃɕϊ��B
	pos = mul(pos, g_projectionMatrix);	//�r���[��Ԃ���ˉe��Ԃɕϊ��B

	return pos;
}
/*!
*@brief	�G�b�W�p�s�N�Z���V�F�[�_�[�B
*/
float4 PSEdge() : COLOR0
{
	//�^����
	return float4(0.0f, 0.0f, 0.0f, 1.0f);
}

////////////////////////////
//�e�N�j�b�N

//���ʂɕ`�悷��p
technique NormalRender
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSMain();
	}

	pass p1
	{
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSMainMini();
	}
}

//�G�b�W�p
technique EdgeRender
{
	pass p0
	{
		VertexShader = compile vs_2_0 VSEdge();
		PixelShader = compile ps_2_0 PSEdge();
	}
}
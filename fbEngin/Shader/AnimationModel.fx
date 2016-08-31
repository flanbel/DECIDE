/*!
 * @brief	�X�L�����f���V�F�[�_�[�B(4�{�[���X�L�j���O)
 */

bool Texflg;

//�X�L���s��B
#define MAX_MATRICES  50
float4x3    g_mWorldMatrixArray[MAX_MATRICES] : WORLDMATRIXARRAY;

float4x4 g_worldMatrix;					//���[���h�s��B
float4x4 g_viewMatrix;					//�r���[�s��B
float4x4 g_projectionMatrix;			//�v���W�F�N�V�����s��B
float4x4 g_rotationMatrix;				//��]�s��B�@������]�����邽�߂ɕK�v�ɂȂ�B���C�e�B���O����Ȃ�K�{�B

float		g_numBone;			//���̐��B

#define DIFFUSE_LIGHT_NUM	4		//�f�B�t���[�Y���C�g�̐��B
float4	g_diffuseLightDirection[DIFFUSE_LIGHT_NUM];	//�f�B�t���[�Y���C�g�̕����B
float4	g_diffuseLightColor[DIFFUSE_LIGHT_NUM];		//�f�B�t���[�Y���C�g�̃J���[�B
float4	g_ambientLight;								//�����B
float4  g_diffuseMaterial : COLOR0;					//�}�e���A���J���[

texture g_diffuseTexture;		//�f�B�t���[�Y�e�N�X�`���B
sampler g_diffuseTextureSampler = 
sampler_state
{
	Texture = <g_diffuseTexture>;
    MipFilter = NONE;
    MinFilter = NONE;
    MagFilter = NONE;
    AddressU = Wrap;
	AddressV = Wrap;
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


/*!
 * @brief	���͒��_
 */
struct VS_INPUT
{
    float4  Pos             : POSITION;
    float4  BlendWeights    : BLENDWEIGHT;
    float4  BlendIndices    : BLENDINDICES;
    float3  Normal          : NORMAL;
    float3  Tex0            : TEXCOORD0;
	float4	color	: COLOR0;
};

/*!
 * @brief	�o�͒��_�B
 */
struct VS_OUTPUT
{
	float4  Pos     : POSITION;
    float3  Normal	: NORMAL;
    float2  Tex0    : TEXCOORD0;
	float4	color	: COLOR0;
	float4  PosWVP	: TEXCOORD5;
};

VS_OUTPUT VSMain( VS_INPUT In )
{
	VS_OUTPUT o = (VS_OUTPUT)0;
	
	//�u�����h����{�[���̃C���f�b�N�X�B
	int4 IndexVector = D3DCOLORtoUBYTE4(In.BlendIndices);
	
	//�u�����h���[�g�B
	float BlendWeightsArray[4] = (float[4])In.BlendWeights;
    int   IndexArray[4]        = (int[4])IndexVector;
    float LastWeight = 0.0f;
    float3 Pos = 0.0f;
    float3 Normal = 0.0f;
	//�{�[�������[�v?
    for (int iBone = 0; iBone < g_numBone-1; iBone++)
    {
        LastWeight = LastWeight + BlendWeightsArray[iBone];
        
        Pos += mul(In.Pos, g_mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
        Normal += mul(In.Normal, g_mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
    }
    LastWeight = 1.0f - LastWeight; 

    //�H�H
	Pos += (mul(In.Pos, g_mWorldMatrixArray[IndexArray[g_numBone-1]]) * LastWeight);
    Normal += (mul(In.Normal, g_mWorldMatrixArray[IndexArray[g_numBone-1]]) * LastWeight);

	//���[���h�s��
	//Pos = mul(float4(Pos.xyz, 1.0f), g_worldMatrix);
	//�r���[�s��
	Pos = mul(float4(Pos.xyz, 1.0f), g_viewMatrix);
	//�v���W�F�N�V�����s��
	o.Pos = mul(float4(Pos.xyz, 1.0f), g_projectionMatrix);
	o.PosWVP = o.Pos;

	//�@���x�N�g�����K��
	Normal = normalize(Normal);
	o.Normal = mul(Normal, g_rotationMatrix);	//�@�����񂷁B

    o.Tex0 = In.Tex0;
	o.color = In.color;

	return o;
}

struct PS_OUTPUT
{
	float4 color0 : COLOR0;		//�F
	float4 color1 : COLOR1;		//�[�x
	float4 color2 : COLOR2;		//�[�x(����)
};

/*!
 * @brief	�s�N�Z���V�F�[�_�[�B
 */
PS_OUTPUT PSMain( VS_OUTPUT In )
{
	PS_OUTPUT output = (PS_OUTPUT)0;
	//�J���[
	if (Texflg)
	{
		output.color0 = tex2D(g_diffuseTextureSampler, In.Tex0);
	}
	else
	{
		output.color0 = g_diffuseMaterial;
	}

	//�f�t���[�Y���C�g���v�Z�B
	{
		float4 dif = 0.0f;

		for (int i = 0; i < DIFFUSE_LIGHT_NUM; i++){
			//0.0f�����Ȃ�0.0f��Ԃ�
			dif.xyz += max(0.0f, dot(In.Normal.xyz, -g_diffuseLightDirection[i].xyz))
				* g_diffuseLightColor[i].xyz;
		}
		dif += g_ambientLight;

		output.color0.xyz *= dif.xyz;
	}

	//�[�x�v�Z
	float Depth = (In.PosWVP.z / In.PosWVP.w);

	output.color1 = Depth;

	if (0.0f <= Depth && Depth < 0.25f)
	{
		output.color2.a = 4 * Depth;
	}
	else if (0.25f < Depth && Depth < 0.75f)
	{
		output.color2.a = 1.0f;
	}
	else if (0.75f < Depth && Depth <= 1.0f)
	{
		output.color2.a = 4 * (1 - Depth);
	}

	return output;
}

technique NormalRender
{
    pass p0
    {
        VertexShader = compile vs_3_0 VSMain();
        PixelShader = compile ps_3_0 PSMain();
    }
}

/*
 *3DLine�`��
 */

float4x4 g_worldMatrix;			//���[���h�s��B
float4x4 g_viewMatrix;			//�r���[�s��B
float4x4 g_projectionMatrix;	//�v���W�F�N�V�����s��B
float4x4 g_rotationMatrix;		//��]�s��B�@������]�����邽�߂ɕK�v�ɂȂ�B���C�e�B���O����Ȃ�K�{�B

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
	
	pos = mul(In.pos, g_worldMatrix);		//���f���̃��[�J����Ԃ��烏�[���h��Ԃɕϊ��B
	pos = mul(pos, g_viewMatrix);			//���[���h��Ԃ���r���[��Ԃɕϊ��B
	pos = mul(pos, g_projectionMatrix);	//�r���[��Ԃ���ˉe��Ԃɕϊ��B
	Out.pos = pos;
	Out.color = In.color;
	Out.normal = mul(In.normal, g_rotationMatrix);	//�@�����񂷁B

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
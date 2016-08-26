/*
 *2D�`��shader
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

//���_�V�F�[�_
VS_OUTPUT vs_main(VS_INPUT In)
{
	//Out��0�ŏ�����
	VS_OUTPUT Out = (VS_OUTPUT)0;
	
	//�|�W�V���������̂܂ܓn��
	Out.pos = In.pos;
	//�F�������̂܂ܓn��
	Out.color = In.color;

	return Out;
}

/*!
* @brief	�����������p�̃s�N�Z���V�F�[�_�[�B
*/
float4 ps_main(VS_OUTPUT In) : COLOR0
{
	return In.color;
}

//2D�v���~�e�B�u�`��
technique TestPrimitive
{
	//����������
	pass p0
	{
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 ps_main();
	}
};
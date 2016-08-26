#include "3DLine.h"
#include "EffectManager.h"

LPDIRECT3DVERTEXBUFFER9 C3DLine::m_Vbuf = NULL;

C3DLine::C3DLine()
{
	if (m_Vbuf == NULL)
	{
		//�P�ʃx�N�g������
		static LINEVERTEX LineV[] =
		{
			{ 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 255, 0, 0) },
			{ 1.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 255, 0, 0) },
		};

		(*graphicsDevice()).CreateVertexBuffer(sizeof(LINEVERTEX), 0, D3DFVF_LINEVERTEX, D3DPOOL_DEFAULT, &m_Vbuf, NULL);
		VOID* pVertices;
		m_Vbuf->Lock(0, sizeof(LineV), (void**)&pVertices, 0);
		memcpy(pVertices, LineV, sizeof(LineV));
		m_Vbuf->Unlock();
	}
}

void C3DLine::Start()
{
	//�G�t�F�N�g�ǂݍ���
	m_pEffect = SINSTANCE(CEffectManager)->LoadEffect("3Dline.fx");
}

void C3DLine::Update()
{
	m_Transform.UpdateTransform();
}

void C3DLine::Render()
{
	m_pEffect->SetTechnique("Line");
	m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	m_pEffect->BeginPass(0);

	////���[���h�s��̓]���B
	m_pEffect->SetMatrix("g_worldMatrix", &m_Transform.WorldMatrix());
	m_pEffect->SetMatrix("g_rotationMatrix", &m_Transform.WorldMatrix());
	//�r���[�s��̓]���B
	m_pEffect->SetMatrix("g_viewMatrix", &m_pcamera->View());
	//�v���W�F�N�V�����s��̓]���B
	m_pEffect->SetMatrix("g_projectionMatrix", &m_pcamera->Projection());

	(*graphicsDevice()).SetStreamSource(0, m_Vbuf, 0, sizeof(LINEVERTEX));
	(*graphicsDevice()).SetFVF(D3DFVF_LINEVERTEX);
	(*graphicsDevice()).DrawPrimitive(D3DPT_LINELIST, 0, 1);

	m_pEffect->EndPass();
	m_pEffect->End();
}

void C3DLine::SetLine(D3DXVECTOR3 line[])
{
	//�n�_�ƏI�_��`
	D3DXVECTOR3 start = line[0], end = line[1];
	//�e�ӂ̒����Z�o
	float x, y, z;
	x = sqrt(pow(end.x - start.x, 2));
	y = sqrt(pow(end.y - start.y, 2));
	z = sqrt(pow(end.z - start.z, 2));
	//�x�N�g���̒����̐�Βl�Z�o
	float length = fabsf(x + y + z);
	//�p�x�Z�o
	D3DXVECTOR3 ang;
	//x�Z�o
	ang.x = atan2(end.y - start.y, end.z - start.z) * 180.0f / 3.1415f;
	//y�Z�o
	ang.y = atan2(end.z - start.z, end.x - start.x) * 180.0f / 3.1415f;
	//z�Z�o
	ang.z = atan2(end.y - start.y, end.x - start.x) * 180.0f / 3.1415f;
	//�n�_�Z�b�g
	m_Transform.LocalPosition = start;
	//�T�C�Y�Z�b�g
	m_Transform.LocalScale = D3DXVECTOR3(length, 1.0f, 1.0f);
	//�p�x�Z�b�g
	//�Ȃ񂩂悭�킩��񂯂ǂ��������ɂȂ���
	m_Transform.LocalRotation = D3DXVECTOR3(0, ang.y, ang.z);

	//�X�V
	m_Transform.UpdateTransform();
}

//void C3DLine::SetCollision(BoxCollision box)
//{
//	//�{�b�N�X�̕��ێ�
//	D3DXVECTOR3 s = box.size;
//	//���C��
//	D3DXVECTOR3 line[2];
//
//	//F �O B ���
//	//L �� R �E
//	//U �� T �� 
//
//	//��O�����̒��_
//	D3DXVECTOR3 FLU = box.pos - (s / 2);
//	//��O����̒��_
//	D3DXVECTOR3 FLT = FLU;
//	FLT.y += s.y;
//	//��O�E���̒��_
//	D3DXVECTOR3 FRU = FLU;
//	FRU.x += s.x;
//	//��O�E��̒��_
//	D3DXVECTOR3 FRT = FRU;
//	FRU.y += s.y;
//
//	{
//		line[0] = FLU;
//		line[1] = FLT;
//		//���C���Z�b�g
//		SetLine(line);
//		Render();
//
//		line[0] = FLU;
//		line[1] = FRU;
//		//���C���Z�b�g
//		SetLine(line);
//		Render();
//
//		line[0] = FRU;
//		line[1] = FRT;
//		//���C���Z�b�g
//		SetLine(line);
//		Render();
//
//		line[0] = FLT;
//		line[1] = FRT;
//		//���C���Z�b�g
//		SetLine(line);
//		Render();
//	}
//}
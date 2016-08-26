#include "CobwebChart.h"

CCobwebChart::CCobwebChart(string name) :C2DObject(name)
{
	m_MaxRank = 0;
	m_ItemNum = 0;
	m_length = 0;
	m_line.SetWidth(1.0);
	m_ProtColor = D3DCOLOR_ARGB(255, 255, 0, 0);
	m_Chenge = false;
	m_Comp = true;

	m_ProtVec = nullptr;
}

void CCobwebChart::Start()
{
	//�e�N�X�`���쐬
	m_RenderT.CreateRenderTarget(&m_tex, 256, 256);
}

void CCobwebChart::Update()
{
	m_Transform.UpdateTransform();
}

void CCobwebChart::LateUpdate()
{
	for each (CText* t in m_Text)
	{
		t->Update();
	}
}

void CCobwebChart::Render()
{
	//�e�N�X�`�����Ȃ��Ƃ��̂�
	//if (m_Sprite.GetTex().pTexture == nullptr)
	{
		//�e�N�X�`���ݒ�
		//m_Sprite.SetTexture(m_tex);
		//�؂�ւ�
		//m_RenderT.SetRenderTarget(0);

		if (m_lineVec[LINETYPE::RANK].size() > 0)
		{

			//���ڐ�
			short size = m_ItemNum;
			//�i�K�����[�v
			for (short n = 1; n <= m_MaxRank; n++)
			{
				//������m��
				const short vecnum = size + 1;
				D3DXVECTOR2* vec = new D3DXVECTOR2[vecnum];

				short j = 0;
				for (short i = size * (n - 1); i < size * n; i++, j++)
				{
					vec[j] = m_lineVec[LINETYPE::RANK][i];
				}
				//�Ō�ɍŏ��̒��_�����Čq����
				vec[j] = m_lineVec[LINETYPE::RANK][size * (n - 1)];

				//�F�ύX
				D3DCOLOR color;
				(n == m_MaxRank || (n % 5) == 0) ? color = D3DCOLOR_ARGB(255, 0, 255, 0) : color = D3DCOLOR_ARGB(100, 0, 255, 0);

				m_line.DrawLine(vec, vecnum, color);
				//���
				SAFE_DELETE_ARRAY(vec);
			}
		}

		if (m_lineVec[LINETYPE::ITEM].size() > 0)
		{

			short size = m_lineVec[LINETYPE::ITEM].size();
			const short vecnum = size + 1;
			D3DXVECTOR2* vec = new D3DXVECTOR2[vecnum];
			short i;
			for (i = 0; i < size; i++)
			{
				vec[i] = m_lineVec[LINETYPE::ITEM][i];
			}
			vec[i] = m_lineVec[LINETYPE::ITEM][0];
			//�F�ύX
			m_line.DrawLine(vec, vecnum, D3DCOLOR_ARGB(255, 0, 255, 100));
			//���
			SAFE_DELETE_ARRAY(vec);
		}

		//���ɖ߂�
		//m_RenderT.BeforeRenderTarget();

		//�摜������Ă��܂��΂����K�v�Ȃ��̂ŃN���A
		//m_lineVec[LINETYPE::RANK].clear();
		//m_lineVec[LINETYPE::ITEM].clear();
	}

	//���[�_�[�`���[�g�`��
	//m_Sprite.Render(m_Transform);

	if (m_lineVec[LINETYPE::PROT].size() > 0)
	{
		short size = m_ItemNum + 1;
		short i;
		for (i = 0; i < m_ItemNum; i++)
		{
			m_ProtVec[i] = m_lineVec[LINETYPE::PROT][i];
		}
		m_ProtVec[i] = m_lineVec[LINETYPE::PROT][0];

		m_line.SetWidth(2.0f);
		m_line.DrawLine(m_ProtVec, size, m_ProtColor);
		m_line.SetWidth(1.0f);
	}

	//�e�L�X�g�`��
	for each (CText* t in m_Text)
	{
		t->Render();
	}
}

void CCobwebChart::CreateChartBase(const short itemnum, float length, short max)
{
	//�L�т�����𔽓](+�������Ɖ��ɐL�тĂ��܂�����)
	length *= -1;
	//�ێ�
	m_MaxRank = max;
	m_ItemNum = itemnum;
	m_length = length;

	//�����ꍇ�폜
	if ((short)m_Text.size() > m_ItemNum)
	{
		vector<CText*>::iterator it = m_Text.begin();
		FOR(m_ItemNum)
		{
			it++;
		}
		while (it != m_Text.end())
		{
			SAFE_DELETE(*it);
			m_Text.erase(it);
		}
	}

	//���Ԃ�v��Ȃ����낤���ǈꉞ
	if (m_lineVec[LINETYPE::RANK].size() > 0)
	{
		m_lineVec[LINETYPE::RANK].clear();
	}

	//�Ԋu
	float ang = 360.0f / m_ItemNum;
	float len = m_length / (float)m_MaxRank;

	//LINETYPE::RANK
	{
		//�i�K�����[�v
		for (short n = 1; n <= m_MaxRank; n++)
		{
			//���ڐ����[�v
			//�e���_�̍��W�����߂�
			FOR(m_ItemNum)
			{
				float theta = D3DXToRadian(ang * i);
				float x = 0.0f, y = len * n;
				/*
				�x�N�g���̉�]��?
				x' = x * cos�� - y * sin��
				y' = x * sin�� + y * cos��
				*/
				D3DXVECTOR2 vec;
				vec.x = x * cos(theta) - y * sin(theta);
				vec.y = x * sin(theta) + y * cos(theta);

				vec.x += m_Transform.Position.x;
				vec.y += m_Transform.Position.y;

				//���_�i�[
				m_lineVec[LINETYPE::RANK].push_back(vec);
			}
		}
	}

	//���Ԃ�v��Ȃ����낤���ǈꉞ
	if (m_lineVec[LINETYPE::ITEM].size() > 0)
	{
		m_lineVec[LINETYPE::ITEM].clear();
	}

	//LINETYPE::ITEM
	{
		D3DXVECTOR2 mypos = { m_Transform.Position.x, m_Transform.Position.y };
		//���ڐ����[�v
		//�e���_�̍��W�����߂�
		FOR(m_ItemNum)
		{
			//�����̃|�W�V�����i�[
			m_lineVec[LINETYPE::ITEM].push_back(mypos);
			float theta = D3DXToRadian(ang * i);
			//���ڂ܂łȂ̂Ń}�b�N�X�T�C�Y(���̃T�C�Y)
			float x = 0.0f, y = m_length;
			/*
			�x�N�g���̉�]��?
			x' = x * cos�� - y * sin��
			y' = x * sin�� + y * cos��
			*/
			D3DXVECTOR2 vec;
			vec.x = x * cos(theta) - y * sin(theta);
			vec.y = x * sin(theta) + y * cos(theta);

			vec += mypos;

			//���_�i�[
			m_lineVec[LINETYPE::ITEM].push_back(vec);
		}
	}

	if (m_ProtVec != nullptr)
	{
		//�o�^����Ă����Ȃ���
		SAFE_DELETE_ARRAY(m_ProtVec);
	}
	//����+1���z����m��
	m_ProtVec = new D3DXVECTOR2[m_ItemNum + 1];

	//�����v���b�g�����ڐ���菭�Ȃ��Ȃ珟��ɏ�����
	if ((int)m_ProtArray.size() < m_ItemNum)
	{
		//��
		short Diff = m_ItemNum - m_ProtArray.size();
		//���������ǉ�
		FOR(Diff)
		{
			m_ProtArray.push_back(0);
			m_NextProtArray.push_back(0);
		}
	}
}

void CCobwebChart::CreateChartProt()
{
	//�|�C���^���m�ۂ���Ă���Ȃ�
	if (m_lineVec[LINETYPE::PROT].size() > 0)
	{
		m_lineVec[LINETYPE::PROT].clear();
	}

	//1���ڂ�����̊p�x
	float ang = 360.0f / m_ItemNum;
	//1�i�K������̒����v�Z
	float len = m_length / m_MaxRank;
	//�]���_�󂯎��
	short rank;
	//�v���b�g�쐬
	FOR(m_ItemNum)
	{
		//�s���Ȑ���
		if (i >= (int)m_ProtArray.size())
		{
			rank = 0;
		}
		else
		{
			rank = (short)m_ProtArray[i];
		}

		//�p�x�Z�o
		float theta = D3DXToRadian(ang * i);
		float x = 0.0f, y = len * rank;
		/*
		�x�N�g���̉�]��?
		x' = x * cos�� - y * sin��
		y' = x * sin�� + y * cos��
		*/
		D3DXVECTOR2 vec;
		vec.x = x * cos(theta) - y * sin(theta);
		vec.y = x * sin(theta) + y * cos(theta);

		vec.x += m_Transform.Position.x;
		vec.y += m_Transform.Position.y;

		m_lineVec[LINETYPE::PROT].push_back(vec);

		//�ő�
		y = m_length;
		vec.x = x * cos(theta) - y * sin(theta);
		vec.y = x * sin(theta) + y * cos(theta);

		vec.x += m_Transform.Position.x;
		vec.y += m_Transform.Position.y;
	}
}

//�l�N�X�g�v���b�g�i�[
void CCobwebChart::NextProt(short* protArray)
{
	m_NextProtArray.clear();
	FOR(m_ItemNum)
	{
		//�s���Ȑ��� || ���������Ȃ��ꍇ�Ƃ���
		//0�ɂ���
		if (protArray[i] < 0)
		{
			m_NextProtArray.push_back(0);
		}
		else
		{
			m_NextProtArray.push_back(protArray[i]);
		}
	}
	//�ύX�t���O��true��
	m_Chenge = true;
	m_Comp = false;
}

//�v���b�g�̈ʒu���l�N�X�g�Ɉ�Â���֐�
//�������Ffloat ���t���[���œ��B�����邩
void CCobwebChart::UpdateProt(float F)
{
	//�ύX����Ă���Ȃ獷���擾
	if (m_Chenge)
	{
		m_DiffProtArray.clear();
		FOR(m_ItemNum)
		{
			short diff = short(m_NextProtArray[i] - m_ProtArray[i]);
			m_DiffProtArray.push_back(diff);
		}
		m_Chenge = false;
	}

	//���B���Ă��Ȃ��Ԃ̂ݍX�V
	if (!m_Comp)
	{
		FOR(m_ItemNum)
		{
			//�l�N�X�g�ɋ߂Â���
			m_ProtArray[i] += (float)m_DiffProtArray[i] * (1.0f / F);
		}

		//������x�߂��Ȃ�����
		if (fabsf(m_NextProtArray[0] - m_ProtArray[0]) < 0.5f)
		{

			//1���ڂ�����̊p�x
			float ang = 360.0f / m_ItemNum;
			//1�i�K������̒����v�Z
			float len = m_length / m_MaxRank;

			FOR(m_ItemNum)
			{
				//����ł҂�����Z�b�g����
				m_ProtArray[i] = m_NextProtArray[i];

				//���ڐ����e�L�X�g�������Ȃ��Ȃ琶��
				if ((short)m_Text.size() < m_ItemNum)
				{
					//�e�L�X�g�쐬
					CText* text = new CText();
					text->Start();
					text->SetFontSize(30);
					text->SetColor(255, 180, 0);

					//�e�L�X�g�̏ꏊ�����߂�
					{
						//�p�x�Z�o
						float theta = D3DXToRadian(ang * i);
						float x = 0.0f;

						//float y = len * m_ProtArray[i];	//�����N�̒���
						float y = m_length;					//�ő�̒���

						D3DXVECTOR2 vec;
						vec.x = x * cos(theta) - y * sin(theta);
						vec.y = x * sin(theta) + y * cos(theta);

						vec.x += m_Transform.Position.x;
						vec.y += m_Transform.Position.y;

						text->Transform()->LocalPosition = D3DXVECTOR3(vec.x, vec.y, 0.0f);
					}

					m_Text.push_back(text);
				}

				//�e�L�X�g�̐����X�V
				{
					//�K���Ɋm��
					WCHAR num[3];
					Support::IntToWchar(num, (int)m_ProtArray[i]);
					m_Text[i]->Createfont(num);
				}
			}
			m_Comp = true;
		}
	}
}
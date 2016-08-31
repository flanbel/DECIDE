#include "ObjectManager.h"

CObjectManager* CObjectManager::m_pInstance = new CObjectManager();

CGameObject* CObjectManager::Add(CGameObject* pAdd, bool leave)
{
	//�c���t���O�ݒ�
	pAdd->Leave(leave);
	//2D
	if (pAdd->Dimension() == DIMENSION::D2)
	{
		//�L���X�g���Ēǉ�
		m_2D[m_CasheIdx].push_back((C2DObject*)pAdd);
	}

	//3D
	if (pAdd->Dimension() == DIMENSION::D3)
	{
		C3DObject* d3 = (C3DObject*)pAdd;
		//�J�����Z�b�g
		d3->SetCamera(m_ppCamera);
		if (m_pLightCamera != nullptr)
		d3->SetLightCamera(m_pLightCamera);
		m_3D[m_CasheIdx].push_back(d3);
	}

	return pAdd;
}

void CObjectManager::AwakeObject()
{
	FOR(m_3D[m_CasheIdx].size())
	{
		//�������A�N�e�B�u�Ȃ�
		if (m_3D[m_CasheIdx][i]->Active())
		m_3D[m_CasheIdx][i]->Awake();
	}

	FOR(m_2D[m_CasheIdx].size())
	{
		if (m_2D[m_CasheIdx][i]->Active())
		m_2D[m_CasheIdx][i]->Awake();
	}
}

void CObjectManager::StartObject()
{
	FOR(m_3D[m_CasheIdx].size())
	{
		if (m_3D[m_CasheIdx][i]->Active())
		m_3D[m_CasheIdx][i]->Start();
	}

	FOR(m_2D[m_CasheIdx].size())
	{
		if (m_2D[m_CasheIdx][i]->Active())
		m_2D[m_CasheIdx][i]->Start();
	}
}

void CObjectManager::UpdateObject()
{
	FOR(m_3D[m_CasheIdx].size())
	{
		if (m_3D[m_CasheIdx][i]->Active())
		{
			m_3D[m_CasheIdx][i]->Update();
		}
	}

	FOR(m_2D[m_CasheIdx].size())
	{
		if (m_2D[m_CasheIdx][i]->Active())
		{
			m_2D[m_CasheIdx][i]->Update();
		}
	}
}

void CObjectManager::LateUpdateObject()
{
	FOR(m_3D[m_CasheIdx].size())
	{
		if (m_3D[m_CasheIdx][i]->Active())
		{
			m_3D[m_CasheIdx][i]->LateUpdate();
		}
	}

	FOR(m_2D[m_CasheIdx].size())
	{
		if (m_2D[m_CasheIdx][i]->Active())
		{
			m_2D[m_CasheIdx][i]->LateUpdate();
		}
	}

	//�J�����̍X�V�͍Ō�?
	if ((*m_ppCamera) != nullptr)
	{
		(*m_ppCamera)->Move();
		(*m_ppCamera)->Update();
	}
	if (m_pLightCamera != nullptr)
	{
		m_pLightCamera->Update();
	}
}

void CObjectManager::RenderObject()
{
	FOR(m_3D[m_CasheIdx].size())
	{
		if (m_3D[m_CasheIdx][i]->Active())
		{
			if (m_LightDepth.pTexture != nullptr)
			{
				m_3D[m_CasheIdx][i]->SetLightDepth(m_LightDepth);
			}
			m_3D[m_CasheIdx][i]->Render();
		}
	}

	FOR(m_2D[m_CasheIdx].size())
	{
		if (m_2D[m_CasheIdx][i]->Active())
		{
			m_2D[m_CasheIdx][i]->Render();
		}
	}
}

void CObjectManager::ReleaseObject()
{
	//2D
	{
		vector<C2DObject*>::iterator it2 = m_2D[m_CasheIdx].begin();
		//�I���܂ŌJ��Ԃ�
		while (it2 != m_2D[m_CasheIdx].end())
		{
			//�t���O���Ȃ��Ȃ�폜
			if (!(*it2)->Leave())
			{
				//(*it2)->Release();
				SAFE_DELETE(*it2);
				//�߂�l�����̃C�e���[�^
				it2 = m_2D[m_CasheIdx].erase(it2);
			}
			else
			{
				//�폜���Ȃ������ꍇ�͎��̃C�e���[�^
				it2++;
			}
		}
	};

	//3D
	{
		vector<C3DObject*>::iterator it = m_3D[m_CasheIdx].begin();
		//�I���܂ŌJ��Ԃ�
		while (it != m_3D[m_CasheIdx].end())
		{
			//�t���O���Ȃ��Ȃ�폜
			if (!(*it)->Leave())
			{
				//(*it)->Release();
				SAFE_DELETE(*it);
				//�߂�l�����̃C�e���[�^
				it = m_3D[m_CasheIdx].erase(it);
			}
			else
			{
				//�폜���Ȃ������ꍇ�͎��̃C�e���[�^
				it++;
			}
		}
	};

}

CGameObject* CObjectManager::FindObject(string name, DIMENSION d)
{
	
	switch (d)
	{
		//�����w��Ȃ�(����)
	case DNON:
		FOR(m_2D[m_CasheIdx].size())
		{
			if (name == m_2D[m_CasheIdx][i]->name())
				return m_2D[m_CasheIdx][i];
		}

		FOR(m_3D[m_CasheIdx].size())
		{
			if (name == m_3D[m_CasheIdx][i]->name())
				return m_3D[m_CasheIdx][i];
		}
		break;

		//2D�̂�
	case D2:
		FOR(m_2D[m_CasheIdx].size())
		{
			if (name == m_2D[m_CasheIdx][i]->name())
				return m_2D[m_CasheIdx][i];
		}
		break;

		//3D�̂�
	case D3:
		FOR(m_3D[m_CasheIdx].size())
		{
			if (name == m_3D[m_CasheIdx][i]->name())
				return m_3D[m_CasheIdx][i];
		}
		break;

	default:
		break;
	}

	//�f�o�b�O���̂݃G���[��f���o��
#ifdef _DEBUG
	string error = "�I�u�W�F�N�g���F" + name
		+ "\n�Ɉ�v���閼�O�����I�u�W�F�N�g�͌�����܂���ł����B\n�o�^����Ă��Ȃ����͖��O���Ԉ���Ă���\��������܂��B";
	MessageBoxA(NULL, error.c_str(), TEXT("error:�I�u�W�F�N�g�͌�����܂���ł����B"), MB_OK);
#endif //_DEBUG

	//������Ȃ���������nullptr��ԋp
	return nullptr;
}

CObjectManager* CObjectManager::getInstance()
{
	if (m_pInstance == NULL)
	{
		m_pInstance = new CObjectManager();
	}
	return m_pInstance;
}
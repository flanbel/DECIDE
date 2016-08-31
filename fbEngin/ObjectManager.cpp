#include "ObjectManager.h"

CObjectManager* CObjectManager::m_pInstance = new CObjectManager();

CGameObject* CObjectManager::Add(CGameObject* pAdd, bool leave)
{
	//残すフラグ設定
	pAdd->Leave(leave);
	//2D
	if (pAdd->Dimension() == DIMENSION::D2)
	{
		//キャストして追加
		m_2D[m_CasheIdx].push_back((C2DObject*)pAdd);
	}

	//3D
	if (pAdd->Dimension() == DIMENSION::D3)
	{
		C3DObject* d3 = (C3DObject*)pAdd;
		//カメラセット
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
		//そいつがアクティブなら
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

	//カメラの更新は最後?
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
		//終わりまで繰り返し
		while (it2 != m_2D[m_CasheIdx].end())
		{
			//フラグがないなら削除
			if (!(*it2)->Leave())
			{
				//(*it2)->Release();
				SAFE_DELETE(*it2);
				//戻り値が次のイテレータ
				it2 = m_2D[m_CasheIdx].erase(it2);
			}
			else
			{
				//削除しなかった場合は次のイテレータ
				it2++;
			}
		}
	};

	//3D
	{
		vector<C3DObject*>::iterator it = m_3D[m_CasheIdx].begin();
		//終わりまで繰り返し
		while (it != m_3D[m_CasheIdx].end())
		{
			//フラグがないなら削除
			if (!(*it)->Leave())
			{
				//(*it)->Release();
				SAFE_DELETE(*it);
				//戻り値が次のイテレータ
				it = m_3D[m_CasheIdx].erase(it);
			}
			else
			{
				//削除しなかった場合は次のイテレータ
				it++;
			}
		}
	};

}

CGameObject* CObjectManager::FindObject(string name, DIMENSION d)
{
	
	switch (d)
	{
		//次元指定なし(両方)
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

		//2Dのみ
	case D2:
		FOR(m_2D[m_CasheIdx].size())
		{
			if (name == m_2D[m_CasheIdx][i]->name())
				return m_2D[m_CasheIdx][i];
		}
		break;

		//3Dのみ
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

	//デバッグ時のみエラーを吐き出す
#ifdef _DEBUG
	string error = "オブジェクト名：" + name
		+ "\nに一致する名前を持つオブジェクトは見つかりませんでした。\n登録されていない又は名前が間違っている可能性があります。";
	MessageBoxA(NULL, error.c_str(), TEXT("error:オブジェクトは見つかりませんでした。"), MB_OK);
#endif //_DEBUG

	//見つからなかった時はnullptrを返却
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
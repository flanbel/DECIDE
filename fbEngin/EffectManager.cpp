#include "EffectManager.h"
#include "Effect.h"

CEffectManager* CEffectManager::m_pInstance = new CEffectManager();

CEffectManager::~CEffectManager()
{
	map<string, CEffect*>::iterator it = m_effectDictinary.begin();
	while (it != m_effectDictinary.end())
	{
		SAFE_RELEASE(it->second);
		it++;
	}
	m_effectDictinary.clear();
}

CEffect* CEffectManager::LoadEffect(string filename)
{
	CEffect* pEffect = nullptr;

	auto it = m_effectDictinary.find(filename);
	string filepath = "Shader/" + filename;
	//�������ɃG�t�F�N�g���o�^����ĂȂ�
	if (it == m_effectDictinary.end()) 
	{
		ID3DXEffect* effect;	//Effect�ւ̃|�C���^
		LPD3DXBUFFER  compileErrorBuffer = NULL;
		//Effect�t�@�C���ǂݍ���
		HRESULT hr = D3DXCreateEffectFromFile(
			graphicsDevice(),
			filepath.c_str(),
			NULL,
			NULL,
#ifdef _DEBUG
			D3DXSHADER_DEBUG,
#else
			D3DXSHADER_SKIPVALIDATION,
#endif
			NULL,
			&effect,
			&compileErrorBuffer
			);

		if (FAILED(hr)) {
			MessageBox(NULL, (char*)(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
		}

		pEffect = new CEffect();
		pEffect->SetEffect(effect);
		//�����ɓo�^
		m_effectDictinary[filename] = pEffect;
	}
	else
	{
		pEffect = it->second;
	}

	return pEffect;
}
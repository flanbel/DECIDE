
#ifndef _EFFECTMANAGER_H_
#define _EFFECTMANAGER_H_
class CEffect;

class CEffectManager
{
public:
	~CEffectManager();
	static CEffectManager* getInstance()
	{
		//Ç»Ç©Ç¡ÇΩèÍçáèâä˙âª
		if (m_pInstance == NULL)
		{
			m_pInstance = new CEffectManager();
		}
		return m_pInstance;
	}
	CEffect* LoadEffect(string filename);

private:
	map<string, CEffect*> m_effectDictinary;
	static CEffectManager* m_pInstance;
};
#endif //_EFFECTMANAGER_H_
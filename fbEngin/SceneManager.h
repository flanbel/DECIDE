

#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

class CScene;
//�ǉ��������Ɏ����Œǉ�
enum SCENE 
{
	NSCENE = -1,	//���̃V�[���ł��Ȃ����Ƃ����������ɂ͎g��Ȃ���
	TEST = 0,		//�e�X�g�V�[��
	TITLE,			//�^�C�g���V�[��
	MENU,			//���j���[�V�[��
	CHARASELECT,	//�L�����N�^�[�Z���N�g
	BATTLE,
};

//�V�[�����Ǘ�����N���X
class CSceneManager
{
public:
	CSceneManager()
	{
		//�L���b�V��������
		FOR(SCENECASHE_NUM)
		{
			m_Cache[i] = SCENE::NSCENE;
		}
	}
	//�V�[���̒ǉ�
	void Add(CScene* pAdd);
	//�V�[���̏��������s��
	//�I�u�W�F�N�g�}�l�[�W���[�ɒǉ�����Ă���I�u�W�F�N�g�̏�����������ɌĂяo��
	void StartScene();
	//�V�[���̍X�V���s��
	//�I�u�W�F�N�g�}�l�[�W���[�ɒǉ�����Ă���I�u�W�F�N�g�̍X�V������ɌĂяo��
	void UpdateScene();
	//�V�[���̕`����s��
	//�I�u�W�F�N�g�}�l�[�W���[�ɒǉ�����Ă���I�u�W�F�N�g�̕`�������ɌĂяo��
	void DrawScene();
	//�V�[���̐؂�ւ�
	//���̃V�[���̏������ƃA�b�v�f�[�g������ɌĂяo���Ă����B
	void ChangeScene(SCENE key);

	//�L���b�V���ǉ�
	void AddCache(SCENE scene);
	//�L���b�V���ɂ��邩�ǂ������ׂ�
	short HitCache(SCENE scene);
	//�C���X�^���X���擾
	static CSceneManager* getInstance();
private:
	SCENE m_nowScene;
	vector<CScene*> m_scenes;
	//�L���b�V���V�[��
	SCENE m_Cache[SCENECASHE_NUM];

	//���̂���ɂ���B
	static CSceneManager* m_pInstance;
};
#endif //_SCENEMANAGER_H_
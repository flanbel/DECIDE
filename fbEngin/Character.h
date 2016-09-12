
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "SkinModelData.h"
#include "Animation.h"
#include "SkinModelManager.h"

//�L�����N�^�[�̃X�e�[�^�X
struct STATE
{
	short hp;			//�̗�
	short power;		//��
	short defense;		//�h��
	short skill;		//�Z��
	short speed;		//�X�s�[�h

	STATE::STATE()
	{
		hp = 0;
		power = 0;
		defense = 0;
		skill = 0;
		speed = 0;	
	}

	STATE::STATE(short h,short p,short d,short s,short sp)
	{
		hp = h;
		power = p;
		defense = d;
		skill = s;
		speed = sp;
	}
};

enum STATE_PATTERN		//�L�����N�^�[�̍s���p�^�[���i���j
{
	STAY,		//�ҋ@
	FIGHTING,	//�t�@�C�e�B���O�|�[�Y
	WALK,		//����
	RUN,		//����
	PUNCH,		//�p���`
	KICK,		//�L�b�N
	ITEM_BRANDISH	//�A�C�e����U��
};

//�L�����N�^�[�̊��N���X
//�L�����N�^�[�̃f�[�^(���)������
//CharacterInfo�̂ق����ǂ���������
class CCharacter
{
public:
	CCharacter()
	{
		pHand = nullptr;
		m_AnimationSpeed = 1.0;
		m_Pattern = STATE_PATTERN::STAY;
	};

	~CCharacter()
	{
	}

	//���������s���֐�(��x�̂݌Ă΂��)
	virtual void Start() = 0;

	//�X�V���s���֐�
	virtual void Update() = 0;

	//�`����s���֐�
	virtual void Render() = 0;

	//���f���f�[�^�փA�N�Z�X���邽�߂̃|�C���^��Ԃ�
	CSkinModelData* GetModelData()
	{
		return &m_ModelData;
	}
	//��̃t���[���擾
	D3DXFRAME_DERIVED* GetHand()
	{
		if (pHand)
			return pHand;
		else
			return nullptr;
	}
	//�L�����N�^�[�̖��O�擾
	WCHAR* GetCharaName()
	{
		return m_CharacterName;
	}

	STATE GetState()
	{
		return m_CharaState;
	}

	//�A�j���[�V�����Đ�
	//�������Fint �A�j���[�V�����̓Y����
	//�������Ffloat �ۊǎ���
	void PlayAnimation(int animationSetIndex, float interpolateTime)
	{
		m_Animation.PlayAnimation(animationSetIndex, interpolateTime);
	}

	void SetPattern(STATE_PATTERN pat)
	{
		m_Pattern = pat;
	}
protected:
	//�L�����N�^�[�̃��f���f�[�^�̒l
	CSkinModelData m_ModelData;
	//�A�j���[�V�����Ǘ�
	CAnimation m_Animation;
	//�e�I�u�W�F�N�g�̃A�j���[�V�����R���g���[���[
	ID3DXAnimationController* m_pAnime;
	//�A�j���[�V�����Đ��X�s�[�h�{��
	float m_AnimationSpeed;

	//�L�����N�^�[�̖��O
	WCHAR* m_CharacterName;
	//��̃t���[���ւ̃|�C���^
	D3DXFRAME_DERIVED* pHand;
	//�X�e�[�^�X
	STATE m_CharaState;
	//�p�^�[��
	STATE_PATTERN m_Pattern;
};

#endif //_CHARACTER_H_
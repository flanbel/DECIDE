/*!
 * @brief	�p�[�e�B�N���B
 */
#ifndef _TKPARTICLE_H_
#define _TKPARTICLE_H_

#include "TextureManager.h"
#include "EffectManager.h"
#include "Camera.h"
#include "Random.h"
#include "Effect.h"

struct SParicleEmitParameter;

#define D3DFVF_PARTICLEVERTEX (D3DFVF_XYZW|D3DFVF_TEX1)

//�|���S������
struct ParticleVertex
{
	FLOAT x, y, z, w;
	FLOAT u, v;
};


/*!
 * @brief	�p�[�e�B�N���B
 */
class CParticle{
	enum eState {
		eStateRun,
		eStateFadeOut,
		eStateDead,
	};
private:
	//�������g���܂킷�̂�static
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	D3DXVECTOR4 m_uv;
	TEXTURE texture;					//!<�e�N�X�`���B
	CEffect*		Effect;				//!<�V�F�[�_�[�G�t�F�N�g�B
	CCamera*		camera;						//!<�J�����B
	CRandom*		random;						//!<�����B
	float			life;						//!<���C�t�B
	float			timer;						//!<�^�C�}�[�B
	D3DXVECTOR3		velocity;					//!<���x�B
	D3DXVECTOR3		position;					//!<���W�B
	D3DXVECTOR3		gravity;					//!<�d�́B
	float			rotateZ;					//!<Z������̉�]�B
	D3DXMATRIX		mWorld;						//!<���[���h�s��B
	D3DXVECTOR3		addVelocityRandomMargih;	//!<���x�̐ϕ��̂Ƃ��̃����_�����B
	bool			isDead;						//!<���S�t���O�B
	bool			isFade;						//!<���ʂƂ��Ƀt�F�[�h�A�E�g����H
	float			fadeTIme;					//!<�t�F�[�h�̎��ԁB
	eState			state;						//!<��ԁB
	float			initAlpha;					//!<�����A���t�@�B
	float			alpha;						//!<�A���t�@�B
	bool			isBillboard;				//!<�r���{�[�h�H
	D3DXVECTOR3		applyForce;					//!<�O����������́B
	float			brightness;					//!<�P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂��B
	int				alphaBlendMode;				//!<0�����������A1���Z�����B

public:
	CParticle();
	~CParticle();
	void Init(CRandom& random, CCamera& camera, const SParicleEmitParameter& param, const D3DXVECTOR3& emitPosition);
	void Start();
	void Update();
	void Render();

	bool GetDead()
	{
		return isDead;
	}
	/*!
	*@brief	�p�[�e�B�N���ɗ͂�������B
	*@param[in]	applyForce		���������Ɏg�p���闐�������@�B
	*/
	void ApplyForce(const D3DXVECTOR3& applyForce)
	{
		this->applyForce = applyForce;
	}
	
	//������F
	D3DXVECTOR3 m_BlendColor;
};

#endif //_TKPARTICLE_H_
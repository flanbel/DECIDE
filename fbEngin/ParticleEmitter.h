/*!
 * @brief	�p�[�e�B�N���̔����@�B
 */

#ifndef _TKPARTICLEEMITTER_H_
#define _TKPARTICLEEMITTER_H_

#include "Particle.h"
#include "Effect.h"
#include "Camera.h"
#include "Random.h"

/*!
* @brief	�p�[�e�B�N�������p�����[�^
*/
struct SParicleEmitParameter {
		//�������B
		void Init()
		{
			memset(this, 0, sizeof(SParicleEmitParameter));
			initAlpha = 1.0f;
			uvTableSize = 1;
			brightness = 1.0f;
			isBillboard = true;
		}
		std::string texturePath;						//!<�e�N�X�`���̃t�@�C���p�X�B
		D3DXVECTOR3	initVelocity;						//!<�����x�B
		float		life;								//!<�����B�P�ʂ͕b�B
		float		intervalTime;						//!<�������ԁB�P�ʂ͕b�B
		float		w;									//!<�p�[�e�B�N���̕��B
		float		h;									//!<�p�[�e�B�N���̍����B
		D3DXVECTOR3	initPositionRandomMargin;			//!<�����ʒu�̃����_�����B
		D3DXVECTOR3	initVelocityVelocityRandomMargin;	//!<�����x�̃����_�����B
		D3DXVECTOR3	addVelocityRandomMargih;			//!<���x�̐ϕ��̂Ƃ��̃����_�����B
		D3DXVECTOR4	uvTable[4];							//!<UV�e�[�u���B�ő�4�܂ŕێ��ł���Bx�������u�Ay�������v�Az���E����u�Aw���E����v�ɂȂ�B
		int			uvTableSize;						//!<UV�e�[�u���̃T�C�Y�B
		D3DXVECTOR3	gravity;							//!<�d�́B
		bool		isFade;								//!<���ʂƂ��Ƀt�F�[�h�A�E�g����H
		float		fadeTime;							//!<�t�F�[�h���鎞�ԁB
		float		initAlpha;							//!<�����A���t�@�l�B
		bool		isBillboard;						//!<�r���{�[�h�H
		float		brightness;							//!<�P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂��B
		int			alphaBlendMode;						//!<0�����������A1���Z�����B
		
	};
	/*!
	 * @brief	�p�[�e�B�N���̔����@
	 */
class CParticleEmitter{
public:

	/*!
	 * @brief	�R���X�g���N�^�B
	 */
	CParticleEmitter();
	/*!
	 * @brief	�f�X�g���N�^�B
	 */
	~CParticleEmitter();
	/*!
	 *@brief	�������B
	 *@param[in]	random		���������Ɏg�p���闐�������@�B
	 *@param[in]	camera		�p�[�e�B�N���̕`��Ŏg�p����J�����B
	 *@param[in]	param		�p�[�e�B�N�������p�̃p�����[�^�B
	 *@param[in]	emitPosition	�G�~�b�^�[�̍��W�B
	 */
	void Init(CRandom& random, CCamera& camera, const SParicleEmitParameter& param, const D3DXVECTOR3& emitPosition);
	void Start();
	void Update();
	void Render();
	/*!
	*@brief	�p�[�e�B�N���ɗ͂�������B
	*@param[in]	applyForce		���������Ɏg�p���闐�������@�B
	*/
	void ApplyForce(const D3DXVECTOR3& applyForce);

	void SetPos(D3DXVECTOR3 pos)
	{
		emitPosition = pos;
	}

	void BlendColor(D3DXVECTOR3 color)
	{
		m_BlendColor = color;
	}
private:
	float					timer;			//!<�^�C�}�[
	CRandom*				random;			//!<���������@�B
	CCamera*				camera;			//!<�J�����B
	SParicleEmitParameter	param;			//!<�p�����[�^�B
	D3DXVECTOR3				emitPosition;	//!<�G�~�b�^�[�̍��W�B
	std::list<CParticle*>	particleList;	//!<�p�[�e�B�N���̃��X�g�B
	std::list<CParticle*>	deleteParticleList;	//!<�폜���ꂽ�p�[�e�B�N���̃��X�g�B

	//������F
	D3DXVECTOR3 m_BlendColor;
};

#endif // _TKPARTICLEEMITTER_H_
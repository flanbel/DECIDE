/*!
 * @brief	�A�j���[�V�����N���X�B
 */
#include <memory>
#ifndef _TKANIMATION_H_
#define _TKANIMATION_H_


/*!
 * @brief	�A�j���[�V�����N���X�B
 */
class CAnimation{
public:
	/*!
	 * @brief	�R���X�g���N�^
	 */
	CAnimation() :
		pAnimController(nullptr),
		numAnimSet(0),
		isBlending(false),
		isInterpolate(false),
		numMaxTracks(0),
		interpolateTime(0.0f),
		interpolateEndTime(0.0f)
	{
	}
	/*!
	 * @brief	�f�X�g���N�^�B
	 */
	~CAnimation()
	{
	}
	/*!
	 * @brief	�������B
	 *@param[in]	anim		�A�j���[�V�����R���g���[���[�B
	 */
	void Init(ID3DXAnimationController* anim);
	/*!
	*@brief	�A�j���[�V�����̍Đ��B
	*@param[in]		animationIndex		�Đ��������A�j���[�V�����̃C���f�b�N�X�B
	*/
	void PlayAnimation(const int& animationSetIndex);
	/*!
	*@brief	�A�j���[�V�����̍Đ��B�A�j���[�V�����̕⊮���s���܂��B
	*@param[in]		animationSetIndex	�Đ��������A�j���[�V�����̃C���f�b�N�X�B
	*@param[in]		interpolateTime		��Ԏ��ԁB
	//��O�����@���[�v��
	*/
	void PlayAnimation(int animationSetIndex, float interpolateTime,int loop = -1);
#if 0
	/*!
	*@brief	�A�j���[�V�����̃u�����f�B���O�Đ��B
	*@param		animationIndex		�Đ��������A�j���[�V�����̃C���f�b�N�X�B
	*/
	void BlendAnimation(int animationSetIndex);
#endif
	/*!
	*@brief	�A�j���[�V�����Z�b�g�̎擾�B
	*/
	int GetNumAnimationSet() const
	{
		return numAnimSet;
	}
	/*!
	*@brief	�A�j���[�V�����̍X�V�B
	*@param[in]		deltaTime	�X�V���ԁB�P�ʂ͕b�B
	*/
	void Update(float deltaTime);
private:
	ID3DXAnimationController*				pAnimController;		//!<�A�j���[�V�����R���g���[���B
	int										numAnimSet;				//!<�A�j���[�V�����Z�b�g�̐��B
	std::unique_ptr<ID3DXAnimationSet*[]>	animationSets;			//!<�A�j���[�V�����Z�b�g�̔z��B
	std::unique_ptr<float[]>				blendRateTable;			//!<�u�����f�B���O���[�g�̃e�[�u���B
	int										currentAnimationSetNo;	//!<���ݍĐ����̃A�j���[�V�����g���b�N�̔ԍ��B
	int										currentTrackNo;			//!<���݂̃g���b�N�̔ԍ��B
	int										numMaxTracks;			//!<�A�j���[�V�����g���b�N�̍ő吔�B
	bool									isBlending;				//!<�A�j���[�V�����u�����f�B���O���H
	bool									isInterpolate;			//!<��Ԓ��H
	float									interpolateEndTime;		//!<��ԏI�����ԁB
	float									interpolateTime;		//!<��Ԏ��ԁB

	int										m_LoopNum;				//�A�j���[�V�����̃��[�v��
};

#endif // _TKMOTION_H_


/*!
 * @brief	アニメーションクラス。
 */
#include <memory>
#ifndef _TKANIMATION_H_
#define _TKANIMATION_H_


/*!
 * @brief	アニメーションクラス。
 */
class CAnimation{
public:
	/*!
	 * @brief	コンストラクタ
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
	 * @brief	デストラクタ。
	 */
	~CAnimation()
	{
	}
	/*!
	 * @brief	初期化。
	 *@param[in]	anim		アニメーションコントローラー。
	 */
	void Init(ID3DXAnimationController* anim);
	/*!
	*@brief	アニメーションの再生。
	*@param[in]		animationIndex		再生したいアニメーションのインデックス。
	*/
	void PlayAnimation(const int& animationSetIndex);
	/*!
	*@brief	アニメーションの再生。アニメーションの補完が行われます。
	*@param[in]		animationSetIndex	再生したいアニメーションのインデックス。
	*@param[in]		interpolateTime		補間時間。
	//第三引数　ループ数
	*/
	void PlayAnimation(int animationSetIndex, float interpolateTime,int loop = -1);
#if 0
	/*!
	*@brief	アニメーションのブレンディング再生。
	*@param		animationIndex		再生したいアニメーションのインデックス。
	*/
	void BlendAnimation(int animationSetIndex);
#endif
	/*!
	*@brief	アニメーションセットの取得。
	*/
	int GetNumAnimationSet() const
	{
		return numAnimSet;
	}
	/*!
	*@brief	アニメーションの更新。
	*@param[in]		deltaTime	更新時間。単位は秒。
	*/
	void Update(float deltaTime);
private:
	ID3DXAnimationController*				pAnimController;		//!<アニメーションコントローラ。
	int										numAnimSet;				//!<アニメーションセットの数。
	std::unique_ptr<ID3DXAnimationSet*[]>	animationSets;			//!<アニメーションセットの配列。
	std::unique_ptr<float[]>				blendRateTable;			//!<ブレンディングレートのテーブル。
	int										currentAnimationSetNo;	//!<現在再生中のアニメーショントラックの番号。
	int										currentTrackNo;			//!<現在のトラックの番号。
	int										numMaxTracks;			//!<アニメーショントラックの最大数。
	bool									isBlending;				//!<アニメーションブレンディング中？
	bool									isInterpolate;			//!<補間中？
	float									interpolateEndTime;		//!<補間終了時間。
	float									interpolateTime;		//!<補間時間。

	int										m_LoopNum;				//アニメーションのループ回数
};

#endif // _TKMOTION_H_


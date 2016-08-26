/*!
 * @brief	パーティクルの発生機。
 */

#ifndef _TKPARTICLEEMITTER_H_
#define _TKPARTICLEEMITTER_H_

#include "Particle.h"
#include "Effect.h"
#include "Camera.h"
#include "Random.h"

/*!
* @brief	パーティクル生成パラメータ
*/
struct SParicleEmitParameter {
		//初期化。
		void Init()
		{
			memset(this, 0, sizeof(SParicleEmitParameter));
			initAlpha = 1.0f;
			uvTableSize = 1;
			brightness = 1.0f;
			isBillboard = true;
		}
		std::string texturePath;						//!<テクスチャのファイルパス。
		D3DXVECTOR3	initVelocity;						//!<初速度。
		float		life;								//!<寿命。単位は秒。
		float		intervalTime;						//!<発生時間。単位は秒。
		float		w;									//!<パーティクルの幅。
		float		h;									//!<パーティクルの高さ。
		D3DXVECTOR3	initPositionRandomMargin;			//!<初期位置のランダム幅。
		D3DXVECTOR3	initVelocityVelocityRandomMargin;	//!<初速度のランダム幅。
		D3DXVECTOR3	addVelocityRandomMargih;			//!<速度の積分のときのランダム幅。
		D3DXVECTOR4	uvTable[4];							//!<UVテーブル。最大4まで保持できる。xが左上のu、yが左上のv、zが右下のu、wが右下のvになる。
		int			uvTableSize;						//!<UVテーブルのサイズ。
		D3DXVECTOR3	gravity;							//!<重力。
		bool		isFade;								//!<死ぬときにフェードアウトする？
		float		fadeTime;							//!<フェードする時間。
		float		initAlpha;							//!<初期アルファ値。
		bool		isBillboard;						//!<ビルボード？
		float		brightness;							//!<輝度。ブルームが有効になっているとこれを強くすると光が溢れます。
		int			alphaBlendMode;						//!<0半透明合成、1加算合成。
		
	};
	/*!
	 * @brief	パーティクルの発生機
	 */
class CParticleEmitter{
public:

	/*!
	 * @brief	コンストラクタ。
	 */
	CParticleEmitter();
	/*!
	 * @brief	デストラクタ。
	 */
	~CParticleEmitter();
	/*!
	 *@brief	初期化。
	 *@param[in]	random		乱数生成に使用する乱数生成機。
	 *@param[in]	camera		パーティクルの描画で使用するカメラ。
	 *@param[in]	param		パーティクル生成用のパラメータ。
	 *@param[in]	emitPosition	エミッターの座標。
	 */
	void Init(CRandom& random, CCamera& camera, const SParicleEmitParameter& param, const D3DXVECTOR3& emitPosition);
	void Start();
	void Update();
	void Render();
	/*!
	*@brief	パーティクルに力を加える。
	*@param[in]	applyForce		乱数生成に使用する乱数生成機。
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
	float					timer;			//!<タイマー
	CRandom*				random;			//!<乱数生成機。
	CCamera*				camera;			//!<カメラ。
	SParicleEmitParameter	param;			//!<パラメータ。
	D3DXVECTOR3				emitPosition;	//!<エミッターの座標。
	std::list<CParticle*>	particleList;	//!<パーティクルのリスト。
	std::list<CParticle*>	deleteParticleList;	//!<削除されたパーティクルのリスト。

	//混ぜる色
	D3DXVECTOR3 m_BlendColor;
};

#endif // _TKPARTICLEEMITTER_H_
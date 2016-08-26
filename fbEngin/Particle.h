/*!
 * @brief	パーティクル。
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

//板ポリゴン生成
struct ParticleVertex
{
	FLOAT x, y, z, w;
	FLOAT u, v;
};


/*!
 * @brief	パーティクル。
 */
class CParticle{
	enum eState {
		eStateRun,
		eStateFadeOut,
		eStateDead,
	};
private:
	//こいつを使いまわすのでstatic
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	D3DXVECTOR4 m_uv;
	TEXTURE texture;					//!<テクスチャ。
	CEffect*		Effect;				//!<シェーダーエフェクト。
	CCamera*		camera;						//!<カメラ。
	CRandom*		random;						//!<乱数。
	float			life;						//!<ライフ。
	float			timer;						//!<タイマー。
	D3DXVECTOR3		velocity;					//!<速度。
	D3DXVECTOR3		position;					//!<座標。
	D3DXVECTOR3		gravity;					//!<重力。
	float			rotateZ;					//!<Z軸周りの回転。
	D3DXMATRIX		mWorld;						//!<ワールド行列。
	D3DXVECTOR3		addVelocityRandomMargih;	//!<速度の積分のときのランダム幅。
	bool			isDead;						//!<死亡フラグ。
	bool			isFade;						//!<死ぬときにフェードアウトする？
	float			fadeTIme;					//!<フェードの時間。
	eState			state;						//!<状態。
	float			initAlpha;					//!<初期アルファ。
	float			alpha;						//!<アルファ。
	bool			isBillboard;				//!<ビルボード？
	D3DXVECTOR3		applyForce;					//!<外部から加わる力。
	float			brightness;					//!<輝度。ブルームが有効になっているとこれを強くすると光が溢れます。
	int				alphaBlendMode;				//!<0半透明合成、1加算合成。

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
	*@brief	パーティクルに力を加える。
	*@param[in]	applyForce		乱数生成に使用する乱数生成機。
	*/
	void ApplyForce(const D3DXVECTOR3& applyForce)
	{
		this->applyForce = applyForce;
	}
	
	//混ぜる色
	D3DXVECTOR3 m_BlendColor;
};

#endif //_TKPARTICLE_H_
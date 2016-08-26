/*!
 * @brief	パーティクル生成機
 */

#include "ParticleEmitter.h"

using namespace std;

CParticleEmitter::CParticleEmitter()
{
}

CParticleEmitter::~CParticleEmitter()
{
}

void CParticleEmitter::Init(CRandom& random, CCamera& camera, const SParicleEmitParameter& param, const D3DXVECTOR3& emitPosition)
{
	this->random = &random;
	this->camera = &camera;
	this->param = param;
	this->emitPosition = emitPosition;
	timer = 0.0f;
}

void CParticleEmitter::Start()
{
}

void CParticleEmitter::Update()
{
	if (timer >= param.intervalTime) {
		//パーティクルを生成。
		CParticle* p = new CParticle();
		p->Init(*random, *camera, param, emitPosition);
		p->m_BlendColor = m_BlendColor;
		timer = 0.0f;
		particleList.push_back(p);
	}
	timer += 1.0f / 60.0f;
	list<CParticle*>::iterator p = particleList.begin();
	while (p != particleList.end()){
		if ((*p)->GetDead()) {
			//メモリ解放してから
			SAFE_DELETE(*p);
			//リストから削除
			//戻り値は次のポインタ
			p = particleList.erase(p);
		}
		else {
			p++;
		}
	}

	for (auto p : particleList) {
		p->Update();
	}
}

/*!
*@brief	パーティクルに力を加える。
*@param[in]	applyForce		乱数生成に使用する乱数生成機。
*/
void CParticleEmitter::ApplyForce(const D3DXVECTOR3& applyForce)
{
	for (auto p : particleList) {
		p->ApplyForce(applyForce);
	}
}

void CParticleEmitter::Render()
{
	for (auto p : particleList) {
		p->Render();
	}
}
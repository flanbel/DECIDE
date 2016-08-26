/*!
 * @brief	�p�[�e�B�N�������@
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
		//�p�[�e�B�N���𐶐��B
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
			//������������Ă���
			SAFE_DELETE(*p);
			//���X�g����폜
			//�߂�l�͎��̃|�C���^
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
*@brief	�p�[�e�B�N���ɗ͂�������B
*@param[in]	applyForce		���������Ɏg�p���闐�������@�B
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
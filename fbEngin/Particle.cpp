/*!
 * @brief	�p�[�e�B�N���B
 */

#include "Particle.h"
#include "ParticleEmitter.h"

CParticle::CParticle()
{
	applyForce = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_BlendColor = VECTOR3_ONE;
}

CParticle::~CParticle()
{
	m_pVB->Release();
}

void CParticle::Init(CRandom& random, CCamera& camera, const SParicleEmitParameter& param, const D3DXVECTOR3& emitPosition)
{
	float halfW = param.w * 0.5f;
	float halfH = param.h * 0.5f;

	if (param.uvTableSize > 0)
	{
		m_uv = param.uvTable[random.GetRandInt() % param.uvTableSize];
	}
	else {
		m_uv = param.uvTable[0];
	}

	//���L�|������
	//if (m_pVB == NULL)
	{
		//�P�ʃ|���S��(������������)
		//��ŏ㉺���]������̂ł����č����ɂ���B
		ParticleVertex vertices[] = {
			{ -halfW, halfH, 0.0f, 1.0f, m_uv.x, m_uv.y, },//����
			{ halfW, halfH, 0.0f, 1.0f, m_uv.z, m_uv.y, },//�E��
			{ -halfW, -halfH, 0.0f, 1.0f, m_uv.x, m_uv.w, },//����
			{ halfW, -halfH, 0.0f, 1.0f, m_uv.z, m_uv.w, },//�E��
		};

		//���_����
		(*graphicsDevice()).CreateVertexBuffer(sizeof(ParticleVertex), 0, D3DFVF_PARTICLEVERTEX, D3DPOOL_DEFAULT, &m_pVB, NULL);
		VOID* pVertices;
		//
		m_pVB->Lock(0, sizeof(vertices), (void**)&pVertices, 0);
		memcpy(pVertices, vertices, sizeof(vertices));
		m_pVB->Unlock();
	}

	texture = SINSTANCE(CTextureManager)->LoadTexture(param.texturePath);

	Effect = SINSTANCE(CEffectManager)->LoadEffect("Plate.fx");

	this->camera = &camera;
	this->random = &random;
	life = param.life;
	velocity = param.initVelocity;
	//�����x�ɗ�����������B
	velocity.x += (((float)random.GetRandDouble() - 0.5f) * 2.0f) * param.initVelocityVelocityRandomMargin.x;
	velocity.y += (((float)random.GetRandDouble() - 0.5f) * 2.0f) * param.initVelocityVelocityRandomMargin.y;
	velocity.z += (((float)random.GetRandDouble() - 0.5f) * 2.0f) * param.initVelocityVelocityRandomMargin.z;
	position = emitPosition;
	position.x += (((float)random.GetRandDouble() - 0.5f) * 2.0f) * param.initPositionRandomMargin.x;
	position.y += (((float)random.GetRandDouble() - 0.5f) * 2.0f) * param.initPositionRandomMargin.y;
	position.z += (((float)random.GetRandDouble() - 0.5f) * 2.0f) * param.initPositionRandomMargin.z;
	addVelocityRandomMargih = param.addVelocityRandomMargih;
	gravity = param.gravity;
	isFade = param.isFade;
	state = eStateRun;
	initAlpha = param.initAlpha;
	alpha = initAlpha;
	fadeTIme = param.fadeTime;
	isBillboard = param.isBillboard;
	brightness = param.brightness;
	alphaBlendMode = param.alphaBlendMode;
	rotateZ = 3.14159265358979323846f * 2.0f * (float)random.GetRandDouble();
}

void CParticle::Start()
{

}
void CParticle::Update()
{
	float deltaTime = 1.0f / 60.0f;
	D3DXVECTOR3 addGrafity = gravity;
	addGrafity *= deltaTime;
	velocity += addGrafity;
	D3DXVECTOR3 force = applyForce;
	force.x += (((float)random->GetRandDouble() - 0.5f) * 2.0f) * addVelocityRandomMargih.x;
	force.y += (((float)random->GetRandDouble() - 0.5f) * 2.0f) * addVelocityRandomMargih.y;
	force.z += (((float)random->GetRandDouble() - 0.5f) * 2.0f) * addVelocityRandomMargih.z;
	force *= deltaTime;
	velocity += force;
	D3DXVECTOR3 addPos = velocity;
	addPos *= deltaTime;
	applyForce = D3DXVECTOR3(0.0f, 0.0f, 0.0f);;

	position += addPos;
	D3DXMATRIX mTrans;
	D3DXMatrixTranslation(&mTrans, position.x, position.y, position.z);

	if (isBillboard) {
		//�r���{�[�h�������s���B
		//�J�����̉�]�s��擾
		const D3DXMATRIX& mCameraRot = camera->Rotation();

		D3DXQUATERNION qRot;

		//�N�H�[�^�j�I������
		float s;
		float halfAngle = rotateZ * 0.5f;
		s = sin(halfAngle);
		qRot.w = cos(halfAngle);
		qRot.x = mCameraRot.m[2][0] * s;
		qRot.y = mCameraRot.m[2][1] * s;
		qRot.z = mCameraRot.m[2][2] * s;

		D3DXMATRIX rot;
		D3DXMatrixRotationQuaternion(&rot, &qRot);

		mWorld = mCameraRot * rot;
		mWorld = mWorld * mTrans;
	}
	else {
		mWorld = mTrans;
	}
	timer += deltaTime;
	switch (state) {
	case eStateRun:
		if (timer >= life) {
			if (isFade) {
				state = eStateFadeOut;
				timer = 0.0f;
			}
			else {
				state = eStateDead;
			}
		}
		break;
	case eStateFadeOut:{
						   float t = timer / fadeTIme;
						   timer += deltaTime;
						   alpha = initAlpha + (-initAlpha)*t;
						   if (alpha <= 0.0f) {
							   alpha = 0.0f;
							   state = eStateDead;	//���S�B
						   }
	}break;
	case eStateDead:
		isDead = true;
		break;
	}

}

void CParticle::Render()
{
	D3DXMATRIX size,pos,world,view,pro,wvp;
	//D3DXMatrixIdentity(&world);
	//�X�P�[�����O
	//D3DXMatrixScaling(&size, (float)texture.imgInfo.Width, (float)texture.imgInfo.Height, 1.0f);
	//�ړ�
	//D3DXMatrixTranslation(&pos, position.x, position.y, position.z);

	//camera->ViewMatrixUpdate();
	//camera->ProjectionMatrixUpdate();
	//���[���h�s��
	//world = size * pos;
	//�J��������f��
	wvp = mWorld * camera->View() * camera->Projection();

	//�V�F�[�_�[�K�p�J�n�B
	//���u�����h����
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	switch (alphaBlendMode)
	{
	case 0:
		(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		Effect->SetTechnique("ColorTexPrimTrans");
		break;
	case 1:
		(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		Effect->SetTechnique("ColorTexPrimAdd");
		break;
	}

	//Z�o�b�t�@
	(*graphicsDevice()).SetRenderState(D3DRS_ZENABLE, FALSE);

	Effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	Effect->BeginPass(0);
	
	Effect->SetMatrix("g_mWVP", &wvp);
	Effect->SetTexture("g_texture", texture.pTexture);

	Effect->SetVector("g_blendColor", &D3DXVECTOR4(m_BlendColor, alpha));
	Effect->SetFloat("g_brightness", brightness);

	(*graphicsDevice()).SetStreamSource(0, m_pVB, 0, sizeof(ParticleVertex));
	(*graphicsDevice()).SetFVF(D3DFVF_PARTICLEVERTEX);
	(*graphicsDevice()).DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	Effect->EndPass();
	Effect->End();
	
	//�ύX�����X�e�[�g�����ɖ߂�
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	(*graphicsDevice()).SetRenderState(D3DRS_ZENABLE, TRUE);
}
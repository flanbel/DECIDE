#include "Animation.h"

static int loopcount = 0;

void CAnimation::Init(ID3DXAnimationController* anim)
{
	pAnimController = anim;
	ID3DXAnimationSet* animSet;
	pAnimController->GetAnimationSet(0, &animSet);
	numAnimSet = pAnimController->GetMaxNumAnimationSets();
	numMaxTracks = pAnimController->GetMaxNumTracks();
	blendRateTable.reset(new float[numMaxTracks]);
	animationSets.reset(new ID3DXAnimationSet*[numAnimSet]);
	for (int i = 0; i < numMaxTracks; i++){
		blendRateTable[i] = 1.0f;
	}
	//�A�j���[�V�����Z�b�g���������B
	for (int i = 0; i < numAnimSet; i++) {
		pAnimController->GetAnimationSet(i, &animationSets[i]);
	}
}
#if 0
void CAnimation::BlendAnimation(int animationSetIndex)
{
	if (pAnimController){
		isBlending = true;
		currentTrackNo++;
		currentTrackNo %= numAnimSet;
		pAnimController->SetTrackWeight(0, 0.0f);
		pAnimController->SetTrackWeight(1, 1.0f);
		pAnimController->SetTrackSpeed(0, 1.0f);
		pAnimController->SetTrackSpeed(1, 1.0f);
		pAnimController->SetTrackEnable(currentTrackNo, TRUE);
		pAnimController->SetTrackAnimationSet(currentTrackNo, animationSets[animationSetIndex]);
	}
}
#endif
void CAnimation::PlayAnimation(const int& animationSetIndex)
{
	if (animationSetIndex < numAnimSet) {
		if (pAnimController) {
			currentAnimationSetNo = animationSetIndex;
			currentTrackNo = 0;
			//0�ԖڈȊO�̃g���b�N�͖����ɂ���B
			for (int i = 1; i < numMaxTracks; i++) {
				pAnimController->SetTrackEnable(i, FALSE);
			}
			pAnimController->SetTrackWeight(0, 1.0f);
			pAnimController->SetTrackAnimationSet(currentTrackNo, animationSets[currentAnimationSetNo]);
			pAnimController->SetTrackEnable(0, TRUE);
			pAnimController->SetTrackPosition(0, 0.0f);
		}
	}
	else {
		//TK_LOG("warning!!! animationSetIndex is over range!!!!!");
	}
}

void CAnimation::PlayAnimation(int animationSetIndex, float interpolateTime,int loop)
{
	m_LoopNum = loop;
	loopcount = 0;
	if (animationSetIndex < numAnimSet) {
		if (pAnimController) {
			//��ԊJ�n�̈�B
			isInterpolate = true;
			this->interpolateTime = 0.0f;
			interpolateEndTime = interpolateTime;
			currentTrackNo = (currentTrackNo + 1) % numMaxTracks;
			pAnimController->SetTrackAnimationSet(currentTrackNo, animationSets[animationSetIndex]);
			pAnimController->SetTrackEnable(currentTrackNo, TRUE);
			pAnimController->SetTrackSpeed(currentTrackNo, 1.0f);
			pAnimController->SetTrackPosition(currentTrackNo, 0.0f);
		}
	}
	else {
		//TK_LOG("warning!!! animationSetIndex is over range!!!!!");
	}
}

void CAnimation::Update(float deltaTime)
{
	if (pAnimController) {
		double a = animationSets[currentTrackNo]->GetPeriod();
		double b = animationSets[currentTrackNo]->GetPeriodicPosition(pAnimController->GetTime());

		pAnimController->AdvanceTime(deltaTime, NULL);

		if (isInterpolate) {
			//��Ԓ��B
			interpolateTime += deltaTime;
			float weight = 0.0f;
			if (interpolateTime > interpolateEndTime) {
				//��ԏI���B
				isInterpolate = false;
				weight = 1.0f;
				//���݂̃g���b�N�ȊO�𖳌��ɂ���B
				for (int i = 0; i < numMaxTracks; i++) {
					if (i != currentTrackNo) {
						pAnimController->SetTrackEnable(i, FALSE);
					}
				}
			}
			else {
				weight = interpolateTime / interpolateEndTime;
				float invWeight = 1.0f - weight;
				//�E�F�C�g��ݒ肵�Ă����B
				for (int i = 0; i < numMaxTracks; i++) {
					if (i != currentTrackNo) {
						pAnimController->SetTrackWeight(i, blendRateTable[i] * invWeight);
					}
					else {
						pAnimController->SetTrackWeight(i, weight);
					}
				}
			}
		}

		if (a < b + deltaTime)
		{
 			loopcount++;
		}

		if (m_LoopNum != -1 &&
			loopcount >= m_LoopNum)
		{
			pAnimController->SetTrackSpeed(currentTrackNo, 0.0f);
		}
	}
}
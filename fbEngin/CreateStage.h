
#ifndef _CREATESTAGE_H_
#define _CREATESTAGE_H_

//�t�@�C������X�e�[�W�𐶐�����N���X
class CCreateStatge
{
public:
	CCreateStatge();
	~CCreateStatge();

	//�X�e�[�W�쐬
	//�������Fconst char* �t�@�C���p�X
	void Create(const char* filepath);
	//�o�C�i���t�@�C����ǂݎ��
	//�������Fconst char* �t�@�C���p�X
	//�������Fint[] int�^�̔z��
	//��O�����Fint �z��̗v�f��
	//�߂�l�Fint �ǂݍ��񂾃f�[�^��
	int ReadBinary(const char* filepath,int* OutArray,int size);
private:

};

#endif //_CREATESTAGE_H_

#ifndef _CREATESTAGE_H_
#define _CREATESTAGE_H_

//�t�@�C������X�e�[�W�𐶐�����N���X
class CCreateStatge
{
public:
	CCreateStatge();
	~CCreateStatge();

	//�X�e�[�W�쐬
	//�������Fconst char* �t�@�C���l�[��
	void Create(const char* filename);
	//�o�C�i���t�@�C����ǂݎ��
	//�������Fconst char* �t�@�C���l�[��
	//�������Fint[] int�^�̔z��
	//��O�����Fint �z��̗v�f��
	//�߂�l�Fint �ǂݍ��񂾃f�[�^��
	int ReadBinary(const char* filepname,int* OutArray,int size);
private:

};

#endif //_CREATESTAGE_H_
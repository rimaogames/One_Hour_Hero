#pragma once
#include "define.h"
#include "Control.h"


//���b�Z�[�W��\������N���X
class Messege
{
//�ϐ�
private:
	//�O���t�B�b�N�n���h��
	int b_messege[MESSEGE::messege_num]; //���b�Z�[�W
	int number[10]; //����(�傫��)
	int number3[10];//�����i�������j

	int index; //���̃��b�Z�[�W��\������̂���ۑ�����ϐ�

	//������`�悷�鎞�Ɏg�p����ϐ�
	char buf[100]; //������ێ�����
	int num; //�����̐���ێ�����

//�֐�
public:
	Messege();
	~Messege();

	void set(int str); //���̃��b�Z�[�W��\������̂���ݒ肷��
	void set_dam(int damage); //�_���[�W�t���̃��b�Z�[�W��ݒ肷��
	void draw(); //�`��
};


#pragma once
#include "define.h"

//�p�����[�^�̕\���N���X
class Parameter
{
//�ϐ�
private:
	int parameter; //�p�����[�^�̃O���t�B�b�N�n���h��
	int number2[10]; //�����̃O���t�B�b�N�n���h��

//�֐�
private:
	void draw(p_status status); //�`��
public:
	Parameter();
	void All(p_status status); //���[�v�ōs��All�֐�
};


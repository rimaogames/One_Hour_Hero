#pragma once
#include "define.h"
#include <random>
#include <string>

//�G�̃N���X

class Enemy
{
//�ϐ�
private:

	//�O���t�B�b�N�n���h��
	int number2[10]; //����
	int slashgh;//�X���b�V��(/)
	int enemygh;//�G

	//�G�̏��
	e_status enemy;

//�֐�
public:
	Enemy();
	~Enemy();
	void e_init(int fl); //������
	bool set_damage(int e_damage); //�_���[�W�̐ݒ�
	void get_point(int *p); //�o���l�������Ɏ擾
	int  get_power(); //�G�̗͂�Ԃ�
	void draw(int d_count,int step); //�`��
	
};


#pragma once
#include "define.h"
#include "Control.h"
#include "InputKey.h"
#include "Enemy.h"
#include "Messege.h"
#include <sstream>
#include <random>


//Messege�N���X�ւ̎Q��
class Messege;


//�o�g���N���X
class Battle
{

//�ϐ�
private:
	//�C���X�^���X
	Enemy *enemy;
	Messege* messege;

	//�O���t�B�b�N�n���h��
	int backgh; //�w�i
	int efectgh[9]; //�v���C���U���G�t�F�N�g
	int magicgh[8]; //�v���C�����@�G�t�F�N�g
	int com[4]; //�R�}���h


	//���o�Ɏg�p����ϐ�
	int step;   //�G������O��
	int swing;  //��ʂ��h���
	int d_count; //�G���_��
	int pre_bx;  //1�O�̔w�i�̕`��x���W
	int pre_by;  //y���W
	int efe_cont; //�U���G�t�F�N�g���o���t���O
	int mag_cont; //���@�G�t�F�N�g���o���t���O

	//�t���O
	bool use_item; //�A�C�e�����g�p����t���O
	bool p_turn; //�v���C���̃^�[���t���O
	bool end;    //�o�g���I���t���O

	//���I��ł���R�}���h
	int now_com; 

	//�^�[�����Ǘ�����ϐ�
	int idx;
	int count;

	//�_���[�W��ێ�����ϐ�
	int e_damage;
	int p_damage;

	//�o���l
	int e_point;

//�֐�
private:

	void draw(); //�`��
	void command(); //�R�}���h
	void recover(); //���C�t��
	void levelup(int point); //���x���A�b�v

public:

	Battle();
	void init(); //�o�g��������
	void set_player_turn(bool flag); //�v���C���^�[���t���O��flag�ɂ���@
	void set_effect(int s, int d, int e, int m,int st); //�G�t�F�N�g�̐ݒ������
	void All(); //���[�v�ōs�����s�֐�

};


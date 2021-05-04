#pragma once
#include "DxLib.h"
#include <Windows.h>
#include <iostream>
#include <vector>
//�l�X�Ȓ�`�w�b�_�[

//���b�Z�[�W�{�b�N�X
#define MSG(m){\
MessageBoxA(NULL,m, "���b�Z�[�W", MB_OK);}


#define KEY 256 //�L�[�{�[�h�̎��


#define MAZE_H 9  //���H�̏c�̒���
#define MAZE_W 11 //��

#define DUNG_H 27 //�_���W�����̏c�̒���(9*3)
#define DUNG_W 33//��(11*3)

#define F_SIZE 80 //���̃p�l���̃T�C�Y

#define NUMBER1_W 27 //����1�̕�(���b�Z�[�W�Ŏg�p)
#define NUMBER2_W 13 //����2�@(�p�����[�^�Ŏg�p)
#define NUMBER3_W 23 //����3�@(���b�Z�[�W�Ŏg�p)



//�v���C���[�̏��@
struct  p_status
{
	int life; //���C�t
	int lifemax; //���C�t�ő�l
	int power; //��
	int food; //�����x
	int point; //���҂��ł���o���l
	int level; //���̃��x��
	int pointmax; //���̃��x���ɂȂ邽�߂̌o���l
	int potion; //�|�[�V����������
	int mp; //���@�Ώ�����
};

//�G�̏��@�񋓌^
struct e_status {
	int type; //�G�̎��
	int life; //���C�t
	int lifemax; //���C�t�ő�l
	int power; //��
	int point; //�o���l
	int x; //�`�悷��x���W
	int y; //�`�悷��y���W
};

//�R�}���h�񋓌^
typedef enum {
	ATTACK, //�U�� 0
	USE_POTION, //�|�[�V���� 1
	MAGIC, //���@ 2
	RUN, //������ 3
	cnum, //�R�}���h�̐� 4
}COM;


//���b�Z�[�W�񋓌^
typedef enum {
	NEW_FLOOR, //�V�����K�ɗ��� 0
	GET_POTION,//�|�[�V�����擾 1
	GET_STONE, //���@�Ύ擾 2
	GET_POISON,//�Ŏ擾 3
	GET_FOOD1, //�H�ו�1�擾�@4
	GET_FOOD2, //�H�ו�2�擾�@5
	ENCOUNTER, //�G�Ƒ����@6
	P_TUEN,    //�v���C���[�̃^�[�� 7
	P_ATTACK,  //�v���C���[�̍U���@8
	P_POTION,  //�|�[�V�����g�p 9
	P_MAGIC,   //���@�@10
	P_AVOID,   //�v���C���[����� 11
	P_RUN,     //�v���C���[���������@12
	P_NOT_RUN, //�������Ȃ����� 13
	E_ATTACK,  //�G�̍U���@14
	E_AVOID,   //�G���������@15
	DAMAGE,    //�Z�Z�_���[�W�@16
	RECOVER,   //�񕜂����@17
	NO_ITEM,   //�A�C�e���������Ă��Ȃ����� 18
	WIN,       //�������@19
	LOSE,      //�������@20
	LEVELUP,   //���x�����A�b�v�����@21
	messege_num, //���b�Z�[�W�̐��@22
}MESSEGE;


//�V�[���@�񋓌^
enum  class eScene { 
	Scene_Menu,    //���j���[���
	Scene_Game,    //�Q�[�����
	Scene_Howto,   //�V�ѕ����
	Scene_Result,  //���ʉ��
	Scene_None,   //��ʂȂ�
};

//�O���[�o���ϐ�
//�S�̂ł̃n�C�X�R�A�́H
extern int hiscore;
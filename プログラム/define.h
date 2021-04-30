#pragma once
#include "DxLib.h"
#include <Windows.h>
#include <iostream>
#include <vector>


//���b�Z�[�W�{�b�N�X
#define MSG(m){\
MessageBoxA(NULL,m, "���b�Z�[�W", MB_OK);}


#define KEY 256 //�L�[�{�[�h�̎��


#define MAZE_H 9  //���H�̏c�̒���
#define MAZE_W 11 //��

#define DUNG_H 27 //�_���W�����̏c�̒���(9*3)
#define DUNG_W 33//��(11*3)

#define F_SIZE 80 //���̃p�l���̃T�C�Y
#define NUMBER_W 27
#define NUMBER2_W 13
#define NUMBER3_W 23
struct  p_status
{
	int life;
	int lifemax;
	int power;
	int food;
	int point;
	int level;
	int pointmax;
	int potion;
	int mp;
};

struct e_status {
	int type;
	int lifemax;
	int life;
	int power;
	int point;
	int x;
	int y;
};

typedef enum {
	ATTACK,
	USE_POTION,
	MAGIC,
	RUN,
	cnum,
}COM;

typedef enum {
	NEW_FLOOR,
	GET_POTION,
	GET_STONE,
	GET_POISON,
	GET_FOOD1,
	GET_FOOD2,
	ENCOUNTER,
	P_TUEN,
	P_ATTACK,
	P_POTION,
	P_MAGIC,
	P_AVOID,
	P_RUN,
	P_NOT_RUN,
	E_ATTACK,
	E_AVOID,
	DAMAGE,
	RECOVER,
	NO_ITEM,
	WIN,
	LOSE,
	LEVELUP,
	messege_num,
}MESSEGE;

typedef enum {
	POTION,
	MAGIC_STONE,
	POISON,
	FOOD1,
	FOOD2
}ITEM;

//���
enum  class eScene {      //�񋓌^
	Scene_Menu,    //���j���[���
	Scene_Game,    //�Q�[�����
	Scene_Howto,   //�V�ѕ����
	Scene_Result,  //���ʉ��
	Scene_None,   //��ʂȂ�
};

extern int hiscore;//�S�̂ł̃n�C�X�R�A�́H
#pragma once
#include "Make_Dungeon.h"
#include "Player.h"
#include "Messege.h"
#include "Battle.h"
#include "define.h"
#include "Parameter.h"

//���ꂼ��̃N���X�ւ̎Q��
class Player;
class Make_Dungeon;
class Messege;
class Battle;
class Parameter;


//�Q�[���V�[��(�Q�[���{�҂̊Ǘ�)�N���X
class Control {

//�ϐ�
private:

	//�C���X�^���X
	Make_Dungeon* make_d;
	Player* player;
	Battle* battle;
	Messege* messege;
	Parameter* para;

	//�Q�[���i�s�Ɏg�p����ϐ�
    int idx; //���̏��
	int count; //���[�v���J�E���g

	//�O���t�B�b�N�n���h��
	int gameovergh; //�Q�[���I�[�o�[�摜
	int gameover_pgh[4]; //�Q�[���I�[�o�[���̃v���C���[�摜


	int floor; //�K�w
	int gameover_index; //�Q�[���I�[�o�[���̃v���C���[�摜�̓Y����
	bool gameend; //�Q�[���I�[�o�[���ۂ�

	//�T�E���h�n���h��
	int dungeon_bgm; //�_���W�����T����BGM
	int battle_bgm; //�o�g����BGM
	int gameover_se; //�Q�[���I�[�o�[SE
    int win_bgm; //����BGM
	int item_se; //�A�C�e���Q�b�gSE
	int stairs_se; //�K�i�����SE
	int e_attack_se; //�G�U��SE
	int p_attack_se; //�v���C���[�U��SE 
	int magic_se; //���@SE
	int recover_se; //��SE
	int run_se;   //������SE

public:
	//����炷�̂��t���O
	bool dungeon_bgm_flag;
	bool battle_bgm_flag;
	bool win_bgm_flag;
	bool gameover_se_flag;
	bool item_se_flag;
	bool stairs_se_flag;
	bool e_attack_se_flag;
	bool p_attack_se_flag;
	bool magic_se_flag;
	bool recover_se_flag;
	bool run_se_flag;

//�֐�
private:
	Control(); //�V���O���g��(�C���X�^���X2�֎~)
	~Control();
	void sound(); //���̊Ǘ��֐�

public:
	void All(); //���[�v�ōs���֐�
	void Update(); //�V�[���ړ�
	void initialize(); //������
	void finalize(); //�I������

	void player_positon(double* x, double* y); //�����Ƀv���C���[�̈ʒu��^���� 
	int dungeon_info(int x,int y);  //(x,y)�̃_���W�����̏���Ԃ�
	void set_dungeon_info(int info, int index_x, int index_y); //(index_x,index_y)�̃_���W�����̏���info�ɂ���
	void set_idx(int index); //���̏�ʂ������ɂ���(index�ɂ���)
	void get_p_status(p_status *pl); //�����Ƀv���C���[�̏���^����
	void set_p_status(p_status pl); //�v���C���[�̏��������̏��ɍX�V����
	bool set_p_damage(int damage); //�v���C���[�Ɉ������̃_���[�W��^����
	int get_floor(); //���݂̊K����Ԃ�
	static Control& Instance() {//�N���X�ÓI�ϐ��A���g�̃C���X�^���X���i�[
		static Control control;//�ÓI�ϐ��Ƃ��Đ錾
		return control;
	}

};
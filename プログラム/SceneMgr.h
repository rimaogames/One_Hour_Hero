#pragma once
#include "define.h"
#include "Menu.h"
#include "Howto.h"
#include "Result.h"
#include "SceneMgr.h"
#include "Control.h"

class Menu;
class Result;
class Howto;

//////�V�[�����Ǘ�����N���X/////////
class SceneMgr
{

//�ϐ�
private:

	//�V�[��
	static eScene Scene; //���̃V�[��
	static eScene NextScene; //���̃V�[��


	//�C���X�^���X
	Menu* menu = 0; //���j���[�V�[��
	Howto* howto = 0; //�V�ѕ������V�[��
	Result* result = 0; //���ʃV�[��


//�֐�
private:

	SceneMgr();  //�Q�̃C���X�^���X���̋֎~�i�V���O���g���j

	void initialize(eScene scene); //�������Ǘ�
	void finalize(eScene scene); //�I���̊Ǘ�


public:
	void Update(); //�V�[���ړ��Ǘ�
	void All();   //���ꂼ���All(���[�v�ԂŌĂяo���֐�)�̊Ǘ�
	void ChangeScene(eScene nextScene);  //���̃V�[���������̂��̂ɂ���

	void loop(); //Main�ŌĂяo�������s�֐�

	static SceneMgr& Instance() {//�N���X�ÓI�ϐ��A���g�̃C���X�^���X���i�[
		static SceneMgr scenemgr;//�ÓI�ϐ��Ƃ��Đ錾
		return scenemgr;
	}
};

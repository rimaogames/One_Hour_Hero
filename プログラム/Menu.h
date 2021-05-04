#pragma once
#include "define.h"
#include "SceneMgr.h"
#include "InputKey.h"



class Menu
{
	//�I������
	typedef enum { //�񋓌^
		mGame,        //�Q�[���J�n 
		mHowto,      //�V�ѕ��@
		mNum,        //�{���ڂ̐� 
	} mScene;

//�ϐ�
private:
	    
	    //�O���t�B�b�N�n���h��
		int menugraph;//���j���[���
		int cursor[6];//�J�[�\��

		
		int NowSelect;//���I�𒆂̍���
		int count; //���[�v�̃J�E���g


		int menu_bgm;//���j���[��ʂ�BGM�n���h��

		int select_sound; //�Q�[���X�^�[�g��I�񂾎��ɖ炷���y�̃n���h��
		bool selectsound_flag; //nowselect_sound��炷���̃t���O

//�֐�
private:
		void draw(); //�`��
		void sound(); //���̊Ǘ�

public:
		Menu();
		void initialize(); //������
		void finalize();//�I���̏���
		void Update(); //�V�[���̍X�V
		void All();  //���[�v�ōs���֐�
};

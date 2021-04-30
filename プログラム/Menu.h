#pragma once
#include "define.h"
class Menu
{//�I������
	typedef enum { //�񋓌^
		mGame,        //�Q�[���J�n 0
		mHowto,      //�V�ѕ��@2
		mNum,        //�{���ڂ̐� 3
	} mScene;

	//���j���[���

	private:
		int menugraph;//���j���[���

		int cursor[6];//�J�[�\��
		int NowSelect;//���I�𒆂̍���
		int count; //�J�E����

		int menu_bgm;//���j���[��ʂ�BGM�n���h��
		bool selectsound_flag; //nowselect_sound��炷���̃t���O
		int select_sound; //�Q�[���X�^�[�g��I�񂾎��ɖ炷���y�̃n���h��

	private:
		void draw(); //�`��
		void sound();
	public:
		Menu();
		void initialize(); //������
		void finalize();//�I���̏���
		void Update(); //�I�[�o�[���C�h
		void All();  //�I�[�o�[���C�h
	};

#include "define.h"
#include "InputKey.h"
#include "SceneMgr.h"
int hiscore = 1;


// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    ChangeWindowMode(TRUE);//���C�u�����ŃQ�[����ʂ�\��
    SetGraphMode(880 ,720, 32); //��ʂ̑傫���ݒ�
    
    
    if (DxLib_Init() == -1) return -1;//DX���C�u�����̏�����
    SetDrawScreen(DX_SCREEN_BACK);//���C�u�����ŕ`���𗠉�ʂ�

    //�L�[�̓��͊Ǘ��N���X�̃C���X�^���X
     InputKey input;

     //�V�[���Ǘ��N���X�̎Q��
     SceneMgr& scenemgr = SceneMgr::Instance();

     while (!ProcessMessage()) {//�E�B���h�E������܂�

	      //���C�u�����ŕ`���ʂ̑O�̉摜����(�����)
	      ClearDrawScreen();

	      //�L�[�̓��͏�Ԃ̍X�V
	      input.Update_Keystate();

          //�Q�[���̏���
          scenemgr.loop();


     	  //���C�u�����ŕ\��ʂɓ]��
	      ScreenFlip();

     }

      DxLib_End(); //DX���C�u�����̏I������
      return 0;
}
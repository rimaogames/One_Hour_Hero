#include "Menu.h"
#include "SceneMgr.h"
#include "InputKey.h"
//�R���X�g���N�^
Menu::Menu() {
	//���C�u�����ŉ摜�̃��[�h
	menugraph = LoadGraph("image/Top.jpg");
	if (LoadDivGraph("image/cursor.png", 6, 6, 1, 16, 30, cursor) == -1) {
		MSG("�G���[����(Menu)");
	}
	//��������
	count = 0;
	NowSelect = mGame; //�ŏ��̓Q�[���J�n��I��ł���i�l��0)
	//���C�u�����ŉ��f�[�^��ǂݍ���
	select_sound = LoadSoundMem("music/enter.ogg");//�I�𒆂̉�
	selectsound_flag = false;
	menu_bgm= LoadSoundMem("music//top.ogg");

}

//������
void Menu::initialize() {


	//���C�u�����ŉ摜�̃��[�h
	menugraph = LoadGraph("image/Top.jpg");

	if (LoadDivGraph("image/cursor.png", 6, 6, 1, 16, 30, cursor) == -1) {
		MSG("�G���[����");
	}
	count = 0;
	NowSelect = mGame; //�ŏ��̓Q�[���J�n��I��ł���i�l��0)
	selectsound_flag = false;
}


//�I���̏���
void Menu::finalize() {
	//���C�u�����ŉ摜�̏���
	DeleteGraph(menugraph);
	DeleteGraph(cursor[5]);
	StopSoundMem(menu_bgm);

}
//��ʂ̍X�V
void Menu::Update() {
	//ScemeMgr�̎Q��
	SceneMgr& scenemgr = SceneMgr::Instance();
	//���L�[�������ꂽ��
	if (InputKey::GetKeyPush(KEY_INPUT_DOWN)) {
		NowSelect = (NowSelect + 1) % mNum;//�I����Ԃ��������
	}
	//��L�[�������ꂽ��
	else if (InputKey::GetKeyPush(KEY_INPUT_UP)) {
		NowSelect = (NowSelect + (mNum - 1)) % mNum;//�I����Ԃ���グ��
	}
	if (InputKey::GetKeyPush(KEY_INPUT_RETURN)) {
		//���I�����Ă�����̂́H
		switch (NowSelect) {
		case mGame:
			scenemgr.ChangeScene(eScene::Scene_Game); //�V�[�����Q�[����ʂɕύX
			selectsound_flag = true;
			break;
		case mHowto:
			scenemgr.ChangeScene(eScene::Scene_Howto); //�V�[����V�ѕ���ʂɕύX
		default:
			break;
		}
	}
	if (selectsound_flag)PlaySoundMem(select_sound, DX_PLAYTYPE_BACK, TRUE);
}


void Menu::draw() {
	//�w�i
	DrawGraph(0, 0, menugraph, FALSE);

	//�J�[�\��
	int y = 450;
	switch (NowSelect) {
	case mGame:
		y = 450;
		break;
	case mHowto:
		y = 540;
	default:
		break;
	}

	int number;
	number = count % 60 / 10;//0,1,2,3�Ɠ���
	DrawGraph(170, y + 10, cursor[number], TRUE);//�`��



}
void Menu::sound() {
	if(count==0)PlaySoundMem(menu_bgm, DX_PLAYTYPE_LOOP, TRUE);
}
void Menu::All() {
	selectsound_flag = false;
	draw();
	sound();
	count++;
}
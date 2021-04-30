#include "Howto.h"
#include "SceneMgr.h"
#include "InputKey.h"

Howto::Howto() {
	howgraphgh = LoadGraph("image/Howto.jpg");    //���C�u�����ŉ摜�̃��[�h
}
Howto::~Howto() {
	DeleteGraph(howgraphgh);
}
void Howto::Update() {

	//SceneMgr�N���X�̎Q��
	SceneMgr& scenemgr = SceneMgr::Instance();
	if (InputKey::GetKeyPush(KEY_INPUT_RETURN)) {
		scenemgr.ChangeScene(eScene::Scene_Menu);//�V�[�������j���[�ɕύX
	}
}
void Howto::All() {
	DrawGraph(0, 0, howgraphgh, FALSE);
}
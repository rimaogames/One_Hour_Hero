#include "Howto.h"
#include "SceneMgr.h"
#include "InputKey.h"

Howto::Howto() {
	//���C�u�����ŉ摜�̃��[�h
	howgraphgh = LoadGraph("image/Howto.jpg");
}
Howto::~Howto() {
	//���C�u�����ŉ摜���̂Ă�
	DeleteGraph(howgraphgh);
}
void Howto::Update() {

	//SceneMgr�N���X�̎Q��
	SceneMgr& scenemgr = SceneMgr::Instance();

	//ENTER�������ꂽ��V�[�������j���[�ɕύX
	if (InputKey::GetKeyPush(KEY_INPUT_RETURN)) {

		scenemgr.ChangeScene(eScene::Scene_Menu);
	}
}

//���[�v�ōs���֐�
void Howto::All() {
	//���C�u�����ŃO���t�B�b�N�n���h����`��
	DrawGraph(0, 0, howgraphgh, FALSE);
}
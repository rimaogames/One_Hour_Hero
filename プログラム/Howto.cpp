#include "Howto.h"
#include "SceneMgr.h"
#include "InputKey.h"

Howto::Howto() {
	howgraphgh = LoadGraph("image/Howto.jpg");    //ライブラリで画像のロード
}
Howto::~Howto() {
	DeleteGraph(howgraphgh);
}
void Howto::Update() {

	//SceneMgrクラスの参照
	SceneMgr& scenemgr = SceneMgr::Instance();
	if (InputKey::GetKeyPush(KEY_INPUT_RETURN)) {
		scenemgr.ChangeScene(eScene::Scene_Menu);//シーンをメニューに変更
	}
}
void Howto::All() {
	DrawGraph(0, 0, howgraphgh, FALSE);
}
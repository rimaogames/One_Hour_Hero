#include "Howto.h"
#include "SceneMgr.h"
#include "InputKey.h"

Howto::Howto() {
	//ライブラリで画像のロード
	howgraphgh = LoadGraph("image/Howto.jpg");
}
Howto::~Howto() {
	//ライブラリで画像を捨てる
	DeleteGraph(howgraphgh);
}
void Howto::Update() {

	//SceneMgrクラスの参照
	SceneMgr& scenemgr = SceneMgr::Instance();

	//ENTERを押されたらシーンをメニューに変更
	if (InputKey::GetKeyPush(KEY_INPUT_RETURN)) {

		scenemgr.ChangeScene(eScene::Scene_Menu);
	}
}

//ループで行う関数
void Howto::All() {
	//ライブラリでグラフィックハンドルを描画
	DrawGraph(0, 0, howgraphgh, FALSE);
}
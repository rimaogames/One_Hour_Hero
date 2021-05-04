#include "Menu.h"


Menu::Menu() {

	//ライブラリで画像のロード
	menugraph = LoadGraph("image/Top.jpg");
	if (LoadDivGraph("image/cursor.png", 6, 6, 1, 16, 30, cursor) == -1) {
		MSG("エラー発生(Menu)");
	}

	//ライブラリで音データを読み込み
	select_sound = LoadSoundMem("music/enter.ogg");//選択中の音
	menu_bgm = LoadSoundMem("music//top.ogg");


	//他初期化
	count = 0;
	NowSelect = mGame; //最初はゲーム開始を選んでいる
	selectsound_flag = false;

}

/////////初期化/////////////
void Menu::initialize() {


	//ライブラリで画像のロード
	menugraph = LoadGraph("image/Top.jpg");

	if (LoadDivGraph("image/cursor.png", 6, 6, 1, 16, 30, cursor) == -1) {
		MSG("エラー発生");
	}

	//他初期化
	count = 0;
	NowSelect = mGame; //最初はゲーム開始を選んでいる（値は0)
	selectsound_flag = false;
}


/////////終了の処理//////////
void Menu::finalize() {

	//ライブラリで画像の消去
	DeleteGraph(menugraph);

	for (int i = 0; i < 5; i++) {
		DeleteGraph(cursor[i]);
	}
	//bgmの停止
	StopSoundMem(menu_bgm);

}
//////////画面の更新////////
void Menu::Update() {
	//ScemeMgrの参照
	SceneMgr& scenemgr = SceneMgr::Instance();
	//下キーが押されたら
	if (InputKey::GetKeyPush(KEY_INPUT_DOWN)) {
		NowSelect = (NowSelect + 1) % mNum;//選択状態を一つ下げる
	}
	//上キーが押されたら
	else if (InputKey::GetKeyPush(KEY_INPUT_UP)) {
		NowSelect = (NowSelect + (mNum - 1)) % mNum;//選択状態を一つ上げる
	}
	if (InputKey::GetKeyPush(KEY_INPUT_RETURN)) {
		//今選択しているものは？
		switch (NowSelect) {
		case mGame:
			scenemgr.ChangeScene(eScene::Scene_Game); //シーンをゲーム画面に変更
			selectsound_flag = true;
			break;
		case mHowto:
			scenemgr.ChangeScene(eScene::Scene_Howto); //シーンを遊び方画面に変更
		default:
			break;
		}
	}
	if (selectsound_flag)PlaySoundMem(select_sound, DX_PLAYTYPE_BACK, TRUE);
}

////////描画////////
void Menu::draw() {
	//背景
	DrawGraph(0, 0, menugraph, FALSE);

	//カーソル
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
	number = count % 60 / 10;//0,1,2,3と動く
	DrawGraph(170, y + 10, cursor[number], TRUE);//描画



}

////////音の管理////////
void Menu::sound() {
	//最初にｂｇｍを流す
	if(count==0)PlaySoundMem(menu_bgm, DX_PLAYTYPE_LOOP, TRUE);
}

//////ループで行う関数/////////
void Menu::All() {
	selectsound_flag = false;
	draw();
	sound();
	count++;
}
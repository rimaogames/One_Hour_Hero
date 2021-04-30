#include "Result.h"
#include "Control.h"
#include "SceneMgr.h"

Result::Result() {
	//ライブラリで音の読み込み
	result_bgm = LoadSoundMem("music/result.ogg");
}



//初期化
void Result::initialize() {
	//ライブラリで画像の読み込み
	LoadDivGraph("image/messege/number.png", 10, 10, 1, 27, 34, g_number);
	resultgh = LoadGraph("image/Result.jpg");
	upgh = LoadGraph("image/rehi.png");

	//結果をセット
	setresult();
	//他初期化
	rehigh_score = hiscore;
	PlaySoundMem(result_bgm, DX_PLAYTYPE_LOOP, TRUE);
}

//終了の処理
void Result::finalize(){
	DeleteGraph(g_number[9]);
	DeleteGraph(resultgh);
	DeleteGraph(upgh);
	StopSoundMem(result_bgm);
}

//結果をセット
void Result::setresult() {
	Control& cont = Control::Instance();
	rescore = cont.get_floor();
}

//描画
void Result::draw() {
	DrawGraph(0, 0, resultgh, FALSE);
	char buf[100];
	memset(buf, 0, sizeof(buf));
	int h_num = 0, s_num = 0, g_num = 0;


	s_num = sprintf_s(buf, "%d", rescore);//bufにスコアを入れる。numには文字数が入る
	for (int i = 0; i < s_num; i++) {
		//ライブラリで値の書き始めはSOCRE_X+20。にy座標45に数字を記入。
		//bufには1バイトずつ数字が格納されている。g_number[buf[i]-0]で数字のbuf[i]-を取得
		DrawGraph(700 + (i * NUMBER_W), 410, g_number[buf[i] - '0'], TRUE);
	}

	h_num = sprintf_s(buf, "%d", rehigh_score);//bufにハイスコアを入れる。numには文字数が入る
	for (int i = 0; i < h_num; i++) {
		//ライブラリで値の書き始めはSOCRE_X+20。にy座標45に数字を記入。
		//bufには1バイトずつ数字が格納されている。g_number[buf[i]-0]で数字のbuf[i]-を取得
		DrawGraph(700 + (i * NUMBER_W), 290, g_number[buf[i] - '0'], TRUE);

	}
		//ハイスコア更新ならハイスコア更新という文字を書く
	if (rescore > rehigh_score) {
		DrawGraph(150, 600, upgh, TRUE);
	}
}

//画面の更新
void Result::Update() {
	//SceneMgrクラスの参照
	SceneMgr& scenemgr = SceneMgr::Instance();
	//表示が終了してGが押されたら
	if (InputKey::GetKeyPush(KEY_INPUT_RETURN) != 0) {
		scenemgr.ChangeScene(eScene::Scene_Menu);//シーンをゲームに変更（再開）
	}


}

//実行
void Result::All() {
	//描画
	draw();
	if (rescore > rehigh_score) {
		hiscore = rescore;
	}
}

#include "Result.h"


Result::Result() {
	//ライブラリで音の読み込み
	result_bgm = LoadSoundMem("music/result.ogg");

	//他初期化(0,NULLで)
	memset(g_number, 0, sizeof(g_number));
	resultgh = NULL;
	upgh = NULL;
}



//////初期化/////////
void Result::initialize() {

	//ライブラリで画像の読み込み
	LoadDivGraph("image/messege/number.png", 10, 10, 1, 27, 34, g_number);
	resultgh = LoadGraph("image/Result.jpg");
	upgh = LoadGraph("image/rehi.png");

	//結果をセット
	set_result();

	//他初期化
	rehigh_score = hiscore; //ハイスコアに今のハイスコアをセットする

	//bgmを鳴らす
	PlaySoundMem(result_bgm, DX_PLAYTYPE_LOOP, TRUE);

}

/////////終了の処理///////
void Result::finalize(){
	//画像を捨てる
	for (int i = 0; i < 9; i++) {
		DeleteGraph(g_number[i]);
	}
	DeleteGraph(resultgh);
	DeleteGraph(upgh);

	//bgmの終了
	StopSoundMem(result_bgm);
}

/////////結果をセット///////
void Result::set_result() {

	Control& cont = Control::Instance();
	//階数の取得
	rescore = cont.get_floor();
}

////////描画///////
void Result::draw() {
	
	///ライブラリで背景画像の描画
	DrawGraph(0, 0, resultgh, FALSE);

    //スコアの描画
	char buf[100];
	memset(buf, 0, sizeof(buf));
	int h_num = 0, s_num = 0;


	//ハイスコア
	//bufにスコアを入れる。s_numには文字数が入る
	h_num = sprintf_s(buf, "%d", rehigh_score);
	//ライブラリで値の書き始めは700。
    //bufには1バイトずつ数字が格納されている。g_number[buf[i]-0]で数字のbuf[i]-を取得
	for (int i = 0; i < h_num; i++) {
		DrawGraph(700 + (i * NUMBER1_W), 290, g_number[buf[i] - '0'], TRUE);

	}

	//スコア（同様に)
	s_num = sprintf_s(buf, "%d", rescore);
	for (int i = 0; i < s_num; i++) {
		DrawGraph(700 + (i * NUMBER1_W), 410, g_number[buf[i] - '0'], TRUE);
	}

	//ハイスコア更新ならハイスコア更新という文字を書く
	if (rescore > rehigh_score) {
		DrawGraph(150, 600, upgh, TRUE);
	}
}

////////画面の更新////////////
void Result::Update() {

	//SceneMgrクラスの参照
	SceneMgr& scenemgr = SceneMgr::Instance();

	//表示が終了してGが押されたら
	if (InputKey::GetKeyPush(KEY_INPUT_RETURN) != 0) {
		scenemgr.ChangeScene(eScene::Scene_Menu); //メニュー画面に移動
	}


}

///////結果画面の処理実行/////////
void Result::All() {

	//描画
	draw();

	//ハイスコア更新
	if (rescore > rehigh_score) {
		hiscore = rescore;
	}
}

#include "Parameter.h"

Parameter::Parameter() {

	//ライブラリで画像の読み込み
	parameter = LoadGraph("image/parameter.png");

	if (LoadDivGraph("image/messege/number2.png", 10, 10, 1, 13, 17, number2) == -1) {
		MSG("エラー発生(number)");
	}
}


//////////描画//////////
void Parameter::draw(p_status status) {

	///ライブラリでパラメータの枠の画像の描画
	DrawGraph(0, 630, parameter, TRUE);

	///////////////////パラメータの数字の描画/////////////////

	//描画に使用する変数の宣言と初期化
	char buf[100];
	int hp_num=0, pow_num=0, fo_num=0, pot_num=0, mp_num=0;
	memset(buf, 0, sizeof(buf));


	//lifeの描画
	hp_num = sprintf_s(buf, "%d", status.life);//bufにハイスコアを入れる。hp_numには文字数が入る
	for (int i = 0; i < hp_num; i++) {
		//ライブラリで値の書き始めは100+数字の幅ごと,y座標645に数字を記入。
		//bufには1バイトずつ数字が格納されている。number[buf[i]-0]でbuf[i]のグラフィックハンドルを取得。描画する
		DrawGraph(100 + (i * NUMBER2_W), 640, number2[buf[i] - '0'], TRUE);
	}

	//以下同様

	//力
	pow_num = sprintf_s(buf, "%d", status.power);
	for (int i = 0; i < pow_num; i++) {
		DrawGraph(100 + (i * NUMBER2_W), 665, number2[buf[i] - '0'], TRUE);
	}

	//満腹度
	fo_num = sprintf_s(buf, "%d", status.food);
	for (int i = 0; i < fo_num; i++) {
		DrawGraph(100 + (i * NUMBER2_W), 690, number2[buf[i] - '0'], TRUE);
	}

	//ポーション
	pot_num = sprintf_s(buf, "%d", status.potion);
	for (int i = 0; i < pot_num; i++) {
		DrawGraph(270 + (i * NUMBER2_W), 640, number2[buf[i] - '0'], TRUE);
	}

	//魔法石
	mp_num = sprintf_s(buf, "%d", status.mp);
	for (int i = 0; i < mp_num; i++) {
		DrawGraph(270 + (i * NUMBER2_W), 660, number2[buf[i] - '0'], TRUE);

	}
}


//ループで行う実行関数
void Parameter::All(p_status status) {

	//引数のステータスを描画
	draw(status);
}
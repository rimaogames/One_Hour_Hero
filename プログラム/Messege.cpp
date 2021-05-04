#include "Messege.h"
#include "define.h"

Messege::Messege() {

	//ライブラリで画像の読み込み
	b_messege[0] = LoadGraph("image/messege/new_floor.png"); //MESSEGE::NEW_FLOOR,
	b_messege[1] = LoadGraph("image/messege/potion.png");    //MESSEGE::GET_POTION,
	b_messege[2] = LoadGraph("image/messege/gem.png");       //MESSEGE::GET_STONE,
	b_messege[3] = LoadGraph("image/messege/trap.png");      //MESSEGE::GET_TRAP,
	b_messege[4] = LoadGraph("image/messege/food10.png");    //MESSEGE::GET_FOOD1,
	b_messege[5] = LoadGraph("image/messege/food100.png");   //MESSEGE::GET_FOOD2,
	b_messege[6] = LoadGraph("image/messege/enco.png");      //MESSEGE::ENCOUNTER,
	b_messege[7] = LoadGraph("image/messege/pla_turn.png");  //MESSEGE::P_TUEN,
	b_messege[8] = LoadGraph("image/messege/pla_attack.png");//MESSEGE::P_ATTACK,
	b_messege[9] = LoadGraph("image/messege/recover.png");   //MESSEGE::P_POTION,
	b_messege[10] = LoadGraph("image/messege/magic.png");    //MESSEGE::P_MAGIC,
	b_messege[11] = LoadGraph("image/messege/pla_avoid.png");//MESSEGE::P_AVOID,
	b_messege[12] = LoadGraph("image/messege/do_run.png");   //MESSEGE::P_RUN,
	b_messege[13] = LoadGraph("image/messege/cant_run.png"); //MESSEGE::P_NUO_RUN,
	b_messege[14] = LoadGraph("image/messege/ene_attack.png");//MESSEGE::E_ATTACK,,
	b_messege[15] = LoadGraph("image/messege/ene_avoid.png"); //MESSEGE::E_AVOID,
	b_messege[16] = LoadGraph("image/messege/attack_string.png");//MESSEGE::DAMAGE,
	b_messege[17] = LoadGraph("image/messege/recover2.png"); //MESSEGE::RECOVER2,
	b_messege[18] = LoadGraph("image/messege/no_item.png");  //MESSEGE::NO_ITEM,
	b_messege[19] = LoadGraph("image/messege/win.png");      //MESSEGE::WIN,
	b_messege[20] = LoadGraph("image/messege/lose.png");     //MESSEGE::LOSE,
	b_messege[21] = LoadGraph("image/messege/levelup.png");  //MESSEGE::LEVELUP,
	if (LoadDivGraph("image/messege/number.png", 10, 10, 1, 27,34 , number)== -1) { 
		MSG("エラー発生(number)");
	}
	if (LoadDivGraph("image/messege/number3.png", 10, 10, 1, 23, 29, number3) == -1) {
		MSG("エラー発生(number)");
	}

	//その他初期化
	index = 0;
	num = 0;
	memset(buf, 0, sizeof(buf));
}
Messege::~Messege() {

	//画像を捨てる
	for (int i = 0; i < MESSEGE::messege_num; i++) {
		DeleteGraph(b_messege[i]);
	}
	for (int i = 0; i < 10; i++) {
		DeleteGraph(number[i]);
		DeleteGraph(number3[i]);
	}
}
/////////メッセージを設定する/////////
void Messege::set(int str) {

	//indexにメッセージの種類をセット
	index = str;

	//もし、メッセージがNEW_FLOORならば
	if (str == MESSEGE::NEW_FLOOR) {
		
		//bufとnumを初期化
		memset(buf, 0, sizeof(buf));
		num = 0;
		//Controlの参照
		Control& cont = Control::Instance();

		//bufに階数を入れる。numには文字数が入る
		num = sprintf_s(buf, "%d", cont.get_floor());
	}
}

///////ダメージありのメッセージを設定する/////////
void Messege::set_dam(int damage) {

	//indexにメッセージの種類をセット
	index = MESSEGE::DAMAGE;

	//bufとnumを初期化
	memset(buf, 0, sizeof(buf));
	num = 0;

	//bufに引数のダメージを入れる。numには文字数が入る
	num = sprintf_s(buf, "%d", damage);
}


/////////描画////////////
void Messege::draw() {

	///描画するメッセージがNEW_FLOORならば
	if (index == MESSEGE::NEW_FLOOR) 
	{

		//階数の描画
		for (int i = 0; i < num; i++) {
			//ライブラリでx座標410+i*数字の幅、y座標300に数字を記入。
			//bufには1バイトずつ数字が格納されている。number[buf[i]-0]で数字のグラフィックハンドルを取得
			DrawGraph(410 + (i * NUMBER1_W), 300, number[buf[i] - '0'], TRUE);
		}

		//ライブラリで新階層来た時の数字以外のメッセージを描画
		DrawGraph(300, 300, b_messege[index], TRUE);
	}

	//描画するメッセージがDAMAGEならば
	else if (index == MESSEGE::DAMAGE)
	{    
		//ダメージ数の描画(階数と同様にして)
		for (int i = 0; i < num; i++) {
			DrawGraph(310 + (i * NUMBER3_W), 605, number3[buf[i] - '0'], TRUE);
		}

		//ライブラリでダメージ数以外のメッセージを描画
		DrawGraph(390, 600, b_messege[index], TRUE);
	}

	//他のメッセージ
	else {

		//ライブラリでメッセージを描画
		DrawGraph(330, 600, b_messege[index], TRUE);
	}
}
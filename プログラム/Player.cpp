#include "Player.h"

Player::Player() {

	//ライブラリでplayer画像読み込み
	if (LoadDivGraph("image/Player.png", 12, 3, 4, 80, 80, playergh) == -1) {
		MSG("エラー発生(player)");
	}
	//プレイヤー画像の大きさ
	width = 80;
	height = 80;

	//プレイヤーの位置
	p_x = 4;
	p_y = 4;

	//ステータス初期化
	status.food = 100; //満腹度
	status.level = 1; //レベル
	status.life = 100; //ライフ
	status.lifemax = 100; //ライフ最大値
	status.point = 0; //経験値
	status.pointmax = 30; //経験値最大
	status.power = 50; //力
	status.potion = 0; //ポーション取得数
	status.mp = 0; //魔法石取得数

	//他初期化
	xcount = 0;
	ycount = 0;
	ix = 0;
	iy = 0;
	index = 0;


	
}

Player::~Player() {

	//画像を捨てる
	for (int i = 0; i < 12; i++) {
		DeleteGraph(playergh[i]);
	}
}
/////////移動////////
void Player::move() {

	//Controlの参照
	Control& cont = Control::Instance();

	//前の座標を保管しておく
	int pre_x = int(p_x);
	int pre_y = int(p_y);

	///////////////////押したキーによって移動/////////////////
	if (InputKey::GetKey(KEY_INPUT_UP)) { //上
		if (cont.dungeon_info(int(p_x), int(p_y) - 1) != 4) {
			p_y -= 0.1;
		}
	}
	if (InputKey::GetKey(KEY_INPUT_DOWN)) { //下
		if (cont.dungeon_info(int(p_x), int(p_y) + 1) != 4) {
			p_y += 0.1;
		}
	}
	if (InputKey::GetKey(KEY_INPUT_LEFT)) { //左
		if (cont.dungeon_info(int(p_x) - 1, int(p_y)) != 4) {
			p_x -= 0.1;
		}
	}
	if (InputKey::GetKey(KEY_INPUT_RIGHT)) { //右
		if (cont.dungeon_info(int(p_x) + 1, int(p_y)) != 4) {
			p_x += 0.1;
		}
	}

	//もし、位置が更新されたら...
	if (pre_x != int(p_x) || pre_y != int(p_y)) {

		//満腹度を1減らす
		status.food -= 1;
		if (status.food < 0) status.food = 0; //0未満は0にする

		//満腹度が0ならばライフを減らす
		if (status.food == 0) {
			status.life -= 10;
			if(status.life<0) status.life = 0; //0未満は0にする
		}
	}



	///////////////////画像を変化させる/////////////////

	//その方向キーを押している間は対応したカウンタを増やし、一定回数分カウンタが増えたなら画像を次の動作のものに切り替える
	if (InputKey::GetKey(KEY_INPUT_LEFT)) {
		if (xcount < 0) xcount = 0;
		++xcount;
	}
	if (InputKey::GetKey(KEY_INPUT_RIGHT)) {
		if (xcount > 0) xcount = 0;
		--xcount;
	}
	if (InputKey::GetKey(KEY_INPUT_UP)) {
		if (ycount < 0) ycount = 0;
		++ycount;
	}
	if (InputKey::GetKey(KEY_INPUT_DOWN)) {
		if (ycount > 0) ycount = 0;
		--ycount;
	}
	//countから画像の添字を決める
	ix = abs(xcount) % 40 / 10;//|xcount|%30/10=0から29を10で割ると0から2までの値を得る=10countごとに画像を変える 0,1,2,3と動く
	iy = abs(ycount) % 40 / 10;//|ycount|%30/10　
	if (ix == 3)ix = 1; //3を１にすることで0,1,2,1,0...と動くようにする
	if (iy == 3)iy = 1;

	//横方向
	//xcount>0は左向き。2行目の先頭添字を足す。
	if (xcount > 0) {
		ix += 3;
		index = ix;//3~5
	}
	else if (xcount < 0) {//xcoount<0は右向き。3行目の先頭添字を足す。
		ix += 6;
		index = ix;//6~8
	}


	//縦方向
	//ycount>0は上向き。4行目の先頭添字を足す。
	if (ycount > 0) {
		iy += 9;
		index = iy;//9~11
	}
	else if (ycount < 0) {//ycount<0は下向き。先頭添字は0なので何もしなくてよい。
		//iy += 0;
		index = iy;
	}


	
	//キー入力無しの時はcountをリセット
	if (InputKey::GetKey(KEY_INPUT_LEFT) != 1 && InputKey::GetKey(KEY_INPUT_RIGHT) != 1) {
		xcount = 0;
	}
	if (InputKey::GetKey(KEY_INPUT_UP) != 1 && InputKey::GetKey(KEY_INPUT_DOWN) != 1) {
		ycount = 0;
	}


}



/////////イベントを踏んだかを調べる(何か手にいれたならばTRUEを返す)////////
bool Player::check() {

	//コントロールの参照
	Control& cont = Control::Instance();
	//一様分布乱数生成器作成
	std::random_device rnd; //真の乱数
	std::mt19937 mt(rnd()); //疑似乱数生成器エンジンを真の乱数で初期化
	std::uniform_int_distribution<> rand100(0,100); //0～100の間の一様分布乱数


	//プレイヤーが宝箱を踏んだならば
	if (cont.dungeon_info(int(p_x), int(p_y)) == 1) {

		//今の場所を普通の道にする(宝箱を消す)
		cont.set_dungeon_info(0, p_x, p_y);

	    //tempに0～100の乱数
		int temp = rand100(mt);

		//tempの値でアイテムを変える
		if (temp <= 50) {               //0～50 ポーション

			//ステータスのポーション+1とget_itemにポーション取得を入れる
			status.potion += 1;
			get_item = MESSEGE::GET_POTION;

		}else
		if (50 < temp && temp<= 85) {   //51～85 魔法石
			//ステータスの魔法石+1とget_itemに魔法石取得を入れる
			status.mp += 1;
			get_item = MESSEGE::GET_STONE;

		}else
		if (85 < temp) {  //86～100 毒

			//ステータスの満腹度/2ととget_itemに毒取得を入れる
			status.food = status.food / 2;
			get_item = MESSEGE::GET_POISON;
		}
		//TUREを返す
		return true;
	}

	//繭を踏んだならば
	else if (cont.dungeon_info(int(p_x), int(p_y)) == 2) 
	{
		//今の場所を普通の道にする(繭を消す)
		cont.set_dungeon_info(0, p_x, p_y);

		//0～100の乱数を入れる
		int temp = rand100(mt);

		//tempの値でアイテムを変化
		if (temp <=40) {       //0～40 敵
		    //Controlの場面添え字を4にして戦闘に移動
			cont.set_idx(4);
			//FALSEを返す
			return false;

		}else
		if (40<temp && temp<=50 ) {    //41～50 食べ物1
			//満腹度とライフ+10
			status.food += 10;
			status.life += 10;
			if (status.life > status.lifemax) status.life = status.lifemax; //ライフは上限を超えないようにする
			//get_itemに食べ物1取得を入れる
			get_item = MESSEGE::GET_FOOD1;
			//TRUEを返す
			return true;
		}

		else
		if (50<temp) {    //51～100 食べ物2
			//満腹度+100とライフ+50
			status.food += 100;
			status.life += 50;
			if (status.life > status.lifemax) status.life = status.lifemax; //ライフは上限を超えないようにする
			//get_itemに食べ物2取得を入れる
			get_item = MESSEGE::GET_FOOD2;
			//TRUEを返す
			return true;
		}
	}
	else {
		//階段を踏んだならば
		if (cont.dungeon_info(int(p_x), int(p_y)) == 3) {
			//Controlの場面添え字を2にする
			cont.set_idx(2);
		}

		//階段　or　なにもイベント無しならば FALSEを返す
		return false;
	}
}

/////////最初の位置を設定する////////
void Player::set_init_positon() {

	//一様分布乱数生成器作成
	std::random_device rnd; //真の乱数
	std::mt19937 ran(rnd()); //疑似乱数を真の乱数で初期化
	std::uniform_int_distribution<> randH(3, DUNG_H - 4); //3～ダンジョンの高さ-4の間の一様分布乱数
	std::uniform_int_distribution<> randW(3, DUNG_W - 4); //3～ダンジョンの幅-4の間の一様分布乱数

	//Controlクラスの生成
	Control& cont = Control::Instance();

	//初期位置が決まるまで続ける
	while (1) {
		//プレイヤーの位置を乱数で決める
		p_x = randW(ran);
		p_y = randH(ran);
		//乱数で決めた位置が道(何もない)ならば設定終了
		if (cont.dungeon_info(p_x, p_y) == 0) {
			break;
		}
		
	}
}


/////////描画////////
void Player::draw() {

	//プレイヤーをindexの添え字の画像で描画する
	DrawGraph(5*F_SIZE, 5*F_SIZE-40, playergh[index], TRUE);

}

/////////ステータスを返す/////////
p_status Player::get_status() {
	return status;
}

////////プレイヤーの位置を引数に渡す//////////
void Player::get_potision(double* x, double* y) {
	*x = p_x;
	*y = p_y;
}

////////プレイヤーが何のアイテムを取得したのかを返す//////////
int  Player::get_item_info() {
	return get_item;
}

/////////生きているのかチェックする(ダンジョンない移動中に使用)//////////
bool Player::check_life() {

	//ライフが0ならばTRUEそれ以外はFALSE
	if (status.life == 0) {
		return true;
	}
	else {
		return false;
	}
}

/////////ダメージをライフにセットする(死んだならばTRUEを返す)////////
bool Player::set_damage(int damage) {

	//引数(damage)をライフから引く
	status.life -= damage;
	//0以下は0に修正
	if (status.life < 0) status.life = 0;

	//0(死んだ)ならばTRUE、生きているならばFALSEを返す
	if (status.life ==0) {
		return true;
	}
	else {
		return false;
	}
}


/////////ステータスを更新する////////
void Player::set_status(p_status pl) {

   //ステータスを引数のステータスに更新する
	status = pl;
}


/////////All（ループで行う関数)////////
bool Player::All(bool init_flag) {
	//描画する
	draw();

	//引数がFALSE(階数の移動中ではない)ならば
	if(!init_flag){
		//動く
		move();
		//checkの結果を返す
	    return check();
	}
	else {//階数の移動中ならば
		//falseを返す
		return false;
	}
}
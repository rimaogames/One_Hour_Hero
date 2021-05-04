#include "Enemy.h"

Enemy::Enemy() {

	//ライブラリで画像の読み込み
	if (LoadDivGraph("image/messege/number2.png", 10, 10, 1, 13, 17, number2) == -1) {
		MSG("エラー発生(number)");
	}
	slashgh = LoadGraph("image/messege/slash.png");
	enemygh = NULL;

	//敵のステータスを初期化
	enemy.type = 0;
	enemy.lifemax = 0;
	enemy.life = 0;
	enemy.power = 0;
	enemy.point = 0;
	enemy.x = 0;
	enemy.y = 0;

}
Enemy::~Enemy() {

	//ライブラリで画像を捨てる
	for (int i = 0; i < 10; i++) {
		DeleteGraph(number2[i]);
	}

	DeleteGraph(enemygh);
	DeleteGraph(slashgh);
}


/////////敵の初期化(引数は今の階数)/////////////
void Enemy::e_init(int fl) {

	//一様分布乱数生成器の作成
	std::random_device rnd; //真の乱数
	std::mt19937 ran(rnd()); //疑似乱数を真の乱数で初期化
	std::uniform_int_distribution<> randfloor(0, fl); //0～今の階数の間の一様分布乱数
	std::uniform_int_distribution<> rand9(0, 9); //0～9の間の一様分布乱数

	///////敵画像の読み込み////////

	//階数が10階以上ならば
	if (fl >= 10) {

		//敵のタイプは0~9でランダム
		enemy.type = rand9(ran);
	}
	//階数が9以下ならば
	else {
		//敵のタイプは0~今の階数でランダム
		enemy.type = randfloor(ran);
	}
	//文字列
	std::string temp;
	//typeから敵の画像の場所を文字列でtempに保管し、それを使用して画像読み込み
	temp = "image/enemy" + std::to_string(enemy.type) + ".png";
	enemygh = LoadGraph(temp.c_str());

	//ライブラリから画像の大きさを取得
	int w, h;
	GetGraphSize(enemygh, &w, &h);

	//敵の情報初期化
	enemy.lifemax = 50 * (enemy.type + 1) + fl * 10 + (rand9(ran) + 1) * 5; //ライフ最大値
	enemy.life = enemy.lifemax; //ライフ最大値で初期化
	enemy.power = 5 * (enemy.type + 1) + fl * 3 + (rand9(ran) + 1) * 2; //力
	enemy.point = 5 * (enemy.type + 1) + fl * 5 + (rand9(ran) + 1) * 2; //経験値
	enemy.x = 440 - w / 2; //敵を描画するx座標
	enemy.y = 560 - h;    //敵を描画するy座標

}

///////ダメージのセット/////////
bool Enemy::set_damage(int e_damage) {

	//敵がまだ生きているならば
	if (enemy.life > 0) {
		//ライフからダメージ分引く
		enemy.life -= e_damage;
	}

	//敵のライフが0以下ならば
	if (enemy.life <= 0) {
		//ライフは0にする
		enemy.life = 0;

		//TRUEを返す
		return true;
	}
	//敵のライフがまだある
	else {
		//FALSEを返す
		return false;
	}
}

//////敵の力を返す///////
int  Enemy::get_power() {
	return enemy.power;
}

///////敵の経験値を引数に渡す///////
void Enemy::get_point(int *p) {
	*p = enemy.point;
}

////////描画////////////
void Enemy::draw(int damage,int step) {

	////敵の描画/////

	//敵が生きている　かつ　敵を点滅させる用のカウント変数が0を超過
	if (enemy.life > 0 && damage > 0) {

		//敵を点滅させる用のカウント変数が2で割り切れる
		if (damage % 2 == 0) {
			//描画しない
		}
		//2で割り切れない
		else {
			//ライブラリで描画
			DrawGraph(enemy.x, enemy.y, enemygh, TRUE);
		}
	}
	//（敵が生きている　かつ）敵を点滅させる用のカウント変数が0[敵がダメージを負っていいない]
	else if (enemy.life > 0) {
		//ライブラリで敵を描画(敵が攻撃している時はyにstep(!=0）分だけ前に描画)
		DrawGraph(enemy.x, enemy.y + step, enemygh, TRUE);
	}

	///////敵の体力の描画////////

	//描画に使用する変数の宣言と初期化
	char buf[100];
	int life_num=0, max_num=0;
	memset(buf, 0, sizeof(buf));


	//lifeの描画
	life_num = sprintf_s(buf, "%d", enemy.life);//bufに敵の体力を入れる。life_numには文字数が入る
	for (int i = 0; i < life_num; i++) {
		//ライブラリで値の書き始めは100+数字の幅ごと,y座標645に数字を記入。
		//bufには1バイトずつ数字が格納されている。number[buf[i]-0]でbuf[i]のグラフィックハンドルを取得。描画する
		DrawGraph(395 + (i * NUMBER2_W), 570, number2[buf[i] - '0'], TRUE);
	}

	//lifemaxの描画
	max_num = sprintf_s(buf, "%d", enemy.lifemax);//bufに敵の最大体力を入れる。max_numには文字数が入る
	for (int i = 0; i <max_num; i++) {
	
		DrawGraph(460 + (i * NUMBER2_W), 570, number2[buf[i] - '0'], TRUE);
	}
	
	//「/」の描画
	DrawGraph(450, 570, slashgh, TRUE);
}

#include "Make_Dungeon.h"
#include "define.h"
#include "Control.h"
#include <random>
#define lengthof(a) (sizeof(a)/sizeof(*(a)))

Make_Dungeon::Make_Dungeon() {

	//////// ライブラリで色の取得///////
	SKY   = GetColor( 0, 255, 255);
	GRAY  = GetColor(96,  96,  96);
	BLACK = GetColor( 0,  0,  0);
	WHITE = GetColor(255, 255, 255);
	//////////初期化/////////
	std::fill((int*)maze, (int*)(maze + lengthof(maze)), 0);   //maze初期化
	std::fill((int*)dungeon, (int*)(dungeon + lengthof(dungeon)), 4); //dungeon初期化

    floorgh= LoadGraph("image/base.png");
	boxgh = LoadGraph("image/box.png");
	cocoongh = LoadGraph("image/cocoon.png");
	wallgh = LoadGraph("image/wall.png");
	wall2gh = LoadGraph("image/wall2.png");
	darkgh = LoadGraph("image/dark.png");
	stairsgh = LoadGraph("image/stairs.png");
	blackgh = LoadGraph("image/black.png");
	countx = 0;
	county = 0;
	count = 0;
}


//////ダンジョンの生成(棒倒し法)/////
void Make_Dungeon::make_dungeon() {

	/////////////////////迷路の生成//////////////////
	 
	//柱から壁を作る時に使う値の定義
	int XP[4] = { 0,1,0,-1 };  //[作らない、右に1マス,作らない、左に1マス]
	int YP[4] = { -1,0,1,0 };  //[下に1マス、作らない、上に1マス、作らない]


	//mazeの初期化
	std::fill((int*)maze, (int*)(maze + lengthof(maze)), 0);

	//周囲の壁の作成       
	for (int i = 0; i < MAZE_W; i++) { //上下の壁
		maze[0][i] = 1;
		maze[MAZE_H - 1][i] = 1;
	}
	for (int i = 1; i < MAZE_H - 1; i++) {  //左右の壁
		maze[i][0] = 1;
		maze[i][MAZE_W - 1] = 1;
	}
	

	//　柱の作成
	for (int i = 2; i < MAZE_H-2; i +=2) {
		for (int j = 2; j < MAZE_W - 2; j +=2) {
			maze[i][j] = 1;
		}
	}


	//柱から壁を伸ばす
	for (int i = 2; i < MAZE_H - 2; i += 2) {
		for (int j = 2; j < MAZE_W - 2; j += 2) {
			int d;
			if (j == 2) {    //1列目の柱(一番左の列)は上下左右
				d = rand() % 4; //0～3から乱数
			}
			else {    //2列目以降は左には壁を作れない(壁が一回転して通れない道を作ることを防ぐ)
				d = rand() % 3; //0～2から乱数
			}

			maze[i + YP[d]][j + XP[d]] = 1;  //乱数で出た値に添って壁を作成
		}
	}


	/////////////迷路を使用してダンジョンの生成///////////////
	
	//全体を壁にする
	std::fill((int*)dungeon, (int*)(dungeon + lengthof(dungeon)), 4); //dungeon初期化
    
	//部屋と通路の作成を配置
	for (int i = 0; i < MAZE_H - 1; i++) {
		for (int j = 0; j < MAZE_W - 1; j++) {

			//迷路の座標をダンジョンの座標に変換(3 * 3マスの中央の座標)
			int tempx = j * 3 + 1;
			int tempy = i * 3 + 1;

			//添え字のmazeが通路　
			if (maze[i][j] == 0) {

				//乱数0～99が20より下(20 %)の確率　->部屋の作成
				if (rand() % 100 < 20) {

					for (int roomy = -1; roomy < 2; roomy++) {
						for (int roomx = -1; roomx < 2; roomx++) {

							//tempx,tempyを中心とした3*3マスの部屋
							dungeon[tempy + roomy][tempx + roomx] = 0;

						}
					}


				}
				else
				{  //80 % の確率で普通の道作成

					dungeon[tempy][tempx] = 0;  //3 * 3マスの中央の座標を道にする

					//3 * 3の範囲において上下左右の道を伸ばす
					if (maze[i - 1][j] == 0)  dungeon[tempy - 1][tempx] = 0;   //迷路において上は道　→　上に道を伸ばす
					if (maze[i + 1][j] == 0)  dungeon[tempy + 1][tempx] = 0;   //下
					if (maze[i][j - 1] == 0)  dungeon[tempy][tempx - 1] = 0;   //左
					if (maze[i][j + 1] == 0)   dungeon[tempy][tempx + 1] = 0;  //右
				}

			}

		}
	}

	set_event();
	
}

void Make_Dungeon::set_event() {
	int x, y;
	std::random_device rnd;
	std::mt19937 ran(rnd());
	std::uniform_int_distribution<> randH(3, DUNG_H - 4);
	std::uniform_int_distribution<> randW(3, DUNG_W - 4);
	std::uniform_int_distribution<> rand100(0, 100);

	while (1) {
		x = randW(ran);
		y = randH(ran);
		if (dungeon[y][x] == 0) {
			for (int i = -1; i < 2; i++) {
				for (int j = -1; j < 2; j++) {
					dungeon[y + i][x + j] = 0;
				}
			}
			dungeon[y][x] = 3; //階段
			break;
		}
	}
    //70回でランダムで配置(この数字が多い程イベントの配置数は上がる)
	for (int i = 0; i < 70; i++) {
		x = randW(ran);
		y = randH(ran);
		if (dungeon[y][x] == 0) {
			int temp = rand100(ran);
			if (temp <= 20)  dungeon[y][x] = 1; //宝箱
			if (20 < temp)   dungeon[y][x] = 2; //煙
		}
	}

}
void Make_Dungeon::draw() {
	double p_x, p_y;
	//Controlの参照
	Control& cont = Control::Instance();
	cont.player_positon(&p_x, &p_y);
	//プレイヤから縦10マス横11の範囲を描画する

	for (int i = -5; i < 6; i++) {
		for (int j = -5; j < 6; j++) {

			//描画用の座標計算
			int X = (j + 5) * F_SIZE;  //床のパネルのx座標 #0～10*80
			int Y = (i + 5) * F_SIZE;  //y座標

			int tempx = int(p_x) + j;
			int tempy = int(p_y) + i;

			//tempx,tempyがダンジョンの大きさの範囲内ならば描画
			if (0 <= tempx && tempx < DUNG_W  && 0 <= tempy && tempy < DUNG_H ) {
				if (dungeon[tempy][tempx] ==0) {
					DrawGraph(X, Y, floorgh, TRUE);
				}
				else if (dungeon[tempy][tempx] == 1) {
					DrawGraph(X, Y, boxgh, TRUE);
				}
				else if (dungeon[tempy][tempx] == 2) {
					DrawGraph(X, Y, cocoongh, TRUE);
				}
				else if (dungeon[tempy][tempx] == 3) {
					DrawGraph(X, Y, stairsgh, TRUE);
				}
				else if (dungeon[tempy][tempx] == 4) {
					DrawGraph(X, Y-40, wallgh, TRUE);
					if (tempy >= 1 && dungeon[tempy - 1][tempx] == 4) {
						DrawGraph(X, Y-80, wall2gh, TRUE);
					}
				}
			}
		}
	}
	DrawGraph(0, 0, darkgh, TRUE);
	
}
void Make_Dungeon::next_floor() {
	if (count < 556) {
		if (count >= 0 && count < 256) {
			SetDrawBright(255 - count, 255 - count, 255 - count);
		}
		if (count == 256)
		{
			make_dungeon();
		}
		if (count >= 300 ) {
			SetDrawBright(count - 300, count - 300, count - 300);
		}
		count +=4;
	}
	else
		if (count == 556) {
			count = 0;
		}
}

int Make_Dungeon::get_dungeon_info(int index_x,int index_y) {
	return dungeon[index_y][index_x];
}

void Make_Dungeon::set_dungeon_info(int info, int index_x, int index_y) {
	dungeon[index_y][index_x] = info;
}

void Make_Dungeon::All () {
	draw();
}



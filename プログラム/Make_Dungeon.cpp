#include "Make_Dungeon.h"
#include "define.h"
#include "Control.h"
#include <random>
#define lengthof(a) (sizeof(a)/sizeof(*(a)))

Make_Dungeon::Make_Dungeon() {

	//////// ���C�u�����ŐF�̎擾///////
	SKY   = GetColor( 0, 255, 255);
	GRAY  = GetColor(96,  96,  96);
	BLACK = GetColor( 0,  0,  0);
	WHITE = GetColor(255, 255, 255);
	//////////������/////////
	std::fill((int*)maze, (int*)(maze + lengthof(maze)), 0);   //maze������
	std::fill((int*)dungeon, (int*)(dungeon + lengthof(dungeon)), 4); //dungeon������

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


//////�_���W�����̐���(�_�|���@)/////
void Make_Dungeon::make_dungeon() {

	/////////////////////���H�̐���//////////////////
	 
	//������ǂ���鎞�Ɏg���l�̒�`
	int XP[4] = { 0,1,0,-1 };  //[���Ȃ��A�E��1�}�X,���Ȃ��A����1�}�X]
	int YP[4] = { -1,0,1,0 };  //[����1�}�X�A���Ȃ��A���1�}�X�A���Ȃ�]


	//maze�̏�����
	std::fill((int*)maze, (int*)(maze + lengthof(maze)), 0);

	//���͂̕ǂ̍쐬       
	for (int i = 0; i < MAZE_W; i++) { //�㉺�̕�
		maze[0][i] = 1;
		maze[MAZE_H - 1][i] = 1;
	}
	for (int i = 1; i < MAZE_H - 1; i++) {  //���E�̕�
		maze[i][0] = 1;
		maze[i][MAZE_W - 1] = 1;
	}
	

	//�@���̍쐬
	for (int i = 2; i < MAZE_H-2; i +=2) {
		for (int j = 2; j < MAZE_W - 2; j +=2) {
			maze[i][j] = 1;
		}
	}


	//������ǂ�L�΂�
	for (int i = 2; i < MAZE_H - 2; i += 2) {
		for (int j = 2; j < MAZE_W - 2; j += 2) {
			int d;
			if (j == 2) {    //1��ڂ̒�(��ԍ��̗�)�͏㉺���E
				d = rand() % 4; //0�`3���痐��
			}
			else {    //2��ڈȍ~�͍��ɂ͕ǂ����Ȃ�(�ǂ����]���Ēʂ�Ȃ�������邱�Ƃ�h��)
				d = rand() % 3; //0�`2���痐��
			}

			maze[i + YP[d]][j + XP[d]] = 1;  //�����ŏo���l�ɓY���ĕǂ��쐬
		}
	}


	/////////////���H���g�p���ă_���W�����̐���///////////////
	
	//�S�̂�ǂɂ���
	std::fill((int*)dungeon, (int*)(dungeon + lengthof(dungeon)), 4); //dungeon������
    
	//�����ƒʘH�̍쐬��z�u
	for (int i = 0; i < MAZE_H - 1; i++) {
		for (int j = 0; j < MAZE_W - 1; j++) {

			//���H�̍��W���_���W�����̍��W�ɕϊ�(3 * 3�}�X�̒����̍��W)
			int tempx = j * 3 + 1;
			int tempy = i * 3 + 1;

			//�Y������maze���ʘH�@
			if (maze[i][j] == 0) {

				//����0�`99��20��艺(20 %)�̊m���@->�����̍쐬
				if (rand() % 100 < 20) {

					for (int roomy = -1; roomy < 2; roomy++) {
						for (int roomx = -1; roomx < 2; roomx++) {

							//tempx,tempy�𒆐S�Ƃ���3*3�}�X�̕���
							dungeon[tempy + roomy][tempx + roomx] = 0;

						}
					}


				}
				else
				{  //80 % �̊m���ŕ��ʂ̓��쐬

					dungeon[tempy][tempx] = 0;  //3 * 3�}�X�̒����̍��W�𓹂ɂ���

					//3 * 3�͈̔͂ɂ����ď㉺���E�̓���L�΂�
					if (maze[i - 1][j] == 0)  dungeon[tempy - 1][tempx] = 0;   //���H�ɂ����ď�͓��@���@��ɓ���L�΂�
					if (maze[i + 1][j] == 0)  dungeon[tempy + 1][tempx] = 0;   //��
					if (maze[i][j - 1] == 0)  dungeon[tempy][tempx - 1] = 0;   //��
					if (maze[i][j + 1] == 0)   dungeon[tempy][tempx + 1] = 0;  //�E
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
			dungeon[y][x] = 3; //�K�i
			break;
		}
	}
    //70��Ń����_���Ŕz�u(���̐������������C�x���g�̔z�u���͏オ��)
	for (int i = 0; i < 70; i++) {
		x = randW(ran);
		y = randH(ran);
		if (dungeon[y][x] == 0) {
			int temp = rand100(ran);
			if (temp <= 20)  dungeon[y][x] = 1; //��
			if (20 < temp)   dungeon[y][x] = 2; //��
		}
	}

}
void Make_Dungeon::draw() {
	double p_x, p_y;
	//Control�̎Q��
	Control& cont = Control::Instance();
	cont.player_positon(&p_x, &p_y);
	//�v���C������c10�}�X��11�͈̔͂�`�悷��

	for (int i = -5; i < 6; i++) {
		for (int j = -5; j < 6; j++) {

			//�`��p�̍��W�v�Z
			int X = (j + 5) * F_SIZE;  //���̃p�l����x���W #0�`10*80
			int Y = (i + 5) * F_SIZE;  //y���W

			int tempx = int(p_x) + j;
			int tempy = int(p_y) + i;

			//tempx,tempy���_���W�����̑傫���͈͓̔��Ȃ�Ε`��
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



#include "Make_Dungeon.h"
#include "define.h"
#include "Control.h"
#include <random>
#define lengthof(a) (sizeof(a)/sizeof(*(a)))

Make_Dungeon::Make_Dungeon() {

	std::fill((int*)maze, (int*)(maze + lengthof(maze)), 0);   //maze������
	std::fill((int*)dungeon, (int*)(dungeon + lengthof(dungeon)), 4); //dungeon������

	//���C�u�����ŉ摜�̓ǂݍ���
    floorgh= LoadGraph("image/base.png");
	boxgh = LoadGraph("image/box.png");
	cocoongh = LoadGraph("image/cocoon.png");
	wallgh = LoadGraph("image/wall.png");
	wall2gh = LoadGraph("image/wall2.png");
	darkgh = LoadGraph("image/dark.png");
	stairsgh = LoadGraph("image/stairs.png");
    
	//��������
	count = 0;
}

Make_Dungeon::~Make_Dungeon() {
	//�摜���̂Ă�
	DeleteGraph(floorgh);
	DeleteGraph(boxgh);
	DeleteGraph(cocoongh);
	DeleteGraph(wallgh);
	DeleteGraph(wall2gh);
	DeleteGraph(darkgh);
	DeleteGraph(darkgh);
	DeleteGraph(stairsgh);
}


//////�_���W�����̐���(�_�|���@)///////
void Make_Dungeon::make_dungeon() {

	//////////////���H�̐���///////////////
	 
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
	 
	//��l���z����������̍쐬
	std::random_device rnd; //�^�̗���
	std::mt19937 mt(rnd()); //�^��������^�̗����ŏ�����
	std::uniform_int_distribution<> rand100(0, 100); //0�`100�̈�l���z����
	
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
				if (rand100(mt) < 20) {

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

	//�C�x���g�̃Z�b�g
	set_event();
	
}

//////�C�x���g�̃Z�b�g////////
void Make_Dungeon::set_event() {

	int x, y;

	//��l���z����������̍쐬
	std::random_device rnd; //�^�̗���
	std::mt19937 mt(rnd()); //�^��������^�̗����ŏ�����
	std::uniform_int_distribution<> randH(3, DUNG_H - 4); //3�`�_���W�����̍���-4�̈�l���z����
	std::uniform_int_distribution<> randW(3, DUNG_W - 4); //3�`�_���W�����̕�-4�̈�l���z����
	std::uniform_int_distribution<> rand100(0, 100);      //0~100�̈�l���z����


	////////�K�i�̐ݒu//////////

	//�K�i��ݒu����܂ő�����
	while (1) {
		//�����Őݒ�
		x = randW(mt);
		y = randH(mt);

		//�ݒ肵�����̂����ł���Ȃ�ΐݒu���ďI��
		if (dungeon[y][x] == 0) {

			//�K�i�̎����3*3�̕����ɂ���
			for (int i = -1; i < 2; i++) {
				for (int j = -1; j < 2; j++) {
					dungeon[y + i][x + j] = 0;
				}
			}

			dungeon[y][x] = 3; //�K�i�ݒu
			break; //�J��Ԃ��I��
		}
	}

	////////�C�x���g�̐ݒu//////////

    //70��Ń����_���Ŕz�u(���̐������������C�x���g�̔z�u���͏オ��)
	for (int i = 0; i < 70; i++) {
		//�����Őݒ�
		x = randW(mt);
		y = randH(mt);
		//�ݒ肵�����̂����ł���Ȃ�ΐݒu
		if (dungeon[y][x] == 0) {
		 
			int temp = rand100(mt);
			if (temp <= 20)  dungeon[y][x] = 1; ////������20�ȉ��ŕ�
			if (20 < temp)   dungeon[y][x] = 2; //������20��蒴�߂Ŗ�
		}
	}

}

/////////�`��////////
void Make_Dungeon::draw() {

	//Control�̎Q��
	Control& cont = Control::Instance();
	//�v���C���[�̈ʒu���擾
	double p_x, p_y;
	cont.player_positon(&p_x, &p_y);



	////////�v���C������11*11�͈̔͂�`�悷��/////////////

	for (int i = -5; i < 6; i++) {
		for (int j = -5; j < 6; j++) {

			//�`��p�̍��W�v�Z
			int X = (j + 5) * F_SIZE;  //���̃p�l����x���W #0�`10*80
			int Y = (i + 5) * F_SIZE;  //y���W

			//�v���C���[�̈ʒu����i,j�}�X����Ă���}�X�̍��W���v�Z
			int tempx = int(p_x) + j;
			int tempy = int(p_y) + i;

			//tempx,tempy���_���W�����̑傫���͈͓̔��Ȃ�Ε`��
			if (0 <= tempx && tempx < DUNG_W  && 0 <= tempy && tempy < DUNG_H ) {

				//��
				if (dungeon[tempy][tempx] ==0) {
					DrawGraph(X, Y, floorgh, TRUE);
				}
				//��
				else if (dungeon[tempy][tempx] == 1) {
					DrawGraph(X, Y, boxgh, TRUE);
				}
				//��
				else if (dungeon[tempy][tempx] == 2) {
					DrawGraph(X, Y, cocoongh, TRUE);
				}
				//�K�i
				else if (dungeon[tempy][tempx] == 3) {
					DrawGraph(X, Y, stairsgh, TRUE);
				}
				//��
				else if (dungeon[tempy][tempx] == 4) {
					DrawGraph(X, Y-40, wallgh, TRUE);
					//(tempx,tempy)��1��̃}�X���ǂȂ�ΓV��`��
					if (tempy >= 1 && dungeon[tempy - 1][tempx] == 4) {
						DrawGraph(X, Y-80, wall2gh, TRUE);
					}
				}
			}
		}
	}

	//�Èł�`��
	DrawGraph(0, 0, darkgh, TRUE);
	
}

////////���̊K�Ɉړ��A�쐬////////////
void Make_Dungeon::next_floor() {

	///���[�v�J�E���g��556�ɂȂ�܂�
	if (count < 656) {

		//���[�v�J�E���g��255�ɂȂ�܂Ń��C�u�����ł��񂾂��ʂ̍ʓx�����炷
		if (count >= 0 && count < 256) {
			SetDrawBright(255 - count, 255 - count, 255 - count);
		}

		//���[�v�J�E���g��256�ŐV�����K�̍쐬
		if (count == 256)
		{
			make_dungeon();
		}

		//���[�v�J�E���g��300�ɂȂ����烉�C�u�����ōʓx�����ɂ��ǂ�
		if (count >= 400 ) {
			SetDrawBright(count - 400, count - 400, count - 400);
		}
		//�J�E���g��4��������
		count +=4;
	
	}
	else
    //���[�v�J�E���g��556�ɂȂ�����J�E���g��0�ɂ���
	if (count ==656) {

		count = 0;
	}
}
//////////�Y�����̃_���W�����̏���Ԃ�//////////////
int Make_Dungeon::get_dungeon_info(int index_x,int index_y) {
	return dungeon[index_y][index_x];
}

//////////�Y�����̈ʒu�̃_���W�����̏��������̏��ɍX�V///////////
void Make_Dungeon::set_dungeon_info(int info, int index_x, int index_y) {
	dungeon[index_y][index_x] = info;
}

//////////���[�v�ōs���֐�////////
void Make_Dungeon::All () {
	draw();
}



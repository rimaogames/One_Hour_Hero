#include "Enemy.h"

Enemy::Enemy() {

	//���C�u�����ŉ摜�̓ǂݍ���
	if (LoadDivGraph("image/messege/number2.png", 10, 10, 1, 13, 17, number2) == -1) {
		MSG("�G���[����(number)");
	}
	slashgh = LoadGraph("image/messege/slash.png");
	enemygh = NULL;

	//�G�̃X�e�[�^�X��������
	enemy.type = 0;
	enemy.lifemax = 0;
	enemy.life = 0;
	enemy.power = 0;
	enemy.point = 0;
	enemy.x = 0;
	enemy.y = 0;

}
Enemy::~Enemy() {

	//���C�u�����ŉ摜���̂Ă�
	for (int i = 0; i < 10; i++) {
		DeleteGraph(number2[i]);
	}

	DeleteGraph(enemygh);
	DeleteGraph(slashgh);
}


/////////�G�̏�����(�����͍��̊K��)/////////////
void Enemy::e_init(int fl) {

	//��l���z����������̍쐬
	std::random_device rnd; //�^�̗���
	std::mt19937 ran(rnd()); //�^��������^�̗����ŏ�����
	std::uniform_int_distribution<> randfloor(0, fl); //0�`���̊K���̊Ԃ̈�l���z����
	std::uniform_int_distribution<> rand9(0, 9); //0�`9�̊Ԃ̈�l���z����

	///////�G�摜�̓ǂݍ���////////

	//�K����10�K�ȏ�Ȃ��
	if (fl >= 10) {

		//�G�̃^�C�v��0~9�Ń����_��
		enemy.type = rand9(ran);
	}
	//�K����9�ȉ��Ȃ��
	else {
		//�G�̃^�C�v��0~���̊K���Ń����_��
		enemy.type = randfloor(ran);
	}
	//������
	std::string temp;
	//type����G�̉摜�̏ꏊ�𕶎����temp�ɕۊǂ��A������g�p���ĉ摜�ǂݍ���
	temp = "image/enemy" + std::to_string(enemy.type) + ".png";
	enemygh = LoadGraph(temp.c_str());

	//���C�u��������摜�̑傫�����擾
	int w, h;
	GetGraphSize(enemygh, &w, &h);

	//�G�̏�񏉊���
	enemy.lifemax = 50 * (enemy.type + 1) + fl * 10 + (rand9(ran) + 1) * 5; //���C�t�ő�l
	enemy.life = enemy.lifemax; //���C�t�ő�l�ŏ�����
	enemy.power = 5 * (enemy.type + 1) + fl * 3 + (rand9(ran) + 1) * 2; //��
	enemy.point = 5 * (enemy.type + 1) + fl * 5 + (rand9(ran) + 1) * 2; //�o���l
	enemy.x = 440 - w / 2; //�G��`�悷��x���W
	enemy.y = 560 - h;    //�G��`�悷��y���W

}

///////�_���[�W�̃Z�b�g/////////
bool Enemy::set_damage(int e_damage) {

	//�G���܂������Ă���Ȃ��
	if (enemy.life > 0) {
		//���C�t����_���[�W������
		enemy.life -= e_damage;
	}

	//�G�̃��C�t��0�ȉ��Ȃ��
	if (enemy.life <= 0) {
		//���C�t��0�ɂ���
		enemy.life = 0;

		//TRUE��Ԃ�
		return true;
	}
	//�G�̃��C�t���܂�����
	else {
		//FALSE��Ԃ�
		return false;
	}
}

//////�G�̗͂�Ԃ�///////
int  Enemy::get_power() {
	return enemy.power;
}

///////�G�̌o���l�������ɓn��///////
void Enemy::get_point(int *p) {
	*p = enemy.point;
}

////////�`��////////////
void Enemy::draw(int damage,int step) {

	////�G�̕`��/////

	//�G�������Ă���@���@�G��_�ł�����p�̃J�E���g�ϐ���0�𒴉�
	if (enemy.life > 0 && damage > 0) {

		//�G��_�ł�����p�̃J�E���g�ϐ���2�Ŋ���؂��
		if (damage % 2 == 0) {
			//�`�悵�Ȃ�
		}
		//2�Ŋ���؂�Ȃ�
		else {
			//���C�u�����ŕ`��
			DrawGraph(enemy.x, enemy.y, enemygh, TRUE);
		}
	}
	//�i�G�������Ă���@���j�G��_�ł�����p�̃J�E���g�ϐ���0[�G���_���[�W�𕉂��Ă����Ȃ�]
	else if (enemy.life > 0) {
		//���C�u�����œG��`��(�G���U�����Ă��鎞��y��step(!=0�j�������O�ɕ`��)
		DrawGraph(enemy.x, enemy.y + step, enemygh, TRUE);
	}

	///////�G�̗̑͂̕`��////////

	//�`��Ɏg�p����ϐ��̐錾�Ə�����
	char buf[100];
	int life_num=0, max_num=0;
	memset(buf, 0, sizeof(buf));


	//life�̕`��
	life_num = sprintf_s(buf, "%d", enemy.life);//buf�ɓG�̗̑͂�����Blife_num�ɂ͕�����������
	for (int i = 0; i < life_num; i++) {
		//���C�u�����Œl�̏����n�߂�100+�����̕�����,y���W645�ɐ������L���B
		//buf�ɂ�1�o�C�g���������i�[����Ă���Bnumber[buf[i]-0]��buf[i]�̃O���t�B�b�N�n���h�����擾�B�`�悷��
		DrawGraph(395 + (i * NUMBER2_W), 570, number2[buf[i] - '0'], TRUE);
	}

	//lifemax�̕`��
	max_num = sprintf_s(buf, "%d", enemy.lifemax);//buf�ɓG�̍ő�̗͂�����Bmax_num�ɂ͕�����������
	for (int i = 0; i <max_num; i++) {
	
		DrawGraph(460 + (i * NUMBER2_W), 570, number2[buf[i] - '0'], TRUE);
	}
	
	//�u/�v�̕`��
	DrawGraph(450, 570, slashgh, TRUE);
}

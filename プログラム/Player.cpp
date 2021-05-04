#include "Player.h"

Player::Player() {

	//���C�u������player�摜�ǂݍ���
	if (LoadDivGraph("image/Player.png", 12, 3, 4, 80, 80, playergh) == -1) {
		MSG("�G���[����(player)");
	}
	//�v���C���[�摜�̑傫��
	width = 80;
	height = 80;

	//�v���C���[�̈ʒu
	p_x = 4;
	p_y = 4;

	//�X�e�[�^�X������
	status.food = 100; //�����x
	status.level = 1; //���x��
	status.life = 100; //���C�t
	status.lifemax = 100; //���C�t�ő�l
	status.point = 0; //�o���l
	status.pointmax = 30; //�o���l�ő�
	status.power = 50; //��
	status.potion = 0; //�|�[�V�����擾��
	status.mp = 0; //���@�Ύ擾��

	//��������
	xcount = 0;
	ycount = 0;
	ix = 0;
	iy = 0;
	index = 0;


	
}

Player::~Player() {

	//�摜���̂Ă�
	for (int i = 0; i < 12; i++) {
		DeleteGraph(playergh[i]);
	}
}
/////////�ړ�////////
void Player::move() {

	//Control�̎Q��
	Control& cont = Control::Instance();

	//�O�̍��W��ۊǂ��Ă���
	int pre_x = int(p_x);
	int pre_y = int(p_y);

	///////////////////�������L�[�ɂ���Ĉړ�/////////////////
	if (InputKey::GetKey(KEY_INPUT_UP)) { //��
		if (cont.dungeon_info(int(p_x), int(p_y) - 1) != 4) {
			p_y -= 0.1;
		}
	}
	if (InputKey::GetKey(KEY_INPUT_DOWN)) { //��
		if (cont.dungeon_info(int(p_x), int(p_y) + 1) != 4) {
			p_y += 0.1;
		}
	}
	if (InputKey::GetKey(KEY_INPUT_LEFT)) { //��
		if (cont.dungeon_info(int(p_x) - 1, int(p_y)) != 4) {
			p_x -= 0.1;
		}
	}
	if (InputKey::GetKey(KEY_INPUT_RIGHT)) { //�E
		if (cont.dungeon_info(int(p_x) + 1, int(p_y)) != 4) {
			p_x += 0.1;
		}
	}

	//�����A�ʒu���X�V���ꂽ��...
	if (pre_x != int(p_x) || pre_y != int(p_y)) {

		//�����x��1���炷
		status.food -= 1;
		if (status.food < 0) status.food = 0; //0������0�ɂ���

		//�����x��0�Ȃ�΃��C�t�����炷
		if (status.food == 0) {
			status.life -= 10;
			if(status.life<0) status.life = 0; //0������0�ɂ���
		}
	}



	///////////////////�摜��ω�������/////////////////

	//���̕����L�[�������Ă���Ԃ͑Ή������J�E���^�𑝂₵�A���񐔕��J�E���^���������Ȃ�摜�����̓���̂��̂ɐ؂�ւ���
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
	//count����摜�̓Y�������߂�
	ix = abs(xcount) % 40 / 10;//|xcount|%30/10=0����29��10�Ŋ����0����2�܂ł̒l�𓾂�=10count���Ƃɉ摜��ς��� 0,1,2,3�Ɠ���
	iy = abs(ycount) % 40 / 10;//|ycount|%30/10�@
	if (ix == 3)ix = 1; //3���P�ɂ��邱�Ƃ�0,1,2,1,0...�Ɠ����悤�ɂ���
	if (iy == 3)iy = 1;

	//������
	//xcount>0�͍������B2�s�ڂ̐擪�Y���𑫂��B
	if (xcount > 0) {
		ix += 3;
		index = ix;//3~5
	}
	else if (xcount < 0) {//xcoount<0�͉E�����B3�s�ڂ̐擪�Y���𑫂��B
		ix += 6;
		index = ix;//6~8
	}


	//�c����
	//ycount>0�͏�����B4�s�ڂ̐擪�Y���𑫂��B
	if (ycount > 0) {
		iy += 9;
		index = iy;//9~11
	}
	else if (ycount < 0) {//ycount<0�͉������B�擪�Y����0�Ȃ̂ŉ������Ȃ��Ă悢�B
		//iy += 0;
		index = iy;
	}


	
	//�L�[���͖����̎���count�����Z�b�g
	if (InputKey::GetKey(KEY_INPUT_LEFT) != 1 && InputKey::GetKey(KEY_INPUT_RIGHT) != 1) {
		xcount = 0;
	}
	if (InputKey::GetKey(KEY_INPUT_UP) != 1 && InputKey::GetKey(KEY_INPUT_DOWN) != 1) {
		ycount = 0;
	}


}



/////////�C�x���g�𓥂񂾂��𒲂ׂ�(������ɂ��ꂽ�Ȃ��TRUE��Ԃ�)////////
bool Player::check() {

	//�R���g���[���̎Q��
	Control& cont = Control::Instance();
	//��l���z����������쐬
	std::random_device rnd; //�^�̗���
	std::mt19937 mt(rnd()); //�^������������G���W����^�̗����ŏ�����
	std::uniform_int_distribution<> rand100(0,100); //0�`100�̊Ԃ̈�l���z����


	//�v���C���[���󔠂𓥂񂾂Ȃ��
	if (cont.dungeon_info(int(p_x), int(p_y)) == 1) {

		//���̏ꏊ�𕁒ʂ̓��ɂ���(�󔠂�����)
		cont.set_dungeon_info(0, p_x, p_y);

	    //temp��0�`100�̗���
		int temp = rand100(mt);

		//temp�̒l�ŃA�C�e����ς���
		if (temp <= 50) {               //0�`50 �|�[�V����

			//�X�e�[�^�X�̃|�[�V����+1��get_item�Ƀ|�[�V�����擾������
			status.potion += 1;
			get_item = MESSEGE::GET_POTION;

		}else
		if (50 < temp && temp<= 85) {   //51�`85 ���@��
			//�X�e�[�^�X�̖��@��+1��get_item�ɖ��@�Ύ擾������
			status.mp += 1;
			get_item = MESSEGE::GET_STONE;

		}else
		if (85 < temp) {  //86�`100 ��

			//�X�e�[�^�X�̖����x/2�Ƃ�get_item�ɓŎ擾������
			status.food = status.food / 2;
			get_item = MESSEGE::GET_POISON;
		}
		//TURE��Ԃ�
		return true;
	}

	//���𓥂񂾂Ȃ��
	else if (cont.dungeon_info(int(p_x), int(p_y)) == 2) 
	{
		//���̏ꏊ�𕁒ʂ̓��ɂ���(��������)
		cont.set_dungeon_info(0, p_x, p_y);

		//0�`100�̗���������
		int temp = rand100(mt);

		//temp�̒l�ŃA�C�e����ω�
		if (temp <=40) {       //0�`40 �G
		    //Control�̏�ʓY������4�ɂ��Đ퓬�Ɉړ�
			cont.set_idx(4);
			//FALSE��Ԃ�
			return false;

		}else
		if (40<temp && temp<=50 ) {    //41�`50 �H�ו�1
			//�����x�ƃ��C�t+10
			status.food += 10;
			status.life += 10;
			if (status.life > status.lifemax) status.life = status.lifemax; //���C�t�͏���𒴂��Ȃ��悤�ɂ���
			//get_item�ɐH�ו�1�擾������
			get_item = MESSEGE::GET_FOOD1;
			//TRUE��Ԃ�
			return true;
		}

		else
		if (50<temp) {    //51�`100 �H�ו�2
			//�����x+100�ƃ��C�t+50
			status.food += 100;
			status.life += 50;
			if (status.life > status.lifemax) status.life = status.lifemax; //���C�t�͏���𒴂��Ȃ��悤�ɂ���
			//get_item�ɐH�ו�2�擾������
			get_item = MESSEGE::GET_FOOD2;
			//TRUE��Ԃ�
			return true;
		}
	}
	else {
		//�K�i�𓥂񂾂Ȃ��
		if (cont.dungeon_info(int(p_x), int(p_y)) == 3) {
			//Control�̏�ʓY������2�ɂ���
			cont.set_idx(2);
		}

		//�K�i�@or�@�Ȃɂ��C�x���g�����Ȃ�� FALSE��Ԃ�
		return false;
	}
}

/////////�ŏ��̈ʒu��ݒ肷��////////
void Player::set_init_positon() {

	//��l���z����������쐬
	std::random_device rnd; //�^�̗���
	std::mt19937 ran(rnd()); //�^��������^�̗����ŏ�����
	std::uniform_int_distribution<> randH(3, DUNG_H - 4); //3�`�_���W�����̍���-4�̊Ԃ̈�l���z����
	std::uniform_int_distribution<> randW(3, DUNG_W - 4); //3�`�_���W�����̕�-4�̊Ԃ̈�l���z����

	//Control�N���X�̐���
	Control& cont = Control::Instance();

	//�����ʒu�����܂�܂ő�����
	while (1) {
		//�v���C���[�̈ʒu�𗐐��Ō��߂�
		p_x = randW(ran);
		p_y = randH(ran);
		//�����Ō��߂��ʒu����(�����Ȃ�)�Ȃ�ΐݒ�I��
		if (cont.dungeon_info(p_x, p_y) == 0) {
			break;
		}
		
	}
}


/////////�`��////////
void Player::draw() {

	//�v���C���[��index�̓Y�����̉摜�ŕ`�悷��
	DrawGraph(5*F_SIZE, 5*F_SIZE-40, playergh[index], TRUE);

}

/////////�X�e�[�^�X��Ԃ�/////////
p_status Player::get_status() {
	return status;
}

////////�v���C���[�̈ʒu�������ɓn��//////////
void Player::get_potision(double* x, double* y) {
	*x = p_x;
	*y = p_y;
}

////////�v���C���[�����̃A�C�e�����擾�����̂���Ԃ�//////////
int  Player::get_item_info() {
	return get_item;
}

/////////�����Ă���̂��`�F�b�N����(�_���W�����Ȃ��ړ����Ɏg�p)//////////
bool Player::check_life() {

	//���C�t��0�Ȃ��TRUE����ȊO��FALSE
	if (status.life == 0) {
		return true;
	}
	else {
		return false;
	}
}

/////////�_���[�W�����C�t�ɃZ�b�g����(���񂾂Ȃ��TRUE��Ԃ�)////////
bool Player::set_damage(int damage) {

	//����(damage)�����C�t�������
	status.life -= damage;
	//0�ȉ���0�ɏC��
	if (status.life < 0) status.life = 0;

	//0(����)�Ȃ��TRUE�A�����Ă���Ȃ��FALSE��Ԃ�
	if (status.life ==0) {
		return true;
	}
	else {
		return false;
	}
}


/////////�X�e�[�^�X���X�V����////////
void Player::set_status(p_status pl) {

   //�X�e�[�^�X�������̃X�e�[�^�X�ɍX�V����
	status = pl;
}


/////////All�i���[�v�ōs���֐�)////////
bool Player::All(bool init_flag) {
	//�`�悷��
	draw();

	//������FALSE(�K���̈ړ����ł͂Ȃ�)�Ȃ��
	if(!init_flag){
		//����
		move();
		//check�̌��ʂ�Ԃ�
	    return check();
	}
	else {//�K���̈ړ����Ȃ��
		//false��Ԃ�
		return false;
	}
}
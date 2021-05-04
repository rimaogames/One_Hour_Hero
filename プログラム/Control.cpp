#include "Control.h"
#include "SceneMgr.h"
#include "InputKey.h"

Control::Control() {

	//���C�u������initialize����ɉ��f�[�^��ǂݍ���
	dungeon_bgm = LoadSoundMem("music/dungeon.ogg");
	battle_bgm = LoadSoundMem("music/battle.ogg");
	gameover_se = LoadSoundMem("music/gameover.ogg");
	win_bgm = LoadSoundMem("music/win.ogg");
	item_se = LoadSoundMem("music/item.ogg");
	stairs_se = LoadSoundMem("music/next.mp3");
	e_attack_se = LoadSoundMem("music/e_attack.ogg");
	p_attack_se = LoadSoundMem("music/p_attack.ogg");
	magic_se = LoadSoundMem("music/magic.ogg");
	recover_se = LoadSoundMem("music/recover.ogg");
	run_se = LoadSoundMem("music/run.ogg");

}

Control::~Control() {

	//�C���X�^���X������
    delete make_d;
	delete player;
	delete battle;
	delete messege;
	delete para;
}

////////������/////////
void Control::initialize() {
	//�C���X�^���X�̐錾�B����
	make_d = new Make_Dungeon;
	player = new Player;
	battle = new Battle;
	messege = new Messege;
	para = new Parameter;

	//�_���W�����̐���
	make_d->make_dungeon();
	//�v���C���[�̏����ʒu����B�ݒ�
	player->set_init_positon();

	//���C�u�����ŉ摜�̓ǂݍ���
	if (LoadDivGraph("image/go_player.png", 4, 1, 4, 80, 80, gameover_pgh) == -1) {
		MSG("�G���[����(controll)");
	}
	gameovergh = LoadGraph("image/Gameover.jpg");

	//��������
	idx = 0;
	count = 0;
	floor = 1;
	gameover_index = 0;
	gameend = false;
	dungeon_bgm_flag=false;
	battle_bgm_flag = false;
	gameover_se_flag = false;
	win_bgm_flag = false;
	item_se_flag = false;
	stairs_se_flag = false;
	e_attack_se_flag = false;
	p_attack_se_flag = false;
	magic_se_flag = false;
	recover_se_flag = false;
	run_se_flag = false;
}

////////�I������///////
void Control::finalize() {

    //�C���X�^���X������
	delete make_d;
	delete player;
	delete battle;
	delete messege;
	delete para;

	//���C�u������BGM���I��点��
	StopSoundMem(dungeon_bgm);
	StopSoundMem(battle_bgm);
	StopSoundMem(win_bgm);
}
void Control::Update() {
	//SceneMgr�̎Q��
	SceneMgr& scenemgr = SceneMgr::Instance();

	//�Q�[�����I����ĂȂ���
	if (!gameend) {
		if (InputKey::GetKeyPush(KEY_INPUT_M)) { //M�L�[��������Ă�����
			scenemgr.ChangeScene(eScene::Scene_Menu);//�V�[�������j���[�ɕύX
		}
	}

	//�Q�[�����I�����ENTER�������ꂽ��
	if (gameend && InputKey::GetKeyPush(KEY_INPUT_RETURN)) {
		scenemgr.ChangeScene(eScene::Scene_Result);//�V�[�������ʉ�ʂɕύX
	}
}

/////////���̊Ǘ��֐�//////////////
void Control::sound() {
	///���ꂼ��̃t���O���������Ȃ�΁A���C�u�����ŉ��𗬂�
	if (dungeon_bgm_flag)PlaySoundMem(dungeon_bgm, DX_PLAYTYPE_LOOP, TRUE);
	if(battle_bgm_flag)PlaySoundMem(battle_bgm, DX_PLAYTYPE_LOOP, TRUE);
    if (gameover_se_flag)PlaySoundMem(gameover_se, DX_PLAYTYPE_BACK, TRUE);
	if (win_bgm_flag)PlaySoundMem(win_bgm, DX_PLAYTYPE_LOOP, TRUE);
	if(item_se_flag)PlaySoundMem(item_se, DX_PLAYTYPE_BACK, TRUE);
	if(stairs_se_flag)PlaySoundMem(stairs_se, DX_PLAYTYPE_BACK, TRUE);
	if(e_attack_se_flag)PlaySoundMem(e_attack_se, DX_PLAYTYPE_BACK, TRUE);
	if(p_attack_se_flag)PlaySoundMem(p_attack_se, DX_PLAYTYPE_BACK, TRUE);
	if(magic_se_flag)PlaySoundMem(magic_se, DX_PLAYTYPE_BACK, TRUE);
	if(recover_se_flag)PlaySoundMem(recover_se, DX_PLAYTYPE_BACK, TRUE);
	if(run_se_flag)PlaySoundMem(run_se, DX_PLAYTYPE_BACK, TRUE);

	//�_���W����BGM�t���O���������Ȃ�Ώ���BGM���~�߂�
	if (dungeon_bgm_flag) {
		//�o�g��BGM�A����BGM���~�߂�
		StopSoundMem(win_bgm);
		StopSoundMem(battle_bgm);
	}
	//����BGM�t���O���������Ȃ�΃o�g��BGM���~�߂�
	if (win_bgm_flag) {
		StopSoundMem(battle_bgm);
	}

	//�o�g��BGM����������_���W����BGM���~�߂�
	if (battle_bgm_flag) {
		StopSoundMem(dungeon_bgm);
	}
}





/////////�v���C���[�̈ʒu�������ɓn��//////////////
void Control::player_positon(double* x, double* y) {

	double tempx, tempy;
	player->get_potision(&tempx, &tempy);

	*x = tempx;
	*y = tempy;

}

/////////�����̈ʒu�̃_���W�����̏���Ԃ�//////////////
int Control::dungeon_info(int x,int y) {
	int temp;
	temp=make_d->get_dungeon_info(x, y);

	return temp;
}

//////////////(index_x,index_y)�̃_���W�����̏���info�ɂ���////////////
void Control::set_dungeon_info(int info, int index_x, int index_y) {

	make_d->set_dungeon_info(info, index_x, index_y);
}

//////////////���̏�ʂ������ɂ���(index�ɂ���)////////////
void Control::set_idx(int index) {

	idx = index;
	count = 0; //�J�E���g������������
}

//////////////���݂̊K����Ԃ�////////////
int Control::get_floor() {

	return floor;
}

//////////////�v���C���[�̏��������ɓn��////////////
void Control::get_p_status(p_status *pl) {

	*pl=player->get_status();
}

//////////////�v���C���[�̏��������̏��ɍX�V����////////////
void Control::set_p_status(p_status pl) {

	player->set_status(pl);
}

//////////////�v���C���[�Ɉ������̃_���[�W��^����////////////
bool Control::set_p_damage(int damage) {

	//�_���[�W������Ȃ�΃v���C���[�Ƀ_���[�W��^����
	if (damage > 0) {
		return player->set_damage(damage); //���񂾂Ȃ��TRUE���Ԃ��Ă���
	}
	else {
		//�_���[�W���Ȃ��Ȃ��FALSE�i�����Ă���)
		return false;
	}
}

//////////////���[�v�ōs�����s�֐�////////////
void Control::All() {

	//�T�E���h�̃t���O��������
	dungeon_bgm_flag = false;
	battle_bgm_flag = false;
	gameover_se_flag = false;
	win_bgm_flag = false;
	item_se_flag = false;
	stairs_se_flag = false;
	e_attack_se_flag = false;
	p_attack_se_flag = false;
	magic_se_flag = false;
	recover_se_flag = false;
	run_se_flag = false;

	//�Q�[���I�[�o�[�t���O������
	gameend = false;

	/////////idx�ŃQ�[���̏�ʂ�؂�ւ���////////
	switch (idx) {

	//�V�K�w
	case 0:

		//�_���W�����N���X�̎��s
		make_d->All();

		//�p�����[�^�N���X�̎��s
		para->All(player->get_status());

		//�v���C���[�N���X�̎��s
		//�A�C�e���Q�b�g�����Ȃ��
		if (player->All(false)) {
			//�A�C�e���Q�b�g��ʂɈړ�
			idx = 3;
			count = 0;
		}
         
		//�J�E���g=1
		if (count == 1) {

			//���b�Z�[�W�Z�b�g
			messege->set(MESSEGE::NEW_FLOOR);

			//�Q�[���X�^�[�g���̂݃_���W����BGM�t���O���R�R�ŗ��Ă�
			if (floor == 1) {
				dungeon_bgm_flag = true;
			}
		}

		//2<�J�E���g<120
		if (count > 2 && count < 120) {
			//���b�Z�[�W�o��
			messege->draw();

			//�����A�v���C���[������
			if (player->check_life()) {
				//�Q�[���I�[�o�[��ʂ�
				idx = 5;
				count = 0;
			}
		}
		//�J�E���g=120
		if (count == 120) {
			//�_���W�����T������ʂɈړ�
			idx = 1;
			count = 0;
		}
		break;

	//�_���W�����T�������
	case 1:

		//�_���W�������s
		make_d->All();
		//�p�����[�^���s
		para->All(player->get_status());


	    //�����Ă���̂��`�F�b�N
		if (player->check_life()) { //���񂾂Ȃ��
			//�Q�[���I�[�o�[��ʂ�
			idx = 5;
			count = 0;
		}
	    
		//�v���C�����s
		if (player->All(false)) { //�A�C�e���Q�b�g�����Ȃ��
			//�A�C�e���Q�b�g��ʂ�
			idx = 3;
			count = 0;
		}
		break;

	//�K���ړ�
	case 2:

		//�����Ă��邩�m�F
		if (player->check_life()) {
			idx = 5;
			count = 0;
		}

		//�_���W�������s
		make_d->All();
		//�v���C�����s(TRUE�œ����Ȃ��悤�ɂ���)
		player->All(true);

		//////���̊K��/////
		//�J�E���g���P
		if (count >= 1) {
			//���̃t���A�ւ�
			make_d->next_floor();
		}

		//�J�E���g=2
		if (count == 2) {
			//�K�i���T�E���h�t���O�𗧂Ă�
			stairs_se_flag = true;
		}

		//�J�E���g=90
		if (count == 90) {
			//�v���C���̈ʒu�ݒ�ƃt���A��+1���₷
			player->set_init_positon();
			floor += 1;
		}

		//�J�E���g=165
		if (count == 165) {
			//�V�K�w��ʂ�
			idx = 0;
			count = 0;
		}
		break;

	//�A�C�e���Q�b�g
	case 3:

		//�_���W�������s
		make_d->All();
		//�v���C�����s(�����Ȃ��悤��TRUE)
		player->All(true);
		//�p�����[�^�̎��s
		para->All(player->get_status());

		//�J�E���g=1
		if (count == 1) {

			//���b�Z�[�W�ɂǂ̃A�C�e������ɓ��ꂽ�̂���^����
			messege->set(player->get_item_info());
			//�A�C�e���Q�b�g�̉��炷
			item_se_flag = true;
		}

		//�J�E���g>1
		if (count > 1) {

			//���b�Z�[�W�o��
			messege->draw(); 
		}

		//�J�E���g=80
		if (count == 80) {
			//�T����ʂɂ��ǂ�
			idx = 1; 
			count = 0;
		}
		break;

	//�o�g�����
	case 4:

		//�J�E���g=1
		if (count == 1) {

			//�o�g��������
			battle->init();
			//�o�g��BGM�t���O���Ă�
			battle_bgm_flag = true;
		}

		//�J�E���g>2
		if (count > 2) {

			//�o�g�����s
			battle->All();
			//�p�����[�^���s
			para->All(player->get_status());

		}
		break;

    //�Q�[���I�[�o�[���
	case 5:

		//�J�E���g=1
		if (count == 1) {

			//BGM���~�߂�
			StopSoundMem(dungeon_bgm);
			StopSoundMem(battle_bgm);
			
		}

		//�J�E���g<=60
		if (count <= 60) {

			//�_���W�������s
			make_d->All();


			/////�v���C����]������///
			 
			//�J�E���g��3�Ŋ���؂�鎞��
			if (count % 3 == 0) {
				//�v���C���摜�̓Y������ύX����
				gameover_index++;
				if (gameover_index == 4)gameover_index = 0; //0,1,2,3,0,1...�ƕύX���Ă���
			}

			//���C�u�����Ńv���C����`�悷��
			DrawGraph(5 * F_SIZE, 5 * F_SIZE - 40, gameover_pgh[gameover_index], TRUE);

		}

		//�J�E���g=61
		if (count == 61) {

			//�Q�[���I�[�o�[SE�̃t���O�𗧂Ă�
			gameover_se_flag = true;

		}

		//�J�E���g>60

		if (count > 60) {

			//�Q�[���I�[�o�[��ʂ����C�u�����ŕ`�悷��
			DrawGraph(0, 0, gameovergh, FALSE);
			//�Q�[���I�[�o�[�t���O�𗧂Ă�
			gameend = true;

		}
		break;
	}
	//���Ǘ��֐�
	sound();

	//�J�E���g���C���N�������g
	count++;

}
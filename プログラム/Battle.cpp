#include "Battle.h"

Battle::Battle() {

	//���C�u�����ŉ摜��ǂݍ���
	backgh = LoadGraph("image/back.jpg");
	if (LoadDivGraph("image/effect.png", 9, 9, 1, 240, 240, efectgh) == -1) {
		MSG("�G���[����1");
	}
	if (LoadDivGraph("image/magic.png", 8, 8, 1, 240, 240, magicgh) == -1) {
		MSG("�G���[����2");
	}
	com[0] = LoadGraph("image/attack.png");
	com[1] = LoadGraph("image/recover.png");
	com[2] = LoadGraph("image/c_magic.png");
	com[3] = LoadGraph("image/run.png");

	//��������
	step = 0;
	swing = 0;
	pre_bx = 0;
	pre_by = 0;
	efe_cont = 0;
	mag_cont = 0;
	d_count = 0;
	p_turn = false;
	end = false;
	now_com = 0;
	idx = 0;
	count = 0;
	use_item = false;
	e_damage = 0;
	p_damage = 0;
	e_point = 0;

}

//////////������////////////////
void Battle::init() {

	//�C���X�^���X����
	enemy = new Enemy;
	messege = new Messege;

	//fl�ɊK����^����
	int fl;
	Control& cont = Control::Instance(); //Control�N���X�̎Q��
	fl = cont.get_floor();
	//�G�̏�����
	enemy->e_init(fl);
    //�^�[����G�����^�[���ɂ���@
	idx = 10;

	//��������
	step = 0;
	swing = 0;
	pre_bx = 0;
	pre_by = 0;
	efe_cont = 0;
	mag_cont = 0;
	d_count = 0;
	p_turn = false;
	end = false;
	now_com = 0;
	count = 0;
	use_item = false;
	e_damage = 0;
	p_damage = 0;
	e_point = 0;
}

///////////�G�t�F�N�g�̐ݒ�//////////////////
void Battle::set_effect(int s, int d,int e,int m,int st) {
	
	//�����̒l�����ꂼ��ɃZ�b�g
	swing = s; //�w�i�h�炷
	d_count = d; //�G�_��
	efe_cont = e; //�U���G�t�F�N�g
	mag_cont = m; //���@�G�t�F�N�g
	step = st; //�G������O�ɂł�

	
}

///////////�`��//////////////////
void Battle::draw() {

	//��l���z����������̍쐬
	std::random_device rnd; //�^�̗���
	std::mt19937 mt(rnd()); //�^��������^�̗����ŏ�����
	std::uniform_int_distribution<> randbx(-20, 20); //-20�`20�̊Ԃ̈�l���z����
	std::uniform_int_distribution<> randby(-10, 10); //-10�`10�̊Ԃ̈�l���z����


	/////////�w�i�̕`��/////////

	//�w�i�̕`��ʒu
	int bx, by;
	bx = 0; //���ʂ�0
	by = 0;

	//swing���ݒ�(>0)�Ȃ��
	if (swing > 0) {
		 
		//swing�����炷
		swing -= 1;
		
		//swing��4�Ŋ���؂��Ȃ�Δw�i��`�悷��ʒu��ς���
		if (swing % 4 == 0) {
			//�����ŕ`�悷��ʒu������
			bx = randbx(mt);
			by = randby(mt);
			//�ϐ��ɍ��̈ʒu��ۊǂ��Ă���
			pre_bx = bx;
			pre_by = by;
		}
		//swing��4�Ŋ���؂�Ȃ���
		else {

			//�ʒu�ɕۊǂ��Ă��������W��^����
			bx = pre_bx;
			by = pre_by;
		}
	}

	//���C�u�����Őݒ肵�����W�ɔw�i��`�悷��
	DrawGraph(bx, by, backgh,FALSE);



	///////�G�̕`��////////

	//�G�̕`��
	enemy->draw(d_count,step);

	//�G�_�ŕϐ����ݒ肳��Ă���Ȃ�΃f�N�������g����
	if (d_count > 0) {
		d_count -= 1;
	 }


	////////////�R�}���h�̕`��//////////////////


	//�v���C���̃^�[���t���O�������Ă����Ȃ��
	if (p_turn) {
		//�R�}���h��`��
		for (int i = 0; i < 4; i++) {
			//�I�𒆂̃R�}���h�͏����E�ɕ`��
			if (i == now_com) {
				DrawGraph(40, 360 + 60 * i, com[i], TRUE);
			}
			//�I�𒆂łȂ��R�}���h��x���W20�ɕ`��
			else {
				DrawGraph(20, 360 + 60 * i, com[i], TRUE);
			}
		}

	}


	//////////�G�t�F�N�g�̕`��//////////////////

	//�U���G�t�F�N�g���ݒ肳�ꂽ�Ȃ��
	if (efe_cont > 0) {
		//�G�t�F�N�g��`��
		DrawGraph(300, 300, efectgh[efe_cont-1], TRUE);
		//�J�E���g��2�Ŋ���؂��Ȃ�΃G�t�F�N�g�̉摜�����̃R�}�ɂ���
		if (count % 2 == 0)efe_cont += 1;
        //�U���G�t�F�N�g�ϐ���10�ŕ`��I��
		if (efe_cont == 10) {
			efe_cont = 0;
		}
	}

	//���@�G�t�F�N�g���ݒ肳�ꂽ�Ȃ��
	if (mag_cont > 0) {
		//�G�t�F�N�g��`��
		DrawGraph(320, 320, magicgh[mag_cont-1], TRUE);
		// �J�E���g��2�Ŋ���؂��Ȃ�΃G�t�F�N�g�̉摜�����̃R�}�ɂ���
		if (count % 4 == 0)mag_cont += 1;
		//���@�G�t�F�N�g�ϐ���8�ŕ`��I��
		if (mag_cont==8) {
			mag_cont = 0;
		}
	}


}


//////////�R�}���h�֐�////////////
void Battle::command() {

	//Control�̎Q��
	Control& cont = Control::Instance();

	/////////�R�}���h�̑I��/////////

	//���L�[�������ꂽ��
	if (InputKey::GetKeyPush(KEY_INPUT_DOWN)) {
		now_com = (now_com + 1) % cnum;//�I����Ԃ��������
	}

	//��L�[�������ꂽ��
	else if (InputKey::GetKeyPush(KEY_INPUT_UP)) {
		now_com = (now_com + (cnum - 1)) % cnum;//�I����Ԃ���グ��
	}

	//Enter�������ꂽ��
	if (InputKey::GetKeyPush(KEY_INPUT_RETURN)) {

		//���I�����Ă�����̂Ń^�[���̓Y������ς���
		switch (now_com) {

		case COM::ATTACK: //�U���I��
			idx = 12; 
			count = 0;
			break;
		case COM::USE_POTION: //�|�[�V�����I��
			idx = 13;
			count = 0;
			break;
		case COM::MAGIC: //���@�I��
			idx = 14;
			count = 0;
			break;
		case COM::RUN: //������I��
			idx = 15;
			count = 0;
			break;
		default:
			break;
		}
	}

}

////////////���x���A�b�v�i�����Ɍo���l)/////////////
void  Battle::levelup(int point) {

	//Control�N���X�̎Q��
	Control& cont = Control::Instance();

	//pl�Ƀv���C���̏���^����
	p_status pl;
	cont.get_p_status(&pl);


	//�c�����o���l���v�Z
	e_point = pl.point + point - pl.pointmax; //(���������Ă���o���l)+(����l�������o���l) - ���̃��x���܂łɕK�v�Ȍo���l 


	//�v���C���̏���ݒ�

	pl.lifemax = pl.lifemax + pl.level * 30; //���C�t�ő�l�ύX
	pl.life = pl.lifemax; //���C�t�ő�l�܂ŉ�
	pl.point = 0; //�o���l������
	pl.pointmax = pl.pointmax + pl.level * 20; //���̃��x���܂ł̌o���l�ύX
	pl.level += 1; //���x��+1
	pl.power += 5; //��+5
	//�v���C���̏���pl�ɂ���
	cont.set_p_status(pl);

}


/////////�̗͉�/////////
void Battle::recover() {

	//Control�Q��
	Control& cont = Control::Instance();

	//pl�ɍ��̏���^����
	p_status pl;
	cont.get_p_status(&pl);

	//�|�[�V����������-1
	pl.potion -= 1;
	//���C�t�����C�t�ő�l�܂ŉ�
	pl.life = pl.lifemax;

	//�v���C���̏���pl�ɕύX
	cont.set_p_status(pl);
}


//���[�v�ōs�����s�֐�
void Battle::All() {

	//Control�Q��
	Control& cont = Control::Instance();

	//��l���z����������̍쐬
	std::random_device rnd; //�^�̗���
	std::mt19937 mt(rnd()); //�^��������^�̗����ŏ�����
	std::uniform_int_distribution<> rand10(0, 10); //0�`10�̊Ԃ̈�l���z����

	//�`��
	draw();



	//////////////���܂̃^�[���ŏ�����ύX����///////////////

	switch (idx) {

	//�퓬�J�n
	case 10:  

		//�J�E���g=1
		if (count == 1) {
			//�G�������b�Z�[�W�ݒ�
			messege->set(MESSEGE::ENCOUNTER);
		}

		//�J�E���g>2
		if (count > 2) {
			//���b�Z�[�W�o��
			messege->draw();
		}

		//�J�E���g=60
		if (count == 60) {
			//�R�}���h���͑҂��^�[���ֈړ�
			idx = 11;
			count = 0;
		}

		break;

	//�R�}���h���͑҂�
	case 11: 

		//���b�Z�[�W�o��
		messege->draw();

		//�J�E���g=1
		if (count == 1) {
			//�v���C���̃^�[���t���O�𗧂Ă�
			p_turn = true;

			//���b�Z�[�W�Ƀv���C���̃^�[�����b�Z�[�W��ݒ�
			messege->set(MESSEGE::P_TUEN);
		}

		//�R�}���h
	    command();

		break;

	//�v���C���[�̍U��
	case 12:

		//���b�Z�[�W���o��
		messege->draw();

		//�J�E���g=1
		if (count == 1) {

			//���b�Z�[�W���̍U�����b�Z�[�W�ɐݒ�
			messege->set(MESSEGE::P_ATTACK);

			//�v���C���̃^�[���t���O�����낷
			p_turn = false;

			//pl�Ƀv���C���̏����擾
			p_status pl;
			cont.get_p_status(&pl);

			//�G�ւ̃_���[�W���v���C���̗͂Ɨ����Ō���
			e_damage = pl.power + rand10(mt); 
		}

		//�J�E���g=5
		if (count == 5) {

		   //�G�t�F�N�g�ݒ�i�U���G�t�F�N�g)
			set_effect(0, 0, 1, 0, 0);
			//�U��SE�t���O�𗧂Ă�
			cont.p_attack_se_flag = true;
		}

		//�J�E���g=35
		if (count == 35) {
			//���b�Z�[�W�ɓG�ւ̃_���[�W�����b�Z�[�W��ݒ�
			messege->set_dam(e_damage);

			//�G�t�F�N�g�ݒ�(�G�_��)
			set_effect(0, 40, 0, 0, 0);
			
			//�G�Ƀ_���[�W���Z�b�g
			if (enemy->set_damage(e_damage) == true) { //�G���S

				//�����^�[���ֈړ�
				idx = 17;
				count = 0;
			}

        //�J�E���g=80
		}
		if (count == 80) {
			//�G�̍U���^�[���ֈړ�
			idx = 16;
			count = 0;
		}

		break;

	//�̗͉�
	case 13: 

		//���b�Z�[�W�o��
		messege->draw();

		//�J�E���g=1
		if (count == 1) {

			//���b�Z�[�W���|�[�V�����g�p���b�Z�[�W�ɐݒ�
			messege->set(MESSEGE::P_POTION);
		}


		//�J�E���g=40
		if (count == 40) {

			//pl�Ƀv���C���̏����擾
			p_status pl;
			cont.get_p_status(&pl);

			//�|�[�V������������0
			if (pl.potion == 0) {
				//���b�Z�[�W�ɃA�C�e�����������b�Z�[�W��ݒ�
				messege->set(MESSEGE::NO_ITEM);

				//�A�C�e���g���t���O��false�̂܂�
				use_item = false;
			}

			//�|�[�V�����������Ă���
			else {

				//�A�C�e���g�p�t���O�𗧂Ă�
				use_item = true;
			}
		}

		//�J�E���g=80
		if (count == 80) {

			//�A�C�e���g�p�t���O�������Ă���Ȃ��
			if (use_item == true) {

				//���b�Z�[�W�ɉ񕜂������b�Z�[�W��ݒ�
				messege->set(MESSEGE::RECOVER);

				//��
				recover();

				//��SE�t���O�𗧂Ă�
				cont.recover_se_flag = true;

                //�A�C�e���g�p�t���O�����낷
				use_item = false;
			}

			//�A�C�e���g�p�t���O�������Ă��Ȃ��Ȃ��
			else {
				//k�R�}���h���͑҂��^�[���ֈړ�
				idx = 11;
				count = 0;
			}
		}

		//�J�E���g=120
		if (count == 120) {
			//�G�̍U���^�[���ֈړ�
			idx = 16;
			count = 0;
		}

		break;

	//���@
	case 14:

		//���b�Z�[�W���o��
		messege->draw();


		//�J�E���g=1
		if (count == 1) {

			//���b�Z�[�W�ɖ��@���b�Z�[�W��ݒ�
			messege->set(MESSEGE::P_MAGIC);
		}

		//�J�E���g=40
		if (count == 40) {

			//pl�Ƀv���C���̏����擾
			p_status pl;
			cont.get_p_status(&pl);

			//�v���C���̖��@�Ώ�������0�Ȃ��
			if (pl.mp == 0) {

				//���b�Z�[�W�ɃA�C�e�����������b�Z�[�W��ݒ�
				messege->set(MESSEGE::NO_ITEM);

				//�A�C�e���g�p�t���O�͂��̂܂�
				use_item = false;
			}

			//���@�Ώ������Ă���Ȃ��
			else {

				//���@�Ώ�����-1
				pl.mp -= 1;

				//�v���C���̏���pl�ɍX�V
				cont.set_p_status(pl);

				//�G�t�F�N�g�ݒ�(���@�G�t�F�N�g)
				set_effect(0, 0, 0, 1, 0);

				//���@SE�t���O�𗧂Ă�
				cont.magic_se_flag = true;

				//���@�g�p�t���O�𗧂Ă�
				use_item = true;
			}
		}

		//�J�E���g=80
		if (count == 80) {

			//�A�C�e���g�p�t���O�������Ă���Ȃ��
			if (use_item == true) {

				//�G�ւ̃_���[�W��200����{�Ƃ��A�����_���Ō��߂�
				e_damage = 200 + rand10(mt)*2;

				//���b�Z�[�W�ɓG�ւ̃_���[�W�t���̃��b�Z�[�W��ݒ�
				messege->set_dam(e_damage);

				//�G�t�F�N�g�ݒ�(�G�_��)
				set_effect(0, 40, 0,0,0);

				//�A�C�e���g�p�t���O�����낷
				use_item = false;

				//�G�Ƀ_���[�W��ݒ肷��
				if (enemy->set_damage(e_damage) == true) { //�G������

					//�����^�[���ֈړ�
					idx = 17;
					count = 0;
				}
			}

			//�����A�C�e���g�p�t���O�������Ă��Ȃ�
			else {

				//�R�}���h���͑҂��^�[���ֈړ�
				idx = 11;
				count = 0;
			}
		}

		//�J�E���g=120
		if (count == 120) {

			//�G�̍U���^�[���ֈړ�
			idx = 16;
			count = 0;
		}

		break;

	//������
	case 15: 

		//���b�Z�[�W���o��
		messege->draw();

		//�J�E���g���P
		if (count == 1) {
			//���b�Z�[�W�𓦂��郁�b�Z�[�W�ɐݒ肷��
			messege->set(MESSEGE::P_RUN);
		}

		//�J�E���g=50
		if (count == 50) {

			//����
			int temp = rand10(mt);

			//������4�ȉ��������瓦�S����
			if (temp <= 4) {

				//������r�d�t���O�𗧂Ă�
				cont.run_se_flag = true;

				//�_���W�����T����ʂɈړ�
				cont.set_idx(1);

				//�_���W�����a�f�l�t���O�𗧂Ă�
				cont.dungeon_bgm_flag = true;
			}

			//������5�ȏ� ���S���s
			else {

				//���b�Z�[�W�ɓ��S���s���b�Z�[�W��ݒ肷��
				messege->set(MESSEGE::P_NOT_RUN);
			}
		}

		//�J�E���g=100
		if (count == 100) {

			//�G�̍U���^�[���ֈړ�
			idx = 16;
			count = 0;
		}

		break;

	//�G�̍U��
	case 16: 

		//���b�Z�[�W�o��
		messege->draw();


		//�J�E���g���P
		if (count == 1) {

			//���b�Z�[�W�ɓG�̍U�����b�Z�[�W��ݒ肷��
			messege->set(MESSEGE::E_ATTACK);
		}

		//�J�E���g=10
		if (count == 10) {

			//�G�t�F�N�g�ݒ�(�G������O��)
			set_effect(0, 0, 0, 0, 40);

			//�U���r�d�t���O�𗧂Ă�
			cont.p_attack_se_flag = true;

			//�v���C���ւ̃_���[�W��G�̗͂Ɨ����Ō���
			p_damage = enemy->get_power() + rand() % 10;
		}

		//�J�E���g=30
		if (count == 30) {

			//���b�Z�[�W���v���C���ւ̃_���[�W�t�����b�Z�[�W�ɐݒ�
			messege->set_dam(p_damage);

			//�G�t�F�N�g�ݒ�(�w�i�h�炷)
		    set_effect(40, 0, 0, 0, 0);

			//�G�̍U���r�d�t���O�𗧂Ă�
			cont.e_attack_se_flag = true;


			//�v���C���Ƀ_���[�W���Z�b�g����
			if (cont.set_p_damage(p_damage)== true) { //�v���C������

				//�s�k�^�[���ֈړ�
				idx = 19;
				count = 0;
			}
		}

		//�J�E���g=90
		if (count == 90) {

			//�R�}���h���͑҂��^�[���ֈړ�
			idx = 11;
			count = 0;
		}

		break;

	//����
	case 17:

		//�J�E���g=1
		if (count == 1) {

			//���b�Z�[�W���������b�Z�[�W�ɐݒ�
			messege->set(MESSEGE::WIN);

			//�����a�f�l�t���O�𗧂Ă�
			cont.win_bgm_flag = true;
		}

		//�J�E���g>2
		if (count > 2) {

			//���b�Z�[�W���o��
			messege->draw();
		}

		//�J�E���g=400
		if (count == 400) {

			//�G�̌o���l��e_point�ɗ^����
			enemy->get_point(&e_point);

			//pl�Ƀv���C���̏����擾
			p_status pl;
			cont.get_p_status(&pl);

			//�����A(�v���C�����������Ă���o���l)+�i�����ɂ��ꂽ�o���l)>=(���̃��x���܂łɕK�v�Ȍo���l)�Ȃ��
			if (pl.point + e_point >= pl.pointmax) {

				//���x���A�b�v�V�[����
				idx = 18;
				count = 0;
			}

			//�܂��o���l������Ȃ��Ȃ��
			else {

				//�o���l�ɍ���̌o���l�𑫂�
				pl.point += e_point;

				//�v���C���̏���pl�ɍX�V
				cont.set_p_status(pl);

				//�_���W�����T��BGM�t���O���𗧂Ă�
				cont.dungeon_bgm_flag = true;

				//�_���W�����T����ʂɈړ�
				cont.set_idx(1);

			}
		}

		break;

     // ���x���A�b�v
	case 18:

		//�J�E���g=1
		if (count == 1) {

			//���x���A�b�v���b�Z�[�W��ݒ�
			messege->set(MESSEGE::LEVELUP);

			//���x���A�b�v����
			levelup(e_point);
		}

		//�J�E���g=2
		if (count > 2) {

			//���b�Z�[�W���o��
			messege->draw();
		}

		//�J�E���g=350
		if (count == 350) {

			//pl�Ƀv���C���̏����擾
			p_status pl;
			cont.get_p_status(&pl);

			//(�v���C�����������Ă���o���l(0))+�i�c�����o���l)>=(���̃��x���܂łɕK�v�Ȍo���l)
			if (pl.point + e_point >= pl.pointmax) {
				//������x���x���A�b�v�^�[��(count=0)�ֈړ�
				idx = 17;
				count = 0;
			}

			//�c�����o���l�����̃��x���ɕK�v�Ȍo���l�𖞂����Ă��Ȃ��Ȃ�
			else {

				//�o���l�Ɏc�����o���l��^����
				pl.point += e_point;

				//�v���C���̏���pl�ɍX�V
				cont.set_p_status(pl);

				//�_���W����BGM�t���O�𗧂Ă�
				cont.dungeon_bgm_flag = true;

				//�_���W�����T����ʂɈړ�
				cont.set_idx(1);

			}
		}

		break;


	//����
	case 19: 

		//���b�Z�[�W���o��
		messege->draw();

		//�J�E���g=1
		if (count == 1) {

			//���b�Z�[�W�𕉂����b�Z�[�W�ɐݒ�
			messege->set(MESSEGE::LOSE);
		}

		//�J�E���g=150
		if (count == 150) {

			//���b�Z�[�W�C���X�^���X������
			delete messege;

			//�Q�[���I�[�o�[��ʂɈړ�
			cont.set_idx(5);
		}
	}

	//�J�E���g���C���N�������g
	count++;
}
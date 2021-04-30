#include "Battle.h"

Battle::Battle() {

	WHITE = GetColor(255, 255, 255);
	BLACK = GetColor(0, 0, 0);
	backgh = LoadGraph("image/back.jpg");
	if (LoadDivGraph("image/effect.png", 9, 9, 1, 240, 240, efectgh) == -1) {
		MSG("エラー発生1");
	}
	if (LoadDivGraph("image/magic.png", 8, 8, 1, 240, 240, magicgh) == -1) {
		MSG("エラー発生2");
	}

	step = 0;
	swing = 0;
	s_x = 0;
	s_y = 0;
	efe_cont = 0;
	mag_cont = 0;
	d_count = 0;
	p_turn = false;
	end = false;
	com[0] = LoadGraph("image/attack.png");
	com[1] = LoadGraph("image/recover.png");
	com[2] = LoadGraph("image/c_magic.png");
	com[3]=LoadGraph("image/run.png");
	now_com = 0;
	idx = 0;
	count = 0;
	use_item = false;
	e_damage = 0;
	p_damage = 0;
	e_point = 0;

}

void Battle::init() {
	enemy = new Enemy;
	messege = new Messege;
	int fl;
	Control& cont = Control::Instance();
	fl = cont.get_floor();
	enemy->e_init(fl);
	end = false;
	idx = 10;
	count = 0;
}


void Battle::set_effect(int s, int d,int e,int m,int st) {
	swing = s;
	d_count = d;
	efe_cont = e;
	mag_cont = m;
	step = st;

	
}
void Battle::draw() {
	std::random_device rnd;
	std::mt19937 ran(rnd());
	std::uniform_int_distribution<> randbx(-20, 20);
	std::uniform_int_distribution<> randby(-10, 10);

	int bx, by;
	bx = 0;
	by = 0;
	if (swing > 0) {
		swing -= 1;
		if (swing % 4 == 0) {
			bx = randbx(ran);
			by = randby(ran);
			s_x = bx;
			s_y = by;
		}
		else {
			bx = s_x;
			by = s_y;
		}
	}
	DrawGraph(bx, by, backgh,FALSE);
	enemy->draw(d_count,step);
	if (d_count > 0) {
		d_count -= 1;
	 }

	if (p_turn) {
		for (int i = 0; i < 4; i++) {
			if (i == now_com) {
				DrawGraph(40, 360 + 60 * i, com[i], TRUE);
			}
			else {
				DrawGraph(20, 360 + 60 * i, com[i], TRUE);
			}
		}

	}

	if (efe_cont > 0) {
		DrawGraph(300, 300, efectgh[efe_cont-1], TRUE);
		if (count % 2 == 0)efe_cont += 1;
		if (efe_cont == 10) {
			efe_cont = 0;
		}
	}
	if (mag_cont > 0) {
		DrawGraph(320, 320, magicgh[mag_cont-1], TRUE);
		if (count % 4 == 0)mag_cont += 1;
		if (mag_cont==8) {
			mag_cont = 0;
		}
	}




}
void Battle::command() {
	Control& cont = Control::Instance();
	//下キーが押されたら
	if (InputKey::GetKeyPush(KEY_INPUT_DOWN)) {
		now_com = (now_com + 1) % cnum;//選択状態を一つ下げる
	}
	//上キーが押されたら
	else if (InputKey::GetKeyPush(KEY_INPUT_UP)) {
		now_com = (now_com + (cnum - 1)) % cnum;//選択状態を一つ上げる
	}
	if (InputKey::GetKeyPush(KEY_INPUT_RETURN)) {
		//今選択しているものは？
		switch (now_com) {
		case COM::ATTACK:
			idx = 12; 
			count = 0;
			break;
		case COM::USE_POTION:
			idx = 13;
			count = 0;
			break;
		case COM::MAGIC:
			idx = 14;
			count = 0;
			break;
		case COM::RUN:
			idx = 15;
			count = 0;
			break;
		default:
			break;
		}
	}
}void  Battle::levelup(int point) {
	Control& cont = Control::Instance();
	p_status pl;
	cont.get_p_status(&pl);


	e_point = pl.point + point - pl.pointmax;


	pl.lifemax = pl.lifemax + pl.level * 30;
	pl.life = pl.lifemax;
	pl.point = 0;
	pl.pointmax = pl.pointmax + pl.level * 20;
	pl.level += 1;
	pl.power += 5;
	cont.set_p_status(pl);
}

void Battle::recover() {
	Control& cont = Control::Instance();
	p_status pl;
	cont.get_p_status(&pl);
	pl.potion -= 1;
	pl.life = pl.lifemax;
	cont.set_p_status(pl);
}
void Battle::All() {
	Control& cont = Control::Instance();
	std::random_device rnd;
	std::mt19937 ran(rnd());
	std::uniform_int_distribution<> rand10(0, 10);
	draw();
	switch (idx) {
	case 10:  //戦闘開始
		if (count == 1) {
			messege->set(MESSEGE::ENCOUNTER);
		}
		if (count > 2) {
			messege->draw();
		}
		if (count == 60) {
			idx = 11;
			count = 0;
		}
		break;
	case 11: //コマンド入力待ち
		messege->draw();
		if (count == 1) {
			p_turn = true;
			messege->set(MESSEGE::P_TUEN);
		}
	    command();
		break;
	case 12:  //プレイヤーの攻撃
		messege->draw();
		if (count == 1) {
			messege->set(MESSEGE::P_ATTACK);
			p_turn = false;


			p_status pl;
			cont.get_p_status(&pl);
			e_damage = pl.power + rand10(ran);
		}
		if (count == 5) {
			set_effect(0, 0, 1, 0, 0);
			cont.p_attack_se_flag = true;
		}

		if (count == 35) {
			messege->set_dam(e_damage);
			set_effect(0, 40, 0, 0, 0);
			
			if (enemy->set_damage(e_damage) == true) {
				idx = 17;
				count = 0;
			}
		}
		if (count == 80) {
			idx = 16;
			count = 0;
		}
		break;
	case 13: //体力回復
		messege->draw();
		if (count == 1) {
			messege->set(MESSEGE::P_POTION);
		}
		if (count == 40) {
			p_status pl;
			cont.get_p_status(&pl);
			if (pl.potion == 0) {
				messege->set(MESSEGE::NO_ITEM);
				use_item = false;
			}
			else {

				use_item = true;
			}
		}
		if (count == 80) {
			if (use_item == true) {
				messege->set(MESSEGE::RECOVER);
				recover();//回復
				cont.recover_se_flag = true;
				use_item = false;
			}
			else {
				idx = 11;
				count = 0;
			}
		}
		if (count == 120) {
			idx = 16;
			count = 0;
		}
		break;
	case 14: //魔法
		messege->draw();
		if (count == 1) {
			messege->set(MESSEGE::P_MAGIC);
		}
		if (count == 40) {
			p_status pl;
			cont.get_p_status(&pl);
			if (pl.mp == 0) {
				messege->set(MESSEGE::NO_ITEM);
				use_item = false;
			}
			else {
				pl.mp -= 1;
				cont.set_p_status(pl);
				set_effect(0, 0, 0, 1, 0);
				cont.magic_se_flag = true;
				use_item = true;
			}
		}
		if (count == 80) {
			if (use_item == true) {
				e_damage = 200 + rand10(ran);
				messege->set_dam(e_damage);
				set_effect(0, 40, 0,0,0);
				use_item = false;
				if (enemy->set_damage(e_damage) == true) {
					idx = 17;
					count = 0;
				}
			}
			else {
				idx = 11;
				count = 0;
			}
		}
		if (count == 120) {
			idx = 16;
			count = 0;
		}
		break;
	case 15: //逃げる
		messege->draw();
		if (count == 1) {
			messege->set(MESSEGE::P_RUN);
		}

		if (count == 50) {
			int temp = rand() % 10;
			if (temp <= 4) {
				cont.run_se_flag = true;
				cont.set_idx(1);
				cont.dungeon_bgm_flag = true;
			}
			else {
				messege->set(MESSEGE::P_NOT_RUN);
			}
		}

		if (count == 100) {
			idx = 16;
			count = 0;
		}
		break;
	case 16: //敵の攻撃
		messege->draw();
		if (count == 1) {
			messege->set(MESSEGE::E_ATTACK);
		}

		if (count == 10) {
		    set_effect(0, 0, 0, 0, 40);
			cont.p_attack_se_flag = true;
			p_damage = enemy->get_power() + rand() % 10;
		}
		if (count == 30) {
			messege->set_dam(p_damage);
		    set_effect(40, 0, 0, 0, 0);
			cont.e_attack_se_flag = true;

			if (cont.set_p_damage(p_damage)== true) {
				idx = 19;
				count = 0;
			}
		}
		if (count == 90) {
			idx = 11;
			count = 0;
		}
		break;
	case 17: //勝ち
		if (count == 1) {
			messege->set(MESSEGE::WIN);
			cont.win_bgm_flag = true;
		}
		if (count > 2) {
			messege->draw();
		}
		if (count == 400) {
			enemy->get_point(&e_point);
			p_status pl;
			cont.get_p_status(&pl);
			if (pl.point + e_point >= pl.pointmax) {
				idx = 18;
				count = 0;
			}
			else {
				pl.point += e_point;
				cont.set_p_status(pl);
				cont.set_idx(1);
				cont.dungeon_bgm_flag = true;
			}
		}
		break;
	case 18:// レベルアップ
		if (count == 1) {
			messege->set(MESSEGE::LEVELUP);
			levelup(e_point);
		}
		if (count > 2) {
			messege->draw();
		}
		if(count==350){
			p_status pl;
			cont.get_p_status(&pl);
			if (pl.point + e_point >= pl.pointmax) {
				idx = 17;
				count = 2;
			}
			else {
				pl.point += e_point;
				cont.set_p_status(pl);
				cont.set_idx(1);
				cont.dungeon_bgm_flag = true;
			}
		}
		break;
	case 19: //負け
		messege->draw();
		if (count == 1) {
			messege->set(MESSEGE::LOSE);
		}
		if (count == 150) {
			delete messege;
			cont.set_idx(5);
		}
	}
	count++;
}
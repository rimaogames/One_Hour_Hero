#include "Control.h"
#include "SceneMgr.h"
#include "InputKey.h"

Control::Control() {
	gameend = false;
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
/*delete make_d;
	delete player;
	delete battle;
	delete messege;
	delete para;*/
}
void Control::initialize() {
	make_d = new Make_Dungeon;
	player = new Player;
	battle = new Battle;
	messege = new Messege;
	para = new Parameter;
	make_d->make_dungeon();
	player->set_init_positon();

	if (LoadDivGraph("image/go_player.png", 4, 1, 4, 80, 80, gameover_pgh) == -1) {
		MSG("エラー発生(controll)");
	}
	gameovergh = LoadGraph("image/Gameover.jpg");
	idx = 0;
	count = 0;
	floor = 1;
	gameover_count = 0;
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
void Control::finalize() {
	delete make_d;
	delete player;
	delete battle;
	delete messege;
	delete para;
	StopSoundMem(dungeon_bgm);
	StopSoundMem(battle_bgm);
	StopSoundMem(win_bgm);
}
void Control::Update() {
	SceneMgr& scenemgr = SceneMgr::Instance();

	//ゲームが終わってない間
	if (!gameend) {
		if (InputKey::GetKeyPush(KEY_INPUT_M)) { //Mキーが押されていたら
			scenemgr.ChangeScene(eScene::Scene_Menu);//シーンをメニューに変更
		}
	}

	//ゲームが終わってRETURNが押されたら
	if (gameend && InputKey::GetKeyPush(KEY_INPUT_RETURN)) {
		scenemgr.ChangeScene(eScene::Scene_Result);//シーンを結果画面に変更
	}
}

void Control::sound() {
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


	if (dungeon_bgm_flag) {
		StopSoundMem(win_bgm);
	}
	if (win_bgm_flag) {
		StopSoundMem(battle_bgm);
	}
}






void Control::player_positon(double* x, double* y) {
	double tempx, tempy;
	player->get_potision(&tempx, &tempy);
	*x = tempx;
	*y = tempy;
}
int Control::dungeon_info(int x,int y) {
	int temp;
	temp=make_d->get_dungeon_info(x, y);
	return temp;
}
void Control::set_dungeon_info(int info, int index_x, int index_y) {
	make_d->set_dungeon_info(info, index_x, index_y);
}
void Control::set_idx(int index) {
	idx = index;
	count = 0;
}
int Control::get_floor() {
	return floor;
}
void Control::get_p_status(p_status *pl) {
	*pl=player->get_status();
}
void Control::set_p_status(p_status pl) {
	player->set_status(pl);
}


bool Control::set_p_damage(int damage) {
	if (damage > 0) {
		return player->set_damage(damage);
	}
	else {
		return false;
	}
}

void Control::All() {
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
	gameend = false;
	switch (idx) {
	case 0:
		make_d->All();
		para->All(player->get_status());
		if (player->All(false)) {
			idx = 3;
			count = 0;
		}
		if (count == 1) {
			messege->set(MESSEGE::NEW_FLOOR);
			if (floor == 1) {
				dungeon_bgm_flag = true;
			}
		}
		if (count > 2 && count < 120) {
			messege->draw();
			if (player->check_life()) {
				idx = 5;
				count = 0;
			}
		}
		if (count == 120) {
			idx = 1;
			count = 0;
		}
		break;
	case 1:
		if (count == 1) {
			StopSoundMem(win_bgm);
			StopSoundMem(battle_bgm);
		}
		if (player->check_life()) {
			idx = 5;
			count = 0;
		}
		make_d->All();
		para->All(player->get_status());
		if (player->All(false)) {
			idx = 3;
			count = 0;
		}
		break;
	case 2:
		//生きているか確認
		if (player->check_life()) {
			idx = 5;
			count = 0;
		}
		make_d->All();
		player->All(true);
		//次の階へ
		if (count > 1) {
			make_d->next_floor();
		}
		if (count == 2) {
			stairs_se_flag = true;
		}
		if (count == 70) {
			player->set_init_positon();
			floor += 1;
		}
		if (count == 139) {
			idx = 0;
			count = 0;
		}
		break;
	case 3:
		make_d->All();
		player->All(true);
		para->All(player->get_status());
		if (count == 1) {
			messege->set(player->get_item_info()); //メッセージにどのアイテムを手に入れたのかを与える
			printfDx("%d", player->get_item_info());
			item_se_flag = true;//アイテムゲットの音鳴らす
		}
		if (count > 1) {
			messege->draw(); //メッセージ出力
		}
		if (count == 100) {
			idx = 1; //探検にもどる
			count = 0;
		}
		break;
	case 4:
		if (count == 1) {
			battle->init();
			StopSoundMem(dungeon_bgm);
			battle_bgm_flag = true;
		}
		if (count > 2) {
			battle->All();
			para->All(player->get_status());
		}
		break;

	case 5:
		if (count == 1) {
			StopSoundMem(dungeon_bgm);
			StopSoundMem(battle_bgm);
		}
		if (count <= 60) {
			make_d->All();
			if (count % 3 == 0) {
				gameover_count++;
				if (gameover_count == 4)gameover_count = 0;
			}
			DrawGraph(5 * F_SIZE, 5 * F_SIZE - 40, gameover_pgh[gameover_count], TRUE);
		}
		if (count == 61) {
			gameover_se_flag = true;
		}
		if (count > 60) {
			DrawGraph(0, 0, gameovergh, FALSE);
			gameend = true;
		}
		break;
	}
	sound();
	count++;

}
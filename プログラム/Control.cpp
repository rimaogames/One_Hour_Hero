#include "Control.h"
#include "SceneMgr.h"
#include "InputKey.h"

Control::Control() {

	//ライブラリでinitializeより先に音データを読み込む
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

	//インスタンスを消す
    delete make_d;
	delete player;
	delete battle;
	delete messege;
	delete para;
}

////////初期化/////////
void Control::initialize() {
	//インスタンスの宣言。生成
	make_d = new Make_Dungeon;
	player = new Player;
	battle = new Battle;
	messege = new Messege;
	para = new Parameter;

	//ダンジョンの生成
	make_d->make_dungeon();
	//プレイヤーの初期位置決定。設定
	player->set_init_positon();

	//ライブラリで画像の読み込み
	if (LoadDivGraph("image/go_player.png", 4, 1, 4, 80, 80, gameover_pgh) == -1) {
		MSG("エラー発生(controll)");
	}
	gameovergh = LoadGraph("image/Gameover.jpg");

	//他初期化
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

////////終了処理///////
void Control::finalize() {

    //インスタンスを消す
	delete make_d;
	delete player;
	delete battle;
	delete messege;
	delete para;

	//ライブラリでBGMを終わらせる
	StopSoundMem(dungeon_bgm);
	StopSoundMem(battle_bgm);
	StopSoundMem(win_bgm);
}
void Control::Update() {
	//SceneMgrの参照
	SceneMgr& scenemgr = SceneMgr::Instance();

	//ゲームが終わってない間
	if (!gameend) {
		if (InputKey::GetKeyPush(KEY_INPUT_M)) { //Mキーが押されていたら
			scenemgr.ChangeScene(eScene::Scene_Menu);//シーンをメニューに変更
		}
	}

	//ゲームが終わってENTERが押されたら
	if (gameend && InputKey::GetKeyPush(KEY_INPUT_RETURN)) {
		scenemgr.ChangeScene(eScene::Scene_Result);//シーンを結果画面に変更
	}
}

/////////音の管理関数//////////////
void Control::sound() {
	///それぞれのフラグが立ったならば、ライブラリで音を流す
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

	//ダンジョンBGMフラグが立ったならば勝ちBGMを止める
	if (dungeon_bgm_flag) {
		//バトルBGM、勝利BGMを止める
		StopSoundMem(win_bgm);
		StopSoundMem(battle_bgm);
	}
	//勝ちBGMフラグが立ったならばバトルBGMを止める
	if (win_bgm_flag) {
		StopSoundMem(battle_bgm);
	}

	//バトルBGMがたったらダンジョンBGMを止める
	if (battle_bgm_flag) {
		StopSoundMem(dungeon_bgm);
	}
}





/////////プレイヤーの位置を引数に渡す//////////////
void Control::player_positon(double* x, double* y) {

	double tempx, tempy;
	player->get_potision(&tempx, &tempy);

	*x = tempx;
	*y = tempy;

}

/////////引数の位置のダンジョンの情報を返す//////////////
int Control::dungeon_info(int x,int y) {
	int temp;
	temp=make_d->get_dungeon_info(x, y);

	return temp;
}

//////////////(index_x,index_y)のダンジョンの情報をinfoにする////////////
void Control::set_dungeon_info(int info, int index_x, int index_y) {

	make_d->set_dungeon_info(info, index_x, index_y);
}

//////////////今の場面を引数にする(indexにする)////////////
void Control::set_idx(int index) {

	idx = index;
	count = 0; //カウントを初期化する
}

//////////////現在の階数を返す////////////
int Control::get_floor() {

	return floor;
}

//////////////プレイヤーの情報を引数に渡す////////////
void Control::get_p_status(p_status *pl) {

	*pl=player->get_status();
}

//////////////プレイヤーの情報を引数の情報に更新する////////////
void Control::set_p_status(p_status pl) {

	player->set_status(pl);
}

//////////////プレイヤーに引数分のダメージを与える////////////
bool Control::set_p_damage(int damage) {

	//ダメージがあるならばプレイヤーにダメージを与える
	if (damage > 0) {
		return player->set_damage(damage); //死んだならばTRUEが返ってくる
	}
	else {
		//ダメージがないならばFALSE（生きている)
		return false;
	}
}

//////////////ループで行う実行関数////////////
void Control::All() {

	//サウンドのフラグを初期化
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

	//ゲームオーバーフラグ初期化
	gameend = false;

	/////////idxでゲームの場面を切り替える////////
	switch (idx) {

	//新階層
	case 0:

		//ダンジョンクラスの実行
		make_d->All();

		//パラメータクラスの実行
		para->All(player->get_status());

		//プレイヤークラスの実行
		//アイテムゲットしたならば
		if (player->All(false)) {
			//アイテムゲット場面に移動
			idx = 3;
			count = 0;
		}
         
		//カウント=1
		if (count == 1) {

			//メッセージセット
			messege->set(MESSEGE::NEW_FLOOR);

			//ゲームスタート時のみダンジョンBGMフラグをココで立てる
			if (floor == 1) {
				dungeon_bgm_flag = true;
			}
		}

		//2<カウント<120
		if (count > 2 && count < 120) {
			//メッセージ出力
			messege->draw();

			//もし、プレイヤーが死んだ
			if (player->check_life()) {
				//ゲームオーバー場面へ
				idx = 5;
				count = 0;
			}
		}
		//カウント=120
		if (count == 120) {
			//ダンジョン探索中場面に移動
			idx = 1;
			count = 0;
		}
		break;

	//ダンジョン探索中場面
	case 1:

		//ダンジョン実行
		make_d->All();
		//パラメータ実行
		para->All(player->get_status());


	    //生きているのかチェック
		if (player->check_life()) { //死んだならば
			//ゲームオーバー場面へ
			idx = 5;
			count = 0;
		}
	    
		//プレイヤ実行
		if (player->All(false)) { //アイテムゲットしたならば
			//アイテムゲット場面へ
			idx = 3;
			count = 0;
		}
		break;

	//階数移動
	case 2:

		//生きているか確認
		if (player->check_life()) {
			idx = 5;
			count = 0;
		}

		//ダンジョン実行
		make_d->All();
		//プレイヤ実行(TRUEで動けないようにする)
		player->All(true);

		//////次の階へ/////
		//カウント＞１
		if (count >= 1) {
			//次のフロアへと
			make_d->next_floor();
		}

		//カウント=2
		if (count == 2) {
			//階段上るサウンドフラグを立てる
			stairs_se_flag = true;
		}

		//カウント=90
		if (count == 90) {
			//プレイヤの位置設定とフロア数+1増やす
			player->set_init_positon();
			floor += 1;
		}

		//カウント=165
		if (count == 165) {
			//新階層場面へ
			idx = 0;
			count = 0;
		}
		break;

	//アイテムゲット
	case 3:

		//ダンジョン実行
		make_d->All();
		//プレイヤ実行(動けないようにTRUE)
		player->All(true);
		//パラメータの実行
		para->All(player->get_status());

		//カウント=1
		if (count == 1) {

			//メッセージにどのアイテムを手に入れたのかを与える
			messege->set(player->get_item_info());
			//アイテムゲットの音鳴らす
			item_se_flag = true;
		}

		//カウント>1
		if (count > 1) {

			//メッセージ出力
			messege->draw(); 
		}

		//カウント=80
		if (count == 80) {
			//探検場面にもどる
			idx = 1; 
			count = 0;
		}
		break;

	//バトル場面
	case 4:

		//カウント=1
		if (count == 1) {

			//バトル初期化
			battle->init();
			//バトルBGMフラグ立てる
			battle_bgm_flag = true;
		}

		//カウント>2
		if (count > 2) {

			//バトル実行
			battle->All();
			//パラメータ実行
			para->All(player->get_status());

		}
		break;

    //ゲームオーバー場面
	case 5:

		//カウント=1
		if (count == 1) {

			//BGMを止める
			StopSoundMem(dungeon_bgm);
			StopSoundMem(battle_bgm);
			
		}

		//カウント<=60
		if (count <= 60) {

			//ダンジョン実行
			make_d->All();


			/////プレイヤ回転させる///
			 
			//カウントが3で割り切れる時に
			if (count % 3 == 0) {
				//プレイヤ画像の添え字を変更する
				gameover_index++;
				if (gameover_index == 4)gameover_index = 0; //0,1,2,3,0,1...と変更していく
			}

			//ライブラリでプレイヤを描画する
			DrawGraph(5 * F_SIZE, 5 * F_SIZE - 40, gameover_pgh[gameover_index], TRUE);

		}

		//カウント=61
		if (count == 61) {

			//ゲームオーバーSEのフラグを立てる
			gameover_se_flag = true;

		}

		//カウント>60

		if (count > 60) {

			//ゲームオーバー画面をライブラリで描画する
			DrawGraph(0, 0, gameovergh, FALSE);
			//ゲームオーバーフラグを立てる
			gameend = true;

		}
		break;
	}
	//音管理関数
	sound();

	//カウントをインクリメント
	count++;

}
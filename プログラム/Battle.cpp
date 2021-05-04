#include "Battle.h"

Battle::Battle() {

	//ライブラリで画像を読み込む
	backgh = LoadGraph("image/back.jpg");
	if (LoadDivGraph("image/effect.png", 9, 9, 1, 240, 240, efectgh) == -1) {
		MSG("エラー発生1");
	}
	if (LoadDivGraph("image/magic.png", 8, 8, 1, 240, 240, magicgh) == -1) {
		MSG("エラー発生2");
	}
	com[0] = LoadGraph("image/attack.png");
	com[1] = LoadGraph("image/recover.png");
	com[2] = LoadGraph("image/c_magic.png");
	com[3] = LoadGraph("image/run.png");

	//他初期化
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

//////////初期化////////////////
void Battle::init() {

	//インスタンス生成
	enemy = new Enemy;
	messege = new Messege;

	//flに階数を与える
	int fl;
	Control& cont = Control::Instance(); //Controlクラスの参照
	fl = cont.get_floor();
	//敵の初期化
	enemy->e_init(fl);
    //ターンを敵遭遇ターンにする　
	idx = 10;

	//他初期化
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

///////////エフェクトの設定//////////////////
void Battle::set_effect(int s, int d,int e,int m,int st) {
	
	//引数の値をそれぞれにセット
	swing = s; //背景揺らす
	d_count = d; //敵点滅
	efe_cont = e; //攻撃エフェクト
	mag_cont = m; //魔法エフェクト
	step = st; //敵が一歩前にでる

	
}

///////////描画//////////////////
void Battle::draw() {

	//一様分布乱数生成器の作成
	std::random_device rnd; //真の乱数
	std::mt19937 mt(rnd()); //疑似乱数を真の乱数で初期化
	std::uniform_int_distribution<> randbx(-20, 20); //-20～20の間の一様分布乱数
	std::uniform_int_distribution<> randby(-10, 10); //-10～10の間の一様分布乱数


	/////////背景の描画/////////

	//背景の描画位置
	int bx, by;
	bx = 0; //普通は0
	by = 0;

	//swingが設定(>0)ならば
	if (swing > 0) {
		 
		//swingを減らす
		swing -= 1;
		
		//swingが4で割り切れるならば背景を描画する位置を変える
		if (swing % 4 == 0) {
			//乱数で描画する位置を決定
			bx = randbx(mt);
			by = randby(mt);
			//変数に今の位置を保管しておく
			pre_bx = bx;
			pre_by = by;
		}
		//swingが4で割り切れない時
		else {

			//位置に保管しておいた座標を与える
			bx = pre_bx;
			by = pre_by;
		}
	}

	//ライブラリで設定した座標に背景を描画する
	DrawGraph(bx, by, backgh,FALSE);



	///////敵の描画////////

	//敵の描画
	enemy->draw(d_count,step);

	//敵点滅変数が設定されているならばデクリメントする
	if (d_count > 0) {
		d_count -= 1;
	 }


	////////////コマンドの描画//////////////////


	//プレイヤのターンフラグが立っていたならば
	if (p_turn) {
		//コマンドを描画
		for (int i = 0; i < 4; i++) {
			//選択中のコマンドは少し右に描画
			if (i == now_com) {
				DrawGraph(40, 360 + 60 * i, com[i], TRUE);
			}
			//選択中でないコマンドはx座標20に描画
			else {
				DrawGraph(20, 360 + 60 * i, com[i], TRUE);
			}
		}

	}


	//////////エフェクトの描画//////////////////

	//攻撃エフェクトが設定されたならば
	if (efe_cont > 0) {
		//エフェクトを描画
		DrawGraph(300, 300, efectgh[efe_cont-1], TRUE);
		//カウントが2で割り切れるならばエフェクトの画像を次のコマにする
		if (count % 2 == 0)efe_cont += 1;
        //攻撃エフェクト変数が10で描画終了
		if (efe_cont == 10) {
			efe_cont = 0;
		}
	}

	//魔法エフェクトが設定されたならば
	if (mag_cont > 0) {
		//エフェクトを描画
		DrawGraph(320, 320, magicgh[mag_cont-1], TRUE);
		// カウントが2で割り切れるならばエフェクトの画像を次のコマにする
		if (count % 4 == 0)mag_cont += 1;
		//魔法エフェクト変数が8で描画終了
		if (mag_cont==8) {
			mag_cont = 0;
		}
	}


}


//////////コマンド関数////////////
void Battle::command() {

	//Controlの参照
	Control& cont = Control::Instance();

	/////////コマンドの選択/////////

	//下キーが押されたら
	if (InputKey::GetKeyPush(KEY_INPUT_DOWN)) {
		now_com = (now_com + 1) % cnum;//選択状態を一つ下げる
	}

	//上キーが押されたら
	else if (InputKey::GetKeyPush(KEY_INPUT_UP)) {
		now_com = (now_com + (cnum - 1)) % cnum;//選択状態を一つ上げる
	}

	//Enterが押されたら
	if (InputKey::GetKeyPush(KEY_INPUT_RETURN)) {

		//今選択しているものでターンの添え字を変える
		switch (now_com) {

		case COM::ATTACK: //攻撃選択
			idx = 12; 
			count = 0;
			break;
		case COM::USE_POTION: //ポーション選択
			idx = 13;
			count = 0;
			break;
		case COM::MAGIC: //魔法選択
			idx = 14;
			count = 0;
			break;
		case COM::RUN: //逃げる選択
			idx = 15;
			count = 0;
			break;
		default:
			break;
		}
	}

}

////////////レベルアップ（引数に経験値)/////////////
void  Battle::levelup(int point) {

	//Controlクラスの参照
	Control& cont = Control::Instance();

	//plにプレイヤの情報を与える
	p_status pl;
	cont.get_p_status(&pl);


	//残った経験値を計算
	e_point = pl.point + point - pl.pointmax; //(今所持している経験値)+(今回獲得した経験値) - 次のレベルまでに必要な経験値 


	//プレイヤの情報を設定

	pl.lifemax = pl.lifemax + pl.level * 30; //ライフ最大値変更
	pl.life = pl.lifemax; //ライフ最大値まで回復
	pl.point = 0; //経験値初期化
	pl.pointmax = pl.pointmax + pl.level * 20; //次のレベルまでの経験値変更
	pl.level += 1; //レベル+1
	pl.power += 5; //力+5
	//プレイヤの情報をplにする
	cont.set_p_status(pl);

}


/////////体力回復/////////
void Battle::recover() {

	//Control参照
	Control& cont = Control::Instance();

	//plに今の情報を与える
	p_status pl;
	cont.get_p_status(&pl);

	//ポーション所持数-1
	pl.potion -= 1;
	//ライフをライフ最大値まで回復
	pl.life = pl.lifemax;

	//プレイヤの情報をplに変更
	cont.set_p_status(pl);
}


//ループで行う実行関数
void Battle::All() {

	//Control参照
	Control& cont = Control::Instance();

	//一様分布乱数生成器の作成
	std::random_device rnd; //真の乱数
	std::mt19937 mt(rnd()); //疑似乱数を真の乱数で初期化
	std::uniform_int_distribution<> rand10(0, 10); //0～10の間の一様分布乱数

	//描画
	draw();



	//////////////いまのターンで処理を変更する///////////////

	switch (idx) {

	//戦闘開始
	case 10:  

		//カウント=1
		if (count == 1) {
			//敵遭遇メッセージ設定
			messege->set(MESSEGE::ENCOUNTER);
		}

		//カウント>2
		if (count > 2) {
			//メッセージ出力
			messege->draw();
		}

		//カウント=60
		if (count == 60) {
			//コマンド入力待ちターンへ移動
			idx = 11;
			count = 0;
		}

		break;

	//コマンド入力待ち
	case 11: 

		//メッセージ出力
		messege->draw();

		//カウント=1
		if (count == 1) {
			//プレイヤのターンフラグを立てる
			p_turn = true;

			//メッセージにプレイヤのターンメッセージを設定
			messege->set(MESSEGE::P_TUEN);
		}

		//コマンド
	    command();

		break;

	//プレイヤーの攻撃
	case 12:

		//メッセージを出力
		messege->draw();

		//カウント=1
		if (count == 1) {

			//メッセージを提の攻撃メッセージに設定
			messege->set(MESSEGE::P_ATTACK);

			//プレイヤのターンフラグをおろす
			p_turn = false;

			//plにプレイヤの情報を取得
			p_status pl;
			cont.get_p_status(&pl);

			//敵へのダメージをプレイヤの力と乱数で決定
			e_damage = pl.power + rand10(mt); 
		}

		//カウント=5
		if (count == 5) {

		   //エフェクト設定（攻撃エフェクト)
			set_effect(0, 0, 1, 0, 0);
			//攻撃SEフラグを立てる
			cont.p_attack_se_flag = true;
		}

		//カウント=35
		if (count == 35) {
			//メッセージに敵へのダメージつきメッセージを設定
			messege->set_dam(e_damage);

			//エフェクト設定(敵点滅)
			set_effect(0, 40, 0, 0, 0);
			
			//敵にダメージをセット
			if (enemy->set_damage(e_damage) == true) { //敵死亡

				//勝利ターンへ移動
				idx = 17;
				count = 0;
			}

        //カウント=80
		}
		if (count == 80) {
			//敵の攻撃ターンへ移動
			idx = 16;
			count = 0;
		}

		break;

	//体力回復
	case 13: 

		//メッセージ出力
		messege->draw();

		//カウント=1
		if (count == 1) {

			//メッセージをポーション使用メッセージに設定
			messege->set(MESSEGE::P_POTION);
		}


		//カウント=40
		if (count == 40) {

			//plにプレイヤの情報を取得
			p_status pl;
			cont.get_p_status(&pl);

			//ポーション所持数が0
			if (pl.potion == 0) {
				//メッセージにアイテム未所持メッセージを設定
				messege->set(MESSEGE::NO_ITEM);

				//アイテム使うフラグはfalseのまま
				use_item = false;
			}

			//ポーション所持している
			else {

				//アイテム使用フラグを立てる
				use_item = true;
			}
		}

		//カウント=80
		if (count == 80) {

			//アイテム使用フラグが立っているならば
			if (use_item == true) {

				//メッセージに回復したメッセージを設定
				messege->set(MESSEGE::RECOVER);

				//回復
				recover();

				//回復SEフラグを立てる
				cont.recover_se_flag = true;

                //アイテム使用フラグをおろす
				use_item = false;
			}

			//アイテム使用フラグが立っていないならば
			else {
				//kコマンド入力待ちターンへ移動
				idx = 11;
				count = 0;
			}
		}

		//カウント=120
		if (count == 120) {
			//敵の攻撃ターンへ移動
			idx = 16;
			count = 0;
		}

		break;

	//魔法
	case 14:

		//メッセージを出力
		messege->draw();


		//カウント=1
		if (count == 1) {

			//メッセージに魔法メッセージを設定
			messege->set(MESSEGE::P_MAGIC);
		}

		//カウント=40
		if (count == 40) {

			//plにプレイヤの情報を取得
			p_status pl;
			cont.get_p_status(&pl);

			//プレイヤの魔法石所持数が0ならば
			if (pl.mp == 0) {

				//メッセージにアイテム未所持メッセージを設定
				messege->set(MESSEGE::NO_ITEM);

				//アイテム使用フラグはそのまま
				use_item = false;
			}

			//魔法石所持しているならば
			else {

				//魔法石所持数-1
				pl.mp -= 1;

				//プレイヤの情報をplに更新
				cont.set_p_status(pl);

				//エフェクト設定(魔法エフェクト)
				set_effect(0, 0, 0, 1, 0);

				//魔法SEフラグを立てる
				cont.magic_se_flag = true;

				//魔法使用フラグを立てる
				use_item = true;
			}
		}

		//カウント=80
		if (count == 80) {

			//アイテム使用フラグが立っているならば
			if (use_item == true) {

				//敵へのダメージを200を基本とし、ランダムで決める
				e_damage = 200 + rand10(mt)*2;

				//メッセージに敵へのダメージ付きのメッセージを設定
				messege->set_dam(e_damage);

				//エフェクト設定(敵点滅)
				set_effect(0, 40, 0,0,0);

				//アイテム使用フラグをおろす
				use_item = false;

				//敵にダメージを設定する
				if (enemy->set_damage(e_damage) == true) { //敵が死んだ

					//勝利ターンへ移動
					idx = 17;
					count = 0;
				}
			}

			//もしアイテム使用フラグが立っていない
			else {

				//コマンド入力待ちターンへ移動
				idx = 11;
				count = 0;
			}
		}

		//カウント=120
		if (count == 120) {

			//敵の攻撃ターンへ移動
			idx = 16;
			count = 0;
		}

		break;

	//逃げる
	case 15: 

		//メッセージを出力
		messege->draw();

		//カウント＝１
		if (count == 1) {
			//メッセージを逃げるメッセージに設定する
			messege->set(MESSEGE::P_RUN);
		}

		//カウント=50
		if (count == 50) {

			//乱数
			int temp = rand10(mt);

			//乱数で4以下だったら逃亡成功
			if (temp <= 4) {

				//逃げるＳＥフラグを立てる
				cont.run_se_flag = true;

				//ダンジョン探索場面に移動
				cont.set_idx(1);

				//ダンジョンＢＧＭフラグを立てる
				cont.dungeon_bgm_flag = true;
			}

			//乱数で5以上 逃亡失敗
			else {

				//メッセージに逃亡失敗メッセージを設定する
				messege->set(MESSEGE::P_NOT_RUN);
			}
		}

		//カウント=100
		if (count == 100) {

			//敵の攻撃ターンへ移動
			idx = 16;
			count = 0;
		}

		break;

	//敵の攻撃
	case 16: 

		//メッセージ出力
		messege->draw();


		//カウント＝１
		if (count == 1) {

			//メッセージに敵の攻撃メッセージを設定する
			messege->set(MESSEGE::E_ATTACK);
		}

		//カウント=10
		if (count == 10) {

			//エフェクト設定(敵が一歩前へ)
			set_effect(0, 0, 0, 0, 40);

			//攻撃ＳＥフラグを立てる
			cont.p_attack_se_flag = true;

			//プレイヤへのダメージを敵の力と乱数で決定
			p_damage = enemy->get_power() + rand() % 10;
		}

		//カウント=30
		if (count == 30) {

			//メッセージをプレイヤへのダメージ付きメッセージに設定
			messege->set_dam(p_damage);

			//エフェクト設定(背景揺らす)
		    set_effect(40, 0, 0, 0, 0);

			//敵の攻撃ＳＥフラグを立てる
			cont.e_attack_se_flag = true;


			//プレイヤにダメージをセットする
			if (cont.set_p_damage(p_damage)== true) { //プレイヤ死んだ

				//敗北ターンへ移動
				idx = 19;
				count = 0;
			}
		}

		//カウント=90
		if (count == 90) {

			//コマンド入力待ちターンへ移動
			idx = 11;
			count = 0;
		}

		break;

	//勝ち
	case 17:

		//カウント=1
		if (count == 1) {

			//メッセージを勝ちメッセージに設定
			messege->set(MESSEGE::WIN);

			//勝利ＢＧＭフラグを立てる
			cont.win_bgm_flag = true;
		}

		//カウント>2
		if (count > 2) {

			//メッセージを出力
			messege->draw();
		}

		//カウント=400
		if (count == 400) {

			//敵の経験値をe_pointに与える
			enemy->get_point(&e_point);

			//plにプレイヤの情報を取得
			p_status pl;
			cont.get_p_status(&pl);

			//もし、(プレイヤが今持っている経験値)+（今回手にいれた経験値)>=(次のレベルまでに必要な経験値)ならば
			if (pl.point + e_point >= pl.pointmax) {

				//レベルアップシーンへ
				idx = 18;
				count = 0;
			}

			//まだ経験値が足りないならば
			else {

				//経験値に今回の経験値を足す
				pl.point += e_point;

				//プレイヤの情報をplに更新
				cont.set_p_status(pl);

				//ダンジョン探索BGMフラグをを立てる
				cont.dungeon_bgm_flag = true;

				//ダンジョン探索場面に移動
				cont.set_idx(1);

			}
		}

		break;

     // レベルアップ
	case 18:

		//カウント=1
		if (count == 1) {

			//レベルアップメッセージを設定
			messege->set(MESSEGE::LEVELUP);

			//レベルアップする
			levelup(e_point);
		}

		//カウント=2
		if (count > 2) {

			//メッセージを出力
			messege->draw();
		}

		//カウント=350
		if (count == 350) {

			//plにプレイヤの情報を取得
			p_status pl;
			cont.get_p_status(&pl);

			//(プレイヤが今持っている経験値(0))+（残った経験値)>=(次のレベルまでに必要な経験値)
			if (pl.point + e_point >= pl.pointmax) {
				//もう一度レベルアップターン(count=0)へ移動
				idx = 17;
				count = 0;
			}

			//残った経験値が次のレベルに必要な経験値を満たしていないなら
			else {

				//経験値に残った経験値を与える
				pl.point += e_point;

				//プレイヤの情報をplに更新
				cont.set_p_status(pl);

				//ダンジョンBGMフラグを立てる
				cont.dungeon_bgm_flag = true;

				//ダンジョン探索場面に移動
				cont.set_idx(1);

			}
		}

		break;


	//負け
	case 19: 

		//メッセージを出力
		messege->draw();

		//カウント=1
		if (count == 1) {

			//メッセージを負けメッセージに設定
			messege->set(MESSEGE::LOSE);
		}

		//カウント=150
		if (count == 150) {

			//メッセージインスタンスを消去
			delete messege;

			//ゲームオーバー場面に移動
			cont.set_idx(5);
		}
	}

	//カウントをインクリメント
	count++;
}
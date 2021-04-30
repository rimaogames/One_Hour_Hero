#pragma once
#include "define.h"
class Menu
{//選択項目
	typedef enum { //列挙型
		mGame,        //ゲーム開始 0
		mHowto,      //遊び方　2
		mNum,        //本項目の数 3
	} mScene;

	//メニュー画面

	private:
		int menugraph;//メニュー画面

		int cursor[6];//カーソル
		int NowSelect;//今選択中の項目
		int count; //カウンと

		int menu_bgm;//メニュー画面のBGMハンドル
		bool selectsound_flag; //nowselect_soundを鳴らすかのフラグ
		int select_sound; //ゲームスタートを選んだ時に鳴らす音楽のハンドル

	private:
		void draw(); //描画
		void sound();
	public:
		Menu();
		void initialize(); //初期化
		void finalize();//終了の処理
		void Update(); //オーバーライド
		void All();  //オーバーライド
	};

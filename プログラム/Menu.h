#pragma once
#include "define.h"
#include "SceneMgr.h"
#include "InputKey.h"



class Menu
{
	//選択項目
	typedef enum { //列挙型
		mGame,        //ゲーム開始 
		mHowto,      //遊び方　
		mNum,        //本項目の数 
	} mScene;

//変数
private:
	    
	    //グラフィックハンドル
		int menugraph;//メニュー画面
		int cursor[6];//カーソル

		
		int NowSelect;//今選択中の項目
		int count; //ループのカウント


		int menu_bgm;//メニュー画面のBGMハンドル

		int select_sound; //ゲームスタートを選んだ時に鳴らす音楽のハンドル
		bool selectsound_flag; //nowselect_soundを鳴らすかのフラグ

//関数
private:
		void draw(); //描画
		void sound(); //音の管理

public:
		Menu();
		void initialize(); //初期化
		void finalize();//終了の処理
		void Update(); //シーンの更新
		void All();  //ループで行う関数
};

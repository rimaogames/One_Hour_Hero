#pragma once
#include "define.h"
#include "Menu.h"
#include "Howto.h"
#include "Result.h"
#include "SceneMgr.h"
#include "Control.h"

class Menu;
class Result;
class Howto;

//////シーンを管理するクラス/////////
class SceneMgr
{

//変数
private:

	//シーン
	static eScene Scene; //今のシーン
	static eScene NextScene; //次のシーン


	//インスタンス
	Menu* menu = 0; //メニューシーン
	Howto* howto = 0; //遊び方説明シーン
	Result* result = 0; //結果シーン


//関数
private:

	SceneMgr();  //２つのインスタンス持つの禁止（シングルトン）

	void initialize(eScene scene); //初期化管理
	void finalize(eScene scene); //終わりの管理


public:
	void Update(); //シーン移動管理
	void All();   //それぞれのAll(ループ間で呼び出す関数)の管理
	void ChangeScene(eScene nextScene);  //次のシーンを引数のものにする

	void loop(); //Mainで呼び出される実行関数

	static SceneMgr& Instance() {//クラス静的変数、自身のインスタンスを格納
		static SceneMgr scenemgr;//静的変数として宣言
		return scenemgr;
	}
};

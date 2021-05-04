#pragma once
#include "define.h"
#include "Control.h"


//メッセージを表示するクラス
class Messege
{
//変数
private:
	//グラフィックハンドル
	int b_messege[MESSEGE::messege_num]; //メッセージ
	int number[10]; //数字(大きい)
	int number3[10];//数字（小さい）

	int index; //何のメッセージを表示するのかを保存する変数

	//数字を描画する時に使用する変数
	char buf[100]; //数字を保持する
	int num; //数字の数を保持する

//関数
public:
	Messege();
	~Messege();

	void set(int str); //何のメッセージを表示するのかを設定する
	void set_dam(int damage); //ダメージ付きのメッセージを設定する
	void draw(); //描画
};


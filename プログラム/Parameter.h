#pragma once
#include "define.h"

//パラメータの表示クラス
class Parameter
{
//変数
private:
	int parameter; //パラメータのグラフィックハンドル
	int number2[10]; //数字のグラフィックハンドル

//関数
private:
	void draw(p_status status); //描画
public:
	Parameter();
	void All(p_status status); //ループで行うAll関数
};


#pragma once
#include "define.h"

//遊び方説明シーンクラス

class Howto
{
//変数
private:
	int howgraphgh; //グラフィックハンドル

//関数
public:
	Howto();
	~Howto();
	void Update();//更新（オーバーライド）
	void All();//実行（オーバーライド）
};


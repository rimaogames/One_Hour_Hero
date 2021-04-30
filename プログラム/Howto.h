#pragma once
#include "define.h"
class Howto
{
private:
	int howgraphgh; //グラフィックハンドル
public:
	Howto();
	~Howto();
	void Update();//更新（オーバーライド）
	void All();//実行（オーバーライド）
};


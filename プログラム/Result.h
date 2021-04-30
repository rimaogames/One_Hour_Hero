#pragma once
#include "define.h"
class Result
{
private:

    int result_bgm;
    int upgh;//はいすこあ更新文字
    int resultgh;//画面のグラフィックハンドル
    int g_number[10];//数字のグラフィックハンドル

    int rescore;//スコア
    int rehigh_score;//ハイスコア

private:
    void draw();//描画
    void setresult();//結果をセットする
public:
    Result();
    void initialize();//初期化
    void finalize();//終了の処理
    void Update();//オーバーライド
    void All();//オーバーライド

};


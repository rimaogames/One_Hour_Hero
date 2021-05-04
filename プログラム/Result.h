#pragma once
#include "define.h"
#include "Control.h"
#include "SceneMgr.h"

//////// 結果画面クラス///////////
class Result
{
//　変数
private:

    //サウンドハンドル
    int result_bgm;

    //グラフィックハンドル
    int upgh;//はいすこあ更新文字
    int resultgh;//画面のグラフィックハンドル
    int g_number[10];//数字のグラフィックハンドル


    //スコア管理変数
    int rescore;//スコア
    int rehigh_score;//ハイスコア



//　関数
private:

    void draw();//描画
    void set_result();//結果をセットする

public:
    Result();
    void initialize();//初期化
    void finalize();//終了の処理
    void Update();//シーンの移動
    void All();//ループで行う関数

};


#pragma once
#include "define.h"

//ダンジョンクラス
class Make_Dungeon
{
private:
 
    int maze[MAZE_H][MAZE_W];   //迷路の情報を保持する配列 1=壁　0=道
    int dungeon[DUNG_H][DUNG_W];//ダンジョンの情報を保持する配列

    //グラフィックハンドル
    int floorgh; //道
    int boxgh; //宝箱
    int cocoongh; //繭
    int stairsgh; //階段
    int wallgh; //壁
    int wall2gh; //壁（天井）
    int darkgh; //暗闇

    int count;//ループカウント

//関数
private:
    void draw();  //描画
    void set_event(); //イベントをセット
public:
    Make_Dungeon();
    ~Make_Dungeon();
    void make_dungeon(); //ダンジョンの生成
    void next_floor(); //次の階層を作成
    int get_dungeon_info(int index_x,int index_y); //添え字のダンジョンの情報を返す
    void set_dungeon_info(int info,int index_x,int index_y); //添え字の位置のダンジョンの情報を引数の情報に更新
    void All(); //ループで行う関数

};

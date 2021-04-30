#pragma once
#include "define.h"
class Make_Dungeon
{
private:
    //色
    int SKY; //水色
    int GRAY;  //灰色
    int BLACK; //黒
    int WHITE;
    int maze[MAZE_H][MAZE_W];   //迷路の情報を保持する配列 1=壁　0=道
    int dungeon[DUNG_H][DUNG_W];//ダンジョンの情報を保持する配列

    int floorgh;
    int boxgh;
    int cocoongh;
    int stairsgh;
    int wallgh;
    int wall2gh;
    int darkgh;
    int blackgh;

    int countx;
    int county;
    int count;
private:
    void draw();  //描画
    void set_event();
public:
    void make_dungeon(); //ダンジョンの生成
    void next_floor();
    int get_dungeon_info(int index_x,int index_y); //添え字のダンジョンの情報を返す
    void set_dungeon_info(int info,int index_x,int index_y);
    Make_Dungeon();
    void All();

};

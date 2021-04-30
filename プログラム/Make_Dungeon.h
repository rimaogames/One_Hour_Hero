#pragma once
#include "define.h"
class Make_Dungeon
{
private:
    //�F
    int SKY; //���F
    int GRAY;  //�D�F
    int BLACK; //��
    int WHITE;
    int maze[MAZE_H][MAZE_W];   //���H�̏���ێ�����z�� 1=�ǁ@0=��
    int dungeon[DUNG_H][DUNG_W];//�_���W�����̏���ێ�����z��

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
    void draw();  //�`��
    void set_event();
public:
    void make_dungeon(); //�_���W�����̐���
    void next_floor();
    int get_dungeon_info(int index_x,int index_y); //�Y�����̃_���W�����̏���Ԃ�
    void set_dungeon_info(int info,int index_x,int index_y);
    Make_Dungeon();
    void All();

};

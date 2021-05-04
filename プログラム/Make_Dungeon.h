#pragma once
#include "define.h"

//�_���W�����N���X
class Make_Dungeon
{
private:
 
    int maze[MAZE_H][MAZE_W];   //���H�̏���ێ�����z�� 1=�ǁ@0=��
    int dungeon[DUNG_H][DUNG_W];//�_���W�����̏���ێ�����z��

    //�O���t�B�b�N�n���h��
    int floorgh; //��
    int boxgh; //��
    int cocoongh; //��
    int stairsgh; //�K�i
    int wallgh; //��
    int wall2gh; //�ǁi�V��j
    int darkgh; //�È�

    int count;//���[�v�J�E���g

//�֐�
private:
    void draw();  //�`��
    void set_event(); //�C�x���g���Z�b�g
public:
    Make_Dungeon();
    ~Make_Dungeon();
    void make_dungeon(); //�_���W�����̐���
    void next_floor(); //���̊K�w���쐬
    int get_dungeon_info(int index_x,int index_y); //�Y�����̃_���W�����̏���Ԃ�
    void set_dungeon_info(int info,int index_x,int index_y); //�Y�����̈ʒu�̃_���W�����̏��������̏��ɍX�V
    void All(); //���[�v�ōs���֐�

};

#pragma once
#include "define.h"
#include "Control.h"
#include "SceneMgr.h"

//////// ���ʉ�ʃN���X///////////
class Result
{
//�@�ϐ�
private:

    //�T�E���h�n���h��
    int result_bgm;

    //�O���t�B�b�N�n���h��
    int upgh;//�͂��������X�V����
    int resultgh;//��ʂ̃O���t�B�b�N�n���h��
    int g_number[10];//�����̃O���t�B�b�N�n���h��


    //�X�R�A�Ǘ��ϐ�
    int rescore;//�X�R�A
    int rehigh_score;//�n�C�X�R�A



//�@�֐�
private:

    void draw();//�`��
    void set_result();//���ʂ��Z�b�g����

public:
    Result();
    void initialize();//������
    void finalize();//�I���̏���
    void Update();//�V�[���̈ړ�
    void All();//���[�v�ōs���֐�

};


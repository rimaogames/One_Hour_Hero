#pragma once
#include "define.h"
class Result
{
private:

    int result_bgm;
    int upgh;//�͂��������X�V����
    int resultgh;//��ʂ̃O���t�B�b�N�n���h��
    int g_number[10];//�����̃O���t�B�b�N�n���h��

    int rescore;//�X�R�A
    int rehigh_score;//�n�C�X�R�A

private:
    void draw();//�`��
    void setresult();//���ʂ��Z�b�g����
public:
    Result();
    void initialize();//������
    void finalize();//�I���̏���
    void Update();//�I�[�o�[���C�h
    void All();//�I�[�o�[���C�h

};


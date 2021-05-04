#include "SceneMgr.h"

//�ŏ��̓��j���[��ʂɂ���
eScene SceneMgr::NextScene = eScene::Scene_None;
eScene SceneMgr::Scene = eScene::Scene_Menu;

//////////�R���X�g���N�^/////////
SceneMgr::SceneMgr() {

    //�C���X�^���X
    menu = new Menu;
    result = new Result;


}

/////////������/////////
void SceneMgr::initialize(eScene scene) {
    //Control�N���X�̎Q��
    Control& control = Control::Instance();

    switch (scene) {          //�V�[���ɂ���ď����𕪊�

    case eScene::Scene_Menu:       //�w���ʂ����j���[��ʂȂ�
        menu->initialize();                 //���j���[��ʂ̏���������������
        break;
    case eScene::Scene_Game:       //�w���ʂ��Q�[����ʂȂ�
        control.initialize();           //�Q�[����ʂ̏���������������             
        break;
    case eScene::Scene_Howto:     //�w���ʂ��V�ѕ���ʂȂ�
        howto = new Howto;          //�V�ѕ���ʂ̏���������������(�C���X�^���X����)
        break;
    case eScene::Scene_Result:  //�w���ʂ����ʉ�ʂȂ�
        result->initialize();             //���ʉ�ʂ̏���������������
        break;
    default:
        break;
    }
}


/////////�I���̏���/////////
void SceneMgr::finalize(eScene scene) {

    //Control�N���X�̎Q��
    Control& control = Control::Instance();


    //////////////�V�[���ɂ���ď����𕪊�/////////////////

    switch (scene) {        
    case eScene::Scene_Menu:     //�w���ʂ����j���[��ʂȂ�
        menu->finalize();                //���j���[��ʂ̏I���̏���������
        break;
    case eScene::Scene_Game:    //�w���ʂ��Q�[����ʂȂ�
        control.finalize();         //�Q�[����ʂ̏I���̏���
        break;
    case eScene::Scene_Howto:  //�w���ʂ��V�ѕ���ʂȂ�
        delete howto;             //�V�ѕ���ʂ̏I���̏���
        break;
    case eScene::Scene_Result:  //�w���ʂ����ʉ�ʂȂ�
        result->finalize();             //���ʉ�ʂ̏I���̏���
        break;
    default:
        break;

    }
}


///////���̃V�[���������̃V�[���ɐݒ�(���N���X����Ăяo�����)///////
void SceneMgr::ChangeScene(eScene scene) {

    //���̃V�[���Ɉ����̃V�[�������
    NextScene = scene;

}


/////////////��ʂ̍X�V////////////
void SceneMgr::Update() {

    //��ʈړ�����Ȃ��
    if (NextScene != eScene::Scene_None) {
        //���̉�ʂ͏I������
        finalize(Scene);
        //��ʂ͓���ւ�
        Scene = NextScene;
        //�\��̃V�[���͏�����
        NextScene = eScene::Scene_None;
        //���̃V�[���i�\�肳��Ă����V�[���j��������������
        initialize(Scene);
    }

    //Control�N���X�̎Q��
    Control& control = Control::Instance();

    ////////////////��ʂ��X�V���閽�߂����邩����/////////////////

    switch (Scene) {       //�V�[���ɂ���ď����𕪊�
    case eScene::Scene_Menu:    //���݂̉�ʂ����j���[�Ȃ�
        menu->Update();            //���j���[��ʂ̍X�V�֐�
        break;//�ȉ���
    case eScene::Scene_Game:    //���݂̉�ʂ��Q�[���Ȃ�
        control.Update();          //�Q�[����ʂ̍X�V�֐�
        break;
    case eScene::Scene_Howto:  //���݂̉�ʂ��V�ѕ������Ȃ�
        howto->Update();           //�V�ѕ��̍X�V�֐�
        break;
    case eScene::Scene_Result:     //���݂̉�ʂ����ʉ�ʂȂ�
        result->Update();            //���ʂ̍X�V�֐�
        break;
    default:
        break;

    }

}


////////All�֐��̎��s/////////
void SceneMgr::All() {
    //Control�N���X�̎Q��
    Control& control = Control::Instance();


    switch (Scene) {      //�V�[���ɂ���ď����𕪊�
    case eScene::Scene_Menu:   //���݂̉�ʂ����j���[��ʂȂ�
        menu->All();              //���j���[��ʂ̏���������
        break;//�ȉ���
    case eScene::Scene_Game: //���݂̉�ʂ��Q�[����ʂȂ�
        control.All();            //�Q�[���̏���������
        break;
    case eScene::Scene_Howto:    //���݂̉�ʂ��V�ѕ���ʂȂ�
        howto->All();              //�V�ѕ���ʂ̏���������
        break;
    case eScene::Scene_Result: //���݂̉�ʂ����ʉ�ʂȂ�
        result->All();             //���ʂ̏���������
        break;
    }
}

///////Main�ŌĂяo�����֐�//////////
void SceneMgr::loop() {

    //�X�V
    Update();
    //���s
    All();
}

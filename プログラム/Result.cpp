#include "Result.h"


Result::Result() {
	//���C�u�����ŉ��̓ǂݍ���
	result_bgm = LoadSoundMem("music/result.ogg");

	//��������(0,NULL��)
	memset(g_number, 0, sizeof(g_number));
	resultgh = NULL;
	upgh = NULL;
}



//////������/////////
void Result::initialize() {

	//���C�u�����ŉ摜�̓ǂݍ���
	LoadDivGraph("image/messege/number.png", 10, 10, 1, 27, 34, g_number);
	resultgh = LoadGraph("image/Result.jpg");
	upgh = LoadGraph("image/rehi.png");

	//���ʂ��Z�b�g
	set_result();

	//��������
	rehigh_score = hiscore; //�n�C�X�R�A�ɍ��̃n�C�X�R�A���Z�b�g����

	//bgm��炷
	PlaySoundMem(result_bgm, DX_PLAYTYPE_LOOP, TRUE);

}

/////////�I���̏���///////
void Result::finalize(){
	//�摜���̂Ă�
	for (int i = 0; i < 9; i++) {
		DeleteGraph(g_number[i]);
	}
	DeleteGraph(resultgh);
	DeleteGraph(upgh);

	//bgm�̏I��
	StopSoundMem(result_bgm);
}

/////////���ʂ��Z�b�g///////
void Result::set_result() {

	Control& cont = Control::Instance();
	//�K���̎擾
	rescore = cont.get_floor();
}

////////�`��///////
void Result::draw() {
	
	///���C�u�����Ŕw�i�摜�̕`��
	DrawGraph(0, 0, resultgh, FALSE);

    //�X�R�A�̕`��
	char buf[100];
	memset(buf, 0, sizeof(buf));
	int h_num = 0, s_num = 0;


	//�n�C�X�R�A
	//buf�ɃX�R�A������Bs_num�ɂ͕�����������
	h_num = sprintf_s(buf, "%d", rehigh_score);
	//���C�u�����Œl�̏����n�߂�700�B
    //buf�ɂ�1�o�C�g���������i�[����Ă���Bg_number[buf[i]-0]�Ő�����buf[i]-���擾
	for (int i = 0; i < h_num; i++) {
		DrawGraph(700 + (i * NUMBER1_W), 290, g_number[buf[i] - '0'], TRUE);

	}

	//�X�R�A�i���l��)
	s_num = sprintf_s(buf, "%d", rescore);
	for (int i = 0; i < s_num; i++) {
		DrawGraph(700 + (i * NUMBER1_W), 410, g_number[buf[i] - '0'], TRUE);
	}

	//�n�C�X�R�A�X�V�Ȃ�n�C�X�R�A�X�V�Ƃ�������������
	if (rescore > rehigh_score) {
		DrawGraph(150, 600, upgh, TRUE);
	}
}

////////��ʂ̍X�V////////////
void Result::Update() {

	//SceneMgr�N���X�̎Q��
	SceneMgr& scenemgr = SceneMgr::Instance();

	//�\�����I������G�������ꂽ��
	if (InputKey::GetKeyPush(KEY_INPUT_RETURN) != 0) {
		scenemgr.ChangeScene(eScene::Scene_Menu); //���j���[��ʂɈړ�
	}


}

///////���ʉ�ʂ̏������s/////////
void Result::All() {

	//�`��
	draw();

	//�n�C�X�R�A�X�V
	if (rescore > rehigh_score) {
		hiscore = rescore;
	}
}

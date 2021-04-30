#include "Result.h"
#include "Control.h"
#include "SceneMgr.h"

Result::Result() {
	//���C�u�����ŉ��̓ǂݍ���
	result_bgm = LoadSoundMem("music/result.ogg");
}



//������
void Result::initialize() {
	//���C�u�����ŉ摜�̓ǂݍ���
	LoadDivGraph("image/messege/number.png", 10, 10, 1, 27, 34, g_number);
	resultgh = LoadGraph("image/Result.jpg");
	upgh = LoadGraph("image/rehi.png");

	//���ʂ��Z�b�g
	setresult();
	//��������
	rehigh_score = hiscore;
	PlaySoundMem(result_bgm, DX_PLAYTYPE_LOOP, TRUE);
}

//�I���̏���
void Result::finalize(){
	DeleteGraph(g_number[9]);
	DeleteGraph(resultgh);
	DeleteGraph(upgh);
	StopSoundMem(result_bgm);
}

//���ʂ��Z�b�g
void Result::setresult() {
	Control& cont = Control::Instance();
	rescore = cont.get_floor();
}

//�`��
void Result::draw() {
	DrawGraph(0, 0, resultgh, FALSE);
	char buf[100];
	memset(buf, 0, sizeof(buf));
	int h_num = 0, s_num = 0, g_num = 0;


	s_num = sprintf_s(buf, "%d", rescore);//buf�ɃX�R�A������Bnum�ɂ͕�����������
	for (int i = 0; i < s_num; i++) {
		//���C�u�����Œl�̏����n�߂�SOCRE_X+20�B��y���W45�ɐ������L���B
		//buf�ɂ�1�o�C�g���������i�[����Ă���Bg_number[buf[i]-0]�Ő�����buf[i]-���擾
		DrawGraph(700 + (i * NUMBER_W), 410, g_number[buf[i] - '0'], TRUE);
	}

	h_num = sprintf_s(buf, "%d", rehigh_score);//buf�Ƀn�C�X�R�A������Bnum�ɂ͕�����������
	for (int i = 0; i < h_num; i++) {
		//���C�u�����Œl�̏����n�߂�SOCRE_X+20�B��y���W45�ɐ������L���B
		//buf�ɂ�1�o�C�g���������i�[����Ă���Bg_number[buf[i]-0]�Ő�����buf[i]-���擾
		DrawGraph(700 + (i * NUMBER_W), 290, g_number[buf[i] - '0'], TRUE);

	}
		//�n�C�X�R�A�X�V�Ȃ�n�C�X�R�A�X�V�Ƃ�������������
	if (rescore > rehigh_score) {
		DrawGraph(150, 600, upgh, TRUE);
	}
}

//��ʂ̍X�V
void Result::Update() {
	//SceneMgr�N���X�̎Q��
	SceneMgr& scenemgr = SceneMgr::Instance();
	//�\�����I������G�������ꂽ��
	if (InputKey::GetKeyPush(KEY_INPUT_RETURN) != 0) {
		scenemgr.ChangeScene(eScene::Scene_Menu);//�V�[�����Q�[���ɕύX�i�ĊJ�j
	}


}

//���s
void Result::All() {
	//�`��
	draw();
	if (rescore > rehigh_score) {
		hiscore = rescore;
	}
}

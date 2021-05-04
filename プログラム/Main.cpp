#include "define.h"
#include "InputKey.h"
#include "SceneMgr.h"
int hiscore = 1;


// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    ChangeWindowMode(TRUE);//ライブラリでゲーム画面を表示
    SetGraphMode(880 ,720, 32); //画面の大きさ設定
    
    
    if (DxLib_Init() == -1) return -1;//DXライブラリの初期化
    SetDrawScreen(DX_SCREEN_BACK);//ライブラリで描画先を裏画面に

    //キーの入力管理クラスのインスタンス
     InputKey input;

     //シーン管理クラスの参照
     SceneMgr& scenemgr = SceneMgr::Instance();

     while (!ProcessMessage()) {//ウィンドウが閉じるまで

	      //ライブラリで描画画面の前の画像消す(裏画面)
	      ClearDrawScreen();

	      //キーの入力状態の更新
	      input.Update_Keystate();

          //ゲームの処理
          scenemgr.loop();


     	  //ライブラリで表画面に転送
	      ScreenFlip();

     }

      DxLib_End(); //DXライブラリの終了処理
      return 0;
}
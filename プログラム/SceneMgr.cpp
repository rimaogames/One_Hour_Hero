#include "SceneMgr.h"

//最初はメニュー画面にする
eScene SceneMgr::NextScene = eScene::Scene_None;
eScene SceneMgr::Scene = eScene::Scene_Menu;

//////////コンストラクタ/////////
SceneMgr::SceneMgr() {

    //インスタンス
    menu = new Menu;
    result = new Result;


}

/////////初期化/////////
void SceneMgr::initialize(eScene scene) {
    //Controlクラスの参照
    Control& control = Control::Instance();

    switch (scene) {          //シーンによって処理を分岐

    case eScene::Scene_Menu:       //指定画面がメニュー画面なら
        menu->initialize();                 //メニュー画面の初期化処理をする
        break;
    case eScene::Scene_Game:       //指定画面がゲーム画面なら
        control.initialize();           //ゲーム画面の初期化処理をする             
        break;
    case eScene::Scene_Howto:     //指定画面が遊び方画面なら
        howto = new Howto;          //遊び方画面の初期化処理をする(インスタンス生成)
        break;
    case eScene::Scene_Result:  //指定画面が結果画面なら
        result->initialize();             //結果画面の初期化処理をする
        break;
    default:
        break;
    }
}


/////////終了の処理/////////
void SceneMgr::finalize(eScene scene) {

    //Controlクラスの参照
    Control& control = Control::Instance();


    //////////////シーンによって処理を分岐/////////////////

    switch (scene) {        
    case eScene::Scene_Menu:     //指定画面がメニュー画面なら
        menu->finalize();                //メニュー画面の終了の処理をする
        break;
    case eScene::Scene_Game:    //指定画面がゲーム画面なら
        control.finalize();         //ゲーム画面の終了の処理
        break;
    case eScene::Scene_Howto:  //指定画面が遊び方画面なら
        delete howto;             //遊び方画面の終了の処理
        break;
    case eScene::Scene_Result:  //指定画面が結果画面なら
        result->finalize();             //結果画面の終了の処理
        break;
    default:
        break;

    }
}


///////次のシーンを引数のシーンに設定(他クラスから呼び出される)///////
void SceneMgr::ChangeScene(eScene scene) {

    //次のシーンに引数のシーン入れる
    NextScene = scene;

}


/////////////画面の更新////////////
void SceneMgr::Update() {

    //画面移動するならば
    if (NextScene != eScene::Scene_None) {
        //今の画面は終了する
        finalize(Scene);
        //画面は入れ替え
        Scene = NextScene;
        //予定のシーンは初期化
        NextScene = eScene::Scene_None;
        //今のシーン（予定されていたシーン）を初期化させる
        initialize(Scene);
    }

    //Controlクラスの参照
    Control& control = Control::Instance();

    ////////////////画面が更新する命令が下るか見る/////////////////

    switch (Scene) {       //シーンによって処理を分岐
    case eScene::Scene_Menu:    //現在の画面がメニューなら
        menu->Update();            //メニュー画面の更新関数
        break;//以下略
    case eScene::Scene_Game:    //現在の画面がゲームなら
        control.Update();          //ゲーム画面の更新関数
        break;
    case eScene::Scene_Howto:  //現在の画面が遊び方説明なら
        howto->Update();           //遊び方の更新関数
        break;
    case eScene::Scene_Result:     //現在の画面が結果画面なら
        result->Update();            //結果の更新関数
        break;
    default:
        break;

    }

}


////////All関数の実行/////////
void SceneMgr::All() {
    //Controlクラスの参照
    Control& control = Control::Instance();


    switch (Scene) {      //シーンによって処理を分岐
    case eScene::Scene_Menu:   //現在の画面がメニュー画面なら
        menu->All();              //メニュー画面の処理をする
        break;//以下略
    case eScene::Scene_Game: //現在の画面がゲーム画面なら
        control.All();            //ゲームの処理をする
        break;
    case eScene::Scene_Howto:    //現在の画面が遊び方画面なら
        howto->All();              //遊び方画面の処理をする
        break;
    case eScene::Scene_Result: //現在の画面が結果画面なら
        result->All();             //結果の処理をする
        break;
    }
}

///////Mainで呼び出される関数//////////
void SceneMgr::loop() {

    //更新
    Update();
    //実行
    All();
}

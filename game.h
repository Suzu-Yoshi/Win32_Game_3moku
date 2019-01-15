///▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
//game.h
///▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

///########## ヘッダファイル読み込み ##########
#include <windows.h>
#include "main.h"

///########## マクロ定義 ##########

//マスの数
#define GAME_MASU_MAX	3	//GAME_MASU_MAX × GAME_MASU_MAXのマスを作成

//マス目の状態
#define GAME_MASU_NONE	0	//空白のとき
#define GAME_MASU_MARU	1	//○のとき
#define GAME_MASU_BATU	2	//×のとき

//表示する文字
#define GAME_MOJI_MARU	"○"	//○の文字
#define GAME_MOJI_BATU	"×"	//×の文字

#define GAME_MOJI_NUM_MARU	1	//○の種類
#define GAME_MOJI_NUM_BATU	2	//×の種類


//○や×の大きさ
#define GAME_OX_SIZE  100	//GAME_OX_SIZE × GAME_OX_SIZEの大きさで作成 



///########## 構造体 ##########

///########## 名前の再定義 ##########

///▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
#pragma once	//二重インクルードの防止
///▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼

///########## グローバル変数 参照の宣言 ##########

///▼▼▼▼▼ 本体はgame.cpp ▼▼▼▼▼

///▲▲▲▲▲ 本体はgame.cpp ▲▲▲▲▲

///########## 外部 関数 参照の宣言 ##########

///▼▼▼▼▼ 本体はgame.cpp ▼▼▼▼▼

//画面を描画する関数
extern VOID MY_DRAW_GAME(MY_WIN);

//画面の背景を描画する関数
extern VOID MY_DRAW_BACKSCREEN(HDC, RECT);

//画面の縦線を描画する関数
extern VOID MY_DRAW_LINE_TATE(HDC , RECT );

//画面の横線を描画する関数
extern VOID MY_DRAW_LINE_YOKO(HDC , RECT );

//マスを初期化する関数
extern VOID MY_INIT_MASU(VOID);

//○や×を表示する関数
extern VOID MY_DRAW_OX(HDC);

///▲▲▲▲▲ 本体はgame.cpp ▲▲▲▲▲
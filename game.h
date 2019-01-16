///▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
//game.h
///▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

///########## ヘッダファイル読み込み ##########
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <locale.h>
#include "main.h"

///########## マクロ定義 ##########

//マスの数
#define GAME_MASU_MAX	3	//GAME_MASU_MAX × GAME_MASU_MAXのマスを作成

//マス目の状態
#define GAME_MASU_NONE	0	//初期状態
#define GAME_MASU_MARU	1	//○のとき：先攻
#define GAME_MASU_BATU	2	//×のとき：後攻

//表示する文字
#define GAME_MOJI_MARU	"○"	//○の文字
#define GAME_MOJI_BATU	"×"	//×の文字

//○や×の大きさ
#define GAME_OX_SIZE  100	//GAME_OX_SIZE × GAME_OX_SIZEの大きさで作成 

//○の勝利タイトル
#define GAME_WIN_O_TITLE	"WINNER[○]"
//○の勝利文
#define GAME_WIN_O_TEXT		"○の勝ち"

//×の勝利タイトル
#define GAME_WIN_X_TITLE	"WINNER[×]"
//×の勝利文
#define GAME_WIN_X_TEXT		"×の勝ち"

//引き分けのタイトル
#define GAME_DRAW_TITLE		"DRAW"
//引き分けの勝利文
#define GAME_DRAW_TEXT		"引き分け"

//もう一度遊ぶかのタイトル
#define GAME_WIN_REPLAY_TITLE	"REPLAY?"
//もう一度遊ぶかの文
#define GAME_WIN_REPLAY_TEXT	"もう一度遊びますか？"

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

//ゲーム内の計算をする関数
extern VOID MY_CALC_GAME(VOID);

//マスをクリックしたときの処理を行う関数
extern VOID MY_CLICK_MASU(VOID);

//マスをクリックしたときの配列の変更を行う関数
extern BOOL MY_CHANGE_MASU(POINT,int);

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

//マウスの位置を表示する関数
extern VOID MY_DRAW_MOUSE_POINT(HDC);

//プレイヤーの番を初期化する関数
extern VOID MY_INIT_PLAYER_TURN(VOID);

//勝敗チェックをする関数
extern VOID MY_CHECK_WIN_LOSE(HWND);

///▲▲▲▲▲ 本体はgame.cpp ▲▲▲▲▲
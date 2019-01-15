///▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
//winproc.cpp
///▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

///########## ヘッダファイル読み込み ##########
#include "main.h"
#include "game.h"
#include "font.h"

///########## ライブラリ読み込み ##########

///########## マクロ定義 ##########

///########## 列挙型 ##########

///########## 構造体 ##########

///########## 名前の再定義 ##########

///########## グローバル変数の宣言と初期化 ##########

//マス目を管理する配列
int masu[GAME_MASU_MAX][GAME_MASU_MAX];

///########## プロトタイプ宣言 ##########

//画面を描画する関数
VOID MY_DRAW_GAME(MY_WIN);

//画面の背景を描画する関数
VOID MY_DRAW_BACKSCREEN(HDC, RECT);

//画面の縦線を描画する関数
VOID MY_DRAW_LINE_TATE(HDC hdc_double, RECT rect);

//画面の横線を描画する関数
VOID MY_DRAW_LINE_YOKO(HDC hdc_double, RECT rect);

//マスを初期化する関数
VOID MY_INIT_MASU(VOID);

//○や×を表示する関数
VOID MY_DRAW_OX(HDC);

///########## 画面を描画する関数 ##########
//引　数：ﾀﾞﾌﾞﾙﾊﾞｯﾌｧﾘﾝｸﾞ用のﾃﾞﾊﾞｲｽｺﾝﾃｷｽﾄのﾊﾝﾄﾞﾙ
//戻り値：なし
VOID MY_DRAW_GAME(MY_WIN mywin)
{
	//背景を描画する
	MY_DRAW_BACKSCREEN(mywin.hdc_double, mywin.win_rect_cli);

	//画面の縦線を描画する
	MY_DRAW_LINE_TATE(mywin.hdc_double, mywin.win_rect_cli);

	//画面の横線を描画する
	MY_DRAW_LINE_YOKO(mywin.hdc_double, mywin.win_rect_cli);

	//○や×を表示する
	MY_DRAW_OX(mywin.hdc_double);

}

///########## 画面の背景を描画する関数 ##########
//引　数：ﾀﾞﾌﾞﾙﾊﾞｯﾌｧﾘﾝｸﾞ用のﾃﾞﾊﾞｲｽｺﾝﾃｷｽﾄのﾊﾝﾄﾞﾙ
//引　数：クライアント領域
//戻り値：なし
VOID MY_DRAW_BACKSCREEN(HDC hdc_double, RECT rect)
{
	//ブラシを作成
	HBRUSH hbrush = CreateSolidBrush(RGB(255, 255, 240));

	//ブラシを設定＆以前のブラシを取得
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc_double, hbrush);

	//四角を描画
	Rectangle(
		hdc_double,		//デバイスコンテキストのハンドル
		rect.left,		//四角の左上のX座標
		rect.top,		//四角の左上のY座標
		rect.right,		//四角の右下のX座標
		rect.bottom);	//四角の右下のY座標

	//以前のブラシに戻す
	SelectObject(hdc_double, hOldBrush);

	//ブラシを削除
	DeleteObject(hbrush);

}

///########## 画面の縦線を描画する関数 ##########
//引　数：ﾀﾞﾌﾞﾙﾊﾞｯﾌｧﾘﾝｸﾞ用のﾃﾞﾊﾞｲｽｺﾝﾃｷｽﾄのﾊﾝﾄﾞﾙ
//引　数：クライアント領域
//戻り値：なし
VOID MY_DRAW_LINE_TATE(HDC hdc_double, RECT rect)
{
	//ループで使用
	int loop = 0;

	//線を描く最大数 
	int Draw_Line_MAX = GAME_MASU_MAX + 1;	//	+1は一番下の線

	//線の描き始め位置
	POINT pt_Start;
	pt_Start.x = rect.left;
	pt_Start.y = rect.top;

	//線の描き終わり位置
	POINT pt_End;
	pt_End.x = rect.left;
	pt_End.y = rect.bottom;

	//ペンを作成
	HPEN hpen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));

	//ペンを設定＆以前のペンを取得
	HPEN hOldPen = (HPEN)SelectObject(hdc_double, hpen);

	for (loop = 0; loop < Draw_Line_MAX; loop++)
	{

		//線の描き始め位置
		MoveToEx(
			hdc_double,							//デバイスコンテキストのハンドル
			pt_Start.x + loop * GAME_OX_SIZE,	//描き始めるX座標
			pt_Start.y,							//描き始めるY座標
			NULL);								//以前のカレントポジション/必要ないならNULL

		//線を描く(斜め棒)
		LineTo(
			hdc_double,						//デバイスコンテキストのハンドル
			pt_End.x + loop * GAME_OX_SIZE,	//描き終わるX座標
			pt_End.y);						//描き終わるY座標
	}

	//以前のペンに戻す
	SelectObject(hdc_double, hOldPen);

	//ペンを削除
	DeleteObject(hpen);
}

///########## 画面の横線を描画する関数 ##########
//引　数：ﾀﾞﾌﾞﾙﾊﾞｯﾌｧﾘﾝｸﾞ用のﾃﾞﾊﾞｲｽｺﾝﾃｷｽﾄのﾊﾝﾄﾞﾙ
//引　数：クライアント領域
//戻り値：なし
VOID MY_DRAW_LINE_YOKO(HDC hdc_double, RECT rect)
{
	//ループで使用
	int loop = 0;

	//線を描く最大数
	int Draw_Line_MAX = GAME_MASU_MAX + 1;	//	+1は一番右の線

	//線の描き始め位置
	POINT pt_Start;
	pt_Start.x = rect.left;
	pt_Start.y = rect.top;

	//線の描き終わり位置
	POINT pt_End;
	pt_End.x = rect.right;
	pt_End.y = rect.top;

	//ペンを作成
	HPEN hpen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));

	//ペンを設定＆以前のペンを取得
	HPEN hOldPen = (HPEN)SelectObject(hdc_double, hpen);

	for (loop = 0; loop < Draw_Line_MAX; loop++)
	{

		//線の描き始め位置
		MoveToEx(
			hdc_double,							//デバイスコンテキストのハンドル
			pt_Start.x,							//描き始めるX座標
			pt_Start.y + loop * GAME_OX_SIZE,	//描き始めるY座標
			NULL);								//以前のカレントポジション/必要ないならNULL

		//線を描く(斜め棒)
		LineTo(
			hdc_double,							//デバイスコンテキストのハンドル
			pt_End.x,							//描き終わるX座標
			pt_End.y + loop * GAME_OX_SIZE);	//描き終わるY座標
	}

	//以前のペンに戻す
	SelectObject(hdc_double, hOldPen);

	//ペンを削除
	DeleteObject(hpen);
}

///########## マスを初期化する関数 ##########
//引　数：なし
//戻り値：なし
VOID MY_INIT_MASU(VOID)
{
	int tate;
	int yoko;

	for (tate = 0; tate < GAME_MASU_MAX; tate++)
	{
		for (yoko = 0; yoko < GAME_MASU_MAX; yoko++)
		{
			//配列を初期化
			masu[tate][yoko] = GAME_MASU_NONE;
		}
	}
}

///########## ○や×を表示する関数 ##########
//引　数：なし
//戻り値：なし
VOID MY_DRAW_OX(HDC double_hdc)
{
	int tate;
	int yoko;

	//文字を描画する領域
	RECT rect;

	for (tate = 0; tate < GAME_MASU_MAX; tate++)
	{
		for (yoko = 0; yoko < GAME_MASU_MAX; yoko++)
		{
			//文字を描画する領域を計算する
			rect.left = yoko * GAME_OX_SIZE;			//左上のX座標
			rect.top = tate * GAME_OX_SIZE;				//左上のY座標
			rect.right = (yoko + 1) * GAME_OX_SIZE;		//右下のX座標
			rect.bottom = (tate + 1) * GAME_OX_SIZE;	//右下のY座標

			//配列を元に描画
			switch (masu[tate][yoko])
			{
			case GAME_MASU_MARU:
				//配列に○のデータが入っているとき

				//文字を描画
				MY_DRAW_CHECK_TEXT(GAME_MOJI_NUM_MARU, double_hdc, rect);

				break;
			case GAME_MASU_BATU:
				//配列に×のデータが入っているとき

				//文字を描画
				MY_DRAW_CHECK_TEXT(GAME_MOJI_NUM_BATU, double_hdc, rect);

				break;
			case GAME_MASU_NONE:
				//配列にデータが入っていないとき

				break;
			}
		}
	}
}
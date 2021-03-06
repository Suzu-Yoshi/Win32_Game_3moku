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

//プレイヤーの番を管理する変数
int player_turn;

//先行と後攻を管理
int player_my = GAME_MASU_NONE;	//自分
int player_cp = GAME_MASU_NONE;	//コンピュータ

//空いているマスを管理
int masu_Blank[GAME_MASU_MAX * GAME_MASU_MAX];

///########## プロトタイプ宣言 ##########

//マスをクリックしたときの処理を行う関数
VOID MY_CLICK_MASU(VOID);

//マスをクリックしたときの配列の処理の関数
BOOL MY_CHANGE_MASU(POINT, int);

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

//マウスの位置を表示する関数
VOID MY_DRAW_MOUSE_POINT(HDC);

//プレイヤーの番を表示する関数
VOID MY_DRAW_PLAYER_OX(HDC);

//プレイヤーの番を初期化する関数
VOID MY_INIT_PLAYER_TURN(VOID);

//勝敗チェックをする関数
VOID MY_CHECK_WIN_LOSE(HWND);

//コンピュータの入力をする関数
VOID MY_INPUT_COMPUTER(VOID);

///########## マスをクリックしたときの処理を行う関数 ##########
//引　数：なし
//戻り値：なし
VOID MY_CLICK_MASU(VOID)
{

	BOOL isClickNone = FALSE;

	//自分の番のとき
	if (player_turn == player_my)
	{
		switch (player_turn)
		{
		case GAME_MASU_MARU:
			//○のプレイヤーのとき

			//マスをクリックしたときの配列の処理
			isClickNone = MY_CHANGE_MASU(MyWin.point_Mouse, GAME_MASU_MARU);

			//○か×が置けたとき
			if (isClickNone == TRUE)
			{
				//プレイヤーの番を変更する
				player_turn = GAME_MASU_BATU;
			}

			break;
		case GAME_MASU_BATU:
			//×のプレイヤーのとき

			//マスをクリックしたときの配列の処理
			isClickNone = MY_CHANGE_MASU(MyWin.point_Mouse, GAME_MASU_BATU);

			//○か×が置けたとき
			if (isClickNone == TRUE)
			{
				//プレイヤーの番を変更する
				player_turn = GAME_MASU_MARU;
			}

			break;
		}
	}

}

///########## マスをクリックしたときの配列の処理の関数 ##########
//引　数：マウス座標X
//引　数：マウス座標Y
//引　数：プレイヤーの種類
//戻り値：○か×を置けたらTRUE
//戻り値：○か×が既に置かれていたらFALSE
BOOL MY_CHANGE_MASU(POINT mouse_pt, int player)
{
	//縦の場所を計算
	int tate = mouse_pt.y / GAME_OX_SIZE;
	//横の場所を計算
	int yoko = mouse_pt.x / GAME_OX_SIZE;

	if (masu[tate][yoko] == GAME_MASU_NONE)
	{
		//○か×がまだ置いていないとき

		switch (player)
		{
		case GAME_MASU_MARU:
			//○のプレイヤーのとき
			masu[tate][yoko] = GAME_MASU_MARU;

			break;
		case GAME_MASU_BATU:
			//×のプレイヤーのとき
			masu[tate][yoko] = GAME_MASU_BATU;

			break;
		}

		//○か×が置けた
		return TRUE;
	}
	else
	{
		//○か×が既に置かれているとき

		//○か×が置けなかった
		return FALSE;
	}
}

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
				MY_DRAW_CHECK_TEXT(GAME_MASU_MARU, double_hdc, rect);

				break;
			case GAME_MASU_BATU:
				//配列に×のデータが入っているとき

				//文字を描画
				MY_DRAW_CHECK_TEXT(GAME_MASU_BATU, double_hdc, rect);

				break;
			case GAME_MASU_NONE:
				//配列にデータが入っていないとき

				break;
			}
		}
	}
}

///########## マウスの位置を表示する関数 ##########
//引　数：デバイスコンテキストのハンドル
//引　数：なし
VOID MY_DRAW_MOUSE_POINT(HDC hdc)
{
	//FPS値を整形するための変数
	CHAR strfpsChr[64];
	size_t wLen = 0;
	errno_t err = 0;

	//FPS値を整形
	sprintf(strfpsChr, "マウス座標[X:%03d][Y:%03d]", MyWin.point_Mouse.x, MyWin.point_Mouse.y);

	//FPS値を表示するための変数
	TCHAR StrfpsTch[64];

	//ロケール指定
	setlocale(LC_ALL, "japanese");

	//文字列をマルチバイト文字からワイド文字に変換
	err = mbstowcs_s(
		&wLen,				//変換された文字数
		StrfpsTch,			//変換されたワイド文字
		strlen(strfpsChr),	//変換する文字数
		strfpsChr,			//変換するマルチバイト文字
		_TRUNCATE			//バッファに収まるだけの文字列まで変換
	);

	SetBkMode(hdc, TRANSPARENT);			//背景色は上書きしない
	SetTextColor(hdc, RGB(0, 0, 0));		//文字色
	SetBkColor(hdc, RGB(255, 255, 255));	//背景色

	//FPSを描画
	TextOut(hdc, 5, 20, StrfpsTch, lstrlen(StrfpsTch));
}

///########## プレイヤーの番を表示する関数 ##########
//引　数：デバイスコンテキストのハンドル
//引　数：なし
VOID MY_DRAW_PLAYER_OX(HDC hdc)
{
	TCHAR strPlayer[64];

	if (player_my == GAME_MASU_MARU)
	{
		wsprintf(strPlayer, TEXT("先行：プレイヤー：○"));
	}
	if (player_my == GAME_MASU_BATU)
	{
		wsprintf(strPlayer, TEXT("後攻：プレイヤー：×"));
	}

	SetBkMode(hdc, TRANSPARENT);			//背景色は上書きしない
	SetTextColor(hdc, RGB(0, 0, 0));		//文字色
	SetBkColor(hdc, RGB(255, 255, 255));	//背景色

	//プレイヤーの番を描画
	TextOut(hdc, 5, 35, strPlayer, lstrlen(strPlayer));
}

///########## プレイヤーの番を初期化する関数 ##########
//引　数：なし
//戻り値：なし
VOID MY_INIT_PLAYER_TURN(VOID)
{
	//初期化
	player_turn = GAME_MASU_NONE;

	//ランダムでプレイヤーを決める
	int random;

	//時刻をもとに乱数表を作成
	srand((unsigned)time(NULL));

	//ランダムで1か2を選ぶ
	random = (rand() % 2) + 1;

	//役割を入れる
	switch (random)
	{
	case GAME_MASU_MARU:
		//player_turn = GAME_MASU_MARU;

		//メッセージボックスを表示
		MessageBox(NULL, TEXT(GAME_SENKOU_TEXT), TEXT(GAME_SENKOU_TITLE), MB_OK);

		player_turn = player_my = GAME_MASU_MARU;	//先行
		player_cp = GAME_MASU_BATU;	//後攻

		break;
	case GAME_MASU_BATU:
		//player_turn = GAME_MASU_BATU;

		//メッセージボックスを表示
		MessageBox(NULL, TEXT(GAME_KOUKOU_TEXT), TEXT(GAME_KOUKOU_TITLE), MB_OK);

		player_my = GAME_MASU_BATU;	//後攻
		player_turn = player_cp = GAME_MASU_MARU;	//先行

		break;
	}

}

///########## 勝敗チェックをする関数 ##########
//引　数：なし
//戻り値：なし
VOID MY_CHECK_WIN_LOSE(HWND hwnd)
{
	//配列の添字に使用
	int tate;
	int yoko;
	int naname;

	//○と×の数をカウント
	int maru_cnt;
	int batu_cnt;
	int draw_cnt;

	//TRUEなら、勝利
	BOOL maru_win = FALSE;
	BOOL batu_win = FALSE;

	//引き分け
	BOOL maru_batu_draw = FALSE;

	//もう一度遊ぶかのメッセージボックスの戻り値
	int retPlayMsgBox;

	//+++++ 縦が揃っているかチェック ++++++++++++++++++++
	if (maru_win == FALSE && batu_win == FALSE)
	{
		//○と×の数を初期化
		maru_cnt = 0;
		batu_cnt = 0;

		for (yoko = 0; yoko < GAME_MASU_MAX; yoko++)
		{
			//○と×の数を初期化
			maru_cnt = 0;
			batu_cnt = 0;

			for (tate = 0; tate < GAME_MASU_MAX; tate++)
			{
				//○の数をカウント
				if (masu[tate][yoko] == GAME_MASU_MARU)
				{
					maru_cnt++;
				}

				//×の数をカウント
				if (masu[tate][yoko] == GAME_MASU_BATU)
				{
					batu_cnt++;
				}
			}

			//○が並んだとき→○の勝利
			if (maru_cnt == GAME_MASU_MAX)
			{
				maru_win = TRUE;	break;
			}

			//×が並んだとき→×の勝利
			if (batu_cnt == GAME_MASU_MAX)
			{
				batu_win = TRUE;	break;
			}
		}
	}

	//+++++ 横が揃っているかチェック ++++++++++++++++++++
	if (maru_win == FALSE && batu_win == FALSE)
	{
		//○と×の数を初期化
		maru_cnt = 0;
		batu_cnt = 0;

		for (tate = 0; tate < GAME_MASU_MAX; tate++)
		{
			//○と×の数を初期化
			maru_cnt = 0;
			batu_cnt = 0;

			for (yoko = 0; yoko < GAME_MASU_MAX; yoko++)
			{
				//○の数をカウント
				if (masu[tate][yoko] == GAME_MASU_MARU)
				{
					maru_cnt++;
				}

				//×の数をカウント
				if (masu[tate][yoko] == GAME_MASU_BATU)
				{
					batu_cnt++;
				}
			}

			//○が並んだとき→○の勝利
			if (maru_cnt == GAME_MASU_MAX)
			{
				maru_win = TRUE;	break;
			}

			//×が並んだとき→×の勝利
			if (batu_cnt == GAME_MASU_MAX)
			{
				batu_win = TRUE;	break;
			}
		}
	}

	//+++++ 斜め(右下がり)が揃っているかチェック ++++++++++++++++++++
	if (maru_win == FALSE && batu_win == FALSE)
	{
		//○と×の数を初期化
		maru_cnt = 0;
		batu_cnt = 0;

		for (naname = 0; naname < GAME_MASU_MAX; naname++)
		{
			//○の数をカウント
			if (masu[naname][naname] == GAME_MASU_MARU)
			{
				maru_cnt++;
			}

			//×の数をカウント
			if (masu[naname][naname] == GAME_MASU_BATU)
			{
				batu_cnt++;
			}

			//○が並んだとき→○の勝利
			if (maru_cnt == GAME_MASU_MAX)
			{
				maru_win = TRUE;	break;
			}

			//×が並んだとき→×の勝利
			if (batu_cnt == GAME_MASU_MAX)
			{
				batu_win = TRUE;	break;
			}
		}
	}

	//+++++ 斜め(右上がり)が揃っているかチェック ++++++++++++++++++++
	if (maru_win == FALSE && batu_win == FALSE)
	{
		//○と×の数を初期化
		maru_cnt = 0;
		batu_cnt = 0;

		for (naname = 0; naname < GAME_MASU_MAX; naname++)
		{
			//○の数をカウント
			if (masu[naname][(GAME_MASU_MAX - 1) - naname] == GAME_MASU_MARU)
			{
				maru_cnt++;
			}

			//×の数をカウント
			if (masu[naname][(GAME_MASU_MAX - 1) - naname] == GAME_MASU_BATU)
			{
				batu_cnt++;
			}

			//○が並んだとき→○の勝利
			if (maru_cnt == GAME_MASU_MAX)
			{
				maru_win = TRUE;	break;
			}

			//×が並んだとき→×の勝利
			if (batu_cnt == GAME_MASU_MAX)
			{
				batu_win = TRUE;	break;
			}
		}
	}

	//+++++ 引き分けかチェック ++++++++++++++++++++
	if (maru_win == FALSE && batu_win == FALSE)
	{
		//○と×の数を初期化
		maru_cnt = 0;
		batu_cnt = 0;

		for (tate = 0; tate < GAME_MASU_MAX; tate++)
		{
			for (yoko = 0; yoko < GAME_MASU_MAX; yoko++)
			{
				//○の数をカウント
				if (masu[tate][yoko] == GAME_MASU_MARU)
				{
					maru_cnt++;
				}

				//×の数をカウント
				if (masu[tate][yoko] == GAME_MASU_BATU)
				{
					batu_cnt++;
				}
			}
		}
	}

	//○と×の合計数を計算
	draw_cnt = maru_cnt + batu_cnt;

	//○と×の合計数がマスの合計数と同じ時、引き分け
	if (draw_cnt == (GAME_MASU_MAX * GAME_MASU_MAX))
	{
		maru_batu_draw = TRUE;
	}

	//まだ勝者がいないときは関数を抜ける
	if (maru_win == FALSE && batu_win == FALSE && maru_batu_draw == FALSE)
	{
		return;
	}

	//○の勝利
	if (maru_win == TRUE)
	{
		//メッセージボックスを表示
		MessageBox(NULL, TEXT(GAME_WIN_O_TEXT), TEXT(GAME_WIN_O_TITLE), MB_OK);
	}

	//×の勝利
	if (batu_win == TRUE)
	{
		//メッセージボックスを表示
		MessageBox(NULL, TEXT(GAME_WIN_X_TEXT), TEXT(GAME_WIN_X_TITLE), MB_OK);
	}

	//引き分け
	if (maru_batu_draw == TRUE)
	{
		//メッセージボックスを表示
		MessageBox(NULL, TEXT(GAME_DRAW_TEXT), TEXT(GAME_DRAW_TITLE), MB_OK);
	}

	//もう一度遊ぶか質問する

	//メッセージボックスを表示
	retPlayMsgBox = MessageBox(NULL, TEXT(GAME_WIN_REPLAY_TEXT), TEXT(GAME_WIN_REPLAY_TITLE), MB_YESNO | MB_ICONQUESTION);

	//「はい」ボタンを押したとき
	if (retPlayMsgBox == IDYES)
	{
		//初期化の処理を行う

		//マスの初期化
		MY_INIT_MASU();

		//プレイヤーの初期化
		MY_INIT_PLAYER_TURN();

	}

	//「いいえ」ボタンを押したとき
	if (retPlayMsgBox == IDNO)
	{
		//終了処理を行う

		//ウィンドウを破棄する
		DestroyWindow(hwnd);
	}

}

///########## コンピュータの入力をする関数 ##########
//引　数：なし
//戻り値：なし
VOID MY_INPUT_COMPUTER(VOID)
{
	//ランダムで場所を決める
	int random;

	//ランダムの範囲
	int randam_MAX = 0;

	//○か×を置いたとき
	BOOL isPutOX = FALSE;
	
	//空いている場所をチェックで使用
	int tate_for;
	int yoko_for;

	int tate_random;
	int yoko_random;

	//まだ何もおいていないマスの場所を入れる
	int none_masu[GAME_MASU_MAX * GAME_MASU_MAX];

	//空いている場所をチェック
	for (tate_for = 0; tate_for < GAME_MASU_MAX; tate_for++)
	{
		for (yoko_for = 0; yoko_for < GAME_MASU_MAX; yoko_for++)
		{
			//マスになにか入っていないときをカウント
			if (masu[tate_for][yoko_for] == GAME_MASU_NONE)
			{
				//何も入っていないマスの場所を入れる
				none_masu[randam_MAX] = tate_for * GAME_MASU_MAX + yoko_for;

				//何も入っていないマスをカウント→ランダムの上限値
				randam_MAX++;
			}
		}
	}

	//何も入っていないマスが0個のとき→引き分けのとき
	if (randam_MAX == 0)
	{
		//○か×を置かない
		return;
	}

	//コンピュータのターンであるとき
	if (player_cp == player_turn)
	{
		//○か×を置くまで無限ループ
		while (isPutOX == FALSE)
		{
			//時刻をもとに乱数表を作成
			srand((unsigned)time(NULL));

			//ランダムで場所を選ぶ
			random = rand() % randam_MAX;

			//縦の位置を復元
			tate_random = none_masu[random] / GAME_MASU_MAX;
			
			//横の位置を復元
			yoko_random = none_masu[random] % GAME_MASU_MAX;

			//コンピュータが先行のとき
			if (player_cp == GAME_MASU_MARU)
			{
				//まだ○か×が置かれていないとき
				if (masu[tate_random][yoko_random] == GAME_MASU_NONE)
				{
					//○を置く
					masu[tate_random][yoko_random] = GAME_MASU_MARU;

					//人間の番にする
					player_turn = player_my;

					//○か×を置いた
					isPutOX = TRUE;
				}
			}

			//コンピュータが後攻のとき
			if (player_cp == GAME_MASU_BATU)
			{
				//まだ○か×が置かれていないとき
				if (masu[tate_random][yoko_random] == GAME_MASU_NONE)
				{
					//×を置く
					masu[tate_random][yoko_random] = GAME_MASU_BATU;

					//人間の番にする
					player_turn = player_my;

					//○か×を置いた
					isPutOX = TRUE;
				}
			}
		}

	}

}
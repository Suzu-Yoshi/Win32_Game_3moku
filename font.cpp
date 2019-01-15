///▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
//font.cpp
///▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

///########## ヘッダファイル読み込み ##########

#include "font.h"
#include "fps.h"
#include "game.h"	

///########## グローバル変数の宣言と初期化 ##########

//テキスト構造体の変数
MY_FONT MyFont_MARU;			//○の文字
MY_FONT MyFont_BATU;			//×の文字

///########## プロトタイプ宣言 ##########

VOID MY_FONT_INIT(VOID);							//テキストを初期化する
BOOL MY_FONT_READ(HWND);							//フォントを一時的に読み込む
HFONT MY_FONT_CREATE(HDC, MY_FONT *);				//フォントを作成する
VOID MY_FONT_REMOVE(HWND);							//一時的に読み込んだフォントを削除する
VOID MY_DRAW_DRAW_TEXT(HDC, MY_FONT *);				//文字を描画する関数
VOID MY_TEXT_ALIGN(MY_FONT *, POINT *, SIZE);		//文字の揃え方を設定する関数
VOID MY_DRAW_CHECK_TEXT(int, HDC, RECT);			//文字を判断する関数

///########## テキストを初期化する関数 ##########
//引　数：なし
//戻り値：なし
VOID MY_FONT_INIT(VOID)
{
	//○の文字の初期化

	wsprintf(MyFont_MARU.string, TEXT(GAME_MOJI_MARU));	//表示する文字
	wsprintf(MyFont_MARU.fontname, FNT_MS_GOTHIC);		//表示する文字のフォント
	MyFont_MARU.charset = ANSI_CHARSET;					//文字コード

	MyFont_MARU.rect.left = 0;							//四角の左上のX座標
	MyFont_MARU.rect.top = 0;							//四角の左上のY座標
	MyFont_MARU.rect.right = 0;							//四角の右下のX座標
	MyFont_MARU.rect.bottom = 0 / 2;					//四角の右下のY座標

	MyFont_MARU.size = GAME_OX_SIZE;					//文字の大きさ
	MyFont_MARU.bold = MOJI_REGU;						//太字
	MyFont_MARU.ita = FALSE;							//斜体
	MyFont_MARU.ul = FALSE;								//下線
	MyFont_MARU.st = FALSE;								//打ち消し
	MyFont_MARU.align = TEXT_ALIGN_C_CENTER;			//左右上下中央揃え

	MyFont_MARU.bkcolor = RGB(255, 255, 255);			//背景色
	MyFont_MARU.color = RGB(255, 0, 0);					//文字色
	MyFont_MARU.bkmode = MOJI_BKMD_TRAN;				//背景モード

	//×の文字の初期化

	wsprintf(MyFont_BATU.string, TEXT(GAME_MOJI_BATU));	//表示する文字
	wsprintf(MyFont_BATU.fontname, FNT_MS_GOTHIC);		//表示する文字のフォント
	MyFont_BATU.charset = ANSI_CHARSET;					//文字コード

	MyFont_BATU.rect.left = 0;							//四角の左上のX座標
	MyFont_BATU.rect.top = 0;							//四角の左上のY座標
	MyFont_BATU.rect.right = 0;							//四角の右下のX座標
	MyFont_BATU.rect.bottom = 0 / 2;					//四角の右下のY座標

	MyFont_BATU.size = GAME_OX_SIZE;					//文字の大きさ
	MyFont_BATU.bold = MOJI_REGU;						//太字
	MyFont_BATU.ita = FALSE;							//斜体
	MyFont_BATU.ul = FALSE;								//下線
	MyFont_BATU.st = FALSE;								//打ち消し
	MyFont_BATU.align = TEXT_ALIGN_C_CENTER;			//左右上下中央揃え

	MyFont_BATU.bkcolor = RGB(255, 255, 255);			//背景色
	MyFont_BATU.color = RGB(0, 0, 255);					//文字色
	MyFont_BATU.bkmode = MOJI_BKMD_TRAN;				//背景モード

}

///########## 文字を判断する関数 ##########
//引　数：○か×の種類
//引　数：ﾀﾞﾌﾞﾙﾊﾞｯﾌｧﾘﾝｸﾞ用のﾃﾞﾊﾞｲｽｺﾝﾃｷｽﾄのﾊﾝﾄﾞﾙ
//引　数：文字の描画領域
//戻り値：なし
VOID MY_DRAW_CHECK_TEXT(int MaruBatu, HDC double_hdc, RECT rect)
{
	switch (MaruBatu)
	{
	case GAME_MOJI_NUM_MARU:

		//表示場所の設定
		MyFont_MARU.rect = rect;

		//文字の描画
		MY_DRAW_DRAW_TEXT(double_hdc, &MyFont_MARU);

		break;

	case GAME_MOJI_NUM_BATU:

		//表示場所の設定
		MyFont_BATU.rect = rect;

		//文字の描画
		MY_DRAW_DRAW_TEXT(double_hdc, &MyFont_BATU);
		
		break;
	}
}

///########## 文字を描画する関数 ##########
//引　数：ﾀﾞﾌﾞﾙﾊﾞｯﾌｧﾘﾝｸﾞ用のﾃﾞﾊﾞｲｽｺﾝﾃｷｽﾄのﾊﾝﾄﾞﾙ
//引　数：フォント構造体
//戻り値：なし
VOID MY_DRAW_DRAW_TEXT(HDC double_hdc, MY_FONT *MyFont)
{
	//フォントの詳細情報
	TEXTMETRIC tm;

	SIZE sz;		//文字の大きさ情報
	POINT text_pt;	//文字のXY座標

	//フォントを作成する
	MyFont->hfont = MY_FONT_CREATE(double_hdc, MyFont);

	//フォントを設定する＆以前のフォントを取得する
	HFONT hOldFont = (HFONT)SelectObject(double_hdc, MyFont->hfont);

	//フォントの詳細情報を取得
	GetTextMetrics(double_hdc, &tm);

	SetTextColor(double_hdc, MyFont->bkcolor);	//背景色
	SetTextColor(double_hdc, MyFont->color);	//文字色
	SetBkMode(double_hdc, MyFont->bkmode);		//背景モード

	//文字の大きさを取得
	GetTextExtentPoint32(
		double_hdc,
		MyFont->string,
		lstrlen(MyFont->string),
		&sz);

	//文字を表示
	TextOut(
		double_hdc,
		MyFont->rect.left,
		MyFont->rect.top,
		MyFont->string,
		lstrlen(MyFont->string));

	//以前のフォントに戻す
	SelectObject(double_hdc, hOldFont);

	//不要なフォントを削除
	DeleteObject(MyFont->hfont);

	return;
}

///########## 一時的にフォントを読み込む関数 ##########
//引　数：アプリケーションのウィンドウハンドル
//戻り値：なし
BOOL MY_FONT_READ(HWND hWnd)
{
	//judge hardフォントを一時的に読み込み
	if (AddFontResourceEx(FNT_JUD_PASS, FR_PRIVATE, NULL) == 0)
	{
		//フォントが読み込めなかったとき
		MessageBox(hWnd, ERR_MSG_NO_READ_FONT, ERR_MSG_FONT_TITLE, MB_OK);

		return FALSE;
	}

	//たぬき油性マジックフォントを一時的に読み込み
	if (AddFontResourceEx(FNT_TANU_PASS, FR_PRIVATE, NULL) == 0)
	{
		//フォントが読み込めなかったとき
		MessageBox(hWnd, ERR_MSG_NO_READ_FONT, ERR_MSG_FONT_TITLE, MB_OK);

		return FALSE;
	}

	//ゴッドイーター風フォントを一時的に読み込み
	if (AddFontResourceEx(FNT_GOD_PASS, FR_PRIVATE, NULL) == 0)
	{
		//フォントが読み込めなかったとき
		MessageBox(hWnd, ERR_MSG_NO_READ_FONT, ERR_MSG_FONT_TITLE, MB_OK);

		return FALSE;
	}

	return TRUE;
}

///########## フォントを設定する関数 ##########
//引　数：ﾀﾞﾌﾞﾙﾊﾞｯﾌｧﾘﾝｸﾞ用のﾃﾞﾊﾞｲｽｺﾝﾃｷｽﾄのﾊﾝﾄﾞﾙ
//引　数：フォント構造体
//戻り値：なし
HFONT MY_FONT_CREATE(HDC hdc, MY_FONT *MyText)
{
	HFONT hFont;
	hFont = CreateFont(
		MyText->size,			//フォントの高さ / 0ならデフォルト(大きさ)
		0,						//文字幅		 / 0なら自動計算
		MyText->angle,			//テキストの角度
		0,						//ベースラインとX軸との角度
		MyText->bold,			//フォントの重さ（太さ）
		MyText->ita,			//イタリック体
		MyText->ul,				//アンダーライン
		MyText->st,				//打ち消し線
		MyText->charset,		//文字セット
		OUT_DEFAULT_PRECIS,		//出力精度
		CLIP_DEFAULT_PRECIS,	//クリッピング精度
		PROOF_QUALITY,			//出力品質
		FIXED_PITCH | FF_MODERN,//ピッチとファミリー
		MyText->fontname);		//フォントの書体名

	return hFont;
}

///########## 一時的なフォントを削除する関数 ##########
//引　数：アプリケーションのウィンドウハンドル
//戻り値：なし
VOID MY_FONT_REMOVE(HWND hWnd)
{
	//一時的に読み込んだ judge hardフォントを削除
	RemoveFontResourceEx(FNT_JUD_PASS, FR_PRIVATE, NULL);

	//一時的に読み込んだ たぬき油性マジックフォントを削除
	RemoveFontResourceEx(FNT_TANU_PASS, FR_PRIVATE, NULL);

	//一時的に読み込んだ ゴッドイーター風マジックフォントを削除
	RemoveFontResourceEx(FNT_GOD_PASS, FR_PRIVATE, NULL);

	return;
}

///########## 文字の揃え方の設定する関数 ##########
//引　数：フォント構造体
//引　数：フォントの左上の座標(ポインタ)
//引　数：文字のサイズ
//戻り値：なし
VOID MY_TEXT_ALIGN(MY_FONT *MyText, POINT *pt, SIZE sz)
{
	//表示方法
	switch (MyText->align)
	{

	case TEXT_ALIGN_U_LEFT:
		//縦：上揃え　/横：左揃え

		pt->x = MyText->rect.left;
		pt->y = MyText->rect.top;

		break;

	case TEXT_ALIGN_U_CENTER:
		//縦：上揃え　/横：中央揃え

		pt->x = MyText->rect.left + MyText->rect.right / 2 - sz.cx / 2;
		pt->y = MyText->rect.top;

		break;

	case TEXT_ALIGN_U_RIGHT:
		//縦：上揃え　/横：右揃え

		pt->x = MyText->rect.left + MyText->rect.right - sz.cx;
		pt->y = MyText->rect.top;

		break;

	case TEXT_ALIGN_C_LEFT:
		//縦：中央揃え/横：左揃え

		pt->x = MyText->rect.left;
		pt->y = MyText->rect.top + MyText->rect.bottom / 2 - sz.cy / 2;

		break;

	case TEXT_ALIGN_C_CENTER:
		//縦：中央揃え/横：中央揃え

		pt->x = MyText->rect.left + MyText->rect.right / 2 - sz.cx / 2;
		pt->y = MyText->rect.top + MyText->rect.bottom / 2 - sz.cy / 2;

		break;

	case TEXT_ALIGN_C_RIGHT:
		//縦：中央揃え/横：右揃え

		pt->x = MyText->rect.left + MyText->rect.right - sz.cx;
		pt->y = MyText->rect.top + MyText->rect.bottom / 2 - sz.cy / 2;

		break;

	case TEXT_ALIGN_D_LEFT:
		//縦：下揃え　/横：左揃え

		pt->x = MyText->rect.left;
		pt->y = MyText->rect.top + MyText->rect.bottom - sz.cy;

		break;

	case TEXT_ALIGN_D_CENTER:
		//縦：下揃え　/横：中央揃え

		pt->x = MyText->rect.left + MyText->rect.right / 2 - sz.cx / 2;
		pt->y = MyText->rect.top + MyText->rect.bottom - sz.cy;

		break;

	case TEXT_ALIGN_D_RIGHT:
		//縦：下揃え　/横：右揃え

		pt->x = MyText->rect.left + MyText->rect.right - sz.cx;
		pt->y = MyText->rect.top + MyText->rect.bottom - sz.cy;

		break;
	}

	return;
}
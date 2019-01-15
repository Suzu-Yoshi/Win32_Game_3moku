///����������������������������������������
//font.cpp
///����������������������������������������

///########## �w�b�_�t�@�C���ǂݍ��� ##########

#include "font.h"
#include "fps.h"
#include "game.h"	

///########## �O���[�o���ϐ��̐錾�Ə����� ##########

//�e�L�X�g�\���̂̕ϐ�
MY_FONT MyFont_MARU;			//���̕���
MY_FONT MyFont_BATU;			//�~�̕���

///########## �v���g�^�C�v�錾 ##########

VOID MY_FONT_INIT(VOID);							//�e�L�X�g������������
BOOL MY_FONT_READ(HWND);							//�t�H���g���ꎞ�I�ɓǂݍ���
HFONT MY_FONT_CREATE(HDC, MY_FONT *);				//�t�H���g���쐬����
VOID MY_FONT_REMOVE(HWND);							//�ꎞ�I�ɓǂݍ��񂾃t�H���g���폜����
VOID MY_DRAW_DRAW_TEXT(HDC, MY_FONT *);				//������`�悷��֐�
VOID MY_TEXT_ALIGN(MY_FONT *, POINT *, SIZE);		//�����̑�������ݒ肷��֐�
VOID MY_DRAW_CHECK_TEXT(int, HDC, RECT);			//�����𔻒f����֐�

///########## �e�L�X�g������������֐� ##########
//���@���F�Ȃ�
//�߂�l�F�Ȃ�
VOID MY_FONT_INIT(VOID)
{
	//���̕����̏�����

	wsprintf(MyFont_MARU.string, TEXT(GAME_MOJI_MARU));	//�\�����镶��
	wsprintf(MyFont_MARU.fontname, FNT_MS_GOTHIC);		//�\�����镶���̃t�H���g
	MyFont_MARU.charset = ANSI_CHARSET;					//�����R�[�h

	MyFont_MARU.rect.left = 0;							//�l�p�̍����X���W
	MyFont_MARU.rect.top = 0;							//�l�p�̍����Y���W
	MyFont_MARU.rect.right = 0;							//�l�p�̉E����X���W
	MyFont_MARU.rect.bottom = 0 / 2;					//�l�p�̉E����Y���W

	MyFont_MARU.size = GAME_OX_SIZE;					//�����̑傫��
	MyFont_MARU.bold = MOJI_REGU;						//����
	MyFont_MARU.ita = FALSE;							//�Α�
	MyFont_MARU.ul = FALSE;								//����
	MyFont_MARU.st = FALSE;								//�ł�����
	MyFont_MARU.align = TEXT_ALIGN_C_CENTER;			//���E�㉺��������

	MyFont_MARU.bkcolor = RGB(255, 255, 255);			//�w�i�F
	MyFont_MARU.color = RGB(255, 0, 0);					//�����F
	MyFont_MARU.bkmode = MOJI_BKMD_TRAN;				//�w�i���[�h

	//�~�̕����̏�����

	wsprintf(MyFont_BATU.string, TEXT(GAME_MOJI_BATU));	//�\�����镶��
	wsprintf(MyFont_BATU.fontname, FNT_MS_GOTHIC);		//�\�����镶���̃t�H���g
	MyFont_BATU.charset = ANSI_CHARSET;					//�����R�[�h

	MyFont_BATU.rect.left = 0;							//�l�p�̍����X���W
	MyFont_BATU.rect.top = 0;							//�l�p�̍����Y���W
	MyFont_BATU.rect.right = 0;							//�l�p�̉E����X���W
	MyFont_BATU.rect.bottom = 0 / 2;					//�l�p�̉E����Y���W

	MyFont_BATU.size = GAME_OX_SIZE;					//�����̑傫��
	MyFont_BATU.bold = MOJI_REGU;						//����
	MyFont_BATU.ita = FALSE;							//�Α�
	MyFont_BATU.ul = FALSE;								//����
	MyFont_BATU.st = FALSE;								//�ł�����
	MyFont_BATU.align = TEXT_ALIGN_C_CENTER;			//���E�㉺��������

	MyFont_BATU.bkcolor = RGB(255, 255, 255);			//�w�i�F
	MyFont_BATU.color = RGB(0, 0, 255);					//�����F
	MyFont_BATU.bkmode = MOJI_BKMD_TRAN;				//�w�i���[�h

}

///########## �����𔻒f����֐� ##########
//���@���F�����~�̎��
//���@���F������ޯ̧�ݸޗp�����޲���÷�Ă������
//���@���F�����̕`��̈�
//�߂�l�F�Ȃ�
VOID MY_DRAW_CHECK_TEXT(int MaruBatu, HDC double_hdc, RECT rect)
{
	switch (MaruBatu)
	{
	case GAME_MOJI_NUM_MARU:

		//�\���ꏊ�̐ݒ�
		MyFont_MARU.rect = rect;

		//�����̕`��
		MY_DRAW_DRAW_TEXT(double_hdc, &MyFont_MARU);

		break;

	case GAME_MOJI_NUM_BATU:

		//�\���ꏊ�̐ݒ�
		MyFont_BATU.rect = rect;

		//�����̕`��
		MY_DRAW_DRAW_TEXT(double_hdc, &MyFont_BATU);
		
		break;
	}
}

///########## ������`�悷��֐� ##########
//���@���F������ޯ̧�ݸޗp�����޲���÷�Ă������
//���@���F�t�H���g�\����
//�߂�l�F�Ȃ�
VOID MY_DRAW_DRAW_TEXT(HDC double_hdc, MY_FONT *MyFont)
{
	//�t�H���g�̏ڍ׏��
	TEXTMETRIC tm;

	SIZE sz;		//�����̑傫�����
	POINT text_pt;	//������XY���W

	//�t�H���g���쐬����
	MyFont->hfont = MY_FONT_CREATE(double_hdc, MyFont);

	//�t�H���g��ݒ肷�違�ȑO�̃t�H���g���擾����
	HFONT hOldFont = (HFONT)SelectObject(double_hdc, MyFont->hfont);

	//�t�H���g�̏ڍ׏����擾
	GetTextMetrics(double_hdc, &tm);

	SetTextColor(double_hdc, MyFont->bkcolor);	//�w�i�F
	SetTextColor(double_hdc, MyFont->color);	//�����F
	SetBkMode(double_hdc, MyFont->bkmode);		//�w�i���[�h

	//�����̑傫�����擾
	GetTextExtentPoint32(
		double_hdc,
		MyFont->string,
		lstrlen(MyFont->string),
		&sz);

	//������\��
	TextOut(
		double_hdc,
		MyFont->rect.left,
		MyFont->rect.top,
		MyFont->string,
		lstrlen(MyFont->string));

	//�ȑO�̃t�H���g�ɖ߂�
	SelectObject(double_hdc, hOldFont);

	//�s�v�ȃt�H���g���폜
	DeleteObject(MyFont->hfont);

	return;
}

///########## �ꎞ�I�Ƀt�H���g��ǂݍ��ފ֐� ##########
//���@���F�A�v���P�[�V�����̃E�B���h�E�n���h��
//�߂�l�F�Ȃ�
BOOL MY_FONT_READ(HWND hWnd)
{
	//judge hard�t�H���g���ꎞ�I�ɓǂݍ���
	if (AddFontResourceEx(FNT_JUD_PASS, FR_PRIVATE, NULL) == 0)
	{
		//�t�H���g���ǂݍ��߂Ȃ������Ƃ�
		MessageBox(hWnd, ERR_MSG_NO_READ_FONT, ERR_MSG_FONT_TITLE, MB_OK);

		return FALSE;
	}

	//���ʂ������}�W�b�N�t�H���g���ꎞ�I�ɓǂݍ���
	if (AddFontResourceEx(FNT_TANU_PASS, FR_PRIVATE, NULL) == 0)
	{
		//�t�H���g���ǂݍ��߂Ȃ������Ƃ�
		MessageBox(hWnd, ERR_MSG_NO_READ_FONT, ERR_MSG_FONT_TITLE, MB_OK);

		return FALSE;
	}

	//�S�b�h�C�[�^�[���t�H���g���ꎞ�I�ɓǂݍ���
	if (AddFontResourceEx(FNT_GOD_PASS, FR_PRIVATE, NULL) == 0)
	{
		//�t�H���g���ǂݍ��߂Ȃ������Ƃ�
		MessageBox(hWnd, ERR_MSG_NO_READ_FONT, ERR_MSG_FONT_TITLE, MB_OK);

		return FALSE;
	}

	return TRUE;
}

///########## �t�H���g��ݒ肷��֐� ##########
//���@���F������ޯ̧�ݸޗp�����޲���÷�Ă������
//���@���F�t�H���g�\����
//�߂�l�F�Ȃ�
HFONT MY_FONT_CREATE(HDC hdc, MY_FONT *MyText)
{
	HFONT hFont;
	hFont = CreateFont(
		MyText->size,			//�t�H���g�̍��� / 0�Ȃ�f�t�H���g(�傫��)
		0,						//������		 / 0�Ȃ玩���v�Z
		MyText->angle,			//�e�L�X�g�̊p�x
		0,						//�x�[�X���C����X���Ƃ̊p�x
		MyText->bold,			//�t�H���g�̏d���i�����j
		MyText->ita,			//�C�^���b�N��
		MyText->ul,				//�A���_�[���C��
		MyText->st,				//�ł�������
		MyText->charset,		//�����Z�b�g
		OUT_DEFAULT_PRECIS,		//�o�͐��x
		CLIP_DEFAULT_PRECIS,	//�N���b�s���O���x
		PROOF_QUALITY,			//�o�͕i��
		FIXED_PITCH | FF_MODERN,//�s�b�`�ƃt�@�~���[
		MyText->fontname);		//�t�H���g�̏��̖�

	return hFont;
}

///########## �ꎞ�I�ȃt�H���g���폜����֐� ##########
//���@���F�A�v���P�[�V�����̃E�B���h�E�n���h��
//�߂�l�F�Ȃ�
VOID MY_FONT_REMOVE(HWND hWnd)
{
	//�ꎞ�I�ɓǂݍ��� judge hard�t�H���g���폜
	RemoveFontResourceEx(FNT_JUD_PASS, FR_PRIVATE, NULL);

	//�ꎞ�I�ɓǂݍ��� ���ʂ������}�W�b�N�t�H���g���폜
	RemoveFontResourceEx(FNT_TANU_PASS, FR_PRIVATE, NULL);

	//�ꎞ�I�ɓǂݍ��� �S�b�h�C�[�^�[���}�W�b�N�t�H���g���폜
	RemoveFontResourceEx(FNT_GOD_PASS, FR_PRIVATE, NULL);

	return;
}

///########## �����̑������̐ݒ肷��֐� ##########
//���@���F�t�H���g�\����
//���@���F�t�H���g�̍���̍��W(�|�C���^)
//���@���F�����̃T�C�Y
//�߂�l�F�Ȃ�
VOID MY_TEXT_ALIGN(MY_FONT *MyText, POINT *pt, SIZE sz)
{
	//�\�����@
	switch (MyText->align)
	{

	case TEXT_ALIGN_U_LEFT:
		//�c�F�㑵���@/���F������

		pt->x = MyText->rect.left;
		pt->y = MyText->rect.top;

		break;

	case TEXT_ALIGN_U_CENTER:
		//�c�F�㑵���@/���F��������

		pt->x = MyText->rect.left + MyText->rect.right / 2 - sz.cx / 2;
		pt->y = MyText->rect.top;

		break;

	case TEXT_ALIGN_U_RIGHT:
		//�c�F�㑵���@/���F�E����

		pt->x = MyText->rect.left + MyText->rect.right - sz.cx;
		pt->y = MyText->rect.top;

		break;

	case TEXT_ALIGN_C_LEFT:
		//�c�F��������/���F������

		pt->x = MyText->rect.left;
		pt->y = MyText->rect.top + MyText->rect.bottom / 2 - sz.cy / 2;

		break;

	case TEXT_ALIGN_C_CENTER:
		//�c�F��������/���F��������

		pt->x = MyText->rect.left + MyText->rect.right / 2 - sz.cx / 2;
		pt->y = MyText->rect.top + MyText->rect.bottom / 2 - sz.cy / 2;

		break;

	case TEXT_ALIGN_C_RIGHT:
		//�c�F��������/���F�E����

		pt->x = MyText->rect.left + MyText->rect.right - sz.cx;
		pt->y = MyText->rect.top + MyText->rect.bottom / 2 - sz.cy / 2;

		break;

	case TEXT_ALIGN_D_LEFT:
		//�c�F�������@/���F������

		pt->x = MyText->rect.left;
		pt->y = MyText->rect.top + MyText->rect.bottom - sz.cy;

		break;

	case TEXT_ALIGN_D_CENTER:
		//�c�F�������@/���F��������

		pt->x = MyText->rect.left + MyText->rect.right / 2 - sz.cx / 2;
		pt->y = MyText->rect.top + MyText->rect.bottom - sz.cy;

		break;

	case TEXT_ALIGN_D_RIGHT:
		//�c�F�������@/���F�E����

		pt->x = MyText->rect.left + MyText->rect.right - sz.cx;
		pt->y = MyText->rect.top + MyText->rect.bottom - sz.cy;

		break;
	}

	return;
}
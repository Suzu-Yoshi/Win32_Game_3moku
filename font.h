///����������������������������������������
//font.h
///����������������������������������������

///########## �w�b�_�t�@�C���ǂݍ��� ##########
#include <Windows.h>
#pragma comment(lib, "msimg32.lib")

///########## �}�N����` ##########

//+++++ �G���[���b�Z�[�W ++++++++++++++++++++

#define ERR_MSG_FONT_TITLE		TEXT("FONT_ERROR")

#define ERR_MSG_NO_READ_FONT	TEXT("�t�H���g��\
�ǂݍ��߂܂���ł���\n�v���O�������I�����܂�")

#define ERR_MSG_NO_REM_FONT	TEXT("�t�H���g��\
�폜�ł��܂���ł���\n�v���O�������I�����܂�")

//+++++ �����R�[�h ++++++++++++++++++++

#define MOJICD_ANSI ANSI_CHARSET		//ANSI
#define MOJICD_SJIS SHIFTJIS_CHARSET	//SHIFT-JIS
#define MOJICD_DEFL	DEFAULT_CHARSET		//�f�t�H���g

//+++++ �����̕\������ ++++++++++++++++++++

#define MOJI_LEFT_RIGHT    0	//  0�x	//������E
#define MOJI_DONW_UP	 900	// 90�x	//�������
#define MOJI_RIGHT_LEFT	1800	//180�x	//�E���獶
#define MOJI_UP_DOWN	2700	//270�x	//�ォ�牺

//+++++ �����̑��� ++++++++++++++++++++
#define MOJI_REGU	FW_REGULAR	//�W���̑���
#define MOJI_BOLD	FW_BOLD 	//�W���̑���

//+++++ �����̔w�i���[�h ++++++++++++++++++++
#define MOJI_BKMD_TRAN	TRANSPARENT	//�w�i���c��
#define MOJI_BKMD_OPAQ	OPAQUE		//�w�i��h��Ԃ�

//+++++ ���ł�PC�ɃC���X�g�[������Ă���t�H���g ++++++++++++++++++++

#define FNT_MS_GOTHIC TEXT("�l�r �S�V�b�N")	//�l�r�͑啶���A���p��
#define FNT_MS_MINCHO TEXT("�l�r ����")		//�l�r�͑啶���A���p��

//+++++ �ꎞ�I�ɓǂݍ��ރt�H���g ++++++++++++++++++++

//FNT_XXX_PASS�F�t�H���g�̑��΃p�X

//FNT_XXX_NAME�F�t�H���g�̖���

#define FNT_JUD_PASS	TEXT(".\\MY_FONT\\JUDGE2.TTF")
#define FNT_JUD_NAME	TEXT("Judge Hard")

#define FNT_TANU_PASS	TEXT(".\\MY_FONT\\TanukiMagic.ttf")
#define FNT_TANU_NAME	TEXT("���ʂ������}�W�b�N")

#define FNT_GOD_PASS	TEXT(".\\MY_FONT\\GodEaterRegular.ttf")
#define FNT_GOD_NAME	TEXT("GodEater")

//+++++ �����̑����� ++++++++++++++++++++

#define TEXT_ALIGN_U_LEFT	1	//�c�F�㑵���@/���F������
#define TEXT_ALIGN_U_CENTER	2	//�c�F�㑵���@/���F��������
#define TEXT_ALIGN_U_RIGHT	3	//�c�F�㑵���@/���F�E����

#define TEXT_ALIGN_C_LEFT	4	//�c�F��������/���F������
#define TEXT_ALIGN_C_CENTER	5	//�c�F��������/���F��������
#define TEXT_ALIGN_C_RIGHT	6	//�c�F��������/���F�E����

#define TEXT_ALIGN_D_LEFT	7	//�c�F�������@/���F������
#define TEXT_ALIGN_D_CENTER	8	//�c�F�������@/���F��������
#define TEXT_ALIGN_D_RIGHT	9	//�c�F�������@/���F�E����

//+++++ ���̑� ++++++++++++++++++++

#define MAX_STRING_NUM	512	//�ő啶����

///########## �\���� ##########

//�t�H���g�\����
struct MY_STRUCT_FONT
{
	HFONT	hfont;
	TCHAR	string[MAX_STRING_NUM] = TEXT("");		//�����̓��e
	TCHAR	fontname[MAX_STRING_NUM] = TEXT("");	//�t�H���g�̖��O
	int		size;		//�����̑傫��
	int		angle;		//�����̕\���p�x
	int		bold;		//����
	BOOL	ita;		//�Α�
	BOOL	ul;			//����
	BOOL	st;			//�ł�������
	int		charset;	//�����R�[�h
	RECT	rect;		//�����̕\���ʒu
	int		align;		//�����̑�����
	COLORREF bkcolor;	//�����̔w�i�F
	COLORREF color;		//�����̐F
	BOOL	 bkmode;	//�w�i�F�̐ݒ�
};

///########## ���O�̍Ē�` ##########

typedef MY_STRUCT_FONT	MY_FONT;

///��������������������������������������������������������
#pragma once	//��d�C���N���[�h�̖h�~
///��������������������������������������������������������

///########## �O���[�o���ϐ� �Q�Ƃ̐錾 ##########

///���������� �{�̂�font.cpp ����������

//�e�L�X�g�\���̂̕ϐ�
extern MY_FONT MyFont_MARU;			//���̕���
extern MY_FONT MyFont_BATU;			//�~�̕���

///���������� �{�̂�font.cpp ����������

///##########  �֐� �Q�Ƃ̐錾 ##########

///���������� �{�̂�font.cpp ����������

extern VOID MY_FONT_INIT(VOID);							//�e�L�X�g������������
extern BOOL MY_FONT_READ(HWND);							//�t�H���g���ꎞ�I�ɓǂݍ���
extern HFONT MY_FONT_CREATE(HDC, MY_FONT *);			//�t�H���g���쐬����
extern VOID MY_FONT_REMOVE(HWND);						//�ꎞ�I�ɓǂݍ��񂾃t�H���g���폜����
extern VOID MY_DRAW_DRAW_TEXT(HDC, MY_FONT *);			//������`�悷��֐�
extern VOID MY_TEXT_ALIGN(MY_FONT *, POINT *, SIZE);	//�����̑�������ݒ肷��֐�
extern VOID MY_DRAW_CHECK_TEXT(int, HDC, RECT);			//�����𔻒f����֐�
///���������� �{�̂�font.cpp ����������
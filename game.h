///����������������������������������������
//game.h
///����������������������������������������

///########## �w�b�_�t�@�C���ǂݍ��� ##########
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <locale.h>
#include "main.h"

///########## �}�N����` ##########

//�}�X�̐�
#define GAME_MASU_MAX	3	//GAME_MASU_MAX �~ GAME_MASU_MAX�̃}�X���쐬

//�}�X�ڂ̏��
#define GAME_MASU_NONE	0	//�������
#define GAME_MASU_MARU	1	//���̂Ƃ��F��U
#define GAME_MASU_BATU	2	//�~�̂Ƃ��F��U

//�\�����镶��
#define GAME_MOJI_MARU	"��"	//���̕���
#define GAME_MOJI_BATU	"�~"	//�~�̕���

//����~�̑傫��
#define GAME_OX_SIZE  100	//GAME_OX_SIZE �~ GAME_OX_SIZE�̑傫���ō쐬 

//���̏����^�C�g��
#define GAME_WIN_O_TITLE	"WINNER[��]"
//���̏�����
#define GAME_WIN_O_TEXT		"���̏���"

//�~�̏����^�C�g��
#define GAME_WIN_X_TITLE	"WINNER[�~]"
//�~�̏�����
#define GAME_WIN_X_TEXT		"�~�̏���"

//���������̃^�C�g��
#define GAME_DRAW_TITLE		"DRAW"
//���������̏�����
#define GAME_DRAW_TEXT		"��������"

//������x�V�Ԃ��̃^�C�g��
#define GAME_WIN_REPLAY_TITLE	"REPLAY?"
//������x�V�Ԃ��̕�
#define GAME_WIN_REPLAY_TEXT	"������x�V�т܂����H"

///########## �\���� ##########

///########## ���O�̍Ē�` ##########

///��������������������������������������������������������
#pragma once	//��d�C���N���[�h�̖h�~
///��������������������������������������������������������

///########## �O���[�o���ϐ� �Q�Ƃ̐錾 ##########

///���������� �{�̂�game.cpp ����������

///���������� �{�̂�game.cpp ����������

///########## �O�� �֐� �Q�Ƃ̐錾 ##########

///���������� �{�̂�game.cpp ����������

//�Q�[�����̌v�Z������֐�
extern VOID MY_CALC_GAME(VOID);

//�}�X���N���b�N�����Ƃ��̏������s���֐�
extern VOID MY_CLICK_MASU(VOID);

//�}�X���N���b�N�����Ƃ��̔z��̕ύX���s���֐�
extern BOOL MY_CHANGE_MASU(POINT,int);

//��ʂ�`�悷��֐�
extern VOID MY_DRAW_GAME(MY_WIN);

//��ʂ̔w�i��`�悷��֐�
extern VOID MY_DRAW_BACKSCREEN(HDC, RECT);

//��ʂ̏c����`�悷��֐�
extern VOID MY_DRAW_LINE_TATE(HDC , RECT );

//��ʂ̉�����`�悷��֐�
extern VOID MY_DRAW_LINE_YOKO(HDC , RECT );

//�}�X������������֐�
extern VOID MY_INIT_MASU(VOID);

//����~��\������֐�
extern VOID MY_DRAW_OX(HDC);

//�}�E�X�̈ʒu��\������֐�
extern VOID MY_DRAW_MOUSE_POINT(HDC);

//�v���C���[�̔Ԃ�����������֐�
extern VOID MY_INIT_PLAYER_TURN(VOID);

//���s�`�F�b�N������֐�
extern VOID MY_CHECK_WIN_LOSE(HWND);

///���������� �{�̂�game.cpp ����������
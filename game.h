///����������������������������������������
//game.h
///����������������������������������������

///########## �w�b�_�t�@�C���ǂݍ��� ##########
#include <windows.h>
#include "main.h"

///########## �}�N����` ##########

//�}�X�̐�
#define GAME_MASU_MAX	3	//GAME_MASU_MAX �~ GAME_MASU_MAX�̃}�X���쐬

//�}�X�ڂ̏��
#define GAME_MASU_NONE	0	//�󔒂̂Ƃ�
#define GAME_MASU_MARU	1	//���̂Ƃ�
#define GAME_MASU_BATU	2	//�~�̂Ƃ�

//�\�����镶��
#define GAME_MOJI_MARU	"��"	//���̕���
#define GAME_MOJI_BATU	"�~"	//�~�̕���

#define GAME_MOJI_NUM_MARU	1	//���̎��
#define GAME_MOJI_NUM_BATU	2	//�~�̎��


//����~�̑傫��
#define GAME_OX_SIZE  100	//GAME_OX_SIZE �~ GAME_OX_SIZE�̑傫���ō쐬 



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

///���������� �{�̂�game.cpp ����������
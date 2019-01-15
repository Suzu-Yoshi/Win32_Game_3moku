///����������������������������������������
//winproc.cpp
///����������������������������������������

///########## �w�b�_�t�@�C���ǂݍ��� ##########
#include "main.h"
#include "game.h"
#include "font.h"

///########## ���C�u�����ǂݍ��� ##########

///########## �}�N����` ##########

///########## �񋓌^ ##########

///########## �\���� ##########

///########## ���O�̍Ē�` ##########

///########## �O���[�o���ϐ��̐錾�Ə����� ##########

//�}�X�ڂ��Ǘ�����z��
int masu[GAME_MASU_MAX][GAME_MASU_MAX];

///########## �v���g�^�C�v�錾 ##########

//��ʂ�`�悷��֐�
VOID MY_DRAW_GAME(MY_WIN);

//��ʂ̔w�i��`�悷��֐�
VOID MY_DRAW_BACKSCREEN(HDC, RECT);

//��ʂ̏c����`�悷��֐�
VOID MY_DRAW_LINE_TATE(HDC hdc_double, RECT rect);

//��ʂ̉�����`�悷��֐�
VOID MY_DRAW_LINE_YOKO(HDC hdc_double, RECT rect);

//�}�X������������֐�
VOID MY_INIT_MASU(VOID);

//����~��\������֐�
VOID MY_DRAW_OX(HDC);

///########## ��ʂ�`�悷��֐� ##########
//���@���F������ޯ̧�ݸޗp�����޲���÷�Ă������
//�߂�l�F�Ȃ�
VOID MY_DRAW_GAME(MY_WIN mywin)
{
	//�w�i��`�悷��
	MY_DRAW_BACKSCREEN(mywin.hdc_double, mywin.win_rect_cli);

	//��ʂ̏c����`�悷��
	MY_DRAW_LINE_TATE(mywin.hdc_double, mywin.win_rect_cli);

	//��ʂ̉�����`�悷��
	MY_DRAW_LINE_YOKO(mywin.hdc_double, mywin.win_rect_cli);

	//����~��\������
	MY_DRAW_OX(mywin.hdc_double);

}

///########## ��ʂ̔w�i��`�悷��֐� ##########
//���@���F������ޯ̧�ݸޗp�����޲���÷�Ă������
//���@���F�N���C�A���g�̈�
//�߂�l�F�Ȃ�
VOID MY_DRAW_BACKSCREEN(HDC hdc_double, RECT rect)
{
	//�u���V���쐬
	HBRUSH hbrush = CreateSolidBrush(RGB(255, 255, 240));

	//�u���V��ݒ聕�ȑO�̃u���V���擾
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc_double, hbrush);

	//�l�p��`��
	Rectangle(
		hdc_double,		//�f�o�C�X�R���e�L�X�g�̃n���h��
		rect.left,		//�l�p�̍����X���W
		rect.top,		//�l�p�̍����Y���W
		rect.right,		//�l�p�̉E����X���W
		rect.bottom);	//�l�p�̉E����Y���W

	//�ȑO�̃u���V�ɖ߂�
	SelectObject(hdc_double, hOldBrush);

	//�u���V���폜
	DeleteObject(hbrush);

}

///########## ��ʂ̏c����`�悷��֐� ##########
//���@���F������ޯ̧�ݸޗp�����޲���÷�Ă������
//���@���F�N���C�A���g�̈�
//�߂�l�F�Ȃ�
VOID MY_DRAW_LINE_TATE(HDC hdc_double, RECT rect)
{
	//���[�v�Ŏg�p
	int loop = 0;

	//����`���ő吔 
	int Draw_Line_MAX = GAME_MASU_MAX + 1;	//	+1�͈�ԉ��̐�

	//���̕`���n�߈ʒu
	POINT pt_Start;
	pt_Start.x = rect.left;
	pt_Start.y = rect.top;

	//���̕`���I���ʒu
	POINT pt_End;
	pt_End.x = rect.left;
	pt_End.y = rect.bottom;

	//�y�����쐬
	HPEN hpen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));

	//�y����ݒ聕�ȑO�̃y�����擾
	HPEN hOldPen = (HPEN)SelectObject(hdc_double, hpen);

	for (loop = 0; loop < Draw_Line_MAX; loop++)
	{

		//���̕`���n�߈ʒu
		MoveToEx(
			hdc_double,							//�f�o�C�X�R���e�L�X�g�̃n���h��
			pt_Start.x + loop * GAME_OX_SIZE,	//�`���n�߂�X���W
			pt_Start.y,							//�`���n�߂�Y���W
			NULL);								//�ȑO�̃J�����g�|�W�V����/�K�v�Ȃ��Ȃ�NULL

		//����`��(�΂ߖ_)
		LineTo(
			hdc_double,						//�f�o�C�X�R���e�L�X�g�̃n���h��
			pt_End.x + loop * GAME_OX_SIZE,	//�`���I���X���W
			pt_End.y);						//�`���I���Y���W
	}

	//�ȑO�̃y���ɖ߂�
	SelectObject(hdc_double, hOldPen);

	//�y�����폜
	DeleteObject(hpen);
}

///########## ��ʂ̉�����`�悷��֐� ##########
//���@���F������ޯ̧�ݸޗp�����޲���÷�Ă������
//���@���F�N���C�A���g�̈�
//�߂�l�F�Ȃ�
VOID MY_DRAW_LINE_YOKO(HDC hdc_double, RECT rect)
{
	//���[�v�Ŏg�p
	int loop = 0;

	//����`���ő吔
	int Draw_Line_MAX = GAME_MASU_MAX + 1;	//	+1�͈�ԉE�̐�

	//���̕`���n�߈ʒu
	POINT pt_Start;
	pt_Start.x = rect.left;
	pt_Start.y = rect.top;

	//���̕`���I���ʒu
	POINT pt_End;
	pt_End.x = rect.right;
	pt_End.y = rect.top;

	//�y�����쐬
	HPEN hpen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));

	//�y����ݒ聕�ȑO�̃y�����擾
	HPEN hOldPen = (HPEN)SelectObject(hdc_double, hpen);

	for (loop = 0; loop < Draw_Line_MAX; loop++)
	{

		//���̕`���n�߈ʒu
		MoveToEx(
			hdc_double,							//�f�o�C�X�R���e�L�X�g�̃n���h��
			pt_Start.x,							//�`���n�߂�X���W
			pt_Start.y + loop * GAME_OX_SIZE,	//�`���n�߂�Y���W
			NULL);								//�ȑO�̃J�����g�|�W�V����/�K�v�Ȃ��Ȃ�NULL

		//����`��(�΂ߖ_)
		LineTo(
			hdc_double,							//�f�o�C�X�R���e�L�X�g�̃n���h��
			pt_End.x,							//�`���I���X���W
			pt_End.y + loop * GAME_OX_SIZE);	//�`���I���Y���W
	}

	//�ȑO�̃y���ɖ߂�
	SelectObject(hdc_double, hOldPen);

	//�y�����폜
	DeleteObject(hpen);
}

///########## �}�X������������֐� ##########
//���@���F�Ȃ�
//�߂�l�F�Ȃ�
VOID MY_INIT_MASU(VOID)
{
	int tate;
	int yoko;

	for (tate = 0; tate < GAME_MASU_MAX; tate++)
	{
		for (yoko = 0; yoko < GAME_MASU_MAX; yoko++)
		{
			//�z���������
			masu[tate][yoko] = GAME_MASU_NONE;
		}
	}
}

///########## ����~��\������֐� ##########
//���@���F�Ȃ�
//�߂�l�F�Ȃ�
VOID MY_DRAW_OX(HDC double_hdc)
{
	int tate;
	int yoko;

	//������`�悷��̈�
	RECT rect;

	for (tate = 0; tate < GAME_MASU_MAX; tate++)
	{
		for (yoko = 0; yoko < GAME_MASU_MAX; yoko++)
		{
			//������`�悷��̈���v�Z����
			rect.left = yoko * GAME_OX_SIZE;			//�����X���W
			rect.top = tate * GAME_OX_SIZE;				//�����Y���W
			rect.right = (yoko + 1) * GAME_OX_SIZE;		//�E����X���W
			rect.bottom = (tate + 1) * GAME_OX_SIZE;	//�E����Y���W

			//�z������ɕ`��
			switch (masu[tate][yoko])
			{
			case GAME_MASU_MARU:
				//�z��Ɂ��̃f�[�^�������Ă���Ƃ�

				//������`��
				MY_DRAW_CHECK_TEXT(GAME_MOJI_NUM_MARU, double_hdc, rect);

				break;
			case GAME_MASU_BATU:
				//�z��Ɂ~�̃f�[�^�������Ă���Ƃ�

				//������`��
				MY_DRAW_CHECK_TEXT(GAME_MOJI_NUM_BATU, double_hdc, rect);

				break;
			case GAME_MASU_NONE:
				//�z��Ƀf�[�^�������Ă��Ȃ��Ƃ�

				break;
			}
		}
	}
}
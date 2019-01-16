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

//�v���C���[�̔Ԃ��Ǘ�����ϐ�
int player_turn;

///########## �v���g�^�C�v�錾 ##########

//�Q�[�����̌v�Z������֐�
VOID MY_CALC_GAME(VOID);

//�}�X���N���b�N�����Ƃ��̏������s���֐�
VOID MY_CLICK_MASU(VOID);

//�}�X���N���b�N�����Ƃ��̔z��̏����̊֐�
BOOL MY_CHANGE_MASU(POINT, int);

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

//�}�E�X�̈ʒu��\������֐�
VOID MY_DRAW_MOUSE_POINT(HDC);

//�v���C���[�̔Ԃ�����������֐�
VOID MY_INIT_PLAYER_TURN(VOID);

//���s�`�F�b�N������֐�
VOID MY_CHECK_WIN_LOSE(HWND);

///########## �Q�[�����̌v�Z������֐� ##########
//���@���F�Ȃ�
//�߂�l�F�Ȃ�
VOID MY_CALC_GAME(VOID)
{


}

///########## �}�X���N���b�N�����Ƃ��̏������s���֐� ##########
//���@���F�Ȃ�
//�߂�l�F�Ȃ�
VOID MY_CLICK_MASU(VOID)
{

	BOOL isClickNone = FALSE;

	switch (player_turn)
	{
	case GAME_MASU_MARU:
		//���̃v���C���[�̂Ƃ�

		//�}�X���N���b�N�����Ƃ��̔z��̏���
		isClickNone = MY_CHANGE_MASU(MyWin.point_Mouse, GAME_MASU_MARU);

		//�����~���u�����Ƃ�
		if (isClickNone == TRUE)
		{
			//�v���C���[�̔Ԃ�ύX����
			player_turn = GAME_MASU_BATU;
		}

		break;
	case GAME_MASU_BATU:
		//�~�̃v���C���[�̂Ƃ�

		//�}�X���N���b�N�����Ƃ��̔z��̏���
		isClickNone = MY_CHANGE_MASU(MyWin.point_Mouse, GAME_MASU_BATU);

		//�����~���u�����Ƃ�
		if (isClickNone == TRUE)
		{
			//�v���C���[�̔Ԃ�ύX����
			player_turn = GAME_MASU_MARU;
		}

		break;
	}

}

///########## �}�X���N���b�N�����Ƃ��̔z��̏����̊֐� ##########
//���@���F�}�E�X���WX
//���@���F�}�E�X���WY
//���@���F�v���C���[�̎��
//�߂�l�F�����~��u������TRUE
//�߂�l�F�����~�����ɒu����Ă�����FALSE
BOOL MY_CHANGE_MASU(POINT mouse_pt, int player)
{
	//�c�̏ꏊ���v�Z
	int tate = mouse_pt.y / GAME_OX_SIZE;
	//���̏ꏊ���v�Z
	int yoko = mouse_pt.x / GAME_OX_SIZE;

	if (masu[tate][yoko] == GAME_MASU_NONE)
	{
		//�����~���܂��u���Ă��Ȃ��Ƃ�

		switch (player)
		{
		case GAME_MASU_MARU:
			//���̃v���C���[�̂Ƃ�
			masu[tate][yoko] = GAME_MASU_MARU;

			break;
		case GAME_MASU_BATU:
			//�~�̃v���C���[�̂Ƃ�
			masu[tate][yoko] = GAME_MASU_BATU;

			break;
		}

		//�����~���u����
		return TRUE;
	}
	else
	{
		//�����~�����ɒu����Ă���Ƃ�

		//�����~���u���Ȃ�����
		return FALSE;
	}
}

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
				MY_DRAW_CHECK_TEXT(GAME_MASU_MARU, double_hdc, rect);

				break;
			case GAME_MASU_BATU:
				//�z��Ɂ~�̃f�[�^�������Ă���Ƃ�

				//������`��
				MY_DRAW_CHECK_TEXT(GAME_MASU_BATU, double_hdc, rect);

				break;
			case GAME_MASU_NONE:
				//�z��Ƀf�[�^�������Ă��Ȃ��Ƃ�

				break;
			}
		}
	}
}

///########## �}�E�X�̈ʒu��\������֐� ##########
//���@���F�f�o�C�X�R���e�L�X�g�̃n���h��
//���@���F�Ȃ�
VOID MY_DRAW_MOUSE_POINT(HDC hdc)
{
	//FPS�l�𐮌`���邽�߂̕ϐ�
	CHAR strfpsChr[64];
	size_t wLen = 0;
	errno_t err = 0;

	//FPS�l�𐮌`
	sprintf(strfpsChr, "�}�E�X���W[X:%03d][Y:%03d]", MyWin.point_Mouse.x, MyWin.point_Mouse.y);

	//FPS�l��\�����邽�߂̕ϐ�
	TCHAR StrfpsTch[64];

	//���P�[���w��
	setlocale(LC_ALL, "japanese");

	//��������}���`�o�C�g�������烏�C�h�����ɕϊ�
	err = mbstowcs_s(
		&wLen,				//�ϊ����ꂽ������
		StrfpsTch,			//�ϊ����ꂽ���C�h����
		strlen(strfpsChr),	//�ϊ����镶����
		strfpsChr,			//�ϊ�����}���`�o�C�g����
		_TRUNCATE			//�o�b�t�@�Ɏ��܂邾���̕�����܂ŕϊ�
	);

	SetBkMode(hdc, TRANSPARENT);			//�w�i�F�͏㏑�����Ȃ�
	SetTextColor(hdc, RGB(0, 0, 0));		//�����F
	SetBkColor(hdc, RGB(255, 255, 255));	//�w�i�F

	//FPS��`��
	TextOut(hdc, 5, 20, StrfpsTch, lstrlen(StrfpsTch));
}

///########## �v���C���[�̔Ԃ�����������֐� ##########
//���@���F�Ȃ�
//�߂�l�F�Ȃ�
VOID MY_INIT_PLAYER_TURN(VOID)
{
	//������
	player_turn = GAME_MASU_NONE;

	//�����_���Ńv���C���[�����߂�
	int random;

	//���������Ƃɗ����\���쐬
	srand((unsigned)time(NULL));

	//�����_����0��1��I��
	random = (rand() % 2) + 1;

	//����������
	switch (random)
	{
	case GAME_MASU_MARU:
		player_turn = GAME_MASU_MARU;
		break;
	case GAME_MASU_BATU:
		player_turn = GAME_MASU_BATU;
		break;
	}

}

///########## ���s�`�F�b�N������֐� ##########
//���@���F�Ȃ�
//�߂�l�F�Ȃ�
VOID MY_CHECK_WIN_LOSE(HWND hwnd)
{
	//�z��̓Y���Ɏg�p
	int tate;
	int yoko;
	int naname;

	//���Ɓ~�̐����J�E���g
	int maru_cnt;
	int batu_cnt;
	int draw_cnt;

	//TRUE�Ȃ�A����
	BOOL maru_win = FALSE;
	BOOL batu_win = FALSE;

	//��������
	BOOL maru_batu_draw = FALSE;

	//������x�V�Ԃ��̃��b�Z�[�W�{�b�N�X�̖߂�l
	int retPlayMsgBox;

	//+++++ �c�������Ă��邩�`�F�b�N ++++++++++++++++++++
	if (maru_win == FALSE && batu_win == FALSE)
	{
		//���Ɓ~�̐���������
		maru_cnt = 0;
		batu_cnt = 0;

		for (yoko = 0; yoko < GAME_MASU_MAX; yoko++)
		{
			//���Ɓ~�̐���������
			maru_cnt = 0;
			batu_cnt = 0;

			for (tate = 0; tate < GAME_MASU_MAX; tate++)
			{
				//���̐����J�E���g
				if (masu[tate][yoko] == GAME_MASU_MARU)
				{
					maru_cnt++;
				}

				//�~�̐����J�E���g
				if (masu[tate][yoko] == GAME_MASU_BATU)
				{
					batu_cnt++;
				}
			}

			//�������񂾂Ƃ������̏���
			if (maru_cnt == GAME_MASU_MAX)
			{
				maru_win = TRUE;	break;
			}

			//�~�����񂾂Ƃ����~�̏���
			if (batu_cnt == GAME_MASU_MAX)
			{
				batu_win = TRUE;	break;
			}
		}
	}

	//+++++ ���������Ă��邩�`�F�b�N ++++++++++++++++++++
	if (maru_win == FALSE && batu_win == FALSE)
	{
		//���Ɓ~�̐���������
		maru_cnt = 0;
		batu_cnt = 0;

		for (tate = 0; tate < GAME_MASU_MAX; tate++)
		{
			//���Ɓ~�̐���������
			maru_cnt = 0;
			batu_cnt = 0;

			for (yoko = 0; yoko < GAME_MASU_MAX; yoko++)
			{
				//���̐����J�E���g
				if (masu[tate][yoko] == GAME_MASU_MARU)
				{
					maru_cnt++;
				}

				//�~�̐����J�E���g
				if (masu[tate][yoko] == GAME_MASU_BATU)
				{
					batu_cnt++;
				}
			}

			//�������񂾂Ƃ������̏���
			if (maru_cnt == GAME_MASU_MAX)
			{
				maru_win = TRUE;	break;
			}

			//�~�����񂾂Ƃ����~�̏���
			if (batu_cnt == GAME_MASU_MAX)
			{
				batu_win = TRUE;	break;
			}
		}
	}

	//+++++ �΂�(�E������)�������Ă��邩�`�F�b�N ++++++++++++++++++++
	if (maru_win == FALSE && batu_win == FALSE)
	{
		//���Ɓ~�̐���������
		maru_cnt = 0;
		batu_cnt = 0;

		for (naname = 0; naname < GAME_MASU_MAX; naname++)
		{
			//���̐����J�E���g
			if (masu[naname][naname] == GAME_MASU_MARU)
			{
				maru_cnt++;
			}

			//�~�̐����J�E���g
			if (masu[naname][naname] == GAME_MASU_BATU)
			{
				batu_cnt++;
			}

			//�������񂾂Ƃ������̏���
			if (maru_cnt == GAME_MASU_MAX)
			{
				maru_win = TRUE;	break;
			}

			//�~�����񂾂Ƃ����~�̏���
			if (batu_cnt == GAME_MASU_MAX)
			{
				batu_win = TRUE;	break;
			}
		}
	}

	//+++++ �΂�(�E�オ��)�������Ă��邩�`�F�b�N ++++++++++++++++++++
	if (maru_win == FALSE && batu_win == FALSE)
	{
		//���Ɓ~�̐���������
		maru_cnt = 0;
		batu_cnt = 0;

		for (naname = 0; naname < GAME_MASU_MAX; naname++)
		{
			//���̐����J�E���g
			if (masu[naname][(GAME_MASU_MAX - 1) - naname] == GAME_MASU_MARU)
			{
				maru_cnt++;
			}

			//�~�̐����J�E���g
			if (masu[naname][(GAME_MASU_MAX - 1) - naname] == GAME_MASU_BATU)
			{
				batu_cnt++;
			}

			//�������񂾂Ƃ������̏���
			if (maru_cnt == GAME_MASU_MAX)
			{
				maru_win = TRUE;	break;
			}

			//�~�����񂾂Ƃ����~�̏���
			if (batu_cnt == GAME_MASU_MAX)
			{
				batu_win = TRUE;	break;
			}
		}
	}

	//+++++ �����������`�F�b�N ++++++++++++++++++++
	if (maru_win == FALSE && batu_win == FALSE)
	{
		//���Ɓ~�̐���������
		maru_cnt = 0;
		batu_cnt = 0;

		for (tate = 0; tate < GAME_MASU_MAX; tate++)
		{
			for (yoko = 0; yoko < GAME_MASU_MAX; yoko++)
			{
				//���̐����J�E���g
				if (masu[tate][yoko] == GAME_MASU_MARU)
				{
					maru_cnt++;
				}

				//�~�̐����J�E���g
				if (masu[tate][yoko] == GAME_MASU_BATU)
				{
					batu_cnt++;
				}
			}
		}
	}

	//���Ɓ~�̍��v�����v�Z
	draw_cnt = maru_cnt + batu_cnt;

	//���Ɓ~�̍��v�����}�X�̍��v���Ɠ������A��������
	if (draw_cnt == (GAME_MASU_MAX * GAME_MASU_MAX))
	{
		maru_batu_draw = TRUE;
	}

	//�܂����҂����Ȃ��Ƃ��͊֐��𔲂���
	if (maru_win == FALSE && batu_win == FALSE && maru_batu_draw == FALSE)
	{
		return;
	}

	//���̏���
	if (maru_win == TRUE)
	{
		//���b�Z�[�W�{�b�N�X��\��
		MessageBox(NULL, TEXT(GAME_WIN_O_TEXT), TEXT(GAME_WIN_O_TITLE), MB_OK);
	}

	//�~�̏���
	if (batu_win == TRUE)
	{
		//���b�Z�[�W�{�b�N�X��\��
		MessageBox(NULL, TEXT(GAME_WIN_X_TEXT), TEXT(GAME_WIN_X_TITLE), MB_OK);
	}

	//��������
	if (maru_batu_draw == TRUE)
	{
		//���b�Z�[�W�{�b�N�X��\��
		MessageBox(NULL, TEXT(GAME_DRAW_TEXT), TEXT(GAME_DRAW_TITLE), MB_OK);
	}

	//������x�V�Ԃ����₷��

	//���b�Z�[�W�{�b�N�X��\��
	retPlayMsgBox = MessageBox(NULL, TEXT(GAME_WIN_REPLAY_TEXT), TEXT(GAME_WIN_REPLAY_TITLE), MB_YESNO | MB_ICONQUESTION);

	//�u�͂��v�{�^�����������Ƃ�
	if (retPlayMsgBox == IDYES)
	{
		//�������̏������s��

		//�}�X�̏�����
		MY_INIT_MASU();

		//�v���C���[�̏�����
		MY_INIT_PLAYER_TURN();

	}

	//�u�������v�{�^�����������Ƃ�
	if (retPlayMsgBox == IDNO)
	{
		//�I���������s��

		//�E�B���h�E��j������
		DestroyWindow(hwnd);
	}

}
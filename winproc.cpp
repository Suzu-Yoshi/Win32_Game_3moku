///����������������������������������������
//winproc.cpp
///����������������������������������������

///########## �w�b�_�t�@�C���ǂݍ��� ##########
#include "main.h"
#include "fps.h"
#include "winproc.h"
#include "game.h"
#include "font.h"

///########## ���C�u�����ǂݍ��� ##########

///########## �}�N����` ##########

///########## �񋓌^ ##########

///########## �\���� ##########

///########## ���O�̍Ē�` ##########

///########## �O���[�o���ϐ��̐錾�Ə����� ##########

///########## �v���g�^�C�v�錾 ##########

//�E�B���h�E�v���V�[�W��
LRESULT CALLBACK MY_WndProc(HWND, UINT, WPARAM, LPARAM);

///########## �E�B���h�E�v���V�[�W���֐� ##########
//���@���F���b�Z�[�W�����������Ƃ��̃C���X�^���X�n���h��
//���@���F���b�Z�[�W
//���@���F�t�����P
//���@���F�t�����Q
//�߂�l�F�E�B���h�E�v���V�[�W������Ԃ����l
LRESULT CALLBACK MY_WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	//HDC�F�f�o�C�X�R���e�L�X�g�̃n���h��
	HDC hdc;

	//PAINTSTRUCT�F�E�B���h�E���Ƃ̕`������Ǘ�����\����
	PAINTSTRUCT ps;

	switch (msg)
	{

	case WM_CREATE:
		//�E�B���h�E�̐�����������

		///���������� �Q�[���ŗL�̐ݒ肱������ ����������

		//�����̏�����
		MY_FONT_INIT();

		//�t�H���g�̓ǂݍ���
		if (MY_FONT_READ(hwnd) == FALSE)
		{	return -1;}//�ǂݍ��݂Ɉُ�A��

		//�}�X�̏�����
		MY_INIT_MASU();

		//�v���C���[�̏�����
		MY_INIT_PLAYER_TURN();

		///���������� �Q�[���ŗL�̐ݒ肱���܂� ����������

		//�E�B���h�E�𐶐�����Ƃ��́A0��Ԃ�
		return 0;

	case WM_PAINT:
		//�E�B���h�E�����ĕ`�悷��Ƃ�

		//�f�o�C�X�R���e�L�X�g�̃n���h�����擾
		hdc = BeginPaint(hwnd, &ps);

		//���݂̃f�o�C�X�R���e�L�X�g��ۑ�����
		SaveDC(hdc);

		///���������� �Q�[���ŗL�̐ݒ肱������ ����������

		//��ʂ̕`��
		MY_DRAW_GAME(MyWin);

		//FPS�̐��l��`��
		MY_FPS_DRAW(MyWin.hdc_double);

		//�}�E�X�̍��W��`��
		MY_DRAW_MOUSE_POINT(MyWin.hdc_double);

		//�v���C���[�̔Ԃ�`��
		MY_DRAW_PLAYER_OX(MyWin.hdc_double);

		///���������� �Q�[���ŗL�̐ݒ肱���܂� ����������

		//���������̉摜��`��
		BitBlt(hdc,
			0, 0, MyWin.win_rect_cli.right, MyWin.win_rect_cli.bottom,
			MyWin.hdc_double, 0, 0, SRCCOPY);

		//�ۑ������f�o�C�X�R���e�L�X�𕜌�����
		RestoreDC(hdc, -1);

		//�f�o�C�X�R���e�L�X�g�̃n���h�����J������
		EndPaint(hwnd, &ps);

		return 0;

	case WM_LBUTTONDOWN:
		//�}�E�X�̍��{�^���������Ă���Ƃ�

		///���������� �Q�[���ŗL�̐ݒ肱������ ����������
		
		//�}�E�X�̍��W���擾
		MyWin.point_Mouse.y = HIWORD(lp);
		MyWin.point_Mouse.x = LOWORD(lp);

		//�}�X���N���b�N�����Ƃ��̏������s��
		MY_CLICK_MASU();

		///���������� �Q�[���ŗL�̐ݒ肱���܂� ����������

		//�^�C�g���o�[���Ȃ��Ƃ�
		if (MyWin.win_mode == WIN_NO_TITLE)
		{
			//���b�Z�[�W��������
			PostMessage(
				hwnd,				//�E�B���h�E�n���h��
				WM_NCLBUTTONDOWN,	//��N���C�A���g�̈�����N���b�N����
				HTCAPTION,			//�^�C�g���o�[���N���b�N����
				MAKELPARAM(0, 0));	//�}�E�X�̍��W�F0,0

			return 0;
		}

		//�N���C�A���g�̈�O�ł��}�E�X�̓����̊Ď����J�n
		SetCapture(hwnd);

		break;

	case WM_LBUTTONUP:
		//�}�E�X�̍��{�^�����グ���Ƃ�

		//�^�C�g���o�[���Ȃ��Ƃ�
		if (MyWin.win_mode == WIN_NO_TITLE)
		{
			return 0;
		}

		//�N���C�A���g�̈�O�ł��}�E�X�̓����̊Ď����I��
		ReleaseCapture();

		break;
	case WM_MOUSEMOVE:

		//�}�E�X�̍��W���擾
		MyWin.point_Mouse.y = HIWORD(lp);
		MyWin.point_Mouse.x = LOWORD(lp);

		break;

	case WM_CLOSE:
		//����{�^�����������Ƃ�

		break;
	case WM_DESTROY:
		//�E�B���h�E���j�����ꂽ(�Ȃ��Ȃ���)�Ƃ�

		///���������� �Q�[���ŗL�̐ݒ肱������ ����������

		//�t�H���g�̍폜
		MY_FONT_REMOVE(hwnd);

		///���������� �Q�[���ŗL�̐ݒ肱���܂� ����������

		//���b�Z�[�W�L���[�� WM_QUIT �𑗂�
		PostQuitMessage(0);

		return 0;
	}

	//�f�t�H���g�̃E�B���h�E�v���V�[�W���֐����Ăяo��
	return DefWindowProc(hwnd, msg, wp, lp);
}
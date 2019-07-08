//=============================================================================
//
// �|�[�Y���� [Pausemenu.cpp]
// Author : �����ʉ�
//
//=============================================================================
#include "Pause.h"
#include "input.h"
#include "fade.h"
#include "game.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PAUSEBG_TEXTURENAME			"data\\TEXTURE\\pause_frame.png"	// �ǂݍ��ރe�N�X�`���t�@�C��(�t���[��)
#define PAUSECONTINUE_TEXTURENAME	"data\\TEXTURE\\pause_100.png"		// �ǂݍ��ރe�N�X�`���t�@�C��(�R���e�j���[)
#define PAUSERETRY_TEXTURENAME		"data\\TEXTURE\\pause_101.png"		// �ǂݍ��ރe�N�X�`���t�@�C��(���g���C)
#define PAUSEQUIT_TEXTURENAME		"data\\TEXTURE\\pause_102.png"		// �ǂݍ��ރe�N�X�`���t�@�C��(�N�C�b�g)
#define PAUSEBG_POS_X				(0)									// �w�i�̍���X���W
#define PAUSEBG_POS_Y				(0)									// �w�i�̍���Y���W
#define PAUSEBG_WHIDTH				(SCREEN_WIDTH)						// �w�i�̕�
#define PAUSEBG_HEIGHT				(SCREEN_HEIGHT)						// �w�i�̍���
#define MAX_TEXTURE					(4)									// �e�N�X�`���̐�

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePause[MAX_TEXTURE] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPausebg = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
PAUSESTATE g_PauseMode;									// �|�[�Y�̏��
COLORSTATE g_PauseColor;
int g_nSelectMenu;										// �I������(0�`2)

//=============================================================================
//	���_���̐ݒ�
//=============================================================================
// ����������
void InitPausemenu(void)
{
	// ������
	g_PauseMode = PAUSESTATE_NONE;
	g_PauseColor = PAUSESTATECOLOR_NONE;

	g_nSelectMenu = 0;				// �I������(0�`2)
	LPDIRECT3DDEVICE9 pDevice;		// �f�o�C�X�ւ̃|�C���^

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		PAUSEBG_TEXTURENAME,
		&g_pTexturePause[0]);

	D3DXCreateTextureFromFile(pDevice,
		PAUSECONTINUE_TEXTURENAME,
		&g_pTexturePause[1]);

	D3DXCreateTextureFromFile(pDevice,
		PAUSERETRY_TEXTURENAME,
		&g_pTexturePause[2]);

	D3DXCreateTextureFromFile(pDevice,
		PAUSEQUIT_TEXTURENAME,
		&g_pTexturePause[3]);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPausebg,
		NULL);

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPausebg->Lock(0, 0, (void**)&pVtx, 0);

	// �t���[�� =======================================================================
	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(430.0f, 160.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(830.0f, 160.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(430.0f, 550.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(830.0f, 550.0f, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �ԁA�΁A��
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// �Â��� =======================================================================
	// ���_���W�̐ݒ�
	pVtx[4].pos = D3DXVECTOR3(475.0f, 215.0f, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(785.0f, 215.0f, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(475.0f, 275.0f, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(785.0f, 275.0f, 0.0f);

	// rhw�̐ݒ�
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �ԁA�΁A��
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���Ȃ��� ===========================================================================
	// ���_���W�̐ݒ�
	pVtx[8].pos = D3DXVECTOR3(480.0f, 315.0f, 0.0f);
	pVtx[9].pos = D3DXVECTOR3(790.0f, 315.0f, 0.0f);
	pVtx[10].pos = D3DXVECTOR3(480.0f, 375.0f, 0.0f);
	pVtx[11].pos = D3DXVECTOR3(790.0f, 375.0f, 0.0f);

	// rhw�̐ݒ�
	pVtx[8].rhw = 1.0f;
	pVtx[9].rhw = 1.0f;
	pVtx[10].rhw = 1.0f;
	pVtx[11].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �ԁA�΁A��
	pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);

	// �^�C�g���ɂ��ǂ� ===========================================================================
	// ���_���W�̐ݒ�
	pVtx[12].pos = D3DXVECTOR3(480.0f, 415.0f, 0.0f);
	pVtx[13].pos = D3DXVECTOR3(790.0f, 415.0f, 0.0f);
	pVtx[14].pos = D3DXVECTOR3(480.0f, 475.0f, 0.0f);
	pVtx[15].pos = D3DXVECTOR3(790.0f, 475.0f, 0.0f);

	// rhw�̐ݒ�
	pVtx[12].rhw = 1.0f;
	pVtx[13].rhw = 1.0f;
	pVtx[14].rhw = 1.0f;
	pVtx[15].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �ԁA�΁A��
	pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[12].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[13].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[14].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[15].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPausebg->Unlock();
}

//=============================================================================
//	�I������
//=============================================================================
void UninitPausemenu(void)
{
	for (int nCntPause = 0; nCntPause < MAX_TEXTURE; nCntPause++)
	{
		// �e�N�X�`���̔j��
		if (g_pTexturePause[nCntPause] != NULL)
		{
			g_pTexturePause[nCntPause]->Release();
			g_pTexturePause[nCntPause] = NULL;
		}
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffPausebg != NULL)
	{
		g_pVtxBuffPausebg->Release();
		g_pVtxBuffPausebg = NULL;
	}
}

//=============================================================================
//	�X�V����
//=============================================================================
void UpdatePausemenu(void)
{
	FADE g_fade = GetFade();

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	if (GetKeyboardTrigger(DIK_S) == true)	// S�L�[(��)�������ꂽ���ǂ���
	{
		PlaySound(SOUND_LABEL_SE_SELECT);

		g_nSelectMenu = (g_nSelectMenu + 1) % 3;
	}
	if (GetKeyboardTrigger(DIK_W) == true)	// W�L�[(��)�������ꂽ���ǂ���
	{
		PlaySound(SOUND_LABEL_SE_SELECT);

		 g_nSelectMenu = (g_nSelectMenu + 2) % 3;
	}

	if (g_nSelectMenu == 0)
	{// CONTINUE
		g_PauseColor = PAUSESTATECOLOR_CONTINUE;

		// ����L�[�������ꂽ���ǂ���
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			if(g_fade != FADE_OUT)
 			{
				g_PauseMode = PAUSESTATE_CONTINUE;
				PlaySound(SOUND_LABEL_SE_DECIDE);
			}
		}
	}
	if (g_nSelectMenu == 1)
	{// RETRY
		g_PauseColor = PAUSESTATECOLOR_RETRY;

		// ����L�[�������ꂽ���ǂ���
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			if (g_fade != FADE_OUT)
			{
				g_PauseMode = PAUSESTATE_RETRY;
				PlaySound(SOUND_LABEL_SE_DECIDE);
			}
		}
	}
	if (g_nSelectMenu == 2)
	{// QUIT
		g_PauseColor = PAUSESTATECOLOR_QUIT;

		// ����L�[�������ꂽ���ǂ���
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			if (g_fade != FADE_OUT)
			{
				g_PauseMode = PAUSESTATE_QUIT;
				PlaySound(SOUND_LABEL_SE_DECIDE);
			}
		}
	}

	switch (g_PauseMode)
	{
	case PAUSESTATE_NONE:
		break;

	case PAUSESTATE_CONTINUE:
		g_PauseMode = PAUSESTATE_NONE;
		SetPause(false);
		break;

	case PAUSESTATE_RETRY:
		g_PauseMode = PAUSESTATE_NONE;

		// �t�F�[�h���[�h�ݒ�
		SetFade(MODE_GAME);
		break;

	case PAUSESTATE_QUIT:
		g_PauseMode = PAUSESTATE_NONE;

		// �t�F�[�h���[�h�ݒ�
		SetFade(MODE_TITLE);
		break;
	}

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPausebg->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_PauseColor)
	{
	case PAUSESTATECOLOR_NONE:
		break;

	case PAUSESTATECOLOR_CONTINUE:
		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �ԁA�΁A��
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);	// �ԁA�΁A��
		pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);	// �ԁA�΁A��
		pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		break;

	case PAUSESTATECOLOR_RETRY:
		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);	// �ԁA�΁A��
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �ԁA�΁A��
		pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);	// �ԁA�΁A��
		pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		break;

	case PAUSESTATECOLOR_QUIT:
		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);	// �ԁA�΁A��
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);	// �ԁA�΁A��
		pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �ԁA�΁A��
		pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		break;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPausebg->Unlock();
}

//=============================================================================
//	�`�揈��
//=============================================================================
void DrawPausemenu(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPausebg, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for (int nCntPause = 0; nCntPause < MAX_TEXTURE; nCntPause++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePause[nCntPause]);

		//�|���S���̕`��
		pDevice->DrawPrimitive
		(D3DPT_TRIANGLESTRIP,
			nCntPause * 4,
			2);	// ����2�͕ς��Ȃ�
	}
}
//=============================================================================
//
// �t�F�[�h���� [fadegame.cpp]
// Author : �����ʉ�
//
//=============================================================================
#include "fadegame.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define BG_POS_X						(0)													//�w�i�̍���X���W
#define BG_POS_Y						(0)													//�w�i�̍���Y���W
#define BG_WIDTH						(SCREEN_WIDTH)							//�w�i�̕�
#define BG_HEIGHT					(SCREEN_HEIGHT)							//�w�i�̍���
#define NUM_POLYGON				(2)

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexFadeGame(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureFadeGame = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFadeGame = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
FADEGAME g_FadeGame;																			// �t�F�[�h���
GAMESTAGE g_modeGameNext;
D3DXCOLOR g_colorFadeGame;														// �t�F�[�h�F

//=============================================================================
// ����������
//=============================================================================
void InitFadeGame(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �l�̏�����
	g_FadeGame = FADEGAME_IN;													//�t�F�[�h�C�����
	g_colorFadeGame = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//������ʁi�s�����j�ɂ���

	// ���_���̐ݒ�
	MakeVertexFadeGame(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitFadeGame(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureFadeGame != NULL)
	{
		g_pTextureFadeGame->Release();
		g_pTextureFadeGame = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffFadeGame != NULL)
	{
		g_pVtxBuffFadeGame->Release();
		g_pVtxBuffFadeGame = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateFadeGame(void)
{
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	if (g_FadeGame != FADEGAME_NONE)
	{
		if (g_FadeGame == FADEGAME_IN)
		{	//�t�F�[�h�C�����
			g_colorFadeGame.a -= 0.03f;	//��ʂ𓧖��ɂ��Ă���
			if (g_colorFadeGame.a <= 0.0f)
			{
				g_colorFadeGame.a = 0.0f;
				g_FadeGame = FADEGAME_NONE;	//�������Ă��Ȃ����
			}
		}
		else if (g_FadeGame == FADEGAME_OUT)
		{	//�t�F�[�h�A�E�g���
			g_colorFadeGame.a += 0.03f;	//��ʂ�s�����ɂ��Ă���
			if (g_colorFadeGame.a >= 1.0f)
			{
				g_colorFadeGame.a = 1.0f;	
				g_FadeGame = FADEGAME_IN;	//�t�F�[�h�C�����

				//���[�h�ݒ�
				SetGameStage(g_modeGameNext);
			}
		}
			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_pVtxBuffFadeGame->Lock(0, 0, (void**)&pVtx, 0);

			//�t�F�[�h�̐F�ݒ�
			pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorFadeGame.a);
			pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorFadeGame.a);
			pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorFadeGame.a);
			pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorFadeGame.a);

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffFadeGame->Unlock();
	}
}

//=============================================================================
// �^�C�g�����
//=============================================================================
void DrawFadeGame(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffFadeGame, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureFadeGame);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 4 * NUM_POLYGON);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexFadeGame(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFadeGame,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffFadeGame->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�o�b�t�@�̏���ݒ�
	//�t�F�[�h�̍��W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, BG_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(BG_POS_X, BG_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�t�F�[�h�F�ݒ�
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFadeGame->Unlock();
}

//=============================================================================
// �t�F�[�h�̐ݒ�
//=============================================================================
void SetFadeGame(GAMESTAGE modeNext)
{
	g_FadeGame = FADEGAME_OUT;												//�t�F�[�h�A�E�g��Ԃɂ���
	g_modeGameNext = modeNext;
	g_colorFadeGame = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//������ʁi�����j�ɂ���
}

//=============================================================================
// �t�F�[�h�̎擾
//=============================================================================
FADEGAME GetFadeGame(void)
{
	return g_FadeGame;
}
//===============================================================================
//
// ���U���g��� [result.cpp]
// Author : �����ʉ�
//
//===============================================================================
#include "main.h"
#include"result.h"
#include "input.h"
#include "fade.h"
#include "game.h"
#include "sound.h"

//==============================================================================
//�}�N����`
//===============================================================================
#define RESULT_GAMECLEAR				 "data/TEXTURE/gameclear.jpg"						//�ǂݍ��ރe�N�X�`��
#define RESULT_PUSUENTER				 "data/TEXTURE/pushenter.png"						//�ǂݍ��ރe�N�X�`��
#define RESULT_GAMEOVER					 "data/TEXTURE/gameover1.jpg"						//�ǂݍ��ރe�N�X�`��
#define RESULT_GAMEOVER_LOGO		 "data/TEXTURE/gameover_logo.png"						//�ǂݍ��ރe�N�X�`��

#define MAX_TEXTURE						(4)									//�e�N�X�`���̐�
#define RESULT_POS_X						(0)									//�w�i�̍���X���W
#define RESULT_POS_Y						(0)									//�w�i�̍���Y���W
#define RESULT_WIDTH						(SCREEN_WIDTH)			//�w�i�̕�
#define RESULT_HEIGHT					(SCREEN_HEIGHT)			//�w�i�̍���

//===============================================================================
//�O���[�o���ϐ��錾
//===============================================================================
LPDIRECT3DTEXTURE9 g_pTextureResult[MAX_TEXTURE] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;					//���_�o�b�t�@�ւ̃|�C���^

//===============================================================================
//���U���g��ʏ���������
//===============================================================================
void InitResult(void)
{
	//�ϐ��錾
	VERTEX_2D * pVtx;						//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	GAMESTATE pGame;

	//�f�o�C�X���擾
	pDevice = GetDevice();
	pGame = GetGameState();

	if (pGame == GAMESTATE_CLEAR)
	{	//�Q�[���N���A
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice, RESULT_GAMECLEAR, &g_pTextureResult[0]);
		//D3DXCreateTextureFromFile(pDevice, RESULT_PUSUENTER, &g_pTextureResult[1]);
	}
	else
	{	//�Q�[���I�[�o�[
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice, RESULT_GAMEOVER, &g_pTextureResult[0]);
		//D3DXCreateTextureFromFile(pDevice, RESULT_GAMEOVER_LOGO, &g_pTextureResult[1]);
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	if (pGame == GAMESTATE_CLEAR)
	{	//�Q�[���N���A
		//�Q�[���N���A�w�i�̍��W�ݒ�
		pVtx[0].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_POS_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_POS_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_HEIGHT, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//�Q�[���N���A�w�i�̐F�ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�Q�[���N���A�w�i�̃e�N�X�`���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		////===============================================================================
		////�v�b�V���G���^�[���W�ݒ�
		//pVtx[4].pos = D3DXVECTOR3(310, 620, 0.0f);
		//pVtx[5].pos = D3DXVECTOR3(990, 620, 0.0f);
		//pVtx[6].pos = D3DXVECTOR3(310, 700, 0.0f);
		//pVtx[7].pos = D3DXVECTOR3(990, 700, 0.0f);

		////rhw�̐ݒ�
		//pVtx[4].rhw = 1.0f;
		//pVtx[5].rhw = 1.0f;
		//pVtx[6].rhw = 1.0f;
		//pVtx[7].rhw = 1.0f;

		////�v�b�V���G���^�[�F�ݒ�
		//pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		////�v�b�V���G���^�[�ݒ�
		//pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
		//pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
		//pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
		//pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

		////============================================================================
		////�v�b�V���G���^�[���S�̍��W�ݒ�
		//pVtx[8].pos = D3DXVECTOR3(690, 600, 0.0f);
		//pVtx[9].pos = D3DXVECTOR3(970, 600, 0.0f);
		//pVtx[10].pos = D3DXVECTOR3(690, 650, 0.0f);
		//pVtx[11].pos = D3DXVECTOR3(970, 650, 0.0f);

		////rhw�̐ݒ�
		//pVtx[8].rhw = 1.0f;
		//pVtx[9].rhw = 1.0f;
		//pVtx[10].rhw = 1.0f;
		//pVtx[11].rhw = 1.0f;

		////�v�b�V���G���^�[���S�̐F�ݒ�
		//pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		////�v�b�V���G���^�[���S�̐ݒ�
		//pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
		//pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
		//pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
		//pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	else
	{	//�Q�[���I�[�o�[
		//�Q�[���I�[�o�[�w�i�̍��W�ݒ�
		pVtx[0].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_POS_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_POS_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_HEIGHT, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//�Q�[���I�[�o�[�w�i�̐F�ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);

		//�Q�[���I�[�o�[�w�i�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		////============================================================================
		////�Q�[���I�[�o�[���S�̍��W�ݒ�
		//pVtx[4].pos = D3DXVECTOR3(600, 360, 0.0f);
		//pVtx[5].pos = D3DXVECTOR3(990, 360, 0.0f);
		//pVtx[6].pos = D3DXVECTOR3(600, 500, 0.0f);
		//pVtx[7].pos = D3DXVECTOR3(990, 500, 0.0f);

		////rhw�̐ݒ�
		//pVtx[4].rhw = 1.0f;
		//pVtx[5].rhw = 1.0f;
		//pVtx[6].rhw = 1.0f;
		//pVtx[7].rhw = 1.0f;

		////�Q�[���I�[�o�[���S�̐F�ݒ�
		//pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		////�Q�[���I�[�o�[���S�̐ݒ�
		//pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
		//pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
		//pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
		//pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;

		////============================================================================
		////�v�b�V���G���^�[���S�̍��W�ݒ�
		//pVtx[8].pos = D3DXVECTOR3(310, 620, 0.0f);
		//pVtx[9].pos = D3DXVECTOR3(990, 620, 0.0f);
		//pVtx[10].pos = D3DXVECTOR3(310, 700, 0.0f);
		//pVtx[11].pos = D3DXVECTOR3(990, 700, 0.0f);

		////rhw�̐ݒ�
		//pVtx[8].rhw = 1.0f;
		//pVtx[9].rhw = 1.0f;
		//pVtx[10].rhw = 1.0f;
		//pVtx[11].rhw = 1.0f;

		////�v�b�V���G���^�[���S�̐F�ݒ�
		//pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		////�v�b�V���G���^�[���S�̐ݒ�
		//pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
		//pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
		//pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
		//pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResult->Unlock();
}

//===============================================================================
//���U���g��ʏI������
//===============================================================================
void UninitResult(void)
{
	int nCntResult;

	for (nCntResult = 0; nCntResult < MAX_TEXTURE; nCntResult++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureResult[nCntResult] != NULL)
		{
			g_pTextureResult[nCntResult]->Release();
			g_pTextureResult[nCntResult] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}

//===============================================================================
//���U���g��ʍX�V����
//===============================================================================
void UpdateResult(void)
{
	//�ϐ��錾
	FADE g_fade;

	//�|�C���^�̎擾
	g_fade = GetFade();

	//����L�[�������ꂽ���ǂ���
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (g_fade != FADE_OUT)
		{	//�t�F�[�h�A�E�g����Enter�L�[�������Ȃ�����
			//���[�h�ݒ�
			SetFade(MODE_TITLE);
			PlaySound(SOUND_LABEL_SE_DECIDE);
		}
	}
}

//===============================================================================
//���U���g��ʕ`�揈��
//===============================================================================
void DrawResult(void)
{
	int nCntResult;
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X���擾����
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntResult = 0; nCntResult < MAX_TEXTURE; nCntResult++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureResult[nCntResult]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntResult, 2);
	}
}
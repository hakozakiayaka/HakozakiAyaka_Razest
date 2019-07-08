//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : �����ʉ�
//
//=============================================================================
#include "score.h"
#include "game.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	TEXTURE_SCORE		"data/TEXTURE/number000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	DUGIT_NUMBER	(8)														//����

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureScore = NULL;				// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
int g_nScore;																				// �X�R�A
int g_aScoreData[DUGIT_NUMBER];											//��

//=============================================================================
// ����������
//=============================================================================
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntScore;

	// �X�R�A�̏�����
	 g_nScore = 0;

	 //�X�R�A�̌��A����������
	 for (nCntScore = 0; nCntScore < DUGIT_NUMBER; nCntScore++)
	 {
		 g_aScoreData[nCntScore] = 0;
	 }

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
								TEXTURE_SCORE,		// �t�@�C���̖��O
								&g_pTextureScore);		// �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	MakeVertexScore(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitScore(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateScore(void)
{
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^
	int nCntScore;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < DUGIT_NUMBER; nCntScore++)
	{
		//�e�N�X�`���̍��W�ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (g_aScoreData[nCntScore] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (g_aScoreData[nCntScore] * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (g_aScoreData[nCntScore] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f +(g_aScoreData[nCntScore] * 0.1f), 1.0f);

		//�X�R�A�̐F�ݒ�
		pVtx[0].col = D3DXCOLOR(0.7f, 0.0f, 0.0f, 0.8f);
		pVtx[1].col = D3DXCOLOR(0.7f, 0.0f, 0.0f, 0.8f);
		pVtx[2].col = D3DXCOLOR(0.7f, 0.0f, 0.0f, 0.8f);
		pVtx[3].col = D3DXCOLOR(0.7f, 0.0f, 0.0f, 0.8f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntScore;

	//�X�e�[�W���擾
	GAMESTAGE pStage;
	pStage = GetGameStage();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureScore);

	// �|���S���̕`��
	for (nCntScore = 0; nCntScore < DUGIT_NUMBER; nCntScore++)
	{
		if (pStage == GAMESTAGE1 || pStage == GAMESTAGE2)
		{	//���ɂ���X�e�[�W1�ƃs�[�}���X�e�[�W2�̎��ɃX�R�A��\������
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntScore, 2);
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^
	int nCntScore;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * DUGIT_NUMBER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	//�X�R�A�̍��W�ݒ�
	for (nCntScore = 0; nCntScore < DUGIT_NUMBER; nCntScore++)
	{
		pVtx[0].pos = D3DXVECTOR3(870.0f + (50.0f * nCntScore), 5.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(920.0f + (50.0f * nCntScore), 5.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(870.0f + (50.0f * nCntScore), 60.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(920.0f + (50.0f * nCntScore), 60.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
	
		//�|���S���̐F�ݒ�
		pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

		//�e�N�X�`���̍��W�ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}

//=============================================================================
// �X�R�A�̉��Z
//=============================================================================
void AddScore(int nValue)
{
	int nNum = 100000000;
	int nNum1 = 10000000;
	int nCntScore;

	g_nScore += nValue;

	for (nCntScore = 0; nCntScore < DUGIT_NUMBER; nCntScore++)
	{
		g_aScoreData[nCntScore] = g_nScore %  nNum / nNum1;
		nNum = nNum / 10;
		nNum1 = nNum1 / 10;
	}
}
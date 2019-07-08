//=============================================================================
//
// �����L���O���� [ranking.cpp]
// Author : �����ʉ�
//
//=============================================================================
#include "ranking.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	TEXTURE_RANKSCORE		"data/TEXTURE/number000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	DUGIT_NUMBER	(8)	//����
//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexRankScore(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureRankScore = NULL;				// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankScore = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
int g_nRankScore;																				// �����L���O
//int g_aRankScoreData[8];																	//��

//=============================================================================
// ����������
//=============================================================================
void InitRankScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �����L���O�̏�����
	 g_nRankScore = 0;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
								TEXTURE_RANKSCORE,			// �t�@�C���̖��O
								&g_pTextureRankScore);		// �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	MakeVertexRankScore(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitRankScore(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureRankScore != NULL)
	{
		g_pTextureRankScore->Release();
		g_pTextureRankScore = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffRankScore != NULL)
	{
		g_pVtxBuffRankScore->Release();
		g_pVtxBuffRankScore = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateRankScore(void)
{
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^
	int nCntRankScore;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntRankScore = 0; nCntRankScore < DUGIT_NUMBER; nCntRankScore++)
	{
		//�e�N�X�`���̍��W�ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (g_nRankScore * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (g_nRankScore * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (g_nRankScore * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (g_nRankScore * 0.1f), 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRankScore->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawRankScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntRankScore;

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, g_pVtxBuffRankScore, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRankScore);

	// �|���S���̕`��
	for (nCntRankScore = 0; nCntRankScore < DUGIT_NUMBER; nCntRankScore++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntRankScore, 2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexRankScore(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^
	int nCntRankScore;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * DUGIT_NUMBER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankScore,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	//�����L���O�̍��W�ݒ�
	for (nCntRankScore = 0; nCntRankScore < DUGIT_NUMBER; nCntRankScore++)
	{
		pVtx[0].pos = D3DXVECTOR3(870.0f + (50.0f * nCntRankScore), 5.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(920.0f + (50.0f * nCntRankScore), 5.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(870.0f + (50.0f * nCntRankScore), 75.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(920.0f + (50.0f * nCntRankScore), 75.0f, 0.0f);

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
	g_pVtxBuffRankScore->Unlock();
}

//=============================================================================
// �����L���O�̐ݒ�
//=============================================================================
void SetRankScore(int nScore)
{
	if (nScore > g_nRankScore)
	{
		g_nRankScore = nScore;
	}
}
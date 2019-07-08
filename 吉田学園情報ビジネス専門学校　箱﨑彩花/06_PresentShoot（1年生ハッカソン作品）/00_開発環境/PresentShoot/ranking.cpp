//=============================================================================
//
// �����L���O���� [ranking.cpp]
// Author : 
//
//=============================================================================
#include "ranking.h"
#include "flontpolygon.h"
#include "score.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_HIGHSCORE		"data/TEXTURE/number001.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define NUM_HIGHSCORE			(8)								//�X�R�A�̌���
#define MOVE_POS				(80.0f)							//�ړ���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexHighScore(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureHighScore = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHighScore = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
int						g_nHighScore;					// �X�R�A
int						g_nScore2;
int						g_aHighNum[NUM_HIGHSCORE];			// �P���ɐ������i�[����ϐ�

//=============================================================================
// ����������
//=============================================================================
void InitHighScore(void)
{
	//�ϐ��錾
	int nCntNum;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �X�R�A�̏�����
	g_nHighScore = 0;
	g_nScore2 = 0;

	for (nCntNum = 0; nCntNum < NUM_HIGHSCORE; nCntNum++)
	{
		g_aHighNum[nCntNum] = 0;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_HIGHSCORE,		// �t�@�C���̖��O
		&g_pTextureHighScore);	// �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	MakeVertexHighScore(pDevice);

	//�^�C�g�����S�̃Z�b�g
	SetFlontPolygon(4, D3DXVECTOR3(640.0f, 200.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 400.0f, 100.0f);
}

//=============================================================================
// �I������
//=============================================================================
void UninitHighScore(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureHighScore != NULL)
	{
		g_pTextureHighScore->Release();
		g_pTextureHighScore = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pTextureHighScore != NULL)
	{
		g_pTextureHighScore->Release();
		g_pTextureHighScore = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateHighScore(void)
{
	//�ϐ��錾
	int nCntHighScore;

	// ���_����ݒ�
	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffHighScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntHighScore = 0; nCntHighScore < NUM_HIGHSCORE; nCntHighScore++)
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * g_aHighNum[nCntHighScore]), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * g_aHighNum[nCntHighScore]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * g_aHighNum[nCntHighScore]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * g_aHighNum[nCntHighScore]), 1.0f);

		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffHighScore->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawHighScore(void)
{
	//�ϐ��錾
	int nCntHighScore;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffHighScore, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureHighScore);

	// �|���S���̕`��
	for (nCntHighScore = 0; nCntHighScore < NUM_HIGHSCORE; nCntHighScore++)
	{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCntHighScore * 4,
			2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexHighScore(LPDIRECT3DDEVICE9 pDevice)
{
	//�ϐ��錾
	int nCntHighScore;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_HIGHSCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffHighScore,
		NULL);

	// ���_����ݒ�
	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

							//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffHighScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntHighScore = 0; nCntHighScore < NUM_HIGHSCORE; nCntHighScore++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(300.0f + 0.0f + (MOVE_POS * nCntHighScore), 300.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(300.0f + MOVE_POS + (MOVE_POS * nCntHighScore), 300.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(300.0f + 0.0f + (MOVE_POS * nCntHighScore), 200.0f + 300.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(300.0f + MOVE_POS + (MOVE_POS * nCntHighScore), 200.0f + 300.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(0.1f, 0.0f, 0.4f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.1f, 0.0f, 0.4f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.1f, 0.0f, 0.4f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.1f, 0.0f, 0.4f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffHighScore->Unlock();
}

//=============================================================================
// �X�R�A�̉��Z
//=============================================================================
void SetHighScore(int nScore)
{
	int nCntNum;			//�X�R�A�̌����̃J�E���^�[
 	int nNum = 100000000;
	int nNum2 = 10000000;
	g_nScore2 = nScore;

	if (g_nHighScore < g_nScore2)
	{
		g_nHighScore = g_nScore2;
	}

	for (nCntNum = 0; nCntNum < NUM_HIGHSCORE; nCntNum++)
	{
		g_aHighNum[nCntNum] = (g_nHighScore % nNum) / nNum2;	//�i�[���鐔�����v�Z

														//�������P�����炷
		nNum = nNum / 10;
		nNum2 = nNum2 / 10;

		if (nCntNum == NUM_HIGHSCORE - 1)
		{//����������
			nNum = 100000000;
			nNum2 = 10000000;
		}
	}
}
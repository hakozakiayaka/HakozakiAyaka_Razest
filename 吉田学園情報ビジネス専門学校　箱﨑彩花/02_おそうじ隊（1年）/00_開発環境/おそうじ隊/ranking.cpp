//===============================================================================
//
// �����L���O��� [ranking.cpp]
// Author : �����ʉ�
//
//===============================================================================
#include "main.h"
#include "fade.h"
#include "input.h"
#include "score.h"
#include "ranking.h"
#include "BG.h"
#include "sound.h"

//==============================================================================
//�}�N����`
//===============================================================================
#define RANKING_TEX		"data/TEXTURE/number001.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define MAX_TEX								(2)
#define RANKING_POS_X					(0)									//�����L���O�̍���X���W
#define RANKING_POS_Y					(0)									//�����L���O�̍���Y���W
#define RANKING_WIDTH					(SCREEN_WIDTH)			//�����L���O�̕�
#define RANKING_HEIGHT					(SCREEN_HEIGHT)			//�����L���O�̍���
#define DUGIT_NUMBER					(8)									//�X�R�A�̌���

//===============================================================================
//�O���[�o���ϐ��錾
//===============================================================================
LPDIRECT3DTEXTURE9 g_pTextureRanking = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;	//���_�o�b�t�@�ւ̃|�C���^
int g_nRanking;																			//�Q�[���̃X�R�A�������p���ϐ�
int g_nHighScore[5];																	//�ŏ��ɓ����Ă���X�R�A[���i���邩]
int g_aRankingData[5][DUGIT_NUMBER];								//�����L���O[���i���邩] [����]
int g_nChange;																			//�\�[�g�̉��u��
int g_nBoss;																					//�\�[�g�̉��u��
bool g_nKeep = true;																	//�����L���O��ۑ�����
int g_nCntTimeRanking;																//�����L���O��ʂ���^�C�g����ʂւ̐؂�ւ��J�E���^�[

//===============================================================================
//�����L���O��ʏ���������
//===============================================================================
void InitRanking(void)
{
	//�ϐ��錾
	VERTEX_2D * pVtx;							//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//�f�o�C�X�ւ̃|�C���^

	//�X�R�A�̌��A�\���̂̏�����
	for (int nCntRanking2 = 0; nCntRanking2 < 5; nCntRanking2++)
	{
		for (int nCntRanking = 0; nCntRanking < DUGIT_NUMBER; nCntRanking++)
		{
			g_aRankingData[nCntRanking2][nCntRanking] = 0;
		}
	}

	//�����X�R�A�̏�����
	if (g_nKeep == true)
	{
		g_nHighScore[0] = 50000;
		g_nHighScore[1] = 40000;
		g_nHighScore[2] = 30000;
		g_nHighScore[3] = 20000;
		g_nHighScore[4] = 10000;
		g_nKeep = false;
	}

	//�\�[�g�̉��u���̏�����
	g_nChange = 0;
	g_nBoss = 0;

	//��ʐ؂�ւ��̃J�E���^�[
	g_nCntTimeRanking = 0;

	//�����L���O��ʂɃn�C�X�R�A��ݒ�
	SetRanking(GetScore());

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, RANKING_TEX, &g_pTextureRanking);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 5 * DUGIT_NUMBER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRanking,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntRanking2 = 0; nCntRanking2 < 5; nCntRanking2++)
	{	//�c�ɕ��ׂ�
		for (int nCntRanking = 0; nCntRanking < DUGIT_NUMBER; nCntRanking++)
		{	//����
			//	 ���_����ݒ�
			pVtx[0].pos = D3DXVECTOR3(450.0f + (50.0f * nCntRanking), 200.0f + (100.0f * nCntRanking2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(500.0f + (50.0f * nCntRanking), 200.0f + (100.0f * nCntRanking2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(450.0f + (50.0f * nCntRanking), 270.0f + (100.0f * nCntRanking2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(500.0f + (50.0f * nCntRanking), 270.0f + (100.0f * nCntRanking2), 0.0f);

			//rhw�̐ݒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//	�|���S���̐F�ݒ�
			pVtx[0].col = D3DXCOLOR(0.5f, 0.7f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.5f, 0.7f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.5f, 0.7f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.5f, 0.7f, 1.0f, 1.0f);

			//	�e�N�X�`���̍��W�ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

			pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRanking->Unlock();

	//�w�i�̏���������
	InitBG();
	SetBG(0);

	//����Q�[���̃X�R�A���X�V
	InitScore();
}

//===============================================================================
//�����L���O��ʏI������
//===============================================================================
void UninitRanking(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureRanking != NULL)
	{
		g_pTextureRanking->Release();
		g_pTextureRanking = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}

	//�w�i�̏I������
	UninitBG();

	//����Q�[���̃X�R�A���X�V
	UninitScore();
}

//===============================================================================
//�����L���O��ʍX�V����
//===============================================================================
void UpdateRanking(void)
{
	//�t�F�[�h���擾
	FADE g_fade = GetFade();

	//��ʐ؂�ւ��J�E���^�[
	g_nCntTimeRanking++;

	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^
	int nCntRanking;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntRanking2 = 0; nCntRanking2 < 5; nCntRanking2++)
	{
		for (nCntRanking = 0; nCntRanking < DUGIT_NUMBER; nCntRanking++)
		{
			//	�e�N�X�`���̍��W�ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f + (g_aRankingData[nCntRanking2][nCntRanking] * 0.1f), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (g_aRankingData[nCntRanking2][nCntRanking] * 0.1f), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (g_aRankingData[nCntRanking2][nCntRanking] * 0.1f), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (g_aRankingData[nCntRanking2][nCntRanking] * 0.1f), 1.0f);

			pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRanking->Unlock();

	//����L�[�������ꂽ���ǂ���
	if (GetKeyboardTrigger(DIK_RETURN) == true || g_nCntTimeRanking % 300 == 0)
	{
		PlaySound(SOUND_LABEL_SE_DECIDE);
		if (g_fade != FADE_OUT)
		{	//�t�F�[�h�A�E�g����Enter�L�[�������Ȃ�����
			//���[�h�ݒ�
			SetFade(MODE_TITLE);
		}
	}
	//�w�i�̍X�V����
	UpdateBG();

	//����Q�[���̃X�R�A���X�V
	UpdateScore();
}

//===============================================================================
//�����L���O��ʕ`�揈��
//===============================================================================
void DrawRanking(void)
{
	//�w�i�̕`�揈��
	DrawBG();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//�f�o�C�X�ւ̃|�C���^
	int nCntRanking;

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRanking);

	for (nCntRanking = 0; nCntRanking < DUGIT_NUMBER * 5; nCntRanking++)
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntRanking, 2);
	}
}

//=============================================================================
 //�����L���O�̐ݒ�
//=============================================================================
void SetRanking(int nScore)
{
	//int nCntRanking;
	int nNum = 100000000;
	int nNum1 = 10000000;

	//�n�C�X�R�A�ƌ��݂̃X�R�A���ׂ�
	for (int nCntRanking2 = 0; nCntRanking2 < 5; nCntRanking2++)
	{
		if (nScore > g_nHighScore[nCntRanking2])
		{
			g_nChange = g_nHighScore[nCntRanking2];		//�O��̃n�C�X�R�A�����u��
			g_nHighScore[nCntRanking2] = nScore;			//���u���̃n�C�X�R�A�Ɣ�ׂāA����̃n�C�X�R�A����

			//���ʂ̓���ւ�
			for (int nCntJuni = nCntRanking2 + 1; nCntJuni < 5; nCntJuni++)
			{
				g_nBoss = g_nHighScore[nCntJuni];				//�������������ʂ́A���̏��ʂ����u��
				g_nHighScore[nCntJuni] = g_nChange;			//�󂢂��Ƃ���ɁA1��̏��ʂ���
				g_nChange = g_nBoss;									//�I���
			}
			break;
		}
	}

	//�����L���O��ʂ̃X�R�A�X�V
	for (int nCntRanking2 = 0; nCntRanking2 < 5; nCntRanking2++)
	{
		for (int nCntRanking = 0; nCntRanking < DUGIT_NUMBER; nCntRanking++)
		{
			g_aRankingData[nCntRanking2][nCntRanking] = (g_nHighScore[nCntRanking2] %  nNum) / nNum1;
			nNum = nNum / 10;
			nNum1 = nNum1 / 10;

			if (nCntRanking == DUGIT_NUMBER - 1)
			{	//�i���ς�����珉��������
				nNum = 100000000;
				nNum1 = 10000000;
			}
		}
	}

	//����Q�[���̃X�R�A�̕`����X�V
	DrawScore();
}
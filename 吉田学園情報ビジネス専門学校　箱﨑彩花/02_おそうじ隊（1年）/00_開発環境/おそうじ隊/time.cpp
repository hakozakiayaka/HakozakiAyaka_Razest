//=============================================================================
//
// �^�C���̏��� [time.cpp]
// Author : �����ʉ�
//
//=============================================================================
#include "time.h"
#include "game.h"
#include "score.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEXTURE_TIME		"data/TEXTURE/number001.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define MAX_TIME				(2)					//����
#define TIMERIMIT				(60 * 40)			//��������

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureTime = NULL;				// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
int g_nTime;																					// �X�R�A
int g_aTimeData[MAX_TIME];													//��
TIMESTATE g_TimeState = TIMESTATE_NONE;						//�^�C���̏�Ԃ̊Ǘ�

//=============================================================================
// ����������
//=============================================================================
void InitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntTime;

	// �^�C���̏�����
	 g_nTime = TIMERIMIT;
	 g_TimeState = TIMESTATE_NORMAL;

	 //�^�C���̌��A����������
	 for (nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	 {
		 g_aTimeData[nCntTime] = 0;
	 }

	 AddTime();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
								TEXTURE_TIME,			// �t�@�C���̖��O
								&g_pTextureTime);		// �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	MakeVertexTime(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitTime(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTime(void)
{
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^
	int nCntTime;
	int nScore = GetScore();

	switch (g_TimeState)
	{
		case TIMESTATE_NORMAL:
			break;

		case TIMESTATE_CLEAR:
			g_nTime = 0;
			SetGameState(GAMESTATE_CLEAR);
			break;

		case TIMESTATE_OVER:
			g_nTime = 0;
			SetGameState(GAMESTATE_OVER);
			break;
	}

	if (g_TimeState == TIMESTATE_NORMAL)
	{
		g_nTime--;

		if ((g_nTime % 60) == 0)
		{
			AddTime();
		}
		if (g_nTime == 0)
		{
			if (nScore >= 4000)
			{	//40000�ȏゾ������Q�[���N���A
				SetGameState(GAMESTATE_CLEAR);
			}
			else if (nScore <= 3000)
			{	//30000�ȉ���������Q�[���I�[�o�[
				SetGameState(GAMESTATE_OVER);
			}
		}

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

		for (nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
		{
			//�e�N�X�`���̍��W�ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f + (g_aTimeData[nCntTime] * 0.1f), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (g_aTimeData[nCntTime] * 0.1f), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (g_aTimeData[nCntTime] * 0.1f), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (g_aTimeData[nCntTime] * 0.1f), 1.0f);

			pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
		}

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffTime->Unlock();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTime(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntTime;

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTime);

	// �|���S���̕`��
	for (nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntTime, 2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^
	int nCntTime;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIME,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	//�^�C���̍��W�ݒ�
	for (nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		pVtx[0].pos = D3DXVECTOR3(560.0f + (45.0f * nCntTime), 5.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(610.0f + (45.0f * nCntTime), 5.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(560.0f + (45.0f * nCntTime), 65.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(610.0f + (45.0f * nCntTime), 65.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//�^�C���̐F�ݒ�
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
	g_pVtxBuffTime->Unlock();
}

//=============================================================================
// �^�C���̉��Z
//=============================================================================
void AddTime(void)
{
	int nNum = 100;
	int nNum1 = 10;
	int nCntTime;
	int nTime;

	nTime = g_nTime / 60;	//1�t���[���̌v�Z

	for (nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		g_aTimeData[nCntTime] = (nTime %  nNum) / nNum1;
		nNum = nNum / 10;
		nNum1 = nNum1 / 10;
	}
}
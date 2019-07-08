//=============================================================================
//
// �X�R�A���� [Life.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "Life.h"
#include "Player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_LIFE		"data/TEXTURE/life.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureLife = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
int g_nLife;									   // �_���[�W�J�E���^�[
bool g_bUse[PLAYER_LIFE];

//=============================================================================
// ����������
//=============================================================================
void InitLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCnt;

	// �X�R�A�̏�����
	g_nLife = 0;

	for (nCnt = 0; nCnt < PLAYER_LIFE; nCnt++)
	{
		g_bUse[nCnt] = true;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_LIFE,		// �t�@�C���̖��O
		&g_pTextureLife);	// �e�N�X�`���ւ̃|�C���^

							// ���_���̍쐬
	MakeVertexLife(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitLife(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureLife != NULL)
	{
		g_pTextureLife->Release();
		g_pTextureLife = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffLife != NULL)
	{
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateLife(void)
{
	int nCnt;
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

					//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < PLAYER_LIFE; nCnt++)
	{
		if (g_bUse[nCnt] == true)
		{
			// ���_����ݒ�	
			pVtx[0].pos = D3DXVECTOR3(0.0f + (50.0f * (PLAYER_LIFE - nCnt - 1)), 0.0f, 0.0f);//��ڂ̒��_�̏ꏊ�w��
			pVtx[1].pos = D3DXVECTOR3(50.0f + (50.0f * (PLAYER_LIFE - nCnt - 1)), 0.0f, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
			pVtx[2].pos = D3DXVECTOR3(0.0f + (50.0f * (PLAYER_LIFE - nCnt - 1)), 50.0f, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
			pVtx[3].pos = D3DXVECTOR3(50.0f + (50.0f * (PLAYER_LIFE - nCnt - 1)), 50.0f, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
		}
		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffLife->Unlock();

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCnt;

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCnt = 0; nCnt <= PLAYER_LIFE; nCnt++)
	{
		if (g_bUse[nCnt] == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureLife);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCnt * 4,
				2);
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice)
{
	int nCnt;
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

					// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * PLAYER_LIFE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL);

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < PLAYER_LIFE; nCnt++)
	{
		// ���_����ݒ�	
		pVtx[0].pos = D3DXVECTOR3(0.0f + (50 * nCnt), 0.0f, 0.0f);//��ڂ̒��_�̏ꏊ�w��
		pVtx[1].pos = D3DXVECTOR3(50.0f + (50 * nCnt), 0.0f, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[2].pos = D3DXVECTOR3(0.0f + (50 * nCnt), 50.0f, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[3].pos = D3DXVECTOR3(50.0f + (50 * nCnt), 50.0f, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�F
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j


		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffLife->Unlock();

}

//=============================================================================
// ���C�t�̐ݒ�
//=============================================================================
void SetLife(int nLifeDown)
{
	int nLostLife = 0;
	int nCnt;

	nLostLife = PLAYER_LIFE - nLifeDown;

	for (nCnt = 0; nCnt < nLostLife; nCnt++)
	{
		if (g_bUse[nCnt] == true)
		{
			g_bUse[nCnt] = false;
		}
	}

}

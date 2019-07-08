//=============================================================================
//
// ���C�t���� [life.cpp]
// Author : �����ʉ�
//
//=============================================================================
#include "life.h"
#include "player.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEXTURE_LIFE		"data/TEXTURE/life001.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureLife = NULL;				// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
int g_nLife;																				//���C�t
bool g_bUse[MAXPLAYER_LIFE];

//=============================================================================
// ����������
//=============================================================================
void InitLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntLife;

	//���C�t�̏�����
	 g_nLife = 0;

	 //���C�t���g���Ă��邩�ǂ���
	 for (nCntLife = 0; nCntLife < MAXPLAYER_LIFE; nCntLife++)
	 {
		 g_bUse[nCntLife] = true;
	 }

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
								TEXTURE_LIFE,			// �t�@�C���̖��O
								&g_pTextureLife);		// �e�N�X�`���ւ̃|�C���^

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
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^
	int nCntLife;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntLife = 0; nCntLife < MAXPLAYER_LIFE; nCntLife++)
	{
		if (g_bUse[nCntLife] == true)
		{
			//�e�N�X�`���̍��W�ݒ�
			pVtx[0].pos = D3DXVECTOR3(0.0f + (60.0f * (MAXPLAYER_LIFE - nCntLife - 1)), 5.0f , 0.0f);
			pVtx[1].pos = D3DXVECTOR3(50.0f + (60.0f * (MAXPLAYER_LIFE - nCntLife - 1)), 5.0f , 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f + (60.0f * (MAXPLAYER_LIFE - nCntLife - 1)), 55.0f , 0.0f);
			pVtx[3].pos = D3DXVECTOR3(50.0f + (60.0f * (MAXPLAYER_LIFE - nCntLife - 1)), 55.0f , 0.0f);
		}
		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLife->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntLife;

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	
	// �|���S���̕`��
	for (nCntLife = 0; nCntLife < MAXPLAYER_LIFE; nCntLife++)
	{
		if (g_bUse[nCntLife] == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureLife);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntLife, 2);
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^
	int nCntLife;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAXPLAYER_LIFE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	//���C�t�e�N�X�`���̍��W�ݒ�
	for (nCntLife = 0; nCntLife < MAXPLAYER_LIFE; nCntLife++)
	{
		pVtx[0].pos = D3DXVECTOR3(0.0f + (40 * nCntLife), 200.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(60.0f + (40 * nCntLife), 200.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f + (40 * nCntLife), 250.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(60.0f + (40 * nCntLife), 250.0f, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLife->Unlock();
}

//=============================================================================
// ���C�t�̐ݒ�
//=============================================================================
void SetLife(int nLifeDown)
{
	int nCntLife;
	int nLostLife = 0;

	nLostLife = MAXPLAYER_LIFE - nLifeDown;

	for (nCntLife = 0; nCntLife < nLostLife; nCntLife++)
	{
		if (g_bUse[nCntLife] == true)
		{
			g_bUse[nCntLife] = false;
		}
	}
}
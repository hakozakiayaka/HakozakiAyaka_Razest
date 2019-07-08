//=============================================================================
//
// �w�i���� [bg.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "main.h"
#include "bg.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define STARBG_TEXTUER "data\\TEXTURE\\star.png" //�ǂݍ��ރe�N�X�`��
#define BG_POS_X (0)					   //�w�i����X
#define BG_POS_Y (0)					   //�w�i����Y
#define BG_WIDTH (SCREEN_WIDTH)			   //�w�i�̕�
#define BG_HEIGHT (SCREEN_HEIGHT)		   //�w�i����
#define MOVE_STAR (0.0005f)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureStarBG= NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStarBG = NULL;
int g_nCntBG = 0;

//=============================================================================
// �|���S������������[InitPolygon]
//=============================================================================
void InitStarBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, STARBG_TEXTUER, &g_pTextureStarBG);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffStarBG, NULL);

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffStarBG->Lock(0, 0, (void**)&pVtx, 0);

	//�w�i�̍��W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);//��ڂ̒��_�̏ꏊ�w��
	pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, BG_POS_Y, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[2].pos = D3DXVECTOR3(BG_POS_X, BG_HEIGHT, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[3].pos = D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�w�i�F�ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j

	//�w�i�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffStarBG->Unlock();

}
//=============================================================================
//�|���S���I������ [UninitPolygon]
//=============================================================================
void UninitStarBG(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureStarBG != NULL)
	{
		g_pTextureStarBG->Release();
		g_pTextureStarBG = NULL;
	}


	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffStarBG != NULL)
	{
		g_pVtxBuffStarBG->Release();
		g_pVtxBuffStarBG = NULL;
	}

}

//=============================================================================
// �|���S���X�V����[UpdataPolygon]
//=============================================================================
void UpdateStarBG(void)
{
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^
	g_nCntBG++;

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffStarBG->Lock(0, 0, (void**)&pVtx, 0);

		//�w�i�̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f + (g_nCntBG*(MOVE_STAR + 1)), 0.0f );//��ڂ̒��_�̏ꏊ�w��
	pVtx[1].tex = D3DXVECTOR2(1.0f + (g_nCntBG*(MOVE_STAR + 1)), 0.0f );//��ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[2].tex = D3DXVECTOR2(0.0f + (g_nCntBG*(MOVE_STAR + 1)), 1.0f );//�O�ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[3].tex = D3DXVECTOR2(1.0f + (g_nCntBG*(MOVE_STAR + 1)), 1.0f );//�O�ڂ̒��_�̏ꏊ�w��i�E���j

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffStarBG->Unlock();

}
//=============================================================================
// �|���S���`�ʏ���[DrawPolygon]
//=============================================================================
void DrawStarBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X���擾����
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffStarBG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureStarBG);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0, 
		2);
}

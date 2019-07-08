//=============================================================================
//
// �|���S������ [flontpolygon.cpp]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#include "flontpolygon.h"
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_TEX	(5)				//�ǂ݂��ރe�N�X�`���̍ő吔
#define MAX_POLYGON	(10)		//�w�i�̍ő吔

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureFlontPolygon[MAX_TEX] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFlontPolygon = NULL;		//���_�o�b�t�@�ւ̃|�C���^
FlontPolygon					g_FlontPolygon[MAX_POLYGON];				//���ݒ�

//=============================================================================
// �X�^�[�g�{�^������������
//=============================================================================
void InitFlontPolygon(void)
{
	//�ϐ��錾
	char	FlontPolygonName[MAX_TEX][48];		//�t�@�C�������i�[����
	int		nCntTex;
	int     nCntFlontPolygon;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��̏�����
	for (nCntFlontPolygon = 0; nCntFlontPolygon < MAX_POLYGON; nCntFlontPolygon++)
	{
		g_FlontPolygon[nCntFlontPolygon].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���S���W
		g_FlontPolygon[nCntFlontPolygon].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//�F
		g_FlontPolygon[nCntFlontPolygon].fHight = 0.0f;								//����
		g_FlontPolygon[nCntFlontPolygon].fWidth = 0.0f;								//��
		g_FlontPolygon[nCntFlontPolygon].nTexNum = 0;				//�e�N�X�`���̔ԍ�
		g_FlontPolygon[nCntFlontPolygon].bUse = false;				//�g�p���Ă��Ȃ���Ԃɂ���
	}

	//�e�N�X�`���t�@�C�������i�[����
	wsprintf(&FlontPolygonName[0][0], "data\\TEXTURE\\title_logo.png");		//�^�C�g�����S
	wsprintf(&FlontPolygonName[1][0], "data\\TEXTURE\\flam002.png");			//�|�[�Y�䎆
	wsprintf(&FlontPolygonName[2][0], "data\\TEXTURE\\GAMECLEAR.png");		//�^�C�g�����S
	wsprintf(&FlontPolygonName[3][0], "data\\TEXTURE\\GAMEOVER.png");			//�|�[�Y�䎆
	wsprintf(&FlontPolygonName[4][0], "data\\TEXTURE\\score_logo.png");			//�|�[�Y�䎆


	//�e�N�X�`���̓ǂݍ���
	for (nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		D3DXCreateTextureFromFile(pDevice,
								  &FlontPolygonName[nCntTex][0],
								  &g_pTextureFlontPolygon[nCntTex]);
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&g_pVtxBuffFlontPolygon,
								NULL);

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffFlontPolygon->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTex = 0; nCntTex < MAX_POLYGON; nCntTex++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFlontPolygon->Unlock();
}

//=============================================================================
// �^�C�g���I������
//=============================================================================
void UninitFlontPolygon(void)
{
	//�ϐ��錾
	int nCntTex;

	//�e�N�X�`���̔j��
	for (nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		if (g_pTextureFlontPolygon[nCntTex] != NULL)
		{
			g_pTextureFlontPolygon[nCntTex]->Release();
			g_pTextureFlontPolygon[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffFlontPolygon != NULL)
	{
		g_pVtxBuffFlontPolygon->Release();
		g_pVtxBuffFlontPolygon = NULL;
	}
}

//=============================================================================
// �^�C�g���X�V����
//=============================================================================
void UpdateFlontPolygon(void)
{
}

//=============================================================================
// �^�C�g���`�揈��
//=============================================================================
void DrawFlontPolygon(void)
{
	//�ϐ��錾
	int nCntFlontPolygon;

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffFlontPolygon, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntFlontPolygon = 0; nCntFlontPolygon < MAX_POLYGON; nCntFlontPolygon++)
	{
		if (g_FlontPolygon[nCntFlontPolygon].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureFlontPolygon[g_FlontPolygon[nCntFlontPolygon].nTexNum]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
								   nCntFlontPolygon * 4,			//�J�n���钸�_�̃C���f�b�N�X
								   2);						//�v���~�e�B�u�̐�
		}
	}
}

//=============================================================================
// ���ݒ�
//=============================================================================
void SetFlontPolygon(int nTexNum, D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHight)
{
	//�ϐ��錾
	int nCntFlontPolygon;
	float fHalfWidth = 0;		//��
	float fHalfHight = 0;		//����

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffFlontPolygon->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntFlontPolygon = 0; nCntFlontPolygon < MAX_POLYGON; nCntFlontPolygon++)
	{
		if (g_FlontPolygon[nCntFlontPolygon].bUse == false)
		{
			g_FlontPolygon[nCntFlontPolygon].pos = pos;				//���S���W
			g_FlontPolygon[nCntFlontPolygon].fHight = fHight;			//����
			g_FlontPolygon[nCntFlontPolygon].fWidth = fWidth;			//��
			g_FlontPolygon[nCntFlontPolygon].col = col;				//�F

			//���ƍ�����ݒ肷��
			fHalfWidth = g_FlontPolygon[nCntFlontPolygon].fWidth * 0.5f;
			fHalfHight = g_FlontPolygon[nCntFlontPolygon].fHight * 0.5f;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(pos.x - fHalfWidth, pos.y - fHalfHight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pos.x + fHalfWidth, pos.y - fHalfHight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pos.x - fHalfWidth, pos.y + fHalfHight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pos.x + fHalfWidth, pos.y + fHalfHight, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);

			g_FlontPolygon[nCntFlontPolygon].nTexNum = nTexNum;		//�e�N�X�`���̔ԍ�
			g_FlontPolygon[nCntFlontPolygon].bUse = true;			//�g�p���Ă����Ԃɂ���
			break;
		}

		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFlontPolygon->Unlock();
}

//=============================================================================
// �w�i������
//=============================================================================
void DeleteFlontPolygon()
{
	//�ϐ��錾
	int nCntFlontPolygon;

	for (nCntFlontPolygon = 0; nCntFlontPolygon < MAX_POLYGON; nCntFlontPolygon++)
	{
		if (g_FlontPolygon[nCntFlontPolygon].bUse == true)
		{
			g_FlontPolygon[nCntFlontPolygon].bUse = false;		//�g�p���Ă��Ȃ���Ԃɂ���
		}
	}
}
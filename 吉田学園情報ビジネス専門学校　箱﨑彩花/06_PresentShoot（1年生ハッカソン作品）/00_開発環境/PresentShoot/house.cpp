//=============================================================================
//
// �n�E�X���� [house.cpp]
// Author : ����ʉ�
//
//=============================================================================
#include "house.h"
#include "main.h"
#include "game.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_TEX	(5)				//�ǂ݂��ރe�N�X�`���̍ő吔
#define MAX_HOUSE	(100)		//�w�i�̍ő吔

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureHouse[MAX_TEX] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHouse = NULL;		//���_�o�b�t�@�ւ̃|�C���^
House					g_House[MAX_HOUSE];				//���ݒ�
int						g_Move;							//�ړ�������
int						g_HouseNum;						//�n�E�X�̔ԍ�

//=============================================================================
// �X�^�[�g�{�^������������
//=============================================================================
void InitHouse(void)
{
	//�ϐ��錾
	char	HouseName[MAX_TEX][48];		//�t�@�C�������i�[����
	int		nCntTex;
	int     nCntHouse;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��̏�����
	for (nCntHouse = 0; nCntHouse < MAX_HOUSE; nCntHouse++)
	{
		g_House[nCntHouse].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���S���W
		g_House[nCntHouse].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//�F
		g_House[nCntHouse].fHight = 0.0f;								//����
		g_House[nCntHouse].fWidth = 0.0f;								//��
		g_House[nCntHouse].nTexNum = 0;									//�e�N�X�`���̔ԍ�
		g_House[nCntHouse].Num = 0;										//�ԍ�
		g_House[nCntHouse].fHalfWidth = 0.0f;
		g_House[nCntHouse].fHalfHeght = 0.0f;
		g_House[nCntHouse].bUse = false;				//�g�p���Ă��Ȃ���Ԃɂ���
	}
	g_Move = 0;		//�ړ���
	g_HouseNum = 0;	//�Ƃ̔ԍ�

	//�e�N�X�`���t�@�C�������i�[����
	wsprintf(&HouseName[0][0], "data\\TEXTURE\\house000.png");			//�n�E�X0
	wsprintf(&HouseName[1][0], "data\\TEXTURE\\house001.png");			//�n�E�X1
	wsprintf(&HouseName[2][0], "data\\TEXTURE\\house002.png");			//�n�E�X2
	wsprintf(&HouseName[3][0], "data\\TEXTURE\\house003.png");			//�n�E�X3
	wsprintf(&HouseName[4][0], "data\\TEXTURE\\tree.png");					//��

	//�e�N�X�`���̓ǂݍ���
	for (nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		D3DXCreateTextureFromFile(pDevice,
								  &HouseName[nCntTex][0],
								  &g_pTextureHouse[nCntTex]);
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_HOUSE,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&g_pVtxBuffHouse,
								NULL);

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffHouse->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTex = 0; nCntTex < MAX_HOUSE; nCntTex++)
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
	g_pVtxBuffHouse->Unlock();
}

//=============================================================================
// �^�C�g���I������
//=============================================================================
void UninitHouse(void)
{
	//�ϐ��錾
	int nCntTex;

	//�e�N�X�`���̔j��
	for (nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		if (g_pTextureHouse[nCntTex] != NULL)
		{
			g_pTextureHouse[nCntTex]->Release();
			g_pTextureHouse[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffHouse != NULL)
	{
		g_pVtxBuffHouse->Release();
		g_pVtxBuffHouse = NULL;
	}
}

//=============================================================================
// �^�C�g���X�V����
//=============================================================================
void UpdateHouse(void)
{
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^
	int nCntHouse;
	float fScroll = -3.0f;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffHouse->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntHouse = 0; nCntHouse < MAX_HOUSE; nCntHouse++)
	{
		if (g_House[nCntHouse].bUse == true)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_House[nCntHouse].pos.x - g_House[nCntHouse].fHalfWidth, g_House[nCntHouse].pos.y - g_House[nCntHouse].fHalfHeght, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_House[nCntHouse].pos.x + g_House[nCntHouse].fHalfWidth, g_House[nCntHouse].pos.y - g_House[nCntHouse].fHalfHeght, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_House[nCntHouse].pos.x - g_House[nCntHouse].fHalfWidth, g_House[nCntHouse].pos.y + g_House[nCntHouse].fHalfHeght, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_House[nCntHouse].pos.x + g_House[nCntHouse].fHalfWidth, g_House[nCntHouse].pos.y + g_House[nCntHouse].fHalfHeght, 0.0f);

			//�ʒu�X�V
			g_House[nCntHouse].pos.x += fScroll;

			if (g_House[nCntHouse].Num == 28)
			{
				if (g_House[nCntHouse].pos.x == 500.0f)
				{
					SetGameState(GAMESTATE_END_CLIA);
				}
			}
		}

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffHouse->Unlock();
}

//=============================================================================
// �^�C�g���`�揈��
//=============================================================================
void DrawHouse(void)
{
	//�ϐ��錾
	int nCntHouse;

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffHouse, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntHouse = 0; nCntHouse < MAX_HOUSE; nCntHouse++)
	{
		if (g_House[nCntHouse].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureHouse[g_House[nCntHouse].nTexNum]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
								   nCntHouse * 4,			//�J�n���钸�_�̃C���f�b�N�X
								   2);								//�v���~�e�B�u�̐�
		}
	}
}

//=============================================================================
// ���ݒ�
//=============================================================================
void SetHouse(int nTexNum, D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHight)
{
	//�ϐ��錾
	int nCntHouse;

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffHouse->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntHouse = 0; nCntHouse < MAX_HOUSE; nCntHouse++)
	{
		if (g_House[nCntHouse].bUse == false)
		{
			//�J�E���^�[�����Z
			g_HouseNum++;

			//�Ƃɔԍ��t��
			g_House[nCntHouse].Num = g_HouseNum;

			g_House[nCntHouse].pos = pos;				//���S���W
			g_House[nCntHouse].fHight = fHight;		//����
			g_House[nCntHouse].fWidth = fWidth;		//��
			g_House[nCntHouse].col = col;					//�F

			//���ƍ�����ݒ肷��
			g_House[nCntHouse].fHalfWidth = g_House[nCntHouse].fWidth * 0.5f;
			g_House[nCntHouse].fHalfHeght = g_House[nCntHouse].fHight * 0.5f;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(pos.x - g_House[nCntHouse].fHalfWidth, pos.y - g_House[nCntHouse].fHalfHeght, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pos.x + g_House[nCntHouse].fHalfWidth, pos.y - g_House[nCntHouse].fHalfHeght, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pos.x - g_House[nCntHouse].fHalfWidth, pos.y + g_House[nCntHouse].fHalfHeght, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pos.x + g_House[nCntHouse].fHalfWidth, pos.y + g_House[nCntHouse].fHalfHeght, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);

			g_House[nCntHouse].nTexNum = nTexNum;		//�e�N�X�`���̔ԍ�
			g_House[nCntHouse].bUse = true;					//�g�p���Ă����Ԃɂ���
			break;
		}

		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffHouse->Unlock();
}

//=============================================================================
// �w�i������
//=============================================================================
void DeleteHouse()
{
	//�ϐ��錾
	int nCntHouse;

	for (nCntHouse = 0; nCntHouse < MAX_HOUSE; nCntHouse++)
	{
		if (g_House[nCntHouse].bUse == true)
		{
			g_House[nCntHouse].bUse = false;		//�g�p���Ă��Ȃ���Ԃɂ���
		}
	}
}
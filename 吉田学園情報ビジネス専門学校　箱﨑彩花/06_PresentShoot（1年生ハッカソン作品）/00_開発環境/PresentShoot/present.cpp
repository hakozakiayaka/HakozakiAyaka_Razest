//=============================================================================
//
// �v���[���g�̏��� [present.cpp]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#include "present.h"
#include "main.h"
#include "chimney.h"
#include "score.h"
#include "effect.h"
#include "sound.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_TEX			(4)			//�ǂ݂��ރe�N�X�`���̍ő吔
#define MAX_PRESENT		(100)		//�w�i�̍ő吔
#define PRESENTSIE_L	(33)		//�v���[���g��L�T�C�Y
#define PRESENTSIE_M	(25)		//�v���[���g��M�T�C�Y
#define PRESENTSIE_S	(20)		//�v���[���g��S�T�C�Y
#define GRAVITY			(0.3f)		//�d��
	
//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTexturePresent[MAX_TEX] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPresent = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Present					g_Present[MAX_PRESENT];				//���ݒ�

//=============================================================================
// �X�^�[�g�{�^������������
//=============================================================================
void InitPresent(void)
{
	//�ϐ��錾
	char	PresentName[MAX_TEX][48];		//�t�@�C�������i�[����
	int		nCntTex;
	int     nCntPresent;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��̏�����
	for (nCntPresent = 0; nCntPresent < MAX_PRESENT; nCntPresent++)
	{
		g_Present[nCntPresent].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���S���W
		g_Present[nCntPresent].OldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�O��̈ʒu
		g_Present[nCntPresent].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
		g_Present[nCntPresent].nTexNum = 0;									//�e�N�X�`���̔ԍ�
		g_Present[nCntPresent].fGravity = 0.0f;								//�d��
		g_Present[nCntPresent].Type = PRESENTTYPE_MAX;						//�v���[���g�̎��
		g_Present[nCntPresent].bUse = false;								//�g�p���Ă��Ȃ���Ԃɂ���
	}

	//�e�N�X�`���t�@�C�������i�[����
	wsprintf(&PresentName[0][0], "data\\TEXTURE\\present_bag.png");		//��
	wsprintf(&PresentName[1][0], "data\\TEXTURE\\present_L.png");		//L�T�C�Y
	wsprintf(&PresentName[2][0], "data\\TEXTURE\\present_M.png");		//M�T�C�Y
	wsprintf(&PresentName[3][0], "data\\TEXTURE\\present_S.png");		//S�T�C�Y

	//�e�N�X�`���̓ǂݍ���
	for (nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		D3DXCreateTextureFromFile(pDevice,
								  &PresentName[nCntTex][0],
								  &g_pTexturePresent[nCntTex]);
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PRESENT,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&g_pVtxBuffPresent,
								NULL);

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPresent->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTex = 0; nCntTex < MAX_PRESENT; nCntTex++)
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
	g_pVtxBuffPresent->Unlock();
}

//=============================================================================
// �^�C�g���I������
//=============================================================================
void UninitPresent(void)
{
	//�ϐ��錾
	int nCntTex;

	//�e�N�X�`���̔j��
	for (nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		if (g_pTexturePresent[nCntTex] != NULL)
		{
			g_pTexturePresent[nCntTex]->Release();
			g_pTexturePresent[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPresent != NULL)
	{
		g_pVtxBuffPresent->Release();
		g_pVtxBuffPresent = NULL;
	}
}

//=============================================================================
// �^�C�g���X�V����
//=============================================================================
void UpdatePresent(void)
{
	//�ϐ��錾
	int nCntPresent;

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPresent->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPresent = 0; nCntPresent < MAX_PRESENT; nCntPresent++)
	{
		if (g_Present[nCntPresent].bUse == true)
		{
			//�O��̈ʒu��ۑ�����
			g_Present[nCntPresent].OldPos = g_Present[nCntPresent].pos;

			//�d�͉��Z
			g_Present[nCntPresent].fGravity += GRAVITY;
			g_Present[nCntPresent].move.y = g_Present[nCntPresent].fGravity;

			//�ʒu�X�V
			g_Present[nCntPresent].pos.y += g_Present[nCntPresent].move.y;

			//�����蔻��
			if (g_Present[nCntPresent].Type == PRESENTTYPE_BAG)
			{
				if (CollisionChimney(&g_Present[nCntPresent].pos, &g_Present[nCntPresent].OldPos, PRESENTSIE_M, PRESENTSIE_M) == true)
				{//�v���[���g������
					DeletePresent(nCntPresent, g_Present[nCntPresent].Type);
				}
			}
			else if (g_Present[nCntPresent].Type == PRESENTTYPE_L)
			{
				if (CollisionChimney(&g_Present[nCntPresent].pos, &g_Present[nCntPresent].OldPos, PRESENTSIE_L, PRESENTSIE_L) == true)
				{//�v���[���g������
					DeletePresent(nCntPresent, g_Present[nCntPresent].Type);
				}
			}
			else if (g_Present[nCntPresent].Type == PRESENTTYPE_M)
			{
				if (CollisionChimney(&g_Present[nCntPresent].pos, &g_Present[nCntPresent].OldPos, PRESENTSIE_M, PRESENTSIE_M) == true)
				{//�v���[���g������
					DeletePresent(nCntPresent, g_Present[nCntPresent].Type);
				}
			}
			else if (g_Present[nCntPresent].Type == PRESENTTYPE_S)
			{
				if (CollisionChimney(&g_Present[nCntPresent].pos, &g_Present[nCntPresent].OldPos, PRESENTSIE_S, PRESENTSIE_S) == true)
				{//�v���[���g������
					DeletePresent(nCntPresent, g_Present[nCntPresent].Type);
				}
			}

			//��ʊO�ɏo����
			if (g_Present[nCntPresent].pos.y > SCREEN_HEIGHT + 100)
			{
				g_Present[nCntPresent].bUse = false;
			}
			
			if (g_Present[nCntPresent].nTexNum == 1)
			{
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_Present[nCntPresent].pos.x - PRESENTSIE_L, g_Present[nCntPresent].pos.y - PRESENTSIE_L, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_Present[nCntPresent].pos.x + PRESENTSIE_L, g_Present[nCntPresent].pos.y - PRESENTSIE_L, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_Present[nCntPresent].pos.x - PRESENTSIE_L, g_Present[nCntPresent].pos.y + PRESENTSIE_L, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_Present[nCntPresent].pos.x + PRESENTSIE_L, g_Present[nCntPresent].pos.y + PRESENTSIE_L, 0.0f);
			}
			else if (g_Present[nCntPresent].nTexNum == 3)
			{
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_Present[nCntPresent].pos.x - PRESENTSIE_S, g_Present[nCntPresent].pos.y - PRESENTSIE_S, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_Present[nCntPresent].pos.x + PRESENTSIE_S, g_Present[nCntPresent].pos.y - PRESENTSIE_S, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_Present[nCntPresent].pos.x - PRESENTSIE_S, g_Present[nCntPresent].pos.y + PRESENTSIE_S, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_Present[nCntPresent].pos.x + PRESENTSIE_S, g_Present[nCntPresent].pos.y + PRESENTSIE_S, 0.0f);
			}
			else
			{
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_Present[nCntPresent].pos.x - PRESENTSIE_M, g_Present[nCntPresent].pos.y - PRESENTSIE_M, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_Present[nCntPresent].pos.x + PRESENTSIE_M, g_Present[nCntPresent].pos.y - PRESENTSIE_M, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_Present[nCntPresent].pos.x - PRESENTSIE_M, g_Present[nCntPresent].pos.y + PRESENTSIE_M, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_Present[nCntPresent].pos.x + PRESENTSIE_M, g_Present[nCntPresent].pos.y + PRESENTSIE_M, 0.0f);
			}
		}

		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPresent->Unlock();
}

//=============================================================================
// �^�C�g���`�揈��
//=============================================================================
void DrawPresent(void)
{
	//�ϐ��錾
	int nCntPresent;

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPresent, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntPresent = 0; nCntPresent < MAX_PRESENT; nCntPresent++)
	{
		if (g_Present[nCntPresent].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTexturePresent[g_Present[nCntPresent].nTexNum]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
								   nCntPresent * 4,			//�J�n���钸�_�̃C���f�b�N�X
								   2);						//�v���~�e�B�u�̐�
		}
	}
}

//=============================================================================
// ���ݒ�
//=============================================================================
void SetPresent(int nTexNum, D3DXVECTOR3 pos)
{
	//�ϐ��錾
	int nCntPresent;
	
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPresent->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPresent = 0; nCntPresent < MAX_PRESENT; nCntPresent++)
	{
		if (g_Present[nCntPresent].bUse == false)
		{
			g_Present[nCntPresent].pos = pos;				//���S���W
			g_Present[nCntPresent].nTexNum = nTexNum;		//�e�N�X�`���̔ԍ�

			if (g_Present[nCntPresent].nTexNum == 0)
			{
				//�^�C�v�̐ݒ�
				g_Present[nCntPresent].Type = PRESENTTYPE_BAG;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(pos.x - PRESENTSIE_M, pos.y - PRESENTSIE_M, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(pos.x + PRESENTSIE_M, pos.y - PRESENTSIE_M, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pos.x - PRESENTSIE_M, pos.y + PRESENTSIE_M, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pos.x + PRESENTSIE_M, pos.y + PRESENTSIE_M, 0.0f);
			}
			else if (g_Present[nCntPresent].nTexNum == 1)
			{
				//�^�C�v�̐ݒ�
				g_Present[nCntPresent].Type = PRESENTTYPE_L;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(pos.x - PRESENTSIE_L, pos.y - PRESENTSIE_L, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(pos.x + PRESENTSIE_L, pos.y - PRESENTSIE_L, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pos.x - PRESENTSIE_L, pos.y + PRESENTSIE_L, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pos.x + PRESENTSIE_L, pos.y + PRESENTSIE_L, 0.0f);
			}
			else if (g_Present[nCntPresent].nTexNum == 2)
			{
				//�^�C�v�̐ݒ�
				g_Present[nCntPresent].Type = PRESENTTYPE_M;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(pos.x - PRESENTSIE_M, pos.y - PRESENTSIE_M, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(pos.x + PRESENTSIE_M, pos.y - PRESENTSIE_M, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pos.x - PRESENTSIE_M, pos.y + PRESENTSIE_M, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pos.x + PRESENTSIE_M, pos.y + PRESENTSIE_M, 0.0f);
			}
			else if (g_Present[nCntPresent].nTexNum == 3)
			{
				//�^�C�v�̐ݒ�
				g_Present[nCntPresent].Type = PRESENTTYPE_S;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(pos.x - PRESENTSIE_S, pos.y - PRESENTSIE_S, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(pos.x + PRESENTSIE_S, pos.y - PRESENTSIE_S, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pos.x - PRESENTSIE_S, pos.y + PRESENTSIE_S, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pos.x + PRESENTSIE_S, pos.y + PRESENTSIE_S, 0.0f);
			}
			
			g_Present[nCntPresent].fGravity = 0.0f;		//�d��
			g_Present[nCntPresent].bUse = true;			//�g�p���Ă����Ԃɂ���
			break;
		}

		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPresent->Unlock();
}

//=============================================================================
// ���ݒ�
//=============================================================================
void DeletePresent(int nCntPresent, PRESENTTYPE type)
{
	if (g_Present[nCntPresent].bUse == true)
	{
		PlaySound(SOUND_LABEL_SE_ITEM);

		if (type == PRESENTTYPE_BAG)
		{
			AddScore(250);
		}
		else if (type == PRESENTTYPE_L)
		{
			AddScore(500);
		}
		else if (type == PRESENTTYPE_M)
		{
			AddScore(200);
		}
		else if (type == PRESENTTYPE_S)
		{
			AddScore(100);
		}

		g_Present[nCntPresent].bUse = false;
		SetEffect(g_Present[nCntPresent].pos, D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f), 5.0f, 1);
		SetEffect(g_Present[nCntPresent].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 5.0f, 1);
		SetEffect(g_Present[nCntPresent].pos, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), 5.0f, 1);
		SetEffect(g_Present[nCntPresent].pos, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 5.0f, 1);
		SetEffect(g_Present[nCntPresent].pos, D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f), 5.0f, 1);
		SetEffect(g_Present[nCntPresent].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 5.0f, 1);
		SetEffect(g_Present[nCntPresent].pos, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), 5.0f, 1);
		SetEffect(g_Present[nCntPresent].pos, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 5.0f, 1);
		SetEffect(g_Present[nCntPresent].pos, D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f), 5.0f, 1);
		SetEffect(g_Present[nCntPresent].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 5.0f, 1);
		SetEffect(g_Present[nCntPresent].pos, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), 5.0f, 1);
		SetEffect(g_Present[nCntPresent].pos, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 5.0f, 1);
	}
}
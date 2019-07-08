//=============================================================================
//
// ���˂̏��� [chimney.cpp]
// Author : ��������
//
//=============================================================================
#include "chimney.h"
#include "main.h"
#include "sound.h"
#include "player.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	MAX_CHIMNEY		(120)							//�u���b�N�̍ő吔
#define CHIMNEY_IMAGE	"data\\TEXTURE\\chimney.png"	//�u���b�N�̃e�N�X�`��

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureChimney = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffChimney = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
Chimney					g_aChimney[MAX_CHIMNEY];		// �u���b�N�̏��
int						g_nCntItemChimney;			// �A�C�e���u���b�N�J�E���^�[

//=============================================================================
// ����������
//=============================================================================
void InitChimney(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	int nCntChimney;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �u���b�N�̏��̏�����
	for(nCntChimney = 0; nCntChimney < MAX_CHIMNEY; nCntChimney++)
	{
		g_aChimney[nCntChimney].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
		g_aChimney[nCntChimney].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ���
		g_aChimney[nCntChimney].fWidth = 0.0f;							//��
		g_aChimney[nCntChimney].fHight = 0.0f;							//����
		g_aChimney[nCntChimney].nCounterMove = 0;						//�ړ��ʂ̃J�E���^�[
		g_aChimney[nCntChimney].bIn = false;							//���˂ɓ����Ă��邩�ǂ���
		g_aChimney[nCntChimney].bUse = false;							//�u���b�N���g�p���Ă��邩�ǂ���
	}
	g_nCntItemChimney = 0;											//�A�C�e���u���b�N�J�E���^�[

	D3DXCreateTextureFromFile(pDevice,
							  CHIMNEY_IMAGE,
							  &g_pTextureChimney);

	// ���_���̍쐬
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_CHIMNEY,
						 D3DUSAGE_WRITEONLY,
						 FVF_VERTEX_2D,
						 D3DPOOL_MANAGED,
						 &g_pVtxBuffChimney,
						 NULL);

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffChimney->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntChimney = 0; nCntChimney < MAX_CHIMNEY; nCntChimney++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);

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

		pVtx += 4;		//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffChimney->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitChimney(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureChimney != NULL)
	{
		g_pTextureChimney->Release();
		g_pTextureChimney = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffChimney != NULL)
	{
		g_pVtxBuffChimney->Release();
		g_pVtxBuffChimney = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateChimney(void)
{
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^
	int nCntChimney;
	float fScroll = -3.0f;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffChimney->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntChimney = 0; nCntChimney < MAX_CHIMNEY; nCntChimney++)
	{
		if (g_aChimney[nCntChimney].bUse == true)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aChimney[nCntChimney].pos.x - g_aChimney[nCntChimney].fWidth, g_aChimney[nCntChimney].pos.y - g_aChimney[nCntChimney].fHight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aChimney[nCntChimney].pos.x + g_aChimney[nCntChimney].fWidth, g_aChimney[nCntChimney].pos.y - g_aChimney[nCntChimney].fHight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aChimney[nCntChimney].pos.x - g_aChimney[nCntChimney].fWidth, g_aChimney[nCntChimney].pos.y + g_aChimney[nCntChimney].fHight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aChimney[nCntChimney].pos.x + g_aChimney[nCntChimney].fWidth, g_aChimney[nCntChimney].pos.y + g_aChimney[nCntChimney].fHight, 0.0f);

			//�ʒu�X�V
			g_aChimney[nCntChimney].pos.x += fScroll;
		}

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffChimney->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawChimney(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	int nCntChimney;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffChimney, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for(nCntChimney = 0; nCntChimney < MAX_CHIMNEY; nCntChimney++)
	{
		if (g_aChimney[nCntChimney].bUse == true)		//�u���b�N���g�p����Ă���
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureChimney);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
								   nCntChimney * 4,
								   2);
		}
	}
}

//=============================================================================
// �u���b�N�̐ݒ菈��
//=============================================================================
void SetChimney(D3DXVECTOR3 pos, float fWidth, float fHight)
{
	//�ϐ��錾
	int nCntChimney;
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffChimney->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntChimney = 0; nCntChimney < MAX_CHIMNEY; nCntChimney++)
	{
		if (g_aChimney[nCntChimney].bUse == false)		//�u���b�N���g�p����ĂȂ�
		{
			g_aChimney[nCntChimney].pos = pos;			//���W
			g_aChimney[nCntChimney].fWidth = fWidth;	//��
			g_aChimney[nCntChimney].fHight = fHight;	//����

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(pos.x - fWidth, pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pos.x + fWidth, pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pos.x - fWidth, pos.y + fHight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pos.x + fWidth, pos.y + fHight, 0.0f);

			g_aChimney[nCntChimney].bUse = true;				//�g�p���Ă����Ԃɂ���
			break;
		}

		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffChimney->Unlock();
}

//=============================================================================
// �u���b�N�̓����蔻��
//=============================================================================
bool CollisionChimney(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, float fWhidth, float fHeight)
{
	bool bLand = false;		//���n���Ă��邩�ǂ���
	int nCntChimney;

	for (nCntChimney = 0; nCntChimney < MAX_CHIMNEY; nCntChimney++)
	{
		if (g_aChimney[nCntChimney].bUse == true)
		{
			g_aChimney[nCntChimney].bIn = false;	//���n���Ă��Ȃ���Ԃɂ���

			if (pPos->x > g_aChimney[nCntChimney].pos.x - g_aChimney[nCntChimney].fWidth&&
				pPos->x < g_aChimney[nCntChimney].pos.x + g_aChimney[nCntChimney].fWidth)
			{//�v���C���[���u���b�N�̕��ɓ����Ă��邩�ǂ���

				//��̔���
				if (pPosOld->y <= g_aChimney[nCntChimney].pos.y && pPos->y >= g_aChimney[nCntChimney].pos.y)
				{//�O��̈ʒu���n�ʂ���ɂ���

					bLand = true;								//���n������Ԃɂ���
					g_aChimney[nCntChimney].bIn = true;			//���n������Ԃɂ���
				}

			}
		}
	}
	return bLand;
}

//=============================================================================
// �u���b�N���̎擾
//=============================================================================
Chimney *GetChimney(void)
{
	return &g_aChimney[0];
}
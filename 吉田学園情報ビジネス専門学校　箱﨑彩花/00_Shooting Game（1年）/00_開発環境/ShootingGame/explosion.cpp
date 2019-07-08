//=============================================================================
//
// �����̏��� [explosion.cpp]
// Author : �����ʉ�
//
//=============================================================================
#include "bullet.h"
#include "input.h"
#include"main.h"
#include"player.h"
#include"explosion.h"
#include "sound.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	MAX_EXPLOSION		(128)											// �����̍ő吔 
#define EXPLOSION_SPEED		(4)												//�����̑���
#define TEXTURE_NAME "data/TEXTURE/explosion000.png"		//�e�N�X�`���̖��O

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXCOLOR col;				//�F
	int nCounterAnim;			//�A�j���[�V�����J�E���^�[
	int nPatternAnim;			//�A�j���[�V����No.
	bool bUse;						//�g�p���Ă��邩�ǂ���
} Explosion;

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureExplosion = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
Explosion g_aExplosion[MAX_EXPLOSION];									//�����̏��

//=============================================================================
// �����̏���������
//=============================================================================
void InitExplosion(void)
{
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �����̏��̏�����
	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		g_aExplosion[nCntExplosion].nCounterAnim = 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
		g_aExplosion[nCntExplosion].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_pTextureExplosion);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//�|���S���̍��W�ݒ�
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);

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
	g_pVtxBuffExplosion->Unlock();
}

//=============================================================================
// �����̏I������
//=============================================================================
void UninitExplosion(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//=============================================================================
// �����̍X�V����
//=============================================================================
void UpdateExplosion(void)
{
	int nCntExplosion;
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{	//�e���g�p����Ă���
			//�J�E���^�[���Z
			g_aExplosion[nCntExplosion].nCounterAnim++;	

			if ((g_aExplosion[nCntExplosion].nCounterAnim % EXPLOSION_SPEED) == 0)
			{	//�����̑���
				g_aExplosion[nCntExplosion].nPatternAnim ++;		//�p�^�[��No.�X�V
			}

			//�����̍��W�ݒ�
			pVtx[nCntExplosion * 4].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x -10, g_aExplosion[nCntExplosion].pos.y -10, 0.0f);
			pVtx[nCntExplosion * 4 + 1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 50, g_aExplosion[nCntExplosion].pos.y - 10, 0.0f);
			pVtx[nCntExplosion * 4 + 2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 10, g_aExplosion[nCntExplosion].pos.y + 50, 0.0f);
			pVtx[nCntExplosion * 4 + 3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 50, g_aExplosion[nCntExplosion].pos.y + 50, 0.0f);

			//�e�N�X�`���̍��W�ݒ�
			pVtx[nCntExplosion * 4].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim  * 0.125f) + 0.0f, 0.0f);
			pVtx[nCntExplosion * 4 + 1].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.125f) + 0.125f, 0.0f);
			pVtx[nCntExplosion * 4 + 2].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.125f) + 0.0f, 1.0f);
			pVtx[nCntExplosion * 4 + 3].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim *0.125f) + 0.125f, 1.0f);

			if (g_aExplosion[nCntExplosion].pos.y + 30 < 0 || g_aExplosion[nCntExplosion] .nPatternAnim > 7)
			{
				g_aExplosion[nCntExplosion].bUse = false;	//�g�p���Ă��Ȃ���Ԃɂ���
			}
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffExplosion->Unlock();
}

//=============================================================================
// �����̕`�揈��
//=============================================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureExplosion);

	// �|���S���̕`��
	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntExplosion,  2);
		}
	}
}

//=============================================================================
// �����̐ݒ菈��
//=============================================================================
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	int nCntExplosion;
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{
			//�����̍��W�ݒ�
			g_aExplosion[nCntExplosion].pos = pos;
			pVtx[nCntExplosion * 4].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 10, g_aExplosion[nCntExplosion].pos.y - 10, 0.0f);
			pVtx[nCntExplosion * 4 + 1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 50, g_aExplosion[nCntExplosion].pos.y - 10, 0.0f);
			pVtx[nCntExplosion * 4 + 2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 10, g_aExplosion[nCntExplosion].pos.y + 50, 0.0f);
			pVtx[nCntExplosion * 4 + 3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 50, g_aExplosion[nCntExplosion].pos.y + 50, 0.0f);

			//�����̐F�ݒ�
			g_aExplosion[nCntExplosion].col = col;
			pVtx[nCntExplosion * 4].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[nCntExplosion * 4 + 1].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[nCntExplosion * 4 + 2].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[nCntExplosion * 4 + 3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);

			g_aExplosion[nCntExplosion].nCounterAnim = 0;

			//�e�N�X�`���̍��W�ݒ�
			g_aExplosion[nCntExplosion].nPatternAnim = 0;
			pVtx[nCntExplosion * 4].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[nCntExplosion * 4 + 1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[nCntExplosion * 4 + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[nCntExplosion * 4 + 3].tex = D3DXVECTOR2(1.0f, 1.0f);

			g_aExplosion[nCntExplosion].bUse = true;	//�g�p���Ă����Ԃɂ���
			break;																//�K���K�v
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffExplosion->Unlock();
}
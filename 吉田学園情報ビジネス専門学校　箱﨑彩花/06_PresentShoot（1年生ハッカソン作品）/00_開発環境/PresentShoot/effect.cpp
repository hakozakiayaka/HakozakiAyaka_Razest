//=============================================================================
//
// �G�t�F�N�g�̏��� [effect.cpp]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#include "effect.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_EFFECT00	"data/TEXTURE/effect000.jpg"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_EFFECT01	"data/TEXTURE/star000.jpg"		// �ǂ݂��ރe�N�X�`���t�@�C����
#define MAX_TEXTURE			(2)								// �e�N�X�`���̍ő吔
#define	MAX_EFFECT			(4096)							// �G�t�F�N�g�̍ő吔
#define EFFECT_LIFE			(150)							// �\������
#define EFFECT_LIFE2		(20)							// �\������ 
#define EFFECT_MOVE			(-1.5f)							// �ړ���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureEffect[MAX_TEXTURE] = {};		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
EFFECT					g_aEffect[MAX_EFFECT];		// �G�t�F�N�g�̏��

//=============================================================================
// ����������
//=============================================================================
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for(int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEffect[nCntEffect].fRadius = 0.0f;
		g_aEffect[nCntEffect].fChngeRadius = 0.0f;
		g_aEffect[nCntEffect].fRadiusCnt = 0.0f;
		g_aEffect[nCntEffect].fAngle = 0.0f;
		g_aEffect[nCntEffect].nLife = 0;
		g_aEffect[nCntEffect].nTexType = 0;
		g_aEffect[nCntEffect].fGravity = 0.0f;
		g_aEffect[nCntEffect].bAngle = false;
		g_aEffect[nCntEffect].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
							  TEXTURE_EFFECT00,
							  &g_pTextureEffect[0]);

	D3DXCreateTextureFromFile(pDevice,
							 TEXTURE_EFFECT01,
							 &g_pTextureEffect[1]);

	// ���_���̍쐬
	MakeVertexEffect(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitEffect(void)
{
	//�ϐ��錾
	int nCntTex;

	//�e�N�X�`���̔j��
	for (nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		if (g_pTextureEffect[nCntTex] != NULL)
		{
			g_pTextureEffect[nCntTex]->Release();
			g_pTextureEffect[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEffect(void)
{
	//�ϐ��錾
	int nCntEffect;

	// ���_�o�b�t�@�̏���ݒ�
	VERTEX_2D*pVtx;					//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)		//�G�t�F�N�g���g�p����Ă���
		{
			//���C�t�̃J�E���g�_�E��
			g_aEffect[nCntEffect].nLife--;

			//���a��傫������
			g_aEffect[nCntEffect].fRadius += 0.3f;

			//�G�t�F�N�g����������
			if (g_aEffect[nCntEffect].nLife <= 0)
			{
				g_aEffect[nCntEffect].col.a -= 0.1f;

				if (g_aEffect[nCntEffect].col.a <= 0.0f)
				{
					g_aEffect[nCntEffect].bUse = false;
				}
			}

			//�v���C���[�̏����擾
			Player * pPlayer;
			pPlayer = GetPlayer();

			//�ړ�����
			g_aEffect[nCntEffect].move.x = 2.0f;

			if (g_aEffect[nCntEffect].bAngle == false)
			{
				//�p�x�����������Ԃɐݒ�
				g_aEffect[nCntEffect].bAngle = true;

				//�ړ����W�����߂�
				g_aEffect[nCntEffect].fAngle = atan2f(rand() % 100, rand() % 100);

				g_aEffect[nCntEffect].move.x = sinf(g_aEffect[nCntEffect].fAngle) * 3.0f;
				g_aEffect[nCntEffect].move.y = cosf(g_aEffect[nCntEffect].fAngle) * -3.0f;
			}

			//�ʒu�̍X�V
			if (pPlayer->nDirectionMove == 0)
			{
				g_aEffect[nCntEffect].pos.x -= g_aEffect[nCntEffect].move.x;
				g_aEffect[nCntEffect].pos.y += g_aEffect[nCntEffect].move.y;

				//�ړ�����
				g_aEffect[nCntEffect].move.x = -1.5f;
			}
			else if (pPlayer->nDirectionMove == 1)
			{
				g_aEffect[nCntEffect].pos.x += g_aEffect[nCntEffect].move.x;
				g_aEffect[nCntEffect].pos.y += g_aEffect[nCntEffect].move.y;

				//�ړ�����
				g_aEffect[nCntEffect].move.x = 1.5f;
			}

			//�ʒu���X�V
			g_aEffect[nCntEffect].pos.x += g_aEffect[nCntEffect].move.x;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].col.g, g_aEffect[nCntEffect].col.b, g_aEffect[nCntEffect].col.a);
			pVtx[1].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].col.g, g_aEffect[nCntEffect].col.b, g_aEffect[nCntEffect].col.a);
			pVtx[2].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].col.g, g_aEffect[nCntEffect].col.b, g_aEffect[nCntEffect].col.a);
			pVtx[3].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].col.g, g_aEffect[nCntEffect].col.b, g_aEffect[nCntEffect].col.a);
		}

		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEffect(void)
{
	//�ϐ��錾
	int nCntEffect;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �|���S���̕`��
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)		//�G�t�F�N�g���g�p����Ă���
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureEffect[g_aEffect[nCntEffect].nTexType]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntEffect * 4,
				2);
		}
	}

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice)
{
	//�ϐ��錾
	int nCntEffect;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	// ���_�o�b�t�@�̏���ݒ�
	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0);
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0);
		pVtx[2].pos = D3DXVECTOR3(0, 0, 0);
		pVtx[3].pos = D3DXVECTOR3(0, 0, 0);

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
	g_pVtxBuffEffect->Unlock();
}


//=============================================================================
// �G�t�F�N�g�ݒ�
//=============================================================================
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int TexType)
{
	//�ϐ��錾
	int nCntEffect;
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == false)		//�G�t�F�N�g���g�p����ĂȂ�
		{
			g_aEffect[nCntEffect].pos = pos;			//���W
			g_aEffect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(pos.x - g_aEffect[nCntEffect].fRadius, pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pos.x + g_aEffect[nCntEffect].fRadius, pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pos.x - g_aEffect[nCntEffect].fRadius, pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pos.x + g_aEffect[nCntEffect].fRadius, pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);

			g_aEffect[nCntEffect].col = col;			//�F

		    //���_�J���[�̐ݒ�
 			pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);

			g_aEffect[nCntEffect].fRadius = fRadius;				//���a
			g_aEffect[nCntEffect].fGravity = 0.0f;					//�d��
			g_aEffect[nCntEffect].fAngle = 0.0f;					//�p�x
			g_aEffect[nCntEffect].nTexType = TexType;				//�e�N�X�`���̃^�C�v
			g_aEffect[nCntEffect].nLife = 30;						//�G�t�F�N�g�̃��C�t
			
			g_aEffect[nCntEffect].bAngle = false;		//�p�x�𔻒肵�Ă邩�ǂ���
			g_aEffect[nCntEffect].bUse    = true;		//�g�p���Ă����Ԃɂ���
			break;
		}

		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}
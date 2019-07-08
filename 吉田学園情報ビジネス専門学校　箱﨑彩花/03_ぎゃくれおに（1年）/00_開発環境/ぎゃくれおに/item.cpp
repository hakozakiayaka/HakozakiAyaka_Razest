//-----------------------------------------------------------------------------
//
//�A�C�e���̏���[item.cpp]
//Author : �L�n���u�@���@�����@���@����
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "item.h"
#include "bullet.h"

//-----------------------------------------------------------------------------
//�}�N����`
//-----------------------------------------------------------------------------
#define TEXTURE_NAME  "data/TEXTURE/�K�\����.png"	//�ǂݍ��ރe�N�X�`���̖��O
#define MAX_ITEM	  (256)							//�A�C�e���̍ő吔
#define ITEM_WIDTH    (30.0f)						//�A�C�e���̕�
#define ITEM_HEIGHT	  (30.0f)						//�A�C�e���̍���
#define ITEM_U		  (1.0f)						//�e�N�X�`��U�͈�
#define ITEM_V		  (1.0f)						//�e�N�X�`��V�͈�

//-----------------------------------------------------------------------------
//�v���g�^�C�v�錾
//-----------------------------------------------------------------------------
void MakeVertexItem(LPDIRECT3DDEVICE9 pDevice); //���_�쐬

//-----------------------------------------------------------------------------
//�O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9		g_pTextureItem		= NULL; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem		= NULL; //���_�o�b�t�@�ւ̃|�C���^
Item					g_aItem[MAX_ITEM];			//�A�C�e���̌���
int						g_nItem;					//�A�C�e���̌�
int						g_nPlayerPossession = 0;	//�v���C���[�̏�����

//-----------------------------------------------------------------------------
//�A�C�e���̏���������
//-----------------------------------------------------------------------------
void InitItem(void)
{
	//���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //�f�o�C�X�̎擾

	// ���_���̍쐬
	MakeVertexItem(pDevice);
}

//-----------------------------------------------------------------------------
//�A�C�e���̏I������
//-----------------------------------------------------------------------------
void UninitItem(void)
{
	//�e�N�X�`���[�̔j��
	if (g_pTextureItem != NULL)
	{
		g_pTextureItem->Release();
		g_pTextureItem = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}

//-----------------------------------------------------------------------------
//�A�C�e���̍X�V����
//-----------------------------------------------------------------------------
void UpdateItem(void)
{
	//���[�J���ϐ��錾
	Player	  g_player = *GetPlayer(); //�v���C���[�̎擾
	Bullet *pBullet = GetBullet();
	VERTEX_3D *pVtx;				   //���_���ւ̃|�C���^
	int		  nCntItem;				   //�A�C�e���̃J�E���g

	//���_�o�b�t�@�����b�N
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntBullet = 0; nCntBullet < 100; nCntBullet++)
	{
		for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
		{//�ʒu�̍X�V
			if (pBullet[nCntBullet].bUse == true)
			{
				if (g_aItem[nCntItem].bUse == true)
				{//�A�C�e�����g�p����Ă���
					switch (g_aItem[nCntItem].state)
					{
					case ITEM_GASOLINE:					  //�R�C���̏ꍇ
						//�A�C�e���̂����蔻��
						if (g_nPlayerPossession == 0 &&
							pBullet[nCntBullet].posBullet.z < g_aItem[nCntItem].pos.z + g_aItem[nCntItem].fHeight && pBullet[nCntBullet].posBullet.z > g_aItem[nCntItem].pos.z &&
							pBullet[nCntBullet].posBullet.x > g_aItem[nCntItem].pos.x && pBullet[nCntBullet].posBullet.x < g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fWidth &&
							pBullet[nCntBullet].posBullet.y > g_aItem[nCntItem].pos.y && pBullet[nCntBullet].posBullet.y < g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fWidth)
						{//�A�C�e�����������Ă��Ȃ��v���C���[���A�C�e���͈͓̔�
							g_aItem[nCntItem].bUse = false;				//�g�p���Ă��Ȃ���ԂɕύX
							DeleteShadow(g_aItem[nCntItem].nIdxShadow); //�e������
							g_nItem--;									//�A�C�e���̌�������
							g_nPlayerPossession++;						//�v���C���[���A�C�e�����擾

							//if (g_nItem <= 0)
							//{//�����Ȃ��Ȃ�����
							//	SetFade(MODE_RESULT); //���ʉ�ʂ֑J��
							//}
						}
						break;
					}

					//�e�̈ʒu�X�V
					SetPositionShadow(g_aItem[nCntItem].nIdxShadow, g_aItem[nCntItem].pos, g_aItem[nCntItem].rot);
				}
			}
		}
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffItem->Unlock();
}

//-----------------------------------------------------------------------------
//�A�C�e���̕`�揈��
//-----------------------------------------------------------------------------
void DrawItem(void)
{
	//���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //�f�o�C�X�̎擾
	D3DXMATRIX		  mtxView, mtxTrans;	 //�v�Z�p�}�g���b�N�X
	int				  nCntItem;				 //�J�E���g

	//�A���t�@�e�X�g����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);	  //�A���t�@�e�X�g������L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);				  //�����̔�r�ΏہE��l			0�������F
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER); //�e�X�g�̏����E��r���@

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aItem[nCntItem].mtxWorld);

		//�A�C�e���𔽉f
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);
		g_aItem[nCntItem].mtxWorld._11 = mtxView._11; //�J�����̋t�s���ݒ�
		g_aItem[nCntItem].mtxWorld._12 = mtxView._21;
		g_aItem[nCntItem].mtxWorld._13 = mtxView._31;
		g_aItem[nCntItem].mtxWorld._21 = mtxView._12;
		g_aItem[nCntItem].mtxWorld._22 = mtxView._22;
		g_aItem[nCntItem].mtxWorld._23 = mtxView._32;
		g_aItem[nCntItem].mtxWorld._31 = mtxView._13;
		g_aItem[nCntItem].mtxWorld._32 = mtxView._23;
		g_aItem[nCntItem].mtxWorld._33 = mtxView._33;

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aItem[nCntItem].pos.x, g_aItem[nCntItem].pos.y, g_aItem[nCntItem].pos.z); //x,y,z�̏�
		D3DXMatrixMultiply(&g_aItem[nCntItem].mtxWorld, &g_aItem[nCntItem].mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aItem[nCntItem].mtxWorld);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_3D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureItem);

		//�A�C�e���̕`��
		if (g_aItem[nCntItem].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntItem * 4, 2);
		}
	}

	//�A���t�@�e�X�g����(���ɖ߂�)
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}
//-----------------------------------------------------------------------------
//�A�C�e���̐ݒ�
//-----------------------------------------------------------------------------
void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 rot, ITEMSTATE state, int nItemPossession)
{
	//���[�J���ϐ��錾
	int nCntItem; //�J�E���g

	g_nPlayerPossession = nItemPossession; //�󂯎��

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == false)
		{
			g_aItem[nCntItem].bUse		 = true;													//�g�p���Ă����Ԃɂ���
			g_aItem[nCntItem].pos		 = pos;														//pos�l���
			g_aItem[nCntItem].rot		 = rot;														//rot�l����
			g_aItem[nCntItem].state		 = state;													//�A�C�e���̎��
			g_nItem++;																				//�A�C�e���̌����J�E���g

			break;
		}
	}
}

//-----------------------------------------------------------------------------
//���_���̍쐬
//-----------------------------------------------------------------------------
void MakeVertexItem(LPDIRECT3DDEVICE9 pDevice)
{
	//���[�J���ϐ��錾
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^
	int		  nCntItem; //�J�E���g

	g_nItem = 0; //�A�C�e�����̏�����

	//�A�C�e���̏��̏�����
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem].pos				= D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�A�C�e���̒��S�������W
		g_aItem[nCntItem].rot				= D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�A�C�e���̌���
		g_aItem[nCntItem].bUse				= false;						 //�g�p���Ă��Ȃ�
		g_aItem[nCntItem].state				= ITEM_GASOLINE;				 //�A�C�e���̏��(���)
		g_aItem[nCntItem].fWidth			= ITEM_WIDTH;					 //�A�C�e���̕�
		g_aItem[nCntItem].fHeight			= ITEM_HEIGHT;					 //�A�C�e���̍���
		g_aItem[nCntItem].nIdxShadow		= 0;							 //�e�̔ԍ�
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_pTextureItem);

	//���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_ITEM,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_3D,
								D3DPOOL_MANAGED,
								&g_pVtxBuffItem,
								NULL);

	//���_�o�b�t�@�����b�N
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	//�z�u
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-5.0f, ITEM_HEIGHT, 0);
		pVtx[1].pos = D3DXVECTOR3(ITEM_WIDTH, ITEM_HEIGHT, 0);
		pVtx[2].pos = D3DXVECTOR3(-5.0f, 0.0f, 0);
		pVtx[3].pos = D3DXVECTOR3(ITEM_WIDTH, 0.0f, 0);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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

		pVtx += 4; //���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffItem->Unlock();
}

//-------------------------------------------------------------------------------------------------------------------------
//�A�C�e���̎擾����
//-------------------------------------------------------------------------------------------------------------------------
Item *GetItem(void)
{
	return &g_aItem[0];
}

//-------------------------------------------------------------------------------------------------------------------------
//�A�C�e���̎擾(������)����
//-------------------------------------------------------------------------------------------------------------------------
int *GetItemPossession(void)
{
	return &g_nPlayerPossession;
}
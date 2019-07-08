//-----------------------------------------------------------------------------
//
//���L���̏���[possession.cpp]
//Author : �L�n���u�@���@����
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "possession.h"
#include "length.h"

//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define	TEXTURE_POSSESSION  "data/TEXTURE/frame_Item.png" //�ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_POSSESSION2 "data/TEXTURE/�K�\����.png"	  //�ǂݍ��ރe�N�X�`���t�@�C����
#define POSSESSION_SIZE		(70)						  //���L���̉���(�e�N�X�`���̐���)
#define	GASORIN_X			(50)
#define MAX_TEXTURE			(2)							  //�e�N�X�`���̍ő吔
#define MAX_ITEM			(256)						  //�A�C�e���̍ő吔(GetItem�p)

//-----------------------------------------------------------------------------
//�O���[�o���ϐ��錾
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9		g_pTexturePossession[MAX_TEXTURE] = {};   //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPossession			  = NULL; //���_�o�b�t�@�ւ̃|�C���^
int						g_nPossession;							  //���L���̂̐��l
D3DXVECTOR3				g_posPossession;						  //���L���̂̒��S���W
D3DXVECTOR3				g_posFramePossession;					  //�t���[���̒��S���W

//-----------------------------------------------------------------------------
//���L���̏���������
//-----------------------------------------------------------------------------
void InitPossession(void)
{
	//���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //�f�o�C�X�̎擾
	int				  nCntPossession;		 //���L���̃J�E���g
	VERTEX_2D		  *pVtx;				 //���_����ݒ�

	//���L���̏�����
	g_posPossession		 = D3DXVECTOR3(150, SCREEN_HEIGHT - 90, 0.0f);  //���L���̏������W
	g_posFramePossession = D3DXVECTOR3(150, SCREEN_HEIGHT - 100, 0.0f); //�t���[���̏������W

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice, 
		TEXTURE_POSSESSION, 
		&g_pTexturePossession[0]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice, 
		TEXTURE_POSSESSION2,
		&g_pTexturePossession[1]
	);

	//���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&g_pVtxBuffPossession,
								NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPossession->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPossession = 0; nCntPossession < MAX_TEXTURE; nCntPossession++)
	{
		if (nCntPossession == 0)
		{
			//�t���[���̒��_�ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_posFramePossession.x - (POSSESSION_SIZE + 70), g_posFramePossession.y - (POSSESSION_SIZE + 20), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posFramePossession.x + (POSSESSION_SIZE + 70), g_posFramePossession.y - (POSSESSION_SIZE + 20), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posFramePossession.x - (POSSESSION_SIZE + 70), g_posFramePossession.y + (POSSESSION_SIZE + 20), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posFramePossession.x + (POSSESSION_SIZE + 70), g_posFramePossession.y + (POSSESSION_SIZE + 20), 0.0f);

			//1.0f�ŌŒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
		else if(nCntPossession == 1)
		{
			//�����̒��_�ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_posPossession.x - GASORIN_X, g_posPossession.y - GASORIN_X, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posPossession.x + GASORIN_X, g_posPossession.y - GASORIN_X, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posPossession.x - GASORIN_X, g_posPossession.y + GASORIN_X, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posPossession.x + GASORIN_X, g_posPossession.y + GASORIN_X, 0.0f);

			//1.0f�ŌŒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			//���L���̂̌��̕�
			g_posPossession.x += 50;
		}

		pVtx += 4; //���_�f�[�^�̃|�C���^��4�i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPossession->Unlock();
}

//-----------------------------------------------------------------------------
//���L���̏I������
//-----------------------------------------------------------------------------
void UninitPossession(void)
{
	//���[�J���ϐ��錾
	int nCntPossession; //�J�E���g

	//�e�N�X�`���̔j��
	for (nCntPossession = 0; nCntPossession < MAX_TEXTURE; nCntPossession++)
	{
		if (g_pTexturePossession[nCntPossession] != NULL)
		{
			g_pTexturePossession[nCntPossession]->Release();
			g_pTexturePossession[nCntPossession] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPossession != NULL)
	{
		g_pVtxBuffPossession->Release();
		g_pVtxBuffPossession = NULL;
	}
}

//-----------------------------------------------------------------------------
//���L���̍X�V����
//-----------------------------------------------------------------------------
void UpdatePossession(void)
{
	//���[�J���ϐ��錾
	int	   pItemPossession	= *GetItemPossession(); //�v���C���[�̏��������擾
	Player pPlayer = *GetPlayer();					//�v���C���[�̏�������
	Item   pItem = *GetItem();

	if (pItemPossession == 1 && GetKeyboardTrigger(DIK_E) == true)
	{
		pItemPossession = 0;
		SetItem(D3DXVECTOR3(pPlayer.pos.x, 0.0f, pPlayer.pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEM_GASOLINE, pItemPossession);
		AddLength(10, LengthTex_HIL);
	}
}

//-----------------------------------------------------------------------------
//���L���̕`�揈��
//-----------------------------------------------------------------------------
void DrawPossession(void)
{
	//���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice		  = GetDevice();		  //�f�o�C�X�̎擾
	int				  nCntPossession;						  //���L���̃J�E���g
	int				  pItemPossession = *GetItemPossession(); //

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPossession, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntPossession = 0; nCntPossession < MAX_TEXTURE; nCntPossession++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePossession[nCntPossession]);

		//�e�N�X�`���̕`��
		if (nCntPossession == 0)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntPossession, 2);
		}
		else if (nCntPossession == 1 && pItemPossession == 1)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntPossession, 2);
		}
	}
}
//=============================================================================
//
// �v���[���[���� [titleplayer.cpp]
// Author : �������D
//
//=============================================================================
#include "titleplayer.h"
#include "main.h"
#include "sound.h"
#include "input.h"
#include "game.h"
#include "effect.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEXTURENAME		"data\\TEXTURE\\santa.png"		//�ǂ݂��ރe�N�X�`���̖��O
#define TITLEPLAYER_ANIM		(20.0f)

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
//VERTEX_2D				g_aVertex[4];				//���_�����i�[����
LPDIRECT3DTEXTURE9		g_pTextureTitlePlayer = NULL;	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitlePlayer = NULL;	//���_�o�b�t�@�ւ̃|�C���^
TitlePlayer				g_player;					//�v���C���[�̃|�C���^

//=============================================================================
//	���_���̐ݒ�
//=============================================================================
void InitTitlePlayer(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//����������
	g_player.nCounterAnim = 0;							//�J�E���^�[������������
	g_player.nPatternAnim = 0;							//�p�^�[��No.������������
	g_player.pos = D3DXVECTOR3(640.0f, 500.0f, 0.0f);	//�����ʒu
	g_player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�O��̈ʒu
	g_player.posMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����l
	g_player.nDirectionMove = 0;
	g_player.bDisp = true;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
								TEXTURENAME,
								&g_pTextureTitlePlayer);

	//���_�o�b�t�@�̐���
	pDevice -> CreateVertexBuffer(sizeof(VERTEX_2D)*4,
								  D3DUSAGE_WRITEONLY,
								  FVF_VERTEX_2D,
								  D3DPOOL_MANAGED,
								  &g_pVtxBuffTitlePlayer,
								  NULL);

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTitlePlayer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - POSCENTER_X, g_player.pos.y - POSCENTER_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + POSCENTER_X, g_player.pos.y - POSCENTER_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - POSCENTER_X, g_player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + POSCENTER_X, g_player.pos.y, 0.0f);

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
	pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitlePlayer->Unlock();
}

//========================================================================================
//�I������
//========================================================================================
void UninitTitlePlayer(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureTitlePlayer != NULL)
	{
		g_pTextureTitlePlayer->Release();
		g_pTextureTitlePlayer = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitlePlayer != NULL)
	{
		g_pVtxBuffTitlePlayer->Release();
		g_pVtxBuffTitlePlayer = NULL;
	}
}

//========================================================================================
//�X�V����
//========================================================================================
void UpdateTitlePlayer(void)
{
	//�ϐ��錾
	g_player.nCounterAnim++;

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	if (g_player.bDisp == true)
	{
		//�O��̈ʒu��ۑ�
		g_player.posOld = g_player.pos;

		//�G�t�F�N�g
		SetEffect(g_player.pos, D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f), 2.0f, 1);

		g_player.nDirectionMove = 0;

		//�A�j���[�V�����̏���
		if ((g_player.nCounterAnim % 30) == 0)
		{
			g_player.nPatternAnim = (g_player.nPatternAnim + 1) % 4;
		}

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffTitlePlayer->Lock(0, 0, (void**)&pVtx, 0);

		//�e�N�X�`�����W�̐ݒ�
		if (g_player.nDirectionMove == 0)
		{//�E�����̎�
			pVtx[1].tex = D3DXVECTOR2(0.5f * g_player.nPatternAnim, 0.0f);
			pVtx[0].tex = D3DXVECTOR2(0.5f + 0.5f * g_player.nPatternAnim, 0.0f);
			pVtx[3].tex = D3DXVECTOR2(0.5f * g_player.nPatternAnim, 1.0f);
			pVtx[2].tex = D3DXVECTOR2(0.5f + 0.5f * g_player.nPatternAnim, 1.0f);
		}
		if (g_player.nDirectionMove == 1)
		{//���Ɍ����Ă���Ƃ�
			pVtx[0].tex = D3DXVECTOR2(0.5f * g_player.nPatternAnim, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.5f + 0.5f * g_player.nPatternAnim, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.5f * g_player.nPatternAnim, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.5f + 0.5f * g_player.nPatternAnim, 1.0f);
		}
	
		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffTitlePlayer->Unlock();
	}
}

//========================================================================================
//�`�揈��
//========================================================================================
void DrawTitlePlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

		//�f�o�C�X�̎擾
		pDevice = GetDevice();

		//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffTitlePlayer, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTitlePlayer);

		if (g_player.bDisp == true)
		{
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
}

//========================================================================================
//�v���C���[�̏��
//========================================================================================
TitlePlayer *GetTitlePlayer(void)
{
	return &g_player;
}
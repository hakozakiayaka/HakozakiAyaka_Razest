//=========================================================================================================================
//
// �G���^�[�̏��� [enter.cpp]
// Author : �L�n ���u
//
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "main.h"
#include "enter.h"		//�G���^�[
#include "game.h"

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define ENTER_TEXTURE_NAME		"data\\TEXTURE\\PressEnter2.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define ENTER_TEXTURE_UV_U		(1.0f)								//�e�N�X�`���A�j���[�V����U�͈�
#define ENTER_TEXTURE_UV_V		(1.0f)								//�e�N�X�`���A�j���[�V����V�͈�
#define ENTER_SIZE_X			(200)
#define	ENTER_SIZE_Y			(50)
#define MAX_TEXTURE				(1)									//�e�N�X�`������

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureEnter = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnter = NULL;			//���_�o�b�t�@�ւ̃|�C���^
Enter g_Enter;

//=========================================================================================================================
// �G���^�[����������
//=========================================================================================================================
void InitEnter(void)
{
	//�f�o�C�X�|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//���[�h�̃|�C���^
	MODE pMode = *GetMode();

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//������
	g_Enter.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Enter.pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 300, SCREEN_HEIGHT / 2, 0.0f);

	if (pMode == MODE_TUTORIAL)
	{
		g_Enter.pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 380, SCREEN_HEIGHT / 2 + 280, 0.0f);
	}
	else if (pMode == MODE_RANKING)
	{
		g_Enter.pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 400, SCREEN_HEIGHT / 2 + 280, 0.0f);
	}


	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		ENTER_TEXTURE_NAME,
		&g_pTextureEnter
	);

	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnter,
		NULL
	);

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	g_pVtxBuffEnter->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//���_�ݒ�
	pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 200,SCREEN_HEIGHT / 2 + 230, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 200, SCREEN_HEIGHT / 2 + 230, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 + 330, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 200, SCREEN_HEIGHT / 2 + 330, 0.0f);
	//1.0f�ŌŒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[�ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//�e�N�X�`���ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(ENTER_TEXTURE_UV_U, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, ENTER_TEXTURE_UV_V);
	pVtx[3].tex = D3DXVECTOR2(ENTER_TEXTURE_UV_U, ENTER_TEXTURE_UV_V);

	if (pMode == MODE_TUTORIAL)
	{
		//���_�ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_Enter.pos.x - ENTER_SIZE_X, g_Enter.pos.y - ENTER_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Enter.pos.x + ENTER_SIZE_X, g_Enter.pos.y - ENTER_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Enter.pos.x - ENTER_SIZE_X, g_Enter.pos.y + ENTER_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Enter.pos.x + ENTER_SIZE_X, g_Enter.pos.y + ENTER_SIZE_Y, 0.0f);
		//1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//���_�J���[�ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(ENTER_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, ENTER_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(ENTER_TEXTURE_UV_U, ENTER_TEXTURE_UV_V);

	}
	else if (pMode == MODE_RANKING)
	{
		//���_�ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_Enter.pos.x - ENTER_SIZE_X, g_Enter.pos.y - ENTER_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Enter.pos.x + ENTER_SIZE_X, g_Enter.pos.y - ENTER_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Enter.pos.x - ENTER_SIZE_X, g_Enter.pos.y + ENTER_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Enter.pos.x + ENTER_SIZE_X, g_Enter.pos.y + ENTER_SIZE_Y, 0.0f);
		//1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//���_�J���[�ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(ENTER_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, ENTER_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(ENTER_TEXTURE_UV_U, ENTER_TEXTURE_UV_V);

	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEnter->Unlock();
}

//=========================================================================================================================
// �G���^�[�I������
//=========================================================================================================================
void UninitEnter(void)
{
	//�e�N�X�`���[�̔j��
	if (g_pTextureEnter != NULL)
	{
		g_pTextureEnter->Release();
		g_pTextureEnter = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEnter != NULL)
	{
		g_pVtxBuffEnter->Release();
		g_pVtxBuffEnter = NULL;
	}
}

//=========================================================================================================================
// �G���^�[�X�V����
//=========================================================================================================================
void UpdateEnter(void)
{
	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

							//���_�o�b�t�@�����b�N
	g_pVtxBuffEnter->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//�_�ŏ���
	//�I�����Ă���J���[�̒l�����炵�Ă���
	g_Enter.col.a -= 0.015f;

	if (g_Enter.col.a < 0.1f)
	{//�M�����Ă���J���[��0.5��؂�����J���[�̒l�������Ă�
		g_Enter.col.a = 1.0f;
	}

	// ���_�J���[�ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Enter.col.a);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Enter.col.a);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Enter.col.a);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Enter.col.a);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEnter->Unlock();
}

//=========================================================================================================================
// �G���^�[�`�揈��
//=========================================================================================================================
void DrawEnter(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�|�C���^

									//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource
	(
		0,
		g_pVtxBuffEnter,
		0,
		sizeof(VERTEX_2D)
	);

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureEnter);

	//�G���^�[�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
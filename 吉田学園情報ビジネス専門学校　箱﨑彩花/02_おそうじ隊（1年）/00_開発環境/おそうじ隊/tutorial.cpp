//===============================================================================
//
// �`���[�g���A����� [tutorial.cpp]
// Author : �����ʉ�
//
//===============================================================================
#include "main.h"
#include"tutorial.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//==============================================================================
//�}�N����`
//===============================================================================
#define TUTORIAL_TEXTURE	 "data/TEXTURE/tutorial.png"				//�ǂݍ��ރe�N�X�`��
#define TUTORIAL_POS_X						(0)									//�w�i�̍���X���W
#define TUTORIAL_POS_Y						(0)									//�w�i�̍���Y���W
#define TUTORIAL_WIDTH						(SCREEN_WIDTH)			//�w�i�̕�
#define TUTORIAL_HEIGHT					(SCREEN_HEIGHT)			//�w�i�̍���

//===============================================================================
//�O���[�o���ϐ��錾
//===============================================================================
LPDIRECT3DTEXTURE9 g_pTextureTutorial = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;	//���_�o�b�t�@�ւ̃|�C���^

//===============================================================================
//�`���[�g���A����ʏ���������
//===============================================================================
void InitTutorial(void)
{
	//�ϐ��錾
	VERTEX_2D * pVtx;						//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X���擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURE, &g_pTextureTutorial);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	//�w�i�̍��W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(TUTORIAL_POS_X, TUTORIAL_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(TUTORIAL_WIDTH, TUTORIAL_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(TUTORIAL_POS_X, TUTORIAL_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(TUTORIAL_WIDTH, TUTORIAL_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�w�i�F�ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�w�i�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTutorial->Unlock();
}

//===============================================================================
//�`���[�g���A����ʏI������
//===============================================================================
void UninitTutorial(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureTutorial != NULL)
	{
		g_pTextureTutorial->Release();
		g_pTextureTutorial = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}
}

//===============================================================================
//�`���[�g���A����ʍX�V����
//===============================================================================
void UpdateTutorial(void)
{
	//�t�F�[�h�̎擾
	FADE g_fade =GetFade();

	//����L�[�������ꂽ���ǂ���
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		PlaySound(SOUND_LABEL_SE_DECIDE);
		if (g_fade != FADE_OUT)
		{	//�t�F�[�h�A�E�g����Enter�L�[�������Ȃ�����
			//���[�h�ݒ�
			SetFade(MODE_GAME);
		}
	}
}

//===============================================================================
//�`���[�g���A����ʕ`�揈��
//===============================================================================
void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X���擾����
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTutorial);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
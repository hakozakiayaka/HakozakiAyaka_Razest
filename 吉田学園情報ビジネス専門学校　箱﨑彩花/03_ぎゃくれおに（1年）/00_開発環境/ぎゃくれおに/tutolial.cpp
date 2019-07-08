//=========================================================================================================================
//
// �^�C�g���̏��� [tutolial.cpp]
// Author :  �L�n���u�@���@����
//
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "main.h"			//���C��
#include "tutolial.h"		//�`���[�g���A��
#include "input.h"			//���͏���
#include "fade.h"			//�t�F�[�h
#include "sound.h"			//�T�E���h
#include "enter.h"			//�G���^�[

//*************************************************************************************************************************
// �}�N����`
//*******************************************************w******************************************************************
#define TUTORIAL_TEXTURE_NAME  "data/TEXTURE/.png"									//�ǂݍ��ރe�N�X�`���t�@�C��
#define TUTORIAL_TEXTURE_NAME1 "data/TEXTURE/�`���[�g���A���R���g���[���[��.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define TUTORIAL_TEXTURE_NAME2 "data/TEXTURE/Tutorial2.png"							//�ǂݍ��ރe�N�X�`���t�@�C��
#define TUTORIAL_POS_X		   (300)												//�`���[�g���A���̍���X���W
#define TUTORIAL_POS_Y		   (600)												//�`���[�g���A���̍���Y���W
#define TUTORIAL_WIDTH		   (1000)												//�`���[�g���A���̕�
#define TUTORIAL_HEIGHT		   (700)											    //�`���[�g���A���̍���
#define MAX_TEXTURE			   (3)													//�e�N�X�`������
#define MAX_TUTORIAL		   (2)													//�`���[�g���A���̍ő吔

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTutorial[MAX_TEXTURE] = {};   //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;				//���_�o�b�t�@�ւ̃|�C���^
int						g_nCntTimeTutorial = 0;					//�J�E���^�[
float					g_nColor2 = 1.0f;						//�w���\���̓����x
Tutorial				g_aTutorial[MAX_TUTORIAL];				//�`���[�g���A���̏��
int						g_nPage;								//�y�[�W��

//=========================================================================================================================
// �^�C�g������������
//=========================================================================================================================
void InitTutolial(void)
{
	//���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //�f�o�C�X�̎擾
	VERTEX_2D		  *pVtx;				 //���_���ւ̃|�C���^
	int				  nCntTutorial;			 //�`���[�g���A���̃J�E���g
	int				  nInterval;			 //�Ԋu(�ʒu)

	//������
	for (nCntTutorial = 0; nCntTutorial < MAX_TUTORIAL; nCntTutorial++)
	{
		g_aTutorial[nCntTutorial].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorial[nCntTutorial].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	g_nPage = 1; //�y�[�W�̏�����

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURE_NAME, &g_pTextureTutorial[0]);  //�w���\��
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURE_NAME1, &g_pTextureTutorial[1]);  //�w���\��
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURE_NAME2, &g_pTextureTutorial[2]); //�`���[�g���A��1
	
	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL
	);

	//���_�o�b�t�@�����b�N
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	//�w���\���̏�����
	//���_�ݒ�
	pVtx[0].pos = D3DXVECTOR3(TUTORIAL_POS_X, TUTORIAL_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(TUTORIAL_WIDTH, TUTORIAL_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(TUTORIAL_POS_X, TUTORIAL_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(TUTORIAL_WIDTH, TUTORIAL_HEIGHT, 0.0f);

	//���_�J���[�ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_nColor2);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_nColor2);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_nColor2);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_nColor2);

	//1.0f�ŌŒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�e�N�X�`���ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//�`���[�g���A�����̏�����
	for (nCntTutorial = 0, nInterval = 0; nCntTutorial < MAX_TUTORIAL; nCntTutorial++, nInterval += SCREEN_WIDTH)
	{
		pVtx += 4;	//���_�f�[�^�̃|�C���^��4�i�߂�

		//���_�ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aTutorial[nCntTutorial].pos.x + nInterval, g_aTutorial[nCntTutorial].pos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aTutorial[nCntTutorial].pos.x + SCREEN_WIDTH + nInterval, g_aTutorial[nCntTutorial].pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aTutorial[nCntTutorial].pos.x + nInterval, g_aTutorial[nCntTutorial].pos.y + SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aTutorial[nCntTutorial].pos.x + SCREEN_WIDTH + nInterval, g_aTutorial[nCntTutorial].pos.y + SCREEN_HEIGHT, 0.0f);

		//���_�J���[�ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTutorial->Unlock();

	//�G���^�[
	InitEnter();
}

//=========================================================================================================================
// �^�C�g���I������
//=========================================================================================================================
void UninitTutolial(void)
{
	//���[�J���ϐ��錾
	int nCntTutorial; //�`���[�g���A���̃J�E���g

	//�e�N�X�`���̔j��
	for (nCntTutorial = 0; nCntTutorial < MAX_TEXTURE; nCntTutorial++)
	{
		if (g_pTextureTutorial[nCntTutorial] != NULL)
		{
			g_pTextureTutorial[nCntTutorial]->Release();
			g_pTextureTutorial[nCntTutorial] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}

	//�G���^�[
	UninitEnter();
}

//=========================================================================================================================
// �^�C�g���X�V����
//=========================================================================================================================
void UpdateTutolial(void)
{
	FADE pFade = GetFade();

	//���[�J���ϐ��錾
	VERTEX_2D *pVtx;			  //���_���ւ̃|�C���^
	int		  nCntTutorial;		  //�`���[�g���A���̃J�E���g
	int		  nInterval;		  //�Ԋu(�ʒu)

	g_nCntTimeTutorial++; //���Ԃ̃J�E���g

	//���_�o�b�t�@�����b�N
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	if ((g_nCntTimeTutorial % 10) == 0) //10�t���[����
	{//��莞�ԂŎw���\���̓_��
		g_nColor2 -= 0.05f;

		if (g_nColor2 <= 0.2f)
		{//���ɖ߂�
			g_nColor2 = 1.0f;
		}
	}

	//���_�J���[�ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_nColor2);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_nColor2);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_nColor2);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_nColor2);

	//�y�[�W�̐i��or�߂�
	if (GetKeyboardTrigger(DIK_RIGHT) == true && g_nPage < 2 || GetJoyPadTrigger(DIJS_BUTTON_12, 0) == true && g_nPage < 2)
	{//���̃y�[�W�֐i��
		for (nCntTutorial = 0, nInterval = 0; nCntTutorial < MAX_TUTORIAL; nCntTutorial++, nInterval += SCREEN_WIDTH)
		{
			
			g_aTutorial[nCntTutorial].move.x = -SCREEN_WIDTH;

			//�ʒu���X�V(�ړ�)
			g_aTutorial[nCntTutorial].pos.x += g_aTutorial[nCntTutorial].move.x;
			g_aTutorial[nCntTutorial].pos.y += g_aTutorial[nCntTutorial].move.y;

			pVtx += 4;	//���_�f�[�^�̃|�C���^��4�i�߂�

			//���_�ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aTutorial[nCntTutorial].pos.x + nInterval, g_aTutorial[nCntTutorial].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aTutorial[nCntTutorial].pos.x + SCREEN_WIDTH + nInterval, g_aTutorial[nCntTutorial].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aTutorial[nCntTutorial].pos.x + nInterval, g_aTutorial[nCntTutorial].pos.y + SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aTutorial[nCntTutorial].pos.x + SCREEN_WIDTH + nInterval, g_aTutorial[nCntTutorial].pos.y + SCREEN_HEIGHT, 0.0f);
		}

		g_nPage += 1; //�y�[�W��i�߂�
	}
	else if (GetKeyboardTrigger(DIK_LEFT) == true && g_nPage > 1 || GetJoyPadTrigger(DIJS_BUTTON_13, 0) == true && g_nPage > 1)
	{//�O�̃y�[�W�֖߂�
		for (nCntTutorial = 0, nInterval = 0; nCntTutorial < MAX_TUTORIAL; nCntTutorial++, nInterval += SCREEN_WIDTH)
		{
			g_aTutorial[nCntTutorial].move.x = SCREEN_WIDTH;

			//�ʒu���X�V(�ړ�)
			g_aTutorial[nCntTutorial].pos.x += g_aTutorial[nCntTutorial].move.x;
			g_aTutorial[nCntTutorial].pos.y += g_aTutorial[nCntTutorial].move.y;

			pVtx += 4;	//���_�f�[�^�̃|�C���^��4�i�߂�

						//���_�ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aTutorial[nCntTutorial].pos.x + nInterval, g_aTutorial[nCntTutorial].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aTutorial[nCntTutorial].pos.x + SCREEN_WIDTH + nInterval, g_aTutorial[nCntTutorial].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aTutorial[nCntTutorial].pos.x + nInterval, g_aTutorial[nCntTutorial].pos.y + SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aTutorial[nCntTutorial].pos.x + SCREEN_WIDTH + nInterval, g_aTutorial[nCntTutorial].pos.y + SCREEN_HEIGHT, 0.0f);
		}

		g_nPage -= 1; //�y�[�W��߂�
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTutorial->Unlock();

	if (pFade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoyPadTrigger(3, 0) == true)
		{
			//���艹
			PlaySound(SOUND_LABEL_SE_DECIDE);
			//���[�h�ݒ�
			SetFade(MODE_GAME);
		}
	}

	//�G���^�[
	UpdateEnter();
}

//=========================================================================================================================
// �^�C�g���`�揈��
//=========================================================================================================================
void DrawTutolial(void)
{
	//���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //�f�o�C�X�̎擾
	int				  nCntTutorial;			 //�`���[�g���A���̃J�E���g

	 //���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntTutorial = 0; nCntTutorial < MAX_TEXTURE; nCntTutorial++)
	{
		//�e�N�X�`���ݒ�
		pDevice->SetTexture(0, g_pTextureTutorial[nCntTutorial]);

		//�`���[�g���A���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTutorial * 4, 2);
	}
	//�G���^�[
	DrawEnter();
}
//=========================================================================================================================
//
// �^�C�g���̏��� [TITLE.cpp]
// Author :  �L�n���u�@���@�����@���@���R
//
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "main.h"
#include "Title.h"		//�^�C�g��
#include "input.h"		//����
#include "fade.h"		//�t�F�[�h
#include "camera.h"		//�J����
#include "light.h"		//���C�g
#include "meshbg.h"		//���b�V���V�����_�[
#include "meshfield.h"	//���b�V���t�B�[���h
#include "sound.h"		//�T�E���h
#include "billboord.h"	//�r���{�[�h
#include "wall.h"		//�E�H�[��
#include "effect.h"		//�G�t�F�N�g
#include "object.h"		//�I�u�W�F�N�g
#include "objectnot.h"	//�����蔻��̂Ȃ��I�u�W�F�N�g
#include "enter.h"		//�G���^�[
#include "frame.h"		//�e�N�X�`��

//*************************************************************************************************************************
// �}�N����`
//**************************************************************************************************************************
#define TITLE_TEXTURE_NAME	   "data/TEXTURE/�\��.png" //�ǂݍ��ރe�N�X�`���t�@�C��
#define TITLE_TEXTURE_NAME_GI  "data/TEXTURE/��.png"   //�ǂݍ��ރe�N�X�`���t�@�C��
#define TITLE_TEXTURE_NAME_XYA "data/TEXTURE/��.png"   //�ǂݍ��ރe�N�X�`���t�@�C��
#define TITLE_TEXTURE_NAME_KU  "data/TEXTURE/��.png"   //�ǂݍ��ރe�N�X�`���t�@�C��
#define TITLE_TEXTURE_NAME_RE  "data/TEXTURE/��.png"   //�ǂݍ��ރe�N�X�`���t�@�C��
#define TITLE_TEXTURE_NAME_O   "data/TEXTURE/��.png"   //�ǂݍ��ރe�N�X�`���t�@�C��
#define TITLE_TEXTURE_NAME_NI  "data/TEXTURE/��.png"   //�ǂݍ��ރe�N�X�`���t�@�C��
#define MAX_TEXTURE			   (7)					   //�e�N�X�`���̍ő吔
#define MAX_TITLE			   (6)					   //�^�C�g�������̍ő吔
#define TITLE_POS_X			   (10)					   //�^�C�g���̍���X���W
#define TITLE_POS_Y			   (-250)				   //�^�C�g���̍���Y���W
#define TITLE_WIDTH			   (250)				   //�^�C�g���̕�
#define TITLE_HEIGHT		   (250)				   //�^�C�g���̍���
#define TITLE2_POS_X		   (300)				   //�w���\���̍���X���W
#define TITLE2_POS_Y		   (600)				   //�w���\���̍���Y���W
#define TITLE2_WIDTH		   (1000)				   //�w���\���̕�
#define TITLE2_HEIGHT		   (700)				   //�w���\���̍���
#define TITLE_SPEED			   (5.0f)				   //�^�C�g���̃X�s�[�h

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTitle[MAX_TEXTURE] = {};  //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;				//���_�o�b�t�@�ւ̃|�C���^
int						g_nCntTimeTitle = 0;				//�J�E���^�[
float					g_nColor = 1.0f;					//�w���\���̓����x
Title					g_aTitle[MAX_TITLE];				//�^�C�g���̏��
int						g_nCountTimer;

//=========================================================================================================================
// �^�C�g������������
//=========================================================================================================================
void InitTitle(void)
{
	//���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //�f�o�C�X�̎擾
	VERTEX_2D		  *pVtx;				 //���_���ւ̃|�C���^
	int				  nCntTitle;			 //�^�C�g���̕����̃J�E���g
	int				  nInterval;			 //�Ԋu

	g_nCntTimeTitle = 0;	 //�J�E���^�[�̏�����

	//������
	for (nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
	{
		g_aTitle[nCntTitle].pos = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y, 0.0f);
		g_aTitle[nCntTitle].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME, &g_pTextureTitle[0]);	 //�w���\��
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_GI, &g_pTextureTitle[1]);  //�^�C�g��1
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_XYA, &g_pTextureTitle[2]); //�^�C�g��2
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_KU, &g_pTextureTitle[3]);  //�^�C�g��3
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_RE, &g_pTextureTitle[4]);  //�^�C�g��4
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_O, &g_pTextureTitle[5]);   //�^�C�g��5
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_NI, &g_pTextureTitle[6]);  //�^�C�g��6

	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	//���_�o�b�t�@�����b�N
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	////�w���\���̒��_���W�̐ݒ�
	//pVtx[0].pos = D3DXVECTOR3(TITLE2_POS_X, TITLE2_POS_Y, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(TITLE2_WIDTH, TITLE2_POS_Y, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(TITLE2_POS_X, TITLE2_HEIGHT, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(TITLE2_WIDTH, TITLE2_HEIGHT, 0.0f);

	////�w���\���̒��_�J���[�ݒ�
	//pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_nColor);
	//pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_nColor);
	//pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_nColor);
	//pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_nColor);

	////1.0f�ŌŒ�
	//pVtx[0].rhw = 1.0f;
	//pVtx[1].rhw = 1.0f;
	//pVtx[2].rhw = 1.0f;
	//pVtx[3].rhw = 1.0f;

	////�w���\���̃e�N�X�`���ݒ�
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//�^�C�g���̕���
	for (nCntTitle = 0, nInterval = 0; nCntTitle < MAX_TITLE; nCntTitle++, nInterval += 200)
	{
		pVtx += 4;	//���_�f�[�^�̃|�C���^��4�i�߂�
		//�^�C�g���̒��_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aTitle[nCntTitle].pos.x + nInterval, g_aTitle[nCntTitle].pos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aTitle[nCntTitle].pos.x + TITLE_WIDTH + nInterval, g_aTitle[nCntTitle].pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aTitle[nCntTitle].pos.x + nInterval, g_aTitle[nCntTitle].pos.y + TITLE_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aTitle[nCntTitle].pos.x + TITLE_WIDTH + nInterval, g_aTitle[nCntTitle].pos.y + TITLE_HEIGHT, 0.0f);

		//�^�C�g���̒��_�J���[�ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//�^�C�g���̃e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTitle->Unlock();

	//�J�����̏���������
	InitCamera();

	//�J�����̏���������
	InitLight();

	//�̏���������
	InitMeshBg();

	//���b�V���t�B�[���h�̏���������
	InitMeshField();

	//�G�t�F�N�g�̏���������
	InitEffect();

	//�I�u�W�F�N�g�̏���������
	InitObject();

	//�����蔻��̂Ȃ��I�u�W�F�N�g�̏���������
	InitObjectNot();

	//�G���^�[�̏���������
	InitEnter();

	//================================================================================
	//�����蔻��̂���I�u�W�F�N�g
	//================================================================================
	//200
	SetObject(D3DXVECTOR3(100.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//400
	SetObject(D3DXVECTOR3(1000.0f, 0.0f, -1400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//600
	SetObject(D3DXVECTOR3(900.0f, 0.0f, -2100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//�M��(��)
	SetObject(D3DXVECTOR3(1200.0f, 0.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//�X��
	SetObject(D3DXVECTOR3(3000.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//�_���{�[��
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -3550.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	//�g���b�N
	SetObject(D3DXVECTOR3(4200.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//��
	SetObject(D3DXVECTOR3(0.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//���̋@
	SetObject(D3DXVECTOR3(1400.0f, 0.1f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//�S�~��
	SetObject(D3DXVECTOR3(1220.0f, 0.1f, -2820.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//�����
	SetObject(D3DXVECTOR3(100.0f, 0.1f, -800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(500.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(700.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------5---------------

	SetObject(D3DXVECTOR3(900.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(900.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(900.0f, 0.0f, -900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(900.0f, 0.0f, -1100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//------------10---------------

	//200
	SetObject(D3DXVECTOR3(500.0f, 0.0f, -1100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(100.0f, 0.0f, -1100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//200
	SetObject(D3DXVECTOR3(100.0f, 0.0f, -2100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(300.0f, 0.0f, -2100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------15---------------

	//200
	SetObject(D3DXVECTOR3(-100.0f, 0.0f, -2100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//200
	SetObject(D3DXVECTOR3(100.0f, 0.0f, -2500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(300.0f, 0.0f, -2500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1100.0f, 0.0f, -2500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------20---------------

	//200
	SetObject(D3DXVECTOR3(100.0f, 0.0f, -2700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(500.0f, 0.0f, -2700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(700.0f, 0.0f, -2700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1100.0f, 0.0f, -2700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(-100.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------25---------------

	//200
	SetObject(D3DXVECTOR3(100.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(300.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(700.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(900.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1100.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------30---------------

	//200
	SetObject(D3DXVECTOR3(100.0f, 0.0f, -3700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(500.0f, 0.0f, -3700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(900.0f, 0.0f, -3700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1100.0f, 0.0f, -3500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(100.0f, 0.0f, -3900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------35---------------

	//200
	SetObject(D3DXVECTOR3(900.0f, 0.0f, -3900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1100.0f, 0.0f, -3900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(900.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(300.0f, 0.0f, -2100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(-100.0f, 0.0f, -2100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------40---------------

	//200
	SetObject(D3DXVECTOR3(2300.0f, 0.0f, -2300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3500.0f, 0.0f, -2100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(500.0f, 0.0f, -4100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1700.0f, 0.0f, -4100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1700.0f, 0.0f, -3700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------45---------------

	//200
	SetObject(D3DXVECTOR3(1700.0f, 0.0f, -3500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1900.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1900.0f, 0.0f, -3500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2100.0f, 0.0f, -3900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3300.0f, 0.0f, -3500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------50---------------

	//200
	SetObject(D3DXVECTOR3(2300.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2500.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3700.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3900.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3300.0f, 0.0f, -3700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------55---------------

	//200
	SetObject(D3DXVECTOR3(2700.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2900.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3100.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3300.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3500.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------60---------------

	//200
	SetObject(D3DXVECTOR3(2500.0f, 0.0f, -3500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2500.0f, 0.0f, -3700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2500.0f, 0.0f, -3900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2900.0f, 0.0f, -3700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2900.0f, 0.0f, -4100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------65---------------

	//200
	SetObject(D3DXVECTOR3(3500.0f, 0.0f, -3700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3900.0f, 0.0f, -3700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3900.0f, 0.0f, -3900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(4100.0f, 0.0f, -3700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------69---------------


	//------------73---------------

	//400

	//------------81---------------

	//200
	SetObject(D3DXVECTOR3(3300.0f, 0.0f, -3900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2500.0f, 0.0f, -3900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2500.0f, 0.0f, -2300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(4100.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------85---------------

	//200
	SetObject(D3DXVECTOR3(1700.0f, 0.0f, -1900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1700.0f, 0.0f, -1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1900.0f, 0.0f, -1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2100.0f, 0.0f, -1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2300.0f, 0.0f, -1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------90---------------

	//200
	SetObject(D3DXVECTOR3(2500.0f, 0.0f, -1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2700.0f, 0.0f, -1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3300.0f, 0.0f, -1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3900.0f, 0.0f, -1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(4100.0f, 0.0f, -1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------95---------------

	//200
	SetObject(D3DXVECTOR3(4100.0f, 0.0f, -1900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3900.0f, 0.0f, -1300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3900.0f, 0.0f, -1100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3900.0f, 0.0f, -900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3900.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------100---------------


	//200
	SetObject(D3DXVECTOR3(3700.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3700.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3700.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3700.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3500.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------105---------------

	//200
	SetObject(D3DXVECTOR3(3300.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3100.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------107---------------

	//400
	SetObject(D3DXVECTOR3(200.0f, 0.0f, -1600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3600.0f, 0.0f, -2600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(4000.0f, 0.0f, -2600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3800.0f, 0.0f, -2000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3000.0f, 0.0f, -1800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2600.0f, 0.0f, -1400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2600.0f, 0.0f, -1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1800.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1800.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));


	//600
	SetObject(D3DXVECTOR3(1900.0f, 0.0f, -2500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2900.0f, 0.0f, -2500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1900.0f, 0.0f, -1100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3300.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�M��(��)
	SetObject(D3DXVECTOR3(1200.0f, 0.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1600.0f, 0.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1600.0f, 0.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�X��
	SetObject(D3DXVECTOR3(100.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(400.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(700.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1000.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2000.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(2700.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3000.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3300.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3600.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3900.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�X��
	SetObject(D3DXVECTOR3(100.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(400.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(700.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1000.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2000.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(2700.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3000.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3300.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3600.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3900.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -100.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -400.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -700.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -1000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -1300.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -1600.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -1900.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -2200.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -2500.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -2800.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -4000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -3700.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -3400.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	//
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -100.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -400.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -700.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -1000.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -1300.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));

	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -1600.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -1900.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -2200.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -2500.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -2800.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));

	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -4000.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -3700.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -3400.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));

	//�_���{�[��
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -3450.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1350.0f, 0.1f, -3450.0f), D3DXVECTOR3(0.0f, -0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1450.0f, 0.1f, -3450.0f), D3DXVECTOR3(0.0f, -0.0f, 0.0f));

	SetObject(D3DXVECTOR3(100.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 0.1f, 0.0f));
	SetObject(D3DXVECTOR3(350.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 0.9f, 0.0f));
	SetObject(D3DXVECTOR3(550.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 0.4f, 0.0f));
	SetObject(D3DXVECTOR3(750.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 0.3f, 0.0f));
	SetObject(D3DXVECTOR3(950.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 0.6f, 0.0f));
	SetObject(D3DXVECTOR3(1300.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(1950.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(2150.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(1700.0f, 0.1f, -3300.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));

	SetObject(D3DXVECTOR3(1750.0f, 0.1f, -3300.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));
	SetObject(D3DXVECTOR3(1750.0f, 0.1f, -3350.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(1700.0f, 0.1f, -3250.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(1700.0f, 0.1f, -3200.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(1800.0f, 0.1f, -3300.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));

	SetObject(D3DXVECTOR3(1100.0f, 0.1f, -3700.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));
	SetObject(D3DXVECTOR3(1100.0f, 0.1f, -3750.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(1100.0f, 0.1f, -3800.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(1150.0f, 0.1f, -3700.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(1150.0f, 0.1f, -3750.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));

	SetObject(D3DXVECTOR3(300.0f, 0.1f, -2700.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));
	SetObject(D3DXVECTOR3(300.0f, 0.1f, -2750.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(300.0f, 0.1f, -2800.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(350.0f, 0.1f, -2700.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(350.0f, 0.1f, -2750.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));
	SetObject(D3DXVECTOR3(350.0f, 0.1f, -2800.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));

	SetObject(D3DXVECTOR3(1100.0f, 0.1f, -300.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));
	SetObject(D3DXVECTOR3(1100.0f, 0.1f, -350.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(1100.0f, 0.1f, -250.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(1150.0f, 0.1f, -350.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(1150.0f, 0.1f, -250.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));

	SetObject(D3DXVECTOR3(1100.0f, 0.1f, -1000.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));
	SetObject(D3DXVECTOR3(1100.0f, 0.1f, -1050.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(1100.0f, 0.1f, -1150.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(1150.0f, 0.1f, -1050.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(1150.0f, 0.1f, -1150.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));
	SetObject(D3DXVECTOR3(1150.0f, 0.1f, -1000.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));

	SetObject(D3DXVECTOR3(3500.0f, 0.1f, -300.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));
	SetObject(D3DXVECTOR3(3500.0f, 0.1f, -350.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(3500.0f, 0.1f, -250.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(3550.0f, 0.1f, -300.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(3550.0f, 0.1f, -350.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));

	SetObject(D3DXVECTOR3(3900.0f, 0.1f, -100.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));
	SetObject(D3DXVECTOR3(3900.0f, 0.1f, -150.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(3900.0f, 0.1f, -50.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(3950.0f, 0.1f, -150.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(3950.0f, 0.1f, -200.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));
	SetObject(D3DXVECTOR3(3900.0f, 0.1f, -0.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));

	SetObject(D3DXVECTOR3(2700.0f, 0.1f, -100.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));
	SetObject(D3DXVECTOR3(2700.0f, 0.1f, -150.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(2700.0f, 0.1f, -50.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(2750.0f, 0.1f, -100.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(2750.0f, 0.1f, -150.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));
	SetObject(D3DXVECTOR3(2750.0f, 0.1f, -50.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));

	SetObject(D3DXVECTOR3(2700.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));
	SetObject(D3DXVECTOR3(2700.0f, 0.1f, -550.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(2700.0f, 0.1f, -450.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(2750.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 1.2f, 0.0f));
	SetObject(D3DXVECTOR3(2750.0f, 0.1f, -550.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));

	SetObject(D3DXVECTOR3(2500.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(2500.0f, 0.1f, -550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2500.0f, 0.1f, -450.0f), D3DXVECTOR3(0.0f, 1.2f, 0.0f));
	SetObject(D3DXVECTOR3(2550.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.4f, 0.0f));
	SetObject(D3DXVECTOR3(2550.0f, 0.1f, -550.0f), D3DXVECTOR3(0.0f, 0.9f, 0.0f));

	SetObject(D3DXVECTOR3(2350.0f, 0.1f, -100.0f), D3DXVECTOR3(0.0f, 0.9f, 0.0f));
	SetObject(D3DXVECTOR3(2350.0f, 0.1f, -150.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(2350.0f, 0.1f, -50.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(2300.0f, 0.1f, -100.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(2300.0f, 0.1f, -150.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));

	SetObject(D3DXVECTOR3(2900.0f, 0.1f, -1500.0f), D3DXVECTOR3(0.0f, 0.9f, 0.0f));
	SetObject(D3DXVECTOR3(2900.0f, 0.1f, -1550.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(2900.0f, 0.1f, -1450.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(2950.0f, 0.1f, -1550.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(2950.0f, 0.1f, -1450.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));
	SetObject(D3DXVECTOR3(2950.0f, 0.1f, -1500.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));

	SetObject(D3DXVECTOR3(3500.0f, 0.1f, -3500.0f), D3DXVECTOR3(0.0f, 0.9f, 0.0f));
	SetObject(D3DXVECTOR3(3500.0f, 0.1f, -3550.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(3500.0f, 0.1f, -3450.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(3550.0f, 0.1f, -3550.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(3550.0f, 0.1f, -3450.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));

	//
	SetObject(D3DXVECTOR3(4100.0f, 0.1f, -3900.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(4150.0f, 0.1f, -3900.0f), D3DXVECTOR3(0.0f, 0.4f, 0.0f));
	SetObject(D3DXVECTOR3(100.0f, 0.1f, -3500.0f), D3DXVECTOR3(0.0f, 0.9f, 0.0f));
	SetObject(D3DXVECTOR3(150.0f, 0.1f, -3550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(300.0f, 0.1f, -4100.0f), D3DXVECTOR3(0.0f, 1.2f, 0.0f));

	SetObject(D3DXVECTOR3(900.0f, 0.1f, -4100.0f), D3DXVECTOR3(0.0f, 0.9f, 0.0f));//�P�̔z�u
	SetObject(D3DXVECTOR3(700.0f, 0.1f, -3500.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));//�P�̔z�u
	SetObject(D3DXVECTOR3(350.0f, 0.1f, -3550.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));//�P�̔z�u
	SetObject(D3DXVECTOR3(700.0f, 0.1f, -350.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(750.0f, 0.1f, -300.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));

	SetObject(D3DXVECTOR3(300.0f, 0.1f, -1100.0f), D3DXVECTOR3(0.0f, 0.9f, 0.0f));
	SetObject(D3DXVECTOR3(350.0f, 0.1f, -1100.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(250.0f, 0.1f, -1150.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(2300.0f, 0.1f, -1550.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(2300.0f, 0.1f, -1450.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));

	SetObject(D3DXVECTOR3(3300.0f, 0.1f, -1300.0f), D3DXVECTOR3(0.0f, 0.9f, 0.0f));
	SetObject(D3DXVECTOR3(3350.0f, 0.1f, -1350.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(3400.0f, 0.1f, -1250.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(3200.0f, 0.1f, -1300.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(3250.0f, 0.1f, -1400.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));

	SetObject(D3DXVECTOR3(2300.0f, 0.1f, -1900.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));
	SetObject(D3DXVECTOR3(2200.0f, 0.1f, -1850.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(2350.0f, 0.1f, -1850.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(2400.0f, 0.1f, -1950.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));
	SetObject(D3DXVECTOR3(2200.0f, 0.1f, -1950.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));

	SetObject(D3DXVECTOR3(1900.0f, 0.1f, -1950.0f), D3DXVECTOR3(0.0f, 0.9f, 0.0f));
	SetObject(D3DXVECTOR3(1900.0f, 0.1f, -1900.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(1900.0f, 0.1f, -1850.0f), D3DXVECTOR3(0.0f, 1.1f, 0.0f));
	SetObject(D3DXVECTOR3(2000.0f, 0.1f, -1950.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(2000.0f, 0.1f, -1850.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));

	SetObject(D3DXVECTOR3(2300.0f, 0.1f, -4100.0f), D3DXVECTOR3(0.0f, 0.9f, 0.0f));
	SetObject(D3DXVECTOR3(2250.0f, 0.1f, -4050.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(2100.0f, 0.1f, -3700.0f), D3DXVECTOR3(0.0f, 1.1f, 0.0f));
	SetObject(D3DXVECTOR3(2050.0f, 0.1f, -3650.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(2700.0f, 0.1f, -3500.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));

	SetObject(D3DXVECTOR3(1900.0f, 0.1f, -1950.0f), D3DXVECTOR3(0.0f, 0.9f, 0.0f));//�_���{�[����Ŏg��
	SetObject(D3DXVECTOR3(2400.0f, 0.1f, -2500.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));//�d�˒u����
	SetObject(D3DXVECTOR3(2400.0f, 0.1f, -2600.0f), D3DXVECTOR3(0.0f, 1.1f, 0.0f));//
	SetObject(D3DXVECTOR3(2450.0f, 0.1f, -2550.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));//
	SetObject(D3DXVECTOR3(2450.0f, 0.1f, -2600.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));//

	SetObject(D3DXVECTOR3(2500.0f, 50.0f, -300.0f), D3DXVECTOR3(0.0f, 0.9f, 0.0f));
	SetObject(D3DXVECTOR3(2520.0f, 20.0f, -300.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(2500.0f, 80.0f, -300.0f), D3DXVECTOR3(0.0f, 1.1f, 0.0f));
	SetObject(D3DXVECTOR3(2500.0f, 20.0f, -340.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(2500.0f, 50.1f, -340.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));

	//�g���b�N
	SetObject(D3DXVECTOR3(2500.0f, 0.1f, -300.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObject(D3DXVECTOR3(2500.0f, 0.1f, -300.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));//�d�˒u����

																				   //��(��)
	SetObject(D3DXVECTOR3(150.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(250.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(350.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(450.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1750.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(650.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(750.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2150.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(950.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1950.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1150.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(2350.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2450.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2650.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2850.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3050.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(3150.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3250.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3450.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3650.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3950.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(250.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(350.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(450.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1750.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(650.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(750.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2150.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(950.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1950.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1150.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(2350.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2450.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2650.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2850.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3050.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(3150.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3250.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3450.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3650.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3950.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -450.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -750.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -950.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -1050.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -1350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -1550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -1850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -2250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -2350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -2550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -3350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -3600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -3600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -3850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -4050.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));


	SetObject(D3DXVECTOR3(1550.0f, 0.1f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -450.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -750.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -950.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -1050.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -1350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -1550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -1850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -2250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -2350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -2550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -3350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -3550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -3550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -3850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -4050.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//-----------------------------------------------------�������ꂠ
	SetObject(D3DXVECTOR3(0.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(150.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(300.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(450.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(600.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(0.0f, 0.1f, -650.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(150.0f, 0.1f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(350.0f, 0.1f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(500.0f, 0.1f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(500.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));


	SetObject(D3DXVECTOR3(2200.0f, 0.1f, -0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2300.0f, 0.1f, -0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2400.0f, 0.1f, -0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2500.0f, 0.1f, -0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2600.0f, 0.1f, -0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(2500.0f, 0.1f, -2700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(150.0f, 0.1f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));//--------------------
	SetObject(D3DXVECTOR3(350.0f, 0.1f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));//�؂����˂������イ
	SetObject(D3DXVECTOR3(500.0f, 0.1f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(500.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(0.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(150.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(300.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(450.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(600.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(0.0f, 0.1f, -650.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(150.0f, 0.1f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(350.0f, 0.1f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(500.0f, 0.1f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(500.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));//-------------------

																				 //���̋@
	SetObject(D3DXVECTOR3(1100.0f, 0.1f, -900.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));

	SetObject(D3DXVECTOR3(1100.0f, 0.1f, -800.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1100.0f, 0.1f, -700.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1200.0f, 0.1f, -3250.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(50.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2100.0f, 0.1f, -2810.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(3000.0f, 0.1f, -2810.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(200.0f, 0.1f, -2810.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3300.0f, 0.1f, -1500.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(3600.0f, 0.1f, -4000.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObject(D3DXVECTOR3(4000.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	//�S�~��
	SetObject(D3DXVECTOR3(100.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	SetObject(D3DXVECTOR3(2220.0f, 0.1f, -2820.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3020.0f, 0.1f, -2820.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(330.0f, 0.1f, -3120.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1520.0f, 0.1f, -3120.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(4020.0f, 0.1f, -2820.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(1820.0f, 0.1f, -3620.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(320.0f, 0.1f, -4120.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3520.0f, 0.1f, -1120.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3520.0f, 0.1f, 80.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2220.0f, 0.1f, -620.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(2300.0f, 0.1f, -2500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//================================================================================
	//�����蔻��̂Ȃ��I�u�W�F�N�g
	//================================================================================
	//
	SetObjectNot(D3DXVECTOR3(1400.0f, 0.1f, -325.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//
	SetObjectNot(D3DXVECTOR3(1400.0f, 0.1f, -325.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//�M��
	SetObjectNot(D3DXVECTOR3(1600.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	//�X��
	SetObjectNot(D3DXVECTOR3(3000.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	//��
	SetObjectNot(D3DXVECTOR3(0.0f, 20.0f, -2850.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	//����
	SetObjectNot(D3DXVECTOR3(-100.0f, 0.2f, -500.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));

	//�ԓ�
	SetObjectNot(D3DXVECTOR3(1400.0f, 0.1f, -975.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1400.0f, 0.1f, -1625.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(1400.0f, 0.1f, -2275.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1400.0f, 0.1f, -2925.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1400.0f, 0.1f, -3700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));// -3575.0f


	SetObjectNot(D3DXVECTOR3(325.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(975.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1625.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	SetObjectNot(D3DXVECTOR3(2275.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2925.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3700.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	//����

	SetObjectNot(D3DXVECTOR3(1400.0f, 0.1f, -1325.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1400.0f, 0.1f, -3620.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1400.0f, 0.1f, -3700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(1400.0f, 0.1f, -2025.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1400.0f, 0.1f, -2375.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(325.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(780.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(780.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	SetObjectNot(D3DXVECTOR3(2020.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2675.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3700.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	//�M��
	SetObjectNot(D3DXVECTOR3(1200.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1600.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1200.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	//�X��
	SetObjectNot(D3DXVECTOR3(100.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(400.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(700.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1000.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2000.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));

	SetObjectNot(D3DXVECTOR3(2700.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3000.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3300.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3600.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3900.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));

	//�X��
	SetObjectNot(D3DXVECTOR3(100.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(400.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(700.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1000.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2000.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(2700.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3000.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3300.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3600.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3900.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -100.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -400.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -700.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -1000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -1300.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -1600.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -1900.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -2200.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -2500.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -2800.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -3400.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -3700.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -4000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	//
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -100.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -400.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -700.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -1000.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -1300.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));

	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -1600.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -1900.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -2200.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -2500.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -2800.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));

	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -3400.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -3700.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -4000.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));

	//��
	SetObjectNot(D3DXVECTOR3(150.0f, 20.0f, -2850.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));

	SetObjectNot(D3DXVECTOR3(250.0f, 20.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(350.0f, 10.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(450.0f, 20.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1750.0f, 10.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(650.0f, 20.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(750.0f, 20.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2150.0f, 20.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(950.0f, 10.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1950.0f, 20.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1150.0f, 20.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(2350.0f, 20.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2450.0f, 10.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2650.0f, 20.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2850.0f, 10.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3050.0f, 10.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(3150.0f, 20.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3250.0f, 10.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3450.0f, 10.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3650.0f, 20.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3950.0f, 10.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(250.0f, 20.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(350.0f, 10.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(450.0f, 20.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1750.0f, 10.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(650.0f, 20.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(750.0f, 20.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2150.0f, 20.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(950.0f, 10.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1950.0f, 20.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1150.0f, 20.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(2350.0f, 20.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2450.0f, 10.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2650.0f, 20.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2850.0f, 10.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3050.0f, 10.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(3150.0f, 20.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3250.0f, 10.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3450.0f, 10.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3650.0f, 20.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3950.0f, 10.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -450.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -750.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -950.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -1050.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -1350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -1550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -1850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -2250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -2350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -2550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -3350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -3600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -3600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -3850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -4050.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));


	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -450.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -750.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -950.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -1050.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -1350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -1550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -1850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -2250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -2350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -2550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -3350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -3550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -3550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -3850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -4050.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//-----------------------------------------------------�������ꂠ
	SetObjectNot(D3DXVECTOR3(0.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(150.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(300.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(450.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(600.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(0.0f, 0.1f, -650.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(150.0f, 0.1f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(350.0f, 0.1f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(500.0f, 0.1f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(500.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(2200.0f, 0.1f, -0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2300.0f, 0.1f, -0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2400.0f, 0.1f, -0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2500.0f, 0.1f, -0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2600.0f, 0.1f, -0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(2500.0f, 0.1f, -2700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(150.0f, 0.1f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));//--------------------
	SetObjectNot(D3DXVECTOR3(350.0f, 0.1f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));//�؂����˂������イ
	SetObjectNot(D3DXVECTOR3(500.0f, 0.1f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(500.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(0.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(150.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(300.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(450.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(600.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(0.0f, 0.1f, -650.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(150.0f, 0.1f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(350.0f, 0.1f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(500.0f, 0.1f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(500.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));//-------------------

																					//����
	SetObjectNot(D3DXVECTOR3(0.0f, 0.2f, -500.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(100.0f, 0.2f, -500.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(200.0f, 0.2f, -500.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(300.0f, 0.2f, -500.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(400.0f, 0.2f, -500.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(500.0f, 0.2f, -500.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(600.0f, 0.2f, -500.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));


	SetObjectNot(D3DXVECTOR3(-100.0f, 0.2f, -600.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(0.0f, 0.2f, -600.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(100.0f, 0.2f, -600.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(200.0f, 0.2f, -600.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(300.0f, 0.2f, -600.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(400.0f, 0.2f, -600.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(500.0f, 0.2f, -600.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(600.0f, 0.2f, -600.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));

	SetObjectNot(D3DXVECTOR3(-100.0f, 0.2f, -700.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(0.0f, 0.2f, -700.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(100.0f, 0.2f, -700.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(200.0f, 0.2f, -700.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(300.0f, 0.2f, -700.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(400.0f, 0.2f, -700.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(500.0f, 0.2f, -700.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(600.0f, 0.2f, -700.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));

	SetObjectNot(D3DXVECTOR3(-100.0f, 0.2f, -800.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(0.0f, 0.2f, -800.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(100.0f, 0.2f, -800.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(200.0f, 0.2f, -800.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(300.0f, 0.2f, -800.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(400.0f, 0.2f, -800.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(500.0f, 0.2f, -800.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(600.0f, 0.2f, -800.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));

	SetObjectNot(D3DXVECTOR3(-100.0f, 0.2f, -900.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(0.0f, 0.2f, -900.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(100.0f, 0.2f, -900.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(200.0f, 0.2f, -900.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(300.0f, 0.2f, -900.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(400.0f, 0.2f, -900.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(500.0f, 0.2f, -900.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(600.0f, 0.2f, -900.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));

	SetObjectNot(D3DXVECTOR3(2250.0f, 0.2f, -2500.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2350.0f, 0.2f, -2500.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2450.0f, 0.2f, -2500.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2550.0f, 0.2f, -2500.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2250.0f, 0.2f, -2600.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2350.0f, 0.2f, -2600.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2450.0f, 0.2f, -2600.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2550.0f, 0.2f, -2600.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
}

//=========================================================================================================================
// �^�C�g���I������
//=========================================================================================================================
void UninitTitle(void)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{//�S�e�N�X�`���̃J�E���g
		//�e�N�X�`���[�̔j��
		if (g_pTextureTitle[nCount] != NULL)
		{
			g_pTextureTitle[nCount] ->Release();
			g_pTextureTitle[nCount] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

	//�J�����̏I������
	UninitCamera();

	//���C�g�̏I������
	UninitLight();

	//�V�����_�[�̏I������
	UninitMeshBg();

	//���b�V���t�B�[���h�̏I������
	UninitMeshField();

	//�G�t�F�N�g�̏I������
	UninitEffect();

	//�I�u�W�F�N�g�̏I������
	UninitObject();

	//�����蔻��̂Ȃ��I�u�W�F�N�g�̏I������
	UninitObjectNot();

	//�G���^�[�̏I������
	UninitEnter();
}

//=========================================================================================================================
// �^�C�g���X�V����
//=========================================================================================================================
void UpdateTitle(void)
{
	//���[�J���ϐ��錾
	VERTEX_2D *pVtx;			   //���_���ւ̃|�C���^
	FADE	  pFade = GetFade();  //�t�F�[�h�̃|�C���^
	int		  nCntTitle;		   //�^�C�g���̕����̃J�E���g
	int		  nInterval;		   //�Ԋu(�ʒu)
	int		  nFrame = 15;		   //�Ԋu(����)

	g_nCntTimeTitle++; //���Ԃ̃J�E���g

	//���_�o�b�t�@�����b�N
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	if ((g_nCntTimeTitle % 10) == 0) //60�t���[����
	{//�w���\���̓_��
		g_nColor -= 0.05f;

		if (g_nColor <= 0.2f)
		{//��莞�Ԕ����Ȃ�
			g_nColor = 1.0f;
		}
	}

	//���_�J���[�ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_nColor);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_nColor);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_nColor);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_nColor);

	//�^�C�g�������̏W��
	for (nCntTitle = 0, nInterval = 0; nCntTitle < MAX_TITLE; nCntTitle++, nInterval += 200)
	{
		//�ړ�
		if (nCntTitle == 0)
		{//�u���v�E����
			if (g_aTitle[0].pos.y < 150)
			{
				g_aTitle[0].move = D3DXVECTOR3(0.0f, TITLE_SPEED, 0.0f);
			}
			else
			{//���̈ʒu�𒴂�����~�܂�
				g_aTitle[0].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
		else if (nCntTitle == 1 && g_nCntTimeTitle >= nFrame)
		{//�u��v�ォ��
			if (g_aTitle[1].pos.y < 150)
			{
				g_aTitle[1].move = D3DXVECTOR3(0.0f, TITLE_SPEED, 0.0f);
			}
			else
			{//���̈ʒu�𒴂�����~�܂�
				g_aTitle[1].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
		else if (nCntTitle == 2 && g_nCntTimeTitle >= (nFrame * 2))
		{//�u���v������
			if (g_aTitle[2].pos.y < 150)
			{
				g_aTitle[2].move = D3DXVECTOR3(0.0f, TITLE_SPEED, 0.0f);
			}
			else
			{//���̈ʒu�𒴂�����~�܂�
				g_aTitle[2].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
		else if (nCntTitle == 3 && g_nCntTimeTitle >= (nFrame * 3))
		{//�u��v�E����
			if (g_aTitle[3].pos.y < 150)
			{
				g_aTitle[3].move = D3DXVECTOR3(0.0f, TITLE_SPEED, 0.0f);
			}
			else
			{//���̈ʒu�𒴂�����~�܂�
				g_aTitle[3].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
		else if (nCntTitle == 4 && g_nCntTimeTitle >= (nFrame * 4))
		{//�u���v�ォ��
			if (g_aTitle[4].pos.y < 150)
			{
				g_aTitle[4].move = D3DXVECTOR3(0.0f, TITLE_SPEED, 0.0f);
			}
			else
			{//���̈ʒu�𒴂�����~�܂�
				g_aTitle[4].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
		else if (nCntTitle == 5 && g_nCntTimeTitle >= (nFrame * 5))
		{//�u�Ɂv������
			if (g_aTitle[5].pos.y < 150)
			{
				g_aTitle[5].move = D3DXVECTOR3(0.0f, TITLE_SPEED, 0.0f);
			}
			else
			{//���̈ʒu�𒴂�����~�܂�
				g_aTitle[5].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}

		//�ʒu���X�V(�ړ�)
		g_aTitle[nCntTitle].pos.x += g_aTitle[nCntTitle].move.x;
		g_aTitle[nCntTitle].pos.y += g_aTitle[nCntTitle].move.y;

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4�i�߂�

		//�^�C�g���̒��_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aTitle[nCntTitle].pos.x + nInterval, g_aTitle[nCntTitle].pos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aTitle[nCntTitle].pos.x + TITLE_WIDTH + nInterval, g_aTitle[nCntTitle].pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aTitle[nCntTitle].pos.x + nInterval, g_aTitle[nCntTitle].pos.y + TITLE_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aTitle[nCntTitle].pos.x + TITLE_WIDTH + nInterval, g_aTitle[nCntTitle].pos.y + TITLE_HEIGHT, 0.0f);
	}

	if (pFade == FADE_NONE)
	{
		//�ݒ�L�[(Enter)�������ꂽ���ǂ���
		if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoyPadTrigger(3, 0) == true)
		{
			if (g_aTitle[5].pos.y == 150)
			{
				//���艹
				PlaySound(SOUND_LABEL_SE_DECIDE);
				//���[�h�Œ�
				SetFade(MODE_SERECT);
			}

			//�G���^�[���������Ƃ��ɖ������ʒu�����炷
			g_aTitle[0].pos.y = 150;
			g_aTitle[1].pos.y = 150;
			g_aTitle[2].pos.y = 150;
			g_aTitle[3].pos.y = 150;
			g_aTitle[4].pos.y = 150;
			g_aTitle[5].pos.y = 150;
		}
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTitle->Unlock();

	//���C�g�̍X�V����
	UpdateLight();

	//�J�����̍X�V����
	UpdateCamera();

	//�V�����_�[�̍X�V����
	UpdateMeshBg();

	//���b�V���t�B�[���h�̍X�V����
	UpdateMeshField();

	//�G�t�F�N�g�̍X�V����
	UpdateEffect();

	//�I�u�W�F�N�g�̍X�V����
	UpdateObject();

	//�����蔻��̂Ȃ��I�u�W�F�N�g�̍X�V����
	UpdateObjectNot();

	//�G���^�[�̍X�V����
	UpdateEnter();
}

//=========================================================================================================================
// �^�C�g���`�揈��
//=========================================================================================================================
void DrawTitle(void)
{
	SetCamera(CAMERA_TYPE_DEMO,5);

	//���b�V���t�B�[���h�̕`�揈��
	DrawMeshField();

	//�V�����_�[�̕`�揈��
	DrawMeshBg();

	//�G�t�F�N�g�̕`�揈��
	DrawEffect();

	//�I�u�W�F�N�g�̕`�揈��
	DrawObject();

	//�����蔻��̂Ȃ��I�u�W�F�N�g�̕`�揈��
	DrawObjectNot();

	//�G���^�[�̕`�揈��
	DrawEnter();


	//���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //�f�o�C�X�̎擾
	int				  nCnt;					 //�J�E���g

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		//�e�N�X�`���ݒ�
		pDevice->SetTexture(0, g_pTextureTitle[nCnt]);

		//�^�C�g���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
}
//===============================================================================
//
// �v���C���[�����̏��� [player.cpp]
// Author : �����ʉ�
//
//===============================================================================
#include "main.h"
#include"player.h"
#include "input.h"
#include "block.h"
#include "item.h"
#include "game.h"
#include"sound.h"

//===============================================================================
//�}�N����`
//===============================================================================
#define PLAYER_TEXTURE "data/TEXTURE/player002.png"				//�g�p����e�N�X�`��
#define PLAYER_POS_X							(200)													//�w�i�̍���X���W
#define PLAYER_POS_Y							(500)													//�w�i�̍���Y���W
#define PLAYER_SPEED							(0.5f)													//�v���C���[�̃X�s�[�h
#define PATTERN									(4)														//�p�^�[����
#define JUMP											(20)													//�W�����v�̍���
#define GRAVITY										(1.0)														//�d��
#define PLAYER_WIDTH							(30)														//�v���C���[�̕�
#define PLAYER_HEIGHT						(70)														//�v���C���[�̍���
#define GROUND									(800)													//�n��

//===============================================================================
//�O���[�o���ϐ��錾
//===============================================================================
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;					//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Player g_player;
int g_nNumPlayer;

//===============================================================================
//�v���C���[��������������
//===============================================================================
void InitPlayer(void)
{
	//�ϐ��錾
	VERTEX_2D * pVtx;							//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X���擾
	pDevice = GetDevice();

	//�\���̂̏�����
	g_player.pos = D3DXVECTOR3(640, 100, 0.0f);		//�|���S���̈ʒu
	g_player.posOld = D3DXVECTOR3(0, 0, 0.0f);
	g_player.move = D3DXVECTOR3(0, 0, 0.0f);			//�|���S���̈ړ���
	g_player.bDisp = true;
	g_player.bJump = true;
	g_player.bUse = true;
	g_player.nPatternAnim = 0;
	g_player.nCntAnim = 0;
	g_player.DirectionMove = 0;
	g_player.nWidth = PLAYER_WIDTH;
	g_player.nHeight = PLAYER_HEIGHT;
	g_player.state = PLAYERSTATE_NORMAL;

	g_nNumPlayer = 0;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, PLAYER_TEXTURE, &g_pTexturePlayer);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);	

	//�|���S���̍��W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH, g_player.pos.y - PLAYER_HEIGHT,0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH, g_player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH, g_player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH, g_player.pos.y, 0.0f);

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
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f,0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}

//===============================================================================
//�v���C���[�����I������
//===============================================================================
void UninitPlayer(void)
{
	//�e�N�X�`���̊J��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//===============================================================================
//�v���C���[�����X�V����
//===============================================================================
void UpdatePlayer(void)
{
	//�ϐ��錾
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//�O��̈ʒu��ۑ�
	g_player.posOld = g_player.pos;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_player.state)
	{
		case PLAYERSTATE_NORMAL:
			//�|���S���̍��W�ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH, g_player.pos.y - PLAYER_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH, g_player.pos.y - PLAYER_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH, g_player.pos.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH, g_player.pos.y, 0.0f);
			break;

		case PLAYERSTATE_SIZEUP:
			//�|���S���̍��W�ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH * 1.5f, g_player.pos.y - PLAYER_HEIGHT * 1.5f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH * 1.5f, g_player.pos.y - PLAYER_HEIGHT * 1.5f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH * 1.5f, g_player.pos.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH * 1.5f, g_player.pos.y, 0.0f);
			break;

		case PLAYERSTATE_SIZEDOWN:
			//�|���S���̍��W�ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH / 2, g_player.pos.y - PLAYER_HEIGHT / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH / 2, g_player.pos.y - PLAYER_HEIGHT / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH / 2, g_player.pos.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH / 2, g_player.pos.y, 0.0f);
			break;
	}

	if (GetKeyboardPress(DIK_A) == true)
	{	//�C�ӂ̃L�[�iA�L�[�j�������ꂽ�Ƃ��A��
		g_player.move.x += sinf(D3DX_PI * -0.5f) * PLAYER_SPEED;
		g_player.move.y += cosf(D3DX_PI * -0.5f) * PLAYER_SPEED;
		g_player.DirectionMove = 1;
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{	//�C�ӂ̃L�[�iD�L�[�j�������ꂽ�Ƃ��A�E
		g_player.move.x += sinf(D3DX_PI * 0.5f) * PLAYER_SPEED;
		g_player.move.y += cosf(D3DX_PI * 0.5f) * PLAYER_SPEED;
		g_player.DirectionMove = 0;
	}

	//	�ړ��̃A�j���[�V����
	if (g_player.bJump == true)
	{
		if (g_player.nPatternAnim % 1 == 0)
		{
			g_player.nCntAnim++;
			if ((g_player.nCntAnim % 7) == 0)
			{
				g_player.nPatternAnim = (g_player.nPatternAnim + 1) % PATTERN;
			}
		}
	}
	else if (g_player.move.x > 1 || g_player.move.x < -1)
	{	//�L�[�����ĂȂ��Ƃ��~�܂�
		g_player.nCntAnim++;
		if ((g_player.nCntAnim % 7) == 0)
		{
			g_player.nPatternAnim = (g_player.nPatternAnim + 1) % PATTERN;
		}
	}
	else
	{
		if (g_player.nPatternAnim == 0 || g_player.nPatternAnim == 2)
		{	//�~�܂����瑫�߂�
			g_player.nCntAnim++;
			if ((g_player.nCntAnim % 7) == 0)
			{
				g_player.nPatternAnim = (g_player.nPatternAnim + 1) % PATTERN;
			}
		}
	}

	if (g_player.bJump == false)
	{
		if (GetKeyboardTrigger(DIK_SPACE) == true)
		{	//�C�ӂ̃L�[�iSPACE�L�[�j�������ꂽ�Ƃ��A��
			g_player.move.y = -JUMP;		//�W�����v��
			g_player.bJump = true;
			PlaySound(SOUND_LABEL_SE_JUMP);
		}
	}

	////�n�ʂ̏���
	//if (g_player.pos.y >= SCREEN_HEIGHT)
	//{
	//	g_player.bJump = false;
	//	g_player.pos.y = SCREEN_HEIGHT;
	//	g_player.move.y = 0.0f;
	//}

	//�d�͉��Z
	g_player.move.y += GRAVITY;

	g_player.pos.x += g_player.move.x;	//���ړ�
	g_player.pos.y += g_player.move.y;	//����

	//��ʊO�ɏo����
	if (g_player.pos.x < 10)
	{ //�E���ɏo����
		g_player.pos.x = SCREEN_WIDTH + 10;
	}
	if (g_player.pos.x > SCREEN_WIDTH + 10)
	{ //�����ɏo����
		g_player.pos.x = 10;
	}

	//�ʒu���̍X�V
	g_player.pos.x += g_player.move.x;

	//�����̃X�s�[�h
	g_player.move.x += (0.0f - g_player.move.x) * 0.2f;
	//g_player.move.y += (0.0f - g_player.move.y) * 0.2f;

	//�u���b�N�Ƃ̓����蔻��
	if (CollisionBlock(&g_player.pos, &g_player.posOld, &g_player.move, PLAYER_WIDTH, PLAYER_HEIGHT) == true)
	{	//�v���C���[�ʏ���
		g_player.bJump = false;
	}
	else
	{
		if (g_player.bJump == false)
		{
			g_player.bJump = true;
		}
	}

	//�A�C�e���̓����蔻��
	CollisionItem(0);
	CollisionItem(1);
	CollisionItem(2);

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f + 0.25f * (g_player.nPatternAnim + 1), 0.5f * g_player.DirectionMove);
	pVtx[1].tex = D3DXVECTOR2(0.25f + 0.25f * (g_player.nPatternAnim + 1), 0.5f * g_player.DirectionMove);
	pVtx[2].tex = D3DXVECTOR2(0.0f + 0.25f * (g_player.nPatternAnim + 1), 0.5f * g_player.DirectionMove + 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25f + 0.25f * (g_player.nPatternAnim + 1), 0.5f * g_player.DirectionMove + 0.5f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}

//===============================================================================
//�v���C���[�����`�揈��
//===============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X���擾����
	pDevice = GetDevice();

	if (g_player.bDisp == true)
	{
		//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePlayer);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//===============================================================================
//�v���C���[���擾
//===============================================================================
Player * GetPlayer(void)
{
	return &g_player;
}
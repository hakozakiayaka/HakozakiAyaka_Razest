//===============================================================================
//
// �v���C���[�����̏��� [player.cpp]
// Author : �����ʉ�
//
//===============================================================================
#include "main.h"
#include"player.h"
#include"input.h"
#include"bullet.h"
#include "explosion.h"
#include "game.h"
#include "sound.h"
#include "life.h"

//===============================================================================
//�}�N����`
//===============================================================================
#define PLAYER_TEXTURE_NAME "data/TEXTURE/player001.png"				//�g�p����e�N�X�`��
#define PLAYER_POS_X							(200)													//�w�i�̍���X���W
#define PLAYER_POS_Y							(500)													//�w�i�̍���Y���W
#define PLAYER_SPEED							(3.0f)													//�v���C���[�̃X�s�[�h
#define PLAYER_TEX_PATTAERN			(10)														//�v���C���[�̃p�^�[����
#define DAMAGE_STATE						(7)														//�_���[�W���	
#define PLAYER_LIFE								(3)														//	�v���C���[�̃��C�t

//===============================================================================
//�O���[�o���ϐ��錾
//===============================================================================
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;					//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;		//���_�o�b�t�@�ւ̃|�C���^
int g_nCounterAnim;																	//�A�j���[�V�����J�E���^�[
int g_nPatternAnim;																	//�A�j���[�V����No.
Player g_player;

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

	g_nCounterAnim = 0;	//�J�E���^�[������������
	g_nPatternAnim = 0;	//�p�^�[��No.������������

	g_player.pos = D3DXVECTOR3(640, 695, 0.0f);		//�|���S���̈ʒu
	g_player.move = D3DXVECTOR3(0,0,0.0f);																	//�|���S���̈ړ���
	g_player.bDisp = true;
	g_player.nCounterState = 0;
	g_player.state = PLAYERSTATE_NORMAL;
	g_player.nLife = PLAYER_LIFE;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, PLAYER_TEXTURE_NAME, &g_pTexturePlayer);

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
	pVtx[0].pos = D3DXVECTOR3(610.0f, 665.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(660.0f, 665.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(610.0f, 715.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(660.0f, 715.0f, 0.0f);

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
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

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

	switch (g_player.state)
	{
	case PLAYERSTATE_NORMAL:
		break;

	case PLAYERSTATE_DAMADE:
		g_player.nCounterState--;
		if (g_player.nCounterState <= 0)
		{
			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			//�|���S���̐F�ݒ�
			pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
			pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
			pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
			pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffPlayer->Unlock();

			g_player.state = PLAYERSTATE_NORMAL;
		}
		break;

	case PLAYERSTATE_DEATH:
		g_player.nCounterState--;
		
		return;
		break;
	}

	//g_nCounterAnim++;		
	
	//�J�E���^�[���Z
	//if ((g_nCounterAnim % 5) == 0)
	//{	//�|���S���̑���
	//	g_nPatternAnim = (g_nPatternAnim + 1) % PLAYER_TEX_PATTAERN;		//�p�^�[��No.�X�V
	//}

	//�ʒu�̍X�V
	/*g_posPolygon += g_movePolygon;
	g_posPolygon -= g_movePolygon;*/

	if (GetKeyboardPress(DIK_A) == true)
	{	//�C�ӂ̃L�[�iA�L�[�j�������ꂽ�Ƃ��A��
		g_player.move.x += sinf(D3DX_PI * -0.5f) * PLAYER_SPEED;
		g_player.move.y += cosf(D3DX_PI * -0.5f) * PLAYER_SPEED;

		if (GetKeyboardPress(DIK_W) == true)
		{	//����ړ�
			g_player.move.x += sinf(D3DX_PI * -0.75f) * PLAYER_SPEED;
			g_player.move.y += cosf(D3DX_PI * -0.75f) * PLAYER_SPEED;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{	//�����ړ�
			g_player.move.x += sinf(D3DX_PI * -0.25f) * PLAYER_SPEED;
			g_player.move.y += cosf(D3DX_PI * -0.25f) * PLAYER_SPEED;
		}
		else
		{	//���ړ�
			g_player.move.x += sinf(D3DX_PI * -0.5f) * PLAYER_SPEED;
			g_player.move.y += cosf(D3DX_PI * -0.5f) * PLAYER_SPEED;
		}
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{	//�C�ӂ̃L�[�iD�L�[�j�������ꂽ�Ƃ��A�E
		g_player.move.x += sinf(D3DX_PI * 0.5f) * PLAYER_SPEED;
		g_player.move.y += cosf(D3DX_PI * 0.5f) * PLAYER_SPEED;

		if (GetKeyboardPress(DIK_W) == true)
		{	//�E��ړ�
			g_player.move.x += sinf(D3DX_PI * 0.75f) * PLAYER_SPEED;
			g_player.move.y += cosf(D3DX_PI * 0.75f) * PLAYER_SPEED;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{	//�E���ړ�
			g_player.move.x += sinf(D3DX_PI * 0.25f) * PLAYER_SPEED;
			g_player.move.y += cosf(D3DX_PI * 0.25f) * PLAYER_SPEED;
		}
		else
		{	//�E�ړ�
			g_player.move.x += sinf(D3DX_PI * 0.5f) * PLAYER_SPEED;
			g_player.move.y += cosf(D3DX_PI * 0.5f) * PLAYER_SPEED;
		}
	}
	else if (GetKeyboardPress(DIK_W) == true)
	{	//�C�ӂ̃L�[�iW�L�[�j�������ꂽ�Ƃ��A��
		g_player.move.x += sinf(D3DX_PI) * PLAYER_SPEED;
		g_player.move.y += cosf(D3DX_PI) * PLAYER_SPEED;
	}
	else if (GetKeyboardPress(DIK_S) == true)
	{	//�C�ӂ̃L�[�iS�L�[�j�������ꂽ�Ƃ��A��
		g_player.move.x += sinf(0.0f) * PLAYER_SPEED;
		g_player.move.y += cosf(0.0f) * PLAYER_SPEED;
	}

	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{	//�C�ӂ̃L�[�iSPACE�L�[�j�������ꂽ�Ƃ��A��
		SetBullet(g_player.pos, D3DXVECTOR3(sinf(D3DX_PI) * PLAYER_SPEED, cosf(D3DX_PI) * 10.0f, 0.0f),BULLETTYPE_PLAYER);	//����
		SetBullet(g_player.pos, D3DXVECTOR3(sinf(2.0f) * PLAYER_SPEED, cosf(2.0f) * 20.0f, 0.0f), BULLETTYPE_PLAYER);					//�E��
		SetBullet(g_player.pos, D3DXVECTOR3(sinf(- 2.0f) * PLAYER_SPEED, cosf(- 2.0f) * 20.0f, 0.0f), BULLETTYPE_PLAYER);				//����
		//PlaySound(SOUND_LABEL_SE_SHOT);
	}

	//�ʒu���̍X�V
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;

	//�ړ��͈͂̔���
	if (g_player.pos.x <= 20)
	{
		g_player.pos.x = 20;
	}
	else if (g_player.pos.x + 20 > SCREEN_WIDTH)
	{
		g_player.pos.x = SCREEN_WIDTH - 20;
	}

	if (g_player.pos.y <= 20)
	{
		g_player.pos.y = 20;
	}
	else if (g_player.pos.y + 20 > SCREEN_HEIGHT)
	{
		g_player.pos.y = SCREEN_HEIGHT - 20;
	}

	//�����̃X�s�[�h
	g_player.move.x += (0.0f - g_player.move.x) * 0.3f;
	g_player.move.y += (0.0f - g_player.move.y) * 0.3f;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//�|���S���̍��W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - 20, g_player.pos.y - 20, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + 20, g_player.pos.y - 20, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - 20, g_player.pos.y + 20, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + 20, g_player.pos.y + 20, 0.0f);

	//�_���\�W�̐F�ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`���̍��W�ݒ�
	//pVtx[0].tex = D3DXVECTOR2((g_nPatternAnim % 5) * 0.2f, 0.5f * (g_nPatternAnim / 5));
	//pVtx[1].tex = D3DXVECTOR2((g_nPatternAnim % 5)* 0.2f + 0.2f, 0.5f * (g_nPatternAnim / 5));
	//pVtx[2].tex = D3DXVECTOR2((g_nPatternAnim % 5)* 0.2f, 0.5f * (g_nPatternAnim / 5) + 0.5f);
	//pVtx[3].tex = D3DXVECTOR2((g_nPatternAnim % 5) * 0.2f + 0.2f, 0.5f * (g_nPatternAnim / 5) + 0.5f);

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
		pDevice ->SetFVF(FVF_VERTEX_2D);	

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePlayer);
	
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
	}
}

//=============================================================================
// �v���C���[�̃_���[�W���
//=============================================================================
void HitPlayer(int nDamage)
{
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	g_player.nLife -= nDamage;
	SetLife(g_player.nLife);

	if (g_player.nLife <= 0)
	{	//���C�t��0�ɂȂ�����
		SetExplosion(g_player.pos, D3DXCOLOR(0.5f, 0.4f, 0.9f, 1.0f));
		g_player.bDisp = false;
		g_player.state = PLAYERSTATE_DEATH;
		g_player.nCounterState = 5;
		SetGameState(GAMESTATE_OVER);
	}
	else
	{	//���C�t���c���Ă���
		g_player.state = PLAYERSTATE_DAMADE;
		g_player.nCounterState = DAMAGE_STATE;		//�_���[�W��Ԃ̎���

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			//�_���\�W�̐F�ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPlayer->Unlock();
	}
}

//=============================================================================
// �v���C���[�̎擾
//=============================================================================
Player *GetPlayer(void)
{
	return &g_player;
}
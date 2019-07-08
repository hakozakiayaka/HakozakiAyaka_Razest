//=============================================================================
//
// e [bullet.cpp]
// Author :  ú±ÊÔ
//
//=============================================================================
#include "bullet.h"
#include "input.h"
#include"main.h"
#include"player.h"
#include"explosion.h"
#include"enemy.h"
#include "effect.h"
#include "sound.h"

//=============================================================================
// }Nè`
//=============================================================================
#define MAX_BULLET								(300)									// eÌÅå
#define LIFE												(50)										//eÌò£
#define POLYGON_RANGE							(30)										//eªGÉ½éÆ«ÌÍÍ
#define BULLET_TEXTURE_NAME "data/TEXTURE/bullet002.png"	//eNX`Ì¼O

//=============================================================================
// \¢Ìè`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;		//Êu
	D3DXVECTOR3 move;		//Ú®Ê
	int nLife;							//õ½
	BULLETTYPE type;			//eÌíÞ
	bool bUse;						//gpµÄ¢é©Ç¤©
} Bullet;

//=============================================================================
// O[oÏé¾
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureBullet = NULL;				// eNX`ÖÌ|C^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;		// ¸_obt@ÖÌ|C^
Bullet g_aBullet[MAX_BULLET];												//eÌîñ

//=============================================================================
// eÌú»
//=============================================================================
void InitBullet(void)
{
	VERTEX_2D * pVtx;		//¸_îñÖÌ|C^
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	// foCXÌæ¾
	pDevice = GetDevice();

	// eÌîñÌú»
	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].bUse = false;
	}

	// eNX`ÌÇÝÝ
	D3DXCreateTextureFromFile(pDevice, BULLET_TEXTURE_NAME, &g_pTextureBullet);

	// ¸_îñÌì¬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	//¸_obt@ðbNµA¸_f[^ÖÌ|C^ðæ¾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//eÌÀWÝè
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);

		//rhwÌÝè
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//|SÌFÝè
		pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

		//eNX`ÌÀWÝè
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//¸_f[^Ì|C^ð4Âªißé
	}

	//¸_obt@ðAbN·é
	g_pVtxBuffBullet->Unlock();
}

//=============================================================================
// eÌI¹
//=============================================================================
void UninitBullet(void)
{
	// eNX`ÌJú
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	// ¸_obt@ÌJú
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//=============================================================================
// eÌXV
//=============================================================================
void UpdateBullet(void)
{
	int nCntBullet;
	VERTEX_2D * pVtx;		//¸_îñÖÌ|C^

	//¸_obt@ðbNµA¸_f[^ÖÌ|C^ðæ¾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{	//eªgp³êÄ¢é
			int nCntEnemy;
			Enemy * pEnemy;

			//eÌÊuðÚ®³¹é
			//g_aBullet[nCntBullet].pos -= D3DXVECTOR3(0.0f,10.0f,0.0f);
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;

			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{	//vC[Ìe
				//GÌæ¾
				pEnemy = GetEnemy();
				SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(0.0f, 0.3f, 0.5f, 1.0f), 20.0f, 20);

				for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					if (pEnemy->bUse == true)
					{	//Gªgp³êÄ¢é
						if (g_aBullet[nCntBullet].pos.x > pEnemy->pos.x - POLYGON_RANGE 
							&& g_aBullet[nCntBullet].pos.x < pEnemy->pos.x + POLYGON_RANGE 
							&& g_aBullet[nCntBullet].pos.y > pEnemy->pos.y - POLYGON_RANGE 
							&& g_aBullet[nCntBullet].pos.y < pEnemy->pos.y + POLYGON_RANGE)
						{	//½è»è
							HitEnemy(nCntEnemy, 1);
							PlaySound(SOUND_LABEL_SE_HIT000);
							g_aBullet[nCntBullet].bUse = false;	//gpµÄ¢È¢óÔÉ·é
						}
					}
				}
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
			{	//GÌe
				Player * pPlayer;

				//vC[Ìæ¾
				pPlayer = GetPlayer();
				SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 16.0f, 10);

				if (pPlayer ->state == PLAYERSTATE_NORMAL)
				{
					if (g_aBullet[nCntBullet].pos.x > pPlayer->pos.x - POLYGON_RANGE
						&& g_aBullet[nCntBullet].pos.x < pPlayer->pos.x + POLYGON_RANGE
						&& g_aBullet[nCntBullet].pos.y > pPlayer->pos.y - POLYGON_RANGE
						&& g_aBullet[nCntBullet].pos.y < pPlayer->pos.y + POLYGON_RANGE)
					{	//½è»è
						HitPlayer(1); 

						PlaySound(SOUND_LABEL_SE_HIT001);
						g_aBullet[nCntBullet].bUse = false;	//gpµÄ¢È¢óÔÉ·é
					}
				}
			}

			//eÌå«³ÀWÝè
			pVtx[nCntBullet * 4].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x -10, g_aBullet[nCntBullet].pos.y -10 ,0.0f);
			pVtx[nCntBullet * 4 + 1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x +10, g_aBullet[nCntBullet].pos.y -10, 0.0f);
			pVtx[nCntBullet * 4 + 2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x -10, g_aBullet[nCntBullet].pos.y +10, 0.0f);
			pVtx[nCntBullet * 4 + 3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x +10, g_aBullet[nCntBullet].pos.y + 10, 0.0f);

			if (30 + g_aBullet[nCntBullet].pos.y < 0 || 30 -  g_aBullet[nCntBullet].pos.y > SCREEN_HEIGHT)
			{
				g_aBullet[nCntBullet].bUse = false;	//gpµÄ¢È¢óÔÉ·é
			}

			//êèÔoß
			g_aBullet[nCntBullet].nLife--;
			if (g_aBullet[nCntBullet].nLife <= 0)
			{
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				g_aBullet[nCntBullet].bUse = false;
			}
		}
	}
	//¸_obt@ðAbN·é
	g_pVtxBuffBullet->Unlock();
}

//=============================================================================
// eÌ`æ
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	// foCXÌæ¾
	pDevice = GetDevice();

	// ¸_obt@ðfoCXÌf[^Xg[ÉoCh
    pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	// ¸_tH[}bgÌÝè
	pDevice->SetFVF(FVF_VERTEX_2D);

	// eNX`ÌÝè
	pDevice->SetTexture(0, g_pTextureBullet);

	// |SÌ`æ
	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBullet,  2);
		}
	}
}

//=============================================================================
// eÌÝè
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move ,BULLETTYPE type)
{
	int nCntBullet;
	VERTEX_2D * pVtx;		//¸_îñÖÌ|C^

	//¸_obt@ðbNµA¸_f[^ÖÌ|C^ðæ¾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			g_aBullet[nCntBullet].pos = pos;
			//eÌå«³ÀWÝè
			pVtx[nCntBullet * 4].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10, g_aBullet[nCntBullet].pos.y - 10, 0.0f);
			pVtx[nCntBullet * 4 + 1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10, g_aBullet[nCntBullet].pos.y - 10, 0.0f);
			pVtx[nCntBullet * 4 + 2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10, g_aBullet[nCntBullet].pos.y + 10, 0.0f);
			pVtx[nCntBullet * 4 + 3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10, g_aBullet[nCntBullet].pos.y + 10, 0.0f);

			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].type = type;
			g_aBullet[nCntBullet].bUse = true;	//gpµÄ¢éóÔÉ·é
			g_aBullet[nCntBullet].nLife = LIFE;
			break;													//K¸Kv
		}
	}
	//¸_obt@ðAbN·é
	g_pVtxBuffBullet->Unlock();
}
//=============================================================================
//
// G [enemy.cpp]
// Author :  ú±ÊÔ
//
//=============================================================================
#include "enemy.h"
#include"main.h"
#include"explosion.h"
#include"bullet.h"
#include "game.h"
#include "score.h"
#include "effect.h"
#include "player.h"
#include "sound.h"

//=============================================================================
// }Nè`
//=============================================================================
#define MAX_TYPE_ENEMY		(4)												// GÌíÞ
#define DAMAGE_STATE			(5)												//_[WóÔ
#define ENEMY_LIFE					(5)												//GÌCt
#define TEX_PATTAERN				(2)												//p^[
#define TEXTURE_NAME "data/TEXTURE/monster000_1.png"		//eNX`Ì¼O
#define TEXTURE_NAME2 "data/TEXTURE/monster001_1.png"		//eNX`Ì¼O
#define TEXTURE_NAME3 "data/TEXTURE/monster002_1.png"		//eNX`Ì¼O
#define TEXTURE_NAME4 "data/TEXTURE/monster003_1.png"		//eNX`Ì¼O

//=============================================================================
// O[oÏé¾
//=============================================================================
LPDIRECT3DTEXTURE9		g_apTextureEnemy[MAX_TYPE_ENEMY] = {};	// eNX`ÖÌ|C^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;							// ¸_obt@ÖÌ|C^
Enemy g_aEnemy[MAX_ENEMY];																	//GÌîñ
int g_nNumEnemy;																							//GÌ

//=============================================================================
// GÌú»
//=============================================================================
void InitEnemy(void)
{
	// ¸_îñÌì¬
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	// foCXÌæ¾
	pDevice = GetDevice();

	// GÌîñÌú»
	for(int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nType = 0;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
		g_aEnemy[nCntEnemy].nCounterState = 0;
		g_aEnemy[nCntEnemy].nLife = 1;
		g_aEnemy[nCntEnemy].nCntAnim = 0;
		g_aEnemy[nCntEnemy].nPatternAnim = 0;
		g_aEnemy[nCntEnemy].nCntMove = 0;
		g_aEnemy[nCntEnemy].nChangeMove = 0;
		g_aEnemy[nCntEnemy].bUse = false;
	}

	// eNX`ÌÇÝÝ(SÌª)
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_apTextureEnemy[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME2, &g_apTextureEnemy[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME3, &g_apTextureEnemy[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME4, &g_apTextureEnemy[3]);

	// ¸_obt@ð¶¬
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffEnemy,
									NULL);

	// ¸_obt@ðbNµA¸_îñÖÌ|C^ðæ¾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//|SÌÀWÝè
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
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);

		pVtx += 4;	//¸_f[^Ì|C^ð4Âªißé
	}

	g_nNumEnemy = 0;		//GÌðNA

	// ¸_obt@ðAbN·é
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
// GÌI¹
//=============================================================================
void UninitEnemy(void)
{
	int nCntTex;

	// eNX`ÌJú
	for(nCntTex = 0; nCntTex < MAX_TYPE_ENEMY; nCntTex++)
	{
		if (g_apTextureEnemy[nCntTex] != NULL)
		{
			g_apTextureEnemy[nCntTex]->Release();
			g_apTextureEnemy[nCntTex] = NULL;
		}
	}

	// ¸_obt@ÌJú
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//=============================================================================
// GÌXV
//=============================================================================
void UpdateEnemy(void)
{
	VERTEX_2D * pVtx;		//¸_îñÖÌ|C^
	int nCntEnemy = 0;
	float fMoveX = 0;		//pxðßé½ßÌX
	float fMoveY = 0;		//pxðßé½ßÌY
	float fangle = 0;			//pxðßé
	float fMoveX2 = 0;		//XÌÚ®Ê
	float fMoveY2 = 0;		//YÌÚ®Ê

	//¸_obt@ðbNµA¸_f[^ÖÌ|C^ðæ¾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{	
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			//|SÌÀWÝè
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 25, g_aEnemy[nCntEnemy].pos.y - 25, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 25, g_aEnemy[nCntEnemy].pos.y - 25, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 25, g_aEnemy[nCntEnemy].pos.y + 25, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 25, g_aEnemy[nCntEnemy].pos.y + 25, 0.0f);

			g_aEnemy[nCntEnemy].nCntAnim++;				//JE^[ÁZ
			if ((g_aEnemy[nCntEnemy].nCntAnim % 40) == 0)
			{	//|SÌ¬³
				g_aEnemy[nCntEnemy].nPatternAnim = (g_aEnemy[nCntEnemy].nPatternAnim + 1) % 2;		//p^[No.XV
			}

			//eNX`ÌÀWÝè
			pVtx[0].tex = D3DXVECTOR2((g_aEnemy[nCntEnemy].nPatternAnim) * 0.5f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2((g_aEnemy[nCntEnemy].nPatternAnim) * 0.5f + 0.5f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2((g_aEnemy[nCntEnemy].nPatternAnim) * 0.5f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2((g_aEnemy[nCntEnemy].nPatternAnim) * 0.5f + 0.5f, 1.0f);
		}
		pVtx += 4;	//¸_f[^Ì|C^ð4Âªißé
	}

	//¸_obt@ðAbN·é
	g_pVtxBuffEnemy->Unlock();
	
	//¸_obt@ðbNµA¸_f[^ÖÌ|C^ðæ¾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{	//Gªgp³êÄ¢é
			//g_aEnemy[nCntEnemy].nCntBullet++;

			if (g_aEnemy[nCntEnemy].nCntMove > 150 || g_aEnemy[nCntEnemy].nCntMove < -150)
			{
				g_aEnemy[nCntEnemy].nChangeMove *= -1;
			}

			g_aEnemy[nCntEnemy].nCntMove += g_aEnemy[nCntEnemy].nChangeMove;
			g_aEnemy[nCntEnemy].pos.x += g_aEnemy[nCntEnemy].nChangeMove;

			switch (g_aEnemy[nCntEnemy].state)
			{	//GÌóÔmF
			case ENEMYSTATE_NORMAL:	//GªÊíóÔÌ
				//êèÔoß
				if ((rand() % 600) == 0)
				{	//êèÔÉÈÁ½çGÍeðÁÄ­é
					//vC[ðæ¾
					Player * pPlayer;
					pPlayer = GetPlayer();

					//GÌeªvC[Éü©ÁÄÁÄ­é
					fMoveX = pPlayer->pos.x - g_aEnemy[nCntEnemy].pos.x;		//pxÌXðßé
					fMoveY = pPlayer->pos.y - g_aEnemy[nCntEnemy].pos.y;		//pxÌYðßé
					fangle = atan2f(fMoveX,fMoveY);												//pxßé

					fMoveX2 = sinf(fangle) * 10.0f;
					fMoveY2 = cosf(fangle) * 10.0f;

					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(fMoveX2,fMoveY2, 0.0f),BULLETTYPE_ENEMY);
				}
				break;

			case ENEMYSTATE_DAMADE:	//Gª_[Wðó¯½
				g_aEnemy[nCntEnemy].nCounterState--;
				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{	//_[WóÔªIíÁ½çAÌÍcÁÄé
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;

					//GÌ_\WFÝè
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}	
				break;
			}
		}
		pVtx += 4;	//¸_f[^Ì|C^ð4Âªißé
	}
	//¸_obt@ðAbN·é
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
// GÌ`æ
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// foCXÌæ¾
	pDevice = GetDevice();

	// ¸_obt@ðfoCXÌf[^Xg[ÉoCh
    pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	// ¸_tH[}bgÌÝè
	pDevice->SetFVF(FVF_VERTEX_2D);

	// |SÌ`æ
	for(int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{	//Gªgp³êÄ¢é
			//eNX`ÌÝè
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);

			//|SÌ`æ
 			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntEnemy, 2);
		}
	}
}

//=============================================================================
// GÌÝè
//=============================================================================
void SetEnemy(D3DXVECTOR3 pos, int nType, int ChangeMove)
{
	int nCntEnemy;
	VERTEX_2D * pVtx;		//¸_îñÖÌ|C^
	
	//¸_obt@ðbNµA¸_f[^ÖÌ|C^ðæ¾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{	//Gªgp³êÄ¢È¢
			//GÌÀWÝè
			g_aEnemy[nCntEnemy].pos = pos;
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 25, g_aEnemy[nCntEnemy].pos.y - 25, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 25, g_aEnemy[nCntEnemy].pos.y - 25, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 25, g_aEnemy[nCntEnemy].pos.y + 25, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 25, g_aEnemy[nCntEnemy].pos.y + 25, 0.0f);

			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
			g_aEnemy[nCntEnemy].nCounterState = 0;
			g_aEnemy[nCntEnemy].nCntAnim = 0;
			g_aEnemy[nCntEnemy].nPatternAnim = 0;
			g_aEnemy[nCntEnemy].nLife = ENEMY_LIFE;
			g_aEnemy[nCntEnemy].nCntMove = 0;
			g_aEnemy[nCntEnemy].nChangeMove = ChangeMove;
			g_aEnemy[nCntEnemy].bUse = true;	//gpµÄ¢éóÔÉ·é
			g_nNumEnemy++;								//GÌðÁZ·é
			break;													//K¸Kv
		}

		pVtx += 4;	//¸_f[^Ì|C^ð4Âªißé
	}

	//¸_obt@ðAbN·é
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
// GÌæ¾
//=============================================================================
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];
}

//=============================================================================
// GÌ_[W
//=============================================================================
void HitEnemy(int nCntEnemy,int nDamage)
{
	VERTEX_2D * pVtx;		//¸_îñÖÌ|C^

	g_aEnemy[nCntEnemy].nLife -= nDamage;
	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{	//Ctª0ÉÈÁ½ç
		PlaySound(SOUND_LABEL_SE_EXPLOSION);
		if (g_aEnemy[nCntEnemy].nType == 0)
		{	//«¢ëÌ­ÌF
			SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(0.9f, 0.4f, 0.1f, 0.7f));
			AddScore(8000);
			g_aEnemy[nCntEnemy].bUse = false;
		}
		else if (g_aEnemy[nCntEnemy].nType == 1)
		{	//Ý¸¢ëÌ­ÌF
			SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(0.1f, 0.4f, 0.4f, 0.7f));
			AddScore(6000);
			g_aEnemy[nCntEnemy].bUse = false;
		}
		else if (g_aEnemy[nCntEnemy].nType == 2)
		{	//Þç³«Ì­ÌF
			SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(0.6f, 0.1f, 0.8f, 0.7f));
			AddScore(4000);
			g_aEnemy[nCntEnemy].bUse = false;
		}
		else if (g_aEnemy[nCntEnemy].nType == 3)
		{	//«ÝÇèÌ­ÌF
			SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(0.1f, 0.7f, 0.3f, 0.7f));
			AddScore(2000);
			g_aEnemy[nCntEnemy].bUse = false;
		}

		g_nNumEnemy--;
		if (g_nNumEnemy <= 0)
		{	//GªSÅµ½ç
			SetGameState(GAMESTATE_CLEAR);
		}
	}
	else
	{	//CtªcÁÄ½ç
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMADE;
		g_aEnemy[nCntEnemy].nCounterState = DAMAGE_STATE;		//_[WóÔÌÔ

		//¸_obt@ðbNµA¸_f[^ÖÌ|C^ðæ¾
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		if (g_aEnemy[nCntEnemy].nType == 0)
		{	//Gr¿áñÌ_[WÌF
			//_[WÌFÝè
			pVtx[nCntEnemy * 4].col = D3DXCOLOR(0, 0.5f, 1.0f, 1.0f);
			pVtx[nCntEnemy * 4 + 1].col = D3DXCOLOR(0, 0.5f, 1.0f, 1.0f);
			pVtx[nCntEnemy * 4 + 2].col = D3DXCOLOR(0, 0.5f, 1.0f, 1.0f);
			pVtx[nCntEnemy * 4 + 3].col = D3DXCOLOR(0, 0.5f, 1.0f, 1.0f);
		}
		else
		{	//»Ì¼ÌG
			//_[WÌFÝè
			pVtx[nCntEnemy * 4].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
			pVtx[nCntEnemy * 4 + 1].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
			pVtx[nCntEnemy * 4 + 2].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
			pVtx[nCntEnemy * 4 + 3].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
		}

		//¸_obt@ðAbN·é
		g_pVtxBuffEnemy->Unlock();
	}
}

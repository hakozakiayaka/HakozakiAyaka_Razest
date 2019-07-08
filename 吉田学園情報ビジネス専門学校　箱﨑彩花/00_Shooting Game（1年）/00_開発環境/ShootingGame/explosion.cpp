//=============================================================================
//
// ­Ì [explosion.cpp]
// Author :  ú±ÊÔ
//
//=============================================================================
#include "bullet.h"
#include "input.h"
#include"main.h"
#include"player.h"
#include"explosion.h"
#include "sound.h"

//=============================================================================
// }Nè`
//=============================================================================
#define	MAX_EXPLOSION		(128)											// ­ÌÅå 
#define EXPLOSION_SPEED		(4)												//­Ì¬³
#define TEXTURE_NAME "data/TEXTURE/explosion000.png"		//eNX`Ì¼O

//=============================================================================
// \¢Ìè`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;		//Êu
	D3DXCOLOR col;				//F
	int nCounterAnim;			//Aj[VJE^[
	int nPatternAnim;			//Aj[VNo.
	bool bUse;						//gpµÄ¢é©Ç¤©
} Explosion;

//=============================================================================
// O[oÏé¾
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureExplosion = NULL;			// eNX`ÖÌ|C^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;		// ¸_obt@ÖÌ|C^
Explosion g_aExplosion[MAX_EXPLOSION];									//­Ìîñ

//=============================================================================
// ­Ìú»
//=============================================================================
void InitExplosion(void)
{
	VERTEX_2D * pVtx;		//¸_îñÖÌ|C^
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;

	// foCXÌæ¾
	pDevice = GetDevice();

	// ­ÌîñÌú»
	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		g_aExplosion[nCntExplosion].nCounterAnim = 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
		g_aExplosion[nCntExplosion].bUse = false;
	}

	// eNX`ÌÇÝÝ
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_pTextureExplosion);

	// ¸_îñÌì¬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	//¸_obt@ðbNµA¸_f[^ÖÌ|C^ðæ¾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
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
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//¸_f[^Ì|C^ð4Âªißé
	}

	//¸_obt@ðAbN·é
	g_pVtxBuffExplosion->Unlock();
}

//=============================================================================
// ­ÌI¹
//=============================================================================
void UninitExplosion(void)
{
	// eNX`ÌJú
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	// ¸_obt@ÌJú
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//=============================================================================
// ­ÌXV
//=============================================================================
void UpdateExplosion(void)
{
	int nCntExplosion;
	VERTEX_2D * pVtx;		//¸_îñÖÌ|C^

	//¸_obt@ðbNµA¸_f[^ÖÌ|C^ðæ¾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{	//eªgp³êÄ¢é
			//JE^[ÁZ
			g_aExplosion[nCntExplosion].nCounterAnim++;	

			if ((g_aExplosion[nCntExplosion].nCounterAnim % EXPLOSION_SPEED) == 0)
			{	//­Ì¬³
				g_aExplosion[nCntExplosion].nPatternAnim ++;		//p^[No.XV
			}

			//­ÌÀWÝè
			pVtx[nCntExplosion * 4].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x -10, g_aExplosion[nCntExplosion].pos.y -10, 0.0f);
			pVtx[nCntExplosion * 4 + 1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 50, g_aExplosion[nCntExplosion].pos.y - 10, 0.0f);
			pVtx[nCntExplosion * 4 + 2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 10, g_aExplosion[nCntExplosion].pos.y + 50, 0.0f);
			pVtx[nCntExplosion * 4 + 3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 50, g_aExplosion[nCntExplosion].pos.y + 50, 0.0f);

			//eNX`ÌÀWÝè
			pVtx[nCntExplosion * 4].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim  * 0.125f) + 0.0f, 0.0f);
			pVtx[nCntExplosion * 4 + 1].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.125f) + 0.125f, 0.0f);
			pVtx[nCntExplosion * 4 + 2].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.125f) + 0.0f, 1.0f);
			pVtx[nCntExplosion * 4 + 3].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim *0.125f) + 0.125f, 1.0f);

			if (g_aExplosion[nCntExplosion].pos.y + 30 < 0 || g_aExplosion[nCntExplosion] .nPatternAnim > 7)
			{
				g_aExplosion[nCntExplosion].bUse = false;	//gpµÄ¢È¢óÔÉ·é
			}
		}
	}
	//¸_obt@ðAbN·é
	g_pVtxBuffExplosion->Unlock();
}

//=============================================================================
// ­Ì`æ
//=============================================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;

	// foCXÌæ¾
	pDevice = GetDevice();

	// ¸_obt@ðfoCXÌf[^Xg[ÉoCh
    pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

	// ¸_tH[}bgÌÝè
	pDevice->SetFVF(FVF_VERTEX_2D);

	// eNX`ÌÝè
	pDevice->SetTexture(0, g_pTextureExplosion);

	// |SÌ`æ
	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntExplosion,  2);
		}
	}
}

//=============================================================================
// ­ÌÝè
//=============================================================================
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	int nCntExplosion;
	VERTEX_2D * pVtx;		//¸_îñÖÌ|C^

	//¸_obt@ðbNµA¸_f[^ÖÌ|C^ðæ¾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{
			//­ÌÀWÝè
			g_aExplosion[nCntExplosion].pos = pos;
			pVtx[nCntExplosion * 4].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 10, g_aExplosion[nCntExplosion].pos.y - 10, 0.0f);
			pVtx[nCntExplosion * 4 + 1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 50, g_aExplosion[nCntExplosion].pos.y - 10, 0.0f);
			pVtx[nCntExplosion * 4 + 2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 10, g_aExplosion[nCntExplosion].pos.y + 50, 0.0f);
			pVtx[nCntExplosion * 4 + 3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 50, g_aExplosion[nCntExplosion].pos.y + 50, 0.0f);

			//­ÌFÝè
			g_aExplosion[nCntExplosion].col = col;
			pVtx[nCntExplosion * 4].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[nCntExplosion * 4 + 1].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[nCntExplosion * 4 + 2].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[nCntExplosion * 4 + 3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);

			g_aExplosion[nCntExplosion].nCounterAnim = 0;

			//eNX`ÌÀWÝè
			g_aExplosion[nCntExplosion].nPatternAnim = 0;
			pVtx[nCntExplosion * 4].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[nCntExplosion * 4 + 1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[nCntExplosion * 4 + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[nCntExplosion * 4 + 3].tex = D3DXVECTOR2(1.0f, 1.0f);

			g_aExplosion[nCntExplosion].bUse = true;	//gpµÄ¢éóÔÉ·é
			break;																//K¸Kv
		}
	}
	//¸_obt@ðAbN·é
	g_pVtxBuffExplosion->Unlock();
}
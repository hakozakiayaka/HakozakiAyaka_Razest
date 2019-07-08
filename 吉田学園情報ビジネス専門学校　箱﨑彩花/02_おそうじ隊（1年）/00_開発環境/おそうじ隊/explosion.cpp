//=============================================================================
//
// ­Ì [explosion.cpp]
// Author :  ú±ÊÔ
//
//=============================================================================
#include "bullet.h"
#include "input.h"
#include"main.h"
#include"explosion.h"
#include "player.h"
#include "shadow.h"

//=============================================================================
// }Nè`
//=============================================================================
#define EXPLOSION_TEX "data/TEXTURE/explosion002.png"			//eNX`Ì¼O
#define MAX_EXPLOSION			(300)												// ­ÌÅå 
#define EXPLOSION_SPEED		(4)													//­Ì¬³
#define EXPLOSION_SIZE			(15.0f)												//­Ìå«³

//*****************************************************************************
// vg^Cvé¾
//*****************************************************************************
void MakeVertexExplosion(LPDIRECT3DDEVICE9 pDevice);

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
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntExplosion;

	// ­ÌîñÌú»
	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		g_aExplosion[nCntExplosion].nCounterAnim = 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
		g_aExplosion[nCntExplosion].bUse = false;
	}

	// ¸_îñÌì¬
	MakeVertexExplosion(pDevice);
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
	VERTEX_3D * pVtx;			//¸_îñÌ|C^
	int nCntExplosion;

	//¸_obt@ðbNµA¸_f[^ÖÌ|C^ðæ¾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{	//eªgp³êÄ¢é
			//JE^[ÁZ
			g_aExplosion[nCntExplosion].nCounterAnim++;

			if ((g_aExplosion[nCntExplosion].nCounterAnim % EXPLOSION_SPEED) == 0)
			{	//­Ì¬³
				g_aExplosion[nCntExplosion].nPatternAnim++;		//p^[No.XV
			}

			//eNX`ÌÀWÝè
			pVtx[0].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim  * 0.125f) + 0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.125f) + 0.125f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.125f) + 0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim *0.125f) + 0.125f, 1.0f);

			if (g_aExplosion[nCntExplosion].pos.y + 30 < 0 || g_aExplosion[nCntExplosion] .nPatternAnim > 7)
			{
				g_aExplosion[nCntExplosion].bUse = false;	//gpµÄ¢È¢óÔÉ·é
			}
		}

		pVtx += 4;
	}

	//¸_obt@ðAbN·é
	g_pVtxBuffExplosion->Unlock();
}

//=============================================================================
// ­Ì`æ
//=============================================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxView;			//vZp}gbNX
	int nCntExplosion;

	//_[Xe[gÌÝè
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//ZeXg
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			// [h}gbNXÌú»
			D3DXMatrixIdentity(&g_aExplosion[nCntExplosion].mtxWorldBullet);

			//r[}gbNXðæ¾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//tsñÌÝè
			g_aExplosion[nCntExplosion].mtxWorldBullet._11 = mtxView._11;
			g_aExplosion[nCntExplosion].mtxWorldBullet._12 = mtxView._21;
			g_aExplosion[nCntExplosion].mtxWorldBullet._13 = mtxView._31;
			g_aExplosion[nCntExplosion].mtxWorldBullet._21 = mtxView._12;
			g_aExplosion[nCntExplosion].mtxWorldBullet._22 = mtxView._22;
			g_aExplosion[nCntExplosion].mtxWorldBullet._23 = mtxView._32;
			g_aExplosion[nCntExplosion].mtxWorldBullet._31 = mtxView._13;
			g_aExplosion[nCntExplosion].mtxWorldBullet._32 = mtxView._23;
			g_aExplosion[nCntExplosion].mtxWorldBullet._33 = mtxView._33;

			// Êuð½f
			D3DXMatrixTranslation(&mtxTrans, g_aExplosion[nCntExplosion].pos.x, g_aExplosion[nCntExplosion].pos.y, g_aExplosion[nCntExplosion].pos.z);
			D3DXMatrixMultiply(&g_aExplosion[nCntExplosion].mtxWorldBullet, &g_aExplosion[nCntExplosion].mtxWorldBullet, &mtxTrans);

			// [h}gbNXÌÝè
			pDevice->SetTransform(D3DTS_WORLD, &g_aExplosion[nCntExplosion].mtxWorldBullet);

			// ¸_obt@ðf[^Xg[ÉÝè
			pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_3D));

			// ¸_tH[}bgÌÝè
			pDevice->SetFVF(FVF_VERTEX_3D);

			// eNX`ÌÝè
			pDevice->SetTexture(0, g_pTextureExplosion);

			// |SÌ`æ
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntExplosion * 4, 2);
		}
	}

	//_[Xe[gÌÝèð³Éß·
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//ZeXgð³Éß·
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
}

//=============================================================================
// ¸_îñÌì¬
//=============================================================================
void MakeVertexExplosion(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D * pVtx;			//¸_îñÌ|C^
	int nCntExplosion;

	//eNX`ÌÇÝÝ
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TEX, &g_pTextureExplosion);

	// ¸_îñÌì¬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	//¸_obt@ðbNµA¸_f[^ÖÌ|C^ðæ¾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//­ÌÀWÝè
		pVtx[0].pos = D3DXVECTOR3(-EXPLOSION_SIZE, EXPLOSION_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(EXPLOSION_SIZE, EXPLOSION_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-EXPLOSION_SIZE, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(EXPLOSION_SIZE, 0.0f, 0.0f);

		//@üxNgÌÝè
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//­ÌFÝè
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

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
// ­ÌÝè
//=============================================================================
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	int nCntExplosion;
	VERTEX_3D * pVtx;		//¸_îñÖÌ|C^

	//¸_obt@ðbNµA¸_f[^ÖÌ|C^ðæ¾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{
			g_aExplosion[nCntExplosion].pos = pos;							//Êu
			g_aExplosion[nCntExplosion].col = col;								//J[
			pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);

			g_aExplosion[nCntExplosion].nCounterAnim = 0;				//Aj[VJE^[
			g_aExplosion[nCntExplosion].nPatternAnim = 0;				//Aj[VÌp^[
			g_aExplosion[nCntExplosion].bUse = true;						//gpµÄ¢éóÔÉ·é
			break;																					//K¸Kv
		}
	}

	//¸_obt@ðAbN·é
	g_pVtxBuffExplosion->Unlock();
}
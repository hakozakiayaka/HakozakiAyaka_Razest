//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 箱﨑彩花
//
//=============================================================================
#ifndef _SOUND_H_		//二重インクルード防止
#define _SOUND_H_

#include "main.h"			//メイン

//*****************************************************************************
// サウンドクラス
//*****************************************************************************
class CSound
{
public:
	//パラメータ構造体定義
	typedef struct
	{
		char *pFilename;								// ファイル名
		int nCntLoop;									// ループカウント(-1でループ再生)
	} SOUNDPARAM;

	//各素材の種類
	typedef enum
	{
		SOUND_LABEL_BGM000 = 0,		// タイトル
		SOUND_LABEL_BGM001,				// チュートリアル
		SOUND_LABEL_BGM002,				// ゲーム
		SOUND_LABEL_BGM003,				// ゲームクリア
		SOUND_LABEL_BGM004,				// ゲームオーバー
		SOUND_LABEL_BGM005,				// らんきんぐ
		SOUND_LABEL_SE_SHOT,				// 弾発射音
		SOUND_LABEL_SE_HIT000,			// ヒット音0
		SOUND_LABEL_SE_HIT001,			// ヒット音1
		SOUND_LABEL_SE_EXPLOSION,	// 爆発音
		SOUND_LABEL_SE_DECIDE,			// 決定音
		SOUND_LABEL_SE_PAUSE,			// ポーズ
		SOUND_LABEL_SE_SELECT,			// 選択音
		SOUND_LABEL_SE_JUMP,				// ジャンプ着地
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	CSound();
	~CSound();
	HRESULT Init(HWND hWnd);
	void Uninit(void);

	//静的メンバ関数
	static HRESULT PlaySound(SOUND_LABEL label);
	static void StopSound(SOUND_LABEL label);
	static void StopSound(void);

private:
	static IXAudio2 * m_pXAudio2;																		// XAudio2オブジェクトへのポインタ
	static IXAudio2MasteringVoice * m_pMasteringVoice;									// マスターボイスへのポインタ
	static IXAudio2SourceVoice * m_apSourceVoice[SOUND_LABEL_MAX];		// ソースボイスへのポインタ
	static BYTE * m_apDataAudio[SOUND_LABEL_MAX];									// オーディオデータへのポインタ
	static DWORD m_aSizeAudio[SOUND_LABEL_MAX];									// オーディオデータサイズ
};
#endif
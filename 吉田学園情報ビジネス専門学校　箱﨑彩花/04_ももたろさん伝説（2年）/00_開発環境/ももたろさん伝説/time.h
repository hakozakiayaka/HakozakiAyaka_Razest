//=============================================================================
//
// タイム処理 [time.h]
// Author : 箱﨑彩花
//
//=============================================================================
#ifndef _TIME_H_		//二重インクルード防止
#define _TIME_H_

#include	"main.h"		//メイン

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_TIME			(3)

//*****************************************************************************
// スコアクラス
//*****************************************************************************
class CTime : public CScene
{
public:
	//タイムの状態
	typedef enum
	{
		TIMESTATE_NONE = 0,
		TIMESTATE_NORMAL,											//通常状態
		TIMESTATE_FINISH,												//終了状態
		TIMESTATE_MAX
	} TIMESTATE;

	CTime();																		//コンストラクタ
	~CTime();																	//デストラクタ
	HRESULT Init(void);													//初期化処理
	void Uninit(void);															//終了処理
	void Update(void);														//更新処理
	void Draw(void);															//描画処理
	void AddTime(void);													//タイムの処理

	//静的メンバ関数
	static CTime * Create(void);										//スコアの生成

private:
	CNumber * m_apTime[MAX_TIME];
	static int m_nTime;
	static int m_nTimeData[MAX_TIME];
	int m_nTimeState;												//状態管理のカウンター
};

#endif
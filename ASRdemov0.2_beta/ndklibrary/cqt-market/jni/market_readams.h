/*** Prompter Demo Application *******************************************************************/

#ifndef __MARKET_READAMS_H__
#define __MARKET_READAMS_H__
#include "market_platform.h"
#include "market_local_data.h"

class CQTMarket_ReadAMS : public MarketInterface
{
public:
	CQTMarket_ReadAMS(PGlobalParam param);
	~CQTMarket_ReadAMS();

	//���ñ������ݽӿ�
	void AMS_SetLocalHandle(CQTLocalAppData* pLocalData);

	//��ʼ�����̣߳����ط�������Դ
	void AMS_StartService();

private:
	CQTLocalAppData* m_pCqtLocalData;

public:
	void DoRunService(JNIEnv *env);
	void GetAppClass(JNIEnv *env);
	void GetAppData(JNIEnv *env);
	void GetRecommend(JNIEnv *env);
};

#endif
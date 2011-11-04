/*** Prompter Demo Application *******************************************************************/

#ifndef __MARKET_SERVICE_H_
#define __MARKET_SERVICE_H_
#include "market_platform.h"
#include "market_service.h"
#include "market_local_data.h"
#include "market_readams.h"
#include "market_packagemanager.h"

//�ð汾���ǱȽϼ򵥣��ٶ������Ӧ�ó��򲻳���100�����������Ƶģ�
//����ǳ�����.
//1����Ҫ�ֶ�ȥȡ�������ݣ����簴25��Ϊһҳ�ӷ�����ȥȡ��
//2������˳�����Ϣ����ȫ�����浽������
class CQTMarketService: public MarketInterface
{
public:
	CQTMarketService(PGlobalParam param);
	~CQTMarketService();

	//�����̣߳�����������APP��Ϣ
	bool				CMS_StartService();

	//�õ��������ݿ���Ϣ�ı�
	CQTLocalAppData*	CMS_GetAppDataInfo() {return m_pcqtLocalAppData;};
	

public:
	CQTLocalAppData*	m_pcqtLocalAppData;
	CQTMarket_ReadAMS*  m_pcqtReadAMS;
	CQTPackManager*		m_pPackManager;

};

#endif
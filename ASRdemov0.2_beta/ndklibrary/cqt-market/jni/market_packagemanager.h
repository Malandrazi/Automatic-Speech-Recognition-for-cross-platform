/*** Prompter Demo Application *******************************************************************/

#ifndef __MARKET_PACKAGEMANAGER_H__
#define __MARKET_PACKAGEMANAGER_H__
#include "market_platform.h"
#include "market_local_data.h"

class CQTPackManager: public MarketInterface
{
public:
	CQTPackManager(PGlobalParam param);
	~CQTPackManager();
	
	//����Ӧ�ø�Ϊ�̱߳ȽϺ�
	//��Ҫһ���̲߳��ϵ�ȥɨ�谲װ״̬�������и��õİ취�������ȡϵͳ��װ����֪ͨ��Ϣ
	bool				CPM_ScanLocalPackInfo(JNIEnv *env);	
	void				CPM_ScanService();

	//��װ
	int					CPM_InstallPackageThread(JNIEnv *env,char* lpAppID);
	int					CPM_InstallPackage(char* lpAppID);

	//ж��
	int					CPM_UnintallPackageThread(JNIEnv *env,char* lpAppID);
	int					CPM_UnintallPackage(char* lpAppID);

	//����
	int					CPM_UpdatePackage(char* lpAppID);
	
	//�Ƿ���Ը���  0�����£� 1����
	int					CPM_IsUpdatePackage(char* lpAppID);

	//�Ƿ��Ѿ���װ��0û�а�װ��1�Ѿ���װ
	int					CPM_IsInstallPackage(char* lpAppID);	
	
	//���ñ�����Ϣ��
	void				CPM_SetAppDataInfo(CQTLocalAppData* pAppData) {m_pcqtLocalAppData = pAppData;};
	
	char m_szAppID[256];
private:
	CQTLocalAppData*	m_pcqtLocalAppData;		
};

#endif
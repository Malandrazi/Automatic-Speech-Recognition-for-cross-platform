/*** Prompter Demo Application *******************************************************************/

#ifndef __MARKET_LOCAL_DATA_H_
#define __MARKET_LOCAL_DATA_H_
#include "market_platform.h"
//���Ӧ�ü������ݿ����
//������demo�����ҵ��㷨�ǣ�
//1�����������صĳ�����Ϣ�����֧��100������Ʒ��ʱ����Ҫ�ĳɷ�ҳģʽ��ȡ���ݡ�
//2�����汾�ذ�װ�ĳ�����Ŀ���֧��100������Ʒ��ʱ�����ʹ�����ݿ����
//3������ȫ�������ڴ档

#define APP_USE_SIMPLE_DEMO_FILE		//ʹ���ļ�����������
//#define APP_USE_DATABASE				//ʹ�����ݿ�

#define MAX_CLASS_COUNT	20				//������
#define MAX_APP_COUNT	100				//���������
#define LOCAL_INSTALLED_CLASSID		"installlocal01"

//���������Ϣ
typedef struct __tagAppClassData
{
	char szClassID[MARKET_STRING_LARGER];			//�����ID����Ψһ��
	char szClassName[MARKET_STRING_LARGER];			//��������
	char szClassImgPath[MARKET_STRING_LARGER];		//ͼƬ��ַ	
	int  nAppCount;									//�������ĸ���
}TAppClassData,*PAppClassData;

//������Ϣ�б�
typedef struct __tagAPPBaseInfo
{
	char szClassID[MARKET_STRING_LARGER];			//�����ID����Ψһ��
	char szAppID[MARKET_STRING_LARGER];				//����ID����Ψһ�ģ�ע�⣺Ҫ���ƶ�AMS�еı����Ψһ�ġ���������Ҫ���ڿ����ߴ���Ӧ�ó����ʱ���ȷ����
	char szPlatformID[MARKET_STRING_LARGER];		//ƽ̨��ID���Ժ��Լ��滮��ƽ̨��ʱ����Ҫ���ǣ�ʲôƽ̨����Ʒ�Ƿ���Ҫ�н�����ʾ�����ԣ��������ڸ�ID�С�
	char szName[MARKET_STRING_MIN];					//����
	char szLanguage[MARKET_STRING_MIN];				//����
	char szCompany[MARKET_STRING_MIN];				//��˾
	char szDescribe[MARKET_STRING_HUGE];			//����
	char szVersion[MARKET_STRING_MIN];				//�汾
	char szIcon[MARKET_STRING_HUGE];				//iconλ��
	char szPublicDate[MARKET_STRING_MIN];			//��������
	char szPrice[MARKET_STRING_MIN];				//�۸�
	int  nStar;										//������
	int	 nDownCount;								//���ش���
}TAPPBaseInfo,*PAPPBaseInfo;

typedef struct __tagAppInstallInfo
{	
	char szAppID[MARKET_STRING_LARGER];	
	char szPackageName[MARKET_STRING_LARGER];						//��װ�İ���
	char szPackageVersion[MARKET_STRING_LARGER];					//��װʱ��İ汾����		
}TAppInstall,*PAppInstall;

typedef struct __tagCqtApp
{
	TAPPBaseInfo tAppBaseInfo;	
}TCqtApp,*PCqtApp;

//////////////////////////////////////////////////////////////////////////
//�ļ�ͷ
typedef struct __tagAppFileHead
{
	char szDescribe[MARKET_STRING_NORMAL];
	char szVersion[MARKET_STRING_MIN];
}TAppFileHead,*PAppFileHead;

#define FILE_PATH_APP_DATA	"/mnt/sdcard/cqtmarket.data"
#define APP_FILE_INFO		"CQT-MARKET Data"
#define APP_VERSION_INFO	"ver0.1"
class CQTLocalAppData: public MarketInterface
{
public:
	CQTLocalAppData(PGlobalParam param);
	~CQTLocalAppData();


	//��ʼ�����ӱ����ļ���ȡ��Ϣ
	void			CA_Init();
	void			CA_Uninit();

	int				CA_GetClassCount(){return m_nClassCount;};
	PAppClassData	CA_GetClassItem(int idx) { return m_pClassData[idx];}; 
	PAppClassData	CA_GetClassItemByID(char* lpID,int& nIdx);
	int				CA_AddClassItem(PAppClassData pItem);
	bool			CA_ModiflyClassItem(int idx, PAppClassData pItem);
	bool			CA_DeleteClassItem(int idx);//ɾ����ʱ�����е����Ҫ��ǰ����

	//lpClassID=NULL��ʱ�򣬲�ѯ����ȫ��Ӧ�ó���
	int				CA_GetAppCount(const char* lpClassID);
	PCqtApp			CA_GetAppItem(const char* lpClassID, int idx);
	PCqtApp			CA_GetAppItemFromID(const char* lpID);
	bool			CA_ModiflyAppItem(const char* lpClassID,int idx,PCqtApp pItem);
	bool			CA_DeleteAppItem(const char* lpClassID, int idx);
	bool			CA_AddAppItem(PCqtApp pItem);

	//����
	int				CA_FindStart(const char* lpClassID,const char* lpKey);
	int				CA_FindNext();
	int				CA_GetAppItemFromKey(const char* lpClassID,const char* lpAppID);

	//�����Ѿ���װ�õĽӿ�
	int				CA_GetLocalCount();
	PAppInstall		CA_GetLocalItem(int idx);
	PAppInstall		CA_GetLocalItemByPackageName(char* lpPackageName);
	PAppInstall		CA_GetLocalItemByAppID(char* lpID);
	int				CA_GetLocalItemIdxByPackageName(char* lpPackageName);
	int				CA_AddLocalItem(PAppInstall pItem);
	bool			CA_DeleteLocalItem(int idx);
	void			CA_SaveLocal();
	void			CA_ReadLocal();
	void			CA_LocalClear();


private:
	//����ҳ���ص�����
	TAppFileHead  m_tAppHead;
	PAppClassData m_pClassData[MAX_CLASS_COUNT];
	int			  m_nClassCount;
	PCqtApp		  m_ppApp[MAX_APP_COUNT];
	int			  m_nAppCount;
	//////////////////////////
	//�Ѿ���װ���˵ĳ����б�
	PAppInstall  m_pAppInstalled[MAX_APP_COUNT];
	int			 m_nAppInstalledCount;

	//�Ƿ��ʼ����
	bool		  m_isInitFlag;

private:
	void Read();
	void Write();
	bool isInit() {return m_isInitFlag;};
	bool IsMaxClass();
	bool IsCheckClassValid(int idx);	
};

#endif
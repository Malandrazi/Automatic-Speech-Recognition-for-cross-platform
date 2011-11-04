/***************************************************************************
* Engine is provice SVOX, Nuance ASR or TTS or Custom voice
* 
* 
* 
* 
****************************************************************************
*     Date     |   version    |  describe           |   author     
*---------------------------------------------------------------------------
*   2011-01-07 |     v0.1     |  Create             |   elias.kang
*              |              |                     |    
***************************************************************************/
#ifndef __SAPI_ENGINE_H__
#define __SAPI_ENGINE_H__
#include "SAPItypes.h"
#include "SAPIPlatform.h"
#include "SAPIConfig.h"
#include "SvoxEngine.h"
class SAPIEngine;
class EngineThread;
//////////////////////////////////////////////////////////////////////////
//���ڴ���������Ľṹ
typedef enum __tagEnThreadTypeInfo
{
	en_type_none = 0,
	en_type_High_level,
	en_type_ASR_Rule,
	en_type_TTS_Rule,
	en_type_Voice_Rule,
	en_type_TTS_text,
	en_type_Voice_File
}EnThreadTypeInfo;
typedef struct __tagEngineParamData
{
	int		nType;// -1 no,1 ASR,2 TTS��3 VOICE,4 TTS Text,5 Voice file
	char	szName[MAX_STRING_COUNT_LARGE];
	char	szLanguage[MAX_STRING_COUNT_LARGE];
	char*	lpText;
}TEngineParamData,*PEngineParamData;

typedef struct __tagEngineInfo
{
	SAPIHANDLE			handle;					//�����ʵ��
	TSAPIRegister		m_tSapiRegister;		//ע��ʱ��״̬��Ϣ
	bool				haveHighlevel;			//�Ƿ��и߼������ļ�����
	CSAPIConfig*		pConfig;				//�����ļ�
	bool				isInitFlag;				//�Ƿ��ʼ��
	ENSAPIStatus		enStatus;				//��ǰ�����״̬
	EngineThread*		pEngineThread;			//�����߳�

	TEngineParamData	tEngineParamData;			//�û�Context
	CThirdEngine*		pThirdEngine;			//����������
	char				szLastASRRuleName[MAX_STRING_COUNT_LARGE];
}TEngineInfo,*PEngineInfo;

//////////////////////////////////////////////////////////////////////////
void SAPI_Engine_Info(PEngineInfo pEngine, EnDebugInfoType eType, char* fmt,...);

class EngineThread:public CQtThread
{
public:
	EngineThread(PEngineInfo pEngine);
	~EngineThread();

public:
	void T_run();

	//�¼���������
public:
	bool StartWork();		//��ʼ����
	bool PauseWork();		//��ͣ����
	bool ResumeWork();		//�ظ�����
	bool StopWork();		//ֹͣ����
	bool isWorking();

	//״̬��
public:
	ENSAPIStatus		GetWorkStatus();
	bool				SetWrokStatus(ENSAPIStatus enStatus);

private:
	bool				Run_TagFun(PEngineInfo pEngine,char* lpTagName);
	bool				Run_DoRuleItem(PEngineInfo pEngine,PDoRuleItem pDoRule,char** ppResult);
	bool				Do_Item(PEngineInfo pEngine,PDoRuleItem pDo,char** ppResult);
	bool				Run_ResultItem(PEngineInfo pEngine,PResultRuleItem pResultItem,char** ppResult);

private:
	bool				WaitForContinue(PEngineInfo pEngine);//�ȴ�����ʼ������fals��ʾҪֹͣ������������

private:
	PEngineInfo			m_pEngine;	
};


//////////////////////////////////////////////////////////////////////////
//SAPIEngine
class SAPIEngine : public CQtObject
{
	Q_OBJECT
public:
	SAPIEngine(CQtObject* parent);
	virtual ~SAPIEngine();
	void	Engine_Create();			//��������
	void	Engine_Destory();			//��������		
	
public: //For Common
	SAPIHANDLE		GetOneSapiHandle();		//�õ�һ���������õ�ʵ��
	SAPIRESULTCODE Engine_Register(SAPIHANDLE handle,PSAPIRegister pSapiRegister);		//Register 
	SAPIRESULTCODE Engine_UnRegister(SAPIHANDLE handle);	
	SAPIRESULTCODE Engine_Stop(SAPIHANDLE handle);			//stop sapi
	ENSAPIStatus   Engine_Status(SAPIHANDLE handle);		//query status

public://for high-level api
	SAPIRESULTCODE Engine_Hi_Start(SAPIHANDLE handle);		//start sapi
	SAPIRESULTCODE Engine_Hi_Pause(SAPIHANDLE handle);		//��ͣ
	SAPIRESULTCODE Engine_Hi_Resume(SAPIHANDLE handle);		//�ָ�
	SAPIRESULTCODE Engine_Hi_QUit(SAPIHANDLE handle);		//�˳�
	
public://for low-level api
	SAPIRESULTCODE Engine_Lo_ASRRule(SAPIHANDLE handle,char* lpRuleName);	//start a asr rule
	SAPIRESULTCODE Engine_Lo_TTSRule(SAPIHANDLE handle,char* lpRuleName);	//start a tts rule
	SAPIRESULTCODE Engine_Lo_VoiceRule(SAPIHANDLE handle,char* lpRuleName);	//start a voic rule
	
	SAPIRESULTCODE Engine_Lo_TTSText(SAPIHANDLE handle,char* lpTTSText,char* lpLanguage);	//start a tts text
	SAPIRESULTCODE Engine_Lo_VoiceFile(SAPIHANDLE handle,char* lpPcmFile);	//start a voic file

	//����߷ǻ������
public:
	bool			Engine_SetActive(SAPIHANDLE handle);
	bool			Engine_isActive(SAPIHANDLE handle);
	PEngineInfo		Engine_GetFromHandle(SAPIHANDLE handle);

private:
	int				__Engine_GetIdleEngine();
	int				__Engine_GetEngine(SAPIHANDLE handle);
	bool			__Engine_ZeroEngine(int i);
	bool			__isWorking(SAPIHANDLE handle);

private:
	PEngineInfo		m_pEngineinfo[ENGINE_MAX_COUNT];
	SAPIHANDLE		m_handecount;
	SAPIHANDLE		m_nActiveHandle;
	CQtObject*		m_parent;

};

#endif//__SAPI_ENGINE_H
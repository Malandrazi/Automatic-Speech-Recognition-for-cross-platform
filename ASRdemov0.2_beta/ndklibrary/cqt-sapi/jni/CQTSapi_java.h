/***************************************************************************
* Cqt supply high-level api(use config file), and suppy low-level api(use 
* function api). Developer can select one to work asr ,tts and custom voice.
* High-level use Sapi_Hi_
* Low-level use Sapi_Lo_
* Other use Sapi_
****************************************************************************
*     Date     |   version    |  describe           |   author     
*---------------------------------------------------------------------------
*   2011-01-07 |     v0.1     |  Create Linux/QT    |   elias.kang
*   2011-04-22 |     v0.2     |  Support Android/QT |   elias.kang
*   2011-05-03 |     v0.3     |  Support Wince/EVC  |   elias.kang
***************************************************************************/

#ifndef __CQT_SAPI_JAVA_H_
#define __CQT_SAPI_JAVA_H_
#include <jni.h>
#include "SAPItypes.h"
#include "SAPIPlatform.h"
#include "CQTSapi.h"

//�������滷��
typedef struct __tagVarValueItem
{
	char* lpValue;
	struct __tagVarValueItem* next;
}TVarValueItem,*PVarValueItem;

typedef struct __tagMemoryVARValue
{
	char* lpVar;
	PVarValueItem pValueItem;
	struct __tagMemoryVARValue* next;
}TMemoryVARValue,*PMemoryVARValue;

class MySapiInterface : public CQTSapiInterface
{
public:
	MySapiInterface();
	~MySapiInterface();
	
public:
	bool	ITF_DebugInfoOutput(SAPIHANDLE hande, EnDebugInfoType etype,char* lpOutputinfo);
	char*	ITF_GetASRVarValue(char* lpASRWordVar,int idx);// if return NULL is over
	char*	ITF_GetTTVarValue(char* lpTTSWordVar);
	bool	ITF_GetUserPressKey();
	bool	ITF_CallApplication(char* lpASRRuleName,char** pparam);	
};

typedef bool (*PFNcallback_SAPI_DebugOutInfo)(JNIEnv *env,char* lpInfo);
typedef bool (*PFNcallback_SAPI_ASRResult)(JNIEnv *env,char* lpASR);
class CQTSapi_Service
{
	Q_OBJECT
public:
	CQTSapi_Service();
	~CQTSapi_Service();	

	//���ûص�����
	void		SetCallBack(PFNcallback_SAPI_DebugOutInfo pfnDebug, PFNcallback_SAPI_ASRResult pfnReslut);

	//��ʼ��
	bool		CSS_Init(char* lpResourcePath, char* lpConfigName,CQtObject* obj);

	//ASR�������
	int			CSS_ASRClear(char* lpVar);

	//ASR��������
	int			CSS_SetASRRuleValue(char* lpVar, char* lpValue);

	//TTS�������
	int			CSS_TTSClear(char* lpVar);

	//TTS��������
	int			CSS_SetTTSRuleValue(char* lpVar, char* lpValue);

	//�õ�sapi����
	CQTSapi*	CSS_GetSapi() {return m_pcqtSapi;};

private:
	CQTSapi*			m_pcqtSapi;
	MySapiInterface*	m_pmySapiInterface;
};

#endif//__CQT_SAPI_H_
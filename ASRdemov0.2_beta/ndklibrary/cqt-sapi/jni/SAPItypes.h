
#ifndef __SAPI_TYPES_H__
#define __SAPI_TYPES_H__


//////////////////////////////////////////////////////////////////////////
//ƽ̨��صĺ�
//#define PLATFORM_SAPI_LINUX_QT
//#define PLATFROM_SAPI_ANDROID_QT
//#define PLATFROM_SAPI_WINCE_EVC
//#define PLATFROM_SAPI_WINCE_QT
//#define PLATFROM_SAPI_ANDROID_NDK

#if defined(PLATFROM_SAPI_ANDROID_QT) || defined(PLATFROM_SAPI_ANDROID_NDK)
#include <string.h>
#include <jni.h>
#include <android/log.h>
#endif

#ifdef PLATFROM_SAPI_WINCE_EVC
#define SAPI_DllExport   __declspec( dllexport )
#else
#define SAPI_DllExport
#endif

//typedef common data
typedef int SAPIRESULTCODE;
typedef int	SAPIHANDLE;//�ӹ�����ʼһֱ�����

//define sring size
#define MAX_STRING_COUNT_HUGE		512
#define MAX_STRING_COUNT_LARGE		256
#define MAX_STRING_COUNT_SMALL		50
//ASRʶ���ķ��ؽ��
#define MAX_ASR_RESULT_COUNT		10

//define micro
#ifdef _WIN32
#ifdef PLATFROM_SAPI_ANDROID_QT
#define SAPI_ASSERT(x) ASSERT(x)
#else
#define SAPI_ASSERT(x)
#endif
#else
#define SAPI_ASSERT(x)
#endif

#define SAPI_ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#define ENGINE_MAX_COUNT		10//���֧��10��config�ļ�һ������

//define error codes
#define SAPI_OK								0
#define SAPI_ERROR							1
#define SAPI_MALLOC_MEMORY_ERROR			3

//read config file
#define SAPI_NOEXIST_CONFIG_FILE			2
#define SAPI_NOT_EXIST_MAININFO				4
#define SAPI_READ_MAININFO_ERROR			5
#define SAPI_READ_ASRRULES_ERROR			6
#define SAPI_READ_TTSText_ERROR				7
#define SAPI_READ_CUSTOMVOICE_ERROR			8
#define SAPI_READ_CONTROLCODES_ERROR		9

//User EXT
#define SAPI_ENGINE_BUSY					10
#define SAPI_ENGINE_NO_RESOURCE				11
#define SAPI_ENGINE_NOT_SUPPORT				12
#define SAPI_ENGINE_NOT_ACTIVE				13

//SAPI status
typedef enum __tagENSAPIStatus
{
	SAPI_Status_Idle = 0,	//���У�ʲô��û����
	SAPI_Status_Starting,	//�������������߳�	
	SAPI_Status_Pauseing,	//������ͣ
	SAPI_Status_Paused,		//�Ѿ���ͣ��
	SAPI_Status_HighLevel,	//���ڸ߼�ִ��
	SAPI_Status_ASRING,		//���ڽ���ʶ��
	SAPI_Status_TTSING,		//���ڽ���TTS����
	SAPI_Status_VoiceING,	//���ڲ���voice
	SAPI_Status_Stoping,	//����ֹͣ
	SAPI_Status_Over,		//�Ѿ��������
	SAPI_Status_Unknow		//δ֪״̬
}ENSAPIStatus;

//SAPI Callback function
typedef enum __tagEnDebugInfoType
{
	en_ITF_MSG_Info = 0,
	en_ITF_MSG_Warning,
	en_ITF_MSG_Error,
	en_ITF_MSG_Debug
}EnDebugInfoType;
class CQTSapiInterface
{
public:
	CQTSapiInterface(){};
	~CQTSapiInterface(){};
public:
	virtual bool ITF_DebugInfoOutput(SAPIHANDLE hande, EnDebugInfoType etype,char* lpOutputinfo) = 0;
	
public:
	//virtual bool ITF_GetASRCommandWord(char* lpASRWordVar,int idx,char* lpWordBuf, int nBufLen) = 0;// if return false is over
	virtual char* ITF_GetASRVarValue(char* lpASRWordVar,int idx) = 0;// if return NULL is over
	virtual char* ITF_GetTTVarValue(char* lpTTSWordVar) = 0;
	virtual bool ITF_GetUserPressKey() = 0;//�ȴ��û���������


	//������û�
	virtual bool ITF_CallApplication(char* lpASRRuleName,char** pparam) = 0;//���Ϊ10
};

//SAPI Register Data
typedef struct __tagSAPIRegister
{
	char				szConfigResoucePath[MAX_STRING_COUNT_HUGE];//�����Ʒ��ʱ����Ҫ��һ�£�������Ʒֻ��һ����ԴĿ¼�����еı�������Դ������һ��λ��
	char				szConfigFileName[MAX_STRING_COUNT_LARGE];//�����ļ�������
	CQTSapiInterface*	pCqtSapiInterface;
}TSAPIRegister,*PSAPIRegister;

void SAPI_DB_PRINTF(char* fmt,...);
//#define SAPI_DB_PRINTF	SAPI_Printf

//debug text
#define STRING_ENGINE_INPUT_PARAM_ERROR			"Input param error,Please check."
#define STRING_ENGINE_BUSY						"Engine has busying,Please try later."
#define STRING_ENGINE_NOT_ACTIVE				"Engine has inactive,Please let you application active."
#endif//__SAPI_TYPES_H__
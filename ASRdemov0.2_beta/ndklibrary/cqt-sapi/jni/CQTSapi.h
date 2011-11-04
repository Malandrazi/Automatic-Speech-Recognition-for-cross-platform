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

#ifndef __CQT_SAPI_H_
#define __CQT_SAPI_H_
#include "SAPItypes.h"
#include "SAPIPlatform.h"

class SAPI_DllExport CQTSapi : public CQtObject
{
	Q_OBJECT
public:
	CQTSapi(CQtObject* parent = 0);
	virtual ~CQTSapi();		
	
public: //For Common	
	SAPIRESULTCODE Sapi_Register(PSAPIRegister pSapiRegister);		//Register
	SAPIRESULTCODE Sapi_UnRegister();	//��ע�ᣬû�в��Թ�����Ϊ���߳�
	SAPIRESULTCODE Sapi_Stop();			//ֹͣ
	ENSAPIStatus   Sapi_Status();		//��ȡ״̬��û�в��Թ�

public://for high-level api
	SAPIRESULTCODE Sapi_Hi_Start();		//start sapi config ����
	SAPIRESULTCODE Sapi_Hi_Pause();		//��ͣ��û���Թ�
	SAPIRESULTCODE Sapi_Hi_Resume();	//�ָ�, û���Թ�
	SAPIRESULTCODE Sapi_Hi_QUit();		//�˳�����ͬ��Sapi_Stop
	
public://for low-level api
	SAPIRESULTCODE Sapi_Lo_ASRRule(char* lpRuleName);	//start a asr rule
	SAPIRESULTCODE Sapi_Lo_TTSRule(char* lpRuleName);	//start a tts rule
	SAPIRESULTCODE Sapi_Lo_VoiceRule(char* lpRuleName);	//start a voic rule
	
	SAPIRESULTCODE Sapi_Lo_TTSText(char* lpTTSText,char* lpLanguage);	//start a tts text
	SAPIRESULTCODE Sapi_Lo_VoiceFile(char* lpPcmFile);					//start a voic file

private:
	SAPIHANDLE m_handle;
};

#endif//__CQT_SAPI_H_
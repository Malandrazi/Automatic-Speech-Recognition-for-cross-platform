package com.demos;

import android.content.Context;
import android.util.Log;
import android.webkit.WebView;

public class CQTSapi {
	public WebView mWebView;
	Context mContext;
	
	final void init_library()
	{
		try 
		{
			System.loadLibrary("utils");
            System.loadLibrary("media");
            System.loadLibrary("testsvox");
            System.loadLibrary("cqtsapi_ndk");
        } catch (UnsatisfiedLinkError e)
        {
            Log.d("cqtmarketapi", "cqtmarketapi jni library not found!");
        }
	}
	
	CQTSapi(){
     	init_library();
     }
     
	void SetContext(Context c)
	{
		mContext = c;
	}
	
	public void JS_OpenFirstURL(final String strURL)
    {
   	 mWebView.loadUrl(strURL);
    }
	
	public void SetWebview(WebView v)
    {
    	mWebView = v;
    	//Log.i("CQTSapi","--------------------------- SetWebview");
    	//JS_CQT_API_Init();
    	//Log.i("CQTSapi","--------------------------- SetWebview OVER");
    }	
	
	//���������Ϣ
	public void callback_SAPI_DebugOutInfo(final String strInfo)
	{
		//Log.i("callback_SAPI_DebugOutInfo",strInfo);
		mWebView.loadUrl("javascript:callback_Debuginfo('" + strInfo + "')");
		//Log.i("callback_SAPI_DebugOutInfo",strInfo + "--Over");
	}
	
	//���ʶ��Ľ��,����û�����������أ�������Ʒ�汾��ʱ����Ҫ�����û�ѡ��
	public void callback_SAPI_ASRResult(final String strASR)
	{
		mWebView.loadUrl("javascript:callback_ASRResult('" + strASR + "')");
	}
	
	public native int JS_SAPI_Init(final String strResultPath, final String strConfigName);
	
	//����4�����������ڵ��ú���JS_SAPI_Hi_Start��JS_SAPI_Lo_ASRRule��JS_SAPI_Lo_TTSRule֮ǰ���ã�
	//�������ʧ�ܻ�����Ч	
	//1 ����������еı���
	public native int JS_SAPI_ASRClear(final String strASRVar);	
	
	//2 �����������еı���	
	public native int JS_SAPI_SetASRRuleValue(final String strASRVar,final String strValue);
	
	//3 ��պϳɹ����еı���
	public native int JS_SAPI_TTSClear(final String strTTSVar);
	
	//4 ���úϳɹ����еı���
	public native int JS_SAPI_SetTTSRuleValue(final String strTTSVar,final String strValue);
	
	//ֹͣ
	public native int JS_SAPI_Stop();
	
	//�߼�API
	public native int JS_SAPI_Hi_Start();
		
	//��ʼһ��ASR
	public native int JS_SAPI_Lo_ASRRule(final String strRule);
	
	//��ʼһ��TTS
	public native int JS_SAPI_Lo_TTSRule(final String strRule);
	
	//��ʼһ��VoiceRule
	public native int JS_SAPI_Lo_VoiceRule(final String strRule);
	
	//��ʼ����һ��TTS�ı�
	public native int JS_SAPI_Lo_TTSText(final String strText);
	
	//��ʼ����һ��Voice File
	public native int JS_SAPI_Lo_VoiceFile(final String strFile);
}

//
//  YvVoiceManager.hpp
//  GameBase
//
//  Created by zjm on 16/9/1.
//
//

#ifndef YvVoiceManager_hpp
#define YvVoiceManager_hpp

#include <stdio.h>
#include "cocos2d.h"

#include "YunVaSDK/yvListern.h"
#include "YunVaSDK/YVTool.h"

class IVoicePlaySink
{
public:
	virtual ~IVoicePlaySink(){}
	virtual void onPlayComplete(){}
};

class YvVoiceManager: public YVSDK::YVListern::YVLoginListern, 
	public YVSDK::YVListern::YVReConnectListern,
    public YVSDK::YVListern::YVStopRecordListern, 
	public YVSDK::YVListern::YVFinishSpeechListern, 
	public YVSDK::YVListern::YVFinishPlayListern, 
	public YVSDK::YVListern::YVUpLoadFileListern,
	public YVSDK::YVListern::YVDownLoadFileListern,
    public YVSDK::YVListern::YVRecordVoiceListern, 
	public YVSDK::YVListern::YVCPUserInfoListern
{

public:
    virtual void onLoginListern(YVSDK::CPLoginResponce*);
    virtual void onRecordVoiceListern(YVSDK::RecordVoiceNotify*);
    virtual void onStopRecordListern(YVSDK::RecordStopNotify*);
    virtual void onDownLoadFileListern(YVSDK::DownLoadFileRespond*);
    virtual void onFinishPlayListern(YVSDK::StartPlayVoiceRespond*);
    virtual void onUpLoadFileListern(YVSDK::UpLoadFileRespond*);
    virtual void onFinishSpeechListern(YVSDK::SpeechStopRespond*);
    virtual void onCPUserInfoListern(YVSDK::GetCPUserInfoRespond*);
    virtual void onReConnectListern(YVSDK::ReconnectionNotify*);
    
public:
	static YvVoiceManager* GetInstance();
	void Init();
	void Cleanup();
	void setUploadListern(YVSDK::YVListern::YVUpLoadFileListern * listern);
	void setVoicePlaySink(IVoicePlaySink * pSink);
	void CpLogin(std::string nickName, std::string uuid);
	void CpLogout();
	void StartRecord();
	void StopRecord();
	void PlayRecord(std::string url);
	void PlayRecord(std::string url, std::string fileName);
	void UploadFile(std::string fileName);
protected:
	YvVoiceManager();
	virtual ~YvVoiceManager();
private:
	bool isPlaying;
    YVSDK::YVTool* pYVTool;
    YVSDK::YVListern::YVUpLoadFileListern * _uploadListen;
	IVoicePlaySink * _voicePlaySink;
};

#endif /* YvVoiceManager_hpp */



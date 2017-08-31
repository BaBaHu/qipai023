//
//  YvVoiceManager.cpp
//  GameBase
//
//  Created by zjm on 16/9/1.
//
//
#include "cocos2d.h"
#include "YunVaSDK/YVTool.h"
#include "UtilityBase.h"
using namespace YVSDK;
#include "MECallBackListenerHelper.h"
#include "YvVoiceManager.h"

YvVoiceManager::YvVoiceManager()
{
	_uploadListen = nullptr;
	_voicePlaySink = nullptr;
}

YvVoiceManager::~YvVoiceManager()
{

}

YvVoiceManager* YvVoiceManager::GetInstance()
{
	static YvVoiceManager* pManager = NULL;
	if (pManager == NULL)
		pManager = new YvVoiceManager();
	return pManager;
}

void YvVoiceManager::Init(){
	pYVTool = YVTool::getInstance();
	pYVTool->initSDK(1000883, cocos2d::FileUtils::getInstance()->getWritablePath(), false);
	cocos2d::log("YvVoiceManager.Init....................................................");
	pYVTool->addLoginListern(this);
	pYVTool->addReConnectListern(this);
	pYVTool->addCPUserInfoListern(this);
	pYVTool->addDownLoadFileListern(this);
	pYVTool->addUpLoadFileListern(this);
	pYVTool->addFinishPlayListern(this);
	pYVTool->addRecordVoiceListern(this);
	pYVTool->addStopRecordListern(this);
	this->isPlaying = false;
}


void YvVoiceManager::Cleanup(){
	cocos2d::log("YvVoiceManager::Cleanup");
	pYVTool->delLoginListern(this);
	pYVTool->delReConnectListern(this);
	pYVTool->delCPUserInfoListern(this);
	pYVTool->delDownLoadFileListern(this);
	pYVTool->delUpLoadFileListern(this);
	pYVTool->delFinishPlayListern(this);
	pYVTool->delRecordVoiceListern(this);
	pYVTool->delStopRecordListern(this);
	pYVTool->releaseSDK();
	pYVTool = NULL;
}

void YvVoiceManager::setUploadListern(YVSDK::YVListern::YVUpLoadFileListern * listern){
	_uploadListen = listern;
}

void YvVoiceManager::setVoicePlaySink(IVoicePlaySink * pSink)
{
	_voicePlaySink = pSink;
}

void YvVoiceManager::CpLogin(std::string nickName, std::string uuid){
	cocos2d::log("YvVoiceManager::CpLogin");
	pYVTool->cpLogin(nickName, uuid);
}

void YvVoiceManager::CpLogout()
{
	cocos2d::log("YvVoiceManager::CpLogout");
	pYVTool->cpLogout();
}

void YvVoiceManager::onLoginListern(CPLoginResponce* r){
	cocos2d::log("YvVoiceManager::onLoginListern");
	std::string str;
	if (r->result != 0)
	{
		str.append("login Error:");
		str.append(r->msg);
	}
	else
	{
		YVTool::getInstance()->setRecord(60, true);
		std::stringstream ss;
		ss << "login succeed" << "UId:";
		ss << r->userid;
		str.append(ss.str());
	}
	CCLOG(str.c_str());
}

void YvVoiceManager::StartRecord(){

	cocos2d::log("YvVoiceManager::StartRecord");
	std::string savePath = cocos2d::FileUtils::getInstance()->getWritablePath() + utility::toString(time(NULL), "");
	pYVTool->startRecord(savePath);
	this->isPlaying = false;
}
void YvVoiceManager::onRecordVoiceListern(RecordVoiceNotify* notify){
	cocos2d::log("YvVoiceManager::onRecordVoiceListern");
}

void YvVoiceManager::StopRecord(){
	cocos2d::log("YvVoiceManager::StopRecord()");
	pYVTool->stopRecord();
}
void YvVoiceManager::onStopRecordListern(RecordStopNotify* notify){
	cocos2d::log("YvVoiceManager::onStopRecordListern");
	std::string fileName = notify->strfilepath;
	this->UploadFile(fileName);
}

void YvVoiceManager::PlayRecord(std::string url, std::string fileName)
{
	cocos2d::log("YvVoiceManager::PlayRecord, url= %s, filename = %s", url.c_str(), fileName.c_str() );
	pYVTool->playRecord(url, fileName);
	isPlaying = true;
}

void YvVoiceManager::PlayRecord(std::string url){
	cocos2d::log("YvVoiceManager::PlayRecord");
	pYVTool->playFromUrl(url);
	isPlaying = true;
	//此处会产生两处回调 onDownLoadFileListern onFinishPlayListern
}

void YvVoiceManager::onDownLoadFileListern(DownLoadFileRespond* resp){
	cocos2d::log("YvVoiceManager::onDownLoadFileListern");
	std::stringstream ss;
	std::string str;
	ss << "<DownLoad File>" << " result id:" << resp->result << "  erro Msg:" << resp->msg << " \npath:" << resp->filename << "\n percent:" << resp->percent;
	str.append(ss.str());
	CCLOG(str.c_str());

	if (resp->result != 0){
		cocos2d::log("YvVoiceManager::onDownLoadFileListern download audio file failed %s", resp->msg.c_str());
		if (_voicePlaySink)
			_voicePlaySink->onPlayComplete();
		isPlaying = false;
	}
	else{
		isPlaying = true;
	}

}

void YvVoiceManager::onFinishPlayListern(StartPlayVoiceRespond* resp){
	cocos2d::log("YvVoiceManager::onFinishPlayListern");
	this->isPlaying = false;
	if (_voicePlaySink)
		_voicePlaySink->onPlayComplete();
}

void YvVoiceManager::UploadFile(std::string fileName){
	cocos2d::log("YvVoiceManager::UploadFile");
	pYVTool->upLoadFile(fileName);
}

void YvVoiceManager::onUpLoadFileListern(UpLoadFileRespond* resp){
	cocos2d::log("YvVoiceManager::onUpLoadFileListern percent %u", resp->percent);
	std::stringstream ss;
	std::string str;
	ss << "<UpLoad File>" << " result id:" << resp->result << " erro Msg:" << resp->msg << " url:" << resp->fileurl << " \n percent:" << resp->percent;
	str.append(ss.str());
	CCLOG(str.c_str());

	if (resp->result != 0){
		cocos2d::log("YvVoiceManager::onUpLoadFileListern upload failed.result %d: %s ", resp->result, resp->msg.c_str());
		return;
	}
	if (_uploadListen)
		_uploadListen->onUpLoadFileListern(resp);
}

void YvVoiceManager::onFinishSpeechListern(SpeechStopRespond*){
	cocos2d::log("YvVoiceManager::onFinishSpeechListern");
}


void YvVoiceManager::onCPUserInfoListern(GetCPUserInfoRespond*){
	cocos2d::log("YvVoiceManager::onCPUserInfoListern");
}
void YvVoiceManager::onReConnectListern(ReconnectionNotify* r){
	cocos2d::log("YvVoiceManager::onReConnectListern");
	std::string str;
	std::stringstream ss;
	ss << "ReConnect, UI:";
	ss << r->userid;
	str.append(ss.str());
	CCLOG(str.c_str());
}
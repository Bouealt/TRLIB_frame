#pragma once
#ifndef TRBASECONTROL_H
#define TRBASECONTROL_H

#include "TR_global.h"
#include "TRAbstractControl.h"
//#include "TRPublicRegister.h"
#include "TRDataDistribution.h"
//#include "TRBaseAction.h"

#include <vector>
#include <QDebug>
#include <QThread>
#include <QTimer>
#include <QEventLoop>

#include <QMutex>
#include <QMutexLocker>

// 将指针pObject转换成Variant
#define CUSTOM_TO_VARIANT(pObject)             QVariant::fromValue((void*)pObject)		
// 将Variant转换成指定的数据类型的指针
#define VARIANT_TO_CUSTOM(pObject, ClassName)  static_cast<ClassName*>(pObject.value<void*>())	



// 阻塞请求，群发
#define TR_REQUESTEXECUTION_ALL_ACT         TRBaseControl::GetTRBaseControl()->RequestExecution(this)
// 非阻塞请求
#define TR_REQUESTEXECUTION(data)           TRBaseControl::GetTRBaseControl()->RequestExecution(data,this)

// 类的前置声明
class TRPublicRegister;
class TRBaseAction;

// 单例类
// 核心管理模块
class TRBaseControl : public QObject, public TRAbstractControl {
	Q_OBJECT
	// 消息分发器 
	friend class TRDataDistribution;
private:
	explicit TRBaseControl();

public:
	// 核心管理模块析构函数
	~TRBaseControl();

	// 注册当前Action模块
	bool RegisterAction(const char * act_name, TRBaseAction * act_object);

	// 解注册当前Action模块
	bool UnRegisterAction(const QString & act_name);
	bool UnRegisterAction(TRBaseAction * act_object);

	// 查找TRBaseAction模块
	TRBaseAction * FindAction(const QString & act_name);

	// 查找到当前的Action名字
	QString FindActionName(TRBaseAction * act_object);

	// 删除所有Action，即当前Control中注册的模块
	void DeleteAllAction();

	// 删除指定Action，释放其资源
	void DeleteAction(const QString & act_name);
	 
	// 注册命令
	bool RegisterCmd(TRBaseAction * act_object, QList<quint64> cmdList);

	// 解注册命令
	bool UnRegisterCmd(TRBaseAction * act_object);

	// 群发接口
	bool RequestExecution(void * pRequester = NULL);

	// 请求处理该种Cmd的消息
	bool RequestExecution(const quint64 & command, void * pRequester = NULL);

	// 请求处理该TRData消息
	bool RequestExecution(const TRData::Ptr data, void * pRequester = NULL);

	// 获得当前请求者
	void * TRRequester();

	// 拿到此消息的请求者
	void * TRRequester(const TRData::Ptr data);

private slots:
	void ActionExecution(TRBaseAction * action, const TRData::Ptr data);

private:
	void * m_requester;								// 当前的请求Actioner
	TRDataDistribution m_data_distribution;			// 消息转发器
	TRPublicRegister m_public_register;				// 模块、消息注册器
	

public:
	// 单例模式，提供唯一实例化Control的接口
	static TRBaseControl * GetTRBaseControl();

private:
	class AutoRelease {
	public:
		AutoRelease() {}
		// 通过AutoRelease类的析构函数，释放m_trbasecontrol
		~AutoRelease() {
			if (m_trbasecontrol) {
				delete m_trbasecontrol;
			}
		}
	};
	
	static  TRBaseControl* volatile m_trbasecontrol;
	// 类静态变量，用于程序退出时，单例类自动析构
	static AutoRelease _autoRelease;
};

#endif // !TRBASECONTROL_H
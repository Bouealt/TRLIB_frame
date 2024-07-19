#pragma once
#ifndef TRBASEACTIONEX_H
#define TRBASEACTIONEX_H

#include "TR_global.h"
#include "TRBaseControl.h"
#include "TRBaseAction.h"
#include <QThread>
#include <QTimer>
#include <QSharedPointer>

class TRBaseActionEx : public QObject, public TRBaseAction {
	Q_OBJECT
public:
	explicit TRBaseActionEx(TRBaseControl *pControl = NULL, const char *act_name = NULL);
	virtual  ~TRBaseActionEx();

private:
	// 继承至TRBaseAction的，重写
	void Execute(const TRData::Ptr data);
	
protected:
	// 继承至TRBaseAction的，重写
	void RegisterCmds();

protected slots:
	// data处理，模块重写，异步执行，将data在模块线程上执行
	virtual void OnExecuteEx(const TRData::Ptr data);
	void OnRegisterCommands();
	
signals:
	void ToExecute(const TRData::Ptr pData);

protected:
	TRBaseControl	*m_Control;
	QThread			*m_Thread;
};

#endif // !TRBASEACTIONEX_H
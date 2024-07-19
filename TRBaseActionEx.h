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
	// �̳���TRBaseAction�ģ���д
	void Execute(const TRData::Ptr data);
	
protected:
	// �̳���TRBaseAction�ģ���д
	void RegisterCmds();

protected slots:
	// data����ģ����д���첽ִ�У���data��ģ���߳���ִ��
	virtual void OnExecuteEx(const TRData::Ptr data);
	void OnRegisterCommands();
	
signals:
	void ToExecute(const TRData::Ptr pData);

protected:
	TRBaseControl	*m_Control;
	QThread			*m_Thread;
};

#endif // !TRBASEACTIONEX_H
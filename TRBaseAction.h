#pragma once
#ifndef TRBASEACTION_H
#define TRBASEACTION_H

#include "TR_global.h"
#include "TRAbstractAction.h"

#include <QObject>

// ע����ǰ��������Ҫ�ڵ�ǰcpp�ļ�����Ӷ�Ӧ���ͷ�ļ�
class TRBaseControl;

// �����ֻ���� void Execute(const FreyaData data) �е���
// �����Data�е�cmd�����Ӧ��cmd��ִ�к����func��������ǣ����Ҹ�ģ����ע�ᣬ��ֱ�ӽ���ǰcmd���뵽��Actionģ���cmd�����С�
// ���Կ�����������ڳ�ʼ��ʱ�������Լ���cmd�����뵽cmd�������У�ע�ᵽControl��ȥ

#define TR_CMD_CONNECT_EXEC(cmd, func)    if(cmd == data->command) \
                                   { func; return; } \
                                   else if(TR_CMD_CMDREGREQUEST == data->command) \
                                   { m_CmdList.append(cmd); }


class TRBaseAction : public TRAbstractAction {
public:
	explicit TRBaseAction(TRBaseControl *pControl = NULL, const char *act_name = NULL);
	virtual ~TRBaseAction();

	// ��д�������ӿ�
	virtual void Execute() {
		TRData::Ptr data = TRData::CreateDate(TR_CMD_NON);
		Execute(data);
	};
	virtual void Execute(TRData::Ptr) {};
	virtual void RegisterCmds();

	QString ActionName();

protected:
	TRBaseControl		* m_Control;
	QList<quint64>		m_CmdList;
	QString				m_ActionName;
};


#endif // !TRBASEACTION_H

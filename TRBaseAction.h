#pragma once
#ifndef TRBASEACTION_H
#define TRBASEACTION_H

#include "TR_global.h"
#include "TRAbstractAction.h"

#include <QObject>

// 注意类前置声明后，要在当前cpp文件中添加对应类的头文件
class TRBaseControl;

// 这个宏只能在 void Execute(const FreyaData data) 中调用
// 如果该Data中的cmd满足对应的cmd就执行后面的func，如果不是，而且该模块已注册，就直接将当前cmd加入到此Action模块的cmd数组中。
// 所以可以用这个宏在初始化时，定义自己的cmd，加入到cmd的数组中，注册到Control中去

#define TR_CMD_CONNECT_EXEC(cmd, func)    if(cmd == data->command) \
                                   { func; return; } \
                                   else if(TR_CMD_CMDREGREQUEST == data->command) \
                                   { m_CmdList.append(cmd); }


class TRBaseAction : public TRAbstractAction {
public:
	explicit TRBaseAction(TRBaseControl *pControl = NULL, const char *act_name = NULL);
	virtual ~TRBaseAction();

	// 重写这两个接口
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

#pragma once

#include "TR_global.h"

#include <QDataStream>
#include <QVariant>
#include <QPair>
#include <QDir>
#include <QUuid>
#include <QDebug>
#include <QSharedPointer>
#include <QEventLoop>

// 注意类前置声明后，要在当前cpp文件中添加对应类的头文件
class TRBaseAction;
class TRData;

// 模块通信信息定义
class TRData {
public:
	// 信息节点的智能共享指针，这样的话，
	// 就自动析构不用再每次使用完Data之后担心是否需要手动释放资源
	typedef QSharedPointer<TRData> Ptr;
	TRData();
	// 拷贝构造函数
	TRData(const TRData & input);
	~TRData();

	QVariant GetArgument();
	void SetArgument(const QVariant &value);

	QVariant GetArgument(const QString &key);
	void SetArgument(const QString &key, const QVariant &value);

	static TRData::Ptr CreateDate(const quint64 &cmd = 0);
	static TRData::Ptr CreateDate(const TRData & input);


public:
	QString     dataID;         // 当前信息节点的ID
	quint64     command;        // 当前信息节点的分类、执行码
private:
	QVariantMap arguments;		// QMap<QString, QVariant> QVariantMap，存储消息的具体内容
};


// 模块注册、消息注册
// 订阅-发布模式
class TRPublicRegister {
public:
	explicit TRPublicRegister();

	// 注册当前模块
	bool RegisterAction(const QString & action_name, TRBaseAction * act_object);
	// 删除当前模块
	bool UnRegisterAction(const QString & action_name);
	// 给具体的Action对象注册cmd
	bool RegisterCmd(TRBaseAction * act_object, const QList<quint64> cmd_list);
	// 删除Action对象的cmd
	bool UnRegisterCmd(TRBaseAction * act_object);
	// 检测当前Action对象中是否有订阅当前cmd
	bool CheakActionCmd(TRBaseAction * act_object, quint64 command);

	// 通过对象名查找Action指针
	TRBaseAction * FindAction(const QString & act_name);
	// 通过Action指针找到Action名字
	QString FindActionName(TRBaseAction * action);

	// 返回当前所有注册到的Action对象
	QHash<QString, TRBaseAction*> & AllRegisterAction();

private:
	QHash<QString, TRBaseAction*>                    m_ActionHash;      // Action列表
	QHash<TRBaseAction*, QList<quint64> >            m_CmdHash;         // action及其对应的cmd列表
};


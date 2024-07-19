#pragma once
#ifndef _TRDATADISTRIBUTION_H_
#define _TRDATADISTRIBUTION_H_

#include "TR_global.h"
#include "TRPublicRegister.h"
#include <QThread>
#include <QMutex>
#include <QMutexLocker>

class TRBaseControl;

// 消息队列
class TRDataDistribution : public QThread {
	Q_OBJECT
public:
	explicit TRDataDistribution(TRBaseControl * control);

	// 拿到当前Data队列中的消息索引
	QStringList GetDataList();
	
	// 插入消息
	bool InsertData(TRData::Ptr data);

	// 通过消息id查找data
	TRData::Ptr FindData(const QString &data_id);

protected:
	// 消费消息
	virtual void run();

private:
	TRBaseControl				*m_Control;		// 控制核心
	QStringList					m_DataList;		// 消息队列中的消息索引(可以采用多个list，做优先级)
	QHash<QString, TRData::Ptr> m_DataQueue;	// 消息队列实体
	QMutex						m_Mutex;		// 队列锁
};

#endif // ! _TRDATADISTRIBUTION_H_



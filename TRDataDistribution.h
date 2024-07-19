#pragma once
#ifndef _TRDATADISTRIBUTION_H_
#define _TRDATADISTRIBUTION_H_

#include "TR_global.h"
#include "TRPublicRegister.h"
#include <QThread>
#include <QMutex>
#include <QMutexLocker>

class TRBaseControl;

// ��Ϣ����
class TRDataDistribution : public QThread {
	Q_OBJECT
public:
	explicit TRDataDistribution(TRBaseControl * control);

	// �õ���ǰData�����е���Ϣ����
	QStringList GetDataList();
	
	// ������Ϣ
	bool InsertData(TRData::Ptr data);

	// ͨ����Ϣid����data
	TRData::Ptr FindData(const QString &data_id);

protected:
	// ������Ϣ
	virtual void run();

private:
	TRBaseControl				*m_Control;		// ���ƺ���
	QStringList					m_DataList;		// ��Ϣ�����е���Ϣ����(���Բ��ö��list�������ȼ�)
	QHash<QString, TRData::Ptr> m_DataQueue;	// ��Ϣ����ʵ��
	QMutex						m_Mutex;		// ������
};

#endif // ! _TRDATADISTRIBUTION_H_



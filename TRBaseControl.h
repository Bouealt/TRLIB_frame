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

// ��ָ��pObjectת����Variant
#define CUSTOM_TO_VARIANT(pObject)             QVariant::fromValue((void*)pObject)		
// ��Variantת����ָ�����������͵�ָ��
#define VARIANT_TO_CUSTOM(pObject, ClassName)  static_cast<ClassName*>(pObject.value<void*>())	



// ��������Ⱥ��
#define TR_REQUESTEXECUTION_ALL_ACT         TRBaseControl::GetTRBaseControl()->RequestExecution(this)
// ����������
#define TR_REQUESTEXECUTION(data)           TRBaseControl::GetTRBaseControl()->RequestExecution(data,this)

// ���ǰ������
class TRPublicRegister;
class TRBaseAction;

// ������
// ���Ĺ���ģ��
class TRBaseControl : public QObject, public TRAbstractControl {
	Q_OBJECT
	// ��Ϣ�ַ��� 
	friend class TRDataDistribution;
private:
	explicit TRBaseControl();

public:
	// ���Ĺ���ģ����������
	~TRBaseControl();

	// ע�ᵱǰActionģ��
	bool RegisterAction(const char * act_name, TRBaseAction * act_object);

	// ��ע�ᵱǰActionģ��
	bool UnRegisterAction(const QString & act_name);
	bool UnRegisterAction(TRBaseAction * act_object);

	// ����TRBaseActionģ��
	TRBaseAction * FindAction(const QString & act_name);

	// ���ҵ���ǰ��Action����
	QString FindActionName(TRBaseAction * act_object);

	// ɾ������Action������ǰControl��ע���ģ��
	void DeleteAllAction();

	// ɾ��ָ��Action���ͷ�����Դ
	void DeleteAction(const QString & act_name);
	 
	// ע������
	bool RegisterCmd(TRBaseAction * act_object, QList<quint64> cmdList);

	// ��ע������
	bool UnRegisterCmd(TRBaseAction * act_object);

	// Ⱥ���ӿ�
	bool RequestExecution(void * pRequester = NULL);

	// ���������Cmd����Ϣ
	bool RequestExecution(const quint64 & command, void * pRequester = NULL);

	// �������TRData��Ϣ
	bool RequestExecution(const TRData::Ptr data, void * pRequester = NULL);

	// ��õ�ǰ������
	void * TRRequester();

	// �õ�����Ϣ��������
	void * TRRequester(const TRData::Ptr data);

private slots:
	void ActionExecution(TRBaseAction * action, const TRData::Ptr data);

private:
	void * m_requester;								// ��ǰ������Actioner
	TRDataDistribution m_data_distribution;			// ��Ϣת����
	TRPublicRegister m_public_register;				// ģ�顢��Ϣע����
	

public:
	// ����ģʽ���ṩΨһʵ����Control�Ľӿ�
	static TRBaseControl * GetTRBaseControl();

private:
	class AutoRelease {
	public:
		AutoRelease() {}
		// ͨ��AutoRelease��������������ͷ�m_trbasecontrol
		~AutoRelease() {
			if (m_trbasecontrol) {
				delete m_trbasecontrol;
			}
		}
	};
	
	static  TRBaseControl* volatile m_trbasecontrol;
	// �ྲ̬���������ڳ����˳�ʱ���������Զ�����
	static AutoRelease _autoRelease;
};

#endif // !TRBASECONTROL_H
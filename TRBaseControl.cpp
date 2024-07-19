#include "TRBaseControl.h"
#include "TRPublicRegister.h"
#include "TRBaseAction.h"

TRBaseControl * volatile TRBaseControl::m_trbasecontrol = NULL;
TRBaseControl::AutoRelease TRBaseControl::_autoRelease;

// ������
static QMutex m_Mutex;

TRBaseControl::TRBaseControl() :
	QObject(NULL),
	TRAbstractControl(),
	m_data_distribution(this) {

}

TRBaseControl::~TRBaseControl() {
	qDebug() << "TRLib > " << "TRBaseControl delete" << this;
	DeleteAllAction();
}

bool TRBaseControl::RegisterAction(const char * act_name, TRBaseAction * act_object) {
	return m_public_register.RegisterAction(act_name, act_object);
}

bool TRBaseControl::UnRegisterAction(const QString & act_name) {
	return m_public_register.UnRegisterAction(act_name);
}

bool TRBaseControl::UnRegisterAction(TRBaseAction * act_object) {
	return m_public_register.UnRegisterAction(FindActionName(act_object));
}

TRBaseAction * TRBaseControl::FindAction(const QString & act_name) {
	return m_public_register.FindAction(act_name);
}

QString TRBaseControl::FindActionName(TRBaseAction * act_object) {
	return m_public_register.FindActionName(act_object);
}

void TRBaseControl::DeleteAllAction() {
	QList<TRBaseAction *> ActionList = m_public_register.AllRegisterAction().values();
	foreach(TRBaseAction * cur_action, ActionList) {
		delete cur_action;
	}
}

void TRBaseControl::DeleteAction(const QString & act_name) {
	TRBaseAction * cur_action = FindAction(act_name);
	delete cur_action;
}

bool TRBaseControl::RegisterCmd(TRBaseAction * act_object, QList<quint64> cmdList) {
	//����cmdList��ӡ����act_object��������ĵ�������Ϣ
	qDebug() << "TRLib > " << "RegisterCmd object:" << FindActionName(act_object) << hex << "commands:" << cmdList;
	return m_public_register.RegisterCmd(act_object, cmdList);
}

bool TRBaseControl::UnRegisterCmd(TRBaseAction * act_object) {
	return m_public_register.UnRegisterCmd(act_object);
}

// ��������Ⱥ��
bool TRBaseControl::RequestExecution(void * pRequester) {
	bool r = false;
	// ���������
	m_requester = pRequester;
	// ������е�BaseAction,Ⱥ��
	QHashIterator<QString, TRBaseAction*> ActionIt(m_public_register.AllRegisterAction());
	while (ActionIt.hasNext()) {
		ActionIt.next();
		r = true;
		TRBaseAction * pAction = ActionIt.value();
		if (pAction) {
			pAction->Execute();
		}
	}
	m_requester = NULL;
	return r;
}

bool TRBaseControl::RequestExecution(const quint64 & command, void * pRequester) {
	return RequestExecution(TRData::CreateDate(command), pRequester);
}

// ��������������ض���Ϣ
bool TRBaseControl::RequestExecution(const TRData::Ptr data, void * pRequester) {
	// ��Ϣ�м�¼��ǰ��������
	data->SetArgument(TR_FLG_REQUESTER, CUSTOM_TO_VARIANT(pRequester));
	m_data_distribution.InsertData(data);

	// �����Ϣת����û��������������
	if (!m_data_distribution.isRunning()) {
		m_data_distribution.start();
	}
	return true;
}

// �õ�ͬ����������Ϣ������
void * TRBaseControl::TRRequester() {
	return m_requester;
}

// �õ��첽��Ϣ����Ϣ������
void * TRBaseControl::TRRequester(const TRData::Ptr data) {
	return VARIANT_TO_CUSTOM(data->GetArgument(TR_FLG_REQUESTER), void);
}

void TRBaseControl::ActionExecution(TRBaseAction * action, const TRData::Ptr data) {
	action->Execute(data); 
}

TRBaseControl * TRBaseControl::GetTRBaseControl() {
	// ˫�ؼ����
	if (NULL == m_trbasecontrol) {
		QMutexLocker locker(&m_Mutex);
		if (NULL == m_trbasecontrol) {
			m_trbasecontrol = new TRBaseControl();
		}
	}
	return m_trbasecontrol;
}


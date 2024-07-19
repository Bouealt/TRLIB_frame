#include "TRPublicRegister.h"
#include "TRBaseAction.h"

// ===========================================================
// TRBaseData

TRData::TRData() {
	// 生成UUID码
	dataID = QUuid::createUuid().toString();
	command = 0x0;
	arguments = QVariantMap();
}

TRData::TRData(const TRData & input) {
	dataID = input.dataID;
	command = input.command;
	arguments = input.arguments;
}

TRData::~TRData() {};

QVariant TRData::GetArgument() {
	return arguments.value(TR_FLG_ARG, QVariant());
}

void TRData::SetArgument(const QVariant &value) {
	arguments.insert(TR_FLG_ARG, value);
}

QVariant TRData::GetArgument(const QString &key) {
	return arguments.value(key);
}

void TRData::SetArgument(const QString &key, const QVariant &value) {
	arguments.insert(key, value);
}

TRData::Ptr TRData::CreateDate(const quint64 &cmd) {
	// 声明一个Data付给其的智能指针
	TRData::Ptr pData(new TRData()); // 这句话可以用这两句话替换：  TRData *data = new TRData(); 
									 //						        TRData::Ptr pData = TRData::Ptr(data);
	pData->command = cmd;
	return pData;
}

TRData::Ptr TRData::CreateDate(const TRData & input) {
	TRData::Ptr pData(new TRData(input));
	return pData;
}

// ==================================================================
// TRPublicRegister

TRPublicRegister::TRPublicRegister() {
	qRegisterMetaType<QSharedPointer<TRData> >("QSharedPointer<TRBaseData>");
	qRegisterMetaType<TRData::Ptr>("TRData::Ptr");
	qRegisterMetaType<TRBaseAction>("TRBaseAction");
	qRegisterMetaType<TRBaseAction*>("TRBaseAction*");
}

bool TRPublicRegister::RegisterAction(const QString & action_name, TRBaseAction * act_object) {
	if (m_ActionHash.contains(action_name) || NULL == act_object) {
		return false;
	}
	else {
		qDebug() << "TRLib > " << "Register Object:" << action_name << act_object;
		m_ActionHash.insert(action_name, act_object);
		return m_ActionHash.contains(action_name);
	}
}

bool TRPublicRegister::UnRegisterAction(const QString & action_name) {
	qDebug() << "TRLib > " << "UnRegister Object:" << action_name << m_ActionHash.value(action_name);
	// 删除其cmd列表
	UnRegisterCmd(m_ActionHash.value(action_name));
	m_ActionHash.remove(action_name);
	return !m_ActionHash.contains(action_name);
}

bool TRPublicRegister::RegisterCmd(TRBaseAction * act_object, const QList<quint64> cmd_list) {
	if (act_object && cmd_list.size() > 0) {
		m_CmdHash.insert(act_object, cmd_list);
		return m_CmdHash.contains(act_object);
	}
	return false;
}

bool TRPublicRegister::UnRegisterCmd(TRBaseAction * act_object) {
	m_CmdHash.remove(act_object);
	return !m_CmdHash.contains(act_object);
}

bool TRPublicRegister::CheakActionCmd(TRBaseAction * act_object, quint64 command) {
	if (m_CmdHash.contains(act_object)) {
		return m_CmdHash.value(act_object).contains(command);
	}
	return false;
}

TRBaseAction * TRPublicRegister::FindAction(const QString & act_name) {
	TRBaseAction * pAction = m_ActionHash.value(act_name);
	if (!pAction) {
		qDebug() << "TRLib > " << " cannot find action: " << act_name;
	}
	return pAction;
}

QString TRPublicRegister::FindActionName(TRBaseAction * action) {
	QString ActName = m_ActionHash.key(action);
	if (ActName.isEmpty()) {
		qDebug() << "TRLib > " << "cannot find action name: " << ActName;
	}
	return ActName;
}

QHash<QString, TRBaseAction*> & TRPublicRegister::AllRegisterAction() {
	return m_ActionHash;
}
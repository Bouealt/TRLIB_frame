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

// ע����ǰ��������Ҫ�ڵ�ǰcpp�ļ�����Ӷ�Ӧ���ͷ�ļ�
class TRBaseAction;
class TRData;

// ģ��ͨ����Ϣ����
class TRData {
public:
	// ��Ϣ�ڵ�����ܹ���ָ�룬�����Ļ���
	// ���Զ�����������ÿ��ʹ����Data֮�����Ƿ���Ҫ�ֶ��ͷ���Դ
	typedef QSharedPointer<TRData> Ptr;
	TRData();
	// �������캯��
	TRData(const TRData & input);
	~TRData();

	QVariant GetArgument();
	void SetArgument(const QVariant &value);

	QVariant GetArgument(const QString &key);
	void SetArgument(const QString &key, const QVariant &value);

	static TRData::Ptr CreateDate(const quint64 &cmd = 0);
	static TRData::Ptr CreateDate(const TRData & input);


public:
	QString     dataID;         // ��ǰ��Ϣ�ڵ��ID
	quint64     command;        // ��ǰ��Ϣ�ڵ�ķ��ࡢִ����
private:
	QVariantMap arguments;		// QMap<QString, QVariant> QVariantMap���洢��Ϣ�ľ�������
};


// ģ��ע�ᡢ��Ϣע��
// ����-����ģʽ
class TRPublicRegister {
public:
	explicit TRPublicRegister();

	// ע�ᵱǰģ��
	bool RegisterAction(const QString & action_name, TRBaseAction * act_object);
	// ɾ����ǰģ��
	bool UnRegisterAction(const QString & action_name);
	// �������Action����ע��cmd
	bool RegisterCmd(TRBaseAction * act_object, const QList<quint64> cmd_list);
	// ɾ��Action�����cmd
	bool UnRegisterCmd(TRBaseAction * act_object);
	// ��⵱ǰAction�������Ƿ��ж��ĵ�ǰcmd
	bool CheakActionCmd(TRBaseAction * act_object, quint64 command);

	// ͨ������������Actionָ��
	TRBaseAction * FindAction(const QString & act_name);
	// ͨ��Actionָ���ҵ�Action����
	QString FindActionName(TRBaseAction * action);

	// ���ص�ǰ����ע�ᵽ��Action����
	QHash<QString, TRBaseAction*> & AllRegisterAction();

private:
	QHash<QString, TRBaseAction*>                    m_ActionHash;      // Action�б�
	QHash<TRBaseAction*, QList<quint64> >            m_CmdHash;         // action�����Ӧ��cmd�б�
};


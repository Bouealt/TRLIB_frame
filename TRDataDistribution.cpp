#include "TRDataDistribution.h"
#include "TRBaseControl.h"

TRDataDistribution::TRDataDistribution(TRBaseControl * control) :
	QThread(NULL),
	m_Control(control) {

}

QStringList TRDataDistribution::GetDataList() {
	return m_DataList;
}

bool TRDataDistribution::InsertData(TRData::Ptr data) {
	QMutexLocker locker(&m_Mutex);
	// ���뵽��Ϣ����
	m_DataList.append(data->dataID);
	m_DataQueue.insert(data->dataID, data);
	return m_DataList.contains(data->dataID);
}

TRData::Ptr TRDataDistribution::FindData(const QString & data_id) {
	return m_DataQueue.value(data_id);
}

void TRDataDistribution::run() {
	// ֻҪ��Ϣ���в�Ϊ��
	while (!m_DataList.isEmpty()) {
		// [1] ȡ��Ϣ
		QMutexLocker locker(&m_Mutex);
		// ��Ϣ����
		QString cur_data_id = m_DataList.takeFirst();
		TRData::Ptr cur_data = m_DataQueue.take(cur_data_id);
		if (cur_data.isNull()) {
			qWarning() << "TRLib > " << "cur data is unavailable!" << cur_data_id;
			continue;
		}

		// [2] ������Ϣ
		// ���������Ѿ�ע���Actionģ��
		QHashIterator<QString, TRBaseAction*> ActionIt(m_Control->m_public_register.AllRegisterAction());
		while (ActionIt.hasNext()) {
			ActionIt.next();
			TRBaseAction * cur_action = ActionIt.value();
			// �����ǰ��Actionģ���ж��ĵ�ǰ������͵���Ϣ����Ӧ����Ϣ
			if (cur_action && m_Control->m_public_register.CheakActionCmd(cur_action, cur_data->command)) {
				// QT��Ԫ����ϵͳ�������ò����ֱ��ǣ�1.�����ö���ָ�� 2.���ö���ķ��� 3.�������� 4.���ܱ����ú����ķ���ֵ����Ҫʹ��Q_RETURN_ARG()�����������������ƺͷ�const����
				// 5.ʣ�µĶ��Ǵ��������Ҫʹ��Q_ARG()�����������������ƺ�const���á�
				// �������ǣ������m_Control�µ�����actionģ�������������ȥExecute�����Ϣ
				QMetaObject::invokeMethod(m_Control, "ActionExecution",
					Qt::QueuedConnection,
					Q_ARG(TRBaseAction*, cur_action),
					Q_ARG(TRData::Ptr, cur_data));
			}
		}
	}
}
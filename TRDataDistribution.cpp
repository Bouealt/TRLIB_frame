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
	// 加入到消息队列
	m_DataList.append(data->dataID);
	m_DataQueue.insert(data->dataID, data);
	return m_DataList.contains(data->dataID);
}

TRData::Ptr TRDataDistribution::FindData(const QString & data_id) {
	return m_DataQueue.value(data_id);
}

void TRDataDistribution::run() {
	// 只要消息队列不为空
	while (!m_DataList.isEmpty()) {
		// [1] 取消息
		QMutexLocker locker(&m_Mutex);
		// 消息出队
		QString cur_data_id = m_DataList.takeFirst();
		TRData::Ptr cur_data = m_DataQueue.take(cur_data_id);
		if (cur_data.isNull()) {
			qWarning() << "TRLib > " << "cur data is unavailable!" << cur_data_id;
			continue;
		}

		// [2] 处理消息
		// 遍历所有已经注册的Action模块
		QHashIterator<QString, TRBaseAction*> ActionIt(m_Control->m_public_register.AllRegisterAction());
		while (ActionIt.hasNext()) {
			ActionIt.next();
			TRBaseAction * cur_action = ActionIt.value();
			// 如果当前的Action模块有订阅当前这个类型的消息，响应该消息
			if (cur_action && m_Control->m_public_register.CheakActionCmd(cur_action, cur_data->command)) {
				// QT的元对象系统，被调用参数分别是：1.被调用对象指针 2.调用对象的方法 3.连接类型 4.接受被调用函数的返回值，需要使用Q_RETURN_ARG()包裹，接受类型名称和非const引用
				// 5.剩下的都是传入参数需要使用Q_ARG()包裹，接受类型名称和const引用。
				// 这句代码是，对这个m_Control下的所有action模块操作，让他们去Execute这个消息
				QMetaObject::invokeMethod(m_Control, "ActionExecution",
					Qt::QueuedConnection,
					Q_ARG(TRBaseAction*, cur_action),
					Q_ARG(TRData::Ptr, cur_data));
			}
		}
	}
}
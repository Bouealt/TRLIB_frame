#include "TRBaseActionEx.h" 

TRBaseActionEx::TRBaseActionEx(TRBaseControl * pControl, const char * action_name) :
	QObject(),
	TRBaseAction(pControl, action_name),
	m_Control(pControl) {
	// 绑定信号槽，ToExecute(Data) -------> OnExecuteEx(Data)
	//下面的OnExecuteEx是虚函数，如果子类重写了，会优先调用子类的
	connect(this, SIGNAL(ToExecute(TRData::Ptr)), SLOT(OnExecuteEx(TRData::Ptr)), Qt::QueuedConnection);

	// 将当前对象跑在线程上
	m_Thread = new QThread;
	moveToThread(m_Thread);
	m_Thread->start();
}

TRBaseActionEx::~TRBaseActionEx() {
	// 得到当前模块名
	qDebug() << "TRLib > " << m_Control->FindActionName(this) << this << "terminate";
	// 暴力结束线程
	m_Thread->terminate();
	// 等待结束完毕
	m_Thread->wait();
	delete m_Thread;
}

void TRBaseActionEx::Execute(const TRData::Ptr data) {
	emit ToExecute(data);
}

void TRBaseActionEx::RegisterCmds() {
	// Register command to control
	TRData::Ptr registerData = TRData::CreateDate(TR_CMD_CMDREGREQUEST);
	this->Execute(registerData);
	// 因为Execute(const TRData::Ptr data)是异步执行的原因，所以这里延迟3秒然后调用OnRegisterCommands
	QTimer::singleShot(3000, this, SLOT(OnRegisterCommands()));
}


void TRBaseActionEx::OnExecuteEx(TRData::Ptr data) {
	qDebug() << "TRLib > " << "ActionEx_Execute:" << hex << data->command << data->dataID;
}

void TRBaseActionEx::OnRegisterCommands() {
	m_Control->RegisterCmd(this, m_CmdList);
}
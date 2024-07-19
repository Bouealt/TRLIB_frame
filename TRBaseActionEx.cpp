#include "TRBaseActionEx.h" 

TRBaseActionEx::TRBaseActionEx(TRBaseControl * pControl, const char * action_name) :
	QObject(),
	TRBaseAction(pControl, action_name),
	m_Control(pControl) {
	// ���źŲۣ�ToExecute(Data) -------> OnExecuteEx(Data)
	//�����OnExecuteEx���麯�������������д�ˣ������ȵ��������
	connect(this, SIGNAL(ToExecute(TRData::Ptr)), SLOT(OnExecuteEx(TRData::Ptr)), Qt::QueuedConnection);

	// ����ǰ���������߳���
	m_Thread = new QThread;
	moveToThread(m_Thread);
	m_Thread->start();
}

TRBaseActionEx::~TRBaseActionEx() {
	// �õ���ǰģ����
	qDebug() << "TRLib > " << m_Control->FindActionName(this) << this << "terminate";
	// ���������߳�
	m_Thread->terminate();
	// �ȴ��������
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
	// ��ΪExecute(const TRData::Ptr data)���첽ִ�е�ԭ�����������ӳ�3��Ȼ�����OnRegisterCommands
	QTimer::singleShot(3000, this, SLOT(OnRegisterCommands()));
}


void TRBaseActionEx::OnExecuteEx(TRData::Ptr data) {
	qDebug() << "TRLib > " << "ActionEx_Execute:" << hex << data->command << data->dataID;
}

void TRBaseActionEx::OnRegisterCommands() {
	m_Control->RegisterCmd(this, m_CmdList);
}
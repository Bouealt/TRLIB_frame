#include "TRLIB.h"


TRLIB::TRLIB(QWidget *parent)
    : QMainWindow(parent) {
      ui.setupUi(this);
	  cur_action = new TRBaseActionEx(TRBaseControl::GetTRBaseControl(), "TR_OBJ_TEST_ALL");

	// 创建按钮
	m_SignalOne = new QPushButton("One", this);
	m_SignalTwo = new QPushButton("Two", this);
	m_SignalThree = new QPushButton("Three", this);
	m_SignalOne->setGeometry(10, 50, 50, 30);
	m_SignalTwo->setGeometry(100, 10, 50, 30);
	m_SignalThree->setGeometry(100, 50, 50, 30);
	connect(m_SignalOne, SIGNAL(clicked()), this, SLOT(OnButtonClicked()));
	connect(m_SignalTwo, SIGNAL(clicked()), this, SLOT(OnButtonClicked()));
	connect(m_SignalThree, SIGNAL(clicked()), this, SLOT(OnButtonClicked()));

	// 客户端对象
	localClientA = new LocalClientA(this);
	localClientB = new LocalClientB();
	localClientC = new LocalClientC();
}

TRLIB::~TRLIB() {

}


void TRLIB::OnButtonClicked() {
	qDebug() << QThread::currentThreadId() << "main";
	QPushButton *btn = qobject_cast<QPushButton*>(sender());	
	
	if (btn == m_SignalOne) {
		TR_REQUESTEXECUTION(TEST_CMD1);
		//TR_REQUESTEXECUTION_ALL_ACT;
	}
	else if (btn == m_SignalTwo) {
		TR_REQUESTEXECUTION(TEST_CMD2);
	}
	else
	{
		//TR_REQUESTEXECUTION(TEST_CMD3);
		TR_REQUESTEXECUTION_ALL_ACT;
	}
}
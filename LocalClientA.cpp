#include "LocalClientA.h"
#include <QApplication>


LocalClientA::LocalClientA(QWidget *parent)
	:TRBaseActionEx(TRBaseControl::GetTRBaseControl(), "TR_OBJ_CLIENTA"), QTextEdit(parent) {
	RegisterCmds();
}

LocalClientA::~LocalClientA() {
	qDebug() << "LocalClientA >   LocalClientA close";
}

void LocalClientA::TestFunc2() {
	qDebug() << QThread::currentThreadId() << "LocalClientA2";
	qDebug() << "test A Ok too!";
}

void LocalClientA::TestFunc3() {
	qDebug() << QThread::currentThreadId() << "LocalClientA3";
	qDebug() << "test A Ok three!";
}


void LocalClientA::OnExecuteEx(const TRData::Ptr data) {
	qDebug() << QThread::currentThreadId() << "LocalClientA1";
	// C++ Óï·¨ÌÇ£ºhttps://www.jianshu.com/p/932812748138
	auto TestFunc1 = [] {
		qDebug() << "test Ok!";
	};

	/*switch (data->command) {
	case FYTS_CMD_QUIT: {
		qApp->quit();
	}
	break;

	case FYTS_CMD_CRY: {
		 append(data->GetArgument().toString());
	}
	break;
	default:
		break;
	}*/

	// ·Ç×èÈû²âÊÔ
	TR_CMD_CONNECT_EXEC(TEST_CMD1, TestFunc1());
	TR_CMD_CONNECT_EXEC(TEST_CMD2, TestFunc2());
	TR_CMD_CONNECT_EXEC(TEST_CMD3, TestFunc3());
}



#include "LocalClientB.h"
#include <QApplication>


LocalClientB::LocalClientB()
	:TRBaseActionEx(TRBaseControl::GetTRBaseControl(), "TR_OBJ_CLIENTB") {
	RegisterCmds();
}

LocalClientB::~LocalClientB() {
	qDebug() << "LocalClientB >   LocalClientB close";
}

void LocalClientB::TestFunc2() {
	qDebug() << QThread::currentThreadId() << "LocalClientB2";
	qDebug() << "test B Ok too!";
}


void LocalClientB::OnExecuteEx(const TRData::Ptr data) {
	qDebug() << QThread::currentThreadId() << "LocalClientB1";
	// C++ Óï·¨ÌÇ£ºhttps://www.jianshu.com/p/932812748138
	auto TestFunc1 = [] {
		qDebug() << "test Ok!";
	};

	switch (data->command) {
	case FYTS_CMD_QUIT: {
		qApp->quit();
	}
						break;

	case FYTS_CMD_CRY: {
		// append(data->GetArgument().toString());
	}
					   break;
	default:
		break;
	}

	// ·Ç×èÈû²âÊÔ
	TR_CMD_CONNECT_EXEC(TEST_CMD1, TestFunc1());
	TR_CMD_CONNECT_EXEC(TEST_CMD2, TestFunc2());
}


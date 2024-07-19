#include "LocalClientC.h"
#include <QApplication>


LocalClientC::LocalClientC()
	:TRBaseAction(TRBaseControl::GetTRBaseControl(), "TR_OBJ_CLIENTC") {
	RegisterCmds();
}

LocalClientC::~LocalClientC() {
	qDebug() << "LocalClientC >   LocalClientC close";
}

void LocalClientC::TestFunc2() {
	qDebug() << QThread::currentThreadId() << "LocalClientC2";
	qDebug() << "test C Ok too!";
}


void LocalClientC::Execute(const TRData::Ptr data) {
	qDebug() << QThread::currentThreadId() << "LocalClientC1";
	// C++ Óï·¨ÌÇ£ºhttps://www.jianshu.com/p/932812748138
	auto TestFunc1 = [] {
		qDebug() << "test Ok!";
	};

	// ·Ç×èÈû²âÊÔ
	TR_CMD_CONNECT_EXEC(TEST_CMD1, TestFunc1());
	TR_CMD_CONNECT_EXEC(TEST_CMD2, TestFunc2());
}



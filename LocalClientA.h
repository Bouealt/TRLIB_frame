#pragma once
#ifndef LOCALCLIENTA_H
#define LOCALCLIENTA_H
#include <QTextEdit>
#include "TRBaseActionEx.h"
#include "TRBaseControl.h"
#include "TR_test_global.h"

class LocalClientA : public TRBaseActionEx, public QTextEdit{
	Q_OBJECT
public:
	LocalClientA(QWidget *parent);
	~LocalClientA();

	void TestFunc2();
	void TestFunc3();

protected:
	virtual void OnExecuteEx(const TRData::Ptr data);
};

#endif // !LOCALCLIENTA_H




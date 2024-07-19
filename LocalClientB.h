#pragma once
#ifndef LOCALCLIENTB_H
#define LOCALCLIENTB_H
#include <QTextEdit>
#include "TRBaseActionEx.h"
#include "TRBaseControl.h"
#include "TR_test_global.h"

class LocalClientB : public TRBaseActionEx {
	Q_OBJECT
public:
	LocalClientB();
	~LocalClientB();

	void TestFunc2();

protected:
	virtual void OnExecuteEx(const TRData::Ptr data);
};

#endif // !LOCALCLIENTB_H



#pragma once
#ifndef LOCALCLIENTC_H
#define LOCALCLIENTC_H

#include "TRBaseAction.h"
#include "TRBaseControl.h"
#include "TR_test_global.h"

class LocalClientC : public TRBaseAction {
public:
	LocalClientC();
	~LocalClientC();

	void TestFunc2();

protected:
	virtual void Execute(const TRData::Ptr data);
};

#endif // !LOCALCLIENTB_H
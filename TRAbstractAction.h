#pragma once
#ifndef TRABSTRACTACTION_H
#define TRABSTRACTACTION_H

#include "TRPublicRegister.h"

class TRAbstractAction {
public:
	virtual ~TRAbstractAction() {}
	virtual void Execute() = 0;
	virtual void Execute(const TRData::Ptr data) = 0;
};

#endif // !TRABSTRACTACTION_H

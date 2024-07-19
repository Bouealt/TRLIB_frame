#pragma once
#ifndef TRABSTRACTCONTROL_H
#define TRABSTRACTCONTROL_H

#include <QString>

#define TRSDKVERSION QString("V1.0")

// 版本管理，模块信息等
class TRAbstractControl {
public:
	QString TRSDKVersion() {
		return TRSDKVERSION;
	}
};

#endif // !TRABSTRACTCONTROL_H




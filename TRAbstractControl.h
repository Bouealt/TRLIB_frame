#pragma once
#ifndef TRABSTRACTCONTROL_H
#define TRABSTRACTCONTROL_H

#include <QString>

#define TRSDKVERSION QString("V1.0")

// �汾����ģ����Ϣ��
class TRAbstractControl {
public:
	QString TRSDKVersion() {
		return TRSDKVERSION;
	}
};

#endif // !TRABSTRACTCONTROL_H




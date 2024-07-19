#include "TRBaseAction.h"
#include "TRBaseControl.h"

TRBaseAction::TRBaseAction(TRBaseControl *pControl, const char *act_name) :
	m_Control(pControl),
	m_CmdList(QList<quint64>()) {
	if (act_name) {
		if (m_Control) { 
			// ×¢²áµ±Ç°Ä£¿é
			if (m_Control->RegisterAction(act_name, this)) {
				m_ActionName = act_name;
			}
		}
	}
}

TRBaseAction::~TRBaseAction() {
	if (m_Control) {
		m_Control->UnRegisterAction(this);
	}
}

QString TRBaseAction::ActionName() {
	return m_ActionName;
}

void TRBaseAction::RegisterCmds() {
	TRData::Ptr register_data = TRData::CreateDate(TR_CMD_CMDREGREQUEST);
	this->Execute(register_data);
	m_Control->RegisterCmd(this, m_CmdList);
}



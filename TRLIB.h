#pragma once

#include <QtWidgets>
#include "TRBaseActionEx.h"
#include "TRBaseControl.h"
#include "LocalClientA.h"
#include "LocalClientB.h"
#include "LocalClientC.h"

#include "ui_TRLIB.h"

class TRLIB : public QMainWindow
{
    Q_OBJECT

public:
    TRLIB(QWidget *parent = Q_NULLPTR);
	~TRLIB();

private slots:
	void OnButtonClicked();

private:
	QPushButton *m_SignalOne;
	QPushButton *m_SignalTwo;
	QPushButton *m_SignalThree;
	TRBaseActionEx * cur_action;
	LocalClientA * localClientA;
	LocalClientB * localClientB;
	LocalClientC * localClientC;

private:;
    Ui::TRLIBClass ui;
};

#pragma once
#ifndef TR_GLOBEL_H
#define TR_GLOBEL_H

#include <QtCore/qglobal.h>

// ǰ8λʮ������λ��0x0000 0000 ffff ffff���趨Ϊ���û�����
// ��8λʮ������λ��0xffff ffff 0000 0000���趨Ϊ��������
/// Argument Key
#define TR_FLG_ARG                "TR_DataFlag_Arguments"
#define TR_FLG_REQUESTER		  "TR_DataFlag_Requester"

/// Data Cmd
#define TR_CMD_NON				  0x0000000000000001ULL	  // û��data��Ĭ��
#define TR_CMD_CMDREGREQUEST      0x0000000000000002ULL   // TR_Cmd_CommandRegisterRequest

#endif // !TR_GLOBEL_H

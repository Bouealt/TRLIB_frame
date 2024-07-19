#pragma once
#ifndef TR_GLOBEL_H
#define TR_GLOBEL_H

#include <QtCore/qglobal.h>

// 前8位十六进制位（0x0000 0000 ffff ffff）设定为“用户命令
// 后8位十六进制位（0xffff ffff 0000 0000）设定为“框架命令”
/// Argument Key
#define TR_FLG_ARG                "TR_DataFlag_Arguments"
#define TR_FLG_REQUESTER		  "TR_DataFlag_Requester"

/// Data Cmd
#define TR_CMD_NON				  0x0000000000000001ULL	  // 没有data，默认
#define TR_CMD_CMDREGREQUEST      0x0000000000000002ULL   // TR_Cmd_CommandRegisterRequest

#endif // !TR_GLOBEL_H

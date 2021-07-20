// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H
#define PCH_H

// 添加要在此处预编译的标头
#include "framework.h"
#include <afxsock.h>

enum { SERVER_PORT = 35671 };
//网络协议编号
enum {
	WK_PRINT = 0x100,
	WK_INSERT,
	WK_DELETE,
	WK_MODIFY,
	WK_CHECK_NUMB,
	WK_FIND_NUMB,
	WK_FIND_NAME,
	WK_FIND_SALA,
	WK_FIND_DATE,

	ADM_LOGIN = 0x200,
	ADM_PRINT,
	ADM_INSERT,
	ADM_DELETE,
	ADM_CHPASS,

};
struct SInfo
{
	int nNumb;
	char sName[20];
	float fSala;
	char sDate[20];
};

struct SAdmin
{
	char sName[20];
	char sPass[20];
	int nPrior;
	int nState;
};

#endif //PCH_H

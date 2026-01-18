
// 连元小学学生成绩管理系统MFC.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号


// C连元小学学生成绩管理系统MFCApp:
// 有关此类的实现，请参阅 连元小学学生成绩管理系统MFC.cpp
//

class C连元小学学生成绩管理系统MFCApp : public CWinApp
{
public:
	C连元小学学生成绩管理系统MFCApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern C连元小学学生成绩管理系统MFCApp theApp;

// DbDriver.h : DbDriver DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSqlAPIApp
// �йش���ʵ�ֵ���Ϣ������� DbDriver.cpp
//

class CDbDriverApp : public CWinApp
{
public:
	CDbDriverApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

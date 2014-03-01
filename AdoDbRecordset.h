#pragma once

#include "SqlDriver.h"



class COMMON_DBLIB CAdoRecordset:public CDbRecordSet
{
public:
	CAdoRecordset(_RecordsetPtr pRecordset);
	~CAdoRecordset(void);
public:
	//ȡ�ֶθ���	
	int GetFieldNum();
	// �ֶ��� 
	string GetFieldName(long lIndex);	
	int GetIndex(char* strFieldName);
	// �ֶ��������� 
	int GetFieldType(long lIndex);
	int GetFieldType(char* lpszFieldName);
	
	// �ֶζ��峤��
	int  GetFieldDefineSize(long lIndex);
	int  GetFieldDefineSize(char* lpszFieldName);
	
	//�ֶ��ж��Ƿ�ΪNULL
	bool IsFieldNull(char* lpFieldName);
	bool IsFieldNull(int nIndex);
public:
	bool IsNull();
	bool IsEmpty();
	bool IsNullEmpty();
	void clear();

	//�ж�ִ���Ƿ�ɹ�
	virtual bool IsSuccess();
public:
	bool IsEOF();
	bool IsBOF();

	void MoveFirst() ;
	void MoveNext();
	void MovePrevious() ;
	void MoveLast() ;

	//���ù��λ��
	long GetCursorPos();
	long SetCursorPos(long i);

	//ȡ���������
	int GetRowNum();

	//��ȡ����ʵ�ʳ���
 	int GetValueSize(long lIndex);
 	int GetValueSize(char* lpszFieldName);

	bool GetValue(int nColumns, _variant_t& vt, bool &nIsNull );
	bool GetValue(char* strFieldName, _variant_t& vt, bool &nIsNull );
	
	bool GetValue(int nColumns, bool& bValue, bool &nIsNull );
	bool GetValue(char* strFieldName, bool& bValue, bool &nIsNull );

	bool GetValue(int nColumns, byte& nValue, bool &nIsNull );
	bool GetValue(char* strFieldName, byte& nValue, bool &nIsNull );

	bool GetValue(int nColumns, short& nValue, bool &nIsNull );
	bool GetValue(char* strFieldName, short& fValue, bool &nIsNull );

	bool GetValue(int nColumns, int& nValue, bool &nIsNull );
	bool GetValue(char* strFieldName, int& nValue, bool &nIsNull );

	bool GetValue(int nColumns, long& lValue, bool &nIsNull );
	bool GetValue(char* strFieldName, long& lValue, bool &nIsNull );

	bool GetValue(int nColumns, __int64& lValue, bool &nIsNull );
	bool GetValue(char* strFieldName, __int64& lValue, bool &nIsNull );

	bool GetValue(int nColumns, float& fValue, bool &nIsNull );
	bool GetValue(char* strFieldName, float& fValue, bool &nIsNull );

	bool GetValue(int nColumns, double& dValue, bool &nIsNull );
	bool GetValue(char* strFieldName, double& dValue, bool &nIsNull );
	
	bool GetValue(int nColumns, string& strValue, bool &nIsNull );
	bool GetValue(char* strFieldName, string& strValue, bool &nIsNull );

	bool GetValue(int nColumns, char* strValue, short len,bool &nIsNull);
	bool GetValue(char* strFldName, char* strValue, short len, bool &nIsNull);
	
	bool GetValue(int nColumns, tm& time, bool &nIsNull );
	bool GetValue(char* strFieldName, tm& time, bool &nIsNull );

	bool GetValue(int nColumns, byte** bDat, long *len, bool &nIsNull );
	bool GetValue(char* strFieldName, byte** bDat, long *len, bool &nIsNull );

private:
	_RecordsetPtr m_pRecordset;
	byte* m_blobData;
};

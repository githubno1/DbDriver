#pragma once
#include "SqlDriver.h"

#define SWAP16PTR(x) \
{                                                                 \
	byte       byTemp, *_pabyDataT = (byte *) (x);              \
	\
	byTemp = _pabyDataT[0];                                       \
	_pabyDataT[0] = _pabyDataT[1];                                \
	_pabyDataT[1] = byTemp;                                       \
}                                                                    

#define SWAP32PTR(x) \
{                                                                 \
	byte       byTemp, *_pabyDataT = (byte *) (x);              \
	\
	byTemp = _pabyDataT[0];                                       \
	_pabyDataT[0] = _pabyDataT[3];                                \
	_pabyDataT[3] = byTemp;                                       \
	byTemp = _pabyDataT[1];                                       \
	_pabyDataT[1] = _pabyDataT[2];                                \
	_pabyDataT[2] = byTemp;                                       \
}                                                                    

#define SWAP64PTR(x) \
{                                                                 \
	byte    byTemp, *_pabyDataT = (byte *) (x);              \
	\
	byTemp = _pabyDataT[0];                                       \
	_pabyDataT[0] = _pabyDataT[7];                                \
	_pabyDataT[7] = byTemp;                                       \
	byTemp = _pabyDataT[1];                                       \
	_pabyDataT[1] = _pabyDataT[6];                                \
	_pabyDataT[6] = byTemp;                                       \
	byTemp = _pabyDataT[2];                                       \
	_pabyDataT[2] = _pabyDataT[5];                                \
	_pabyDataT[5] = byTemp;                                       \
	byTemp = _pabyDataT[3];                                       \
	_pabyDataT[3] = _pabyDataT[4];                                \
	_pabyDataT[4] = byTemp;                                       \
}                                                                    

#define SWAPDOUBLE(p) SWAP64PTR(p)

class COMMON_DBLIB CPgDbRecordset:public CDbRecordSet
{
public:
	CPgDbRecordset(PGresult* pRes);
	~CPgDbRecordset(void);
public:
	//ȡ�ֶθ���
	int GetFieldNum();
	// �ֶ��� 
	string GetFieldName(long lIndex);	
	int GetIndex(char* strFieldName);
	// �ֶ��������� 
	int GetFieldType(long lIndex);
	int GetFieldType(char* strFieldName);
	
	// �ֶζ��峤��
	int  GetFieldDefineSize(long lIndex);
	int  GetFieldDefineSize(char* strFieldName);
	
	//�ֶ��ж��Ƿ�ΪNULL
 	bool IsFieldNull(char* lpFieldName);
 	bool IsFieldNull(int nIndex); 
public:
	bool IsNull();
	bool IsEmpty();
	bool IsNullEmpty();
	void clear();

	//�ж�ִ���Ƿ�ɹ�
	bool IsSuccess();
public:
	bool IsEOF();
	bool IsBOF();

	//����ƶ�
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
	PGresult*  m_pResult;
	int m_nCurrentRow;
};

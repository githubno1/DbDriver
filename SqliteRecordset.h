#pragma once
#include "SqlDriver.h"

//
//#include "spatialite.h"
//#include "spatialite/gaiageo.h"
//#pragma  comment(lib,"freexl_i.lib")
//#pragma  comment(lib,"gdal_i.lib")
//#pragma  comment(lib,"geos_c_i.lib")
//#pragma  comment(lib,"spatialite_i.lib")
//#pragma  comment(lib,"freexl_i.lib")
//#pragma  comment(lib,"geotiff_i.lib")
//#pragma  comment(lib,"iconv.lib")
//#pragma  comment(lib,"proj_i.lib")


#include "sqlite3.h"
#pragma comment(lib,"sqlite3.lib")
//}
class COMMON_DBLIB CSqliteRecordset : public CDbRecordSet
{
public:
	CSqliteRecordset(void);
	CSqliteRecordset(sqlite3_stmt *stmt);
	~CSqliteRecordset(void);
public:

	//�ֶ���
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
	bool IsFieldNull(int nIndex) ;

public:
	void clear();
	// �жϲ�ѯ������Ƿ�ΪNULL
	bool IsNull();
	// �жϽ�����Ƿ�Ϊempty(����Ϊ0)
	bool IsEmpty();
	bool IsNullEmpty();

	//�ж�ִ���Ƿ�ɹ�
	bool IsSuccess();
public:
	bool IsEOF();
	bool IsBOF();

	//��ѯ���������ƶ�
	void MoveFirst();
	void MoveNext();
	void MovePrevious(){};
	void MoveLast();

	//���ù��λ��(��1����)
	virtual long GetCursorPos();
	virtual long SetCursorPos(long i);
    
	//ȡ����
	int GetRowNum();

	//��ȡ����ʵ�ʳ���
	int GetValueSize(long lIndex);
	int GetValueSize(char* lpszFieldName);

	//��ȡ����
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
	void InitRowNum();
	int AnalyType(CString strType);
	tm& AnalyDateTime(char* strDateTime);
	
private:
	/*char **m_Recordset;*/
	sqlite3_stmt *m_stmt;
	long m_lRows;   //����
	long m_lCols;  //����
	long m_lCur;  //���λ��(��1����)
};

#include "StdAfx.h"
#include "SqliteRecordset.h"
#include "CodingConv.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CSqliteRecordset::CSqliteRecordset(void)
{
	//m_Recordset = NULL;
	m_lRows = 0;
	m_lCols = 0;
	m_lCur = 0;
    m_stmt = NULL;
}
CSqliteRecordset::CSqliteRecordset(sqlite3_stmt *stmt)
{
	m_lCur = 0;
    m_stmt =stmt;
	m_lCols = sqlite3_column_count(stmt);
	InitRowNum();
}

CSqliteRecordset::~CSqliteRecordset(void)
{
	clear();
}

 //�ֶ��� 
string CSqliteRecordset::GetFieldName(long lIndex)
{
	ASSERT(m_stmt != NULL);

	return sqlite3_column_name(m_stmt,lIndex);
}

//�ֶ����
int CSqliteRecordset::GetIndex(char* strFieldName)
{
	ASSERT(m_stmt != NULL);

	char *szFieldName = new char[50];
	CCodingConv::GB2312_2_UTF8(szFieldName,50,strFieldName,(int)strlen(strFieldName));//��GB2312����תΪUTF8����

	for (long i=0; i<m_lCols ;i++)
	{
		string name = sqlite3_column_name(m_stmt,i);
		if(name == szFieldName)
			return i;
	}

	return -1;
}
//���������ʹ��ַ���תΪint
int CSqliteRecordset::AnalyType(CString strType)
{
	strType.MakeUpper();
	//ƥ������
    //������ֵ
   
	if(strType == "TINYINT")
		return FLD_CHAR;

	else if(strType == "INT2")
		return FLD_INT2; 

	else if(strType == "MEDIUMINT")
		return FLD_INT4; 

	else if (strType == "SMALLINT" || strType == "INTEGER" || strType == "INT"  ||strType == "INT4" )
		return FLD_INT4;

	else if( strType == "UNSIGNED BIG INT") //�µģ�δ�ҵ�����
		return FLD_INT8; 

	else if ( strType == "BIGINT" || strType == "INT8")
       return FLD_INT8;

	//�ַ���
	else if(strType.Find("VARYING CHARACTER") >=0 || strType.Find("NATIVE CHARACTER") >=0 ||  strType.Find("CHARACTER") >=0 ||
		strType.Find("NVARCHAR") >=0 || strType.Find("VARCHAR") >=0 || strType.Find("NCHAR") >=0 ||
		strType.Find("CHAR(") >=0 || strType== "TEXT" || strType == "CLOB")
		return FLD_VARCHAR;
   
    //������
	else if(strType=="FLOAT" || strType=="FLOAT4" )
		return FLD_FLOAT;

	else  if(strType == "DOUBLE" || strType == "DOUBLE PRECISION" || strType == "FLOAT8" || strType == "REAL")
		return FLD_DOUBLE;

    //numinc
	else if(strType == "DATE" )//����
		return FLD_DATE;

	else if(strType == "TIME")//ʱ��
		return FLD_TIME;

	else if(strType == "DATETIME")//����ʱ��
		return FLD_DATETIME;

	else if(strType == "BOOLEAN")
		return FLD_BOOL;

	else if(strType == "NUMERIC" || strType.Find("DECIMAL(")) //�����渡�����ݵ��ַ���
	    return FLD_NUMERIC;

    //������
	else if(strType == "BLOB" || strType == "TINYBLOB" || strType == "MEDIUMBLOB" || strType == "LONGBLOB" || strType == "BYTEA")
		return FLD_BLOB;

	//��
	else
		return FLD_UNKNOWN;

}

// �ֶ��������� 
int CSqliteRecordset::GetFieldType(long lIndex)
{
    ASSERT(m_stmt != NULL);
	char* szType= const_cast<char*>(sqlite3_column_decltype(m_stmt,lIndex)); 

	return AnalyType(szType);
}
int CSqliteRecordset::GetFieldType(char* lpszFieldName)
{ 
	ASSERT(m_stmt != NULL);

	long lIndex=GetIndex(lpszFieldName);
	char* szType= const_cast<char*>(sqlite3_column_decltype(m_stmt,lIndex)); 
	
	return AnalyType(szType);
}

// �ֶζ��峤��
int  CSqliteRecordset::GetFieldDefineSize(long lIndex)
{
	ASSERT(m_stmt != NULL);
	CString strType= (CString)const_cast<char*>(sqlite3_column_decltype(m_stmt,lIndex));
	int nPos1(-1),nPos2(-1);

	nPos1 = strType.Find('(');
	if(nPos1<0)
		return 0;

	nPos2 = strType.Find(')');
	if(nPos2<0)
		return 0;

     CString strLength = strType.Mid(nPos1+1,nPos2-nPos1-1);

	return  atoi(strLength);
}

int  CSqliteRecordset::GetFieldDefineSize(char* strFieldName)
{
	ASSERT(m_stmt != NULL);

	long lIndex = GetIndex(strFieldName);
	CString strType= (CString)const_cast<char*>(sqlite3_column_decltype(m_stmt,lIndex));
	int nPos1(-1),nPos2(-1);

	nPos1 = strType.Find('(');
	if(nPos1<0)
		return 0;

	nPos2 = strType.Find(')');
	if(nPos2<0)
		return 0;

	CString strLength = strType.Mid(nPos1+1,nPos2-nPos1-1);

	return  atoi(strLength);
}

//�ֶ��ж��Ƿ�ΪNULL
bool CSqliteRecordset::IsFieldNull(char* lpFieldName) 
{
    int type = GetFieldType(lpFieldName); //
	return type == SQLITE_NULL;
}

bool CSqliteRecordset::IsFieldNull(int nIndex) 
{
    int type = GetFieldType(nIndex);
	return type == SQLITE_NULL;
}

//������ݼ�
void CSqliteRecordset::clear()
{
	if (m_stmt != NULL)
		sqlite3_finalize(m_stmt);  
}

// �жϲ�ѯ������Ƿ�ΪNULL
bool CSqliteRecordset::IsNull()
{
	if (m_stmt == NULL)
		return true;

	return false;
}

//������Ƿ�Ϊ��
bool CSqliteRecordset::IsEmpty()
{
	if (m_stmt != NULL && sqlite3_column_count(m_stmt) <= 0)
		return true;

	return false;
}
bool CSqliteRecordset::IsNullEmpty()
{
	if (m_stmt == NULL || sqlite3_column_count(m_stmt) <= 0)
		return true;

	return false;
}

//�ж�ִ���Ƿ�ɹ�
bool CSqliteRecordset::IsSuccess()
{
	if (m_stmt != NULL)
		return true;

	return false;
}

//�Ƿ�Ϊ���һ����¼
bool CSqliteRecordset::IsEOF()
{
	return m_lCur == m_lRows;
}

//�Ƿ�Ϊ��һ����¼
bool CSqliteRecordset::IsBOF()
{
	return m_lCols == 1;
}

//��ѯ���������ƶ�
//�Ƶ���һ����¼
void CSqliteRecordset::MoveFirst()
{
	ASSERT(m_stmt != NULL);
	
	if(m_lCur != 1)
       sqlite3_reset(m_stmt);

	int ret = sqlite3_step(m_stmt);
	if (ret != SQLITE_DONE && ret != SQLITE_ROW)
	{
		sqlite3_finalize(m_stmt);
		return;
	}

    m_lCur = 1;
}
//��һ����¼
void CSqliteRecordset::MoveNext()
{
	ASSERT(m_stmt != NULL);
	int ret = sqlite3_step(m_stmt);
	if (ret != SQLITE_DONE && ret != SQLITE_ROW)
	{
		sqlite3_finalize(m_stmt);
		return;
	}
	m_lCur ++;
}
//void CSqliteRecordset::MovePrevious()
//�Ƶ����һ����¼
void CSqliteRecordset::MoveLast()
{
	ASSERT(m_stmt != NULL);

	int ret;
	while (m_lCur < m_lRows)
	{
		 ret = sqlite3_step(m_stmt);
		if (ret != SQLITE_DONE && ret != SQLITE_ROW)
		{
			sqlite3_finalize(m_stmt);
			return;
		}
		m_lCur++;
	}
	
}

//ȡ���λ��
long CSqliteRecordset::GetCursorPos()
{
	return m_lCur;
}
//���ù��λ��
long CSqliteRecordset::SetCursorPos(long i)
{
	ASSERT(m_stmt != NULL);
	
	if (i<1)
		return -1;

	if(i == m_lCur)//���õĹ��λ��Ϊ��ǰλ��
		return 1;

	int ret;
	m_lCur = 0;
	sqlite3_reset(m_stmt);//����SQL���

	do 
	{
		ret = sqlite3_step(m_stmt);
		if (ret != SQLITE_DONE && ret != SQLITE_ROW)
		{
			sqlite3_finalize(m_stmt);
			return -1;
		}
		m_lCur++;
	} while (m_lCur < i);

	return 1;
}

//�ֶ���
int CSqliteRecordset::GetFieldNum() 
{
	ASSERT(m_stmt != NULL);
	return m_lCols;
}

//����
int CSqliteRecordset::GetRowNum()
{
	ASSERT(m_stmt != NULL);
	return m_lRows; 
}

//ȡ����
int CSqliteRecordset::GetValueSize(long lIndex)
{
	return 0;
}

int CSqliteRecordset::GetValueSize(char* lpszFieldName)
{
	return 0;
}

bool CSqliteRecordset::GetValue(int nColumns, bool& bValue, bool &nIsNull )
{
	ASSERT(m_stmt != NULL);
	if(nColumns < 0)
		return false;

	int nValue = sqlite3_column_int(m_stmt,nColumns);
	if (nValue == 1)
		bValue = true;
	else
		bValue = false;

	return true;
}
bool CSqliteRecordset::GetValue(char* strFieldName, bool& bValue, bool &nIsNull )
{
	ASSERT(m_stmt != NULL);
	int nIndex = GetIndex(strFieldName);
	if (nIndex < 0)
		return false;

	int nValue = sqlite3_column_int(m_stmt,nIndex);
	if (nValue == 1)
		bValue = true;
	else
		bValue = false;

	return true;
}
bool CSqliteRecordset::GetValue(int nColumns, byte& nValue, bool &nIsNull )//int1
{
	ASSERT(m_stmt != NULL);
	if(nColumns < 0)
		return false;

	int values = sqlite3_column_int(m_stmt,nColumns);
	nValue = (byte)values;
	return true;
}
bool CSqliteRecordset::GetValue(char* strFieldName, byte& nValue, bool &nIsNull )
{
	ASSERT(m_stmt != NULL);
	int nIndex = GetIndex(strFieldName);
	if (nIndex < 0)
		return false;

	int values = sqlite3_column_int(m_stmt,nIndex);
	nValue = (byte)values;
	return true;
}

bool CSqliteRecordset::GetValue(int nColumns, float& fValue, bool &nIsNull ) 
{
	ASSERT(m_stmt != NULL);
	if(nColumns < 0)
		return false;

	fValue = (float)sqlite3_column_double(m_stmt,nColumns);
	return true;
}

bool CSqliteRecordset::GetValue(char* strFieldName, float& fValue, bool &nIsNull)
{
     ASSERT(m_stmt != NULL);
	 int nIndex = GetIndex(strFieldName);
	 if (nIndex < 0)
	 return false;

	 fValue = (float)sqlite3_column_double(m_stmt,nIndex);
	 return true;
}

bool CSqliteRecordset::GetValue(int nColumns, long& lValue, bool &nIsNull )
{
	ASSERT(m_stmt != NULL);
	if(nColumns < 0)
		return false;

	lValue = (long)sqlite3_column_int(m_stmt,nColumns);
	return true;
}

 bool CSqliteRecordset::GetValue(char* strFieldName, long& lValue, bool &nIsNull )
 {
	 ASSERT(m_stmt != NULL);
	 int nIndex = GetIndex(strFieldName);
	 if (nIndex < 0)
		 return false;

	 lValue = (long)sqlite3_column_int(m_stmt,nIndex);
	 return true;
 }

 bool CSqliteRecordset::GetValue(int nColumns, string& strValue, bool &nIsNull) 
 {
	 ASSERT(m_stmt != NULL);
	 if(nColumns < 0)
		 return false;

	 strValue = (string)(char*)sqlite3_column_text(m_stmt,nColumns);
	 if (strValue.length() < 1)
		 return false;

	 char* szGBKValue = new char[strValue.length()];
	 CCodingConv::UTF8_2_GB2312(szGBKValue,(int)strValue.length()+1,strValue.c_str(),(int)strValue.length());//��UTF8�����ַ�תΪGBK
     strValue = szGBKValue;

	 return true;
 }
bool CSqliteRecordset::GetValue(char* strFieldName, string& strValue, bool &nIsNull)
{
	ASSERT(m_stmt != NULL);
	int nIndex = GetIndex(strFieldName);
	if (nIndex < 0)
		return false;

	strValue = (string)(char*)sqlite3_column_text(m_stmt,nIndex);
	if (strValue.length() < 1)
		return false;

	char* szGBKValue = new char[strValue.length()];
	CCodingConv::UTF8_2_GB2312(szGBKValue,(int)strValue.length()+1,strValue.c_str(),(int)strValue.length());//��UTF8�����ַ�תΪGBK
	strValue = szGBKValue;
	return true;  
}

bool CSqliteRecordset::GetValue(int nColumns, char* strValue, short len,bool &nIsNull)
{
	ASSERT(m_stmt != NULL);
 	if(nColumns < 0)
		return false;

	char * szValue = (char*)sqlite3_column_text(m_stmt,nColumns);
	if (szValue == NULL)
		return false;

     CCodingConv::UTF8_2_GB2312(strValue,len,szValue,(int)strlen(szValue));

	//strcpy_s(strValue,len,szValue);
	return true;
}
bool CSqliteRecordset::GetValue(char* strFldName, char* strValue, short len, bool &nIsNull)
{
	ASSERT(m_stmt != NULL);
	int nIndex = GetIndex(strFldName);
	if (nIndex < 0)
		return false;

	char *szValue = (char*)sqlite3_column_text(m_stmt,nIndex);
	if (szValue == NULL)
		return false;

	 CCodingConv::UTF8_2_GB2312(strValue,len,szValue,(int)strlen(szValue));
	//strcpy_s(strValue,len,szValue);
	return true;
}

bool CSqliteRecordset::GetValue(int nColumns, int& nValue, bool &nIsNull )
{
	ASSERT(m_stmt != NULL);
	if(nColumns < 0)
		return false;

	nValue = sqlite3_column_int(m_stmt,nColumns);
	return true;
}
bool CSqliteRecordset::GetValue(char* strFieldName, int& nValue, bool &nIsNull )
{
	ASSERT(m_stmt != NULL);
	int nIndex = GetIndex(strFieldName);
	if (nIndex < 0)
		return false;

	nValue = sqlite3_column_int(m_stmt,nIndex);
	return true;  
}
bool CSqliteRecordset::GetValue(int nColumns, __int64& lValue, bool &nIsNull )
{
	ASSERT(m_stmt != NULL);
	if(nColumns < 0)
		return false;

	lValue = sqlite3_column_int64(m_stmt,nColumns);
   return true;
}
bool CSqliteRecordset::GetValue(char* strFieldName, __int64& lValue, bool &nIsNull )
{
	ASSERT(m_stmt != NULL);
	int nIndex = GetIndex(strFieldName);
	if (nIndex < 0)
		return false;

	lValue = sqlite3_column_int64(m_stmt,nIndex);
   return true;
}
bool CSqliteRecordset::GetValue(int nColumns, short& nValue, bool &nIsNull )
 {
	 ASSERT(m_stmt != NULL);
	 if(nColumns < 0)
		 return false;

	 nValue = (short)sqlite3_column_int(m_stmt,nColumns);
	 return true;
 }
bool CSqliteRecordset::GetValue(char* strFieldName, short& nValue, bool &nIsNull )
{
	ASSERT(m_stmt != NULL);
	int nIndex = GetIndex(strFieldName);
	if (nIndex < 0)
		return false;

	nValue = (short)sqlite3_column_int(m_stmt,nIndex);
	return true;  
}

bool CSqliteRecordset::GetValue(int nColumns, double& lValue, bool &nIsNull )
{
	ASSERT(m_stmt != NULL);
	if(nColumns < 0)
		return false;

	lValue = sqlite3_column_double(m_stmt,nColumns);
	return true;
}
bool CSqliteRecordset::GetValue(char* strFieldName, double& lValue, bool &nIsNull )
{
	ASSERT(m_stmt != NULL);
	int nIndex = GetIndex(strFieldName);
	if (nIndex < 0)
		return false;

	lValue = sqlite3_column_double(m_stmt,nIndex);
	return true;  
}
bool CSqliteRecordset::GetValue(int nColumns, tm& time, bool &nIsNull )
{
	if (nColumns <0)
		return false;

	short len(25);
	char *szDataTime = new char[len];
	GetValue(nColumns,szDataTime,len,nIsNull);
	if(szDataTime == NULL)
		return false;

	time = AnalyDateTime(szDataTime);
	return true;  
}
bool CSqliteRecordset::GetValue(char* szFieldName, tm& time, bool &nIsNull )
{
	if (szFieldName == NULL)
		return false;

	short len(25);
	char * szDateTime = new char[len];
	GetValue(szFieldName,szDateTime,len,nIsNull);
	if(szDateTime == NULL)
		return false;

	time = AnalyDateTime(szDateTime);
	return true;  
}

bool CSqliteRecordset::GetValue(int nColumns, byte** bDat, long *len, bool &nIsNull )
{
	ASSERT(m_stmt != NULL);
	
	const void* pcvData = sqlite3_column_blob(m_stmt,nColumns);  //const void*תbyte**
	*len = sqlite3_column_bytes(m_stmt,nColumns);

	*bDat = new byte[*len];
	memcpy(*bDat,pcvData,*len);
	return true;  
}
bool CSqliteRecordset::GetValue(char* strFieldName, byte** bDat, long *len, bool &nIsNull )
{
	ASSERT(m_stmt != NULL);

	int nIndex = GetIndex(strFieldName);
	if (nIndex < 0)
		return false;

	const void* pcvData = sqlite3_column_blob(m_stmt,nIndex);  //const void*תbyte**
	*len = sqlite3_column_bytes(m_stmt,nIndex);

	*bDat = new byte[*len];
	memcpy(*bDat,pcvData,*len);
	return true;  
}


void CSqliteRecordset::InitRowNum()
{
	ASSERT(m_stmt != NULL);

	int  rc;
	m_lRows = 0;
	sqlite3_reset(m_stmt);
	
	do{   
		rc = sqlite3_step(m_stmt);  
		if(rc == SQLITE_ROW /*|| rc== SQLITE_DONE*/)  
		{  
			m_lRows++;
		}  

		else 
			break;  

	}while(1);  

	sqlite3_reset(m_stmt);
}



//strDateTime:YYYY-MM-DD HH:MM:SS
//��strDateTime: YYYY-MM-DD HH:MM (��Ϊ0)
tm& CSqliteRecordset::AnalyDateTime(char* szDateTime)
{
	tm *dateTime = new tm; 
	string str="";
	string strDateTime = (string)szDateTime;
   
	int nPos = (int)strDateTime.find_first_of(' ');
	//1.���ݿո�ֽ�ʱ��Ϊ������
	string strValue1 = strDateTime.substr(0, nPos);
	string strValue2 = strDateTime.substr(nPos+1, (int)strlen(szDateTime) - nPos - 1);

	//2.��������
	int nFPos = (int)strValue1.find_first_of('-');
	int nLPos = (int)strValue1.find_last_of('-');
	dateTime->tm_year = atoi(strValue1.substr(0, nFPos).c_str());
	dateTime->tm_mon = atoi(strValue1.substr(nFPos + 1, nLPos - nFPos - 1).c_str());
	dateTime->tm_mday = atoi(strValue1.substr(nLPos + 1, (int)strlen(strValue1.c_str())-nLPos - 1).c_str());

	//3.����ʱ��
	nFPos = (int)strValue2.find_first_of(':');
	nLPos = (int)strValue2.find_last_of(':');
	dateTime->tm_hour = atoi(strValue2.substr(0, nFPos).c_str());
	dateTime->tm_min = atoi(strValue2.substr(nFPos + 1, nLPos - nFPos - 1).c_str());

	if(nFPos == nLPos)
		dateTime->tm_sec =0;
	else
	{
		string strValue3 = strValue2.substr(nLPos + 1, (int)strlen(strValue2.c_str())-nLPos - 1);
	    dateTime->tm_sec = atoi(strValue3.substr(0, nFPos).c_str());
	}
  
	return *dateTime;
}
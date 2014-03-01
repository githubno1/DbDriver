#ifndef SQL_DEF_H
#define SQL_DEF_H

//���ݿ�����
typedef enum 
{
	DBUnknown		= 0,
	DB_SQLITE		= 1,
	DB_POSTGRESQL	= 2,
	DB_ACCESS		= 3,
	DB_ORACLE		= 4,
	DB_MSSQL		= 5,
	DB_EXCEL        = 6,
}DB_TYPE;


//�ֶ�����
typedef enum
{
	FLD_UNKNOWN		=	0,	//δ֪
	FLD_BOOL			,	//������
	FLD_BLOB			,	//������
	FLD_CHAR			,	//�ַ���
	FLD_INT2			,	
	FLD_INT4			,
	FLD_INT8			,
	FLD_FLOAT			,	//float4
	FLD_DOUBLE			,	//float8
	FLD_VARCHAR			,	//varchar
	FLD_DATE			,
	FLD_TIME			,
	FLD_DATETIME		,
	FLD_NUMERIC			,
}FIELD_TYPE;



#endif
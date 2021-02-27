//#include "StdAfx.h"
#include "IngeniousException.h"

// begin to implement the IngeniousException class

IngeniousException::IngeniousException(String16 tips,UInt32 id/*,ERROR_TYPE = ERROR*/)
: m_tips(tips)
//, m_errorType(ERROR)
, m_errorID(id)
{
#ifdef _DEBUG
	m_traceLevel = GUI_DEBUG;
#endif
}

IngeniousException::~IngeniousException(void)
{

}

int  IngeniousException::GetErrorID()
{	
	return (int)m_errorID;
}

String16  IngeniousException::GetErrorMessage()
{
	return GetMessageFromID(m_errorID);
	/*return String16(L"");*/
}

char*	IngeniousException::GetErrorMsg()
{
	String16 str16= GetErrorMessage();
	char *strTchar = new char[256];
	setlocale(LC_CTYPE,"");
	wcstombs(strTchar, str16.c_str(), 256);
	return strTchar ;
}

#ifdef _DEBUG
void  IngeniousException::SetTraceLevel(TRACE_LEVEL level)
{
	m_traceLevel = level;
}

void  IngeniousException::TraceOutput()
{
}
#endif

// begin to implement the OsException class
ErrorInfo OsException::ErrorTable1[] = 
{
	{ERR_SYS ,		String16(L"ϵͳ --- ")},
	{ERR_CAP ,		String16(L"ͼ��ɼ��豸 --- ")},
	{ERR_IMAGE   ,		String16(L"ͼ�����豸 --- ")},
	{ERR_NETDEV ,		String16(L"�����豸 --- ")},
	{ERR_MOTION ,		String16(L"�˶������豸 --- ")},
	{ERR_VOICE   ,		String16(L"�����豸 --- ")},
	{ERR_SERIAL ,		String16(L"�����豸 --- ")},
	{ERR_MONITOR ,		String16(L"����豸 --- ")},
	{ERR_PSD   ,		String16(L"PSD�豸 --- ")},
	{ERR_ULTRASONIC   , 	String16(L"�����豸 --- ")},
	{ERR_ENCODER ,          String16(L"����---")},
	{ERR_MTFITTINGS ,   String16(L"����豸---")},
	{ERR_GYRO ,         String16(L"������---")},
	{ERR_ACCELEROMETER ,String16(L"���ٶȼ�---")},
	{ERR_COMPASS3200 ,  String16(L"ƽ������---")},
	{ERR_CAMERA,        String16(L"��̨�����---")},
	{ERR_DIDO,       String16(L"DIDO�豸---")},
	{ERR_CHECK,       String16(L"Ӳ���Լ�---")},
	{0,String16(L"")}
};

ErrorInfo OsException::ErrorTable2[] = 
{
	{ERR_FILENOTFOUND ,		String16(L"·�������ļ�δ�ҵ�!")},
	{ERR_DEV_CREATEFAIL ,		String16(L"�豸����ʧ��")},
	{ERR_USER_PTRNULL   ,		String16(L"�û�ָ��Ϊ��")},
	{ERR_DEV_INITFAIL ,		String16(L"��ʼ��ʧ��")},
	{ERR_DEV_STARTFAIL ,		String16(L"����ʧ��")},
	{ERR_BUFFPTRNULL   ,		String16(L"�豸������ָ��Ϊ��")},
	{ERR_DEV_ENDFAIL ,		String16(L"ֹͣ�豸����ʧ��")},
	{ERR_INTERFACENOTEXIST ,	String16(L"��ѯ�Ľӿڲ�����")},
	{ERR_CREATEOBJECTFAIL , 	String16(L"������������ʧ��")},
	{ERR_NEWFACTORYFAIL ,		String16(L"NEW����COM FACTORYʧ��")},
	{ERR_FACTORYIDNOTMATCH ,	String16(L"FACTORY ID��ƥ��")},
	{ERR_CREATEINSTANCE   , 	String16(L"����COMʵ��ʧ��")},
	{ERR_UNRECO ,			String16(L"δ֪����")},
	{ERR_SOCKINITFAIL ,		String16(L"SOCKET��ʼ��ʧ��")},
	{ERR_CONNECTFAIL   ,		String16(L"SOCKET����ʧ��")},
	{ERR_SOCKBINDFAIL ,		String16(L"SOCKET��ʧ��")},
	{ERR_SOCKLISTENFAIL ,		String16(L"SOCKET����ʧ��")},
	{ERR_ACCEPTFAIL   ,		String16(L"����SOCKET����ʧ��")},
	{ERR_SENDFAIL ,			String16(L"��������ʧ��")},
	{ERR_COLORN24 ,			String16(L"��ɫΪ��24ɫ")},
	{ERR_VIDEODEVICEUNVALID   , 	String16(L"��Ƶ�豸��Ч")},
	{ERR_COLORN256   ,		String16(L"��ɫΪ��256ɫ")},
	{ERR_LOADFILEFAIL   ,		String16(L"�����ļ�ʧ��")},
	{0,String16(L"")}
};

ErrorInfo OsException::ErrorTable3[] = 
{
	{ERR_DEV_STATE , String16(L"�豸״̬��ת����")},
	{0,String16(L"")}
};

OsException::OsException(String16 tips,UInt32 id/*,ERROR_TYPE errorType = ERROR*/)
: IngeniousException(tips,id/*,errorType*/)
{

}

OsException::~OsException()
{
}

 String16 OsException::GetMessageFromID( UInt32 id )
{

	long temp1;
	long temp2;
	long temp3;
	temp1 = id & 0x0ff0000;
	temp2 = id & 0x00ff00;
	temp3 = id & 0x0000ff;
	String16 str1,str2,str3;
	String16 strRes(L"");

	for ( int i = 0;ErrorTable1[i].id > 0; i++ )
	{
		if ( ErrorTable1[i].id == temp1 )
		{
			str1 = ErrorTable1[i].message;
		}
	}
	for ( int i = 0;ErrorTable2[i].id > 0; i++ )
	{
		if ( ErrorTable2[i].id == temp2 )
		{
			str2 = ErrorTable2[i].message;
		}
	}
/*	for ( int i = 0;ErrorTable3[i].id > 0; i++ )
	{
		if ( ErrorTable3[i].id == temp3 )
		{
			str3 = ErrorTable3[i].message;
		}
	}
*/
	strRes.append(str1);
	strRes.append(str2);
//	strRes.append(str3);
	return String16(strRes);
}


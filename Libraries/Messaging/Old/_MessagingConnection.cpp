#include "MessagingConnection.h"

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

namespace messaging{

	MessagingConnection::MessagingConnection(const char* platformGuid, const char* sensorGuid, IMessageRouter* router)
		:m_router(router)
	{
		m_sourceLogistics.has_platformGuid = (platformGuid != 0);
		m_sourceLogistics.has_sensorGuid = (sensorGuid != 0);
		strcpy(m_sourceLogistics.platformGuid, platformGuid);
		strcpy(m_sourceLogistics.sensorGuid, sensorGuid);
	}

	MessagingConnection::~MessagingConnection()
	{
	}

}
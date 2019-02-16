#ifndef GUID_H
#define GUID_H

namespace util{ namespace guid{

	const int GuidSize = 40;

	const int HashedSensorTableSize = 19;

	int Hash(const char* guid);

}}
#endif
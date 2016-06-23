#include "ResUpdateInfo.h"

using namespace std;

ResUpdateInfo::ResUpdateInfo(int state, const string &path, const string &uri, bool isFile)
{
	m_updateState = state;
	m_path = path;
	m_uri = uri;
	m_isFile = isFile;
}

ResUpdateInfo::~ResUpdateInfo(void)
{
}


int ResUpdateInfo::getState()
{
	return m_updateState;
}


const string &ResUpdateInfo::getPath()
{
	return m_path;
}


const string &ResUpdateInfo::getUri()
{
	return m_uri;
}

bool ResUpdateInfo::getIsFile()
{
	return m_isFile;
}
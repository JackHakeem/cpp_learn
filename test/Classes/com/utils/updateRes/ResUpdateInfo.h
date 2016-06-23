#ifndef MHXJ_MODEL_RES_UPDATE_INFO_H__
#define MHXJ_MODEL_RES_UPDATE_INFO_H__
#include <string>

class ResUpdateInfo
{
public:
	static const int kUpdateState = 0;
	static const int kNewState = 1;
	static const int kRemoteState = 2;

	ResUpdateInfo(int state, const std::string &path,
		const std::string &uri, bool isFile);
	~ResUpdateInfo(void);

	int getState();
	const std::string &getPath();
	const std::string &getUri();
	bool getIsFile();
private:
	int m_updateState;
	std::string m_path;
	std::string m_uri;
	bool m_isFile;
};

#endif
#ifndef __LOGGER_H__
#define __LOGGER_H__

#ifdef _WIN32
#pragma warning (disable:4786)
#pragma warning (disable:4503)
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <ostream>

#ifdef _WIN32
#define snprintf _snprintf
#define vsnprintf _vsnprintf
#else
#include <sys/time.h>
#endif

#include "my_stl.h"

using std::ofstream;
using std::ostream;
using std::ios;


CC_NS_BEGIN

    class CLogger : public ofstream
    {
        public:
            CLogger();
            ~CLogger();

        public:
            void SetLogPath(const string& strPath);
            CLogger& NewLine(int nFileType = 0);

        public:
            inline bool IsSetPath() const
            {
                return !m_strPath.empty();
            }

            friend ostream& EndLine(ostream& logger);

		private:
			int CreateDir(const char *strPath);

        private:
            string m_strPath;
            string m_strFile;

    };

    //自定义的操纵符io manip
    extern ostream& EndLine(ostream& logger);
    extern ostream& EndFile(ostream& logger);

    enum {MAX_LOG_BUFF_SIZE = 10240,};

    //extern void Log(const char* section, const char* key, const char* msg, va_list& ap);
    extern void LogDebug(const char* key, const char* msg, ...);
    extern void LogInfo(const char* key, const char* msg, ...);
    extern void LogWarning(const char* key, const char* msg, ...);
    extern void LogError(const char* key, const char* msg, ...);
    extern void LogCritical(const char* key, const char* msg, ...);
    extern void LogConsole(const char* key, const char* msg, ...);
    extern void LogScript(const char* level, const char* msg, ...);

    extern void Error(const char* level, const char* msg, ...);

    extern CLogger g_logger;


#ifndef _WIN32
    //g_logger对应的线程锁
    extern pthread_mutex_t* g_logger_mutex;
#endif

CC_NS_END

#endif

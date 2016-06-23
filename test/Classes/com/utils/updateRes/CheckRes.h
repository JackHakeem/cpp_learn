#ifndef MHSJ_CLASSES_CHECK_RES_H__
#define MHSJ_CLASSES_CHECK_RES_H__
#include <vector>
#include "ResUpdateInfo.h"
#include "Md5Info.h"

static std::vector<ResUpdateInfo *> s_infos;

void checkRes();
void cmpRes(Md5Info *local, Md5Info *remote);
void resAddNode(Md5Info *node);
void resDeleteNode(Md5Info *node);

void writeInfoToFile();
 
#endif
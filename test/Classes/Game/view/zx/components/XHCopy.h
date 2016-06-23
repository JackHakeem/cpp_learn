#pragma once

#include "LayerNode.h"

class XH;
class XHCopy:public LayerNode
{
public:

public:
	XHCopy();
	~XHCopy();

	bool init(XH* org);
public:
	XH* m_pOrg;
};
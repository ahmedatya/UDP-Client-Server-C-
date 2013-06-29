/*
 * SRAU.cpp
 *
 *  Created on: Jun 28, 2013
 *      Author: aatya
 */

#include "SRAU.h"

namespace SISA_NET {



STATE SRAU::SendTo(byte * buffer, uint32 length, char * ip_addr)
{
	SEG * segments = Segmentation(buffer,length);
	return SUCC;
}

STATE SRAU::RecvFrom(byte * buffer, uint32 length, char * ip_addr)
{
	return SUCC;
}

} /* namespace SISA_NET */

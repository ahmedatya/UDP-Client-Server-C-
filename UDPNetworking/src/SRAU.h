/*
 * SRAU.h
 *
 *  Created on: Jun 28, 2013
 *      Author: aatya
 */

#ifndef SRAU_H_
#define SRAU_H_

#include "ConnControl.h"

namespace SISA_NET {

class SRAU : public ConnControl{

private:

	virtual STATE FlowControl();
	virtual STATE FlowInfo();
	virtual STATE ReTrasmit(uint32 seq_num);

public:
	SRAU() {};

	virtual STATE SendTo(byte * buffer, uint32 length, char * ip_addr);
	virtual STATE RecvFrom(byte * buffer, uint32 length, char * ip_addr = "");


	virtual ~SRAU() {};
};

} /* namespace SISA_NET */
#endif /* SRAU_H_ */

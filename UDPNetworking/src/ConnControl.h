/*
 * ConnControl.h
 *
 *  Created on: Jun 28, 2013
 *      Author: aatya
 */

#ifndef CONNCONTROL_H_
#define CONNCONTROL_H_

#include "UDPHandler.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

namespace SISA_NET {

/*
 * Flow Control and Reliability Definitions
 */
#define MAX_NUM_RETX 5 // maximum number of retransmission

/*
 * Packets type + To figure the type of packets and the payload it carries
 */
enum MAGIC_TYPE
{
	REQ = 0x80,
	REP = 0x81,
	DATA = 0x82,
	REQ_CNT = 0x90,
	REP_CNT = 0x91,
	CNT = 0x92
};

struct ConnHeader
{
	uint32 sequence_num; // Sequence number 4 bytes
	uint8 magic; // Packet type
	uint8 version; // Flow Control Algo. version
	uint16 control; // Two bytes control
	uint32 ack_num; // Acknowledgment number 4 bytes
};

/*
 * Segments Construction
 */
struct SEG
{
	ConnHeader header; // This contains our header
	byte * paylod; //[MAX_SEG_SIZE];
};

/*
 * This Class contains the interfaces for all the flow control schemes
 * A control instance per flow
 */
class ConnControl {
private:

	uint16 flow_id;
	uint32 seq_num;
	uint8 version;
	// Convert a stream of data to segments
	SEG * Segmentation(byte * buffer, uint32 length);
	byte * DeSegmentation(SEG * seg_ptr, uint32 num);
	virtual STATE FlowControl() = 0;
	virtual STATE FlowInfo() = 0;
	virtual STATE ReTrasmit(uint32 seq_num) = 0;
public:
	virtual STATE SendTo(byte * buffer, uint32 length, char * ip_addr) = 0;
	virtual STATE RecvFrom(byte * buffer, uint32 length, char * ip_addr = "") = 0;

	ConnControl();
	ConnControl(uint16 id, uint16 ver);

	void SetFlowID(uint16 id){flow_id = id;}
	uint16 GetFlowID(){return flow_id;}

	void SetVersion(uint16 ver){version = ver;}
	uint16 GetVersion(){return version;}

	virtual ~ConnControl(){}
};

} /* namespace SISA_NET */
#endif /* CONNCONTROL_H_ */

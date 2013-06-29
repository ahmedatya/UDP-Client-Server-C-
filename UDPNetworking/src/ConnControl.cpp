/*
 * ConnControl.cpp
 *
 *  Created on: Jun 28, 2013
 *      Author: aatya
 */

#include "ConnControl.h"

namespace SISA_NET{

ConnControl::ConnControl()
{
		srand(time(NULL));
		seq_num = rand();
}
ConnControl::ConnControl(uint16 id, uint16 ver)
{
	srand(time(NULL));
	seq_num = rand();
	flow_id = id;version = ver;
}

/*
 * Assume for now all the packet sizes are multiple of the max_seg_size
 */
SEG * ConnControl::Segmentation(byte * buffer, uint32 length)
{
	uint32 seg_num = ceil((double)length/(double)MAX_SEG_SIZE);
	SEG * segments = new SEG[seg_num];

	uint32 index = 0;

	for(int i = 0 ; i < seq_num; i++)
	{
		segments[i].header.sequence_num = seq_num++;
		segments[i].header.version = version;
		segments[i].header.ack_num = 0;
		segments[i].header.control = DATA;
		segments[i].header.control = 0;
		memcpy(segments[i].paylod, &buffer[index], MAX_SEG_SIZE);
		index+=MAX_SEG_SIZE;
	}
	return segments;
}

/*
 * Assume all the segments are full of the payload and no padding
 */
byte * ConnControl::DeSegmentation(SEG * seg_ptr, uint32 num)
{
	byte * buffer = new byte[num* MAX_SEG_SIZE];
	uint32 index = 0;
	for(int i = 0 ; i < seq_num; i++)
		{
			memcpy(&buffer[index], seg_ptr[i].paylod, MAX_SEG_SIZE);
			index+=MAX_SEG_SIZE;
		}

	return buffer;
}

}

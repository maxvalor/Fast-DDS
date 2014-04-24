/*************************************************************************
 * Copyright (c) 2013 eProsima. All rights reserved.
 *
 * This copy of FastCdr is licensed to you under the terms described in the
 * EPROSIMARTPS_LIBRARY_LICENSE file included in this distribution.
 *
 *************************************************************************/

/*
 * RTPSReader.cpp
 *
 *  Created on: Feb 25, 2014
 *      Author: Gonzalo Rodriguez Canosa
 *      email:  gonzalorodriguez@eprosima.com
 */

#include "eprosimartps/reader/RTPSReader.h"
#include "eprosimartps/HistoryCache.h"

#include "eprosimartps/dds/Subscriber.h"

namespace eprosima {
namespace rtps {

RTPSReader::RTPSReader(uint16_t historysize,uint32_t payload_size):
		m_stateType(STATELESS),
		m_reader_cache(historysize,payload_size,READER,(Endpoint*)this),
		expectsInlineQos(true),
		mp_Sub(NULL),
		newMessageSemaphore(new boost::interprocess::interprocess_semaphore(0)),
		mp_listener(NULL)

{
	pDebugInfo("RTPSReader created correctly"<<endl);
}

RTPSReader::~RTPSReader() {

	pDebugInfo("RTPSReader destructor"<<endl;);
	delete(newMessageSemaphore);
}

bool RTPSReader::readNextCacheChange(void* data)
{
	if(!m_reader_cache.m_changes.empty())
	{

	}
	return false;
}


bool RTPSReader::readAllCacheChange(std::vector<void*>* data_vec)
{
return false;
}


} /* namespace rtps */
} /* namespace eprosima */



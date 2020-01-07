// Copyright 2019 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * @file SubscriberImpl.hpp
 *
 */

#ifndef _FASTDDS_SUBSCRIBERIMPL_HPP_
#define _FASTDDS_SUBSCRIBERIMPL_HPP_
#ifndef DOXYGEN_SHOULD_SKIP_THIS_PUBLIC

#include <fastrtps/attributes/SubscriberAttributes.h>

#include <fastrtps/rtps/reader/ReaderListener.h>
#include <fastdds/dds/subscriber/qos/SubscriberQos.hpp>
#include <fastdds/dds/topic/qos/DataReaderQos.hpp>
#include <fastrtps/types/TypesBase.h>

#include <dds/core/status/State.hpp>
#include <fastdds/dds/domain/DomainParticipant.hpp>

#include <mutex>
#include <map>

using eprosima::fastrtps::types::ReturnCode_t;

namespace eprosima {
namespace fastrtps {
namespace rtps {

class RTPSParticipant;

} //namespace rtps

class TopicAttributes;

} // namespace fastrtps

namespace fastdds {
namespace dds {

class SubscriberListener;
class Subscriber;
class DataReaderImpl;
class Topic;
class TopicQos;

/**
 * Class SubscriberImpl, contains the actual implementation of the behaviour of the Subscriber.
 *  @ingroup FASTRTPS_MODULE
 */
class SubscriberImpl
{
    friend class DomainParticipantImpl;
    friend class DataReaderImpl;

    /**
     * Create a subscriber, assigning its pointer to the associated writer.
     * Don't use directly, create Subscriber using create_subscriber from Participant.
     */
    SubscriberImpl(
            DomainParticipantImpl* p,
            const SubscriberQos& qos,
            SubscriberListener* listen = nullptr);

public:

    virtual ~SubscriberImpl();

    const SubscriberQos& get_qos() const;

    ReturnCode_t set_qos(
            const SubscriberQos& qos);

    SubscriberListener* get_listener() const;

    ReturnCode_t set_listener(
            SubscriberListener* listener);

    DataReader* create_datareader(
            Topic* topic,
            const DataReaderQos& reader_qos = DDS_DATAREADER_QOS_DEFAULT,
            DataReaderListener* listener = nullptr,
            const ::dds::core::status::StatusMask& mask = ::dds::core::status::StatusMask::all());

    ReturnCode_t delete_datareader(
            DataReader* reader);

    DataReader* lookup_datareader(
            const std::string& topic_name) const;

    bool contains_entity(
            const fastrtps::rtps::InstanceHandle_t& handle) const;
    /* TODO
       bool begin_access();
     */

    /* TODO
       bool end_access();
     */

    /* TODO When StateKinds are implemented.
       bool get_datareaders(
        std::vector<DataReader*>& readers,
        std::vector<SampleStateKind> sample_states,
        std::vector<ViewStateKind> view_states,
        std::vector<InstanceStateKind> instance_states) const;
     */
    ReturnCode_t get_datareaders(
            std::vector<DataReader*>& readers) const;

    bool has_datareaders() const;

    ReturnCode_t notify_datareaders() const;

    ReturnCode_t delete_contained_entities();

    ReturnCode_t set_default_datareader_qos(
            const DataReaderQos& qos);

    const DataReaderQos& get_default_datareader_qos() const;

    ReturnCode_t copy_from_topic_qos(
            DataReaderQos& reader_qos,
            const TopicQos& topic_qos) const;

    /**
     * Update the Attributes of the subscriber;
     * @param att Reference to a SubscriberAttributes object to update the parameters;
     * @return True if correctly updated, false if ANY of the updated parameters cannot be updated
     */
    bool set_attributes(
            const fastrtps::SubscriberAttributes& att);

    /**
     * Get the Attributes of the Subscriber.
     * @return Attributes of the Subscriber.
     */
    const fastrtps::SubscriberAttributes& get_attributes() const
    {
        return qos_.sub_attr;
    }

    DomainParticipant& get_participant() const;

    const fastrtps::rtps::RTPSParticipant* rtps_participant() const
    {
        return rtps_participant_;
    }

    fastrtps::rtps::RTPSParticipant* rtps_participant()
    {
        return rtps_participant_;
    }

    Subscriber* get_subscriber() const
    {
        return user_subscriber_;
    }

    //! Remove all listeners in the hierarchy to allow a quiet destruction
    void disable();

    //! Check if any reader uses the given type name
    bool type_in_use(
            const std::string& type_name) const;

    /**
     * @brief A method called when a new cache change is added
     * @param change The cache change that has been added
     * @return True if the change was added (due to some QoS it could have been 'rejected')
     */
    bool on_new_cache_change_added(
            const fastrtps::rtps::CacheChange_t* const change);

    ReturnCode_t autoenable_entities();

private:

    //!Participant
    DomainParticipantImpl* participant_;

    SubscriberQos qos_;

    //!Map of Pointer to associated DataReaders. Topic name is the key.
    std::map<std::string, std::vector<DataReaderImpl*> > readers_;

    mutable std::mutex mtx_readers_;

    SubscriberListener* listener_;

    Subscriber* user_subscriber_;

    //!RTPSParticipant
    fastrtps::rtps::RTPSParticipant* rtps_participant_;

    DataReaderQos default_datareader_qos_;

    fastrtps::rtps::InstanceHandle_t handle_;

};

} /* namespace dds */
} /* namespace fastdds */
} /* namespace eprosima */
#endif
#endif /* _FASTDDS_SUBSCRIBERIMPL_HPP_ */

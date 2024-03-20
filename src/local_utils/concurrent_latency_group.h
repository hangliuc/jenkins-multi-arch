#pragma once


#include <iostream>
#include <glog/logging.h>
#include <brpc/server.h>
#include <butil/time.h>
#include <bvar/bvar.h>
#include <vector>

#include "local_double_buffer_holder.h"

namespace shareAds {

class ConcurrentLatencyGroup {
public:
    using STLatencyMap = std::unordered_map<std::string/*latency_name*/, bvar::LatencyRecorder*>;
public:
    ConcurrentLatencyGroup(const std::string& globle_unique_group_name, size_t max_size=100);
    virtual ~ConcurrentLatencyGroup();

    bvar::LatencyRecorder& Get(const std::string& latency_name);

private:
    bvar::LatencyRecorder* _TryCreate(const std::string& latency_name);

private:
    std::mutex _mutex;
    size_t _max_size;
    std::string _group_name;

    LocalDoubleBufferHolderV1<STLatencyMap> _in_use;
    STLatencyMap _all_latencies;

    static bvar::LatencyRecorder _nil_recorder;
};

} /* namespace shareAds */

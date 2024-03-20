#include "concurrent_latency_group.h"

namespace shareAds {

bvar::LatencyRecorder ConcurrentLatencyGroup::_nil_recorder;

ConcurrentLatencyGroup::ConcurrentLatencyGroup(const std::string& globle_unique_group_name, size_t max_size)
:_max_size(max_size), _group_name(globle_unique_group_name) {

}

ConcurrentLatencyGroup::~ConcurrentLatencyGroup() {
    // TODO Auto-generated destructor stub
}

bvar::LatencyRecorder& ConcurrentLatencyGroup::Get(const std::string& latency_name) {
    std::shared_ptr<STLatencyMap> in_use = _in_use.GetPtr();

    auto iter = in_use->find(latency_name);
    if (iter != in_use->end()) {
        return *(iter->second);
    }

    if(in_use->size() >= _max_size) {
        return _nil_recorder;
    }

    bvar::LatencyRecorder* target_recorder = _TryCreate(latency_name);
    if(target_recorder) {
        return *target_recorder;
    }

    return _nil_recorder;
}

bvar::LatencyRecorder* ConcurrentLatencyGroup::_TryCreate(const std::string& latency_name) {
    if(!_mutex.try_lock()) {
        return nullptr;
    }

    auto iter = _all_latencies.find(latency_name);
    if(iter != _all_latencies.end()) {
        _mutex.unlock();
        return  iter->second;
    }

    if(_all_latencies.size() >= _max_size) {
        _mutex.unlock();
        return nullptr;
    }

    bvar::LatencyRecorder* new_latency = new bvar::LatencyRecorder(_group_name, latency_name);
    _all_latencies[latency_name] = new_latency;

    // 更新双 buffer
    std::shared_ptr<STLatencyMap> new_latency_map = std::make_shared<STLatencyMap>();
    for(auto& [latency_name, latency] : _all_latencies) {
        (*new_latency_map)[latency_name] = latency;
    }
    _in_use.SwapPtr(new_latency_map);

    _mutex.unlock();

    return new_latency;
}

} /* namespace shareAds */

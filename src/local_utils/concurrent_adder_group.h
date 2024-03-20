#pragma once

#include <mutex>
#include <glog/logging.h>
#include <brpc/server.h>
#include <butil/time.h>
#include <bvar/bvar.h>

#include "local_double_buffer_holder.h"


namespace shareAds {

struct STConcurrentAdderInfo {
    using Ptr = std::shared_ptr<STConcurrentAdderInfo>;

    STConcurrentAdderInfo(const std::string& group_name, const std::string& adder_name_);

    std::string adder_name;
    bvar::Adder<int>* adder;
    bvar::Window<bvar::Adder<int>>* window;
};
using STConcurrentAdderMap = std::unordered_map<std::string/*adder_name*/, STConcurrentAdderInfo::Ptr>;

class ConcurrentAdderGroup {
public:
    ConcurrentAdderGroup(const std::string& globle_unique_group_name, size_t max_size=500);
    virtual ~ConcurrentAdderGroup() {}

    void Inc(const std::string& adder_name, int cnt=1);
    void Add(const std::string& adder_name, int cnt=1);

private:
    void _TryCreate(const std::string& adder_name);

private:
    std::mutex _mutex;
    size_t _max_size;
    std::string _group_name;

    LocalDoubleBufferHolderV1<STConcurrentAdderMap> _in_use;
    STConcurrentAdderMap _all_adders;
};

} /* namespace shareAds */

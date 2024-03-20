#pragma once

#include <string>
#include <atomic>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <glog/logging.h>

#include "runtime_info/runtime_info.h"

namespace shareAds {

class DagTracer {
public:
    DagTracer(int max_path_size = 40);
    virtual ~DagTracer();

    void SetDebugMode(bool need_debug=true);

    // 线程安全
    void Trace(const std::string& op_name);

    // 这3个非线程安全，调用条件：要在dag执行结束后才能调用
    void GetExePath(std::string& exe_path);
    uint GetExeOpCount();
    std::string GetLastOpName();

private:
    bool _EnableTrace();

private:
    bool _debug_mode;

    std::atomic_uint _idx;
    std::vector<std::string> _exe_path;

    std::unordered_map<std::string/*opname*/, std::atomic_int/*cnt*/> _op_exe_times_map;
};

} /* namespace shareAds */

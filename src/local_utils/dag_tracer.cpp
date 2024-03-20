 /*
 * DagExePlanTracer.cpp
 *
 *  Created on: May 27, 2022
 *      Author: shareit
 */

#include "dag_tracer.h"
#include "monitor/adder_group.h"

namespace shareAds {


static std::unordered_set<std::string> op_names = {"TrafficInterceptOp", "ParseReqeustOp", "GetAbtestOp",
        "CrtSizeFilter2Op", "CapLimitCheckOp", "InvokeMAOp", "EcpmLimitByTypeOp", "EcpmLimitFinalOp",
        "TrafficLimitOp", "Rerank2Op", "TrafficFilterOp", "KfkResponseLogOp", "WhitelistRecallOp",
        "FillWhitelistEcpmOp", "InvokeRTA3Op", "BuildResponseWhitelistOp", "MacroParamReplace2Op", "InvokeRecallV4Op",
        "AdPositionFilterByMaxPriceOp", "AdPositionFilter2Op", "FilterByTimeOp", "EcpmLimitSetOp",
        "GetUserClusterIdsOp", "InvokeRecallV5Op", "ReplaceRuLinksOp", "ReplaceNotRuLinksOp",
        "InvokeAdxOp", "InvokeFrequencyControl2Op", "FrequencyControlInCampOp",
        "InvokeFrequencyControlAgain2Op", "GetUserClusterIdsV2Op", "ProcessCvrFeatureOp", "BlacklistFilterOp",
        "GaidFcOp", "RecordResponseGaidOp", "Rerank4Op", "InvokeMA4Op", "BuildResponse7Op", "ReplaceRuLinksV2Op", "ReplaceNotRuLinksV2Op",
        "InvokeRTA4Op", 

        "InternalParseReqeustV1Op", "InternalInvokeRecallOp", "InternalInvokeRTAOp", "InternalRerankOp", "InternalGetAbtestOp",
        "InternalSplitMARequestOp", "InternalInvokeNonIncentiveMAOp", "InternalInvokeIncentiveMAOp", "InternalMergeMAResponseOp",
        "FillAdCreativeInfo2Op", "InternalBuildNoneIncentiveResponseOp", "InternalBuildIncentiveResponseOp", "InternalRerank2Op",
        "InternalGetUserClusterIdsOp", "InternalInvokeRecall3Op", "InternalEcpmLimitSetOp", "InternalRerank3Op", "InternalGetUserClusterIdsV2Op", "InternalProcessCvrFeatureOp",
        "InternalKfkResponseLogOp", "InternalInvokeRTA2Op",
};
static AdderGroup dag_error_adder("access_dag_error", op_names);

DagTracer::DagTracer(int max_path_size)
:_debug_mode(false), _idx(0) {

    if(!_EnableTrace()) {
        return;
    }

    _exe_path.resize(max_path_size);

    for(const auto& op : op_names) {
        _op_exe_times_map.emplace(op, 0);
    }
}

DagTracer::~DagTracer() {

}

void DagTracer::SetDebugMode(bool need_debug) {
    _debug_mode = need_debug;
}

void DagTracer::Trace(const std::string& op_name) {

    if(!_EnableTrace()) {
        return;
    }

    uint pre_idx = _idx.fetch_add(1);
    if(pre_idx < _exe_path.size()) {
        _exe_path[pre_idx] = op_name;
    }

    std::unordered_map<std::string/*opname*/, std::atomic_int/*idx*/>::iterator iter = _op_exe_times_map.find(op_name);
    if(iter ==_op_exe_times_map.end()) {
        LOG(ERROR) << "dag_tracer_skip: not found " << op_name;
        return;
    }

    iter->second += 1;
    if(iter->second != 1) {
        dag_error_adder.Inc(op_name);

        std::string exe_path;
        GetExePath(exe_path);
        LOG(ERROR) << "dag_tracer_error: exe [" << op_name << "] " << iter->second << " times, "
                << "exe_path: " << exe_path;
        return;
    }
}

void DagTracer::GetExePath(std::string& exe_path) {

    if(!_EnableTrace()) {
        return;
    }

    uint exe_path_size = _idx.load();
    for(uint i=0; i< exe_path_size && i< _exe_path.size(); ++i) {
        exe_path += _exe_path[i] + " ";
    }
}

uint DagTracer::GetExeOpCount() {
    return _idx.load();
}


std::string DagTracer::GetLastOpName() {
    if(!_EnableTrace()) {
        return "tracer_not_enable";
    }

    uint exe_path_size = _idx.load();
    if(exe_path_size == 0) {
        return "tracer_path_empty";
    }

    uint last_idx = exe_path_size - 1;
    if(last_idx >= _exe_path.size()) {
        return "tracer_path_overflow";
    }

    return _exe_path[last_idx];
}

inline bool DagTracer::_EnableTrace() {
#if 1
    return shareAds::RuntimeInfo::GetInstance().is_canary
            || !shareAds::RuntimeInfo::GetInstance().is_prod
            || _debug_mode;
#else
    return true;    // TODO: 20230808 临时都放开
#endif
}

} /* namespace shareAds */

#pragma once

#include <brpc/http_status_code.h>
#include <brpc/policy/hasher.h>
#include <brpc/rpc_dump.h>
#include <brpc/server.h>
#include <bvar/bvar.h>
#include <sstream>
#include <stdlib.h>


#include "src/local_utils/concurrent_latency_group.h"
#include "src/local_utils/concurrent_adder_group.h"
#include "monitor/latency_group.h"
#include "timer/timer_latency_util.h"
#include "lbs/lbs_service.pb.h"

#if defined ARM_CPU_ARC
    #include "release/linux-arm/include/shareit-lbs-cpp.h"
#else
    #include "release/linux-amd64/include/shareit-lbs-cpp.h"
#endif

namespace shareAds {
class LbsImpl : public ::ecom::lbs::ecom_lbs {
public:
    LbsImpl() {
    }
    virtual ~LbsImpl() {
    }

    virtual void get_loc(::google::protobuf::RpcController* controller,
                const ::ecom::lbs::RequestBody* request,
                ::ecom::lbs::ResponseBody* response,
                ::google::protobuf::Closure* done);

private:
    bool _GetLocationWithSCK(double lat, double lon, std::string ip, ::ecom::lbs::ResponseBody* response);

};

}  // namespace shareAds

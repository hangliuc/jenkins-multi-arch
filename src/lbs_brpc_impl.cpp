#include "lbs_brpc_impl.h"
namespace shareAds {

static bvar::LatencyRecorder latency("lbs", "cost");


void LbsImpl::get_location(::google::protobuf::RpcController* controller,
        const ::ecom::lbs::RequestBody* request,
        ::ecom::lbs::ResponseBody* response,
        ::google::protobuf::Closure* done) {

    TimerLatencyUtil timerUtil(latency);
    brpc::ClosureGuard done_guard(done);

    brpc::Controller* cntl = static_cast<brpc::Controller*>(controller);
    assert(nullptr != cntl);

    return;
};


bool LbsImpl::_GetLocationWithSCK(double lat, double lon, std::string& ip, ::ecom::lbs::ResponseBody* response) {
    Location* origin_loc = ::get_location(lat, lon, ip.c_str());
    if(!origin_loc) {
        return false;
    }

    if(origin_loc->country.code) {
        response->mutable_country()->set_code(origin_loc->country.code);
    }

    if(origin_loc->country.name) {
        response->mutable_country()->set_name(origin_loc->country.name);
    }

    if(origin_loc->province.code) {
        response->mutable_province()->set_code(origin_loc->province.code);
    }

    if(origin_loc->province.name) {
        response->mutable_province()->set_name(origin_loc->province.name);
    }

    if(!origin_loc->district) {
        response->set_district(origin_loc->district);
    }

    if(!origin_loc->city) {
        response->set_city(origin_loc->city);
    }

    return true;

}

}  // namespace shareAds

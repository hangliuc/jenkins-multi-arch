#include "lbs_brpc_impl.h"
namespace shareAds {

static bvar::LatencyRecorder latency("lbs", "cost");


void LbsImpl::get_loc(::google::protobuf::RpcController* controller,
        const ::ecom::lbs::RequestBody* request,
        ::ecom::lbs::ResponseBody* response,
        ::google::protobuf::Closure* done) {

    TimerLatencyUtil timerUtil(latency);
    brpc::ClosureGuard done_guard(done);

    brpc::Controller* cntl = static_cast<brpc::Controller*>(controller);
    assert(nullptr != cntl);

    _GetLocationWithSCK(request->lat(), request->lng(), request->ip(), response);

    return;
};


bool LbsImpl::_GetLocationWithSCK(double lat, double lon, std::string ip, ::ecom::lbs::ResponseBody* response) {
    ::csp::lbs::LocationInfo origin_loc = ::csp::lbs::get_location(lat, lon, ip.c_str());
    if(origin_loc.res == 0) {
        // 说明没有命中
        LOG(ERROR) << " not hit location lat:" << lat << ", lon:" << lon << ", ip:" << ip << ", msg:" << origin_loc.msg.c_str();
        return false;
    }

    response->mutable_country()->set_code(origin_loc.country.code.c_str());
    response->mutable_country()->set_name(origin_loc.country.name.c_str());
    response->mutable_province()->set_code(origin_loc.province.code.c_str());
    response->mutable_province()->set_name(origin_loc.province.name.c_str());
    response->set_district(origin_loc.district.c_str());
    response->set_city(origin_loc.city.c_str());

    return true;
}

}  // namespace shareAds

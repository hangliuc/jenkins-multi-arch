#include <brpc/server.h>
#include <gflags/gflags.h>
#include <glog/logging.h>
#include <stdlib.h>
#include <iostream>


#include "runtime_info/runtime_info.h"
#include "src/local_utils/local_util.h"
#include "lbs_brpc_impl.h"


DEFINE_int32(port, 50051, "TCP Port of this server");
DEFINE_int32(idle_timeout_s, -1, "Connection will be closed if there is no " "read/write operations during the last `idle_timeout_s'");



void InitGlog(char* argv[]) {
    // FLAGS_minloglevel = google::INFO; // 输出日志级别 google::INFO google::WARNING google::ERROR
    FLAGS_log_dir = "/data/logs/";  // 设置日志路径
    FLAGS_alsologtostderr = true;   // 日志记录到文件的同时输出到stderr
    FLAGS_max_log_size = 512;       // 最大日志大小（MB）, 如果设置为0将默认为1
    FLAGS_stop_logging_if_full_disk = true;  // 磁盘满停止记录日志

    // 初始化glog
    google::InitGoogleLogging(argv[0]);

    LOG(INFO) << "logging info......";
    LOG(WARNING) << "logging warning......";
    LOG(ERROR) << "logging error......";
}

int InitRuntimeInfo() {
    auto& rt = shareAds::RuntimeInfo::GetInstance();
    if (0 != rt.init()) {
        LOG(ERROR) << "init run time info error";
        return -1;
    }

    if (rt.str_env.empty()) {
        rt.str_env = "test";
        rt.is_prod = false;
    }

    LOG(ERROR) << "debug:runtimeinfo|isprod:" << rt.is_prod << "|istest:" << rt.is_test
               << "|iscanary:" << rt.is_canary << "|env:" << rt.str_env
               << "|servername:" << rt._server_name << "|is_gcs:" << rt._is_gcs
               << "|is_us_east:" << rt.is_us_east << "|is_europe:" << rt.is_europe
               << "|which_zone:" << rt._which_zone;

    return 0;
}


void InitLbsSDK() {
    if(shareAds::RuntimeInfo::GetInstance().is_us_east) {
        csp::lbs::init_config("s3://shareit-deploy-ue1/CBS/lbs/GeoIP2-City.mmdb.gz");
    } else if (shareAds::RuntimeInfo::GetInstance().is_europe) {
        csp::lbs::init_config("s3://shareit-deploy-ec1/CBS/lbs/GeoIP2-City.mmdb.gz");
    } else {
        throw std::runtime_error("lbs sdk has no data file configed");
    }
}


int main(int argc, char* argv[]) {
    google::ParseCommandLineFlags(&argc, &argv, true);
    InitGlog(argv);

    if (0 != InitRuntimeInfo()) {
        LOG(ERROR) << "init run time info error, exit";
        return -1;
    }

    InitLbsSDK();

    // Add services into server. Notice the second parameter, because the
    // service is put on stack, we don't want server to delete it, otherwise
    // use brpc::SERVER_OWNS_SERVICE.
    brpc::Server server;
    shareAds::LbsImpl lbs_svc;
    if (server.AddService(&lbs_svc, brpc::SERVER_DOESNT_OWN_SERVICE) != 0) {
        LOG(ERROR) << "Fail to add lbs_svc";
        return -1;
    }

    // Start the server.
    brpc::ServerOptions options;
    options.idle_timeout_sec = FLAGS_idle_timeout_s;
    if (server.Start(FLAGS_port, &options) != 0) {
        LOG(ERROR) << "Fail to start HttpServer";
        return -1;
    }

    // Wait until Ctrl-C is pressed, then Stop() and Join() the server.
    server.RunUntilAskedToQuit();

    return 0;
}

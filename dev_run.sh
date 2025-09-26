#!/bin/bash

export EcomServerName="lbs"
export Env="prod"
export DspRegion="singapore"
export PlatForm="aws"

server_path=bazel-bin/src/
env_flag_file=conf/prod.conf
echo "server_path: ${server_path}"
echo "env_flag_file: ${env_flag_file}"
echo "env_flag_file: ${env_flag_file}"
#killall access_brpc 
#for model_adapter_pid in "`ps -ef | grep access_brpc | awk '{print $2}'| sed -n '1'p`"
#do
#kill -9 $model_adapter_pid;
#done

${server_path}/lbs_brpc --flagfile=${env_flag_file}

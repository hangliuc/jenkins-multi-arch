#!/bin/bash

# check
if [[ -z "${Env}"  ]]; then
    echo "Please input environment argument Env=[prod|dev|test]"
    exit 1
fi

server_path=/data/code/

loglevel=0
# 本地环境
if [ "${Env}" == "local" ];then
    server_path=bazel-bin/src/
    loglevel=0
    env_flag_file=conf/test.conf
fi
# 测试环境
if [ "${Env}" == "test" ];then
    server_path=/data/code/
    env_flag_file=${server_path}conf/${Env}.conf
fi
# 正式环境
if [ "${Env}" == "prod" ];then
    server_path=/data/code/
    env_flag_file=${server_path}conf/${Env}.conf
fi

echo "Env: ${Env}"
echo "server_path: ${server_path}"

# env_flag_file
echo "env_flag_file: ${env_flag_file}"
${server_path}/access_brpc --flagfile=${env_flag_file}

FROM 526418118390.dkr.ecr.ap-southeast-1.amazonaws.com/shareit-csp/jenkins:compile_x86 as build
RUN chmod +x shell/build.sh 
RUN sh shell/build.sh


FROM 848318613114.dkr.ecr.ap-southeast-1.amazonaws.com/shareit-common/gcc-base:gcc7.4-s3cmd-bazelv18
# 配置文件路径
RUN mkdir -p /data/code/conf/

COPY --from=build lbs_brpc  /data/code/
COPY --from=build run.sh   /data/code/
COPY --from=build conf/prod.conf  /data/code/conf/
COPY --from=build conf/test.conf  /data/code/conf/

CMD ["/bin/bash", "-c", "bash /data/code/run.sh   ${Env} "]

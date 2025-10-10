FROM 526418118390.dkr.ecr.ap-southeast-1.amazonaws.com/shareit-common/gcc-base:gcc7.4-s3cmd-bazelv18-arm
# 配置文件路径
RUN mkdir -p /data/code/conf/

COPY lbs_brpc  /data/code/
COPY run.sh   /data/code/
COPY conf/prod.conf  /data/code/conf/
COPY conf/test.conf  /data/code/conf/

CMD ["/bin/bash", "-c", "bash /data/code/run.sh   ${Env} "]

FROM 848318613114.dkr.ecr.ap-southeast-1.amazonaws.com/shareit-common/gcc-base:gcc7.4-s3cmd-bazelv16
# 配置文件路径
RUN mkdir -p /data/code/conf/

COPY access_brpc  /data/code/
COPY run.sh   /data/code/
COPY conf/prod.conf  /data/code/conf/
COPY conf/test.conf  /data/code/conf/
COPY access_dag_with_recall.pos /data/code/
COPY access_internal_dag.pos /data/code/

COPY access_forward_to_adx_dag.pos /data/code/

CMD ["/bin/bash", "-c", "bash /data/code/run.sh   ${Env} "]

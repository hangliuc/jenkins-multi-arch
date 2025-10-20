FROM 526418118390.dkr.ecr.ap-southeast-1.amazonaws.com/shareit-csp/jenkins:compile_x86 
COPY . .

ARG SSH_PRIVATE_KEY
RUN mkdir -p /root/.ssh && \
    echo "$SSH_PRIVATE_KEY" > /root/.ssh/id_rsa && \
    chmod 600 /root/.ssh/id_rsa

ENV GIT_SSH_COMMAND="ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no"

RUN chmod +x shell/build.sh && sh shell/build.sh


RUN mkdir -p /data/code/conf/

COPY  bazel-bin/src/lbs_brpc  /data/code/  
COPY  run.sh   /data/code/
COPY  conf/prod.conf  /data/code/conf/
COPY  conf/test.conf  /data/code/conf/

CMD ["/bin/bash", "-c", "bash /data/code/run.sh   ${Env} "]

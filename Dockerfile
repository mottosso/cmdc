# Build locally for Linux on any platform, e.g. Windows
FROM mottosso/mayabase-centos7

RUN yum install centos-release-scl -y && \
    yum install devtoolset-7 bc -y

ENV DEVKIT_LOCATION=/devkit
WORKDIR /workspace

COPY docker_entrypoint.sh /usr/bin/entrypoint.sh
RUN chmod +x /usr/bin/entrypoint.sh
ENTRYPOINT [ "/usr/bin/entrypoint.sh" ]
# Build locally for Linux on any platform, e.g. Windows
FROM mottosso/mayabase-centos7

RUN yum install centos-release-scl -y && \
    yum install devtoolset-7 bc -y

RUN echo source scl_source enable devtoolset-7 >> ~/.bashrc

WORKDIR /workspace

ENTRYPOINT bash

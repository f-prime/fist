FROM debian:9 AS builder
WORKDIR /root/fist
COPY . /root/fist/
RUN set -ex; \
    apt-get update; \
    apt-get install -y --no-install-recommends \
        gcc \
        libc-dev \
        make; \
    rm -rf /var/lib/apt/lists/*; \
    make -j$(nproc)

FROM debian:9
COPY --from=builder /root/fist/bin/fist /usr/local/bin/fist
RUN set -ex; \
    groupadd --gid 1000 fist; \
    useradd --uid 1000 --gid fist --shell /bin/bash --no-create-home fist; \
    mkdir -p /var/local/lib/fist; \
    chown fist:fist /var/local/lib/fist; \
    mkdir -p /usr/local/etc/fist; \
    echo "Host 0.0.0.0" >> /usr/local/etc/fist/fist_config;
WORKDIR /var/local/lib/fist
USER fist
EXPOSE 5575
ENTRYPOINT ["/usr/local/bin/fist"]

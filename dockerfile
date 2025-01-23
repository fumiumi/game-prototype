FROM ubuntu:24.04

RUN apt-get update && apt-get install -y \
    build-essential \
    clang \
    cmake \
    ninja-build \
    git \
    python3 \
    python3-pip && \
    rm -rf /var/lib/apt/lists/*

# vcpkgのセットアップ
RUN git clone https://github.com/microsoft/vcpkg.git /vcpkg && \
    /vcpkg/bootstrap-vcpkg.sh && \
    echo "export PATH=/vcpkg:$PATH" >> /etc/profile

# アーキテクチャに応じたトリプレットの設定
RUN ARCH=$(uname -m) && \
    if [ "$ARCH" = "x86_64" ]; then \
        TRIPLET="x64-linux"; \
    elif [ "$ARCH" = "aarch64" ]; then \
        TRIPLET="arm64-linux"; \
    else \
        echo "Unsupported architecture: $ARCH"; exit 1; \
    fi && \
    /vcpkg/vcpkg install --triplet=$TRIPLET

# 環境変数の設定
ENV VCPKG_ROOT=/vcpkg
ENV PATH=${VCPKG_ROOT}:${PATH}
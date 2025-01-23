FROM ubuntu:24.04

# パッケージリストの更新
RUN apt-get update

# タイムゾーンの設定
RUN apt install -y tzdata
ENV TZ=Asia/Tokyo

# パッケージのインストール
RUN apt-get update && apt-get install -y \
    pkg-config \
    build-essential \
    clang \
    gcc \
    g++ \
    cmake \
    ninja-build \
    git \
    curl \
    zip \
    unzip \
    tar \
    libgl-dev \
    libglu1-mesa-dev \
    libxinerama-dev \
    libxcursor-dev \
    xorg-dev \
    autoconf \
    automake \
    libtool \
    && rm -rf /var/lib/apt/lists/*

# vcpkg のセットアップ
RUN git clone https://github.com/microsoft/vcpkg.git /vcpkg
WORKDIR /vcpkg
RUN git pull
RUN ./bootstrap-vcpkg.sh
RUN ./vcpkg update
RUN echo "export PATH=/vcpkg:$PATH" >> /etc/profile

# vcpkg.json をコピー
COPY ../vcpkg.json /vcpkg/vcpkg.json

# アーキテクチャ情報の取得
ARG TARGETARCH

# アーキテクチャに応じたトリプレットの設定
RUN case "$TARGETARCH" in \
  amd64) TRIPLET="x64-linux" ;; \
  arm64) TRIPLET="arm64-linux" ;; \
  *) echo "Unsupported architecture: $TARGETARCH"; exit 1 ;; \
  esac && \
  cd /vcpkg && \
  ./vcpkg install --triplet=$TRIPLET --x-manifest-root=/vcpkg

# 環境変数の設定
ENV VCPKG_ROOT=/vcpkg
ENV PATH=${VCPKG_ROOT}:${PATH}
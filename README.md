# game-prototype
新規企画のプロトタイプ用のエンジン開発

## 環境構築手順

os間で互換性を担保するために、`CMake`と`vcpkg`を利用する。vcpkgで依存ライブラリを統一

```
./vcpkg install sdl2 opengl
```


### コンパイラ設定の統一

CMakeを利用してコンパイラ設定を明示
CMakeLists.txtに共通設定を記述しておけば、コンパイラ設定を統一できます。

例：

```
# プロジェクトの基本設定
cmake_minimum_required(VERSION 3.15)
project(MyApp LANGUAGES CXX)

# コンパイラオプション
if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(MyApp PRIVATE /W4 /std:c++17)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "AppleClang")
    target_compile_options(MyApp PRIVATE -Wall -Wextra -std=c++17)
endif()
```

### プラットフォーム固有の設定

WindowsとmacOSで異なる設定が必要な場合は、CMakeの条件分岐を利用します。

例: プラットフォーム特化の処理

```bash
if(WIN32)
    target_link_libraries(MyApp PRIVATE ws2_32) # Windows固有のライブラリ
elseif(APPLE)
    target_link_libraries(MyApp PRIVATE "-framework Cocoa") # macOS固有の設定
endif()
```

### ビルド環境の自動化

スクリプトでビルドプロセスを統一
Windows用とmacOS用のビルドスクリプトをリポジトリに含めます。

```bash
cmake -G "Ninja" -B build
```

例: Windows（build.bat）

```bash
cmake -DCMAKE_TOOLCHAIN_FILE=C:/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake ..
cmake --build .
```

例: macOS（build.sh）

```bash
cmake -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake ..
cmake --build .
```

### 継続的インテグレーション（CI）の活用

```yaml
name: Build

on:
  push:
    branches:
      - main

jobs:
  build-windows:
    runs-on: windows-latest
    steps:
      - uses: actions/checkout@v3
      - run: ./vcpkg/bootstrap-vcpkg.bat
      - run: cmake -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake .
      - run: cmake --build .

  build-macos:
    runs-on: macos-latest
    steps:
      - uses: actions/checkout@v3
      - run: ./vcpkg/bootstrap-vcpkg.sh
      - run: cmake -DCMAKE_TOOLCHAIN_FILE=$HOME/vcpkg/scripts/buildsystems/vcpkg.cmake .
      - run: cmake --build .
```
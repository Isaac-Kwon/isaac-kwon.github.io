---
layout : single
title  : "CVMFS 세팅에서 garfieldpp 활용하기"
date   : 2019-07-17
categories:
  - ComputationalPhysics

toc : true
toc_label : "목차"
toc_sticky : true

show_adsense : true
---

다음 링크의 포스트를 발췌하였습니다. [gist link](https://gist.github.com/Isaac-Kwon/5d92144ab27b0b5c25a009a42c53fad9)

> ***2021년 7월 18일 기준, KISTI-GSDC-KIAF 실행 가능***

## garfieldpp 를 빌드하고 설치하기

> 본 과정을 시행하는데에 있어서, 예상하지 않은 에러(ERROR, Error, error)가 발생한 경우에는 **절대로** 바로 뒷 과정을 시행하지 말고, 에러메시지를 읽고 확인한 후 문제가 없으면 뒷 과정을 진행하세요. ~~제발~~
>
> **에러메시지가 발생하는 것은, 그 에러메시지나 나온 과정이나, 그 이전 과정에 오류가 있었던 것입니다.**

1. 필요사항 가져오기 (ROOT, GEANT, GSL 등)

    ``` bash
    source /cvmfs/sft.cern.ch/lcg/views/LCG_99/x86_64-centos7-gcc10-opt/setup.sh
    ```

2. 환경변수 설정

    1. 다음 둘 중 하나를 하세요.  
        만약, `$HOME/.bash_profile` 에 `export GARFIELD_HOME=/path/to/garfieldpp` 가 이미 있다면, 이 과정은 하지 않습니다.  
        (**주의:** `/path/to/` 는 garfieldpp 를 설치할 폴더입니다. 적절히 변경한 후 시행하세요.)
        - 다음과 같은 shell 커맨드를 입력하거나,

            ``` bash
            echo "export GARFIELD_HOME=/path/to/garfieldpp >> $HOME/.bash_profile"
            ```

        - 다음과 같이 시행합니다.

            ```bash
            # vi 를 활용하여 .bash_profile 을 엽니다.
            # vi 의 사용법 (입력방법, 종료방법) 을 모른다면, *nano* 를 써도 됩니다.
            vi $HOME/.bash_profile
            
            # 다음과 같은 텍스트를 파일 내에 입력하고 저장합니다.
            export GARFIELD_HOME=/path/to/garfieldpp
            ```

    2. 다음 커맨드를 shell 에 입력하세요.

    ```bash
    source $HOME/.bash_profile
    ```

3. 소스 가져오기 (`$GARFIELD_HOME` 에)

    1. `$GARFIELD_HOME` 이 비어있는지 확인하기

        ```bash
        ls -al $GARFIELD_HOME
        ```

        - 다음과 같이 `$GARFIELD_HOME` 안에 아무것도 없거나, `$GARFIELD_HOME` 폴더가 없어야 합니다.

            - 아무것도 없는 경우

                ``` text
                total 80
                drwxr-x---. 2 user group  0 Jan 02 00:02 .
                drwxrwx---. 4 user group 51 Jan 02 00:02 ..
                ```

            - 폴더가 없는 경우

                ``` text
                ls: cannot access /path/to/garfieldpp: No such file or directory
                ```

        - 폴더에 무언가가 있는 경우에는, 해당 폴더를 지워버림으로서 해결할 수 있습니다.  
            **지우기 전에 중요한 데이터가 있지는 않은지 확인하세요!**
            ```bash
            # sudo 하지마세요!
            rm -rf $GARFIELD_HOME
            ```

    2. `git clone` 하기
        ``` bash
        git clone https://gitlab.cern.ch/garfield/garfieldpp.git $GARFIELD_HOME
        ```
        
        - `gitlab.cern.ch` 의 계정정보를 요구하지 않습니다. 계정정보를 요구하는 경우에는 문제가 있는 것입니다. *(주소를 잘못 입력하였거나, 레포지토리를 찾을 수 없는 등의 문제)*

4. 빌드와 설치에 관한 환경 설정 (`cmake`)

    1. `$GARFIELD_HOME` 폴더로 이동합니다.

        ``` bash
        cd $GARFIELD_HOME
        ```

    2. `build` 폴더와 `install` 폴더를 생성합니다.

        ``` bash
        mkdir build install
        ```

    3. `build` 폴더에 진입합니다.

        ``` bash
        cd build
        ```

    4. `cmake` 를 합니다

        ``` bash
        cmake ..
        ```

        - 다음과 같이 텍스트들이 출력됩니다.

            ``` text
            -- The CXX compiler identification is GNU 10.1.0
            -- The Fortran compiler identification is GNU 10.1.0
            -- Detecting CXX compiler ABI info
            -- Detecting CXX compiler ABI info - done
            -- Check for working CXX compiler: /cvmfs/sft.cern.ch/lcg/releases/gcc/10.1.0-6f386/x86_64-centos7/bin/g++ - skipped

            ...

            -- Configuring done
            -- Generating done
            -- Build files have been written to: /path/to/garfieldpp/build
            ```

        - 출력된 마지막 텍스트가 위 텍스트의 마지막 3줄과 같아야 합니다.  
          (`/path/to/garfieldpp` 는 위에서 설정한 `$GARFIELD_HOME` 임.)

            - ***마지막 3줄이 정상적으로 출력되지 않았거나, 중간에 에러가 발생한 경우 절대 뒷 과정을 진행하지 마세요.***

        - `Install path: /path/to/garfieldpp/install` 의 `/path/to/garfieldpp/` 가 이전에 설정한 `$GARFIELD_HOME` 가 맞는지 확인하세요.

            - `cmake` 시작 후 출력되는 메시지의 12번째 줄에 있습니다.

            - 또는, `ccmake ..` 를 실행해보면, `CMAKE_INSTALL_PREFIX` 의 옆에 있습니다.

                - `ccmake` 는 `q` 를 눌러서 빠져나옵니다.

            - 또는, `CMakeCache.txt` 파일에서, `CMAKE_INSTALL_PREFIX:PATH=` 를 찾으면 됩니다.

5. 빌드와 설치 (`make`)

    1. *(빌드)* 다음과 같이 커맨드를 입력합니다.

        ``` bash
        make
        ```

        - 사용 가능한 코어 (또는 스레드) 갯수에 따라, 다음과 같이 입력하여 여러 스레드에 동시에 작업 할 수 있습니다. (`-j` 뒤의 숫자를 변경하면 됩니다.)

            ``` bash
            make -j4 # 코어를 최대 4개 동시에 사용
            make -j8 # 코어를 최대 8개 동시에 사용
            make -j20 # 코어를 최대 20개 동시에 사용
            ```

        - 마지막 메시지에 `Error` 와 같은 것이 없다면, 정상적으로 빌드된 것입니다.

    2. *(설치)* 다음과 같이 커맨드를 입력합니다.

        ``` bash
        make install
        ```

        - 출력되는 메시지 중에 `Error` 와 같은 (또는 유사한) 것이 없다면, 정상적으로 설치된 것입니다.


## garfieldpp 를 활용하여 프로그램 빌드하기

### 환경변수 설정

다음과 같은 커멘드를 한번에 입력하여서 환경 변수를 구성합니다.

{% gist 5d92144ab27b0b5c25a009a42c53fad9 garfield-envfun.sh %}

다음과 같이 `garfield-envfun.sh` 를 `source` 한 이후 `igarfield` 를 실행하면 자동으로 환경변수가 설정됩니다.

```bash
# 이렇게 실행하면,
source /path/to/garfield-envfun.sh
igarfield

# 다음과 같이 출력됩니다
Set garfieldpp!
```

환경변수를 확인해보면 다음과 같습니다.

``` bash
$ export | grep GARFIELD # 이렇게 실행하면,

# 아래와 같이 출력됩니다.
declare -x GARFIELD_HOME="/path/to/garfieldpp"
declare -x GARFIELD_HOME_CVMFS="/cvmfs/sft.cern.ch/lcg/releases/Garfield++/HEAD-09e01/x86_64-centos7-gcc10-opt"
declare -x GARFIELD_HOME_USER="/path/to/garfieldpp"
declare -x GARFIELD_INSTALL="/path/to/garfieldpp/install"
```

`source /path/to/garfield-envfun.sh` 를 `~/.bash_profile` 에 미리 입력해두면 필요시 `igarfield` 만 입력하면 손쉽게 환경변수를 설정할 수 있습니다.

### Standalone 빌드

> ***[주의]***  
> garfieldpp 환경변수가 설정된 shell에서만 standalone 빌드를 할 수 있습니다.  
> 환경변수가 설정되지 않은 shell 에서는 빌드를 진행할 때 에러메시지가 출력될 수 있습니다.  
> ``export | grep LD_LIBRARY_PATH`` 를 실행했을 때 출력되는 텍스트에 ``/path/to/garfieldpp/install/lib`` 가 있어야 합니다.

#### 빌드 연습

아무 예제를 들고와서 빌드해봅니다.

```bash
# 굳이 Silicon 예제가 아닌, 다른 예제를 활용해도 됩니다.
cp -r /path/to/garfieldpp/Examples/Silicon/ ~/ # 예제 중 하나를 홈폴더로 복사합니다.
cd ~/Silicon # 복사해 온 예제 폴더에 액세스합니다.
mkdir build  # build 폴더를 만듭니다.
cd build     # build 폴더에 액세스합니다.
cmake ..     # 소스 폴더에 cmake 를 합니다.
# 이 과정에서 에러가 나는 것은, 환경변수 설정이 제대로 되지 않은 것입니다.

make         # build 를 진행합니다.
# 이 과정에서 에러가 나는 것은, 적절한 환경이 cmake 에서 만들어지지 않았거나,
# 코드를 잘못 작성하여 에러가 난 것입니다.

# *** make install 은 하지 않습니다.
```

`build` 폴더에 새로 생성된 실행가능파일(Executable)을 실행하면 프로그램이 실행됩니다.

#### 자작 프로그램 빌드

자신이 만든 프로그램을 빌드해봅니다.

##### `CMakeLists.txt` 만들기

`cmake` 를 하기 위해서는 `CMakeLists.txt` 이 필요합니다. 이는 어떻게 `cmake` 를 할 지에 대한 적절한 안내문으로서, `CMakeLists.txt` 없이는 `cmake` 가 실행되지 않습니다.

*메모장*, `vi`, `nano`, *Visual Studio Code* 등으로 `CMakeLists.txt` 를 소스 폴더에 (`build` 폴더가 아님! 빌드할 코드가 있는 폴더와 동일한 폴더에!) 다음과 같이 입력하여 생성해줍니다. [참고자료1](https://gitlab.cern.ch/garfield/garfieldpp/-/blob/master/Examples/Silicon/CMakeLists.txt)

```cmake
#############################################################
# Use the code in this section for standalone projects
cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(myFirstProject)
if(NOT TARGET Garfield::Garfield)
  find_package(Garfield REQUIRED)
endif()
#############################################################
# Build executable
add_executable(myfirstprogram myfirstcode.cpp)
target_link_libraries(myfirstprogram Garfield::Garfield)

```

단 위 텍스트 중, 다음은 자신이 만든 파일의 이름이나 설정에 맞게 변경해주면 됩니다.

|   예시에서의 텍스트    | 변경해야할 텍스트                                |
|:------------------:|:-------------------------------------------|
| `myFirstProject`   | 프로젝트 이름                                  |
| `myfirstcode.cpp`  | 빌드할 코드의 파일명                             |
| `myfirstprogram`   | `myfirstcode.cpp` 가 빌드되어 나올 프로그램의 파일명 |

#### `cmake` 와 `make`

이후 과정은 *예제 빌드* 와 동일합니다.  
다음 커맨드를 입력합니다.

```bash
mkdir build  # build 폴더를 만듭니다.
# 이미 build 폴더가 있다면 생략해도 됩니다.

cd build     # build 폴더에 액세스합니다.
cmake ..     # 소스 폴더에 cmake 를 합니다.
# 이 과정에서 에러가 나는 것은, 환경변수 설정이 제대로 되지 않은 것입니다.

make         # build 를 진행합니다.
# 이 과정에서 에러가 나는 것은, 적절한 환경이 cmake 에서 만들어지지 않았거나,
# 코드를 잘못 작성하여 에러가 난 것입니다.

# *** make install 은 하지 않습니다.
```

#### 빌드된 프로그램 실행해보기

`build` 폴더 안에 생성된 실행가능파일을 실행해보면 됩니다. (예시에서는 `myfirstprogram`) `build` 폴더 안에서 다음과 같은 커맨드를 입력하면 됩니다.

```bash
./myfirstprogram # 만약 프로그램 파일명을 바꾼 경우, 그 파일명을 입력해야 합니다.
```

### ROOT 라이브러리 활용하기

> ***[주의]***  
> ***root 환경변수가 설정된 shell에서만 root 라이브러리를 포함한 빌드를 할 수 있습니다.***  
> ***환경변수가 설정되지 않은 shell 에서는 빌드를 진행할 때 에러메시지가 출력될 수 있습니다.***  
> ***`root-config --help` 를 실행했을 때, 메시지가 정상적으로 출력된다면 `root` 가 설정되어있는 것입니다.***

*garfieldpp* 가 ROOT 의 라이브러리를 일부분 가지고 활용하기는 하지만, 미리 연결되어있지 않은 라이브러리를 쓸 때에는 수동으로 연결해주어야 합니다. 이는 `CMakeLists.txt` 의 `target_link_libraries` 에 추가해주면 됩니다. (보통, `TTree` 를 쓸 때 문제가 발생합니다.)

연결될 다른 라이브러리와의 구별은 *띄어쓰기* 로 하면 됩니다.

아래 예시는 `ROOT` 의 `TTree` 를 활용할 때 필요한 라이브러리 연결하는 것에 대한 예시입니다.

```cmake
#############################################################
# Use the code in this section for standalone projects
cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(myFirstProject)

# Find Garfield
if(NOT TARGET Garfield::Garfield)
  find_package(Garfield REQUIRED)
endif()

#############################################################
# Build executable
add_executable(myfirstprogram myfirstcode.cpp)
target_link_libraries(myfirstprogram Garfield::Garfield ROOT::Tree)
```

ROOT 에서 연결가능한 라이브러리의 목록은 다음과 같습니다. [참고자료1](https://cliutils.gitlab.io/modern-cmake/chapters/packages/ROOT.html), [참고자료2](https://root.cern/manual/integrate_root_into_my_cmake_project/)

``` text
ROOT::Core
ROOT::Gpad
ROOT::Graf3d
ROOT::Graf
ROOT::Hist
ROOT::Imt
ROOT::MathCore
ROOT::Matrix
ROOT::MultiProc
ROOT::Net
ROOT::Physics
ROOT::Postscript
ROOT::RIO
ROOT::ROOTDataFrame
ROOT::ROOTVecOps
ROOT::Rint
ROOT::Thread
ROOT::TreePlayer
ROOT::Tree
```
---
layout: single
title: "X11 Forwarding 환경에서 DISPLAY 변수 가져오기"
date : 2023-01-25

toc : true
toc_label : "목차"
toc_sticky : false

show_adsense : true
---

## 오류

`tmux`나 `screen` 환경을 활용하면서 `X11Forwarding` 을 쓰고있을 때, 창을 띄우려고 하면 다음과 같은 오류가 날 때가 있습니다.

```text
Error: Can't open display: 127.0.0.1:1
```

본 오류는 shell 에 기존에 잡혀있던 환경변수 중 `DISPLAY` 가 현재 SSH 로 연결된 X11 소켓과 다른 경우 발생합니다. ssh 로 접속한 후 열린 shell 에서는 발생하지 않고, 접속 전부터 실행중이던 `tmux` 세션을 `attach` 했을 때, 그 세션에서 발생합니다.

## 해결 방법

본 오류는 `DISPLAY` 환경변수를 바꿔주는 것만으로 바로 작동합니다.

1. 올바른 `DISPLAY` 환경변수가 무엇인지 찾고
2. 그 환경변수를 적용하기만 하면 됩니다.

### 초간단 적용방법

가장 간단하게는, **새로운 shell 을 열고** 다음과 같이 입력합니다. (tmux 세션 안에서 발생한 문제였던 경우, 그 세션을 detatch 해서 빠져나오기만 해도 됩니다.) **환경변수를 참고하는 shell 에서 xclock, xeyes 등 X11Forwarding 은 작동해야합니다.**

```bash
$ export | grep DISPLAY
# >> 다음과 같이 출력됩니다. ('='뒤의 것들은 다를 수 있습니다.)
declare -x DISPLAY="127.0.0.1:5"
```

이것은, 처음의 shell 에서 127.0.0.1:1 가 아닌, 127.0.0.1:5 여야 한다는 것을 의미합니다.  
원래의 shell 로 돌아가서, 다음과 같이 입력하면 됩니다.

```bash
export DISPLAY=127.0.0.1:5
```

그러면 해당 shell 에서도 `xclock`, `xeyes` 를 작동하였을 때에도 `X11Forwarding` 이 제대로 작동합니다.

### 다른 Shell 쓰지 않고 해결하기

올바른 `DISPLAY` 를 찾는 방법을, 다음 StackExchange 에서 찾을 수 있습니다. [https://unix.stackexchange.com/questions/429092/](https://unix.stackexchange.com/questions/429092/){:target="_blank"}

``` bash
$ ps -u $(id -u) -o pid= |
  xargs -I{} cat /proc/{}/environ 2>/dev/null |
  tr '\0' '\n' |
  grep -m1 '^DISPLAY='
# >> 다음과 같이 출력됩니다. ('='뒤의 것들은 다를 수 있습니다.)
DISPLAY=127.0.0.1:5
```

위와 같은 결과를 얻었을 때, 결과값을 긁어다가, 다음과 같이 shell 에 입력하면 됩니다.

```bash
export DISPLAY=127.0.0.1:5
```

### 자동화

위 과정을 한번에 묶어서 한번에 할 수 있게 `alias` 를 만들면, 다음과 같습니다. 다음과 같은 shell script 를 `.bash_profile` 이나 `.bashrc` 에 넣어두면, `xx` 만 입력해주면 올바른 DISPLAY 환경변수를 자동으로 설정해줍니다.

```bash
alias xx="export \$(ps -u \$(id -u) -o pid= | xargs -I{} cat /proc/{}/environ 2>/dev/null | tr '\0' '\n' | grep -m1 '^DISPLAY=')"
```

## 참고자료

[https://unix.stackexchange.com/questions/429092/](https://unix.stackexchange.com/questions/429092/){:target="_blank"}

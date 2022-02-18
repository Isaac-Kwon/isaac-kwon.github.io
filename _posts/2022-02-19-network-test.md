---
layout : single
title  : "네트워크 속도 테스트 방법"
date   : 2022-02-19
categories: posts
toc : true
toc_label : "목차"
toc_sticky : true
#toc_icon : "angle-right"  # corresponding Font Awesome icon name (without fa prefix) -->

show_adsense : true
---


## `ssh` 로 다운로드 테스트

참고한 [링크 1](https://unix.stackexchange.com/questions/610133){:target="_blank"}, [링크 2](https://lateweb.info/how-to-check-the-speed-of-your-ssh-connection/){:target="_blank"}

``` bash
# Download
ssh remote_host cat /dev/zero | pv > /dev/null
# Upload
yes | pv | ssh remote_host "cat >/dev/null"
```

`pv` 는 별도 설치 필요 (CentOS: `yum install pv`, macOS: `brew install pv`)

### `scp` 에 비해 장점

* 저장장치 읽기/쓰기 병목현상을 배제한 테스트 가능.
* **원하는 시간 만큼** 테스트할 수 있음. (Ctrl+C - SIGINT - 로 중지가능)
    * `scp` 는 **정해진 용량만큼** 테스트하게 되는 것.


## `speedtest.net CLI`

[정식 안내 페이지](https://www.speedtest.net/apps/cli)

``` bash
# macOS
brew tap teamookla/speedtest
brew update
# Example how to remove conflicting or old versions using brew
# brew uninstall speedtest --force
brew install speedtest --force

# CentOS
## If migrating from prior bintray install instructions please first...
# sudo rm /etc/yum.repos.d/bintray-ookla-rhel.repo
# sudo yum remove speedtest
## Other non-official binaries will conflict with Speedtest CLI
# Example how to remove using yum
# rpm -qa | grep speedtest | xargs -I {} sudo yum -y remove {}
curl -s https://install.speedtest.net/app/cli/install.rpm.sh | sudo bash
sudo yum install speedtest
```

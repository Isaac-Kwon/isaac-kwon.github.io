---
layout: single
title: "macOS에서 ping 이 매우 튀는 현상"
date : 2023-01-25

categories: posts
tags:
  - post

toc : true
toc_label : "목차"
toc_sticky : false

show_adsense : true
---

macOS 에서, ***Wi-Fi 환경에서*** ping 이 가끔, 엄청 튀는 경우가 있습니다. 이러한 현상은 외부 망으로 접속하는 것 뿐만 아니라 *내부망* 에서 통신하는 경우도 발생합니다. 특징적인 부분은 ***Wi-Fi환경*** 에서만 발생한다는 것입니다. 이러한 ping 증가는 평시에는 큰 문제가 없으나, 실시간 상호작용을 하는 ping 이 매우 중요한 환경, 예를 들면 NVIDIA Geforce NOW 나 Stadia(지금은 중단됐지만)와 같은 클라우드 게이밍에서 화면과 소리가 끊기는 현상을 만들 수 있습니다.

```
64 bytes from 192.168.0.254: icmp_seq=508 ttl=64 time=1.762 ms
64 bytes from 192.168.0.254: icmp_seq=509 ttl=64 time=2.015 ms
64 bytes from 192.168.0.254: icmp_seq=510 ttl=64 time=1.912 ms
64 bytes from 192.168.0.254: icmp_seq=511 ttl=64 time=72.796 ms
64 bytes from 192.168.0.254: icmp_seq=512 ttl=64 time=1.583 ms
64 bytes from 192.168.0.254: icmp_seq=513 ttl=64 time=1.733 ms
64 bytes from 192.168.0.254: icmp_seq=514 ttl=64 time=1.579 ms
64 bytes from 192.168.0.254: icmp_seq=515 ttl=64 time=1.818 ms
64 bytes from 192.168.0.254: icmp_seq=516 ttl=64 time=1.631 ms
64 bytes from 192.168.0.254: icmp_seq=517 ttl=64 time=1.504 ms
64 bytes from 192.168.0.254: icmp_seq=518 ttl=64 time=1.601 ms
64 bytes from 192.168.0.254: icmp_seq=519 ttl=64 time=3.607 ms
64 bytes from 192.168.0.254: icmp_seq=520 ttl=64 time=1.784 ms
64 bytes from 192.168.0.254: icmp_seq=521 ttl=64 time=80.346 ms
64 bytes from 192.168.0.254: icmp_seq=522 ttl=64 time=1.592 ms
64 bytes from 192.168.0.254: icmp_seq=523 ttl=64 time=3.625 ms
```

80ms 에서, 가끔은 300ms 까지 ping 이 늘어나기도 합니다. 본 현상은 macOS의 에서 활용중인 다른 기능에 의해 ping 을 잡아먹는 것이며 (주로 브로드캐스트에 의해서) 가장 간단한 해결책은 ***무선인터넷을 쓰지 않고 유선 연결을 쓰는 것***입니다. 

## 예상할 수 있는 원인

* Wi-Fi 찾기
* AirDrop
* Location Service Setup

## 테스트 방법

여러 방법을 통해 테스트하면서 해결되었는지 파악할 수 있습니다.

### 핑테스트

```bash
ping -i 0.25 192.168.0.254 --apple-time
```

## 해결 방법

1. 다른 와이파이 등을 찾는 행동을 **하지 않습니다**
2. AirDrop 을 끕니다.
3. (한국어) 시스템 설정 -> 위치 서비스 -> (가장 아래) 시스템 서비스 [상세]-> 네트워킹 및 무선 (Networking and Wireless) **끄기**  <br>
   (영어) System Setting -> Location Service -> System Service [Detail] -> Networking and Wireless **끄기** <br>
   **또는,** 위치 서비스(Location Service) 자체를 끕니다.

## 참고할만한 페이지

* [Apple Developer Thread 97805](https://developer.apple.com/forums/thread/97805){:target="_blank"}
* [Apple StackExchange MacBook Pro experiencing ping spikes to local router](https://apple.stackexchange.com/questions/263638/macbook-pro-experiencing-ping-spikes-to-local-router){:target="_blank"}
* [OS X Daily Fix Wi-Fi Problems in macOS Sierra](http://osxdaily.com/2016/09/22/fix-wi-fi-problems-macos-sierra/9){:target="_blank"}

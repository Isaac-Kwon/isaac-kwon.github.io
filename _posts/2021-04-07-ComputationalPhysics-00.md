---
layout : single
title  : "실전 전산물리학"
date   : 2021-04-07
categories: posts
tags:
  - ComputationalPhysics
  - 실전전산물리학
toc : true
toc_label : "목차"
toc_sticky : true
toc_icon : "angle-right"  # corresponding Font Awesome icon name (without fa prefix) -->

show_adsense : true
---
> **실전 전산물리학**: *Computational Physics in a nutshell*

## 도입

*실전 전산물리학* 은 다음을 질문들을 위해 작성됩니다.  
물론, 계획은 거창하지만... 추후 변경될 수 있습니다.

* 물리학에서 하는 계산들에는 무엇이 있을까?
* 물리 실험을 설명하기 위한 모델(가설)을 어떻게 실험값과 비교할 수 있을까?
* 물리 실험을 어떻게 컴퓨터를 이용하여 시뮬레이션 할까?
* 물리 실험을 시뮬레이션하기 위해 무엇이 필요할까?
* 이 세상의 다른 물리 시뮬레이션은 어떻게 구동될까?
  * 계획적으로 프로그래밍을 할 수 있을까?
    * 시뮬레이션을 위해 만든 것을 조금 재사용을 잘 할 수 있도록 만들 수 있을까?
  * 실전에서 활용되는 물리 시뮬레이션은 어떻게 구성되어 있을까?
  * ~~세상은 컴퓨터로 이루어져 있을까?~~ 
* 실전에서 물리 시뮬레이션은 어떻게 활용될까?
  * 자주 겪을 수 있는 문제는 무엇일까?
* 물리학 실험값의 분석을 어떻게 해야할까?
* ~~GO TO STACK-OVERFLOW~~

~~내용에 대한 구상은 거의 다 했는데 언제 작문을 해서... 코딩을 해서... 포스팅이 될 지 기약이 좀 없음~~

## 포함할 내용

* 도입
  * 계산기
  * 계산기로서의 컴퓨터
  * 물리학에서 하는 계산들
* 물리 실험에서의 모델링 (일반물리학실험을 기반으로 하여)
  * 물리적 모델링, 이론과 실험
  * 중력가속도 실험의 실험 과정
  * 실험결과를 설명하기 위한 모든 것
  * 실전 계산
  * 오차의 발생과 전파
  * 다회 실험과 몬테카를로방법
* 컴퓨팅 세상으로 들어가기
  * 컴퓨터를 왜 쓸까?
  * 컴퓨터가 일하는 방법
  * 컴퓨터 시뮬레이션과 실험의 공통점
* 날코딩과 계획코딩
  * 컴퓨터에게 기초부터 가르치기
    * ~~기초는 개뿔 사드세요 제발~~
  * 물리적 모델을 계산기에 넣기
  * 물리적 모델을 *구조적*으로 계산기에 넣기
  * 실험 기구를 만들고 세팅하기
  * 구동 예시와 내부 구조
  * 최적화
  * 적용 예시
* 실전에서 쓸 수 있는 패키지 코딩
  * 물리학 이론도 결국에는 전산질이 된다
  * 실전에서 구축한 모델링 예시
* 최적화와 실전에서의 문제, 예시
  * 필요에 따른 계산정확도 구성
  * 독립연산 구성과 병렬화
  * 정수와 실수 문제, 데이터 타이핑문제
  * 메모리와 저장공간 소모, 그리고 극단분석
  * 바퀴의 재발명?
* 데이터 분석
  * 아날로그 데이터와 디지털 데이터
  * 진정한 의미의 디지털 데이터
  * 유의미한 값 측정하기
  * 측정된 값의 계산
  * 통계질 

내용 전개 상황에 따라 내용이 추가될 수도 있고, 통합되거나 삭제될수도 있습니다.  
내용 전개의 순서만을 나타낼 뿐, **각각의 줄이 하나의 포스트를 뜻하는 것은 아닙니다.**
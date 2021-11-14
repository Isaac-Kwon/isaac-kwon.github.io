---
layout: single
title:  "Javascript Plugin Test Page"
volume: 3
permalink: /jstestpage/
sitemap: false
---

Javascript 로 구성된 요소가 사용자의 웹브라우저에 작동하는지 판단하기 위한 웹페이지입니다.  
본 웹사이트에는 MathML, JSROOT 가 사용되었으며, 아래에서 해당 플러그인이 제대로 작동하는지 볼 수 있습니다.  
만약, 제대로 동작하지 않는 플러그인이 있는 경우, 웹 브라우저를 상위 버전으로 변경하거나, 최신 웹브라우저를 사용하여 주십시오.

This page is for testing the properties with Javascript for user's web browser.  
You can test your web browser with followings. If there's plugin not working, you should upgrade your web browser to higher version. (If your web-broswer is depreciated -- ex. Internet Explorer --, you should install nearly supported web-browser.)


## MathML

MathML 은 게시글에 수식을 작성하기 위해 사용되었으며, $$\LaTeX$$ 방식으로 작성된 수식을 보기 쉬운 형태로 바꾸어 표기해줍니다.

MathML is used for writing equations in post. It converts equations from $$\LaTeX$$ format to human-readable format.

$$ x = \frac{-b \pm \sqrt{b^2 - 4 ac}}{2 a} $$

$$ \LaTeX $$

> **Well printed example**
> **잘 표시된 예시**  
> ![MathML represenation example / MathML 표시 예시](/assets/img/JSTest/MathML.png)


## JSROOT

JSROOT 는 ROOT 를 웹 브라우저에서 상호작용하여 사용할 수 있도록 만들어진 Javascript 플러그인으로, 서버에 설치하여 분석환경을 제공하거나 외부에서 그래프를 읽을 수 있는 기조성된 ROOT 환경을 불러와 지정된 root 파일에서 화상요소를 (그래프, 히스토그램, 2차원/3차원 그래픽디자인 등) 불러올 수 있게 해줍니다.

JSROOT is javascript plugin for using ROOT in user's web browser with interactive . It can be used with installing on web server to serve analysis framework in javascript syntax. Also, pre-compiled application with JSROOT can be loaded from other website to load graphics (graph, histogram, 2D/3D graphic designs etc.) on web browser.

<iframe width="700" height="400"
        src="https://root.cern/js/latest/?nobrowser&file=../files/hsimple.root&item=hpxpy&opt=colz">
</iframe>

> **Well printed example**
> **잘 표시된 예시**  
> ![JSROOT represenation example / JSROOT 표시 예시](/assets/img/JSTest/JSROOT.png)

<!-- ## Chart.js

a -->

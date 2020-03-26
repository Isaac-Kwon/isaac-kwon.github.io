---
layout : single
title  : "분포 분석: 곡선 피팅"
date   : 2019-04-03
categories:
  - gplab

toc : true
toc_label : "목차"
toc_sticky : true
#toc_icon : "angle-right"  # corresponding Font Awesome icon name (without fa prefix) -->
---
<!-- 분포 분석은 다양한 방법으로 진행될 수 있는데, 그 중 곡선 피팅에 대해 다뤄보도록 한다. -->

> 이 페이지는 MathJax.js, JSROOT 를 활용합니다. 인터넷에 연결되어있지 않은 채로 페이지를 볼 경우 (페이지 저장 등) 일부 수식이 보이지 않을 수 있습니다.
>
> 페이지의 요소가 제대로 표시되지 않는 것으로 보일 경우 다음 링크를 통해 제대로 보이는지 확인해주십시오. [#](/jstestpage/)

분포 분석은 다양한 방법으로 진행될 수 있는데, 그 중 곡선 피팅에 대해 다뤄보도록 한다.


## 시작하기 전에, 간단 설명

**Q1. 곡선 피팅을 간단하게 설명해주세요.**  
두 변수 (또는 그 이상의 갯수) 사이의 측정값의 분포를 이용하여 두 변수 사이의 "대략적인 관계식을 알고 싶을 때" 활용하는 방법입니다. 정확하게는, **정해지지 않은 계수와 상수가 있는** 방정식에서, 분포에 맞추어 **계수와 상수를 찾는** 방법입니다.

**Q2. 그래서 무엇이 필요하나요?**  
다음 것들이 필요합니다.  

1. 변수쌍
2. 미지의 계수 또는 상수가 포함된 방정식
    - 단, 변수쌍은 미지의 계수 또는 상수의 갯수보다 많아야 함.

**Q3. 그래서 수학적으로 뭘 풀어야 하나요?**  
옛날같았으면 모든 것을 손으로 풀어야 했었지만, 요새는 세상이 좋아서 컴퓨터로 거의 다 됩니다. 엑셀, SPSS, MATLAB 등의 프로그램이 있고 1변수 1차방정식 정도는 $$\left(y=a x+ b \right)$$ ~~세상이 너무 좋은 나머지~~ 인터넷에 뒤져보면 계산해주는 페이지가 있습니다. <sub>[예시 링크](http://www.neoprogrammics.com/linear_least_squares_regression/)</sub>  
뭐 굳이 손으로 풀고 싶다면 막지는 않겠지만, 일반물리학실험 교재 맨 앞 챕터에 있습니다.

## 왜 하나요?
두 변수 사이의 관계를 알고싶을 때 활용합니다.  
아래와 같은 데이터를 가지고 있다고 합시다.

<!-- ![Image of datapoints on graph](/assets/img/posts/gplab/trendline_p1.png) -->
<div style="position:relative;padding-top:70.00%;">
<iframe style="position:absolute;top:0;left:0;width:98%;height:100%;" src="/assets/jsroot/?nobrowser&file=../img/posts/gplab/trendline_p1.root&item=c1;1">
</iframe>
</div>
**Figure 1) 어떤 1차식을 따르는 것 같아 보이는 그래프 위의 데이터포인트들**

**뭔가** $$y$$ 의 분포가 $$x$$ 값을 따르는 것 같고, **뭔가** 관계가 있어 보입니다. ~~물론 그렇게 데이터를 찍었으니까...~~ 근데 숫자로 된 값으로 ***$$x$$ 와 $$y$$ 가 어떤 관계가 있는지 관계식을 구하고 싶습니다.*** 그러면 어떻게 해야 할까요? 그냥 임의의 선 하나만 긋고 *'아 이런 것 같애'* 하면 비논리적입니다. 수치계의 논리학은 수학이니 수학적인 것을 써먹어야 합니다.

우리가 구하고 싶어하는 방정식의 형태는 아래 그림과 같을겁니다. (아직 방정식이 무엇인지는 표시하지 않았고, $$y=ax+b$$ 의 개형을 따른다고 가정합니다.)

<!-- ![Image of datapoints on graph with trendline](/assets/img/posts/gplab/trendline_p1_with_line.png) -->
<div style="position:relative;padding-top:70.00%;">
<iframe style="position:absolute;top:0;left:0;width:98%;height:100%;" src="/assets/jsroot/?nobrowser&file=../img/posts/gplab/trendline_p1.root&item=c2;1&item=c2;1">
</iframe>
</div>

**Figure 2) Figure 1 에서 1차식 피팅을 포함한 그래프**

간단히 말해서, 까만 데이터포인트와 거리를 최소화하는 <span style="color:red">빨간 직선</span>을 찾는 겁니다.

자세한 개념에 대한 이야기는 전반적인 이야기를 다 하고 다룹니다. (더 깊게 들어가면 안읽음. 간단한 이야기만 여기서...)

## 그래서 뭘 볼까요?

### 계수

수식을 찾았다는 것은 계수가 얼마인지 알게 되었다는 것입니다. 에상하는 수식의 개형으로부터 실질적인 **숫자** 를 알게 된 것은 다른 이론값/실험값과 비교할 것이 생겼다는 이야기입니다.

### 성능 판정

데이터로부터 수식을 추정했으면, 수식이 데이터에 얼마나 맞는지를 **수치적으로** 찾아야 합니다. 예상되는 수식의 개형이 하나라면 별 상관이 없지만, 하나 이상이거나 최소제곱법에 활용하는 수식이 비선형<sub>non-linear</sub>이어서 최소값을 바로 찾을 수 없는 경우에는 성능 판정을 한 후 그것을 다른 수식개형 또는 다른 계수에 대해 서로 비교하여 더 맞는 개형이나 계수를 결정합니다.

다음과 같은 여러 방법으로 진행할 수 있습니다. ~~나머지는 직접 찾아보시길 , (관련 검색어: Evaluating Goodness of Fit)~~

- 오차의 제곱합 : SSE
- 오차의 제곱평균제곱근 : RMSE
- 카이제곱/ndf : $$\chi^2/\mathrm{ndf}$$
- 결정계수 : $$R^2$$
- 수정된 결정계수 : $$\mathrm{Adjusted }R^2$$

## 자세한 이야기: 선지자의 부름

<!-- 약간 생각해보면, <span style="color:red">빨간 직선</span> 은 까만 데이터포인트들과의 거리가 최소화되면 직선이 데이터포인트를 잘 기술하는 것이 아닐까? 라고 생각해볼 수 있습니다.   -->
~~고맙게도~~ 이런걸 어떻게 하는지에 대한 문제는 선지자님들께서 다 풀어놓았습니다. ~~아니면 갓-컴퓨터가 할 수 있거나~~ **무언가를 최소화** 하는 아이디어는 오래 전 부터 있었던 생각으로, 그래프에서의 곡선 피팅은 **데이터포인트와** **피팅할 곡선이** 멀 수록 커지는 어떤 수를 **최소화하는** 아이디어에서 시작합니다. (물론 이런 방법이 한두개가 아닙니다)

### 최소제곱법

> 데이터 포인트 $$(x_i,y_i)$$ 와 방정식 $$f\left(x\right)$$ 가 있다고 할 때, $$\sum_{i} \left(y_i - f\left(x_i\right) \right)^2$$ 를 최소로 하는 $$f(x)$$ 를 찾는 방법

**저 수식들이 뭔지 모르겠어요!**  

네. 당연히 본격적인 분석을 ~~과학자 코스프레~~ 하려면 수식놀음을 해야합니다. 그런데 당연히 이해가 가지 않을 것입니다. 그러니 수식 나오는것을 하나하나 불러봅시다.

$$(x_i,y_i)$$ ... (Eq. 1)  
데이터포인트입니다. 실험에서 데이터를 뽑았을 때, 어떤 관계에 있는지는 모르는 두 변수 $$x$$ 와 $$y$$ 를 측정했고 그것을 $$n$$ 번 진행했는데 그 중 $$i$$ 번째 데이터입니다.

$$f\left(x\right)$$ ... (Eq. 2)  
계수를 찾고 싶어하는 어떤 함수입니다. 이 때의 함수는 계수만 결정되어있지 않고 개형은 대충 결정되어있어야합니다. $$y=ax+b$$ 라든지, $$y=A\exp\left[\beta x + \gamma \right]$$ 라든지의 **계수, 상수값만 없고** 형태는 갖추어져있어야 합니다.

$$y_i - f\left(x_i\right)$$ ... (Eq. 3)  
[Eq. 1] 에서의 데이터포인트 $$(x_i,y_i)$$ 에서의 $$x_i$$ 을 바탕으로 구한 방정식 $$f(x)$$ 의 값과 데이터포인트 $$y_i$$ 사이의 변위입니다. 간단히 말해서 **데이터포인트와 $$f(x)$$ 사이의 세로 변위** 이자, 데이터포인트의 **방정식으로부터 구한 예상치에 대한 편차** 입니다. 이것을 오차라고 부릅니다 (Error, Residual).  

$$\sum_{i} \left(y_i - f\left(x_i\right) \right)^2$$ ... (Eq. 4)  
[Eq. 3] 을 모든 데이터포인트에 대해 적용하여 제곱한 후 그것을 합한 것입니다. 이 값을 최소화하는 $$f(x)$$ 의 계수를 찾는 것이 목표입니다. **아직 모르겠다고요?**

**편차의 제곱의 합과** 비슷한 개념을 **분산<sub>Variation</sub>이라는**[^1] 이름으로 고등학교 통계시간에 배운 적이 있습니다. ~~수포자였다면 할 말 x~~ 다르게 말해서 평균값을 방정식의 값으로 간주하고 **분산을 최소화하는** 방향으로 방정식을 찾는 것이 목표입니다. ~~약간 다르지만~~

그림으로 다시 설명하자면, 
<!-- ![Image of datapoints on graph with trendline, plotted with residual](/assets/img/posts/gplab/trendline_p1_with_line_Residual.png) -->
<div style="position:relative;padding-top:70.00%;">
<iframe style="position:absolute;top:0;left:0;width:98%;height:100%;" src="/assets/jsroot/?nobrowser&file=../img/posts/gplab/trendline_p1.root&item=c3;1">
</iframe>
</div>
**Figure 3) Figure 2 에서 $$f(x_i)-y_i$$ 를 포함한 그래프**

Figure 3 에서 **각 파란 선의 길이의 제곱의 합이 최소가 되는** $$f(x)$$ 를 찾는 것입니다.

## 직선과 데이터 사이의 관계

피팅한 직선과 데이터와의 차이 또한 분석의 요소가 될 수 있습니다. 위에서, **찾은 직선** 은 모든 데이터포인트의 **대푯값** 정도로 해당하는 값으로 간주할 수 있으며, 그 대표값을 기준으로 실험값의 차이를 구해볼 수 있습니다.


<div style="position:relative;padding-top:110.00%;">
<iframe style="position:absolute;top:0;left:0;width:98%;height:100%;" src="/assets/jsroot/?nobrowser&file=../img/posts/gplab/trendline_p1_compare.root&item=c4;1">
</iframe>
</div>

**Figure 4) Figure 2 에서, 피팅한 직선과 데이터 사이의 오차를 추가한 그래프.**

Figure 4 에서 아래에 새로 그려진 그래프는 데이터값과 피팅 곡선 사이의 값 차이 (Figure 3 의 파란 선) 의 길이를 $$y$$ 값에 두고 그린 그래프입니다. 해당 그래프를 이용하면, 데이터 값이 피팅 곡선에 대해 $$x$$ 시계열 상에서 어떤 경향성을 보이는지 알 수 있습니다. Figure 4 는 경향성이 나타나지 않는 예시입니다만, 실제 데이터에서는 다음 예시와 같은 경향성을 보일 수 있습니다.

>
> * 피팅한 직선/곡선보다 낮은 값이었다가, 특정 값 이상에서 높아짐. (혹은 그 반대)
> * 피팅한 직선/곡선에 대해 일정 주기로 진동함.
>

또한, 다음 Figure 5 와 같이 오차를 계급값으로 하는 히스토그램을 그려볼 수 있습니다.

<div style="position:relative;padding-top:70.00%;">
<iframe style="position:absolute;top:0;left:0;width:98%;height:100%;" src="/assets/jsroot/?nobrowser&file=../img/posts/gplab/trendline_p1.root&item=c5;1">
</iframe>
</div>

**Figure 5) 오차의 분포 히스토그램**

값의 분포로부터 $$x$$ 와 $$y$$ 의 관계식에서 어떻게 값이 떨어져있는지를 볼 수 있습니다. Figure 5 로부터 오차는 -2와 2 사이에서 무작위로 분포하는 것으로 추정해볼 수 있습니다.  
분포를 더 확정해보고싶다면 히스토그램 $$x$$ 와 $$y$$ 의 관계쌍을 더 수집하여 (실험을 여러번 더 하여) 통계치를 더 늘려보면 됩니다.

[^1]: 편차의 제곱의 평균 $$$$


## 참고자료

1. Steven J. Miller, The Method of Least Squares, [https://web.williams.edu/Mathematics/sjmiller/public_html/BrownClasses/54/handouts/MethodLeastSquares.pdf](https://web.williams.edu/Mathematics/sjmiller/public_html/BrownClasses/54/handouts/MethodLeastSquares.pdf)

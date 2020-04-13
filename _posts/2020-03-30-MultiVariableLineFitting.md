---
layout : single
title  : "3변수 직선 맞춤"
date   : 2020-03-30
categories: post gplab
toc : true
toc_label : "목차"
toc_sticky : true
#toc_icon : "angle-right"  # corresponding Font Awesome icon name (without fa prefix) -->
---

> 작성중, 뭔가 안맞는데 확인중임.

> 이 페이지는 MathJax.js, JSROOT 를 활용합니다. 인터넷에 연결되어있지 않은 채로 페이지를 볼 경우 (페이지 저장 등) 일부 수식이 보이지 않을 수 있습니다.
>
> 페이지의 요소가 제대로 표시되지 않는 것으로 보일 경우 다음 링크를 통해 제대로 보이는지 확인해주십시오. [#](/jstestpage/)

2차원 평면에서의 직선 맞춤 (직선 피팅) 은 알려진 바에 따라 최소제곱법으로 쉽게 유도할 수 있고, 3변수 단일방정식 또한 동일한 방식으로 구할 수 있다.

다만, $$n$$ 개의 차원을 가진 $$n$$ 개 이상의 위치들에 대해 $$n-1$$ 차원의 성질을 가지는 피팅을 진행할 수는 있으나, (2차원 공간에서 1차원 직선 피팅을 하는 것과 3차원 공간에서 2차원 평면 피팅을 하는 것들.) 

# 단일 방정식과 직선

2차원 공간에서의 단일 방정식 (ex. $$y=2x+1$$) 은 직선을 나타내지만, 3차원 공간에서의 단일 방정식 (ex. $$x+2y+z=2$$) 는 평면을 나타낸다. 이것은, $$n$$ 차원 공간에서 정의된 방정식에서 $$n-1$$ 개 변수의 값을 정해주면 나머지 하나의 값을 알 수 있는 것인데, 이와 다르게 직선은 1개의 변수 값만 주어지만 나머지 변수들의 값도 바로 알 수 있다. 그렇기 위해서는, 다음과 같은 방법으로의 정의를 해주면 된다.

$$ \begin{aligned} \text{With }& \vec{x_0} \text{ and } \vec{v_0} \\ \text{All point on } \overrightarrow{x} = &\vec{x_0} + t\vec{v_0}  \text{  for any real number }t \end{aligned} $$

그러면, 만약 이 직선이 3차원에서의 값이라고 하면, $$\overrightarrow{x_0}$$ 와 $$\overrightarrow{v_0}$$ 에서 각각 3개의 원소가 있으니 6개의 미지수를 풀어야 합니다.  

## 결국엔 저 상수들은, 최소제곱법으로 구해야 한다.

**최소제곱**법이란 결국에는 데이터포인트들 중 하나와 그것에 준할 새로운 대푯값과 어떤 연산을 하여 제곱 한 후 모든 데이터포인트에 대해 합한 것이 최소가 되도록 하는 방법이니, *어떤 연산* 을 무엇을 할 지부터 생각해보아야 합니다.  
일단, 3차원 *공간* 이라는 눈에 보이는 기하학적 특성이 있고 최종적으로 찾을 것이 어떤 *직선* 이라는, 이 또한 기하학적인 것이니 찾을 직선과 데이터포인트 사이의 거리를 그 *어떤 연산* 이라고 정의하는 것이 말이 되어 보입니다.  
그러니, 다음 방법으로 설명가능하게 최소제곱법을 찾아보도록 합시다.


> **데이터포인트와 직선 사이의 거리의 제곱의 합** 이 최소가 되게 하는 방법

이를 조금 더 수학적인 말을 붙여서 정의하면 아래와 같습니다.

> 데이터포인트 $$\vec{x_n}$$ 에 대해 데이터포인트와 직선사이 거리 $$d_n$$ 의 제곱의 합인 $$\sum_n{d_n^2}$$ 이 최소가 되도록 하는 방법

그러면, 데이터포인트와 직선 사이의 거리는 어떻게 구하는가가 문제가 됩니다.

## 3차원 공간에서, 직선과 점 사이의 거리 구하기

![임의의 데이터포인트에 대해 직선과의 거리를 구하는 기하학적 도식](/assets/img/posts/gplab/FittingDistance.png)

데이터 포인트 X<sub>n</sub> 과 직선 위로의 데이터포인트로부터의 수선의 발인 P<sub>n</sub>, 직선 위 어떤 점 (중 초기점으로 쓰이는 점) X<sub>0</sub> 로 구성된 직각삼각형을 그려보면, 이 직각삼각형의 면적과 2차원 벡터에서의 외적과의 관계를 활용하여 다음과 같은 등식을 쓸 수 있습니다.

$$
\left|\overrightarrow{d_n}\times\left(\vec{x_0}-\vec{x_n}\right)\right| = \left| t\vec{v_0}  \times\left(\vec{x_0}-\vec{x_n}\right) \right| = \left| t\vec{v_0}  \times \overrightarrow{d_n} \right|
$$

이 중 두번째와 세번째 항만 가져다가 쓰고 P<sub>n</sub> 의 점의 정의에 의해 다음과 같은 관계가 성립합니다.

$$\left| t\vec{v_0} \times \overrightarrow{d_n}  \right| = t \left|\vec{v_0}\right|\left|\overrightarrow{d_n}\right| $$

해당 사항을 활용하여 두번째 항과 세번째 항을 풀면 다음과 같은 관계가 있습니다.

$$
\begin{align}
\left| t\vec{v_0}  \times\left(\vec{x_0}-\vec{x_n}\right) \right| &= \left| t\vec{v_0}  \times \overrightarrow{d_n} \right|\\
 & = t \left|\vec{v_0}\right|\left|\overrightarrow{d_n}\right| \\ 
t \left|\vec{v_0}  \times\left(\vec{x_0}-\vec{x_n}\right) \right| & = \\
\frac{\left|\vec{v_0}  \times\left(\vec{x_0}-\vec{x_n}\right) \right|}{\left|\vec{v_0}\right|} & = \left|\overrightarrow{d_n}\right| \left(\equiv d_n\right)
\end{align}
$$

어떤 $$\vec{x_0}$$ 와 $$\vec{v_0}$$ 을 주면, 먼저 주어진 데이터포인트 X<sub>n</sub> 에 대해 $$d_n$$ 를 구할 수 있게 되었고, $$\sum_n{d_n} \left(\equiv S\right)$$ 을 구할 수 있게 되었습니다.

# 최소제곱법으로 상수 구하기

## 거리 제곱의 합에 대한 식을 정리하기

$$ 
\begin{align}
S = \sum_n{d_n^2} & = \sum_n\left(\frac{\left|\vec{v_0}  \times\left(\vec{x_0}-\vec{x_n}\right) \right|}{\left|\vec{v_0}\right|}\right)^2 \\
&= \sum_n\frac{\left(\vec{v_0}  \times\left(\vec{x_0}-\vec{x_n}\right)\right) \cdot \left(\vec{v_0}  \times\left(\vec{x_0}-\vec{x_n}\right)\right) }{\vec{v_0}\cdot\vec{v_0}}
\end{align}
$$

$$\sum$$ 안의 $$d_n^2$$ 의 분자값부터 계산하면, 벡터곱 규칙 $$A \cdot \left( B \times C \right) = B \cdot \left( C \times A \right)$$ 에 의해 

$$
\begin{align}
 & \left(\vec{v_0}  \times\left(\vec{x_0}-\vec{x_n}\right)\right) \cdot \left(\vec{v_0}  \times\left(\vec{x_0}-\vec{x_n}\right)\right) \\
=& \vec{v_0} \cdot \left( \left(\vec{x_0}-\vec{x_n}\right) \times \left(\vec{v_0}  \times\left(\vec{x_0}-\vec{x_n}\right)\right) \right)
\end{align}
$$

이고, 백터삼중곱 규칙 $$ A \times \left( B \times C \right) = \left(A \cdot C\right) B - \left(B \cdot C\right)A $$ 에 의해 (여기서는, 편의상 $$ \vec{x_n}' = \vec{x_0}-\vec{x_n} $$ 로 두자.) 위 식은

$$
\begin{align}
&= \vec{v_0} \cdot \left( \vec{x_n}' \times \left(\vec{v_0}  \times \vec{x_n}' \right)\right)\\
&= \vec{v_0} \cdot \left( \left(\vec{x_n}' \cdot \vec{x_n}' \right) \vec{v_0} - \left(\vec{v_0} \cdot \vec{x_n}' \right)\vec{x_n}' \right)\\
&= \left(\vec{x_n}' \cdot \vec{x_n}' \right) \left(\vec{v_0} \cdot \vec{v_0} \right) - \left(\vec{v_0} \cdot \vec{x_n}' \right)^2
\end{align}
$$

로 변환됩니다. 분모값도 같이 들고와서 $$d_n^2$$ 을 계산해보면,

$$
\begin{align}
d_n^2 &= \frac{\left(\vec{x_n}' \cdot \vec{x_n}' \right) \left(\vec{v_0} \cdot \vec{v_0} \right) - \left(\vec{v_0} \cdot \vec{x_n}' \right)^2}{\vec{v_0}\cdot\vec{v_0}}\\
      &= \left(\vec{x_n}' \cdot \vec{x_n}' \right) - \frac{\left(\vec{v_0} \cdot \vec{x_n}' \right)^2}{\vec{v_0}\cdot\vec{v_0}}
\end{align}
$$

이라는 $$\vec{v_0}$$ 에 관련이 있는 항과 없는 항으로 분리됩니다.

## 최솟값 조건 쓰기

최솟값 또는 최댓값에서 다음과 같은 수식이 성립함을 생각할 수 있습니다.

$$ \nabla S = 0 $$

이는 각각 모든 변수인 $$\vec{x_0}$$ 와 $$\vec{v_0}$$ 의 요소들로 분해될 수 있으며, 그러므로

$$ \nabla S = \left(\nabla_\vec{x_0} + \nabla_\vec{v_0} \right) S = 0 $$

입니다. 구하고자 하는 모든 변수에 대해 (어떤 변수의 상황에서) 그 변수들이 변화함에 따라 가지는 거리의 변화가 0이어야 한다는 뜻으로, Gradient ($$\nabla$$) 는 벡터값이므로, 모든 변수에 대해 극대/극소값을 찾는 것이라고 볼 수 있습니다.

$$S=\sum_n{d_n^2}$$ 이므로, $$\nabla S=\nabla \sum_n{d_n^2}$$ 이나, 미분연산자 $$\nabla$$ 는 합연산에 내포될 수 있습니다.$$\sum_n{\nabla d_n^2}$$ 의 연산을 진행하면 되며, 편의상 $$\nabla d_n^2$$ 의 연산을 끝낸 후에 합연산을 하도록 합니다.

## 벡터미분연산

개별 요소의 미분 연산을 하려면, 다음과 같은 미분연산을 해야합니다.

$$
\begin{align}
\nabla d_n^2 &= \left(\nabla_\vec{x_0} + \nabla_\vec{v_0} \right) d_n^2\\
&= \left(\nabla_\vec{x_0} + \nabla_\vec{v_0} \right) \left( \left(\vec{x_n}' \cdot \vec{x_n}' \right) - \frac{\left(\vec{v_0} \cdot \vec{x_n}' \right)^2}{\vec{v_0}\cdot\vec{v_0}} \right)
\end{align}
$$

위 연산을 하기 위해서, 다음 4개 미분연산을 하고 적절히 합해주면 됩니다.

$$
\begin{align}
&\nabla_\vec{x_0} \left(\vec{x_n}' \cdot \vec{x_n}' \right) 
&\nabla_\vec{x_0} \frac{\left(\vec{v_0} \cdot \vec{x_n}' \right)^2}{\vec{v_0}\cdot\vec{v_0}} \\
&\nabla_\vec{v_0} \left(\vec{x_n}' \cdot \vec{x_n}' \right) \left(=0\right)
&\nabla_\vec{v_0} \frac{\left(\vec{v_0} \cdot \vec{x_n}' \right)^2}{\vec{v_0}\cdot\vec{v_0}}
\end{align}
$$

왼쪽 아래 방정식은, $$\vec{v_0}$$ 와 $$\vec{x_0}$$ 는 무관하니 직관적으로 0임을 알 수 있습니다. 그러니, 그것을 제외한 세 개만 풀어주면 됩니다.

## 각 항별로 풀기

$$ \begin{align}
\hat{v_0} &\equiv \vec{v_0}/\left|\vec{v_0}\right| \\
\vec{x_n}' &\equiv \vec{x_0} - \vec{x_n}
\end{align} $$

### 첫번째 항 

$$
\begin{align}
 \nabla_\vec{x_0} \left(\vec{x_n}' \cdot \vec{x_n}' \right) &= \nabla_\vec{x_0} \left(\left(\vec{x_0}-\vec{x_n}\right) \cdot \left(\vec{x_0}-\vec{x_n}\right) \right) \\
&= 2\left(\vec{x_0}-\vec{x_n}\right) \nabla_\vec{x_0}\left(\vec{x_0}-\vec{x_n}\right)\\
&= 2\left(\vec{x_0}-\vec{x_n}\right)\\
&= 2\vec{x_n}'
\end{align}
$$

### 두번째 항

$$\begin{align}
\nabla_\vec{x_0} \frac{\left(\vec{v_0} \cdot \vec{x_n}' \right)^2}{\vec{v_0}\cdot\vec{v_0}} &= \frac{1}{\vec{v_0}\cdot\vec{v_0}} \nabla_\vec{x_0} \left(\vec{v_0} \cdot \left(\vec{x_0}-\vec{x_n}\right) \right)^2 \\
&= \frac{2}{\vec{v_0}\cdot\vec{v_0}}  \left(\vec{v_0} \cdot \left(\vec{x_0}-\vec{x_n}\right) \right) \nabla_\vec{x_0} \left(\vec{v_0} \cdot \left(\vec{x_0}-\vec{x_n}\right) \right)\\
&= \frac{2}{\vec{v_0}\cdot\vec{v_0}}  \left(\vec{v_0} \cdot \left(\vec{x_0}-\vec{x_n}\right) \right) \vec{v_0}\\
&= 2 \left(\hat{v_0} \cdot \vec{x_n}' \right) \hat{v_0}
\end{align}
$$

### 네번째 항

$$\begin{align}
\nabla_\vec{v_0} \frac{\left(\vec{v_0} \cdot \vec{x_n}' \right)^2}{\vec{v_0}\cdot\vec{v_0}} &=  \nabla_\vec{v_0} \frac{\left(\vec{v_0} \cdot \left(\vec{x_0}-\vec{x_n}\right) \right)^2}{\vec{v_0}\cdot\vec{v_0}}\\
&= \frac{ \left(\vec{v_0}\cdot\vec{v_0}\right) \nabla_\vec{v_0} \left(\vec{v_0} \cdot \left(\vec{x_0}-\vec{x_n}\right) \right)^2 - \left(\vec{v_0} \cdot \left(\vec{x_0}-\vec{x_n}\right) \right)^2\nabla_\vec{v_0} \left(\vec{v_0}\cdot\vec{v_0}\right) }{ \left(\vec{v_0}\cdot\vec{v_0}\right)^2  } \\
&= \frac{ \left(\vec{v_0}\cdot\vec{v_0}\right) 2\left(\vec{v_0}\cdot\left(\vec{x_0}-\vec{x_n}\right)\right)\left(\vec{x_0}-\vec{x_n}\right) - \left(\vec{v_0} \cdot \left(\vec{x_0}-\vec{x_n}\right) \right)^2 2 \vec{v_0} }{ \left(\vec{v_0}\cdot\vec{v_0}\right)^2  }\\
&= 2\frac{ \left(\vec{v_0}\cdot\vec{v_0}\right)\left(\vec{v_0}\cdot\left(\vec{x_0}-\vec{x_n}\right)\right)\left(\vec{x_0}-\vec{x_n}\right) - \left(\vec{v_0} \cdot \left(\vec{x_0}-\vec{x_n}\right) \right)^2 \vec{v_0} }{ \left(\vec{v_0}\cdot\vec{v_0}\right)^2  }\\
&= 2\frac{ \left(\hat{v_0}\cdot \vec{x_n}' \right)\vec{x_n}' - \left(\hat{v_0} \cdot \vec{x_n}' \right)^2 \hat{v_0} }{ \left(\vec{v_0}\cdot\vec{v_0}\right)^{1/2}  }
\end{align}
$$

### 합산

$$
\nabla d_n^2 = 2\vec{x_n}' -  2 \left(\hat{v_0} \cdot \vec{x_n}' \right) \hat{v_0} - 2\frac{ \left(\hat{v_0}\cdot \vec{x_n}' \right)\vec{x_n}' - \left(\hat{v_0} \cdot \vec{x_n}' \right)^2 \hat{v_0} }{ \left(\vec{v_0}\cdot\vec{v_0}\right)^{1/2} } 
$$

이므로

$$
\nabla S = \nabla \sum_n{ d_n^2} = 2 \sum_n{\left[ \vec{x_n}' - \left(\hat{v_0} \cdot \vec{x_n}' \right) \hat{v_0} - \frac{ \left(\hat{v_0}\cdot \vec{x_n}' \right)\vec{x_n}' - \left(\hat{v_0} \cdot \vec{x_n}' \right)^2 \hat{v_0} }{ \left(\vec{v_0}\cdot\vec{v_0}\right)^{1/2} } \right]}
$$

$$\nabla S = 0$$ 인 조건을 풀면 되나, 여러 벡터 성분이 있으므로 모든 벡터 성분이 0이 되어야 합니다. 각 벡터 성분 별로 모두 0이 되는 조건을 찾으면 됩니다.

## 각 벡터 성분별로 풀기

위 방정식을 벡터 성분 $$\vec{x_n}'$$ (정확하게는, $$\vec{x_0}$$) 과 $$\hat{v_0}$$ 으로 나누어 풀면, 

$$
\begin{align}
0 &= \sum_n{ \vec{x_n}' \left(1 - \frac{\left(\hat{v_0}\cdot \vec{x_n}' \right) }{ \left(\vec{v_0}\cdot\vec{v_0}\right)^{1/2}} \right) } & ... & ~~~(1)\\
0 &= \sum_n{  \left(\hat{v_0}\cdot\vec{x_n}'\right) \left( 1 + \frac{\left(\hat{v_0} \cdot \vec{x_n}' \right) }{ \left(\vec{v_0}\cdot\vec{v_0}\right)^{1/2} } \right) } & ... & ~~~ (2)
\end{align}
$$

의 서로 유사해보이는 두 식으로 분리할 수 있습니다. $$(2)$$ 식에는, 맨 앞에 $$\hat{v_0}$$ 이 곱하여져 있어야 하나 값의 정의상 0이 될 수 없기 때문에 그 뒤 급수만 표기하였습니다.

$$(1)$$ 식에 $$\hat{v_0}$$ 을 점곱하여 $$(2)$$ 식과 더하고 빼면, 다음과 같은 관계를 구할 수 있습니다.

$$ \begin{align}
0 &= \sum_n{\hat{v_0}\cdot\vec{x_n}'} = \hat{v_0}\cdot \sum_n{\vec{x_n}'}  & ... & ~~~(3)\\
0 &= \sum_n{\left(\hat{v_0}\cdot\vec{x_n}'\right)^2}  & ... & ~~~(4)\\
\end{align} $$ 

$$(3)$$ 식으로 부터 $$\sum_n{\vec{x_n}'}$$ 와 $$\hat{v_0}$$ 은 수직이거나, $$\sum_n{\vec{x_n}'}=0$$ 이어야 한다는 사실을 알 수 있습니다.

<!-- 
# 직선이니까 가능한 방법
~~인생은 리니어하다ㅏㅏㅏ~~ -->

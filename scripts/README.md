## 소개

[Atcoder](https://atcoder.jp/) 및 여타 online judge를 command line으로 제출하기 위해 만들어진 [online-judge-tools/oj](https://github.com/online-judge-tools/oj)를 조금 더 원활하게 사용하기 위한 스크립트 파일들입니다.

oj에 대한 사용법은 [공식 docs](https://github.com/online-judge-tools/oj/blob/master/docs/getting-started.md)를 참고하시거나, [여기](https://blog.naver.com/raararaara/223106235174)를 확인해주세요.

## 사용법

Atcoder Beginner Contest를 기준으로 사용할 수 있습니다.

현재 스크립트는 아래와 같은 디렉토리 구조를 기준으로 작성되었습니다.

```
.
├── root
│── scripts
│   ├── down
│   ├── set
│   ├── s
│   └── t
├── test
│   ├── sample-1.in
│   ├── sample-1.out
│   ├── sample-2.in
│   ├── sample-2.out
│   └── ...
├── Utils
│   ├── LazySegTree.hpp
│   ├── SegTree.hpp
│   └── ...
├── a.out
├── input.txt
├── main.cpp
└── ...
```

```bash
> sh set ROUND_NO
> sh down TASK_NO
> sh t
> sh s TASK_NO
```

* `set`

  submission과 test case download를 위해 url이 필요합니다.
  
  특정 문제의 url은 `https://atcoder.jp/contests/abc[0-9]*/tasks/abc[0-9]*_[a-z]` 와 같은 포맷이므로, tc download, 혹은 submit 전에 알맞은 라운드로 변경해줍니다.

  ```bash
  > sh set 303
  down:
  rm -rf ../test/ && oj d https://atcoder.jp/contests/abc303/tasks/abc303_$1 -d ../test/
  s:
  oj s -l 4003 -y --no-open https://atcoder.jp/contests/abc303/tasks/abc303_$1 ../main.cpp
  ```
  
* `down`

  지정한 문제에 해당하는 test case들을 다운받습니다.
  상위 디렉토리에 `test/`라는 디렉토리를 flush한 후 요청한 문제에 대한 sample input & output에 대한 정보가 다운로드됩니다.

  ```bash
  > sh down c
  [INFO] online-judge-tools 11.5.1 (+ online-judge-api-client 10.10.1)
  [INFO] load cookie from: /Users/user/Library/Application Support/online-judge-tools/cookie.jar
  [NETWORK] GET: https://atcoder.jp/contests/abc303/tasks/abc303_c
  [NETWORK] 200 OK
  [INFO] save cookie to: /Users/user/Library/Application Support/online-judge-tools/cookie.jar

  [INFO] sample 0
  [INFO] input: sample-1
  4_2_3_1
  RUDL
  -1_-1
  1_0
  
  [SUCCESS] saved to: ../test/sample-1.in
  [INFO] output: sample-1
  Yes

  [SUCCESS] saved to: ../test/sample-1.out
  
  [INFO] sample 1
  [INFO] input: sample-2
  5_2_1_5
  LDRLD
  0_0
  -1_-1
  
  [SUCCESS] saved to: ../test/sample-2.in
  [INFO] output: sample-2
  No
  
  [SUCCESS] saved to: ../test/sample-2.out
  ```
* `t` (test)

  download한 sample input을 기준으로 `main.cpp` 를 실행했을 때 나오는 결과와 sample output을 비교합니다.
  * 커스텀 테스트케이스의 경우 `input.txt` 에 작성을 한 후 `main.cpp` 내에서는 `input.txt` file open부분을 `#ifndef ONLINE_JUDGE`, `#endif`로 묶어서 처리할 수 있습니다.
  * sample input & output과의 비교 시 ignore-space & ignore newline 옵션이 켜져 있습니다.(`-N`)
  
  ```bash
  > sh t
  [INFO] online-judge-tools 11.5.1 (+ online-judge-api-client 10.10.1)
  [INFO] 2 cases found
  [WARNING] GNU time is not available: gtime
  [HINT] You can install GNU time with: $ brew install gnu-time
  
  [INFO] sample-1
  [INFO] time: 0.299283 sec
  [SUCCESS] AC
  
  [INFO] sample-2
  [INFO] time: 0.015473 sec
  [SUCCESS] AC
  
  [INFO] slowest: 0.299283 sec  (for sample-1)
  [SUCCESS] test success: 2 cases
  ```
* `s` (submit)
  
  디렉토리 내 main.cpp를 args로 넘겨준 문제번호에 맞춰 제출합니다.
  * 제출 언어 및 컴파일러를 C++ GCC 9.2.1로 설정하였습니다.(`-l 4003`)
  * default option은 제출 시 confirm check & submission result page를 open합니다.
    
    현재 스크립트는 confirm check을 하지 않고(`-y`) result page또한 열지 않습니다.(`--no-open`) 
  ```bash
  > sh s c
  [INFO] online-judge-tools 11.5.1 (+ online-judge-api-client 10.10.1)
  [WARNING] cannot guess URL since the given file is not in the current directory
  [INFO] code (1597 byte):
  #include<bits/stdc++.h>
  #include_<ext/pb_ds/assoc_container.hpp>
  
  using_namespace_std;
  using_namespace___gnu_pbds;
  using_lint_=_long_long;
  using_ii_=_pair<int,_int>;
  using_il_=_pair<int,_lint>;
  using_li_=_pair<lint,_int>;
  using_ll_=_pair<lint,_lint>;
  ... (51 lines) ...
  ____________if(mp.find(ii(cx,_cy))_!=_mp.end()_&&_H_<_K)_{
  ________________H_=_K;
  ________________mp.erase(ii(cx,_cy));
  ____________}
  ________}
  ________cout_<<_Yes;
  ____}
  
  ____return_0;
  }
  
  [INFO] load cookie from: /Users/user/Library/Application Support/online-judge-tools/cookie.jar
  [NETWORK] GET: https://atcoder.jp/contests/agc001/submit
  [NETWORK] 200 OK
  [INFO] You are logged in.
  [NETWORK] GET: https://atcoder.jp/contests/abc303/tasks/abc303_c
  [NETWORK] 200 OK
  [INFO] chosen language: 4003 (C++ (GCC 9.2.1))
  [WARNING] the problem "https://atcoder.jp/contests/abc303/tasks/abc303_c" is specified to submit, but no samples were downloaded in this directory. this may be mis-operation
  [NETWORK] GET: https://atcoder.jp/contests/abc303/tasks/abc303_c
  [NETWORK] 200 OK
  [NETWORK] GET: https://atcoder.jp/contests/abc303/submit
  [NETWORK] 200 OK
  [NETWORK] POST: https://atcoder.jp/contests/abc303/submit
  [NETWORK] redirected to: https://atcoder.jp/contests/abc303/submissions/me
  [NETWORK] 200 OK
  [SUCCESS] result: https://atcoder.jp/contests/abc303/submissions/41928705
  [INFO] save cookie to: /Users/user/Library/Application Support/online-judge-tools/cookie.jar
  ```
  
## .zshrc

스크립트 파일을 좀더 편리하게 사용할 수 있도록 command를 구성했습니다.

본인의 shell profile에 copy&paste하여 사용하실 수 있습니다.

```shell
> ac chk
> ac set ROUND_NO
> ac s [TASK_NO]
> ac t
> ac nxt
> ac down [TASK_NO]
```

* `ac chk`

  환경변수 `TASK_NO`와 스크립트 파일 `down`, `s`의 내용을 출력합니다.
  
* `ac set ROUND_NO`
  
  1) 현재 위치를 `..../some_path/scripts`로 이동
  2) 스크립트 파일 `down`과 `s`의 Url을 지정한 라운드에 맞게 수정
  3) 환경변수 `TASK_NO`값을 'a'로 초기화
  4) 설정한 round의 첫번째 문제의 test case 다운로드

* `ac s [TASK_NO]`

  문제번호를 파라미터로 넘겨줄 시 스크립트 파일 `s`을 실행하는 것과 동일하며, 파라미터가 없을 경우 환경변수 `TASK_NO`의 현재값에 대응하는 문제번호에 제출을 시도합니다.

* `ac t`

  스크립트 파일 `t`를 실행하는 것과 동일합니다.

* `ac nxt`

  환경변수 `TASK_NO`에 저장되어 있는 문제번호를 다음 번호로 변경하고, 그에 해당하는 테스트케이스를 다운로드합니다.

* `ac down [TASK_NO]`

  문제번호를 파라미터로 넘겨줄 시 스크립트 파일 `down`을 실행하는 것과 동일하며, 파라미터가 없을 경우 환경변수 `TASK_NO`의 현재값에 대응하는 문제번호의 테스트케이스를 다운로드합니다.
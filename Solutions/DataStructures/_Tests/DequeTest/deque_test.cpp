#include <bits/stdc++.h>
using namespace std;

// 배열의 크기를 충분히 크게 잡아서 앞뒤로 데이터를 추가할 수 있게 함
const int MX = 1000005;
int dat[2 * MX + 1];
// head와 tail을 배열의 중간에서 시작하여 양쪽으로 확장 가능하게 함
int head = MX, tail = MX;

// push_front 함수에서 전위 감소 연산자(--head)를 사용해야 하는 이유:
// 1. 데크는 head가 첫 번째 원소를 가리키는 구조
// 2. 새 원소를 앞에 추가하려면 head를 먼저 감소시킨 후 그 위치에 값을 저장해야 함
// 3. head--를 사용하면 현재 위치에 값을 저장한 후 head가 감소되어 데이터가 잘못된 위치에 저장됨
//
// 예시:
// 초기 상태: [30][ ][ ]
//            h   t
// push_front(25) 실행 시:
// --head 사용: [25][30][ ]  (올바른 결과)
//              h   →  t
// head-- 사용: [?][25][30]  (잘못된 결과, 30을 25로 덮어쓰고 head가 감소)
//             h   →   t
void push_front(int x) {
  dat[--head] = x;  // 전위 감소로 먼저 head를 감소시킨 후 새 값을 저장
}

// tail이 가리키는 위치에 새 원소를 추가하고 tail을 증가
// 후위 증가를 사용해도 되는 이유: 현재 tail 위치는 비어있는 상태이기 때문
void push_back(int x) {
  dat[tail++] = x;
}

// head를 증가시켜서 첫 번째 원소를 제거하는 효과
void pop_front() {
  head++;
}

// tail을 감소시켜서 마지막 원소를 제거하는 효과
void pop_back() {
  tail--;
}

// head가 가리키는 위치의 원소(첫 번째 원소) 반환
int front() {
  return dat[head];
}

// tail 바로 이전 위치의 원소(마지막 원소) 반환
int back() {
  return dat[tail - 1];
}

void test() {
  push_back(30); // 30
  cout << front() << '\n'; // 30
  cout << back() << '\n'; // 30
  push_front(25); // 25 30
  push_back(12); // 25 30 12
  cout << back() << '\n'; // 12
  push_back(62); // 25 30 12 62
  pop_front(); // 30 12 62
  cout << front() << '\n'; // 30
  pop_front(); // 12 62
  cout << back() << '\n'; // 62
}

int main(void) {
  test();
}

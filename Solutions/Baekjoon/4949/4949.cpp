#include <bits/stdc++.h>

using namespace std;

/*
괄형잡힌 문자열 검사 알고리즘 원리:
- 목표: 괄호의 짝이 올바르게 매칭되는지 확인
- 사용 자료구조: 스택 (후입선출 LIFO 구조)

동작 과정:
1. 문자열 입력 처리
   - getline()으로 한 줄 전체를 입력받음
   - "." 입력 시 프로그램 종료

2. 괄호 검사 과정
   - 문자열의 각 문자를 순차적으로 확인
   - 여는 괄호 처리:
     * '[' 또는 '(' 를 만나면 스택에 push
   - 닫는 괄호 처리:
     * ']' 또는 ')' 를 만났을 때:
       → 스택이 비어있으면 실패 (짝이 없는 닫는 괄호)
       → 스택 top의 괄호와 짝이 맞지 않으면 실패
       → 짝이 맞으면 스택에서 pop

3. 최종 검사
   - 문자열 끝까지 검사 후 스택이 비어있지 않으면 실패
     (짝이 없는 여는 괄호가 남아있음)
   - 모든 조건을 통과하면 "yes" 출력, 실패하면 "no" 출력

예시:
"So when I die (the [first] death)" → "yes"
"([)]" → "no" (교차된 괄호는 잘못된 경우)
*/

/*GetLine function
1. string a;
   - 문자열을 저장할 변수 a를 선언

2. getline(cin, a);
   - getline() 함수는 한 줄 전체를 입력받는 함수
   - 엔터키(개행문자 \n)를 만날 때까지의 모든 문자를 읽어들임
   - cin >> 과의 차이점:
     * cin >>: 공백(' ')을 만나면 입력을 중단
     * getline(): 공백도 포함하여 개행문자 전까지 모든 문자를 읽음

3. if (a == ".") break;
   - 입력된 문자열이 단순히 마침표(".")인 경우 프로그램 종료
   - 문제의 입력 종료 조건

예시 입력:
"So when I die (the [first] death), I am just going to be invisible."
- 위 문장 전체가 공백을 포함하여 변수 a에 저장됨
*/

int main() {
    ios::sync_with_stdio(0);
    cin.tie();

    while (true) {
        string a;

        getline(cin, a);
        if (a == ".") break;
        stack<char> s;
        bool isValid = true;
        for (auto c : a) {
            if (c == '[' || c == '(') s.push(c);
            else if (c == ')') {
                if (s.empty() || s.top() != '(') {
                    isValid = false;
                    break;
                }
                s.pop();
            }
            else if (c == ']') {
                if (s.empty() || s.top() != '[') {
                    isValid = false;
                    break;
                }
                s.pop();
            }
        }
        if (!s.empty()) isValid = false;
        if (isValid) cout << "yes\n";
        else cout << "no\n";
    }
}
#include <bits/stdc++.h>

#define X first;
#define Y second;

using namespace std;

// dist 배열: 각 위치까지 도달하는데 걸리는 최소 시간을 저장
// 배열 크기가 100002인 이유: 문제의 제한 조건이 0 ≤ N, K ≤ 100,000이므로, 여유있게 설정
int dist[100002];
int n, k;  // n: 수빈이의 시작 위치, k: 동생의 위치

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0);

    // 시작 위치(n)와 목표 위치(k) 입력 받기
    cin >> n >> k;

    // dist 배열을 -1로 초기화
    // -1은 아직 방문하지 않은 위치를 의미
    fill(dist, dist + 100001, -1);

    // 시작 위치의 소요 시간을 0으로 설정
    dist[n] = 0;

    // BFS를 위한 큐 생성 및 시작 위치 삽입
    queue<int> Q;
    Q.push(n);

    // 동생을 찾을 때까지(k 위치의 거리가 계산될 때까지) BFS 실행
    while (dist[k] == -1) {
        // 현재 위치를 큐에서 추출
        int cur = Q.front(); Q.pop();

        // 현재 위치에서 가능한 3가지 이동 방법을 순회
        // 1. cur-1: 한 칸 뒤로 이동
        // 2. cur+1: 한 칸 앞으로 이동
        // 3. 2*cur: 순간이동 (현재 위치의 2배)
        for (int nxt : {cur - 1, cur + 1, 2 * cur}) {
            // 범위를 벗어나는 경우 스킵
            if (nxt < 0 || nxt > 100000) continue;
            // 이미 방문한 위치인 경우 스킵
            if (dist[nxt] != -1) continue;

            // 다음 위치까지의 소요 시간 = 현재 위치 소요 시간 + 1
            dist[nxt] = dist[cur] + 1;
            // 다음 위치를 큐에 삽입하여 나중에 탐색
            Q.push(nxt);
        }
    }

    // 동생의 위치(k)까지 도달하는데 걸리는 최소 시간 출력
    cout << dist[k];
}
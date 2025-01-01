#include <bits/stdc++.h>

using namespace std;
int main() {
    ios::sync_with_stdio(0);
    cin.tie();
    int n;
    cin >> n;
    queue<int> q;
    while (n--) {
        string op;
        int c;
        cin >> op, c;
        if (op == "push") {
            cin >> c;
            q.push(c);
        }
        if (op == "pop") {
            if (q.empty()) {
                cout << -1 << "\n";
            }
            else {
                cout << q.front() << "\n";
                q.pop();
            }
        }
        if (op == "size") {
            cout << q.size() << "\n";
        }
        if (op == "empty") {
            if (q.empty())
                cout << 1 << "\n";
            else
                cout << 0 << "\n";
        }
        if (op == "front") {
            if (q.empty())
                cout << "-1" << "\n";
            else
                cout << q.front() << "\n";
        }
        if (op == "back") {
            if (q.empty())
                cout << "-1" << "\n";
            else
                cout << q.back() << "\n";
        }

    }
}
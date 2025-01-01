#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;

    stack<int> s;

    while (n >= 0) {
        string c;
        cin >> c;
        if (c == "push") {
            int t;
            cin >> t;
            s.push(t);
        }
        else if (c == "pop") {
            if (s.empty())
                cout << -1 << '\n';
            else {
                cout << s.top() << '\n';
                s.pop();
            }
        }
        else if (c == "size") {
            cout << s.size() << '\n';
        }
        else if (c == "empty") {
            if (s.empty())
                cout << 1 << '\n';
            else
                cout << 0 << '\n';
        }
        else if (c == "top") {
            if (s.empty())
                cout << -1 << '\n';
            else
                cout << s.top() << '\n';
        }
        n--;
    }
}
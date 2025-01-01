#include <bits/stdc++.h>

using namespace std;

void sol(int num, int weight) {
    int maxValue = 0;

    vector<int> dp(weight + 1, 0);

    vector<pair<int, int>> items(num);

    for (int i = 0; i < num; i++) {
        int w, v;
        cin >> w >> v;
        items[i].first = w;
        items[i].second = v;
    }

    for (int i = 0; i < num - 1; i++) {
        pair<int, int> temp = items[i];
        if (items[i].first > items[i + 1].first) {
            items[i] = items[i + 1];
            items[i + 1] = temp;
        }
    }

    for (int i = 0; i < items.size(); i++) {
        for (int j = weight; j >= items[i].first; j--) {
            dp[j] = std::max(dp[j], dp[j - items[i].first] + items[i].second);
        }
    }

    for (int i = 0; i <= weight; i++) {
        if (dp[i] > maxValue)
            maxValue = dp[i];
    }

    cout << maxValue;
}

int main() {
    int num;
    int weight;

    cin >> num >> weight;

    sol(num, weight);
}
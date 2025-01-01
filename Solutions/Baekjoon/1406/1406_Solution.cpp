#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    string chars;

    list<char> charInput;

    cin >> chars;

    for (auto c : chars)
    {
        charInput.push_back(c);
    }

    auto cursor = charInput.end();

    int commands;

    cin >> commands;

    while (commands--)
    {
        char op;

        cin >> op;

        if (op == 'P')
        {
            char inserts;

            cin >> inserts;

            charInput.insert(cursor, inserts);
        }
        else if (op == 'L')
        {
            if (cursor != charInput.begin())
            {
                cursor--;
            }
        }
        else if (op == 'D')
        {
            if (cursor != charInput.end())
            {
                cursor++;
            }
        }
        else if (op == 'B')
        {
            if (cursor != charInput.begin())
            {
                cursor--;
                cursor = charInput.erase(cursor);
            }
        }
    }

    for (auto c : charInput)
    {
        cout << c;
    }
    cout << '\n';

    return 0;
}
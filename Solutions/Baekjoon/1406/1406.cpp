#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    string chars;

    // input 받을 list6
    list<char> charInput;

    // 수정할 char들을 입력
    cin >> chars;

    // 입력받은 string을 charinput 리스트에 주입
    for (auto c : chars)
    {
        charInput.push_back(c);
    }

    // Cursor : input List 의 0번째 혹은 input 리스트로 입력받은 char 의 마지막 인덱스 +1 (맨 끝) 이나 중간 어느곳이나 존재할수 있음
    // std::list<char>::iterator cursor = charInput.end(); = 마지막 요소 다음의 빈 위치를 가리키는  iterator
    auto cursor = charInput.end();

    int commands;

    // 명령어의 갯수를 입력
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
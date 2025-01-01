// http://boj.kr/ece8236c02cf46aba9933f28e358b51c
#include <iostream>

using namespace std;

void Ans1()
{
	cin.tie(0);
	string s;
	cin >> s;
	for (char a = 'a'; a <= 'z'; a++)
	{
		int cnt = 0;
		for (char c : s)
			if (a == c)
				cnt++;
		cout << cnt << ' ';
	}
}

void getAlphabets(int res[])
{
	int i = 0;
	string s;
	cin >> s;
	for (char a = 'a'; a <= 'z'; a++)
	{
		int cnt = 0;
		for (char c : s)
		{
			if (a == c)
			{
				cnt++;
			}
		}
		res[i] = cnt;
		i++;
	}
}

int main(void)
{
	int res[26];
	getAlphabets(res);
	for (int i = 0; i < 26; i++)
	{
		cout << res[i] << ' ';
	}
}

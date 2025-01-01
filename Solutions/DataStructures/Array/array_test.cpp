#include <bits/stdc++.h>
using namespace std;
/*
* int* arrTo = (int*)malloc(sizeof(int) * 5);
* * = 8 Byte;
* struct char , int (byte)
* byte padding
* int* arr == int arr[5]
* [ int | int | int | int | int ]
* void*
*/

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


void insert(int idx, int num, int arr[], int& len) { 
	/*
	* arr = {10 , 20 , 30 , 40}
	* idx 가 1이고 , len이 4일때
	* for 문 진입  : i = 4 , idx = 1;
	* 첫번째 반복
	* 배열에 5번째 있는 요소에 하나 전에 있는 요소를 대입
	* {10,20,30,40,40}
	* i-- => i = 3
	* {10,20,30,30,40}
	* i-- => i = 2
	* {10,20,20,30,40}
	* i-- => i = 1 탈출
	* arr[1] 번째에 num 을 대입
	* {10,50,20,30,40}
	* int arr[5] = {};
	* arr[0] += size(int) * idx
	* arr[5]
	*/
	for (int i = len; i > idx; i--) 
	{
		arr[i] = arr[i - 1];
	}		
	arr[idx] = num;

	len++;
}

void erase(int idx, int arr[], int& len){
	/*
	* arr = {10, 50, 40, 30, 70, 20 , _};
	* len = 6;
	* idx = 4
	* arr[4] = 70 에 arr[6] = _ 을 대입
	* arr = {10,50,40,30,_,20,_}
	* i = 5
	* 첫번째 반복
	* arr[4] = _ 에 arr[5] = 20 을 대입
	* 두번쨰 sol
	* {10,50,40,30,20,_}
	* len = 5
	* idx = 1 
	* arr[1] = 50 에 arr[len] = _ 을 대입
	* {10,_,40,30,20,_}
	*/
	arr[idx] = arr[len];
	for (int i = idx; i < len - 1; i++)
	{
		arr[i] = arr[i + 1];
	}
	len--;
}



void printArr(int arr[], int& len){
  for(int i = 0; i < len; i++) cout << arr[i] << ' ';
  cout << "\n\n";
}

void insert_test(){
  cout << "***** insert_test *****\n";
  int arr[10] = {10, 20, 30};
  int len = 3;
  insert(3, 40, arr, len); // 10 20 30 40
  printArr(arr, len);
  insert(1, 50, arr, len); // 10 50 20 30 40
  printArr(arr, len);
  insert(0, 15, arr, len); // 15 10 50 20 30 40
  printArr(arr, len);
}

void erase_test(){
  cout << "***** erase_test *****\n";
  int arr[10] = {10, 50, 40, 30, 70, 20};
  int len = 6;
  erase(4, &arr[2], len); // 10 50 40 30 20
  printArr(arr, len);
  erase(1, arr, len); // 10 40 30 20
  printArr(arr, len);
  erase(3, arr, len); // 10 40 30
  printArr(arr, len);
}

int main(void) 
{
	int res[26]; 
	getAlphabets(res);
	for (int i = 0; i < 26; i++)
	{
		cout << res[i] << ' ';
	}
	return 0;
}


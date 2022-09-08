#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main(){
  int M = 1;
  vector<int> A = {0};
  string S;
  getline(cin, S);
  if (S == "#") break;
  for (char c : S){
    if (!isdigit(c) && !isalpha(c)){
      A.push_back(0);
    } else if (isdigit(c)){
      A.back() *= 10;
      A.back() += c - '0';
    } else {
      int l = c - 'a' + 1;
      A.pop_back();
      for (int i = 0; i < (1 << l); i++){
        A.push_back(__builtin_popcount(i));
      }
    }
  }
  int n = 4;
  int N = A.size();
  cout << "a = [";
  for (int i = 0; i < N; i++){
    cout << A[i];
    if (i < N - 1){
      cout << ',';
    }
  }
  cout << "]" << endl;
  cout << "k = " << N << endl;
  if (A[N - 1] == 0){
    cout << "Rule 1" << endl;
    cout << "a = [";
    for (int i = 0; i < N - 1; i++){
      cout << A[i];
      if (i < N - 2){
        cout << ',';
      }
    }
    cout << "]" << endl;
  } else {
    cout << "Rule 2" << endl;
    int D = max(A[N - 1] - A[N - 2], -M);
    int r = 0;
    for (int i = N - 1; i >= 1; i--){
      if (A[i] < A[N - 1] && A[i] - A[i - 1] < D){
        r = i;
        break;
      }
    }
    cout << "i = " << r + 1 << ", a_i = " << A[r] << endl;
    int d = A[N - 1] - A[r] - 1;
    cout << "Delta = " << d << endl;
    cout << "A = [";
    for (int i = 0; i < r; i++){
      cout << A[i];
      if (i < r - 1){
        cout << ',';
      }
    }
    cout << "]" << endl;
    cout << "B_0 = [";
    for (int i = r; i < N - 1; i++){
      cout << A[i];
      if (i < N - 2){
        cout << ',';
      }
    }
    cout << "]" << endl;
    vector<int> A2;
    for (int i = 0; i < r; i++){
      A2.push_back(A[i]);
    }
    for (int i = 0; i <= n; i++){
      for (int j = r; j < N - 1; j++){
        A2.push_back(A[j] + d * i);
      }
    }
    int N2 = A2.size();
    cout << "a = [";
    for (int i = 0; i < N2; i++){
      cout << A2[i];
      if (i < N2 - 1){
        cout << ',';
      }
    }
    cout << "]" << endl;
  }
}

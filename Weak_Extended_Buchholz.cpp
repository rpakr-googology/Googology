#include <iostream>
#include <string>
using namespace std;
string get(string S, int &p){
  if (S[p] == '0'){
    p++;
    return "0";
  }
  string res;
  res += S[p];
  p++;
  res += get(S, p);
  res += S[p];
  p++;
  res += get(S, p);
  res += S[p];
  p++;
  return res;
}
pair<string, string> parse(string S){
  int N = S.size();
  int p = 1;
  string a = get(S, p);
  p++;
  string b = get(S, p);
  return make_pair(a, b);
}
string psi(string alpha, string beta){
  return "(" + alpha + "," + beta + ")";
}
string zero = "0";
string one = psi(zero, zero);
string omega = psi(zero, psi(one, zero));
bool operator <(string alpha, string beta){
  if (beta == zero){
    return false;
  } else if (alpha == zero){
    return true;
  } else {
    pair<string, string> A = parse(alpha);
    pair<string, string> B = parse(beta);
    if (A.first == B.first){
      return A.second < B.second;
    } else {
      return A.first < B.first;
    }
  }
}
string dom(string alpha){
  if (alpha == zero){
    return alpha;
  }
  string beta = parse(alpha).first;
  string gamma = parse(alpha).second;
  if (dom(gamma) == zero){
    if (dom(beta) < omega){
      return alpha;
    } else {
      return dom(beta);
    }
  }
  if (omega < dom(gamma) && alpha < dom(gamma)){
    return omega;
  }
  return dom(gamma);
}
string fs(string alpha, string eta){
  string beta = parse(alpha).first;
  string gamma = parse(alpha).second;
  if (dom(gamma) == zero){
    if (dom(beta) < omega){
      return eta;
    }
    return psi(fs(beta, eta), zero);
  }
  if (dom(gamma) == one){
    return psi(beta, fs(gamma, zero));
  }
  if (omega < dom(gamma) && alpha < dom(gamma)){
    string delta = fs(parse(dom(gamma)).first, zero);
    string epsilon;
    if (eta == zero){
      epsilon = zero;
    }
    if (eta != zero){
      epsilon = parse(fs(alpha, fs(eta, zero))).second;
    }
    return psi(beta, fs(gamma, psi(delta, epsilon)));
  }
  return psi(beta, fs(gamma, zero));
}
int main(){
  while (true){
    string t;
    cin >> t;
    if (t == "EXIT"){
      break;
    }
    if (t == "COMP"){
      string x, y;
      cin >> x >> y;
      if (x == y){
        cout << x << "=" << y << endl;
      } else if (x < y){
        cout << x << "<" << y << endl;
      } else {
        cout << y << "<" << x << endl;
      }
    }
    if (t == "DOM"){
      string x;
      cin >> x;
      cout << "dom(" << x << ")=" << dom(x) << endl;
    }
    if (t == "[]"){
      string x, y;
      cin >> x >> y;
      cout << x << "[" << y << "]=" << fs(x, y) << endl;
    }
    cout << endl;
  }
}

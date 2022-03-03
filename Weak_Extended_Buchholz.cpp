#include <iostream>
#include <string>
#include <map>
#include <utility>
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
  return psi(beta, fs(gamma, eta));
}
map<string, string> sugar_list;
map<string, string> desugar_list;
string sugar(string s){
  while (true){
    int N = s.size();
    bool ok = true;
    for (int i = 0; i < N; i++){
      for (int j = i + 1; j <= N; j++){
        if (desugar_list.count(s.substr(i, j - i))){
          string t = desugar_list[s.substr(i, j - i)];
          s = s.substr(0, i) + t + s.substr(j);
          ok = false;
          goto A;
        }
      }
    }
    A:
    if (ok){
      break;
    }
  }
  return s;
}
string desugar(string s){
  while (true){
    int N = s.size();
    bool ok = true;
    for (int i = 0; i < N; i++){
      for (int j = i + 1; j <= N; j++){
        if (sugar_list.count(s.substr(i, j - i))){
          string t = sugar_list[s.substr(i, j - i)];
          s = s.substr(0, i) + t + s.substr(j);
          ok = false;
          goto A;
        }
      }
    }
    A:
    if (ok){
      break;
    }
  }
  return s;
}
int main(){
  while (true){
    string t;
    cin >> t;
    for (char &c : t){
      c = toupper(c);
    }
    if (t == "EXIT"){
      break;
    }
    if (t == "SUGAR"){
      for (auto P : sugar_list){
        cout << P.first << ' ' << P.second << endl;
      }
    }
    if (t == "DESUGAR"){
      string x;
      cin >> x;
      cout << desugar(x) << endl;
    }
    if (t == "ADD-SUGAR"){
      string x, y;
      cin >> x >> y;
      sugar_list[y] = x;
      desugar_list[x] = y;
    }
    if (t == "COMP"){
      string x, y;
      cin >> x >> y;
      string x2 = desugar(x);
      string y2 = desugar(y);
      if (x2 == y2){
        cout << x << "=" << y << endl;
      } else if (x2 < y2){
        cout << x << "<" << y << endl;
      } else {
        cout << y << "<" << x << endl;
      }
    }
    if (t == "DOM"){
      string x;
      cin >> x;
      string x2 = desugar(x);
      cout << "dom(" << x << ")=" << sugar(dom(x2)) << endl;
    }
    if (t == "[]"){
      string x, y;
      cin >> x >> y;
      string x2 = desugar(x);
      string y2 = desugar(y);
      cout << x << "[" << y << "]=" << sugar(fs(x2, y2)) << endl;
    }
    if (t == "FS"){
      string x;
      cin >> x;
      string x2 = desugar(x);
      cout << "FS of " << x << ":" << endl;
      cout << sugar(fs(x2, zero)) << endl;
      cout << sugar(fs(x2, psi(zero, zero))) << endl;
      cout << sugar(fs(x2, psi(zero, psi(zero, zero)))) << endl;
      cout << sugar(fs(x2, psi(zero, psi(zero, psi(zero, zero))))) << endl;
    }
    cout << endl;
  }
}

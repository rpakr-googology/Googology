//New Side Nesting Notation
//Notation by p-bot
//Japanese definition: https://googology.wikia.org/ja/wiki/%E3%83%A6%E3%83%BC%E3%82%B6%E3%83%BC%E3%83%96%E3%83%AD%E3%82%B0:P%E9%80%B2%E5%A4%A7%E5%A5%BD%E3%81%8Dbot/Veblen%E9%96%A2%E6%95%B0%E3%81%AB%E4%BC%B4%E3%81%84%E3%81%9D%E3%81%86%E3%81%A7%E4%BC%B4%E3%82%8F%E3%81%AA%E3%81%84%E9%A0%86%E5%BA%8F%E6%95%B0%E8%A1%A8%E8%A8%98
//English definition: https://googology.wikia.org/wiki/User_blog:P%E9%80%B2%E5%A4%A7%E5%A5%BD%E3%81%8Dbot/New_Side_Nesting_Notation
#include <bits/stdc++.h>
using namespace std;
string zero = "()";
string one = "(()()())";
int Compcalls = 0;
int OTcalls=0;
int R4=0;
int R5=0;
int R6=0;
int R7=0;
//0: No shorthands
//1: Use 0
//2: Use 0 and 1
//3: Use 0, 1 and ω
int sthd = 3;
string simplify(string s){
	string res = s;
	if (sthd == 0) return res;
	res = "";
	for (int i = 0; i < s.size(); i++){
		res += s[i];
		if (i > 0){
			if (s.substr(i - 1, 2) == "()"){
				for (int i = 0; i < 2; i++) res.pop_back();
			res += "0";
			}
		}
	}
	if (sthd == 1) return res;
	s = res;
	res = "";
	for (int i = 0; i < s.size(); i++){
		res += s[i];
		if (i > 3){
			if (s.substr(i - 4, 5) == "(000)"){
				for (int i = 0; i < 5; i++) res.pop_back();
				res += "1";
			}
		}
	}
	if (sthd == 2) return res;
	s = res;
	res = "";
	for (int i = 0; i < s.size(); i++){
		res += s[i];
		if (i > 3){
			if (s.substr(i - 4, 5) == "(001)"){
				for (int i = 0; i < 5; i++) res.pop_back();
				res += "ω";
			}
		}
	}
	if (sthd == 3) return res;
	return res;
}
int type(string s){
	int res = 1;
	int nests = 0;
	for (int i = 0; i < s.size(); i++){
		if (s[i] == '(') nests++;
		if (s[i] == ')') nests--;
		if (s[i] == '+' && nests == 0) res = 2;
	}
	return res;
}
string arg(string s, int n){
	string res;
	int argcount = 0;
	int nests = 0;
	if (type(s) == 1){
		for (int i = 0; i < s.size() - 1; i++){
			if (s[i] == '('){
				nests++;
				if (nests == 2 && s[i - 1] != '+') argcount++;
			}
			if (argcount == n) res += s[i];
			if (s[i] == ')') nests--;
		}
	} else {
		n--;
		for (int i = 0; i < s.size(); i++){
			if (s[i] == '+' && argcount == 0 && nests == 0){
				argcount++;
				continue;
			}
			if (argcount == n) res += s[i];
			if (s[i] == '(') nests++;
			if (s[i] == ')') nests--;
		}
	}
	return res;
}
bool isinT(string s){
	if (s == zero) return true;
	for (int i = 0; i < s.size(); i++){
		if (s[i] != '(' && s[i] != ')' && s[i] != '+') return false;
	}
	int nests = 0;
	for (int i = 0; i < s.size(); i++){
		if (s[i] == '(') nests++;
		if (s[i] == ')') nests--;
		if (nests < 0) return false;
	}
	if (nests != 0) return false;
	if (type(s) == 1){
		int argcount = 0;
		int nests = 0;
		for (int i = 0; i < s.size(); i++){
			if (s[i] == '('){
				nests++;
				if (nests == 2 && s[i - 1] != '+') argcount++;
			}
			if (s[i] == ')') nests--;
		}
		if (argcount != 3) return false;
		if (!isinT(arg(s,1))) return false;
		if (!isinT(arg(s,2))) return false;
		if (!isinT(arg(s,3))) return false;
		return true;
//		return isinT(arg(s,1)) && isinT(arg(s,2)) && isinT(arg(s,3));
	} else {
		if (arg(s,1) == zero || arg(s,2) == zero) return false;
		return isinT(arg(s,1)) && isinT(arg(s,2));
	}
}
bool isinPT(string s){
	return isinT(s) && type(s) == 1;
}
bool L(string s, string t);
bool leq(string s, string t){
	return (L(s,t) || s == t);
}
bool L(string s, string t){
	Compcalls++;
	if (s == zero) return t != zero;
	if (s != zero && t == zero) return false;
	string a = arg(s,1);
	string b = arg(s,2);
	string c = arg(s,3);
	string d = arg(t,1);
	string e = arg(t,2);
	string f = arg(t,3);
	if (type(s) == 1){
		if (type(t) == 1){
			R4++;
			if (a == d){
				if (b == e){
					return L(c,f);
				} else if (L(b,e)){
					return leq(c,t);
				} else {
					return L(s,f);
				}
			} else if (L(a,d)){
				return leq(c,t);
			} else {
				return L(s,f);
			}
		} else {
			R5++;
			return leq(s,d);
		}
	} else {
		if (type(t) == 1){
			R6++;
			return !L(t,s);
		} else {
			R7++;
			if (a == d){
				return L(b,e);
			} else {
				return L(a,d);
			}
		}
	}
}
string A(string a, string b){
	return a + '+' + b;
}
string P(string a, string b, string c){
	return '(' + a + b + c + ')';
}
string rev(string s){
	string res;
	for (int i = s.size() - 1; i >= 0; i--){
		res += s[i];
	}
	return res;
}
string mult(string a, string t){
	if (t == zero) return zero;
	if (type(t) == 1){
		string d = arg(t,1);
		string e = arg(t,2);
		string f = arg(t,3);
		if (leq(P(zero,zero,P(zero,zero,A(P(a,zero,zero),one))),t)){
			return t;
		}
		if (t == one){
			return P(a,zero,zero);
		}
		if (d == zero && e == zero && t != one){
			return P(zero,zero,A(P(a,zero,zero),f));
		}
		if (d == zero && e != zero){
			return P(zero,zero,A(P(a,zero,zero),t));
		}
		return P(zero,zero,A(P(a,zero,zero),t));
	} else {
		string d = rev(arg(rev(t),2));
		string e = rev(arg(rev(t),1));
		return A(mult(a,d),mult(a,e));
	}
}
bool isinOT(string S, string x){
	OTcalls++;
	if (S == zero) return true;
	if (type(S) == 1){
		string a = arg(S,1);
		string b = arg(S,2);
		string c = arg(S,3);
		if (!isinOT(a,x)) return false;
		if (!isinOT(b,x)) return false;
		if (!isinOT(c,x)) return false;
		if (a == zero){
			if (!leq(mult(one,b),x)) return false;
			if (!isinOT(b,mult(one,b))) return false;
		} else {
			if (!leq(mult(A(a,one),b),x)) return false;
			if (!isinOT(b,mult(A(a,one),b))) return false;
		}
		if (!L(c,S)) return false;
	} else {
		string s = rev(arg(rev(S),2));
		string t = rev(arg(rev(S),1));
		if (!isinOT(s,x)) return false;
		if (!isinOT(t,x)) return false;
		if (isinPT(s)){
			if (!leq(t,s)) return false;
		}
		if (type(s) == 2){
			string b = rev(arg(rev(s),1));
			if (!leq(t,b)) return false;
		}
	}
	return true;
}
bool isstd(string s){
	return isinT(s) && isinOT(s,s);
}
void FS(string s, int n){
	if (s == zero){
		for (int i = 0; i <= n; i++){
			cout << simplify(s) << "[" << i << "]=" << simplify(zero) << endl;
		}
		return;
	}
	string res = zero;
	vector<set<string>> exp((s.size() + 9 * n + 1) / 3);
	//strings in exp[n] has 3n+2 chars
	for (int i = 0; i < exp.size(); i++){
		if (i == 0) exp[i].insert(zero);
		for (int a = 0; a < i - 1; a++){
			for (int b = 0; b < i - 1 - a; b++){
				int c = i - 2 - a - b;
				for (string s1 : exp[a]){
					for (string s2 : exp[b]){
						if (s1 == zero){
							if (L(s,mult(one,s2))) continue;
						} else {
							if (L(s,mult(A(s1,one),s2))) continue;
						}
						for (string s3 : exp[c]){
							string S = P(s1,s2,s3);
							if (!L(s3,S)) continue;
							exp[i].insert(S);
if (i==19 && exp[i].size()%1000==0) cout << exp[i].size() << endl;
						}
					}
				}
			}
		}
		for (int a = 1; a < i - 1; a++){
			int b = i - 1 - a;
			for (string s1 : exp[a]){
				if (!isinPT(s1)) continue;
				for (string s2 : exp[b]){
					//s2+s1
					if (isinPT(s2)){
						if (!leq(s1,s2)) continue;
					}
					string S = A(s2,s1);
					if (type(s1) == 2){
						string b = rev(arg(rev(s1),1));
						if (!leq(s2,b)) continue; 
					}
					exp[i].insert(S);
if (i==19 && exp[i].size()%1000==0) cout << exp[i].size() << endl;
				}
			}
		}
		for (string t : exp[i]){
			if (L(t,s)){
				if (L(res,t)){
				if (isstd(t)) res = t;
				}
			}
		}
		cout << simplify(res) << endl;
		/*
		cout << 3*i+2 << ":" << exp[i].size() << endl;
		cout << "Comparison calls: " << Compcalls << endl;
		cout << "Rule 4: "<< R4 << "," << (double)R4/Compcalls << endl;
		cout << "Rule 5: "<< R5 << "," << (double)R5/Compcalls << endl;
		cout << "Rule 6: "<< R6 << "," << (double)R6/Compcalls << endl;
		cout << "Rule 7: "<< R7 << "," << (double)R7/Compcalls << endl;
		cout << "OT calls: " << OTcalls << endl;
		cout << endl;
		*/
	}
}
int main(){
	string S,T;
	cin >> S;
	for (int i = 0; i < S.size(); i++){
		T += S[i];
		if (S[i] == '0'){
			T.pop_back();
			T += zero;
		}
		if (S[i] == '1'){
			T.pop_back();
			T += one;
		}
		if (S[i] == '2'){
			T.pop_back();
			T += "(()()())+(()()())";
		}
	}
	S = T;
	if (!isinT(S)){
		cout << simplify(S) << " is not valid" << endl;
	} else {
		if (!isstd(S)){
			cout << simplify(S) << " is not standard" << endl;
		} else {
			FS(S,5);
		}
	}
}

//New Side Nesting Notation
//Notation by p-bot
//Japanese definition: https://googology.wikia.org/ja/wiki/%E3%83%A6%E3%83%BC%E3%82%B6%E3%83%BC%E3%83%96%E3%83%AD%E3%82%B0:P%E9%80%B2%E5%A4%A7%E5%A5%BD%E3%81%8Dbot/Veblen%E9%96%A2%E6%95%B0%E3%81%AB%E4%BC%B4%E3%81%84%E3%81%9D%E3%81%86%E3%81%A7%E4%BC%B4%E3%82%8F%E3%81%AA%E3%81%84%E9%A0%86%E5%BA%8F%E6%95%B0%E8%A1%A8%E8%A8%98
//English definition: https://googology.wikia.org/wiki/User_blog:P%E9%80%B2%E5%A4%A7%E5%A5%BD%E3%81%8Dbot/New_Side_Nesting_Notation
#include <bits/stdc++.h>
using namespace std;
string zero = "()";
string one = "(()()())";
//0: No shorthands
//1: Use 0
//2: Use 0 and 1
//3: Use 0, 1 and ω
int sthd = 3;
//0: No detailed output
//1: Detailed output in comparisons
//2: Detailed output in standardness
//3: Detailed output in fundamental sequences
int det = 3;
int spcs = 0;
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
void f(string s, int n){
	if (n == 2 && det == 2) for (int i = 0; i < spcs; i++) cout << ' ';
	if (n == det) cout << simplify(s) << endl;
}
void g(bool b, int n){
	if (n == det){
		if (b){
			cout << "true" << endl;
		} else {
			cout << "false" << endl;
		}
	}
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
		return isinT(arg(s,1)) && isinT(arg(s,2)) && isinT(arg(s,3));
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
//	f("Comparing s=" + s + ", t=" + t,1);
	if (s == zero) return t != zero;
	if (s != zero && t == zero) return false;
	string a = arg(s,1);
	string b = arg(s,2);
	string c = arg(s,3);
	string d = arg(t,1);
	string e = arg(t,2);
	string f = arg(t,3);
	bool res;
	if (type(s) == 1){
		if (type(t) == 1){
//			f("Rule 4",1);
			if (a == d){
				res = L(b,e) && leq(c,t) || b == e && L(c,f);
//				g(res,1);
			} else {
				res = L(a,d) && leq(c,t) || L(d,a) && L(s,f);
//				g(res,1);
			}
		} else {
//			f("Rule 5",1);
			res = leq(s,d);
//			g(res,1);
		}
	} else {
		if (type(t) == 1){
//			f("Rule 6",1);
			res = !L(t,s);
//			g(res,1);
		} else {
//			f("Rule 7",1);
			res = L(a,d) || a == d && L(b,e);
//			g(res,1);
		}
	}
	return res;
}
string A(string a, string b){
	return a + '+' + b;
}
string B(string a, string b, string c){
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
		if (leq(B(zero,zero,B(zero,zero,A(B(a,zero,zero),one))),t)){
			return t;
		}
		if (t == one){
			return B(a,zero,zero);
		}
		if (d == zero && e == zero && t != one){
			return B(zero,zero,A(B(a,zero,zero),f));
		}
		if (d == zero && e != zero){
			return B(zero,zero,A(B(a,zero,zero),t));
		}
		return B(zero,zero,A(B(a,zero,zero),t));
	} else {
		string d = rev(arg(rev(t),2));
		string e = rev(arg(rev(t),1));
		return A(mult(a,d),mult(a,e));
	}
}
bool isinOT(string S, string x){
	spcs++;
	f("S=" + S,2);
	f("x=" + x,2);
	if (S == zero){
		spcs--;
		return true;
	}
	if (type(S) == 1){
		f("Rule 2",2);
		string a = arg(S,1);
		string b = arg(S,2);
		string c = arg(S,3);
		f("Rule 2.1 check 1/3",2);
		if (!isinOT(a,x)){
			spcs--;
			return false;
		}
		f("Rule 2.1 check 2/3",2);
		if (!isinOT(b,x)){
			spcs--;
			return false;
		}
		f("Rule 2.1 check 3/3",2);
		if (!isinOT(c,x)){
			spcs--;
			return false;
		}
		if (a == zero){
			f("Rule 2.2 check",2);
			f("mult(one,b)=" + mult(one,b),2);
			f("x=" + x,2);
			f("b=" + b,2);
			if (!leq(mult(one,b),x) || !isinOT(b,mult(one,b))){
				spcs--;
				return false;
			}
		} else {
			f("Rule 2.3 check",2);
			f("mult(A(a,one),b)=" + mult(A(a,one),b),2);
			f("x=" + x,2);
			f("b=" + b,2);
			if (!leq(mult(A(a,one),b),x) || !isinOT(b,mult(A(a,one),b))){
				spcs--;
				return false;
			}
		}
		f("Rule 2.4 check",2);
		f("c=" + c,2);
		f("S=" + S,2);
		if (!L(c,S)){
			spcs--;
			return false;
		}
	} else {
		f("Rule 3",2);
		string s = rev(arg(rev(S),2));
		string t = rev(arg(rev(S),1));
		f("Rule 3.1 check 1/2",2);
		if (!isinOT(s,x)){
			spcs--;
			return false;
		}
		f("Rule 3.1 check 2/2",2);
		if (!isinOT(t,x)){
			spcs--;
			return false;
		}
		if (isinPT(s)){
			f("Rule 3.2 check",2);
			f("t=" + t,2);
			f("s=" + s,2);
			if (!leq(t,s)){
				spcs--;
				return false;
			}
		}
		if (type(s) == 2){
			f("Rule 3.3 check",2);
			string a = rev(arg(rev(s),2));
			string b = rev(arg(rev(s),1));
			f("t=" + t,2);
			f("b=" + b,2);
			if (!leq(t,b)){
				spcs--;
				return false;
			}
		}
	}
	f("S=" + S + " is in OT_{x=" + x + "}",2);
	spcs--;
	return true;
}
bool isstd(string s){
	return isinT(s) && isinOT(s,s);
}
void FS(string s, int n){
	f("Computing the fundamental sequence of " + s,3);
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
						for (string s3 : exp[c]){
							string S = B(s1,s2,s3);
							if (!L(s3,S)) continue;
							exp[i].insert(S);
						}
					}
				}
			}
		}
		for (int a = 1; a < i - 1; a++){
			int b = i - 1 - a;
			for (string s1 : exp[a]){
				for (string s2 : exp[b]){
					string S = A(s1,s2);
					string S1 = rev(arg(rev(S),2));
					string S2 = rev(arg(rev(S),1));
					if (isinPT(S1) && !leq(S2,S1)) continue;
					if (type(S1) == 2){
						string b = rev(arg(rev(S1),1));
						if (!leq(S2,b)) continue; 
					}
					exp[i].insert(S);
				}
			}
		}
		for (string t : exp[i]){
			if (L(res,t) && L(t,s)){
				if (isstd(t)){
					f(t + " is std",3);
					res = t;
					f("res=" + res,3);
				} else {
					f(t + " is not std",3);
				}
			}
		}
		if ((3 * i + 2 - s.size()) % 9 == 0 && 3 * i + 2 > s.size()){
			cout << simplify(s) << "[" << (3 * i + 2 - s.size()) / 9 << "]=" << simplify(res) << endl;
		}
	}
}
int main(){
	/*
	string S;
	cin >> S;
	if (!isinT(S)){
		cout << simplify(S) << " is not valid" << endl;
	} else {
		if (!isstd(S)){
			cout << simplify(S) << " is not standard" << endl;
		} else {
			cout << simplify(S) << " is standard" << endl;
		}
	}
	*/
	/*
	string S;
	cin >> S;
	if (!isinT(S)){
		cout << simplify(S) << " is not valid" << endl;
	} else {
		if (!isstd(S)){
			cout << simplify(S) << " is not standard" << endl;
		} else {
			FS(S,5);
		}
	}
	*/
}

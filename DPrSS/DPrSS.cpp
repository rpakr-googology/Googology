//DPrSS expansion
#include <bits/stdc++.h>
using namespace std;
int main() {
	string str;
	cin >> str;
	vector<int> seq;
	//Initializing sequence
	seq.clear();
	//Reading input
	char c = str[1];
	bool valid = true;
	if (str.front() != '('){
		valid = false;
	}
	if (str.back() != ']'){
		valid = false;
	}
	int k = 0;
	int cchar;
	for (cchar = 1; cchar <= str.size() - 1 && (str[cchar] != ')'); cchar++){
		c = str[cchar];
		if (isdigit(c)){
			if (k == seq.size()){
				seq.push_back(c - '0');
			} else {
				seq[seq.size() - 1] = seq.back() * 10 + (c - '0');
			}
		} else if (c == ','){
			k++;
			if (!isdigit(str[cchar + 1])){
				valid = false;
			}
			if (!isdigit(str[cchar - 1])){
				valid = false;
			}
		} else {
			valid = false;
		}
	}
	if (cchar >= str.size() - 2){
		valid = false;
	}
	int bracket;
	if (str[cchar + 1] != '['){
		valid = false;
	} else {
		for (cchar = cchar + 2; cchar <= str.size() - 2; cchar++){
			c = str[cchar];
			if (isdigit(c)){
				if (str[cchar - 1] == '['){
					bracket = c - '0';
				} else {
					bracket = bracket * 10 + (c - '0');
				}
			} else {
				valid = false;
			}
		}
	}
	if (!valid){
		cout << "Sequence invalid" << endl;
	} else {
		if (str[1] == ')'){
			//Rule 1
			cout << bracket << endl;
		} else {
			k++;
			bool flg = true;
			for (int i = 0; i < k - 1; i++){
				if (seq[i] < seq[k - 1]){
					flg = false;
				}
			}
			if (flg){
				//Rule 2
				if (str[2] == ')'){
					cout << "()[" << bracket + 1 << "]" << endl;
				} else {
					cout << '(';
					for (int i = 0; i < k - 2; i++){
						cout << seq[i] << ',';
						}
					cout << seq[k - 2] << ')';
					cout << '[' << bracket + 1 << ']' << endl;
				}
			} else {
				//Rule 3,4,5
				vector<int> p(k,-1);
				for (int i = 0; i < k; i++){
					for (int j = i - 1; j >= 0; j--){
						if (seq[j] < seq[i]){
							p[i] = j;
							break;
						}
					}
				}
				vector<int> n(k,1);
				for (int i = 0; i < k; i++){
					if (p[i] != -1) n[i] = seq[i] - seq[p[i]];
				}
				if (n[k - 1] == 1){
					//Rule 3
					int length = k;
					seq.pop_back();
					length--;
					for (int rept = 0; rept < bracket - 1; rept++){
						for (int i = p[k - 1]; i < k; i++){
							seq.push_back(seq[i]);
							length++;
						}
					}
					//Output
					cout << '(';
					for (int i = 0; i < length - 1; i++){
						cout << seq[i] << ',';
					}
					cout << seq[length - 1] << ')';
					cout << '[' << bracket << ']' << endl;
				} else {
					//r search
					int r = k;
					while (n[r] >= n[k - 1]){
						r = p[r];
					}
					//r2 search
					int r2 = r;
					int i;
					seq.push_back(0);
					bool flg = false;
					while (true){
						r2 = p[r2];
						if (r2 == -1){
							flg = true;
							break;
						}
						if (n[r2] < n[k - 1]){
							i = 0;
							while (seq[r2 + i] - seq[r2] == seq[r + i] - seq[r]){
								i++;
							}
							if (seq[r2 + i] - seq[r2] < seq[r + i] - seq[r]){
								break;
							}
						}
					}
					if (flg){
						cout << "Expansion undefined" << endl;
					} else {
						//Rule 4 check
						flg = true;
						if (r + i != k) flg = false;
						if (seq[r2 + i] - seq[r2] != seq[r + i] - seq[r] - 1) flg = false;
						for (int j = r2 + i + 1; j < k; j++){
							if (seq[j] <= seq[r2 + i]) flg = false;
						}
						if (flg){
							//Expansion
							int length = k;
							int delta = seq[r] - seq[r2];
							for (int j = k; j > r; j--){
								seq.pop_back();
								length--;
							}
							for (int rept = 0; rept < bracket - 1; rept++){
								for (int j = r2; j < r; j++){
									seq.push_back(seq[j] + delta * (rept + 1));
									length++;
								}
							}
							//Output
							cout << '(';
							for (int j = 0; j < length - 1; j++){
								cout << seq[j] << ',';
							}
							cout << seq[length - 1] << ')';
							cout << '[' << bracket << ']' << endl;
						} else {
							//r3 search
							int r3 = r2;
							flg = false;
							while (1){
								for (int j = k; j > r3; j--){
									if (p[j] == r3){
										if (n[j] < n[k]){
											flg = true;
										} else {
											r3 = j;
										}
										break;
									}
								}
								if (flg) break;
							}
							for (int j = r3; j < k; j++){
								if (p[j] == r3 && n[j] < n[k]){
									r3 = j;
									break;
								}
							}
							//Expansion
							int delta = seq[k] - seq[r3] - 1;
							int length = k;
							seq.pop_back();
							length--;
							for (int rept = 0; rept < bracket - 1; rept++){
								for (int j = r3; j < k; j++){
									seq.push_back(seq[j] + delta * (rept + 1));
									length++;
								}
							}
							for (int j = 0; j < k - r; j++){
								seq.pop_back();
								length--;
							}
							//Output
							cout << "(";
							for (int j = 0; j < length - 1; j++){
								cout << seq[j] << ',';
							}
							cout << seq[length - 1] << ')';
							cout << '[' << bracket << ']' << endl;
						}
					}
				}
			}
		}
	}
	return 0;
}

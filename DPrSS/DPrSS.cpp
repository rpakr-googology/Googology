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
	if (str[1] != ')'){
		if (seq[0] != 1){
			valid = false;
		}
	}
	for (int i = 0; i <= k - 1; i++){
		if (seq[i] < seq[0]){
			valid = false;
		}
	}
	if (valid){
		if (str[1] == ')'){
			//Base case
			cout << bracket << endl;
		} else if (seq.back() == 1){
			//Successor case
			if (str[2] == ')'){
				cout << "()[" << bracket + 1 << "]" << endl;
			} else {
				cout << '(';
				for (int i = 0; i <= k - 2; i++){
					cout << seq[i] << ',';
				}
				cout << seq[k - 1] << ')';
				cout << '[' << bracket + 1 << ']' << endl;
			}
		} else {
			//Limit case
			//Parent search
			int r;
			for (int i = k; i >= 0; i--){
				r = i;
				if (seq[i] < seq.back()){
					break;
				}
			}
			int length = k;
			if (seq.back() - seq[r] == 1){
				//Constant case
				seq.pop_back();
				length--;
				for (int rept = 0; rept < bracket - 1; rept++){
					for (int i = r; i < k; i++){
						seq.push_back(seq[i]);
						length++;
					}
				}
				//Output
				cout << '(';
				for (int i = 0; i < length ; i++){
					cout << seq[i] << ',';
				}
				cout << seq[length] << ')';
				cout << '[' << bracket << ']' << endl;
			} else {
				//Parent search
				int p[k + 1];
				p[0] = -1;
				for (int i = 1; i <= k; i++){
					if (seq[i] == 1){
						p[i] = -1;
					} else {
						for (int j = i; j >= 0; j--){
							p[i] = j;
							if (seq[j] < seq[i]){
								break;
							}
						}
					}
				}
				//Find node value
				int n[k + 2];
				for (int i = 0; i <= k; i++){
					if (seq[i] == 1){
						n[i] = 1;
					} else {
						n[i] = seq[i] - seq[p[i]];
					}
				}
				n[k + 1] = 0;
				//BR search 1
				r = k;
				while (n[r] == 2){
					r = p[r];
				}
				//BR search 2
				int r2 = r;
				int i;
				seq.push_back(0);
				while (r2 >= 0){
					r2 = p[r2];
					if (n[r2] == 1){
						i = 0;
						while (seq[r2 + i] - seq[r2] == seq[r + i] - seq[r]){
							i++;
						}
						if (seq[r2 + i] - seq[r2] < seq[r + i] - seq[r]){
							break;
						}
					}
				}
				seq.pop_back();
				//Adding rule check
				bool LC = true;
				if (r + i != k) LC = false;
				if (seq[r2 + i] - seq[r2] != seq[r + i] - seq[r] - 1) LC = false;
				for (int j = r2 + i + 1; j < k; j++){
				    if (seq[j] <= seq[r2 + i]) LC = false;
				}
				if (LC){
					//Expansion
					int delta = seq[r] - seq[r2];
					for (int j = k; j >= r; j--){
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
					for (int j = 0; j < length; j++){
						cout << seq[j] << ',';
					}
					cout << seq[length] << ')';
					cout << '[' << bracket << ']' << endl;
				} else {
					//Bad root search
					int r3 = r;
					for (int j = r2; j < k; j++){
						if (p[j] == p[r] && seq[j] == seq[p[j]] + 1){
							r3 = j;
							break;
						}
					}
					//Expansion
					int delta = seq[k] - seq[r3] - 1;
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
					for (int j = 0; j < length; j++){
						cout << seq[j] << ',';
					}
					cout << seq[length] << ')';
					cout << '[' << bracket << ']' << endl;
				}
			}
		}
	} else {
		cout << "Sequence invalid" << endl;
	}
	return 0;
}

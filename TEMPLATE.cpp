// TEMPLATE.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

/////////////////////////////////////////////////////////////
// ====== Г=== |\\  //| г==\  ||         /\     ====== Г===//
//   ||   ||   ||\\//|| ||  ) ||        //\\      ||   ||  //
//   ||   [=== || \/ || [==/  ||       //  \\     ||   [===//
//   ||   ||   ||    || ||    ||      //====\\    ||   ||  //
//   ||   L=== ||    || ||    ||==== //      \\   ||   L===//
/////////////////////////////////////////////////////////////

#define opt 1
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <ccomplex>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
#include <ios>

#define srt(hh) sort(hh.begin(), hh.end()) 
#define rvs(hh) reverse(hh.begin(), hh.end()) 
#define space " "
#define endl "\n"
#define vec2d vector<vector<int>> 
#define stdvec vector<int> 
#define stdset set<int> 
#define sdict map<int, int> 
#define ll long long 
#define ld long double 
#define llvec vector<ll> 
#define dvec vector<ld> 
#define dv2d vector<vector<ld>>  
#define llv2d vector<vector<ll>> 
#define str string
#define vc vector<char>  
#define vvc vector<vector<char>> 
#define last(v) v[v.size()-1] 
 
#pragma comment(linker, "/STACK:1000000000000000000")  
 
 
using namespace std; 
 
template<typename T>  
void inpv(vector<T> & v){
	for (int i = 0; i < v.size(); i++) { 
		cin >> v[i];  
	}
}

template<typename T, typename U>
void inpv2d(vector<vector<T>>& v) {
	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v[i].size(); j++) {
			cin >> v[i][j];
		}
	}
}

template<typename T>
void outv(vector<T> v) {
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << space;
	}
}

template<typename T>
void outv2d(vector<vector<T>> v) {
	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v[i].size(); j++) {
			cout << v[i][j] << space;
		}
		cout << endl;
	}
}

void start() {
	ios_base::sync_with_stdio(0); 
	cin.tie(0);
	cout.tie(0);
	cout << setprecision(11) << fixed;
}

template<typename T>
struct SegTree {
	T(*f)(T, T);
	T noassig;
	vector<vector<T>> main_;
	T summm(T a, T b) {
		return a + b;
	}
	SegTree() {}
	SegTree(vector<T> a = {}, T F(T, T) = SegTree::summm, T na = NULL) {
		main_.push_back(a);
		while (a.size() > 1) {
			main_.push_back({});
			for (int i = 0; 2 * i + 1 < a.size(); i++) {
				main_.back().push_back(F(a[2 * i], a[2 * i + 1]));
			}
			if (a.size() % 2 == 1) {
				main_.back().push_back(a.back());
			}
			a = main_.back();
		}
		//outv2d<T>(main_);
		f = F;
		noassig = na;
	}
  	T operator[](int n) {
		return main_[0][n];
	}
 	void assig(int n, T zn) {
 		main_[0][n] = zn;
 		int j = 1;
 		n = n / 2;
 		for (int i = 1; i < main_[0].size(); i *= 2) {
	 		if (n * 2 + 1 >= main_[j - 1].size()) {
			 	main_[j][n] = main_[j - 1][n * 2];
			 	continue;
			}
			//cout << j << " " << n << "\n"; 
			main_[j][n] = f(main_[j - 1][2 * n], main_[j - 1][2 * n + 1]);
			j++;
			n = n / 2;
		}
		//outv2d<T>(main_);
	}
	T count(int l, int r) {
		int j = 0;
		T ans = noassig;
		//cout << "nor";
		//cout << "OKK" << endl;
		while (r - l > 0) {
			if (l % 2 == 1) {
				ans = f(main_[j][l], ans);
				l++;
			}
			if (r % 2 == 0) {
				ans = f(main_[j][r], ans);
				r--;
			}
			l = l / 2;
			r = r / 2;
			j++;
			//cout << l << " " << r << " " << f(1, 2) << endl;
		}
		//outv2d<int>(main_[0]);
		if (j < main_.size() and l - r == 0) {
			//cout << j << " " << l << " " << main_[j].size() << main_[j][l][0] << endl;
			ans = f(main_[j][l], ans);
		}

		//cout << "OKKK" << endl;
		return ans;
	}
};

istream& operator>>(istream& CIN, vector<int>& V) {
	for (int i = 0; i < V.size(); i++) {
		CIN >> V[i];
		//cout << i << V.size() << V[i];
	}
	return CIN;
}
istream& operator>>(istream& CIN, vector<pair<int, int>>& V) {
	for (int i = 0; i < V.size(); i++) {
		
		CIN >> V[i].first >> V[i].second;
	}
	return CIN;
}
ostream& operator<<(ostream& COUT, vector<int> v) {
	for (int i : v) {
		cout << i << " ";
	}
	cout << endl;
	return COUT;
}

int f(int a, int b) {
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}

int maxx(vector<int> v) {
	int ans = -1;
	for (auto i : v) {
		ans = f(ans, i);
	}
	return ans;
}

int maxx(SegTree<int> v) {
	int ans = -1;
	for (int i = 0; i < v.main_[0].size();i++) {
		ans = f(ans, v[i]);
	}
	return ans;
}

int main(const int argc, const char** argv) {  
	start(); 
	int H, W, N;
	cin >> H >> W >> N;
	SegTree<int> v(vector<int>(H, W), f, 0);
	for (int i = 0; i < N; i++) {
		int l = -1, r = H, I;
		cin >> I;
		while (r - l > 1) {
			int m = (l + r) / 2;
			if (m == H) {
				return 0;
			}
			//cout << v.count(0, m + 1) << endl;
			if (v.count(0, m) >= I) {
				r = m;
			}
			else {
				l = m;
			}
		}
		if(r == H){
			cout << -1 << endl;
		}
		else {
			v.assig(r, v[r] - I);
			cout << r + 1 << endl;
		}
		//cout << v.main_[0];
	}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

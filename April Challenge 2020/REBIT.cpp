#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<long, long> pll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef priority_queue<int> pqb;
typedef priority_queue<int, vi, greater<int> > pqs;

#define iamtheflash         ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define mod                 998244353
#define debug1(x)           cout<<"#x: "<<x<<"\n"
#define debug2(x,y)         cout<<"#x: "<<x<<" #y: "<<y<<"\n"
#define debug3(x,y,z)       cout<<"#x: "<<x<<" #y: "<<y<<" #z: "<<z<<"\n"
#define debug4(x,y,z,w)     cout<<"#x: "<<x<<" #y: "<<y<<" #z: "<<z<<" #w: "<<w<<"\n"
#define rep(i,n)            for(int i=0;i<(n);i++)
#define repl(i,n)           for(ll i=0;i<(n);i++)
#define fori(i,a,b)         for(int i=(a);i<=(b);i++)
#define forl(i,a,b)         for(ll i=(a);i<=(b);i++)
#define ford(i,a,b)         for(int i=(a);i>=(b);i--)
#define fordl(i,a,b)        for(ll i=(a);i>=(b);i--)
#define pb                  push_back
#define mp                  make_pair
#define ff                  first
#define ss                  second
#define mid(s,e)            (s+(e-s)/2)
#define setbits(x)          __builtin_popcountll(x)
#define zrobits(x)          __builtin_ctzll(x)
#define ps(x,y)             fixed<<setprecision(y)<<x
#define w(x)                int x; cin>>x; while(x--)
#define in(x)               int x; cin>>x;
#define ins(x)              string x; cin>>x;
#define endl                '\n'
#define infi                INT_MAX
#define infll               LLONG_MAX
#define infim               INT_MIN
#define infllm              LLONG_MIN
#define mk(arr,n,type)      type *arr = new type[n];
#define umap(x,type1,type2) unordered_map<type1, type2 > x;
#define int                 ll

void singh07() {
	iamtheflash
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
}

// (a^n) % mod
int pwmd(int a, int n) {
	if (!n)
		return 1;
	int pt = pwmd(a, n / 2);
	pt *= pt, pt %= mod;
	if (n & 1)
		pt *= a, pt %= mod;
	return pt;
}

int a = 2, A = 3;

stack<char> oper;
stack<vi> val;

int mul(int a, int b) {
	a %= mod;
	b %= mod;
	return (a * b) % mod;
}

int modinv_of_2 = pwmd(2, mod - 2);

void operate_once() {
	vi r = val.top();
	val.pop();
	vi l = val.top();
	val.pop();
	char op = oper.top();
	oper.pop();
	vi res(4);
	switch (op) {
		case '&':
			res[0] = mul(l[0], r[1] + r[a] + r[A]) + mul(l[1] + l[a] + l[A], r[0])
			         + mul(l[0], r[0]) + mul(l[a], r[A]) + mul(l[A], r[a]);
			res[1] = mul(l[1], r[1]);
			break;
		case '|':
			res[0] = mul(l[0], r[0]);
			res[1] = mul(l[1], r[0] + r[a] + r[A]) + mul(l[0] + l[a] + l[A], r[1])
			         + mul(l[1], r[1]) + mul(l[a], r[A]) + mul(l[A], r[a]);
			break;
		case '^':
			res[0] = mul(l[0], r[0]) + mul(l[1], r[1]) + mul(l[a], r[A])
			         + mul(l[A], r[a]);
			res[1] = mul(l[0], r[1]) + mul(l[1], r[0]) + mul(l[a], r[A])
			         + mul(l[A], r[a]);
			break;
	}
	res[0] %= mod;
	res[1] %= mod;

	int prob_gone = (res[0] + res[1]) % mod;
	int rem_prob = (1 - prob_gone + mod) % mod;
	res[a] = res[A] = mul(rem_prob, modinv_of_2);

	val.push(res);
}

int32_t main() {
	singh07();

	int one_by_4 = pwmd(4, mod - 2);
	vi equals = {one_by_4, one_by_4, one_by_4, one_by_4};

	w(t) {
		ins(exp);
		for (char ch : exp) {
			if (ch == '#') {
				val.push(equals);
			} else if (ch == '(') {
				continue;
			} else if (ch == ')') {
				operate_once();
			} else {
				oper.push(ch);
			}
		}
		vi ans = val.top();
		val.pop();
		cout << ans[0] << ' ' << ans[1] << ' ' << ans[a] << ' ' << ans[A] << endl;
	}

	return 0;
}

// #include<iostream>
// using namespace std;
// class A
// {
// public:
// 	A()
// 	{}

// 	virtual inline void func(int val = 1){ std::cout << "A->" << val << std::endl; }
// 	virtual void test(){ func(); }
// };

// class B : public A
// {
// public:
// 	void func(int val = 10000000){ std::cout << "B->" << val << std::endl; }
// };

// int main(int argc, char* argv[])
// {
// 	B*p = new B;
// 	p->test();

// 	return 0;
// }

// #include<iostream>
// #include<vector>
// #include<string>
// #include<unordered_set>
// using namespace std;

// int main() {
// 	int n;
// 	cin >> n;
// 	unordered_set<string> st;
// 	vector<string> res;
// 	while(n) {
// 		string temp;
// 		cin >> temp;
// 		if(st.find(temp) != st.end()) {
// 			st.emplace(temp);
// 			res.emplace_back(temp);
// 		}
// 	}
// 	for(auto& s : res) {
// 		cout << s << endl;
// 	}
// 	return 0;
// }

// #include <iostream>
// #include <vector>
// #include <string>
// using namespace std;
// const int MOD = 1000000007;
// int main()
// {
// 	int n, m;
// 	string s;
// 	cin >> n >> m >> s;
// 	vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
// 	for (int j = 1; j <= m; j++) {
// 		dp[1][j] = 1;
// 	}
// 	for (int i = 2; i <= n; i++) {
// 		if (s[i - 2] == '<') {
// 			for (int j = 1; j <= m; j++) {
// 				for (int k = 1; k < j; k++) {
// 					dp[i][j] = (dp[i][j] + dp[i - 1][k]) % MOD;
// 				}
// 			}
// 		}
// 		else if (s[i - 2] == '=') {
// 			for (int j = 1; j <= m; j++) {
// 				dp[i][j] = dp[i - 1][j];
// 			}
// 		}
// 		else {
// 			for (int j = 1; j <= m; j++) {
// 				for (int k = j + 1; k <= m; k++) {
// 					dp[i][j] = (dp[i][j] + dp[i - 1][k]) % MOD;
// 				}
// 			}
// 		}
// 	}
// 	int ans = 0;
// 	for (int j = 1; j <= m; j++){
// 		ans = (ans + dp[n][j]) % MOD;
// 	}
// 	cout << ans << endl;
// 	for(auto& v : dp) {
// 		for(auto& n : v) {
// 			cout << n << " ";
// 		}
// 		cout << endl;
// 	}
// 	return 0;
// }

#if 0
#include<iostream>
using namespace std;

class Base
{
public:
    virtual void Func1()
    {
        cout << "Func1()" << endl;
    }

    virtual void Func2()
    {
        cout << "Func2()" << endl;
    }

    void Func3()
    {
        cout << "Func3()" << endl;
    }

private:
    int _b = 1;
    char _ch = '\0';
};

class A {
    int a;
    virtual void test() = 0;
};

int main()
{
    cout << sizeof(Base) << endl;
    Base bs;
    cout << sizeof(A) << endl;
    return 0;
}
#endif


#if 1

#include <iostream>

// 定义了一个空的 print 函数，这是因为当使用可变参数的模板，需要定义一个处理最后情况的函数，如果不写，会编译错误。
void print() {}

// 可变参数模板，递归调用取出可用参数
template<typename T, typename... Types>
void print(const T& firstArg, const Types&... args) {
    std::cout << firstArg << " " << sizeof...(args) << std::endl;
    print(args...);
}

template <typename... Types>
void print(const Types&... args) {
  std::cout << "print(...)" << std::endl;
}

int main(int argc, char *argv[]) {
    print(2, "hello", 1);   // 调用的是特化版本的，即第一个模板

    return 0;
}



#endif

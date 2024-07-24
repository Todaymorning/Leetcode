#include<iostream>
#include<string>
using std::string;

char encode(int idx, char ch, const string& K) {
    char res = K[idx % K.size()];
    int a;
    if(res >= 'a' && res <= 'z') {
        a = (res - 'a');   // 找到索引
    }
    else if(res >= 'A' && res <= 'Z') {
        a = (res - 'A');
    }
    // 开始平移，只平移字母
    if(ch >= 'a' && ch <= 'z') {
        ch = 'a' + (ch - 'a' + a) % 26;   // 找到索引
    }
    else if(ch >= 'A' && ch <= 'Z') {
        ch = 'A' + (ch - 'A' + a) % 26;
    }
    return ch;
}

int main() {
    string K;
    string S;
    std::cin >> K;
    std::cin >> S;
    string result(S.size(), ' ');
    for(int i=0; i<S.size(); i++) {
        result[i] = encode(i, S[i], K);
    }
    for(auto& ch : result) {
        std::cout << ch << " ";
    }
    return 0;
}

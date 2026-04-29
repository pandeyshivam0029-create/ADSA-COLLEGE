#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

int precedence(char ch) {
    if (ch == '^') return 3;
    if (ch == '*' || ch == '/') return 2;
    if (ch == '+' || ch == '-') return 1;
    return -1;
}

string infixToPostfix(string s) {
    stack<char> st;
    string result = "";

    for (char c : s) {
        if (isalnum(c)) result += c;
        else if (c == '(') st.push(c);
        else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                result += st.top();
                st.pop();
            }
            st.pop();
        }
        else {
            while (!st.empty() && precedence(st.top()) >= precedence(c)) {
                result += st.top();
                st.pop();
            }
            st.push(c);
        }
    }

    while (!st.empty()) {
        result += st.top();
        st.pop();
    }

    return result;
}

string infixToPrefix(string s) {
    reverse(s.begin(), s.end());

    for (char &c : s) {
        if (c == '(') c = ')';
        else if (c == ')') c = '(';
    }

    string postfix = infixToPostfix(s);
    reverse(postfix.begin(), postfix.end());
    return postfix;
}

int main() {
    string infix = "A+(B*C-D)/E";
    cout << "Prefix: " << infixToPrefix(infix) << endl;
    return 0;
}
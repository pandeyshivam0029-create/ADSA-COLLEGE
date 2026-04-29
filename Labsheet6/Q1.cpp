#include <iostream>
#include <stack>
using namespace std;

int getTop(stack<int>& st) {
    if (st.empty()) {
        cout << "Stack is empty\n";
        return -1;
    }
    return st.top();
}

int main() {
    stack<int> st;
    st.push(10);
    st.push(20);
    st.push(30);

    cout << "Top element: " << getTop(st) << endl;
    cout << "Stack size after top(): " << st.size() << endl;
    return 0;
}
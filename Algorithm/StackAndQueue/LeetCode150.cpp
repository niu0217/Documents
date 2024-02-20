/* ************************************************************************
> File Name:     LeetCode150.cpp
> Author:        niu0217
> Created Time:  二  2/20 16:32:22 2024
 ************************************************************************/

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<long long> st;
        for(string token : tokens) {
            if(token == "+" || token == "-" || token == "*" || token == "/") {
                long long firtOperationNumber = st.top();
                st.pop();
                long long secondOperationNumber = st.top();
                st.pop();
                if(token == "+") {
                    st.push(secondOperationNumber + firtOperationNumber);
                }
                else if(token == "-") {
                    st.push(secondOperationNumber - firtOperationNumber);
                }
                else if(token == "*") {
                    st.push(secondOperationNumber * firtOperationNumber);
                }
                else if(token == "/") {
                    st.push(secondOperationNumber / firtOperationNumber);
                }
            }
            else {
                st.push(stol(token));
            }
        }
        int result = st.top();
        return result;
    }
};

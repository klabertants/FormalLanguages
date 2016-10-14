//
//  main.cpp
//  PracticalWork1
//
//  Created by Дмитрий Ткаченко on 14/10/2016.
//  Copyright © 2016 Dmitry Tkachenko. All rights reserved.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <stack>
#include <unordered_set>

using namespace std;

//Variables and consts block.
int k, l;

string alpha, regExp;

const unordered_set<char> letters = {'a', 'b', 'c', '1'};
const unordered_set<char> operations = {'.', '+', '*'};
stack<pair<string, unordered_set<int>>> st;
unordered_set<string> curSet;

//Main function.
int main() {

    //Reading values.
    cin >> alpha >> k >> l;
    
    for (int i = 0; i < alpha.length(); i++) {
        if (letters.find(alpha[i]) != letters.end()) {
            string tmp = "";
            tmp += alpha[i];
            unordered_set<int> s;
            if (alpha[i] == '1') {
                s.insert(0);
            } else {
                s.insert(1);
            }
            st.push(make_pair(tmp, s));
        } else if (operations.find(alpha[i]) != operations.end()) {
            if (alpha[i] == '*') {
                if (st.size() == 0) { //If postfix notation is illegal.
                    cout << "INF";
                    return 0;
                } else {
                    string tmp = st.top().first;
                    unordered_set<int> tmpSet = st.top().second;
                    st.pop();
                    unordered_set<int> Set;
                    if (tmp[0] != '(') {
                        tmp = '(' + tmp + ')' + alpha[i];
                    } else {
                        tmp += alpha[i];
                    }
                    for (auto x : tmpSet) {
                        for (int j = 0; j < k; j++) {
                            Set.insert((x * j) % k);
                        }
                    }
                    st.push(make_pair(tmp, Set));
                }
            } else {
                if (st.size() < 2) { //If postfix notation is illegal.
                    cout << "INF";
                    return 0;
                } else {
                    string tmp1 = st.top().first;
                    unordered_set<int> tmpSet1 = st.top().second;
                    st.pop();
                    string tmp2 = st.top().first;
                    unordered_set<int> tmpSet2 = st.top().second;
                    st.pop();
                    unordered_set<int> tmpSet;
                    if (alpha[i] == '.') {
                        tmp1 = tmp1 + tmp2;
                        for (auto x : tmpSet1) {
                            for (auto y : tmpSet2) {
                                    tmpSet.insert((x + y) % k);
                                }
                            }
                        } else {
                            tmp1 = '(' + tmp1 + alpha[i] + tmp2 + ')';
                            for (auto x : tmpSet1) {
                                tmpSet.insert(x % k);
                            }
                            for (auto x : tmpSet2) {
                                tmpSet.insert(x % k);
                            }
                        }
                        st.push(make_pair(tmp1, tmpSet));
                    }
                }
            } else { //If illegal symbol is reached.
                cout << "INF";
                return 0;
            }
        }
    
    //If postfix notation was illegal.
    if (st.size() != 1) {
        cout << "INF";
        return 0;
    }
        
    regExp = st.top().first;
    unordered_set<int> ansSet = st.top().second;
    st.pop();
        
    cout << ((ansSet.find(l) != ansSet.end()) ? "YES\n" : "NO\n");
}

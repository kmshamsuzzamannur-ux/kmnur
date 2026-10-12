#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

string highestValuePalindrome(string s, int n, int k) {
    vector<bool> changed(n, false);
    int used = 0;

    // Step 1: make it a palindrome
    for (int i = 0, j = n - 1; i < j; i++, j--) {
        if (s[i] != s[j]) {
            char big = max(s[i], s[j]);
            s[i] = big;
            s[j] = big;
            changed[i] = true;
            used++;
        }
    }

    if (used > k) {
        return "-1";
    }

    int left = k - used;

    // Step 2: make it as large as possible
    for (int i = 0, j = n - 1; i <= j; i++, j--) {
        if (i == j) {
            if (left >= 1 && s[i] != '9') {
                s[i] = '9';
                left--;
            }
        } else {
            if (s[i] == '9') continue;

            if (changed[i]) {
                if (left >= 1) {
                    s[i] = '9';
                    s[j] = '9';
                    left--;
                }
            } else {
                if (left >= 2) {
                    s[i] = '9';
                    s[j] = '9';
                    left -= 2;
                }
            }
        }
    }

    return s;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);
    int k = stoi(first_multiple_input[1]);

    string s;
    getline(cin, s);

    string result = highestValuePalindrome(s, n, k);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}

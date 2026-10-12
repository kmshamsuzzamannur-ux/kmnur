
#include <iostream>
#include <vector>
using namespace std;

int nonDivisibleSubset(int n, int k, vector<int> s) {
    vector<int> count(k, 0);

    for (int i = 0; i < n; i++) {
        count[s[i] % k]++;
    }

    int result = 0;

    if (count[0] > 0)
        result++;

    for (int i = 1; i <= k / 2; i++) {
        if (i != k - i) {
            result += max(count[i], count[k - i]);
        }
    }

    if (k % 2 == 0 && count[k / 2] > 0)
        result++;

    return result;
}

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> s(n);

    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    cout << nonDivisibleSubset(n, k, s) << endl;

    return 0;
}

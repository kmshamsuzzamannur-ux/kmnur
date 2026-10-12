
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Node {
    int next[26];
    int fail, out;
    vector<int> index;
    vector<long long> prefix;

    Node() {
        fill(next, next + 26, -1);
        fail = out = 0;
    }
};

vector<Node> trie;

void insertGene(string gene, int id, int h) {
    int cur = 0;

    for (char c : gene) {
        int x = c - 'a';

        if (trie[cur].next[x] == -1) {
            trie[cur].next[x] = trie.size();
            trie.push_back(Node());
        }

        cur = trie[cur].next[x];
    }

    trie[cur].index.push_back(id);

    long long sum = h;
    if (!trie[cur].prefix.empty())
        sum += trie[cur].prefix.back();

    trie[cur].prefix.push_back(sum);
}

void buildTrie() {
    vector<int> q;
    for (int i = 0; i < 26; i++) {
        int v = trie[0].next[i];

        if (v == -1)
            trie[0].next[i] = 0;
        else {
            trie[v].fail = 0;
            trie[v].out = 0;
            q.push_back(v);
        }
    }

    for (int p = 0; p < (int)q.size(); p++) {
        int u = q[p];

        for (int i = 0; i < 26; i++) {
            int v = trie[u].next[i];

            if (v == -1) {
                trie[u].next[i] =
                    trie[trie[u].fail].next[i];
            } else {
                trie[v].fail =
                    trie[trie[u].fail].next[i];

                int f = trie[v].fail;

                trie[v].out =
                    !trie[f].index.empty() ? f : trie[f].out;

                q.push_back(v);
            }
        }
    }
}

long long calculateHealth(string dna, int first, int last) {
    int cur = 0;
    long long total = 0;

    for (char c : dna) {
        cur = trie[cur].next[c - 'a'];

        int u = !trie[cur].index.empty()
                    ? cur : trie[cur].out;

        while (u != 0) {
            auto &ids = trie[u].index;
            auto &pre = trie[u].prefix;

            int l = lower_bound(ids.begin(), ids.end(), first)
                    - ids.begin();

            int r = upper_bound(ids.begin(), ids.end(), last)
                    - ids.begin();

            if (l < r) {
                total += pre[r - 1];

                if (l > 0)
                    total -= pre[l - 1];
            }

            u = trie[u].out;
        }
    }

    return total;
}

int main() {
    int n;
    cin >> n;

    vector<string> genes(n);
    for (int i = 0; i < n; i++)
        cin >> genes[i];

    vector<int> health(n);
    for (int i = 0; i < n; i++)
        cin >> health[i];

    trie.push_back(Node());

    for (int i = 0; i < n; i++)
        insertGene(genes[i], i, health[i]);

    buildTrie();

    int s;
    cin >> s;

    long long minimum = 0, maximum = 0;

    for (int i = 0; i < s; i++) {
        int first, last;
        string dna;

        cin >> first >> last >> dna;

        long long h = calculateHealth(dna, first, last);

        if (i == 0) {
            minimum = maximum = h;
        } else {
            minimum = min(minimum, h);
            maximum = max(maximum, h);
        }
    }

    cout << minimum << " " << maximum << endl;

    return 0;
}

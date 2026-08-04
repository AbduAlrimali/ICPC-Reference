#include "../utilities/template.h"
#include "../../content/strings/PalindromicTree.h"

void test_palindromic_tree(const string& s) {
    PalindromicTree pt(s);
    pt.calc_occurrences();

    // Collect all distinct palindromic substrings via brute force
    map<string, int> brute_occurrences;
    int n = sz(s);
    rep(i, 0, n) {
        rep(j, i, n) {
            string sub = s.substr(i, j - i + 1);
            string rev = sub;
            reverse(all(rev));
            if (sub == rev) {
                brute_occurrences[sub]++;
            }
        }
    }

    // Number of distinct palindromes (excluding empty string etc)
    int distinct_palindromes = sz(brute_occurrences);
    assert(pt.sz - 2 == distinct_palindromes);

    // Verify properties of each node in the tree
    rep(i, 3, pt.sz + 1) {
        string sub = s.substr(pt.t[i].st, pt.t[i].len);
        // Check if indeed a palindrome
        string rev = sub;
        reverse(all(rev));
        assert(sub == rev);

        // Check length
        assert(pt.t[i].len == sz(sub));

        // Check occurrences
        assert(pt.t[i].oc == brute_occurrences[sub]);
    }
}

int main() {
    test_palindromic_tree("abacaba");
    test_palindromic_tree("a");
    test_palindromic_tree("aaaaa");
    test_palindromic_tree("abcde");
    test_palindromic_tree("");
    cout << "PalindromicTree tests passed!" << endl;
    return 0;
}

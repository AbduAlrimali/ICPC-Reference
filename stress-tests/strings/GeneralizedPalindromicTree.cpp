#include "../utilities/template.h"
#include "../../content/strings/GeneralizedPalindromicTree.h"

void test_generalized_palindromic_tree() {
    vector<string> strs = {"aba", "abacaba", "cba"};
    int total_len = 0;
    for (const string& s : strs) total_len += sz(s);

    GeneralizedPalindromicTree gpt(total_len);
    for (int i = 0; i < sz(strs); i++) {
        gpt.add_string(strs[i], i + 1);
    }

    // Verify "b" is in all 3 strings
    int b_node = gpt.t[1].nxt['b' - 'a'];
    assert(b_node != 0);
    assert(gpt.in_how_many[b_node] == 3);

    // "a" is in all 3 strings
    int a_node = gpt.t[1].nxt['a' - 'a'];
    assert(a_node != 0);
    assert(gpt.in_how_many[a_node] == 3);

    // "c" is in 2 strings ("abacaba" and "cba")
    int c_node = gpt.t[1].nxt['c' - 'a'];
    assert(c_node != 0);
    assert(gpt.in_how_many[c_node] == 2);

    // "aba" is in 2 strings ("aba" and "abacaba")
    int aba_node = gpt.t[b_node].nxt['a' - 'a'];
    assert(aba_node != 0);
    assert(gpt.in_how_many[aba_node] == 2);
}

int main() {
    test_generalized_palindromic_tree();
    cout << "GeneralizedPalindromicTree tests passed!" << endl;
    return 0;
}

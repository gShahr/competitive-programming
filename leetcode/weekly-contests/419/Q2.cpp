/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

 vector<int> res;
 vector<int> sz(2001, 0);
 vector<bool> perfect(2001, false);
 int val = 0;

void dfs(TreeNode* node) {
    if (node == nullptr) return;
    if (node->left == nullptr && node->right == nullptr) {
        perfect[node->val] = true;
        sz[node->val] = 1;
        res.push_back(1);
    } else {
        if (node->left != nullptr) dfs(node->left);
        if (node->right != nullptr) dfs(node->right);
        if (node->left != nullptr && node->right != nullptr) {
            if (perfect[node->left->val] && perfect[node->right->val]
            && sz[node->left->val] == sz[node->right->val]) {
                perfect[node->val] = true;
                sz[node->val] = sz[node->left->val] + sz[node->right->val] + 1;
                res.push_back(sz[node->val]);
            }
        }
    }
}

void preprocess(TreeNode* node) {
    if (node == nullptr) return;
    node->val = val;
    val++;
    if (node->left != nullptr) preprocess(node->left);
    if (node ->right != nullptr) preprocess(node->right);
}

void dfs2(TreeNode* node) {
    if (node == nullptr) return;
    cout << node->val << ' ';
    if (node->left != nullptr) dfs2(node->left);
    if (node ->right != nullptr) dfs2(node->right);
}

class Solution {
public:
    int kthLargestPerfectSubtree(TreeNode* root, int k) {
        preprocess(root);
        // dfs2(root);
        // cout << endl << endl;
        dfs(root);
        sort(res.begin(), res.end(), greater<>());
        int ans = -1;
        for (auto i: res) cout << i << endl;
        if (k <= res.size()) ans = res[k-1];

        res.clear();
        for (int i = 0; i <= 2000; i++) {
            sz[i] = 0;
            perfect[i] = false;
        }
        val = 0;
        return ans;
    }
};

/*

DFS DP

*/
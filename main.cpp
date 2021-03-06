#include <bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using namespace std;

#define NEWLINE '\n'
// ||

static random_device rd;
static mt19937 rng{rd()};
long long random(long long min_val, long long max_val) {
    std::uniform_int_distribution<long long> uid(min_val, max_val);
    return uid(rng);
}

struct treap {
    treap *nodeL = nullptr, *nodeR = nullptr;
    int key;
    int priority;
    explicit treap(int k) {
        key = k;
        priority = (int) random(1, 1000000);
    }
};

void print(treap *current, ll depth = 0) {
    if (current->nodeL && current->nodeR) {
        print(current->nodeR, depth + 1);
        for (ll i = 0; i < depth; ++i) cout << "\t";
        cout << current->key << '/' << current->priority << "\n";
        print(current->nodeL, depth + 1);
    } else {
        if (current->nodeR) print(current->nodeR, depth + 1);
        for (ll i = 0; i < depth; ++i) cout << "\t";
        cout << current->key << '/' << current->priority << "\n";
        if (current->nodeL) print(current->nodeL, depth + 1);
    }
}

pair <treap*, treap*> split(treap *root, int key) {
    if (root == nullptr) {
        return {nullptr, nullptr};
    } else if (key > root->key) {
        pair <treap*, treap*> t = split(root->nodeR, key);
        root->nodeR = t.first;
        return {root, t.second};
    } else {
        pair <treap*, treap*> t = split(root->nodeL, key);
        root->nodeL = t.second;
        return {t.first, root};
    }
}

treap* merge(treap *t1, treap *t2) {
    if (t2 == nullptr) {
        return t1;
    } else if (t1 == nullptr) {
        return t2;
    } else if (t1->priority > t2->priority) {
        t1->nodeR = merge(t1->nodeR, t2);
        return t1;
    } else {
        t2->nodeL = merge(t1, t2->nodeL);
        return t2;
    }
}

bool exists(treap *root, int key) {
    if (root != nullptr) {
        if (key < root->key) {
            return exists(root->nodeL, key);
        } else if (key > root->key){
            return exists(root->nodeR, key);
        } else {
            return true;
        }
    } else {
        return false;
    }
}

treap* insert(treap* root, int k) {
    if (!exists(root, k)) {
        pair<treap*, treap*> t = split(root, k);
        treap *t1 = merge(t.first, new treap(k));
        return merge(t1, t.second);
    } else {
        return root;
    }
}

treap* remove(treap* root, int k) {
    if (root == nullptr) {
        return nullptr;
    }
    if (k == root->key) {
        return merge(root->nodeL, root->nodeR);
    }
    if (k < root->key) {
        root->nodeL = remove(root->nodeL, k);
    } else {
        root->nodeR = remove(root->nodeR, k);
    }
    return root;
}

int main() {
    ios_base::sync_with_stdio(false);
//    cin.tie(nullptr);
//    cout.tie(nullptr);
    string query;
    treap *root = nullptr;
    while (cin >> query) {
        int n;
        cin >> n;
        if (query == "i") {
            root = insert(root, n);
            cout << NEWLINE;
            print(root);
            cout << NEWLINE;
        } else if (query == "exists") {
            if (exists(root, n)) cout << "true" << endl;
            else cout << "false" << endl;
            cout << NEWLINE;
            print(root);
            cout << NEWLINE;
        } else if (query == "delete"){
            root = remove(root, n);
            cout << NEWLINE;
            print(root);
            cout << NEWLINE;
        } else if (query == "split") {
            pair <treap*, treap*> temp = split(root, n);
            cout << NEWLINE;
            print(temp.first);
            cout << NEWLINE << NEWLINE;
            print(temp.second);
            cout << NEWLINE;
        }
    }
    return 0;
}

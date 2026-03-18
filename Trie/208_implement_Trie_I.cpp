#include <string>
using namespace std;

struct TrieNode {
  TrieNode *children[26];
  bool isEnd;
  TrieNode() {
    isEnd = false;
    for (int i{0}; i < 26; i++) {
      children[i] = nullptr;
    }
  }
};
class Trie {
private:
  TrieNode *root = new TrieNode();

public:
  Trie() {}

  void insert(string word) {
    TrieNode *cur = root;
    for (char c : word) {
      if (cur->children[c - 'a'] == nullptr) {
        TrieNode *newNode = new TrieNode();
        cur->children[c - 'a'] = newNode;
      }
      cur = cur->children[c - 'a'];
    }
    cur->isEnd = true;
  }

  bool search(string word) {
    TrieNode *cur = root;
    for (char c : word) {
      if (cur->children[c - 'a'] == nullptr)
        return false;
      cur = cur->children[c - 'a'];
    }
    return cur->isEnd;
  }

  bool startsWith(string prefix) {
    TrieNode *cur = root;
    for (char c : prefix) {
      if (cur->children[c - 'a'] == nullptr)
        return false;
      cur = cur->children[c - 'a'];
    }
    return true;
  }
};

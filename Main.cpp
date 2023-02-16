#include <iostream>
#include <string>
#include <vector>
using namespace std;

class TrieNode {
public:
    bool is_word;
    vector<TrieNode*> children;
    TrieNode() {
        is_word = false;
        children = vector<TrieNode*>(26, nullptr);
    }
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }
    void insert(string word) {
        TrieNode* node = root;
        for (char c : word) {
            if (node->children[c - 'a'] == nullptr) {
                node->children[c - 'a'] = new TrieNode();
            }
            node = node->children[c - 'a'];
        }
        node->is_word = true;
    }
    bool search(string word) {
        TrieNode* node = root;
        for (char c : word) {
            if (node->children[c - 'a'] == nullptr) {
                return false;
            }
            node = node->children[c - 'a'];
        }
        return node->is_word;
    }
    vector<string> get_words_with_prefix(string prefix) {
        vector<string> result;
        TrieNode* node = root;
        for (char c : prefix) {
            if (node->children[c - 'a'] == nullptr) {
                return result;
            }
            node = node->children[c - 'a'];
        }
        get_words_from_node(node, prefix, result);
        return result;
    }
private:
    TrieNode* root;
    void get_words_from_node(TrieNode* node, string word, vector<string>& result) {
        if (node->is_word) {
            result.push_back(word);
        }
        for (int i = 0; i < 26; i++) {
            if (node->children[i] != nullptr) {
                get_words_from_node(node->children[i], word + (char)('a' + i), result);
            }
        }
    }
};

int main() {
    setlocale(LC_ALL, "");
    // создаем словарь
    Trie trie;
    trie.insert("apple");
    trie.insert("banana");
    trie.insert("orange");
    trie.insert("pear");
    trie.insert("peach");

    // запрашиваем ввод пользователя
    string prefix;
    while (true) {
        cout << "Введите префикс: ";
        cin >> prefix;

        // ищем слова с заданным префиксом
        vector<string> words = trie.get_words_with_prefix(prefix);

        // выводим результаты
        if (words.empty()) {
            cout << "Слова с таким префиксом не найдены" << endl;
        }
        else {
            cout << "Подходящие слова:" << endl;
            for (string word : words) {
                cout << " - " << word << endl;
            }
        }
    }

    return 0;
}

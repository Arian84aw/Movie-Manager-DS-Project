#pragma once
#include "Headers.h"

class CompressedTrie {
public:
    unordered_map<char, CompressedTrie*> nodes;
    string prefix;
    bool is_leaf;

    CompressedTrie(const string& prefix = "", bool is_leaf = false)
        : prefix(prefix), is_leaf(is_leaf) {}

    tuple<string, string, string> match(const string& word) {
        size_t x = 0;
        for (size_t i = 0; i < prefix.size() && i < word.size(); ++i) {
            if (prefix[i] != word[i]) break;
            x++;
        }
        return { prefix.substr(0, x), prefix.substr(x), word.substr(x) };
    }

    void insert_many(const vector<string>& words) {
        for (const auto& word : words) {
            insert(word);
        }
    }

    void insert(const string& word) {
        if (prefix == word && !is_leaf) {
            is_leaf = true;
            return;
        }

        if (nodes.find(word[0]) == nodes.end()) {
            nodes[word[0]] = new CompressedTrie(word, true);
            return;
        }

        CompressedTrie* incoming_node = nodes[word[0]];
        tuple<string, string, string> result = incoming_node->match(word);
        string matching_string = std::get<0>(result);
        string remaining_prefix = std::get<1>(result);
        string remaining_word = std::get<2>(result);

        if (remaining_prefix.empty()) {
            incoming_node->insert(remaining_word);
        }
        else {
            incoming_node->prefix = remaining_prefix;

            CompressedTrie* aux_node = nodes[matching_string[0]];
            nodes[matching_string[0]] = new CompressedTrie(matching_string, false);
            nodes[matching_string[0]]->nodes[remaining_prefix[0]] = aux_node;

            if (remaining_word.empty()) {
                nodes[matching_string[0]]->is_leaf = true;
            }
            else {
                nodes[matching_string[0]]->insert(remaining_word);
            }
        }
    }

    bool find(const string& word) {
        auto it = nodes.find(word[0]);
        if (it == nodes.end()) return false;

        tuple<string, string, string> result = it->second->match(word);
        string matching_string = get<0>(result);
        string remaining_prefix = get<1>(result);
        string remaining_word = get<2>(result);

        if (!remaining_prefix.empty()) 
            return false;

        if (remaining_word.empty())
            return it->second->is_leaf;

        return it->second->find(remaining_word);
    }

    bool delete_word(const string& word) {
        auto it = nodes.find(word[0]);
        if (it == nodes.end())
            return false;

        tuple<string, string, string> result = it->second->match(word);
        string matching_string = get<0>(result);
        string remaining_prefix = get<1>(result);
        string remaining_word = get<2>(result);

        if (!remaining_prefix.empty())
            return false;

        if (!remaining_word.empty()) {
            return it->second->delete_word(remaining_word);
        }

        if (!it->second->is_leaf)
            return false;

        if (it->second->nodes.empty()) {
            delete it->second;
            nodes.erase(it);

            if (nodes.size() == 1 && !is_leaf) {
                CompressedTrie* merging_node = nodes.begin()->second;
                is_leaf = merging_node->is_leaf;
                prefix += merging_node->prefix;
                nodes = move(merging_node->nodes);
                delete merging_node;
            }
        }
        else if (it->second->nodes.size() > 1) {
            it->second->is_leaf = false;
        }
        else {
            CompressedTrie* merging_node = it->second->nodes.begin()->second;
            it->second->is_leaf = merging_node->is_leaf;
            it->second->prefix += merging_node->prefix;
            it->second->nodes = move(merging_node->nodes);
            delete merging_node;
        }

        return true;
    }


    void get_similar_results(const string& word, vector<string>& res) {
        CompressedTrie* node = this;
        string prefix_match = "";
        int curIndex = 0;
        int prefixInd = 0;
        while (curIndex < word.length()) {
            for (int i = 0; i < node->prefix.length() && curIndex < word.length(); i++) {
                if (node->prefix[i] != word[curIndex]) {
                    cout << "No matching words found !" << endl;
                    return;
                }
                prefix_match += word[curIndex];
                curIndex++;
                prefixInd = i;
            }
            if (curIndex >= word.length())
                break;
            if (curIndex < word.length() && node->nodes.find(word[curIndex]) != node->nodes.end())
                node = node->nodes[word[curIndex]];
            else if (node->nodes.find(word[curIndex]) == node->nodes.end())
                return;
        }
        get_all_words(node, prefix_match, prefixInd + 1, res);
    }

    void get_all_words(CompressedTrie* node, const string& prefix, int prefixInd, vector<string>& res) {
        string s = prefix;
        for (int i = prefixInd; i < node->prefix.length(); i++) {
            s += node->prefix[i];
        }
        if (node->is_leaf) {
            res.push_back(s);
        }
        for (const auto& pair : node->nodes) {
            get_all_words(pair.second, s + pair.second->prefix, pair.second->prefix.length(), res);
        }
    }

    void print_tree(int height = 0) const {
        if (!prefix.empty()) {
            cout << string(height, '-') << " " << prefix
                << (is_leaf ? "  (leaf)" : "") << "\n";
        }

        for (const auto& pair : nodes) {
            pair.second->print_tree(height + 1);
        }
    }
};
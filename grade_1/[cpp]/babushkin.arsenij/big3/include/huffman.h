#pragma once

#include <iostream>
#include <fstream>
#include <cstdint>
#include <unordered_map>
#include <set>
#include <vector>

using namespace std;

class readException : public exception {
public:
    const char* what() const noexcept override { return "Failed to read file"; };
};

class dataException : public exception {
public:
    const char* what() const noexcept override { return "Invalid data"; };
};

class huffmanTree {
private:
    class Node;
    typedef Node* pNode;
    class Node {
    public:
        static const uint32_t read_size = 2;

        bool term;
        uint8_t c;
        pNode L, R;

        Node(uint8_t c): term(1), c(c), L(NULL), R(NULL){}
        Node(pNode L, pNode R): term(0), c(0), L(L), R(R){}
        Node(const Node &ot) = delete;
        Node& operator=(const Node &ot) = delete;
        ~Node(){}

        void destruct() {
            if (L) {
                L->destruct();
            }
            if (R) {
                R->destruct();
            }
            delete this;
        }

    };

    pNode root;
    vector<uint8_t> data;
    uint32_t sz;

    void write(pNode v, ofstream &fout) {
        uint8_t fr = 0, sc = v->c;
        fr |= ((bool)v->L) << 0;
        fr |= ((bool)v->R) << 1;
        fr |= (v->term) << 2;
        fout.write((char*)&fr, 1);
        fout.write((char*)&sc, 1);
        if (v->L) {
            write(v->L, fout);
        }
        if (v->R) {
            write(v->R, fout);
        }
    }

    void save_to_keep(pNode v, string cur);
        pNode make_node(uint32_t pos) {
        if (pos + 1 >= data.size()) {
            throw dataException();
        }
        uint8_t fr = data[pos], sc = data[pos + 1];
        int l = (bool)(fr & 1), r = (bool)(fr & 2), term = (bool)(fr & 4);
        if (!(term ^ (l || r))) {
            throw dataException();
        }
        if (term) {
            return new Node(sc);
        } else {
            pNode pl = NULL, pr = NULL;
            if (l) {
                pl = (pNode)1;
            }
            if (r) {
                pr = (pNode)1;
            }
            return new Node(pl, pr);
        }
    }

    pNode make_tree(uint32_t &pos) {
        pNode cur;
        cur = make_node(pos);

        pos += Node::read_size;
        if (cur->L) {
            cur->L = make_tree(pos);
        }
        if (cur->R) {
            cur->R = make_tree(pos);
        }
        return cur;
    }

public:
    unordered_map<uint8_t, string> keep;

    huffmanTree(): root(NULL), data(vector<uint8_t>()), sz(0) {}
    huffmanTree(const huffmanTree &ot) = delete;
    huffmanTree& operator=(const huffmanTree &ot) = delete;
    ~huffmanTree();

    int size() const;
    void make(vector<uint8_t> &rd);
    void read(ifstream &fin);
    void write(ofstream &fout);
    void decode(vector<uint8_t> &rd, vector<uint8_t> &wr, uint32_t sz);
};


class huffmanArchiver {
private:
    ifstream &fin;
    ofstream &fout;
    huffmanTree tree;
    vector<uint8_t> rd, wr;

    void get_bytes();
    void write_bytes();
    void code_input();
    void decode_input(uint32_t sz);

public:
    huffmanArchiver(ifstream &fin, ofstream &fout): fin(fin), fout(fout), tree(), rd(vector<uint8_t>()), wr(vector<uint8_t>()) {}
    ~huffmanArchiver() {}

    void calc(int type);
};
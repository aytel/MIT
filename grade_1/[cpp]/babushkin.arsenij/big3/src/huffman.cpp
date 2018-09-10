#include "huffman.h"

huffmanTree::~huffmanTree() {
    if (root) {
        root->destruct();
    }
}

int huffmanTree::size() const {
    return sz;
}

void huffmanTree::read(ifstream &fin) {
    fin.read((char*)&sz, 4);
    if (fin.fail()) {
        throw readException();
    }
    for (uint32_t it = 0; it < sz; it++) {
        uint8_t c;
        fin.read((char*)&c, 1);
        if (fin.fail()) {
            throw readException();
        }
        data.push_back(c);
    }

    uint32_t pos = 0;
    root = make_tree(pos);
}

void huffmanTree::make(vector<uint8_t> &rd) {
    unordered_map<uint8_t,int> count;
    set<pair<int, pNode>> all;
    for (uint8_t c : rd) {
        count[c]++;
    }
    for (auto &cur : count) {
        all.insert({cur.second, new Node(cur.first)});
        sz += Node::read_size;
    }
    while (all.size() > 1) {
        auto fr = *all.begin();
        all.erase(all.begin());
        auto sc = *all.begin();
        all.erase(all.begin());
        all.insert({fr.first + sc.first, new Node(fr.second, sc.second)});
        sz += Node::read_size;
    }
    root = all.begin()->second;
    save_to_keep(root, "");
}

void huffmanTree::save_to_keep(pNode v, string cur) {
    if (v->term) {
        keep[v->c] = cur;
        return;
    }
    save_to_keep(v->L, cur + '0');
    save_to_keep(v->R, cur + '1');
}

void huffmanTree::write(ofstream &fout)  {
    fout.write((char*)&sz, 4);
    write(root, fout);
}

void huffmanTree::decode(vector<uint8_t> &rd, vector<uint8_t> &wr, uint32_t sz) {
    int pos = 0, diff = 7;
    pNode v = root;
    uint32_t cn = 0;
    while (true) {
        if (cn == sz) {
            break;
        }
        if (v == NULL) {
            cerr << "KEK\n";
            throw dataException();
        }
        if (pos == (int)rd.size()) {
            cerr << "! " << sz - cn << '\n';
            throw dataException();
        }
        if (rd[pos] & (1 << (diff--))) {
            v = v->R;
        } else {
            v = v->L;
        }
        if (diff < 0) {
            diff = 7, pos++;
        }
        if (v->term) {
            wr.push_back(v->c);
            v = root;
            cn++;
        }
    }
}

void huffmanArchiver::get_bytes() {
    while (true) {
        uint8_t c;
        fin.read((char*)&c, 1);
        if (fin) {
            rd.push_back(c);
        } else {
            break;
        }
    }
}

void huffmanArchiver::write_bytes() {
    fout.write((char*)wr.data(), wr.size());
}

void huffmanArchiver::code_input() {
    int len = 0;
    for (uint8_t c : rd) {
        len += tree.keep[c].length();
    }
    wr.resize((len - 1) / 8 + 1);
    int pos = 0, diff = 7;
    for (uint8_t c : rd) {
        string cur = tree.keep[c];

        for (uint8_t t : cur) {
            t -= '0';

            wr[pos] |= t << (diff--);
            if (diff < 0) {
                diff = 7, pos++;
            }
        }
    }
}

void huffmanArchiver::decode_input(uint32_t sz) {
    tree.decode(rd, wr, sz);
}

void huffmanArchiver::calc(int type) {
    if (!type) {
        get_bytes();

        if (!rd.size()) {
            cout << "0\n0\n";
            return;
        }

        tree.make(rd);
        code_input();
        
        tree.write(fout);

        uint32_t sz = rd.size();
        fout.write((char*)&sz, 4);

        write_bytes();
        cout << rd.size() << '\n' << wr.size() << '\n' << tree.size() << '\n';
    } else {
        tree.read(fin);

        uint32_t sz;
        fin.read((char*)&sz, 4);
        if (!fin) {
            cerr << "HEH\n";
            throw dataException();
        }

        get_bytes();

        decode_input(sz);
        write_bytes();

        cout << rd.size() << '\n' << wr.size() << '\n' << tree.size() << '\n';
    }
}
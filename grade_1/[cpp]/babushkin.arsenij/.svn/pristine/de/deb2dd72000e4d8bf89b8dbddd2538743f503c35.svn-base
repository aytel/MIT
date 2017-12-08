#ifndef DSU
#define DSU

#include <vector>
#include <map>

using namespace std;

template <class T>
class dsu {
private:
    std::map<T, int> Set;
    std::vector<int> anc, sz;

    int find_anc(int i) {
        return (anc[i] == i ? i : anc[i] = find_anc(anc[i]));
    }

    int get_ind(T obj) {
        if (!Set.count(obj)) {
            return -1;
        }
        return Set[obj];
    }

public:
    void push(T obj) {
        int num = anc.size();
        anc.push_back(num);
        sz.push_back(1);
        Set[obj] = num;
    }

    bool merge(T a, T b) {
        int fr = get_ind(a), sc = get_ind(b);
        if (fr == -1 || sc == -1) {
            return 0;
        }
        fr = find_anc(fr), sc = find_anc(sc);
        if (fr == sc) {
            return 0;
        } else {
            if (sz[fr] < sz[sc]) {
                std::swap(fr, sc);
            }
            anc[sc] = fr;
            sz[fr] += sz[sc];
            return 1;
        }
    }

    int get_size(T obj) {
        int i = get_ind(obj);
        if (i == -1) {
            return 0;
        }
        i = find_anc(i);
        return sz[i];
    }
};

#endif
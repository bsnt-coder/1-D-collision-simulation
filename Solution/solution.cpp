
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <tuple>
#include <limits>

using namespace std;
class Empty : public exception {
};

class useIt {
protected:
    class _Item {
    public:
        pair<double, int> _key;
        int _value;

        _Item(const pair<double, int>& key, int value) : _key(key), _value(value) {}

        bool operator<(const _Item& other) const {
            if (_key.first != other._key.first)
                return _key < other._key;
            return _key.second < other._key.second;
        }

        void set_value(const pair<double, int>& kk) {
            _key = kk;
        }
    };

  /*  bool is_empty() const {
        return len() == 0;
    }*/
};

class PriorityQueue : public useIt {
private:
    vector<_Item> _list;

    int _left(int j) const { return 2 * j + 1; }
    int _right(int j) const { return 2 * j + 2; }
    int _parent(int j) const { return (j - 1) / 2; }
    bool _has_left(int j) const { return _left(j) < _list.size(); }
    bool _has_right(int j) const { return _right(j) < _list.size(); }

    void _swap(int i, int j, vector<int>& lst) {
        swap(lst[_list[i]._value], lst[_list[j]._value]);
        swap(_list[i], _list[j]);
    }

    void _upheap(int j, vector<int>& lst) {
        if (j > 0 && _list[j] < _list[_parent(j)]) {
            int parent = _parent(j);
            _swap(j, parent, lst);
            _upheap(parent, lst);
        }
    }

    void _downheap(int j, vector<int>& lst) {
        if (_has_left(j)) {
            int left = _left(j);
            int sc = left;
            if (_has_right(j)) {
                int right = _right(j);
                if (_list[right] < _list[left])
                    sc = right;
            }
            if (_list[sc] < _list[j]) {
                _swap(j, sc, lst);
                _downheap(sc, lst);
            }
        }
    }

public:
    PriorityQueue() = default;

    size_t len() const { return _list.size(); }

    pair<pair<double, int>, int> min() const {
        const auto& ans = _list[0];
        return {ans._key, ans._value};
    }

    void add(const pair<double, int>& key, int value, vector<int>& lst) {
        _list.emplace_back(key, value);
        lst[value] = _list.size() - 1;
        _upheap(_list.size() - 1, lst);
    }

    pair<pair<double, int>, int> remove_min(vector<int>& lst) {
        _swap(0, _list.size() - 1, lst);
        auto ans = _list.back();
        _list.pop_back();
        lst[ans._value] = -1;
        if (!_list.empty())
            _downheap(0, lst);
        return {ans._key, ans._value};
    }

    void heapify(int j, vector<int>& lst) {
        _downheap(j, lst);
    }

    void deapify(int j, vector<int>& lst) {
        _upheap(j, lst);
    }

    void change(int j, const pair<double, int>& val1) {
        _list[j].set_value(val1);
    }
};

vector<tuple<double, int, double>> listCollisions(vector<double>& M,  vector<double>& x, vector<double>& v, int m, double T) {
    int n = M.size();
    vector<tuple<double, int, double>> ans;
    PriorityQueue heap;
    vector<int> lyst(n, -1);
    vector<double> tym(n, 0);

    for (int i = 0; i < n - 1; ++i) {
        double vr = v[i] - v[i + 1];
        if (vr > 0) {
            double tim = abs(x[i + 1] - x[i]) / vr;
            heap.add({tim, i}, i, lyst);
        } else {
            heap.add({2 * T, i}, i, lyst);
        }
    }

    int colls = 0;
    while (colls < m) {
        auto top = heap.min();
        int ith = top.second;
        double t = top.first.first;

        if (t > T) {
            break;
        }

        double vith = v[ith];
        double viith = v[ith + 1];
        double vi = ((M[ith] - M[ith + 1]) * vith / (M[ith] + M[ith + 1])) + (2 * M[ith + 1] * viith / (M[ith] + M[ith + 1]));
        double vii = (2 * M[ith] * vith / (M[ith] + M[ith + 1])) - ((M[ith] - M[ith + 1]) * viith / (M[ith] + M[ith + 1]));
        double xx = x[ith];
        x[ith] = xx + vith * (t - tym[ith]);
        x[ith + 1] = x[ith];
        v[ith] = vi;
        v[ith + 1] = vii;
        cout << v[ith] << endl;
        cout << v[ith + 1] << endl;
        ans.emplace_back(t, ith, x[ith]);
        heap.remove_min(lyst);
        colls++;
        tym[ith] = t;
        tym[ith + 1] = t;

        if (ith - 1 >= 0) {
            double nvr = v[ith - 1] - v[ith];
            if (nvr > 0) {
                double ntym = (v[ith] * tym[ith] - v[ith - 1] * tym[ith - 1] - (x[ith] - x[ith - 1])) / (v[ith] - v[ith - 1]);
                heap.change(lyst[ith - 1], {ntym, ith - 1});
                heap.deapify(lyst[ith - 1], lyst);
            }
        }
        if (ith + 2 <= n - 1) {
            double nvr = v[ith + 1] - v[ith + 2];
            if (nvr > 0) {
                double ntym = (v[ith + 2] * tym[ith + 2] - v[ith + 1] * tym[ith + 1] - (x[ith + 2] - x[ith + 1])) / (v[ith + 2] - v[ith + 1]);
                heap.change(lyst[ith + 1], {ntym, ith + 1});
                heap.deapify(lyst[ith + 1], lyst);
            }
        }
        heap.add({2 * T, ith}, ith, lyst);
    }
    return ans;
}

int main() {
    vector<double> M = {10000.0, 1.0, 100.0};
    vector<double> x = {0.0, 1.0, 2.0};
    vector<double> v = {0.0, 0.0, -1.0};
    int m = 6;
    double T = 10.0;

    auto result = listCollisions(M, x, v, m, T);

    for (const auto& collision : result) {
        cout << "Time: " << get<0>(collision)
                  << ", Index: " << get<1>(collision)
                  << ", Position: " << get<2>(collision) << endl;
    }

    return 0;
}


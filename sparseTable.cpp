using namespace std;

template<typename T>
class SparseTable {
    int n, LOG;
    vector<vector<T>> st;
    vector<int> logv;
    T (*combine)(T, T);
public:
    SparseTable(const vector<T>& a, T (*merge)(T, T)) {
        n = a.size();
        LOG = 32 - __builtin_clz(n);
        combine = merge;
        st.assign(LOG, vector<T>(n));
        logv.assign(n + 1, 0);
        for (int i = 2; i <= n; i++)
            logv[i] = logv[i/2] + 1;
        for (int i = 0; i < n; i++)
            st[0][i] = a[i];
        for (int j = 1; j < LOG; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                st[j][i] = combine(st[j-1][i], st[j-1][i + (1 << (j-1))]);
            }
        }
    }
    T query(int l, int r) {
        int j = logv[r - l + 1];
        return combine(st[j][l], st[j][r - (1 << j) + 1]);
    }
};
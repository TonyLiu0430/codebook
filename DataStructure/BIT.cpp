class Bitree {
public:
    /* bit 一定是 1 indexed */
    vector<int> data;
    Bitree(const vector<int> &nums) {
        data.resize(nums.size() + 1, 0);
        for(int i = 0; i < nums.size(); i++ ) {
            update(i, nums[i]);
        }
    }
    void update(int x, int val) {
        x++; /*變成 1 indexed*/
        for(; x < data.size(); x += lowbit(x)) {
            data[x] += val;
        }
    }
    int query(int x) {
        x++; /*變成 1 indexed*/
        int result = 0;
        for(; x > 0; x -= lowbit(x)) {
            result += data[x];
        }
        return result;
    }
    static int lowbit(int x) {
        return x & (-x);
    }
};
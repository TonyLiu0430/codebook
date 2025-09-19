const int MAXN = 200005;
const int lgN = 20;
/* Sp[i][j] 為 區間 [i, i + 2^j - 1] 的值 */
/* 從 i 開始 長度為 2 ^ j */
/* 解決可重複貢獻問題 */
struct SP{ //sparse table
	int Sp[MAXN][lgN];
	function<int(int,int)> opt;
	void build(vector<int> &nums){ // 0 base
		for (int i = 0; i < nums.size(); i++) Sp[i][0]=nums[i];

		for (int h = 1; h < lgN; h++) {
			int len = 1 << (h - 1), i=0;
			for (; i + len < nums.size(); i++)
				Sp[i][h] = opt(Sp[i][h-1], Sp[i+len][h-1]);
			for (; i < nums.size(); i++)
				Sp[i][h] = Sp[i][h-1];
		}
	}
	int query(int l, int r){
		int h = __lg(r-l+1);
		int len = 1<<h;
		return opt(Sp[l][h], Sp[r-len+1][h] );    
	}
};


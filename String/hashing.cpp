// Hashing 0 based indexing
const int MAX = 1e6 + 5;

int mods[2] = {1040160883, 1072857881};
// back-up primes: 1066517951, 998244353 
int bases[2] = {137, 281};
int basePow[2][MAX];

int add(int x, int y, int mod) { return (x + y >= mod ? x + y - mod : x + y); }
int sub(int x, int y, int mod) { return (x - y < 0 ? x - y + mod : x - y); }
int gun(int x, int y, int mod) { return ((x * 1ll * y) % mod); }

bool PrePro;
void Preprocess()
{
    PrePro = true;
    basePow[0][0] = basePow[1][0] = 1;
    for (ll i = 0; i < 2; i++)
        for (ll j = 1; j < MAX; j++)
            basePow[i][j] = gun(basePow[i][j - 1], bases[i], mods[i]);
}

struct Hashing
{
    vector<ll> hsh[2];
    string str;

    Hashing(string _str)
    {
        if (!PrePro) Preprocess();
        str = _str;
        for(int i=0;i<2;++i) hsh[i].resize(str.size() + 1);
        Build();
    }

    void Build()
    {
        for (ll i = str.size() - 1; i >= 0; i--)
            for (int j = 0; j < 2; j++)
                hsh[j][i] = add(str[i], gun(hsh[j][i + 1], bases[j], mods[j]), mods[j]);
    }

    pair<int, int> GetHash(int l, int r)
    {
        assert(l <= r);
        int ret[2];
        for(int i = 0; i < 2 ; ++i)
            ret[i] = sub(hsh[i][l], gun(hsh[i][r + 1], basePow[i][r - l + 1], mods[i]), mods[i]);
        return make_pair(ret[0], ret[1]);
    }
};
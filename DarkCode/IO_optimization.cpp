// fread input. read(x) returns false on eof.
struct fast_input {
    static constexpr size_t size = 1 << 16;
    array<char, size> buf{};
    size_t pos = 0, len = 0;

    int get() {
        if (pos == len) {
            len = fread(buf.data(), 1, size, stdin);
            pos = 0;
            if (!len) return EOF;
        }
        return buf[pos++];
    }

    template<class t>
    bool read(t &x) {
        int c = get(), sign = 1;
        while (c != EOF && c != '-' && (c < '0' || c > '9')) c = get();
        if (c == EOF) return false;
        if (c == '-') sign = -1, c = get();
        x = 0;
        while ('0' <= c && c <= '9') x = x * 10 + c - '0', c = get();
        x *= sign;
        return true;
    }
};

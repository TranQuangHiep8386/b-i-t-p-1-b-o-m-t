// cipher_all.cpp
#include <bits/stdc++.h>
using namespace std;

/* Utility */
string only_alpha(string s) {
    string out;
    for(char c: s) if (isalpha((unsigned char)c)) out.push_back(c);
    return out;
}
string preserve_case_encrypt(const string &in, const string &out_plain) {
    // not used; simpler implementations manipulate letters directly
    return out_plain;
}

/* 1) Caesar */
string caesar_encrypt(const string &plain, int k) {
    string out = plain;
    for (size_t i=0;i<out.size();++i) {
        char c = out[i];
        if (isupper((unsigned char)c)) out[i] = char((c - 'A' + k + 26) % 26 + 'A');
        else if (islower((unsigned char)c)) out[i] = char((c - 'a' + k + 26) % 26 + 'a');
    }
    return out;
}
string caesar_decrypt(const string &cipher, int k) { return caesar_encrypt(cipher, (26-k)%26); }

/* 2) Affine: C = (a*P + b) mod26 */
int egcd(int a, int b, int &x, int &y){
    if(b==0){ x=1; y=0; return a; }
    int x1,y1; int g=egcd(b,a%b,x1,y1);
    x = y1; y = x1 - (a/b)*y1;
    return g;
}
int modinv(int a, int m) {
    int x,y; int g = egcd(a,m,x,y);
    if(g!=1) return -1;
    x %= m; if(x<0) x+=m;
    return x;
}
string affine_encrypt(const string &plain, int a, int b) {
    string out = plain;
    for (size_t i=0;i<out.size();++i){
        char c=out[i];
        if(isupper((unsigned char)c)) out[i] = char((a*((c-'A')) + b) % 26 + 'A');
        else if(islower((unsigned char)c)) out[i] = char((a*((c-'a')) + b) % 26 + 'a');
    }
    return out;
}
string affine_decrypt(const string &cipher, int a, int b) {
    int a_inv = modinv(a,26);
    if(a_inv==-1) return "[affine_decrypt error: a not invertible]";
    string out = cipher;
    for(size_t i=0;i<out.size();++i){
        char c=out[i];
        if(isupper((unsigned char)c)){
            int v = (a_inv * ((c-'A') - b + 26)) % 26;
            out[i] = char(v+'A');
        } else if(islower((unsigned char)c)){
            int v = (a_inv * ((c-'a') - b + 26)) % 26;
            out[i] = char(v+'a');
        }
    }
    return out;
}

/* 3) Columnar Transposition (simple) */
string columnar_encrypt(const string &plain, const string &key) {
    string p = plain;
    // remove non-alpha or keep spaces? We'll keep all characters including spaces for simplicity
    int cols = key.size();
    int rows = (p.size() + cols - 1) / cols;
    vector<string> grid(rows, string(cols, '\0'));
    int idx=0;
    for(int r=0;r<rows;++r){
        for(int c=0;c<cols;++c){
            if(idx < (int)p.size()) grid[r][c] = p[idx++]; else grid[r][c] = 'X';
        }
    }
    // order columns by sorted key characters, stable with index
    vector<pair<char,int>> order;
    for(int i=0;i<cols;++i) order.push_back({key[i], i});
    sort(order.begin(), order.end());
    string out;
    for(auto &pr: order){
        int c = pr.second;
        for(int r=0;r<rows;++r) out.push_back(grid[r][c]);
    }
    return out;
}
string columnar_decrypt(const string &cipher, const string &key) {
    int cols = key.size();
    int rows = (cipher.size() + cols -1)/cols;
    vector<pair<char,int>> order;
    for(int i=0;i<cols;++i) order.push_back({key[i], i});
    sort(order.begin(), order.end());
    vector<string> grid(rows, string(cols,'\0'));
    int idx=0;
    for(auto &pr: order){
        int c = pr.second;
        for(int r=0;r<rows;++r){
            if(idx < (int)cipher.size()) grid[r][c] = cipher[idx++]; else grid[r][c] = 'X';
        }
    }
    string out;
    for(int r=0;r<rows;++r) for(int c=0;c<cols;++c) out.push_back(grid[r][c]);
    return out;
}

/* 4) Vigenere */
string vigenere_encrypt(const string &plain, const string &key) {
    string out = plain;
    int m = key.size();
    if(m==0) return out;
    int ki=0;
    for(size_t i=0;i<out.size();++i){
        char c = out[i];
        if(isalpha((unsigned char)c)){
            int k = toupper(key[ki % m]) - 'A';
            if(isupper((unsigned char)c)) out[i] = char((c - 'A' + k) % 26 + 'A');
            else out[i] = char((c - 'a' + k) % 26 + 'a');
            ki++;
        }
    }
    return out;
}
string vigenere_decrypt(const string &cipher, const string &key) {
    string out = cipher;
    int m = key.size();
    if(m==0) return out;
    int ki=0;
    for(size_t i=0;i<out.size();++i){
        char c = out[i];
        if(isalpha((unsigned char)c)){
            int k = toupper(key[ki % m]) - 'A';
            if(isupper((unsigned char)c)) out[i] = char((c - 'A' - k + 260) % 26 + 'A');
            else out[i] = char((c - 'a' - k + 260) % 26 + 'a');
            ki++;
        }
    }
    return out;
}

/* 5) Playfair (I/J combined) */
struct Pos { int r,c; };
string prepare_playfair(const string &s) {
    string t;
    for(char ch: s){
        if(isalpha((unsigned char)ch)){
            char u = toupper(ch);
            if(u=='J') u='I';
            t.push_back(u);
        }
    }
    // build digraphs with filler X when needed
    string res;
    for(size_t i=0;i<t.size();++i){
        char a = t[i];
        char b = (i+1 < t.size()) ? t[i+1] : '\0';
        if(b==0){
            res.push_back(a);
            res.push_back('X');
        } else if (a==b){
            res.push_back(a);
            res.push_back('X');
        } else {
            res.push_back(a);
            res.push_back(b);
            ++i;
        }
    }
    return res;
}
array<int,25> build_pf_matrix(const string &key, char mat[5][5]) {
    bool used[26] = {0};
    used['J'-'A'] = true; // merge J into I
    string k;
    for(char ch: key){
        if(isalpha((unsigned char)ch)){
            char u = toupper(ch);
            if(u=='J') u='I';
            if(!used[u-'A']) { used[u-'A']=true; k.push_back(u); }
        }
    }
    for(char ch='A'; ch<='Z'; ++ch){
        if(!used[ch-'A']) {
            k.push_back(ch);
        }
    }
    array<int,25> pos;
    int idx=0;
    for(int r=0;r<5;++r){
        for(int c=0;c<5;++c){
            mat[r][c] = k[idx];
            pos[k[idx]-'A'] = r*5 + c;
            ++idx;
        }
    }
    return pos;
}
string playfair_encrypt(const string &plain, const string &key) {
    char mat[5][5];
    build_pf_matrix(key, mat);
    string prep = prepare_playfair(plain);
    string out;
    for(size_t i=0;i<prep.size(); i+=2){
        char A = prep[i], B = prep[i+1];
        // find pos
        int ax=-1,ay=-1,bx=-1,by=-1;
        for(int r=0;r<5;++r) for(int c=0;c<5;++c){
            if(mat[r][c]==A){ ax=r; ay=c; }
            if(mat[r][c]==B){ bx=r; by=c; }
        }
        if(ax==bx){ // same row -> right
            out.push_back(mat[ax][(ay+1)%5]);
            out.push_back(mat[bx][(by+1)%5]);
        } else if (ay==by){ // same col -> down
            out.push_back(mat[(ax+1)%5][ay]);
            out.push_back(mat[(bx+1)%5][by]);
        } else {
            out.push_back(mat[ax][by]);
            out.push_back(mat[bx][ay]);
        }
    }
    return out;
}
string playfair_decrypt(const string &cipher, const string &key) {
    char mat[5][5];
    build_pf_matrix(key, mat);
    string out;
    for(size_t i=0;i<cipher.size(); i+=2){

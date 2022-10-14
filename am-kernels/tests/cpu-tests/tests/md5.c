#include "trap.h"
#include <memory.h>
#include <stdio.h>


typedef struct {
    unsigned int count[2];
    unsigned int state[4];
    unsigned char buffer[64];
}MD5_CTX;


#define F(x,y,z) ((x & y) | (~x & z))
#define G(x,y,z) ((x & z) | (y & ~z))
#define H(x,y,z) (x^y^z)
#define I(x,y,z) (y ^ (x | ~z))
#define ROTATE_LEFT(x,n) ((x << n) | (x >> (32-n)))
#define FF(a,b,c,d,x,s,ac) \
          { \
          a += F(b,c,d) + x + ac; \
          a = ROTATE_LEFT(a,s); \
          a += b; \
          }
#define GG(a,b,c,d,x,s,ac) \
          { \
          a += G(b,c,d) + x + ac; \
          a = ROTATE_LEFT(a,s); \
          a += b; \
          }
#define HH(a,b,c,d,x,s,ac) \
          { \
          a += H(b,c,d) + x + ac; \
          a = ROTATE_LEFT(a,s); \
          a += b; \
          }
#define II(a,b,c,d,x,s,ac) \
          { \
          a += I(b,c,d) + x + ac; \
          a = ROTATE_LEFT(a,s); \
          a += b; \
          }                                            
void MD5Init(MD5_CTX* context);
void MD5Update(MD5_CTX* context, unsigned char* input, unsigned int inputlen);
void MD5Final(MD5_CTX* context, unsigned char digest[16]);
void MD5Transform(unsigned int state[4], unsigned char *block);
void MD5Encode(unsigned char* output, unsigned int* input, unsigned int len);
void MD5Decode(unsigned int* output, unsigned char* input, unsigned int len);



unsigned char PADDING[] = { 0x80,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                         0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                         0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                         0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

void MD5Init(MD5_CTX* context) {
    context->count[0] = 0;
    context->count[1] = 0;
    context->state[0] = 0x67452301;
    context->state[1] = 0xEFCDAB89;
    context->state[2] = 0x98BADCFE;
    context->state[3] = 0x10325476;
}
void MD5Update(MD5_CTX* context, unsigned char* input, unsigned int inputlen) {
    unsigned int i = 0, index = 0, partlen = 0;
    index = (context->count[0] >> 3) & 0x3F;
    partlen = 64 - index;
    context->count[0] += inputlen << 3;
    if (context->count[0] < (inputlen << 3))
        context->count[1]++;
    context->count[1] += inputlen >> 29;

    if (inputlen >= partlen) {
        memcpy(&context->buffer[index], input, partlen);
        MD5Transform(context->state, context->buffer);
        for (i = partlen;i + 64 <= inputlen;i += 64)
            MD5Transform(context->state, &input[i]);
        index = 0;
    }
    else {
        i = 0;
    }
    memcpy(&context->buffer[index], &input[i], inputlen - i);
}
void MD5Final(MD5_CTX* context, unsigned char digest[16]) {
    unsigned int index = 0, padlen = 0;
    unsigned char bits[8];
    index = (context->count[0] >> 3) & 0x3F;
    padlen = (index < 56) ? (56 - index) : (120 - index);
    MD5Encode(bits, context->count, 8);
    MD5Update(context, PADDING, padlen);
    MD5Update(context, bits, 8);
    MD5Encode(digest, context->state, 16);
}
void MD5Encode(unsigned char* output, unsigned int* input, unsigned int len) {
    unsigned int i = 0, j = 0;
    while (j < len) {
        output[j] = input[i] & 0xFF;
        output[j + 1] = (input[i] >> 8) & 0xFF;
        output[j + 2] = (input[i] >> 16) & 0xFF;
        output[j + 3] = (input[i] >> 24) & 0xFF;
        i++;
        j += 4;
    }
}
void MD5Decode(unsigned int* output, unsigned char* input, unsigned int len) {
    unsigned int i = 0, j = 0;
    while (j < len) {
        output[i] = (input[j]) |
            (input[j + 1] << 8) |
            (input[j + 2] << 16) |
            (input[j + 3] << 24);
        i++;
        j += 4;
    }
}
void MD5Transform(unsigned int state[4], unsigned char* block) {
    unsigned int a = state[0];
    unsigned int b = state[1];
    unsigned int c = state[2];
    unsigned int d = state[3];
    unsigned int x[64];
    MD5Decode(x, block, 64);
    FF(a, b, c, d, x[0], 7, 0xd76aa478); /* 1 */
    FF(d, a, b, c, x[1], 12, 0xe8c7b756); /* 2 */
    FF(c, d, a, b, x[2], 17, 0x242070db); /* 3 */
    FF(b, c, d, a, x[3], 22, 0xc1bdceee); /* 4 */
    FF(a, b, c, d, x[4], 7, 0xf57c0faf); /* 5 */
    FF(d, a, b, c, x[5], 12, 0x4787c62a); /* 6 */
    FF(c, d, a, b, x[6], 17, 0xa8304613); /* 7 */
    FF(b, c, d, a, x[7], 22, 0xfd469501); /* 8 */
    FF(a, b, c, d, x[8], 7, 0x698098d8); /* 9 */
    FF(d, a, b, c, x[9], 12, 0x8b44f7af); /* 10 */
    FF(c, d, a, b, x[10], 17, 0xffff5bb1); /* 11 */
    FF(b, c, d, a, x[11], 22, 0x895cd7be); /* 12 */
    FF(a, b, c, d, x[12], 7, 0x6b901122); /* 13 */
    FF(d, a, b, c, x[13], 12, 0xfd987193); /* 14 */
    FF(c, d, a, b, x[14], 17, 0xa679438e); /* 15 */
    FF(b, c, d, a, x[15], 22, 0x49b40821); /* 16 */

    /* Round 2 */
    GG(a, b, c, d, x[1], 5, 0xf61e2562); /* 17 */
    GG(d, a, b, c, x[6], 9, 0xc040b340); /* 18 */
    GG(c, d, a, b, x[11], 14, 0x265e5a51); /* 19 */
    GG(b, c, d, a, x[0], 20, 0xe9b6c7aa); /* 20 */
    GG(a, b, c, d, x[5], 5, 0xd62f105d); /* 21 */
    GG(d, a, b, c, x[10], 9, 0x2441453); /* 22 */
    GG(c, d, a, b, x[15], 14, 0xd8a1e681); /* 23 */
    GG(b, c, d, a, x[4], 20, 0xe7d3fbc8); /* 24 */
    GG(a, b, c, d, x[9], 5, 0x21e1cde6); /* 25 */
    GG(d, a, b, c, x[14], 9, 0xc33707d6); /* 26 */
    GG(c, d, a, b, x[3], 14, 0xf4d50d87); /* 27 */
    GG(b, c, d, a, x[8], 20, 0x455a14ed); /* 28 */
    GG(a, b, c, d, x[13], 5, 0xa9e3e905); /* 29 */
    GG(d, a, b, c, x[2], 9, 0xfcefa3f8); /* 30 */
    GG(c, d, a, b, x[7], 14, 0x676f02d9); /* 31 */
    GG(b, c, d, a, x[12], 20, 0x8d2a4c8a); /* 32 */

    /* Round 3 */
    HH(a, b, c, d, x[5], 4, 0xfffa3942); /* 33 */
    HH(d, a, b, c, x[8], 11, 0x8771f681); /* 34 */
    HH(c, d, a, b, x[11], 16, 0x6d9d6122); /* 35 */
    HH(b, c, d, a, x[14], 23, 0xfde5380c); /* 36 */
    HH(a, b, c, d, x[1], 4, 0xa4beea44); /* 37 */
    HH(d, a, b, c, x[4], 11, 0x4bdecfa9); /* 38 */
    HH(c, d, a, b, x[7], 16, 0xf6bb4b60); /* 39 */
    HH(b, c, d, a, x[10], 23, 0xbebfbc70); /* 40 */
    HH(a, b, c, d, x[13], 4, 0x289b7ec6); /* 41 */
    HH(d, a, b, c, x[0], 11, 0xeaa127fa); /* 42 */
    HH(c, d, a, b, x[3], 16, 0xd4ef3085); /* 43 */
    HH(b, c, d, a, x[6], 23, 0x4881d05); /* 44 */
    HH(a, b, c, d, x[9], 4, 0xd9d4d039); /* 45 */
    HH(d, a, b, c, x[12], 11, 0xe6db99e5); /* 46 */
    HH(c, d, a, b, x[15], 16, 0x1fa27cf8); /* 47 */
    HH(b, c, d, a, x[2], 23, 0xc4ac5665); /* 48 */

    /* Round 4 */
    II(a, b, c, d, x[0], 6, 0xf4292244); /* 49 */
    II(d, a, b, c, x[7], 10, 0x432aff97); /* 50 */
    II(c, d, a, b, x[14], 15, 0xab9423a7); /* 51 */
    II(b, c, d, a, x[5], 21, 0xfc93a039); /* 52 */
    II(a, b, c, d, x[12], 6, 0x655b59c3); /* 53 */
    II(d, a, b, c, x[3], 10, 0x8f0ccc92); /* 54 */
    II(c, d, a, b, x[10], 15, 0xffeff47d); /* 55 */
    II(b, c, d, a, x[1], 21, 0x85845dd1); /* 56 */
    II(a, b, c, d, x[8], 6, 0x6fa87e4f); /* 57 */
    II(d, a, b, c, x[15], 10, 0xfe2ce6e0); /* 58 */
    II(c, d, a, b, x[6], 15, 0xa3014314); /* 59 */
    II(b, c, d, a, x[13], 21, 0x4e0811a1); /* 60 */
    II(a, b, c, d, x[4], 6, 0xf7537e82); /* 61 */
    II(d, a, b, c, x[11], 10, 0xbd3af235); /* 62 */
    II(c, d, a, b, x[2], 15, 0x2ad7d2bb); /* 63 */
    II(b, c, d, a, x[9], 21, 0xeb86d391); /* 64 */
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
}

/* 数量 */
#define MD5_LIST_N 14
/* 用于 md5 的字符串 */
const  char* encryptlist[] = {
"admin",
"passwd",
"123453253",
"hello",
"nihao",
"wordl",
"string",
"sdfasdfjlkadsjf",
"VTHNt9m3xbZFXw45J2Rm",
"nhDMfujBfi1Jqqx9QxXi",
"Mxq71trbv1gTn3xnaeqK",
"B2bFWtq8AK8IBJpjKnfS",
"e4QnNYMNxSVkqcKXOgWUOJEcckmtzaas",
"WAuTDa8hc39N2WfddywmqJN65oA1wOjxgzVlF3IKrLwoi3MfGqTe4gpvPAclbgE9"
};
// /* 生成结果数组 */
// void gendata(void) {
//     unsigned char decrypt[16];
//     printf("static const unsigned char md5_table[] =\n{\n");
//     for (int i = 0; i < MD5_LIST_N; i++) {
//         MD5_CTX md5;
//         MD5Init(&md5);
//         MD5Update(&md5, (unsigned char*)encryptlist[i], strlen((char*)encryptlist[i]));
//         MD5Final(&md5, decrypt);
//         /* 输出 md5 共 16bybte ,占 4 int */
//         for (int j = 0; j < 16; j++) {
//             printf("0x");
//             printf("%02x", decrypt[j]);
//             putchar(',');
//         }
//         putchar('\n');
//     }
//     printf("};\n");
// }

/* md5 结果 */
static const unsigned char md5_table[] =
{
0x21,0x23,0x2f,0x29,0x7a,0x57,0xa5,0xa7,0x43,0x89,0x4a,0x0e,0x4a,0x80,0x1f,0xc3,
0x76,0xa2,0x17,0x3b,0xe6,0x39,0x32,0x54,0xe7,0x2f,0xfa,0x4d,0x6d,0xf1,0x03,0x0a,
0x6c,0x7e,0x91,0x74,0xad,0x75,0x63,0x7c,0xc4,0x7a,0xf6,0x07,0xf3,0x83,0xae,0x38,
0x5d,0x41,0x40,0x2a,0xbc,0x4b,0x2a,0x76,0xb9,0x71,0x9d,0x91,0x10,0x17,0xc5,0x92,
0x19,0x4c,0xe5,0xd0,0xb8,0x9c,0x47,0xff,0x6b,0x30,0xbf,0xb4,0x91,0xf9,0xdc,0x26,
0x28,0xfd,0x31,0x74,0x89,0x12,0x1e,0x2f,0x3f,0x5f,0xf0,0xf7,0xd8,0x9d,0xf5,0x45,
0xb4,0x5c,0xff,0xe0,0x84,0xdd,0x3d,0x20,0xd9,0x28,0xbe,0xe8,0x5e,0x7b,0x0f,0x21,
0x5e,0x38,0x3c,0xf2,0xa3,0x84,0xa5,0x2c,0x83,0x8e,0x74,0x61,0x11,0x10,0x85,0x25,
0x99,0xa8,0xd7,0xb9,0x04,0xc5,0xeb,0x2b,0x45,0x96,0x39,0xfc,0xb4,0x7a,0x85,0x50,
0x5c,0xfc,0x29,0x20,0x77,0xf8,0x0b,0xca,0x55,0x7b,0x12,0x22,0x7a,0xd8,0x40,0x83,
0x89,0x32,0x0e,0x80,0x45,0xf6,0x90,0xd6,0x7e,0x8c,0x87,0x16,0xe3,0x8f,0x81,0x33,
0x48,0x22,0x57,0x19,0x36,0xcb,0xb4,0x14,0x82,0x1b,0x86,0x93,0xc2,0x10,0x25,0xc5,
0x5e,0x1b,0xb7,0x38,0xbb,0x32,0x34,0xd9,0x8a,0x3a,0x32,0x3f,0x88,0x4c,0x67,0x3a,
0xaa,0x6c,0x8b,0x44,0x2c,0x3f,0x9a,0x6e,0xdf,0xa4,0xb3,0xdc,0x1a,0x58,0xdc,0xde
};


void md5_test(void) {
    unsigned char decrypt[16];
    int i;
    for (i = 0; i < MD5_LIST_N; i++) {
        MD5_CTX md5;
        MD5Init(&md5);
        MD5Update(&md5, (unsigned char*)encryptlist[i], strlen((char*)encryptlist[i]));
        MD5Final(&md5, decrypt);
        /* 比较 md5 */
        for (int j = 0; j < 16; j++) {
            // if (decrypt[j] == md5_table[i * 16 + j]) {
            // }
            check(decrypt[j] == md5_table[i * 16 + j]);
        }
    }
    check(i == MD5_LIST_N);
}

int main(int argc, char* argv[]) {
    md5_test();
    //gendata();
    return 0;
}



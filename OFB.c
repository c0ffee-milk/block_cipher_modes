#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "AES.h"

typedef unsigned char EleType;
EleType I[16] = "qwertyuiopasdfgh";

void shifts_register(EleType R[16], EleType s) {
    for(int i = 0; i < 15; i++) {
        R[i] = R[i + 1];
    }

    R[15] = s;
}

void print(EleType* array, int len) {
    for (int i = 0; i < len; i++) {
        // 打印两位十六进制数，格式为"XX"
        printf("%02x", array[i]);
        // 可以在这里添加一个空格或者换行符，根据你的输出格式要求
        // printf(" ");
    }
    // 打印换行符，以分隔不同的输出
    printf("\n");
}

void OFB(EleType* plaintext, EleType* key_o, int length) {
    EleType E[16];
    EleType key[11][16];
    GenerateKey(key_o, key);
    for(int i = 0; i < length; i++) {
        AES(I, E, key, 10);
        shifts_register(I, E[15]);
        plaintext[i] = plaintext[i] ^ E[15];
    }
}

int main() {
    EleType* data_o;
    EleType* data;
    EleType key_o[32];
    EleType* key = (EleType*)malloc(sizeof(EleType) * 16);
    int len;
    int mode = 0;

    printf("0:加密，1:解密，请输入：");
    scanf("%d", &mode);
    getchar();

    if(mode == 0) {
        printf("请输入明文长度：");
        scanf("%d", &len);
        printf("请输入明文：");
    }
    else if(mode == 1) {
        printf("请输入密文长度：");
        scanf("%d", &len);
        printf("请输入密文：");
    }
    else {
        printf("输入错误，默认为加密模式！\n");
        printf("请输入明文长度：");
        scanf("%d", &len);
        printf("请输入明文：");
    }

    data_o = (EleType*)malloc(sizeof(EleType) * len);
    data = (EleType*)malloc(sizeof(EleType) * (len/2));
    scanf("%s", data_o);
    getchar();

    printf("请输入密钥：");
    scanf("%s", key_o);
    getchar();

    for (int j = 0; j < len; j+=2) {
        data[j/2] = (transform(data_o[j]))*16+(transform(data_o[j+1]));
    }
    for(int j = 0; j < 32; j+=2) {
        key[j/2] = (transform(key_o[j]))*16+(transform(key_o[j+1]));
    }
 
    if(mode == 1) {
        OFB(data, key, len/2);
    }
    else {
        OFB(data, key, len/2);
    }

    print(data, len/2);

    return 0;
}
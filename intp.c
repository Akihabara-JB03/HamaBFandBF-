#include <stdio.h>
#include <string.h>
#include "jmp.h"
#include <windows.h>
#define MEM_SIZE 300000
char code[CODE_SIZE];
int max_pos = 0;
// 元のコード: char iniPath;
// 修正版: 文字列が入るように配列（サイズはMAX_PATH）にする
char iniPath[MAX_PATH]; 

#define DG_DT 0
int debug_mode = DG_DT;
void dump_memory(unsigned short *mem, int pos, int size)
{
    printf("\r");
    for(int i = 0; i < size; i++)
    {
        if(i == pos)
            printf("[%05d] ", mem[i]);
        else
            printf(" %05d  ", mem[i]);
    }

    fflush(stdout);
}
int main(int argc, char *argv[]) {
    // INIファイルから [Debug] セクションの Interval の値を読み込む（見つからない場合のデフォルトは1000ミリ秒）
    GetFullPathName("config.ini", MAX_PATH, iniPath, NULL);
    UINT interval = GetPrivateProfileInt("Debug", "Interval", 1000, iniPath);
    
    if (argc < 3) {
        printf("使い方: brainfuck.exe ファイル名 (-debug or -nodebug)\n");
        return 1;
    }
    unsigned short mem[MEM_SIZE] = {0};
    int pos = 0;
    FILE *fp = fopen(argv[1], "r");

    if (fp == NULL) {
        printf("ファイルを開けません\n");
        return 1;
    }
    fread(code, 1, CODE_SIZE - 1, fp);
    code[CODE_SIZE - 1] = '\0';
    if(strcmp(argv[2], "-debug") == 0)
    {
        debug_mode = 1;
    }
    else if(strcmp(argv[2], "-nodebug") == 0)
    {
        debug_mode = 0;
    }
    else
    {
        printf("不明なオプションです\n");
        return 1;
    }

    fclose(fp);
    int i = 0;
    // []の対応表を作る
    i = 0;
    while (code[i] != '\0') {
        if (code[i] == '[') {
            find_open(i);
        }

        if (code[i] == ']') {
            find_close(i);
        }

        i++;
    }
    i = 0;
    while (code[i] != '\0') {

        switch (code[i]) {
            case '\\':
                return 0;
            case '#':
                if (mem[pos] == 1) {
                    return 0;
                }
                break;
            case '+':
                mem[pos]++;
                break;
            case '-':
                mem[pos]--;
                break;
            case '>':
                pos++;
                if (pos >= (MEM_SIZE - 1)) {
                    pos = (MEM_SIZE - 1);
                }
                if (max_pos < pos)
                {
                    /* code */
                    max_pos = pos;
                }
                
                
                break;
            case '/':
                mem[pos] = 0;
                break;
            case '^':
                mem[pos] *= 2;
                break;
            case '<':
                pos--;
                if (pos < 0) {
                    pos = 0;
                }
                break;
            case '.':
                if (debug_mode == 1) {
                    printf("OUTPUT:%c\n",mem[pos]);
                } else {
                    putchar(mem[pos]);
                }
                break;
            case '[':
                if (mem[pos] == 0) {
                    i = position[i];
                }
                break;
            case ']':
                if (mem[pos] != 0) {
                    i = position[i];
                }
                break;
            case ',':
                mem[pos] = getchar();
                break;
            case '$':
                pos = 0;
                break;
        }
        i++;
        if (debug_mode == 1) {
            dump_memory(mem,pos,max_pos+1);   
        }
        Sleep(interval);
    }
    
}
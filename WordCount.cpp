#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#include <fcntl.h>
#include <io.h>
#endif

void count_characters(FILE* file)
{
    int ch, char_count = 0;
    while ((ch = fgetc(file)) != EOF)
    {
        char_count++;
    }
    wprintf(L"字符总数: %d\n", char_count);
}

void count_words(FILE* file)
{
    int ch, word_count = 1;
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == ' ' || ch == ',' || ch == '\n' || ch == '\t')
        {
            word_count++;
        }
    }
    wprintf(L"单词总数: %d\n", word_count);
}

void print_usage()
{
    wprintf(L"使用方法:\n");
    wprintf(L"wordcount [参数] [文件名]\n");
    wprintf(L"[参数]: -c 计算字符数；-w 计算单词数\n");
    wprintf(L"[文件名]: 输入文件名\n");
}

int main(int argc, char* argv[])
{
#ifdef _WIN32
    // 设置控制台为UTF-8编码
    SetConsoleOutputCP(CP_UTF8);
    _setmode(_fileno(stdout), _O_U8TEXT);
#endif

    if (argc != 3)
    {
        print_usage();
        return 1;
    }

    FILE* file = fopen(argv[2], "r");
    if (file == NULL)
    {
        wprintf(L"无法打开文件 %s\n", argv[2]);
        return 1;
    }

    if (strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "-C") == 0)
    {
        count_characters(file);
    }
    else if (strcmp(argv[1], "-w") == 0 || strcmp(argv[1], "-W") == 0)
    {
        count_words(file);
    }
    else
    {
        print_usage();
    }

    fclose(file);
    return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/**
 *  -x 表示以下的命令 
 *
 *  -c 要有字母
 *  -n 包含数字
 *  -e 包含特殊字符
 *  -16 密码长度可更改
 */

#define Long_Password 16

int long_Password = Long_Password;

typedef enum TYPE {error = 0, c, n, e, cn = 9, ce = 12, ne = 15, cne = 18} TYPE;

char * StringStore[] = {"abcdefghijklmnopqrstuvwxyz",
                        "1234567890",
                        "!@#$^&*()_+~{}|:<>?[],.",
                       };

int Cifang(int number, int Ci);
int Trans_to_Number(char * str, int length);
int Analyze_Command(int numebr, char * command[]);//命令行分析
void Create_Password(char * Password, int Password_LONG, int Kind);//产生密码

int main(int argc, char * argv[])
{
    int Kind = 0;
    char *Password = NULL;

    Kind = (int)Analyze_Command(argc, argv);//分析指令

    Password = (char *)malloc(long_Password + 1);
    Create_Password(Password, long_Password + 1, Kind);//生成密码
    
    printf("%s\n\n", Password);//显示密码
    free(Password);

    return 0;
}

int Cifang(int number, int Ci)
{
    int i = 0;
    int result = 1;

    for(i = 0; i < Ci; i++)
    {
        result = result * number;
    }

    return result;
}

int Trans_to_Number(char * str, int length)
{
    int i = 0;
    int number = 0;

    for(i = 1; i < length; i++)
    {
        number = number + ((str[i] - '0') * Cifang(10, length - 1 - i)); 
    }   

    return number;
}

int Analyze_Command(int number, char * command[])//命令行分析
{
    int i = 1;
    int result = 0;

    for(i = 1; i < number; i++)
    {
        if(command[i][0] == '-')
        {
            if(strchr(command[i], 'c'))
                result = result + c;
            else if(strchr(command[i], 'n'))
                result = result + n;
            else if(strchr(command[i], 'e'))
                result = result + e;
            else
            {
                long_Password = Trans_to_Number(command[i], strlen(command[i]));
            }
        }
    }
    return (((result > 3) || ((result == 3) && (number == 3))) ? (result * 3) : result);
}

void Create_Password(char * Password, int Password_LONG, int Kind)
{
    int i = 0; 
    srand((unsigned int)time(NULL));

    if((Kind == c) || (Kind == n) || (Kind == e))
    {
        for(i = 0; i < Password_LONG; i++)
        {
            Password[i] = StringStore[Kind - 1][rand()%(strlen(StringStore[Kind - 1]))];
        }
    }
    else if((Kind == cn) || (Kind == ce) || (Kind == ne))
    {
        for(i = 0; i < Password_LONG; i++)
        {
            if(Kind != ne)
            {
                if((rand() % 2) == 1)
                {
                    Password[i] = StringStore[0][rand()%(strlen(StringStore[0]))];
                }
                else
                {
                    if(Kind == cn)
                        Password[i] = StringStore[1][rand()%(strlen(StringStore[1]))];
                    else
                        Password[i] = StringStore[2][rand()%(strlen(StringStore[2]))];
                }

            }
            else
            {
                if((rand() % 2) == 1)
                    Password[i] = StringStore[1][rand()%(strlen(StringStore[1]))];
                else
                    Password[i] = StringStore[2][rand()%(strlen(StringStore[2]))];
            }
        }
    }
    else if(Kind == cne)
    {
        for(i = 0; i < Password_LONG; i++)
        {

            if((rand() % 3) == 0)
            {
                Password[i] = StringStore[0][rand()%(strlen(StringStore[0]))];
            }
            else if((rand() % 3) == 1)
            {
                Password[i] = StringStore[1][rand()%(strlen(StringStore[1]))];
            }
            else
            {
                Password[i] = StringStore[2][rand()%(strlen(StringStore[2]))];
            }
        }
    }
    Password[long_Password] = '\0';
}
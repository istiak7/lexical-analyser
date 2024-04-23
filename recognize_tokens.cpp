#include<bits/stdc++.h>
#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
using namespace std;

stack<char>st;
stack<string>mul_com;
set<string>paren_string , constant_string , keyword_string , iden_string , log_string , header_string;
set<char>arith_string, pun_string;

int com , paren_count , mul_com_count , mul_flag;
int keyword_library(char temp[])
{
    int count = 0, flag = 0;
    char keywords[32][12] = {"return", "continue", "extern", "static", "long", "signed",
                             "switch", "char", "else", "unsigned", "if", "struct",
                             "union", "goto", "while", "float", "enum", "sizeof", "double", "volatile",
                             "const", "case", "for", "break", "void", "register", "int",
                             "do", "default", "short", "typedef", "auto"
                            };
    while (count <= 31)
    {
        if (strcmp(keywords[count], temp) == 0)
        {
            flag = 1;
            break;
        }
        count = count + 1;
    }
    return (flag);
}

int const_library(char temp[]) {
    int count = 0 , i = 0 ,  flag = 0 ;
    char constant [] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int size = 0 ;
    while (temp[size] != '\0') {
        size++;
    }
    while (temp[i] != '\0') {
        count = 0 ;
        while (count < 10) {
            if (constant[count] == temp[i]) {
                flag++;

                break;
            }
            count += 1 ;
        }
        i++;
    }
    if (flag == size)
        return 1 ;
    return 0 ;
}

void paren_library(char ch) {
    if (ch == '(' || ch == '{' || ch == '[') {
        st.push(ch);
    }
    else if (ch == ')' || ch == '}' || ch == ']') {
        if (!st.empty()) {
            if (ch == ')' && st.top() == '(')paren_string.insert("()");
            else if (ch == '}' && st.top() == '{')paren_string.insert("{}");
            else if (ch == ']' && st.top() == '[')paren_string.insert("[]");
            st.pop();
        }
    }
}

int is_header(char temp[]){
    int len = 0 , flag = 0 ;
                while (temp[len] != '\0') {
                    len++;
                }
                int ok = 0 ;
                string in = "include";
                for (int i = 0 ; i < 7 ; i++) {
                    if (temp[i] == in[i])ok++;
                }
                if (ok == 7 && temp[len - 1] == 'h') {
                   return 1;
                }
    return 0 ;
}

void display() {
    printf("\n");
    printf("punctuation_count : %d : { ", pun_string.size());
    for (auto i : pun_string)cout << i << ' ';
    printf("}\n");

    printf("\nconstant_string_count : %d : { ", constant_string.size());

    for (auto i : constant_string)cout << i << " ";

    printf("}\n");

    printf("\nArithmetic_string_count : %d : { ", arith_string.size());
    for (auto i : arith_string)cout << i << " ";

    printf("}\n\n");

    printf("Logical_operator : %d ", log_string.size());
    for (auto u : log_string)cout << u << " ";
    printf("\n");
    printf("\nkeyword_string_count : %d: { ", keyword_string.size());

    for (auto i : keyword_string)cout << i << " ";
    printf("}\n\n");
    printf("\nSingle Comment : %d\n", com);
    printf("\nMultiple Comment : %d\n", mul_com_count);
    printf("\nparenthesis_count : %d : ", paren_string.size());

    for (auto i : paren_string)cout << i << ' ';
    printf("\n\n");
    printf("\nheader_count : %d : ", header_string.size());
    printf("\n");

    for (auto i : header_string)cout << i << '\n';
    printf("\n\n");
    printf("\nidentifier_count : %d : ", iden_string.size());
    printf("\n");

    for (string i : iden_string)cout << i << '\n';
}

int x ;

int main()
{
    char ch, temp[40], arithmetic_operator[] = "=+%*/-" , pun[] = ";:,";
    FILE *file_pointer;
    int count;
    x = 0;
    file_pointer = fopen("demo.txt", "r");
    if (file_pointer == NULL)
    {
        printf("The file could not be opened.\n");
        exit(0);
    }
    int com_flag = 0 , log_flag = 0 ;
    char comment , log = '$' ;
    while ((ch = fgetc(file_pointer)) != EOF)
    {
        // here is update comment .......
        if (ch == '*' && !mul_com.empty()) {
            mul_flag++;
            continue;
        }
        if (mul_flag > 0 && ch == '/') {
            mul_flag = 0 ;
            com_flag = 0 ;
            mul_com_count++;
            mul_com.pop();
        }
        if (ch == '/')
        {
            com_flag++; //2
            if (com_flag == 1)
            {
                comment = '/';
                continue;
            }
        }
        if (com_flag == 1)
        {
            if (ch == '*') {
                mul_com.push("/*");
                continue;
            }
            else {
                arith_string.insert(comment);
                comment =  NULL;
                com_flag = 0 ;
            }
        }
        else if (com_flag == 2 && ch == '\n')
        {
            com_flag = 0 ;
            comment = NULL;
            com++;
            continue;
        }
        else if (com_flag == 2)continue;
        if ((ch == '>' || ch == '<' || ch == '=' || ch == '!') && log == '$') {
            log_flag++;
            log = ch ;
            continue;
        }
        if (log_flag == 1 && (ch != '=')) {
            log_flag = 0 ;
            log = '$';
        }
        if (log_flag == 1 && (ch == '=')) {
            string s = "";
            s += log , s += ch ;
            log_string.insert(s);
            log_flag = 0 ;
            log = '$';
        }
        if (ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == '[' || ch == ']') {
            paren_library(ch);
            continue;
        }

        count = 0;
        while (count <= 5)
        {
            if (ch == arithmetic_operator[count])
            {
                arith_string.insert(ch);
            }
            count = count + 1;
        }

        count = 0 ;
        while (count < 3)
        {
            if (ch == pun[count])
            {
                pun_string.insert(ch);

            }
            count = count + 1 ;

        }
        if (isalnum(ch))
        {
            temp[x++] = ch;
        }
        else if ((ch == '\n' || ch == ' ') && (x != 0))
        {
            temp[x] = '\0';
            x = 0;
            if (keyword_library(temp) == 1)
            {
                keyword_string.insert(temp);
            }
            else if (const_library(temp) == 1)
            {
                constant_string.insert(temp);
            }
            else
            {
                int len = 0 ;
                while (temp[len] != '\0') {
                    len++;
                }
                if(is_header(temp) == 1){
                    string ans = "";
                    for (int i = 7 ; i < len - 1 ; i++) {
                        ans += temp[i];
                    }
                    ans += ".h";
                    header_string.insert(ans);
                }
                else
                    iden_string.insert(temp);
            }
        }

    }
    display();
    fclose(file_pointer);
    getch();
    return 0;
}


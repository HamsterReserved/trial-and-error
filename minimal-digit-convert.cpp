/*-------------------------------------------------------
【程序设计】
---------------------------------------------------------

题目：输入一个整数（位数不超过9位）代表一个人民币值（单位为元），请转换成财务
要求的大写格式。如23108元，转换后变成“贰万叁仟壹佰零捌元”。200101元，转换后
变成“贰拾万零壹佰零壹元”。
运行结果见样张。
对应的大写数字为：
壹贰叁肆伍陆柒捌玖拾佰仟万亿
100000000
运行输出必须和样张完全一样才能得满分。

-------------------------------------------------------*/
#include <iostream>
#include <cmath>
using namespace std;
int main()
{

/**********Program**********/
    char* chs_digit[] = {"零","壹","贰","叁","肆","伍","陆","柒","捌","玖",""};
    char* chs_unit[] = {"","拾","佰","仟","万","拾","佰","仟","亿"};
    char in[19] = {0}; // 从第9个字节起放入读取的字符串，它最长占用9字节，加NULL最大19字节
    char should_print[9] = {0}; // 是否应该打印这一位
    char* curr;

    cin >> ((char*)in + 9);

    char* start = (char*)in + 9;
    while (*start) {
        *start -= '0';
        start++;
    } // 找到输入字符串的末尾，并把数字转为整形
    start -= 9; // 把输入字符串放到start开头的9字节末尾

    // 打印非0、后面跟了有效数字的0
    for (int curr_pos = 0; curr_pos < 9; curr_pos++) {
        if (start[curr_pos] || (curr_pos <= 8 && start[curr_pos + 1])) {
            should_print[curr_pos] = 1;
        }
    }

    // 去掉唯一的前缀0，但保留全0的最后一个0
    if (start[0] == 0) {
        for (curr = start + 1; curr <= &start[8] && !(*curr); curr++);
        should_print[curr - 1 - start] = (curr - 1 == &start[8]);
    }

    if (start[4] == 0 && *(int*)(start + 1)) {
        // 第二组最后一位为0但第二组有非0时，附加“万”单位
        start[4] = 10;
        should_print[4] = 1;
    }

    // 打印
    for (int curr_pos = 0; curr_pos < 9; curr_pos++) {
        if (should_print[curr_pos]) {
            if (curr_pos == 5 && start[4] == 10 && start[5] != 0) {
                // 额外条件：101001000 壹亿零壹佰万[零]壹仟 不属于原始序列，需额外添加
                cout << chs_digit[0];
            }

            cout << chs_digit[start[curr_pos]];

            if (start[curr_pos]) {
                cout << chs_unit[8 - curr_pos];
            }
        }
    }
/**********  End  **********/

        return 0;
}



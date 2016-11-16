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
    wstring chs_digit[] = {L"零",L"壹",L"贰",L"叁",L"肆",L"伍",L"陆",L"柒",L"捌",L"玖",L""};
    wstring chs_unit[] = {L"",L"拾",L"佰",L"仟",L"万",L"拾",L"佰",L"仟",L"亿"};
    char in[20] = {0}; // 从第9个字节起放入读取的字符串，它最长占用9字节，加NULL最大19字节，前面空一个字节
    char should_print[9] = {0}; // 是否应该打印这一位
    char* curr; // Temp

    cin >> ((char*)in + 10);

    char* start = (char*)in + 10;
    while (*start) {
        *start -= '0';
        start++;
    } // 找到输入字符串的末尾，并把数字转为整形
    start -= 9; // 把输入字符串放到start开头的9字节末尾

    // 初步判断哪些数字要打印（保证连续的0只出现一个，这样处理就不用区分前缀后缀了）
    for (int curr_pos = 0; curr_pos < 9; curr_pos++) {
        if (start[curr_pos] || start[curr_pos - 1]) {
            should_print[curr_pos] = 1;
        } else {
            should_print[curr_pos] = 0;
        }
    }

    // 处理特殊情况
    if (start[8] == 0) {
        // 必定存在一个后缀0，处理掉最近一个后缀0. 这个0可以是第3组带的，也可以是第2组继承来的（第三组全0）
        // 当第3组自己有后缀0的时候，第二组的后缀0由下面一个if处理
        curr = &start[7];
        while (!*(curr--) && curr > start);
        should_print[curr + (*(curr + 1) ? 2 : 1) - start] = 0;
    }

    if (start[4] == 0) {
        // 第2组的后缀0，注意这里忽略了后缀0在千万位的情况：千万位的0如果到现在仍被设置为要打印（表明第一组有数字、第二组有前缀0），则它总是要打印的
        curr = &start[3];
        while (!*(curr--) && curr > start);
        should_print[curr + 2 - start] = 0;

        // 最后一位为0但第二组有非0时，附加“万”单位
        if (*(int*)(start + 1)) {
            start[4] = 10;
            should_print[4] = 1;
        }
    }

    // 打印
#ifndef WIN32
    wcout.imbue(locale("zh_CN.UTF-8"));
#else
    wcout.imbue(locale("chs"));
#endif
    for (int curr_pos = 0; curr_pos < 9; curr_pos++) {
        if (should_print[curr_pos]) {
            wcout << chs_digit[start[curr_pos]];

            if (start[curr_pos]) {
                wcout << chs_unit[8 - curr_pos];
            }
        }
    }
/**********  End  **********/

        return 0;
}



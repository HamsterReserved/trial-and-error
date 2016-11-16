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
#define POW10(x) (pow(10, x))
#define POP_DIGIT_ON(x, pos) (x >= POW10(pos - 1) ? (tmp = x / POW10(pos - 1), x -= tmp * POW10(pos - 1), tmp) : 0)
    wstring chs_digit[] = {L"零",L"壹",L"贰",L"叁",L"肆",L"伍",L"陆",L"柒",L"捌",L"玖"};
    wstring chs_unit[] = {L"",L"拾",L"佰",L"仟"};
    wstring out; // 为了能正确计数中文字符，要使用wstring
    //  给定数值        当前位的数字      上一个打印的是不是0  本组里是否全0       输出是否全0      取数字用
    int given_num = 0, curr_digit = 0, last_zero = 1,   segment_valid = 0, all_valid = 0, tmp = 0;
    // last_zero = 1 默认禁止打印前导0

    cin >> given_num;

    // Process digit 9
    if ((curr_digit = POP_DIGIT_ON(given_num, 9))) {
        out.append(chs_digit[curr_digit]).append(L"亿");
        last_zero = 0;
        all_valid = 1;
    }

    // Process digit 5~8
    for (int curr_pos = 8; curr_pos > 4; curr_pos--) {
        if ((curr_digit = POP_DIGIT_ON(given_num, curr_pos))) {
            // 如果这一位不是0，就打印它，再加上单位
            out.append(chs_digit[curr_digit]).append(chs_unit[curr_pos - 5]);
            last_zero = 0;
            segment_valid = 1;
            all_valid = 1;
        } else {
            // 如果这一位是0，且
            if (!last_zero) {
                // 上一位打印的不是0，就打印它，不带单位
                out.append(chs_digit[curr_digit]);
                // 但连续的零只允许打印一个
                last_zero = 1;
            }
        }
    }
    if (curr_digit == 0) {
        // 如果本组最后一位是0，那么如果前面任何一个组（包括本组）有有效数字
        // 则肯定多且只多打了一个零，需要截掉
        // 如果前面没有有效数字，out会是空的，调用substr无影响
        out = out.substr(0, out.length() - 1);
    }
    if (segment_valid) {
        out.append(L"万");
    }
    last_zero = !all_valid; // 如果前面打印了有效数字，那下一组就要打印前导0，否则不可以
    segment_valid = 0;

    // Process digit 1~4
    for (int curr_pos = 4; curr_pos > 0; curr_pos--) {
        if ((curr_digit = POP_DIGIT_ON(given_num, curr_pos))) {
            out.append(chs_digit[curr_digit]).append(chs_unit[curr_pos - 1]);
            last_zero = 0;
            segment_valid = 1;
        } else {
            if (!last_zero) {
                out.append(chs_digit[curr_digit]);
                last_zero = 1;
            }
        }
    }
    if (curr_digit == 0) {
        out = out.substr(0, out.length() - 1);
    }
    if (out.length() == 0) {
        // 空字符串，表示输入就是0
        out.append(chs_digit[0]);
    }
#ifndef WIN32
    wcout.imbue(locale("zh_CN.UTF-8"));
#else
    wcout.imbue(locale("chs"));
#endif
    wcout << out;
/**********  End  **********/

        return 0;
}



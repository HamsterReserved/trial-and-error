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
    //  给定数值        当前位的数字       当前组是否打印了后缀0      当前组是否打印了前导0    当前组是否全0        整个输出是否全0   取数字用
    int given_num = 0, curr_digit = 0, segment_post_zero = 0, segment_pre_zero = 0, segment_valid = 0, all_valid = 0, tmp = 0;
    cin >> given_num;

    // Process digit 9
    if ((curr_digit = POP_DIGIT_ON(given_num, 9))) {
        out.append(chs_digit[curr_digit]).append(L"亿");
        all_valid = 1;
    }

    // Process digit 5~8
    for (int curr_pos = 8; curr_pos > 4; curr_pos--) {
        if ((curr_digit = POP_DIGIT_ON(given_num, curr_pos))) {
            // 如果这一位不是0，就打印它，再加上单位
            out.append(chs_digit[curr_digit]).append(chs_unit[curr_pos - 5]);
            segment_valid = 1;
            all_valid = 1;
        } else {
            // 如果这一位是0，且
            if (segment_valid && !segment_post_zero) {
                // 这一组之前打印了其他数字，就打印这个零
                out.append(L"零");
                // 但这种后缀类型的零只允许打印一个（规则^[1-9]+0+.*$）
                segment_post_zero = 1;
            } else if (!segment_valid && !segment_pre_zero && all_valid) {
                // 这一组在有效数字之前都是0，并且之前还打印了其他数字，就打印这个零
                out.append(L"零");
                // 但这种前缀类型的零只允许打印一个（规则^0+.*$）
                segment_pre_zero = 1;
            }
        }
    }
    if (segment_valid && curr_digit == 0) {
        // 若本组打印了有效数字，但最后一位是0，则表明这个零是多打的，去掉
        // 规则 ^.*0+$ 这种情况下不需要后缀0
        out = out.substr(0, out.length() - 1);
    }
    if (segment_valid) {
        out.append(L"万");
    }
    segment_valid = segment_post_zero = segment_pre_zero = 0;

    // Process digit 1~4
    for (int curr_pos = 4; curr_pos > 0; curr_pos--) {
        if ((curr_digit = POP_DIGIT_ON(given_num, curr_pos))) {
            out.append(chs_digit[curr_digit]).append(chs_unit[curr_pos - 1]);
            segment_valid = 1;
            all_valid = 1;
        } else {
            if (segment_valid && !segment_post_zero) {
                out.append(L"零");
                segment_post_zero = 1;
            } else if (!segment_valid && !segment_pre_zero && all_valid) {
                out.append(L"零");
                segment_pre_zero = 1;
            }
        }
    }
    if (segment_valid && curr_digit == 0) {
        out = out.substr(0, out.length() - 1);
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



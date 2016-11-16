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
    wstring chs_digit[] = {L"零",L"壹",L"贰",L"叁",L"肆",L"伍",L"陆",L"柒",L"捌",L"玖"};
    wstring chs_unit[] = {L"仟",L"佰",L"拾",L""};
    wstring out; // 为了能正确计数中文字符，要使用wstring
    char in[19]; // 从第9个字节起放入读取的字符串，它最长占用9字节，加NULL最大19字节
    int valid_segments = 0;

    cin >> ((char*)in + 9);

    char* start = (char*)in + 9;
    while (*start) {
        *start -= '0';
        start++;
    } // 找到输入字符串的末尾，并把数字转为整形
    start -= 9; // 把输入字符串放到start开头的9字节末尾
    char* curr = start;

    if (*curr) {
        out.append(chs_digit[start[0]]).append(L"亿");
        valid_segments |= 1 << 2; // 第3组有效
    }

    curr = start += 1;
    if (*(int*)(curr)) {
        for (; curr < start + 4; curr++) {
            if (*curr) {
                out.append(chs_digit[*curr]).append(chs_unit[curr - start]);
                valid_segments |= 1 << 1; // 第2组已打印字符
            } else {
                if (valid_segments) out.append(chs_digit[0]); // 只在打印了其他数字的前提下才可以打印零
                while (!(*curr++) && curr < start + 4); // 查找下一个非0数字
                if (*--curr) --curr; // 如果这个判断不成立，则表明找到了结尾也没找到非0数字，不需要管。否则要再往前跳一个让这个数字输出来
            }
        }
        if (*(start + 3) == 0) { // 解决多余的后缀0
        	out = out.substr(0, out.length() - 1);
    	}
    	out.append(L"万");
    }

    curr = start += 4;
    if (*(int*)(curr)) {
    	if (valid_segments == 1 << 2 && *curr) out.append(chs_digit[0]); // 1、3组有效，2组无效
        for (; curr < start + 4; curr++) {
            if (*curr) {
                out.append(chs_digit[*curr]).append(chs_unit[curr - start]);
                valid_segments |= 1 << 0; // 第1组已打印字符
            } else {
                if (valid_segments) out.append(chs_digit[0]);
                while (!(*curr++) && curr < start + 4); // 查找下一个数字
                if (*--curr) --curr;
            }
        }
        if (*(start + 3) == 0) {
        	out = out.substr(0, out.length() - 1);
    	}
    }
    if (!valid_segments) {
        // 没有一组有效，表明就是0
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



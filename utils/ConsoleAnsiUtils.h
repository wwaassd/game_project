//
// Created by 14368 on 2022/8/21.
//

#ifndef GAME_PROJECT_CONSOLEANSIUTILS_H
#define GAME_PROJECT_CONSOLEANSIUTILS_H
/// Set output mode to handle virtual terminal sequences
#include <windows.h>
#include <string>

const std::string ANSI_RESET="\033[m";
/// 开启控制台的Ansi转义序列识别功能
/// \return
int EnableConsoleAnsi(){
    system("chcp 65001");
    system("cls");
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    {
        return false;
    }
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    if (hIn == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    DWORD dwOriginalOutMode = 0;
    DWORD dwOriginalInMode = 0;
    if (!GetConsoleMode(hOut, &dwOriginalOutMode))
    {
        return false;
    }
    if (!GetConsoleMode(hIn, &dwOriginalInMode))
    {
        return false;
    }

    DWORD dwRequestedOutModes = ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;
    DWORD dwRequestedInModes = ENABLE_VIRTUAL_TERMINAL_INPUT;

    DWORD dwOutMode = dwOriginalOutMode | dwRequestedOutModes;
    if (!SetConsoleMode(hOut, dwOutMode))
    {
        // we failed to set both modes, try to step down mode gracefully.
        dwRequestedOutModes = ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        dwOutMode = dwOriginalOutMode | dwRequestedOutModes;
        if (!SetConsoleMode(hOut, dwOutMode))
        {
            // Failed to set any VT mode, can't do anything here.
            return -1;
        }
    }

    DWORD dwInMode = dwOriginalInMode | dwRequestedInModes;
    if (!SetConsoleMode(hIn, dwInMode))
    {
        // Failed to set VT input mode, can't do anything here.
        return -1;
    }
}
/// 移动光标到指定位置
/// \param x >=1
/// \param y >=1
void MoveCursor(int x, int y) {
    printf("\033[%d;%df", y, x);
}
/// 从屏幕左上角开始绘制长为x宽为y的边框
/// \param x
/// \param y
void DrawBox(int x, int y) {
    for (int i = 1; i <= y; ++i) {
        for (int j = 1; j <= x; ++j) {
            MoveCursor(j, i);
            if (j == 1 && i == 1) {
                printf("┌");
            } else if (j > 1 && j < x && i == 1) {
                printf("─");
            } else if (j == x && i == 1) {
                printf("┐");
            } else if ((j == 1 || j == x) && i > 1 && i < y) {
                printf("│");
            } else if (j == 1 && i == y) {
                printf("└");
            } else if (j > 1 && j < x && i == y) {
                printf("─");
            } else if (j == x && i == y) {
                printf("┘");
            }
        }
    }
}
class RGBColor{
public:
    RGBColor(int r,int g, int b):r(r),g(g),b(b){}
    RGBColor(float hue){
        int red0 = 255 * (1 - hue);
        int red1 = 255 * (1 - abs(hue - 3));
        int red;
        if (red0 > 0) red = red0;
        else if (red1 > 0)
            red = red1;
        else
            red = 0;
        int green = 255 * (1 - abs(hue - 1));
        if (green > 255) green = 255;
        if (green < 0) green = 0;
        int blue = 255 * (1 - abs(hue - 2));
        if (blue > 255) blue = 255;
        if (blue < 0) blue = 0;
        r= red;
        g = green;
        b=blue;
    }
    int r;
    int g;
    int b;
};
/// 将矩阵绘制到屏幕，1为指定颜色，0为黑色
/// \param matrix
/// \param x
/// \param y
/// \param color
void DrawMatrix(const int *matrix, int x, int y,RGBColor color) {
    static int matrixLast[200];
    printf("\033[?25l");
    //    DrawBox(x+2,y+2);
    MoveCursor(1, 1);
    for (int j = 0; j < y; ++j) {
        MoveCursor(2, j + 2);
        for (int i = 0; i < x; ++i) {
            if (matrix[i + j * y] != matrixLast[i + j * y]) {
                matrixLast[i + j * y] = matrix[i + j * y];
                printf("\033[38;2;%d;%d;%dm█%s", color.r, color.g, color.b, ANSI_RESET.c_str());
                MoveCursor(15,5);
                printf("\033[38;2;%d;%d;%dm██color now: r%-3d g%-3d b%-3d██%s",  color.r, color.g, color.b,  color.r, color.g, color.b, ANSI_RESET.c_str());
            } else {
                //                MoveCursor(i+2,j+2);
                printf(" ");
            }
        }
    }
    printf("\033[?5h");
}
void SetBlock(int x, int y, int lengthX, int value, int *matrix) {
    matrix[y * lengthX + x] = value;
}
#endif//GAME_PROJECT_CONSOLEANSIUTILS_H

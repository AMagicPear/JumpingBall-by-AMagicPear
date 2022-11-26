#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <cmath>

//#include "function.h"
const float g = 0.3;
const float height = 450;
const float width = 800;

//function MyRand( array $arr , $number );
int main() {
    //画布基本参数
    initgraph(width, height);
    //小球的基本参数
    double ball_x, ball_y, ball_vy, radius;
    radius = 20;
    //方块的基本参数
    double rect_left_x, rect_width, rect_height;
    double rect_vx;
    //得分
    int score = 0;
    int times = 0;
    TCHAR s[20];
    TCHAR print_score[20];
    bool show_two_rects = false;
    float space0 = 200, space = 200;
    //进入循环
    while (true) {
        ++times;
        //数据初始化
        ball_x = width / 4;
        ball_y = height - radius;
        rect_height = 100;
        rect_width = 20;
        rect_left_x = width * 3 / 4;
        rect_vx = -3;
        std::cout << "在此控制台处按R或空格键开始游戏" << std::endl;
        cleardevice();
        _stprintf(print_score, _T("在控制台内按R或空格键开始游戏"));
        settextstyle(40, 0, _T("Microsoft Yahei"));
        outtextxy(170, 200, print_score);
        //检测R开始游戏
        while (true) {
            if (kbhit()) {
                char input = _getch();
                if (input == 'r' || input == 'R' || input == ' ') {
                    std::cout << "请按空格键控制小球跳跃" << std::endl;
                    break;
                }
            }
        }
        //绘制初始界面
        cleardevice();
        _stprintf(print_score, _T("请按空格键控制小球跳跃"));
        settextstyle(40, 0, _T("Microsoft Yahei"));
        outtextxy(200, 200, print_score);
        fillrectangle(rect_left_x, height - rect_height, rect_left_x + rect_width, height);
        fillcircle(ball_x, ball_y, radius);
        _stprintf(s, _T("%d"), score);
        settextstyle(40, 0, _T("Arial"));
        outtextxy(50, 30, s);
        //检测玩家第一次按空格键时进入游戏主体
        while (true) {
            if (kbhit()) {
                char input = _getch();
                if (input == ' ') {
                    printf("游戏愉快~\n");
                    printf("按E键退出游戏，按P键暂停\n");
                    ball_vy = -10;
                    break;
                }
            }
        }
        //游戏主体
        pause:
        while (true) {
            //获取键盘输入
            if (kbhit()) {
                char input = _getch();
                if (input == ' ')
                    ball_vy = 0.3 * ball_vy - 10;
                if (input == 'e' || input == 'E')
                    goto over;
                if (input == 'P' || input == 'p') {
                    _getch();
                    goto pause;
                }
            }
            //小球的运动
            ball_vy += g;
            ball_y += ball_vy;
            if (ball_y >= height - radius) {
                ball_vy = 0;
                ball_y = height - radius;
            }
            if (ball_y <= radius) {
                ball_vy = 0;
                ball_y = radius;
            }
            //方块的移动
            if (space > 2 * radius + 20) {
                space = space0 - (double) 10 * score;
            }//分数越高间距越小
            if (score > 2) {
                show_two_rects = true;
            }
            rect_left_x += rect_vx;
            if (rect_left_x <= 0) {
                score++;
                rect_left_x = width;
                rect_height = rand() % int(height / 4) + height / 6;
                rect_vx = rand() / float(RAND_MAX) * 4 - 7 - 0.3 * score;
            }
            //得分增加
            /*if (rect_right_x-ball_x<100) {
                ++score;
                printf_s("当前得分：%d\n", score);
            }*/
            //碰撞判定
            if (!show_two_rects)
                if (ball_x > rect_left_x && ball_x < rect_left_x + rect_width + 2 * radius &&
                    ball_y + radius > height - rect_height) {
                    std::cout << "你無了！" << "该次得分：" << score << std::endl;
                    /*cleardevice();
                    _stprintf(print_score, _T("你無了！\n该次得分：%d"), score);
                    settextstyle(40, 0, _T("Microsoft Yahei"));
                    outtextxy(250, 200, print_score);*/
                    score = 0;
                    break;
                }
            if (show_two_rects)
                if (ball_x > rect_left_x && ball_x < rect_left_x + rect_width + 2 * radius &&
                    !((ball_y + radius <= height - rect_height) && (ball_y - radius >= height - rect_height - space))) {
                    std::cout << "你無了！" << "该次得分：" << score << std::endl;
                    /*cleardevice();
                    _stprintf(print_score, _T("你無了！\n该次得分：%d"), score);
                    settextstyle(40, 0, _T("Microsoft Yahei"));
                    outtextxy(250, 200, print_score);*/
                    score = 0;
                    break;
                }
            //每帧的绘制
            cleardevice();
            if (score == 1) {
                _stprintf(print_score, _T("很好！就是这样。"), score);
                settextstyle(40, 0, _T("Microsoft Yahei"));
                outtextxy(200, 200, print_score);
            }
            if (score == 2) {
                _stprintf(print_score, _T("E键退出，P键暂停"), score);
                settextstyle(40, 0, _T("Microsoft Yahei"));
                outtextxy(200, 200, print_score);
            }
            fillrectangle(rect_left_x, height - rect_height, rect_left_x + rect_width, height);
            if (show_two_rects) fillrectangle(rect_left_x, 0, rect_left_x + rect_width, height - rect_height - space);
            fillcircle(ball_x, ball_y, radius);
            _stprintf(s, _T("%d"), score);
            settextstyle(40, 0, _T("Arial"));
            outtextxy(50, 30, s);

            Sleep(10);
        }
    }
    over:
    closegraph();
}
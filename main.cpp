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
    //������������
    initgraph(width, height);
    //С��Ļ�������
    double ball_x, ball_y, ball_vy, radius;
    radius = 20;
    //����Ļ�������
    double rect_left_x, rect_width, rect_height;
    double rect_vx;
    //�÷�
    int score = 0;
    int times = 0;
    TCHAR s[20];
    TCHAR print_score[20];
    bool show_two_rects = false;
    float space0 = 200, space = 200;
    //����ѭ��
    while (true) {
        ++times;
        //���ݳ�ʼ��
        ball_x = width / 4;
        ball_y = height - radius;
        rect_height = 100;
        rect_width = 20;
        rect_left_x = width * 3 / 4;
        rect_vx = -3;
        std::cout << "�ڴ˿���̨����R��ո����ʼ��Ϸ" << std::endl;
        cleardevice();
        _stprintf(print_score, _T("�ڿ���̨�ڰ�R��ո����ʼ��Ϸ"));
        settextstyle(40, 0, _T("Microsoft Yahei"));
        outtextxy(170, 200, print_score);
        //���R��ʼ��Ϸ
        while (true) {
            if (kbhit()) {
                char input = _getch();
                if (input == 'r' || input == 'R' || input == ' ') {
                    std::cout << "�밴�ո������С����Ծ" << std::endl;
                    break;
                }
            }
        }
        //���Ƴ�ʼ����
        cleardevice();
        _stprintf(print_score, _T("�밴�ո������С����Ծ"));
        settextstyle(40, 0, _T("Microsoft Yahei"));
        outtextxy(200, 200, print_score);
        fillrectangle(rect_left_x, height - rect_height, rect_left_x + rect_width, height);
        fillcircle(ball_x, ball_y, radius);
        _stprintf(s, _T("%d"), score);
        settextstyle(40, 0, _T("Arial"));
        outtextxy(50, 30, s);
        //�����ҵ�һ�ΰ��ո��ʱ������Ϸ����
        while (true) {
            if (kbhit()) {
                char input = _getch();
                if (input == ' ') {
                    printf("��Ϸ���~\n");
                    printf("��E���˳���Ϸ����P����ͣ\n");
                    ball_vy = -10;
                    break;
                }
            }
        }
        //��Ϸ����
        pause:
        while (true) {
            //��ȡ��������
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
            //С����˶�
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
            //������ƶ�
            if (space > 2 * radius + 20) {
                space = space0 - (double) 10 * score;
            }//����Խ�߼��ԽС
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
            //�÷�����
            /*if (rect_right_x-ball_x<100) {
                ++score;
                printf_s("��ǰ�÷֣�%d\n", score);
            }*/
            //��ײ�ж�
            if (!show_two_rects)
                if (ball_x > rect_left_x && ball_x < rect_left_x + rect_width + 2 * radius &&
                    ball_y + radius > height - rect_height) {
                    std::cout << "��o�ˣ�" << "�ôε÷֣�" << score << std::endl;
                    /*cleardevice();
                    _stprintf(print_score, _T("��o�ˣ�\n�ôε÷֣�%d"), score);
                    settextstyle(40, 0, _T("Microsoft Yahei"));
                    outtextxy(250, 200, print_score);*/
                    score = 0;
                    break;
                }
            if (show_two_rects)
                if (ball_x > rect_left_x && ball_x < rect_left_x + rect_width + 2 * radius &&
                    !((ball_y + radius <= height - rect_height) && (ball_y - radius >= height - rect_height - space))) {
                    std::cout << "��o�ˣ�" << "�ôε÷֣�" << score << std::endl;
                    /*cleardevice();
                    _stprintf(print_score, _T("��o�ˣ�\n�ôε÷֣�%d"), score);
                    settextstyle(40, 0, _T("Microsoft Yahei"));
                    outtextxy(250, 200, print_score);*/
                    score = 0;
                    break;
                }
            //ÿ֡�Ļ���
            cleardevice();
            if (score == 1) {
                _stprintf(print_score, _T("�ܺã�����������"), score);
                settextstyle(40, 0, _T("Microsoft Yahei"));
                outtextxy(200, 200, print_score);
            }
            if (score == 2) {
                _stprintf(print_score, _T("E���˳���P����ͣ"), score);
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
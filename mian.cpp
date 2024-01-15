#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include <graphics.h>	// 引用图形库头文件
#include <conio.h>
#include <easyx.h>
#include<mmsystem.h>//包含多媒体设备接口头文件
#include<iostream>
#pragma comment (lib, "WINMM.LIB")
int pos[5];
int st,ed;

void BGM()
{
    mciSendString(_T("open ssb.mp3"), NULL, 0, NULL);
    mciSendString(_T("play ssb.mp3"), NULL, 0, NULL);          

void Backgound()
{
	//背景图片1
	IMAGE background1;
    loadimage(&background1, _T("bg.png"), 1514, 915);
	putimage(0, 0, &background1);
   
}

//修改方格位置and长宽,第一个是x负责左右，y负责上下是第二个
void button(int x, int y, int w, int h, TCHAR* text)
{
	setbkmode(TRANSPARENT);
	setfillcolor(GREEN);
	fillroundrect(x, y, x + w, y + h, 10, 10);
	// 输出字符串（MBCS 字符集）
	TCHAR s1[] = L"黑体";
	settextstyle(30, 0, s1);
	TCHAR s[50] = L"hello";
	int tx = x + (w - textwidth(text)) / 2;
	int ty = y + (h - textheight(text)) / 2;
	outtextxy(tx, ty, text);
}
TCHAR s1[50] = L"1.操场";
TCHAR s2[50] = L"2.蠡园";
TCHAR s3[50] = L"3.农场";
TCHAR s4[50] = L"4.E栋";
TCHAR s5[50] = L"5.ABD栋";
TCHAR s6[50] = L"6.青教楼";
TCHAR s7[50] = L"7.各类运动场所";
TCHAR s8[50] = L"8.风雨球场";
TCHAR s9[50] = L"9.456栋";
TCHAR s10[50] = L"10.新活";
TCHAR s11[50] = L"11.多攸香";
TCHAR s12[50] = L"12.荷花池";
TCHAR s13[50] = L"13.八九教";
TCHAR s14[50] = L"14.邮局";
TCHAR s15[50] = L"15.C栋";
TCHAR s16[50] = L"16.黑师兄";
TCHAR s17[50] = L"17.校史馆";
TCHAR s18[50] = L"18.四教";
TCHAR s19[50] = L"19.五教";
TCHAR s20[50] = L"20.十教";
TCHAR s21[50] = L"21.1号门";
TCHAR s22[50] = L"22.一教";
TCHAR s23[50] = L"23.三教";
TCHAR s24[50] = L"24.3号门";
TCHAR s25[50] = L"25.七教";
TCHAR s26[50] = L"26.图书馆";
TCHAR s27[50] = L"27.二教";

struct Button {
    int x, y, w, h;
    TCHAR* text;
} buttons[27] = {
{155, 100, 100, 50, s1},
{20, 100, 100, 50, s2},
{30, 30, 100, 50, s3},
{105, 220, 100, 50, s4},
{105, 340, 120, 50, s5},
{305, 350, 150, 50, s6},
{275, 230, 205, 50, s7},
{310, 75, 160, 50, s8},
{480, 75, 110, 50, s9},
{610, 75, 110, 50, s10},
{740, 75, 130, 50, s11},
{690, 205, 135, 50, s12},
{620, 350, 130, 50, s13},
{420, 520, 120, 50, s14},
{610, 560, 100, 50, s15},
{750, 610, 135, 50, s16},
{780, 370, 135, 50, s17},
{900, 540, 135, 50, s18},
{850, 290, 135, 50, s19},
{950, 370, 135, 50, s20},
{1125, 630, 135, 50, s21},
{1235, 520, 135, 50, s22},
{1275, 360, 135, 50, s23},
{1375, 250, 135, 50, s24},
{1275, 155, 130, 50, s25},
{1175, 85, 135, 50, s26},
{975, 75, 130, 50, s27}
};
#define Infinity 2000  //表示无穷大
#define MaxVertexNum 43
#define key 27  //顶点个数

typedef struct arcell {  //边的权值
    int adj;  //权值
}arcell, adjmatrix[MaxVertexNum][MaxVertexNum];

typedef struct vexsinfo {  //顶点信息
    int position;  //地点编号
    char name[32];  //地点名称
}vexsinfo;

typedef struct mgraph {  //定义图的结构体
    vexsinfo vexs[MaxVertexNum];  //顶点数组
    adjmatrix arcs;  //邻接矩阵
    int vexnum, arcnum;  //顶点数和边数
}mgraph;

mgraph campus;
int d[30];
int visited[30];
int shortest[MaxVertexNum][MaxVertexNum];  //存储最短路径
int pathh[MaxVertexNum][MaxVertexNum];  //存储路径
mgraph initgraph() {
    int i = 0, j = 0;
    mgraph c;
    c.vexnum = 27;
    c.arcnum = 43;
    for (i = 1; i <= key; i++)
        c.vexs[i].position = i;
    strcpy(c.vexs[1].name, "操场");
    strcpy(c.vexs[2].name, "蠡园");
    strcpy(c.vexs[3].name, "农场");
    strcpy(c.vexs[4].name, "E栋");
    strcpy(c.vexs[5].name, "ABD栋");
    strcpy(c.vexs[6].name, "青教楼");
    strcpy(c.vexs[7].name, "各类运动场所");
    strcpy(c.vexs[8].name, "风雨球场");
    strcpy(c.vexs[9].name, "456栋");
    strcpy(c.vexs[10].name, "新活");
    strcpy(c.vexs[11].name, "多攸香");
    strcpy(c.vexs[12].name, "荷花池");
    strcpy(c.vexs[13].name, "八九教");
    strcpy(c.vexs[14].name, "邮局");
    strcpy(c.vexs[15].name, "C栋");
    strcpy(c.vexs[16].name, "黑师兄");
    strcpy(c.vexs[17].name, "校史馆");
    strcpy(c.vexs[18].name, "四教");
    strcpy(c.vexs[19].name, "五教");
    strcpy(c.vexs[20].name, "十教");
    strcpy(c.vexs[21].name, "1号门");
    strcpy(c.vexs[22].name, "一教");
    strcpy(c.vexs[23].name, "三教");
    strcpy(c.vexs[24].name, "3号门");
    strcpy(c.vexs[25].name, "七教");
    strcpy(c.vexs[26].name, "图书馆");
    strcpy(c.vexs[27].name, "二教");
    for (i = 1; i <= key; i++)
        for (j = 1; j <= key; j++)
            c.arcs[i][j].adj = Infinity;
    c.arcs[1][2].adj = 50;  c.arcs[1][4].adj = 25;
    c.arcs[1][7].adj = 30;  c.arcs[1][8].adj = 10;
    c.arcs[2][3].adj = 20;  c.arcs[4][5].adj = 75;
    c.arcs[5][6].adj = 30;  c.arcs[7][9].adj = 60;
    c.arcs[5][14].adj = 75;  c.arcs[6][7].adj = 100;
    c.arcs[8][9].adj = 125;  c.arcs[13][15].adj = 50;
    c.arcs[9][10].adj = 50;  c.arcs[10][11].adj = 20;
    c.arcs[10][12].adj = 40;  c.arcs[12][19].adj = 125;
    c.arcs[11][12].adj = 20;  c.arcs[11][27].adj = 125;
    c.arcs[12][13].adj = 50;  c.arcs[13][14].adj = 30;
    c.arcs[13][19].adj = 70;  c.arcs[14][15].adj = 20;
    c.arcs[15][16].adj = 30;  c.arcs[17][18].adj = 100;
    c.arcs[17][19].adj = 80;  c.arcs[18][20].adj = 50;
    c.arcs[18][21].adj = 125;  c.arcs[19][20].adj = 75;
    c.arcs[19][27].adj = 90;  c.arcs[21][22].adj = 20;
    c.arcs[22][23].adj = 20;  c.arcs[22][26].adj = 80;
    c.arcs[23][24].adj = 70;  c.arcs[23][25].adj = 30;
    c.arcs[24][25].adj = 50;  c.arcs[25][26].adj = 20;
    c.arcs[26][27].adj = 30;  c.arcs[4][7].adj = 30;
    c.arcs[7][10].adj = 200;  c.arcs[16][18].adj = 110;
    c.arcs[7][12].adj = 110;  c.arcs[7][13].adj = 120;
    c.arcs[12][19].adj = 80;  c.arcs[13][17].adj = 30;
    c.arcs[17][20].adj = 80;
    for (i = 1; i <= key; i++)
        for (j = 1; j <= key; j++)
            c.arcs[j][i].adj = c.arcs[i][j].adj;
    return c;
}

//查询两地点间的最短路径（floyd算法）
void floyd(mgraph c)
{
    int i, j, k;
    for (i = 1; i <= key; i++)  //将图的邻接矩阵赋值给shortest二维数组，将矩阵pathh全部初始化为-1
    {
        for (j = 1; j <= key; j++)
        {
            shortest[i][j] = c.arcs[i][j].adj;
            pathh[i][j] = j;
        }
    }
    int i1, j1, k1 = 0;
    for (k = 1; k <= key; k++)  //完成了以k为中间点对所有的顶点对（i,j）进行检测和修改
    {
        for (i = 1; i <= key; i++)
        {
            for (j = 1; j <= key; j++)
            {
                if (shortest[i][j] > shortest[i][k] + shortest[k][j])
                {
                    shortest[i][j] = shortest[i][k] + shortest[k][j];
                    pathh[i][j] = pathh[i][k];  //记录一下所走的路  //P数组用来存放前驱顶点
                }
            }
        }
    }
}

//打印出最短路径
void display(mgraph c, int i, int j)
{
    int a, b;
    a = i; b = j;
    printf("您要查询的两地点间的最短路径是：\n\n");
    printf("%s", c.vexs[a].name);
    TCHAR str[10];
    _stprintf_s(str, _T("%d"), a);
    outtextxy(buttons[a - 1].x, buttons[a - 1].y - 30, str);  // 在按钮上方输出地点编号
    while (pathh[i][j] != b)
    {
        printf("-->%s", c.vexs[pathh[i][j]].name);
        _stprintf_s(str, _T("%d"), pathh[i][j]);
        outtextxy(buttons[pathh[i][j] - 1].x, buttons[pathh[i][j] - 1].y - 30, str);  // 在按钮上方输出地点编号
        i = pathh[i][j];
    }
    printf("-->%s\n\n", c.vexs[b].name);
    _stprintf_s(str, _T("%d"), b);
    outtextxy(buttons[b - 1].x, buttons[b - 1].y - 30, str);  // 在按钮上方输出地点编号
    printf("%s-->%s的最短路径是：%d 米。\n\n", c.vexs[a].name, c.vexs[b].name, shortest[a][b]);
}



//任意两点间最短距离（floyd算法）
int shortdistance(mgraph c,int i,int j)
{
    
        floyd(c);
        //printf_Pshuzu();
        display(c, i, j);
    return 1;
}

void algo(int x,int y) {
    campus = initgraph();
    shortdistance(campus,x,y);
}

int main()
{
    BGM();
	initgraph(1514, 915);    //创建窗口大小为640x480像素
	setbkcolor(WHITE);
    Backgound();    //加载背景
    //
	//cleardevice();
    setcolor(BLACK);
    setlinestyle(PS_DASH, 4);
    line(70, 125, 50, 35);//2 3
    line(205, 125, 70, 125);//1 2
    line(205, 125, 155, 245);//1 4
    line(205, 125, 377.5, 255);//1 7
    line(535, 100, 377.5, 255);//9 7
    line(155, 245, 165, 365);//4 5
    line(165, 365, 380, 375);//5 6
    line(155, 245, 377.5, 255);//4 7
    line(205, 125, 390, 100);//1 8
    line(390, 100, 535, 100);//8 9
    line(535, 100, 665, 100);// 9 10
    line(665, 100, 805, 100);// 10 11
    line(665, 100, 757.5, 230);// 10 12
    line(665, 100, 377.5, 255);// 10 7
    line(685, 375, 377.5, 255);// 13 7
    line(757.5, 230, 685, 375);// 12 13
    line(847.5, 395, 685, 375);// 17 13
    line(847.5, 395, 1017.5, 375);// 17 20
    line(805, 100, 757.5, 230);// 11 12
    line(380, 375, 377.5, 255);//6 7
    line(757.5, 230, 377.5, 255);//12 7
    line(165, 365, 480, 545);//5 14
    line(480, 545, 660, 585);// 14 15
    line(685, 375, 660, 585);// 13 15
    line(757.5, 230, 917.5, 315);// 12 19
    line(660, 585, 817.5, 635);//  15 16
    line(967.5, 565, 817.5, 635);//  18 16
    line(685, 375, 907.5, 305);//13 19
    line(685, 375, 480, 545);//13 14
    line(917.5, 315, 1040, 115);//19 27
    line(805, 100, 1040, 115);//11 27
    line(917.5, 315, 1017.5, 375);//19 20
    line(847.5, 375, 967.5, 565);// 17 18
    line(917.5, 315, 847.5, 375);//19 17
    line(967.5, 565, 1017.5, 375);//18 20
    line(967.5, 565, 1192.5, 655);//18 21
    line(1302.5, 545, 1192.5, 655);//22 21
    line(1252.5, 545, 1242.5, 125);//22 26
    line(1040, 115, 1242.5, 125);//27 26
    line(1340, 195, 1242.5, 125);//25 26
    line(1340, 195, 1442.5, 275);//25 24
    line(1340, 195, 1342.5, 385);//25 23
    line(1302.5, 545, 1342.5, 385);//22 23
    line(1442.5, 275, 1342.5, 385);//24 23
    setcolor(WHITE);
    setlinestyle(PS_SOLID, 4);
	button(30, 30, 100, 50, s3);
    button(20, 100, 100, 50, s2);
    button(155, 100, 100, 50, s1);
    button(105, 220, 100, 50, s4);
    button(105, 340, 120, 50, s5);
    button(305, 350, 150, 50, s6);
    button(275, 230, 205, 50, s7);
    button(310, 75, 160, 50, s8);
    button(480, 75, 110, 50, s9);
    button(610, 75, 110, 50, s10);
    button(740, 75, 130, 50, s11);
    button(690, 205, 135, 50, s12);
    button(620, 350, 130, 50, s13);
    button(420, 520, 120, 50, s14);
    button(610, 560, 100, 50, s15);
    button(750, 610, 135, 50, s16);
    button(780, 370, 135, 50, s17);
    button(900, 540, 135, 50, s18);
    button(850, 290, 135, 50, s19);
    button(950, 370, 135, 50, s20);
    button(1125, 630, 135, 50, s21);
    button(1235, 520, 135, 50, s22);
    button(1275, 360, 135, 50, s23);
    button(1375, 250, 135, 50, s24);
    button(1275, 155, 130, 50, s25);
    button(1175, 85, 135, 50, s26);
    button(975, 75, 130, 50, s27);
    
    ExMessage msg;
    int clickCount = 0;  // 点击次数
    Button* start = nullptr;  // 出发点
    Button* end = nullptr;  // 终点
    setfillcolor(WHITE);
    while (true) {
        if (peekmessage(&msg, EM_MOUSE)) {
            switch (msg.message) {
            case WM_MOUSEMOVE:
                // 检查每个按钮
                for (int i = 0; i < 27; i++)
                {
                    Button& btn = buttons[i];
                    if (msg.x >= btn.x && msg.x <= btn.x + btn.w && msg.y >= btn.y && msg.y <= btn.y + btn.h)
                    {
                        // 鼠标在这个按钮上
                        setcolor(RED);
                        rectangle(btn.x, btn.y, btn.x + btn.w, btn.y + btn.h); // 绘制红色边框
                    }
                    else
                    {
                        // 鼠标不在这个按钮上
                        setcolor(WHITE);
                        rectangle(btn.x, btn.y, btn.x + btn.w, btn.y + btn.h); // 绘制白色边框
                    }
                }
                break;
            case WM_LBUTTONDOWN:
                // 检查每个按钮
                for (int i = 0; i < 27; i++)
                {
                    Button& btn = buttons[i];
                    if (msg.x >= btn.x && msg.x <= btn.x + btn.w && msg.y >= btn.y && msg.y <= btn.y + btn.h)
                    {
                        // 用户点击了这个按钮
                        mciSendString(_T("play dj.mp3"), NULL, 0, NULL);
                        settextcolor(RGB(0, 0, 0));  // 设置字体颜色
                        clickCount++;
                        if (clickCount == 1) {
                            start = &btn;
                            pos[1] = i + 1;  // 记录出发点的编号
                            setfillstyle(SOLID_FILL, BLACK);  // 设置填充样式为实心
                            bar(0, 700, 350, 730);               // 创建一个矩形来覆盖旧的文本
                            outtextxy(0, 700, _T("出发点: "));
                            outtextxy(100, 700, start->text);
                        }
                        else if (clickCount == 2) {
                            end = &btn;
                            pos[2] = i + 1;  // 记录终点的编号
                            setfillstyle(SOLID_FILL, BLACK);  // 设置填充样式为实心
                            bar(0, 750, 350, 780);  // 创建一个矩形来覆盖旧的文本
                            outtextxy(0, 750, _T("终点: "));
                            outtextxy(80, 750, end->text);

                            // 计算并输出 pos[1] 和 pos[2] 的和
                            algo(pos[1], pos[2]);
                            int sum = shortest[pos[1]][pos[2]];
                            TCHAR str[10];
                            bar(450, 750, 800, 780);  // 创建一个矩形来覆盖旧的文本
                            _stprintf_s(str, _T("%d"), sum);
                            settextcolor(BLACK);
                            outtextxy(450, 750, _T("最短路径长度为:     m"));
                            outtextxy(690, 750, str);

                            // 新增：输出路径
                            bar(480, 820, 1200, 850);  // 创建一个矩形来覆盖旧的文本
                            outtextxy(450, 790, _T("最短路径为:"));
                            int x_offset = 40;  // 设置水平偏移量
                            int  a, b;
                            a = pos[1]; b = pos[2];
                            _stprintf_s(str, _T("%02d"), a);
                            outtextxy(480, 820, str);  // 输出第一个点
                            while (pathh[a][b] != b)
                            {
                                _stprintf_s(str, _T("->%02d"), pathh[a][b]);
                                outtextxy(480 + x_offset, 820, str);  // 在下方输出路径
                                x_offset += 60;  // 更新偏移量
                                a = pathh[a][b];
                            }
                            _stprintf_s(str, _T("->%02d"), b);
                            outtextxy(480 + x_offset, 820, str);  // 输出最后一个点

                            clickCount = 0;  // 重置点击次数
                        }
                        break;
                    }
                }
                break;
            default:
                break;
            }
        }
    }
	return 0;
}

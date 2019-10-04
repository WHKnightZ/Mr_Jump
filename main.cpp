#include <conio.h>
#include <fstream>
#include <graphics.h>
#include <time.h>

#define MAXX 490
#define MAXY 680
#define BGC 11

int Score, Gold, Time, TotalGold, Cost;
char str[20];

char TxtHighScore[] = "321";
char TxtMrJump[] = "Mr Jump";
char TxtByKnightZ[] = "By KnightZ";
char TxtGameOver[] = "Game Over";

struct Struct_Foot {
    int x, y;
} Foot[] = {{4, 0}, {7, 4}, {8, 5}};

class Class_Hero {
  private:
    int x, y;

  public:
    int IsJump;
    void Init(int x, int y, int IsJump) {
        this->x = x;
        this->y = y;
        this->IsJump = IsJump;
    }
    void SetY(int y) { this->y += y; }
    void Draw();
    void Clear();
};

void Class_Hero::Draw() {
    setlinestyle(0, 0, 2);
    setcolor(0);
    circle(x, y - 40, 5);
    line(x, y - 35, x, y - 20);
    line(x, y - 32, x - 7, y - 20);
    line(x, y - 32, x + 7, y - 20);
    line(x, y - 20, x - Foot[IsJump].x, y - Foot[IsJump].y);
    line(x, y - 20, x + Foot[IsJump].x, y - Foot[IsJump].y);
    setlinestyle(0, 0, 1);
}

void Class_Hero::Clear() {
    setlinestyle(0, 0, 2);
    setcolor(BGC);
    circle(x, y - 40, 5);
    line(x, y - 35, x, y - 20);
    line(x, y - 32, x - 7, y - 20);
    line(x, y - 32, x + 7, y - 20);
    line(x, y - 20, x - Foot[IsJump].x, y - Foot[IsJump].y);
    line(x, y - 20, x + Foot[IsJump].x, y - Foot[IsJump].y);
    setlinestyle(0, 0, 1);
}

class Class_Platform {
  private:
    int x, y;

  public:
    int Status;
    void Init(int x, int y, int Status) {
        this->x = x;
        this->y = y;
        this->Status = Status;
    }
    void Update(int x, int y);
    void Draw();
    void Clear();
    void ClearExtra();
};

void Class_Platform::Update(int x, int y) {
    this->x -= x;
    this->y += y;
}

void Class_Platform::Draw() {
    if (Status > 2) {
        setcolor(1);
        line(x - 1, MAXY, x - 1, y - 1);
        line(x - 1, y - 1, x + 49, y - 1);
        line(x + 48, y, x + 48, MAXY + 1);
        setfillstyle(1, 3);
        bar(x, y, x + 48, MAXY + 1);
        switch (Status) {
        case 3:
            setlinestyle(0, 0, 2);
            setcolor(2);
            circle(x + 24, y - 30, 15);
            setfillstyle(1, 7);
            floodfill(x + 24, y - 30, 2);
            setcolor(0);
            line(x + 24, y - 28, x + 24, y - 41);
            line(x + 24, y - 28, x + 32, y - 36);
            setlinestyle(0, 0, 1);
            break;
        case 4:
            setcolor(15);
            setlinestyle(0, 0, 2);
            circle(x + 24, y - 30, 16);
            setfillstyle(1, 14);
            floodfill(x + 24, y - 30, 15);
            circle(x + 24, y - 30, 11);
            setlinestyle(0, 0, 1);
            break;
        }
    }
}

void Class_Platform::Clear() {
    if (Status > 2) {
        setfillstyle(1, BGC);
        bar(x - 1, y - 1, x + 49, MAXY + 1);
        if (Status == 3 || Status == 4) {
            setcolor(BGC);
            pieslice(x + 24, y - 30, 0, 360, 17);
        }
    }
}

void Class_Platform::ClearExtra() {
    setfillstyle(1, BGC);
    setcolor(BGC);
    pieslice(x + 24, y - 30, 0, 360, 17);
}

void BackGround() {
    setfillstyle(1, BGC);
    bar(0, 0, MAXX + 1, MAXY + 1);
}

void ImportTotalGold() {
    std::ifstream f;
    f.open("Gold.txt");
    f >> TotalGold;
    f.close();
}

void ExportTotalGold() {
    std::ofstream f;
    f.open("Gold.txt");
    f << TotalGold;
    f.close();
}

void FrameScore(int x, int y, int r) {
    setlinestyle(0, 0, 2);
    setcolor(2);
    line(x - 5 * r, y - 3 * r, x + 5 * r, y - 3 * r);
    line(x - 5 * r, y + 3 * r, x + 5 * r, y + 3 * r);
    line(x - 6 * r, y - 2 * r, x - 6 * r, y + 2 * r);
    line(x + 6 * r, y - 2 * r, x + 6 * r, y + 2 * r);
    arc(x + 5 * r, y - 2 * r, 0, 90, r);
    arc(x - 5 * r, y - 2 * r, 90, 180, r);
    arc(x - 5 * r, y + 2 * r, 180, 270, r);
    arc(x + 5 * r, y + 2 * r, 270, 360, r);
    setfillstyle(1, 15);
    floodfill(x, y, 2);
    setlinestyle(0, 0, 1);
}

void InitFrameScore() {
    FrameScore(100, 50, 8);
    FrameScore(245, 50, 8);
    FrameScore(390, 50, 8);
    setcolor(9);
    setfillstyle(1, 10);
    for (int i = 0; i < 3; i++) {
        rectangle(62 + i * 11, 52 - i * 10, 70 + i * 11, 65);
        bar(63 + i * 11, 53 - i * 10, 70 + i * 11, 65);
    }
    setcolor(2);
    circle(220, 50, 15);
    setfillstyle(1, 7);
    floodfill(220, 50, 2);
    setcolor(0);
    line(220, 52, 220, 39);
    line(220, 52, 228, 44);
    setcolor(14);
    circle(365, 50, 15);
    setfillstyle(1, 14);
    floodfill(365, 50, 14);
    setcolor(15);
    circle(365, 50, 11);
    settextstyle(10, 0, 3);
    setbkcolor(15);
    setcolor(5);
    outtextxy(100, 38, TxtHighScore);
}

void UpdateScore() {
    sprintf(str, "%d", Score);
    settextstyle(10, 0, 5);
    setbkcolor(BGC);
    setcolor(2);
    outtextxy(235, 110, str);
}

void UpdateGold() {
    sprintf(str, "%2d", Gold);
    settextstyle(10, 0, 3);
    setbkcolor(15);
    setcolor(2);
    outtextxy(393, 38, str);
}

void UpdateTime() {
    sprintf(str, "%2d", Time / 32);
    settextstyle(10, 0, 3);
    setbkcolor(15);
    setcolor(9);
    outtextxy(248, 38, str);
}

int Revive() {
    FrameScore(245, 260, 30);
    setcolor(0);
    setlinestyle(0, 0, 2);
    circle(170, 220, 34);
    setlinestyle(0, 0, 1);
    setfillstyle(1, 13);
    setcolor(5);
    setbkcolor(15);
    settextstyle(10, 0, 3);
    sprintf(str, "Gold: %d", TotalGold);
    outtextxy(250, 205, str);
    setcolor(1);
    sprintf(str, "Cost %d: +30s", Cost);
    outtextxy(150, 280, str);
    setcolor(13);
    int a = 90;
    while (a != -270) {
        if (kbhit()) {
            if (getch() == 13)
                return 1;
            return 0;
        }
        pieslice(170, 220, a - 4, a, 30);
        a -= 4;
        delay(40);
    }
    return 0;
}

void Logo() {
    setbkcolor(BGC);
    settextstyle(10, 0, 8);
    setcolor(5);
    outtextxy(85, 195, TxtMrJump);
    settextstyle(8, 0, 3);
    setcolor(9);
    outtextxy(205, 275, TxtByKnightZ);
}

int main() {
    srand(time(0));
    initwindow(MAXX + 9, MAXY + 13);
    ImportTotalGold();
    BackGround();
    Class_Hero Hero;
    Class_Platform Platform[9];
    Hero.Init(94, 582, 0);
    Hero.Draw();
    int Current, Current2, c, drt, t, mx, my, Game;
    Platform[0].Init(10, 620, 5);
    Platform[0].Draw();
    Platform[1].Init(70, 584, 5);
    Platform[1].Draw();
    Platform[2].Init(130, 548, rand() % 8);
    Platform[2].Draw();
    Current = 2;
    Score = 0;
    Gold = 0;
    Time = 1920;
    Cost = 60;
    InitFrameScore();
    UpdateTime();
    UpdateGold();
    while (Current < 7) {
        if (Platform[Current].Status > 2) {
            Current++;
            Platform[Current].Init(10 + 60 * Current, 620 - 36 * Current, rand() % 9);
            Platform[Current].Draw();
        } else {
            Current++;
            Platform[Current].Init(10 + 60 * Current, 620 - 36 * Current, rand() % 6 + 3);
            Platform[Current].Draw();
        }
    }
    Logo();
    getch();
    setfillstyle(1, BGC);
    setcolor(BGC);
    int x, y;
    for (int i = 0; i < 36; i++) {
        if (kbhit())
            getch();
        x = 70 + i % 12 * 30;
        y = 210 + i / 12 * 30;
        bar(x, y, x + 30, y + 30);
        delay(40);
    }
    UpdateScore();
    do {
        while (true) {
            if (kbhit()) {
                c = getch();
                if (!Hero.IsJump) {
                    switch (c) {
                    case 97:
                        Hero.Clear();
                        Hero.IsJump = 1;
                        drt = -12;
                        t = 0;
                        mx = 5;
                        my = 3;
                        break;
                    case 100:
                        Hero.Clear();
                        Hero.IsJump = 2;
                        drt = -12;
                        t = 0;
                        mx = 10;
                        my = 6;
                        break;
                    }
                }
            }
            if (Hero.IsJump) {
                if (t == 0 || (Hero.IsJump == 2 && t == 6)) {
                    if (Platform[Current].Status > 2) {
                        Current++;
                        if (Current == 9)
                            Current = 0;
                        Platform[Current].Init(490, 332, rand() % 9);
                        Platform[Current].Draw();
                    } else {
                        Current++;
                        if (Current == 9)
                            Current = 0;
                        Platform[Current].Init(490, 332, rand() % 6 + 3);
                        Platform[Current].Draw();
                    }
                }
                for (int i = 0; i < 9; i++) {
                    Platform[i].Clear();
                    Platform[i].Update(mx, my);
                    Platform[i].Draw();
                }
                Hero.Clear();
                Hero.SetY(drt);
                Hero.Draw();
                t++;
                if (t == 6)
                    drt = -drt;
                else if (t == 9) {
                    Current2 = Current - 6;
                    if (Current2 < 0)
                        Current2 += 9;
                    if (Platform[Current2].Status > 2) {
                        switch (Platform[Current2].Status) {
                        case 3:
                            Platform[Current2].Status = 5;
                            Platform[Current2].ClearExtra();
                            Time += 32;
                            UpdateTime();
                            break;
                        case 4:
                            Platform[Current2].Status = 5;
                            Platform[Current2].ClearExtra();
                            Gold++;
                            UpdateGold();
                            break;
                        }
                    }
                } else if (t == 12) {
                    if (Platform[Current2].Status > 2) {
                        Score += Hero.IsJump;
                        UpdateScore();
                        Hero.Clear();
                        Hero.IsJump = 0;
                        Hero.Draw();
                    } else {
                        for (int i = 0; i < 10; i++) {
                            Hero.Clear();
                            Hero.SetY(15);
                            Hero.Draw();
                            delay(30);
                        }
                        break;
                    }
                }
            }
            Time--;
            if (Time % 32 == 0)
                UpdateTime();
            if (Time == 0)
                break;
            delay(30);
        }
        TotalGold += Gold;
        if (TotalGold >= Cost) {
            if (Revive()) {
                TotalGold -= Cost;
                ExportTotalGold();
                Game = 1;
                Cost += 30;
                Time = 960;
                Hero.Clear();
                Hero.Init(94, 582, 0);
                Hero.Draw();
                Current2 = Current - 6;
                if (Current2 < 0)
                    Current2 += 9;
                if (Platform[Current2].Status <= 2) {
                    Platform[Current2].Status = 5;
                    Platform[Current2].Draw();
                }
                setfillstyle(1, BGC);
                bar(60, 150, 430, 352);
            } else
                Game = 0;
        } else
            Game = 0;
    } while (Game);
    setfillstyle(1, BGC);
    bar(60, 150, 430, 352);
    ExportTotalGold();
    FrameScore(245, 260, 25);
    settextstyle(8, 0, 5);
    setcolor(12);
    setbkcolor(15);
    outtextxy(135, 235, TxtGameOver);
    getch();
    closegraph();
    return 0;
}

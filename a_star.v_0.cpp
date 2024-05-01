#include <bits/stdc++.h>
#include <graphics.h>

using namespace std;

const int WIDTH = 620;
const int HEIGHT = 460;
const int CELL_SIZE = 20;

int SOURCE_X, SOURCE_Y;
int DESTINATION_X, DESTINATION_Y;

vector<pair<int, int> > OBSTACLES;

void initSource(int X, int Y) {
    setfillstyle(SOLID_FILL, RED);
    setcolor(RED);
    // Draw the rectangle at position (15, 10)
    int posX = X * CELL_SIZE;
    int posY = Y * CELL_SIZE;
    rectangle(posX, posY, posX + CELL_SIZE, posY + CELL_SIZE);
    floodfill(posX + 1, posY + 1, RED);
}

void initDestination(int X, int Y) {
    setfillstyle(SOLID_FILL, BLUE);
    setcolor(BLUE);
    // Draw the rectangle at position (15, 10)
    int posX = X * CELL_SIZE;
    int posY = Y * CELL_SIZE;
    rectangle(posX, posY, posX + CELL_SIZE, posY + CELL_SIZE);
    floodfill(posX + 1, posY + 1, BLUE);
}

void initObstacles() {

    setfillstyle(SOLID_FILL, BROWN);
    setcolor(BROWN);

    for (int i = 0; i < OBSTACLES.size(); i++) {
        int posX = OBSTACLES[i].first * CELL_SIZE;
        int posY = OBSTACLES[i].second * CELL_SIZE;
        rectangle(posX, posY, posX + CELL_SIZE, posY + CELL_SIZE);
        floodfill(posX + 1, posY + 1, BROWN);
    }

}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    for (int i = 0; i < WIDTH; i += CELL_SIZE) {
        for (int j = 0; j < HEIGHT; j += CELL_SIZE) {
            // Draw a rectangle for each cell
            rectangle(i, j, i + CELL_SIZE, j + CELL_SIZE);
        }
    }

    // initializing source
    SOURCE_X = 0;
    SOURCE_X = 0;
    initSource(SOURCE_X, SOURCE_Y);

    // delay(2000);

    // initializing destination
    DESTINATION_X = 30;
    DESTINATION_Y = 22;
    initDestination(DESTINATION_X, DESTINATION_Y);


    // initializing obstacles
    OBSTACLES.push_back(make_pair(2, 4));
    OBSTACLES.push_back(make_pair(5, 11));
    OBSTACLES.push_back(make_pair(2, 19));
    OBSTACLES.push_back(make_pair(5, 17));
    OBSTACLES.push_back(make_pair(7, 13));
    OBSTACLES.push_back(make_pair(12, 7));
    OBSTACLES.push_back(make_pair(19, 11));
    OBSTACLES.push_back(make_pair(3, 17));
    initObstacles();


    getch();
    closegraph();
    return 0;
}

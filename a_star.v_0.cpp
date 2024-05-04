#include <bits/stdc++.h>
#include <graphics.h>
#include <cstdlib>
#include <ctime>

using namespace std;

#define int long long

const int WIDTH = 620;
const int HEIGHT = 460;
const int CELL_SIZE = 5;
const int SOURCE = 1;
const int DESTINATION = 2;
const int OBSTACLE = 0;
const int ROW = HEIGHT / CELL_SIZE;
const int COL = WIDTH / CELL_SIZE;

int SOURCE_X, SOURCE_Y;
int DESTINATION_X = 0, DESTINATION_Y = 0;

struct Cell{
    int data = -1;
    int px = -1;
    int py = -1;
    bool visited = false;
};

struct ComparePairs {
    bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs) const {
        //return abs(lhs.first - DESTINATION_X) + abs(lhs.second - DESTINATION_Y) < abs(rhs.first - DESTINATION_X) + abs(rhs.second - DESTINATION_Y);

        int sourceDistanceLHS = sqrt((lhs.first - SOURCE_X) * (lhs.first - SOURCE_X) + (lhs.second - SOURCE_Y) * (lhs.second - SOURCE_Y));
        int destinationDistanceLHS = sqrt((lhs.first - DESTINATION_X) * (lhs.first - DESTINATION_X) + (lhs.second - DESTINATION_Y) * (lhs.second - DESTINATION_Y));

        int sourceDistanceRHS = sqrt((rhs.first - SOURCE_X) * (rhs.first - SOURCE_X) + (rhs.second - SOURCE_Y) * (rhs.second - SOURCE_Y));
        int destinationDistanceRHS = sqrt((rhs.first - DESTINATION_X) * (rhs.first - DESTINATION_X) + (rhs.second - DESTINATION_Y) * (rhs.second - DESTINATION_Y));

        return sourceDistanceLHS + destinationDistanceLHS > sourceDistanceRHS + destinationDistanceRHS;
    }
};

vector<pair<int, int> > OBSTACLES;
vector<pair<int, int> > directions;

Cell adj[ROW][COL];

void initSource(int X, int Y) {
    setfillstyle(SOLID_FILL, RED);
    setcolor(RED);
    // Draw the rectangle at position (15, 10)
    int posX = X * CELL_SIZE;
    int posY = Y * CELL_SIZE;
    rectangle(posX, posY, posX + CELL_SIZE, posY + CELL_SIZE);
    floodfill(posX + 1, posY + 1, RED);
    adj[Y][X].data = SOURCE;
}

void initDestination(int X, int Y) {
    setfillstyle(SOLID_FILL, BLUE);
    setcolor(BLUE);
    // Draw the rectangle at position (15, 10)
    int posX = X * CELL_SIZE;
    int posY = Y * CELL_SIZE;
    rectangle(posX, posY, posX + CELL_SIZE, posY + CELL_SIZE);
    floodfill(posX + 1, posY + 1, BLUE);
    adj[Y][X].data = DESTINATION;
}

void initObstacles() {

    setfillstyle(SOLID_FILL, BROWN);
    setcolor(BROWN);

    for (int i = 0; i < OBSTACLES.size(); i++) {
        int posX = OBSTACLES[i].first * CELL_SIZE;
        int posY = OBSTACLES[i].second * CELL_SIZE;
        rectangle(posX, posY, posX + CELL_SIZE, posY + CELL_SIZE);
        floodfill(posX + 1, posY + 1, BROWN);
        adj[OBSTACLES[i].second][OBSTACLES[i].first].data = OBSTACLE;
    }

}

void colorVisitedCell(int X, int Y) {
    setfillstyle(SOLID_FILL, MAGENTA);
    setcolor(MAGENTA);
    // Draw the rectangle at position (15, 10)
    int posX = X * CELL_SIZE;
    int posY = Y * CELL_SIZE;
    rectangle(posX, posY, posX + CELL_SIZE, posY + CELL_SIZE);
    floodfill(posX + 2, posY, MAGENTA);
}

void aStarSearch(int s_x, int s_y, int d_x, int d_y) {

    priority_queue<pair<int, int>, vector<pair<int, int> >, ComparePairs> pq;
    //queue<pair<int, int> > pq;
    bool flag = false;

    pq.push(make_pair(s_x, s_y));
    adj[s_y][s_x].visited = true;

    while (pq.size() > 0 && flag == false) {
        //pair<int, int> p = pq.front();
        pair<int, int> p = pq.top();
        pq.pop();

        for (int i = 0; i < directions.size(); i++) {
            int new_x = p.first + directions[i].first;
            int new_y = p.second + directions[i].second;

            if (new_x < 0 || new_x >= COL || new_y < 0 || new_y >= ROW || adj[new_y][new_x].visited || adj[new_y][new_x].data == OBSTACLE) {
                continue;
            }

            adj[new_y][new_x].visited = true;

            adj[new_y][new_x].px = p.first;
            adj[new_y][new_x].py = p.second;

            pq.push(make_pair(new_x, new_y));

            if (new_x == DESTINATION_X && new_y == DESTINATION_Y) {
                flag = true;
                break;
            }
            colorVisitedCell(new_x, new_y);
            //delay(1);
        }
    }

    cout << "PQ: " << pq.size() << "\n";
}

void colorPath(int X, int Y) {
    setfillstyle(SOLID_FILL, GREEN);
    setcolor(GREEN);
    // Draw the rectangle at position (15, 10)
    int posX = X * CELL_SIZE;
    int posY = Y * CELL_SIZE;
    rectangle(posX, posY, posX + CELL_SIZE, posY + CELL_SIZE);
    floodfill(posX + 1, posY + 1, GREEN);
}

void drawPath() {
    int child_x = DESTINATION_X, child_y = DESTINATION_Y;
    while (child_x != -1 && child_y != -1) {
        colorPath(child_x, child_y);
        child_x = adj[child_y][child_x].px;
        child_y = adj[child_y][child_x].py;
        delay(5);
    }
}

int getRandomRow() {
    // Generate a random number within a specific range (1 to 100)
    int range_start = 1;
    int range_end = ROW - 1;
    int random_in_range = range_start + (rand() % (range_end - range_start + 1));

    return random_in_range;
}

int getRandomCol() {
    // Generate a random number within a specific range (1 to 100)
    int range_start = 1;
    int range_end = COL - 1;
    int random_in_range = range_start + (rand() % (range_end - range_start));

    return random_in_range;
}

void setObstacles() {
    //OBSTACLES.push_back(make_pair(COL - 2, ROW - 2));
    //OBSTACLES.push_back(make_pair(COL - 2 + 1, ROW - 2));
    //OBSTACLES.push_back(make_pair(COL - 2, ROW - 2 + 1));
    for (int i = 0; i < ROW * COL / 10; i++) {
        OBSTACLES.push_back(make_pair(getRandomCol(), getRandomRow()));
    }
}

void setDirections() {
    directions.push_back(make_pair(0, 1));
    directions.push_back(make_pair(1, 0));
    directions.push_back(make_pair(0, -1));
    directions.push_back(make_pair(-1, 0));
}

int32_t main() {
    int32_t gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    for (int i = 0; i < WIDTH; i += CELL_SIZE) {
        for (int j = 0; j < HEIGHT; j += CELL_SIZE) {
            // Draw a rectangle for each cell
            rectangle(i, j, i + CELL_SIZE, j + CELL_SIZE);
        }
    }

    // initializing source
    SOURCE_X = 0;
    SOURCE_Y = 0;
    initSource(SOURCE_X, SOURCE_Y);

    // delay(2000);

    // initializing destination
    DESTINATION_X = COL - 1;
    DESTINATION_Y = ROW - 1;
    initDestination(DESTINATION_X, DESTINATION_Y);

    // initializing obstacles
    setObstacles();
    initObstacles();

    // set directions
    setDirections();

    // call A* search algorithm
    aStarSearch(SOURCE_X, SOURCE_Y, DESTINATION_X, DESTINATION_Y);

    // draw the path
    drawPath();
    initDestination(DESTINATION_X, DESTINATION_Y);
    initSource(SOURCE_X, SOURCE_Y);

    //delay(5000);
    getch();
    closegraph();
    return 0;
}

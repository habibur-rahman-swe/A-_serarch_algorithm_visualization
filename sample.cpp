#include <graphics.h>
int WIDTH = 620;
int HEIGHT = 460;

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int cellSize = 20; // Adjust this value for the size of each cell

    for (int i = 0; i < WIDTH; i += cellSize) {
        for (int j = 0; j < HEIGHT; j += cellSize) {
            // Draw a rectangle for each cell
            rectangle(i, j, i + cellSize, j + cellSize);
        }
    }

    setfillstyle(SOLID_FILL, RED);
    setcolor(RED);
    // Draw the rectangle at position (15, 10)
    int posX = 15 * cellSize;
    int posY = 10 * cellSize;
    rectangle(posX, posY, posX + cellSize, posY + cellSize);
    floodfill(posX + 1, posY + 1, RED);

    getch();
    closegraph();
    return 0;
}

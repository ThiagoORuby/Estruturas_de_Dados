#include <stdio.h>
#include <stdlib.h>

// creating the Point class
typedef struct point{
    // atributes
    int x;
    int y;
    // methods instances
    void (*print)(struct point * obj);
    void (*move)(struct point * obj, int dx, int dy);
} Point;

// methods implementation
void PointPrint(struct point * obj)
{
    printf("(x : %d, y : %d)\n", obj->x, obj->y);
}

void PointMove(struct point * obj, int dx, int dy)
{
    obj->x += dx;
    obj->y += dy;
}

// constructor
Point * newPoint(int x, int y)
{
    Point * obj = malloc(sizeof(Point));
    obj->x = x;
    obj->y = y;
    obj->move = PointMove;
    obj->print = PointPrint;
    return obj;
}

void destroyPoint(Point * obj)
{
    free(obj);
}

// main
int main()
{
    Point * point = newPoint(2, 3);
    point->print(point);
    point->move(point, 2, 2);
    point->print(point);
    return 0;
}



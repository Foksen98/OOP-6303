#include <iostream>
#include "square.h"
#include "hexagon.h"
#include "ellipse.h"

int main ()
{
    Square sq(1, 1, 4);
    Hexagon hex(0, 0, 8);
    Ellipse elps(10, 10, 2, 5);

    cout << sq << endl;
    cout << hex << endl;
    cout << elps << endl;

    sq.setColor("blue");
    sq.rotate(90);

    hex.move(10, 10);

    elps.setColor("red");
    elps.scale(2);

    cout << sq << endl;
    cout << hex << endl;
    cout << elps << endl;

    return 0;
}

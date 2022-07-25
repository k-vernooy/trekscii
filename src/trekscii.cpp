#include <iostream>
#include <sys/ioctl.h>
#include "trekscii.h"

#define MIN_WIDTH 46
#define MIN_HEIGHT 16

int main(int argc, char** argv) {

    // random seeding copied from stackoverflow :)
    uint32_t seed=0;
    FILE *devrnd = fopen("/dev/random","r");
    fread(&seed, 4, 1, devrnd);
    fclose(devrnd);
    srand(seed);

    // get window size
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);

    int dimY;
    if (argc >= 2) {
        dimY = std::stoi(argv[1]);
        if (dimY < MIN_HEIGHT) {
            std::cerr << "Error: height must be at least " << MIN_HEIGHT << std::endl;
            return 1;
        }
    } else {
        // default to half terminal height, with MIN_HEIGHT min
        dimY = std::max(w.ws_row / 2, MIN_HEIGHT);
    }

    int dimX;
    if (argc >= 3) {
        dimX = std::stoi(argv[2]);
        if (dimX < MIN_WIDTH) {
            std::cerr << "Error: width must be at least " << MIN_WIDTH << std::endl;
            return 1;
        }
    } else {
        // default to half terminal width, with MIN_WIDTH min
        dimX = std::max(w.ws_col / 2, MIN_WIDTH);
    }

    Canvas canvas = Canvas(dimX, dimY - 2);
    canvas.generate();
    canvas.print();
}

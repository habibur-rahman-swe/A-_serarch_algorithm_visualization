#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    // Seed the random number generator with the current time
    srand(time(0));

    int random_number = rand();
    cout << "Random number (between 0 and RAND_MAX): " << random_number << endl;

    // Generate a random number within a specific range (1 to 100)
    int range_start = 1;
    int range_end = 100;
    int random_in_range = range_start + (rand() % (range_end - range_start + 1));
    cout << "Random number within range (" << range_start << " to " << range_end << "): " << random_in_range << endl;

    return 0;
}

#include "Quat.h"
#include <valarray>
int main(int argc, char const *argv[]) {
    std::valarray<Quat> q(4);
    for (size_t i = 0; i < 4; i++)
        q[i][i] = 1;
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++)
            std::cout << " |" << q[i] * q[j];
        std::cout << '\n';
    }
    Quat x;
    std::cout << "Enter quaternion x" << '\n';
    std::cin >> x;
    std::cout << "x: " << '\n';
    std::cout << x << '\n';
    return 0;
}

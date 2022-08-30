#include <list>
#include <iostream>
#include <vector>
#include <cmath>
#include "polsh.h"
#include "Lexeme.h"
double abs(double x) {
    if (x < 0) {
        return -x;
    } else {
        return x;
    }
}
void test() {
    std::vector<std::pair<std::string, double>> array = {{"1+2+3",                1 + 2 + 3},
                                                         {"(1+2)+2/671",          (1 + 2) + 2 / 671},
                                                         {"ln(2)*sqrt(7)",        log(2) * sqrt(7)},
                                                         {"(3-(6*6-8*1-4)-9)+1",  (3 - (6 * 6 - 8 * 1 - 4) - 9) + 1},
                                                         {"2+7*(132/sin(41))",    2 + 7 * (132. / sin(41))},
                                                         {"cos(sin(ln(sqrt(3)))", cos(sin(log(sqrt(3))))}
    };

    for (auto [in, out]: array) {
        double res = Сalculator(ToPostfix(read(in)));

        std::cout << in << "=" << res << " - " << (((res - out) < 10e-3  ) ? "ok" : "fail") << "\n";
    }
}


int main() {
    test();
    return 0;
}

#include <stdio.h>
#include <math.h>

int main(void)
{
    int test[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 14}};
    float x = 9;
    int blur = round((test[1][1] + test[1][0] + test[1][2] + test [0][1] + test[0][0] + test [0][2] + test[2][1] + test[2][0] + test[2][2]) / x);
    printf("%i\n", blur);
}

#include <stdio.h>

int get_gcd(int a, int b) {
    while (b != 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int main() {
    int n1 = 1071, n2 = 1029;
    printf("%d와 %d의 최대공약수: %d\n", n1, n2, get_gcd(n1, n2));
    return 0;
}

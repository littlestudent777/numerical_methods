#pragma warning(disable : 4996)
#include "Functions.h"
#define MAXN 2000

int main() {
	ErrAndItFromEps(MyFunc, MAXN);
	ErrFromLen(MyFunc, MAXN);
	return 0;
}
#include <iostream>
#include "LogManager.h"
#include "QueryManager.h"
#include "PageManager.h"

int main()
{
	QueryManager a;

	a.Listen();
	return 0;
}

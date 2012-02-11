#include"heap.h"

inline int PARENT(int i)
{
	return (i - 1)/2;
}

inline int LEFT(int i)
{
	return 2*i + 1;
}

inline int RIGHT(int i)
{
	return 2*i + 2;
}

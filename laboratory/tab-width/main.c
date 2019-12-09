#include	<stdio.h>
#define		ASDF 	1


struct test {
	// How these looks like?
 	unsigned 	a 		: 10;
	unsigned 	abcdef 	: 1;
	signed		foo 	: 1;
};


int main(int argc, char **argv)
{
	// What about these?
	int		a 	= 1;
	int		foo = 2;

	struct	test t;

	return	0;
}

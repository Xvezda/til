#include	<stdio.h>
#define		ASDF	1


struct	test	{
	//Howtheselookslike?
	unsigned	a		:	10;
	unsigned	abcdef	:	1;
	signed		foo		:	1;
};


int	main(int	argc,	char	**argv)
{
	//What	aboutthese?
	int	a	=	1;
	int	foo	=	2;

	struct	test	t;

	return	0;
}

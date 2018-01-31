/**
 *	print.c
 *
 *	Implementation of print functions for Windows.
 *
 *	Jeff Campbell
 *	1/31/18
 */
 
/* Includes */
#include <stdio.h>

/* Prototypes */
void gvPrint(char *pszString);

/* Local Variables */

/**
 *	void gvPrint(char *pszString)
 *
 *	Description:
 *		Wrapper function for printf().
 *
 *	Parameters:
 *		pszString = Pointer to character string
 *					(Must be null terminated)
 *
 *	Returns:
 *		N/A
 *
 */
void gvPrint(char *pszString)
{
	/* Call print function */
	printf(pszString);
}
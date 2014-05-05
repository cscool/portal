#include "contains.h"

using namespace std;

/* if a contains b. 1 or 0. */
int contains (const char * a, const char * b)
{
		  if (a == NULL || b == NULL)
		  {
					 Log("contains received bad args\n");
					 return 0;
		  }
		  unsigned int a_len = strlen(a);
		  unsigned int b_len = strlen(b);
		  if (a_len < 1 || b_len < 1)
		  {
					 Log("contains received bad args\n");
					 return 0;
		  }
		  if (a_len < b_len)
		  {
					 Log("first arg must be longer than second arg\n");
					 return 0;
		  }
		  int good = 0, j = 0;
		  for (unsigned int i = 0; i < a_len && j < b_len; i++)
		  {
					 if (a[i] != b[j])
					 {
								if ((a_len - i) < b_len)
								{
										  return 0;
								}
								good = 0;
								j = -1;
					 }
					 else
					 {
								good = 1;
					 }
					 j++;
		  }
		  return good;
}

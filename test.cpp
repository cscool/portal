#include <iostream>
#include <cstring>

using namespace std;

int contains (const char * a, const char * b);

int main(void)
{
		  char * str1, * str2;

		  while (1)
		  {
					 str1 = new char [512];
					 str2 = new char [512];

					 cout << "Enter a long string, suppposed to contain the next string you'll enter: ";
					 cin.getline(str1, 511, '\n');
					 cout << "Enter the string to search for in the previous string: ";
					 cin.getline(str2, 511, '\n');

					 if (contains(str1, str2))
					 {
								cout << "True!\n";
					 }
					 else
					 {
								cout << "False!\n";
					 }
					 delete [] str1;
					 delete [] str2;
					 str1 = str2 = NULL;
		  }

		  return 0;
}

/* if a contains b. 1 or 0. */
int contains (const char * a, const char * b)
{
		  if (a == NULL || b == NULL)
		  {
					 return 0;
		  }
		  unsigned int a_len = strlen(a);
		  unsigned int b_len = strlen(b);
		  if (a_len < 1 || b_len < 1)
		  {
					 return 0;
		  }
		  if (a_len < b_len)
		  {
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

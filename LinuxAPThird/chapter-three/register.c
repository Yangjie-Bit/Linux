#include <stdio.h>
int main()
{
  register int i,sum=0;
  for(i=0;i<10;i++)
  {
    sum+=i;
  }
  printf("%d\n",sum);
  return 0;
}

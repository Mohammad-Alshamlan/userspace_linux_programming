/*
http://how-to.linuxcareer.com/c-development-on-linux-flow-control-iv
*/

#include <stdio.h>

int main()
{
  char option;
  int number;
  
  printf("Please enter the number you want converted.\n");
  /*Please refrain from using gets() because of its
 * insecure "features" */
  scanf("%i", &number);
  
  printf("What kind of conversion do you need?\n");
  printf("Press 'o' for octal and 'x' for hexadecimal.\n");
  
  while((option = getchar()) != EOF && (option = getchar()) != '\n')
  {
    switch(option)
    {
      case 'o':
        printf("The number in octal is 0%o.\n", number);
        break;
      case 'x':
        printf("The number in hex is 0x%x.\n", number);
        break;
      default:
        printf("Option not valid.\n");
  break;
    }
  }
  return 0;
}

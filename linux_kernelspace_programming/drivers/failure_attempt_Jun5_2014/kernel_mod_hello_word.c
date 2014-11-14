/*
 * source http://www.freesoftwaremagazine.com/articles/drivers_linux
 */
 


#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("Dual BSD/GPL");

static int hello_init(void) {
  printk("<1> Hello world!\n");
  return 0;
}

static void hello_exit(void) {
  printk("<1> Bye, cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);

/*
// note:
The actual functions hello_init and hello_exit can be given any name desired. However, in order for them to be identified as the corresponding loading and removing functions, they have to be passed as parameters to the functions module_init and module_exit.
*/

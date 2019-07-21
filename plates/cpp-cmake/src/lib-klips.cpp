/*#############################################################################
## Author: Shaun Reed							     ##
## Legal: All Content (c) 2019 Shaun Reed, all rights reserved	 	     ##
##									     ##
## Contact: shaunrd0@gmail.com	| URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
*/

#include <lib-klips.hpp>
#include <iostream>

void PrintHello(int n) {
	while (n) {
		std::cout << n << ". " << "Hello World!" << std::endl;
		--n;
	};
}


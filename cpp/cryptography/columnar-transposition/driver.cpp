/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved                ##
## About: An example of using columnar transposition cipher                   ##
## + Using concept at www.braingle.com/brainteasers/codes/columnartrans.php   ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
*/

#include "lib-cipher.hpp"

#include<iostream>

// Columnar transposition cipher
// https://www.braingle.com/brainteasers/codes/columnartrans.php#form
// NOTE: Must check the 'irregular case' box to produce same results
// + I only used the irregular case to encrypt and decrypt
// + I did not write any code for testing with the regular case


/******************************************************************************/
// Main program loop
int main (const int argc, const char * argv[]) {
  // Left some test cases I used commented out :)

  // Using example keyword from www.braingle.com
  // + The embedded example there doesn't seem to support numbers in keywords :(
  CipherData cData("ZEBRAS");

  // Taking user input for keyword using CipherData ctor
//  CipherData cData;

  int choice = 0;
  bool exit = false;
  std::string message; // Message to encrypt or decrypt
  while (!exit) {

    std::string result;
    switch (choice) {
      case 1:
        std::cout << "\nEncrypting...\n";

        // Encrypt example from www.braingle.com
        result = cData.Encrypt("WEAREDISCOVEREDFLEEATONCE");

        // Take input for encrypting a message
//        result = cData.Encrypt();

        std::cout << "Encrypted message: " << result << std::endl;
        exit = true;
        break;

      case 2:
        std::cout << "\nDecrypting...\n";

        // Encrypt, decrypt example from www.braingle.com
        result = cData.Decrypt(cData.Encrypt("WEAREDISCOVEREDFLEEATONCE"));

        // Take input for previously encrypted message to decrypt
//        result = cData.Decrypt();

        std::cout << "Decrypted message: " << result << std::endl;
        exit = true;
        break;

      default:
        std::cout << "What would you like to do?\n1. Encrypt\n2. Decrypt\n";
        // Take input, handle it accordingly
        // + https://www.cplusplus.com/forum/general/207458/
        if (!(std::cin >> choice)) {
          std::cout << "Invalid character input, choose an option below\n";
        }
        else if (choice != 1 && choice != 2) {
          std::cout << "Incorrect option entered (" << choice << ")\n";
        }
        std::cin.clear();
        std::cin.ignore();
        break;
    }

  }

  return 0;
}

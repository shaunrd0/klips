/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved                ##
## About: An example of using columnar transposition cipher                   ##
## + Using concept at www.braingle.com/brainteasers/codes/columnartrans.php   ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
*/

#ifndef COLUMNARTRANSPOSITION_LIB_CIPHER_HPP
#define COLUMNARTRANSPOSITION_LIB_CIPHER_HPP

#include <iostream>
#include<algorithm>
#include<vector>

/******************************************************************************/
// CipherData struct to hold data and methods related to encrypting / decrypting
struct CipherData {
  // Can't create this object without providing a keyWord to initialize order
  explicit CipherData(std::string keyWord) : keyWord_(std::move(keyWord))
  {
    InitOrder(keyWord_);
  }
  CipherData() : keyWord_(GetKey()) { InitOrder(keyWord_);}

  /****************************************************************************/
  // Member functions

  // Initializes orderVect, pass by value to create local copy of keyWord
  void InitOrder(std::string temp);

  static std::string GetKey();

  static void
  Transpose(const std::vector<std::string> &in, std::vector<std::string> &out);

  // Default values for param allows calling with no message
  std::string Encrypt(std::string message="");
  std::string Decrypt(std::string message="");

private:
  // Used to make a valid keyword from an invalid keyWord
  // + Still encrypts / decrypts with whatever the user inputs as keyWord
  // + But technically the keyword is modified without the user knowing :)
  void ValidateKeyword(const std::string &message);

  std::string keyWord_;
  std::vector<int> orderVect_;
};

#endif // COLUMNARTRANSPOSITION_LIB_CIPHER_HPP

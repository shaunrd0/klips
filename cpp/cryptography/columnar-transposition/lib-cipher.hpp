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
// KeyData struct to hold data related to key ciphers
struct KeyData {
  explicit KeyData(std::string key) : keyWord_(std::move(key)) {};
  explicit KeyData() : keyWord_(GetKey()) {};
  // Pure virtual dtor to make abstract class despite no pure virtual members
  virtual ~KeyData() = 0;

  // Allows getting keyWord when using KeyData default ctor
  static std::string GetKey()
  {
    std::string key;
    std::cout << "Enter the keyword: ";
    std::getline(std::cin, key);
    std::cout << "Keyword entered: \"" << key << "\"\n";
    return key;
  }

protected:
  std::string keyWord_;
};
// Definition of pure virtual dtor

/******************************************************************************/
// Columnar struct to define methods related to columnar transposition
struct Columnar : KeyData {
  // Can't create this object without providing a keyWord to initialize order
  explicit Columnar(std::string keyWord) : KeyData(std::move(keyWord))
  {
    InitOrder(keyWord_);
  }
  // Inherit call to GetKey() from KeyData default ctor
  Columnar() { InitOrder(keyWord_);}

  // Initializes orderVect to determine order columns should be used
  void InitOrder(std::string temp);


  /****************************************************************************/
  // Member function definitions

  void ValidateKeyword(const std::string &message);

  // Transpose a character matrix, using a vector of strings
  static void Transpose(const std::vector<std::string> &in,
                        std::vector<std::string> &out);

  // Default parameter allows calling Encrypt() to take message input
  std::string Encrypt(std::string message="");
  // Default parameter allows calling Decrypt() to take message input
  std::string Decrypt(std::string message="");

private:
  std::vector<int> orderVect_;
};

#endif // COLUMNARTRANSPOSITION_LIB_CIPHER_HPP

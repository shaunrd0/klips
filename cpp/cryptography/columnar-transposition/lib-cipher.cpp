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

// Initializes orderVect to determine order columns should be used
void CipherData::InitOrder(std::string temp)
{
  // Create a temp value sorted lexicographically, remove duplicate characters
  // https://en.cppreference.com/w/cpp/string/basic_string/operator_cmp
  std::sort(temp.begin(), temp.end());
  auto it = std::unique(temp.begin(), temp.end());
  temp.erase(it, temp.end());

  // Step through each character in lexicographic order
  for (int i = 0; i < temp.size(); i++) {
    // Check each character in the keyWord for the current lexicographic char
    for (int j = 0; j < keyWord_.size(); j++) {
      // If they are equal, push the index of the char in keyWord to orderVect
      if (keyWord_[j] == temp[i]) {
        orderVect_.push_back(j);
      }
    }
  }

}

// Allows getting keyWord when using CipherData default ctor
std::string CipherData::GetKey()
{
  std::string key;
  std::cout << "Enter the keyword: ";
  std::getline(std::cin, key);
  std::cout << "Keyword entered: " << key << std::endl;
  return key;
}

// Transpose a character matrix, using a vector of strings
void CipherData::Transpose(const std::vector<std::string> &in,
                           std::vector<std::string> &out)
{
  int cols = in[0].size();
  // JIC some other row is larger than the first
  for (const auto &row : in) cols = (row.size() > cols) ? row.size() : cols;
  int rows = in.size();

  out.resize(cols);

  for (int i = 0; i < cols; i++) {
    for (int j = 0; j < rows; j++) {
      if (in[j].size() <= i) continue;
      out[i] += in[j][i];
    }
  }
}

std::string CipherData::Encrypt(std::string message)
{
  // If no message was provided, ask for one
  if (message.empty()) {
    std::cout << "Input message to encrypt: ";
    std::getline(std::cin, message);
    std::cout << "Encrypting message \"" << message << "\"\n";
  }
  std::string encryptedMessage;
  std::vector<std::string> rows;

  // Split the message into rows equal to the length of our keyWord
  for (size_t i = 0; i < message.size(); i+=keyWord_.size()) {
    std::string substr = message.substr(i, keyWord_.size());
    rows.push_back(substr);
  }

  // Transpose the matrix of characters
  std::vector<std::string> transposed;
  Transpose(rows, transposed);

  // Append each row of the transposed matrix to our encryptedMessage
  for (const auto &val : orderVect_) encryptedMessage += transposed[val];
  return encryptedMessage;
}

std::string CipherData::Decrypt(std::string message)
{
  // If no message was provided, ask for one
  if (message.empty()) {
    std::cout << "Input message to decrypt: ";
    std::getline(std::cin, message);
    std::cout << "Decrypting message \"" << message << "\"\n";
  }
  std::string result;
  std::vector<std::string> rows;

  // Split the message into rows equal to the length of our keyWord
  int rowLength = message.size() / keyWord_.size();
  // If dividing message and keyword size has a remainder N
  // + There will be N rows with +1 characters
  int fullRows = message.size() % keyWord_.size();

  rows.resize(orderVect_.size());
  // Track the ending position after each substring is taken
  int lastPos = 0;
  for (int i = 0; i < orderVect_.size(); i++) {
    // If we are assigning to any row < fullRows, it should have + 1 character
    if (orderVect_[i] < fullRows) {
      rows[orderVect_[i]] = message.substr(lastPos, rowLength + 1);
      lastPos += rowLength + 1;
    }
    else {
      rows[orderVect_[i]] = message.substr(lastPos, rowLength);
      lastPos += rowLength;
    }
  }

  std::vector<std::string> transposed;
  Transpose(rows, transposed);

  for (const auto &row : transposed) result += row;
  return  result;
}

#include <iostream>
#include <algorithm>
#include <cctype>

using namespace std;
void encrypt(string&, string&, string&);
void decrypt(string&, string&, string&);
char getEncryptedText(char p, char k);
char getDecryptedText(char p, char k);
string decryptionKey(string&, string&);

int main() {
    string input;
    string key;
    string encryptedText;
    string decryptedText;

    cout << "Enter secret message: ";
    getline(cin, input);
    cout << "Enter key (longer than message): ";
    getline(cin, key);

    input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());
    key.erase(remove_if(key.begin(), key.end(), ::isspace), key.end());

    if (key.length() < input.length()) {
        cout << "The encryption key must be longer than the message." << endl;
        return 1;
    }

    encrypt(input, key, encryptedText);

    cout << "\nThe encrypted text is:" << endl;
    cout << encryptedText << endl;

    decrypt(encryptedText, key, decryptedText);

    cout << "\nThe decrypted text is:" << endl;
    cout << decryptedText << endl;

    return 0;
}

void encrypt(string &input, string &key, string &encryptedText) {
    encryptedText = "";
    for (size_t i = 0; i < input.length(); ++i) {
        if (isalpha(input[i])) {
            encryptedText += getEncryptedText(tolower(input[i]), tolower(key[i % key.length()]));
        }
    }
}

char getEncryptedText(char p, char k) {
    return ((p - 'a') + (k - 'a')) % 26 + 'a';
}

void decrypt(string &encryptedText, string &key, string &decryptedText) {
    string decryptedKey = decryptionKey(key, encryptedText);
    decryptedText = "";
    for (size_t i = 0; i < encryptedText.length(); ++i) {
        if (isalpha(encryptedText[i])) {
            decryptedText += getDecryptedText(tolower(encryptedText[i]), tolower(decryptedKey[i]));
        }
    }
}

char getDecryptedText(char p, char k) {
    int decryptedText = (p - 'a') - (k - 'a');
    if (decryptedText < 0)
        decryptedText += 26;
    return decryptedText % 26 + 'a';
}

string decryptionKey(string &key, string &encryptedText) {
    string decryptedKey;
    for (size_t i = 0; i < encryptedText.length(); ++i) {
        decryptedKey += key[i % key.length()];
    }
    return decryptedKey;
}

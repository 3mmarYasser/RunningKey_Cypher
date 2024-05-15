#include <iostream>
#include <algorithm>
#include <cctype>

using namespace std;

void encrypt(string&, string&, string&);
void decrypt(string&, string&, string&);
char getEncryptedText(char p, char k);
char getDecryptedText(char p, char k);
string decryptionKey(string&, string&);
string decryptMessage(string&, string&);

int main() {
    string input;
    string key;
    string encryptedText;
    string decryptedText;
    char choice;

    do {
        cout << "\nOptions:" << endl;
        cout << "1. Encrypt" << endl;
        cout << "2. Decrypt" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                cout << "Enter secret message: ";
                cin.ignore();
                getline(cin, input);
                cout << "Enter key (longer than message): ";
                getline(cin, key);

                key.erase(remove_if(key.begin(), key.end(), ::isspace), key.end());

                if (key.length() < input.length()) {
                    cout << "The encryption key must be longer than the message." << endl;
                    break;
                }

                encrypt(input, key, encryptedText);
                cout << "\nThe encrypted text is:" << endl;
                cout << encryptedText << endl;
                break;

            case '2':
                cout << "Enter encrypted message: ";
                cin.ignore(); // Clear the newline character from the input buffer
                getline(cin, input);
                cout << "Enter key: ";
                getline(cin, key);

                key.erase(remove_if(key.begin(), key.end(), ::isspace), key.end());

                if (key.length() < input.length()) {
                    cout << "The decryption key must be longer than the message." << endl;
                    break;
                }

                decryptedText = decryptMessage(input, key);
                cout << "\nThe decrypted text is:" << endl;
                cout << decryptedText << endl;
                break;

            case '3':
                cout << "Exiting the program." << endl;
                break;

            default:
                cout << "Invalid choice. Please enter a valid option (1, 2, or 3)." << endl;
        }
    } while (choice != '3');

    return 0;
}

void encrypt(string &input, string &key, string &encryptedText) {
    encryptedText = "";
    size_t keyIndex = 0;
    for (size_t i = 0; i < input.length(); ++i) {
        if (isalpha(input[i])) {
            encryptedText += getEncryptedText(tolower(input[i]), tolower(key[keyIndex % key.length()]));
            keyIndex++;
        } else {
            encryptedText += input[i];
        }
    }
}

char getEncryptedText(char p, char k) {
    return ((p - 'a') + (k - 'a')) % 26 + 'a';
}

void decrypt(string &encryptedText, string &key, string &decryptedText) {
    string decryptedKey = decryptionKey(key, encryptedText);
    decryptedText = "";
    size_t keyIndex = 0;
    for (size_t i = 0; i < encryptedText.length(); ++i) {
        if (isalpha(encryptedText[i])) {
            decryptedText += getDecryptedText(tolower(encryptedText[i]), tolower(decryptedKey[keyIndex % decryptedKey.length()]));
            keyIndex++;
        } else {
            decryptedText += encryptedText[i];
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
    size_t keyIndex = 0;
    for (size_t i = 0; i < encryptedText.length(); ++i) {
        if (isalpha(encryptedText[i])) {
            decryptedKey += key[keyIndex % key.length()];
            keyIndex++;
        }
    }
    return decryptedKey;
}

string decryptMessage(string &encryptedText, string &key) {
    string decryptedText;
    decrypt(encryptedText, key, decryptedText);
    return decryptedText;
}

#include <iostream>
#include <fstream>
#include "interface_template.cpp"

int main() {
    PhoneBook phone_book;
    phone_book.readRecordsFromFile("Details_new.txt");

    std::vector<PhoneRecord*> contacts = phone_book.fetchContacts(new std::string("Akshay Trivedi"));

    std::ofstream resultFile("test_results.txt", std::ios::app);

    if (contacts.empty()) {
        std::cout << "test_fetch_nonexistent_contact: Passed" << std::endl;
        resultFile << "passed, test_fetch_nonexistent_contact" << std::endl;
    } else {
        std::cerr << "test_fetch_nonexistent_contact: Failed" << std::endl;
        resultFile << "failed, test_fetch_nonexistent_contact" << std::endl;
    }

    resultFile.close();

    return 0;
}

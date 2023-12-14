#include <iostream>
#include <fstream>
#include "interface_template.cpp"

int main() {
    PhoneBook phone_book;
    phone_book.readRecordsFromFile("Details_new.txt");

    std::vector<PhoneRecord*> contacts = phone_book.fetchContacts(new std::string("Shekhar"));

    std::ofstream resultFile("test_results.txt", std::ios::app);

    if (!contacts.empty()) {
        std::cout << "test_search_with_middle_name: Passed" << std::endl;
        resultFile << "passed, test_search_with_middle_name" << std::endl;
    } else {
        std::cerr << "test_search_with_middle_name: Failed" << std::endl;
        resultFile << "failed, test_search_with_middle_name" << std::endl;
    }

    resultFile.close();

    return 0;
}

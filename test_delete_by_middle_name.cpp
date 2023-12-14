#include <iostream>
#include <fstream>
#include "interface_template.cpp"

int main() {
    PhoneBook phone_book;
    phone_book.readRecordsFromFile("Details_new.txt");

    std::ofstream resultFile("test_results.txt", std::ios::app);

    if (phone_book.deleteContact(new std::string("Dev"))) {
        std::cout << "test_delete_by_middle_name: Passed" << std::endl;
        resultFile << "passed, test_delete_by_middle_name" << std::endl;
    } else {
        std::cerr << "test_delete_by_middle_name: Failed" << std::endl;
        resultFile << "failed, test_delete_by_middle_name" << std::endl;
    }

    resultFile.close();

    return 0;
}

#include <iostream>
#include <fstream>
#include "interface_template.cpp"

int main() {
    PhoneBook phone_book;
    phone_book.readRecordsFromFile("Details_new.txt");

    vector<string> phoneNumbers1 = {"7889234231"};
    PhoneRecord record1("Adhir Ranjan", "Novotel", phoneNumbers1);
    phone_book.addContact(&record1);

    std::vector<PhoneRecord*> contacts = phone_book.fetchContacts(new std::string("Adhir Ranjan"));

    std::ofstream resultFile("test_results.txt", std::ios::app); // Open the file in append mode

    if (contacts.size() >= 1 && contacts[0]->getName() == "Adhir Ranjan") {
        std::cout << "test_add_and_fetch_contact: Passed" << std::endl;
        resultFile << "passed, test_add_and_fetch_contact" << std::endl;
    } else {
        std::cerr << "test_add_and_fetch_contact: Failed" << std::endl;
        resultFile << "failed, test_add_and_fetch_contact" << std::endl;
    }

    resultFile.close(); // Close the file

    return 0;
}

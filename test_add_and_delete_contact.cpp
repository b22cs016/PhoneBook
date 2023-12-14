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

    std::ofstream resultFile("test_results.txt", std::ios::app);


    if (phone_book.deleteContact(new std::string("Adhir Ranjan"))) {
        std::cout << "test_add_and_delete_contact: Passed" << std::endl;
        resultFile << "passed, test_add_and_delete_contact" << std::endl;
    } else {
        std::cerr << "test_add_and_delete_contact: Failed" << std::endl;
        resultFile << "failed, test_add_and_delete_contact" << std::endl;
    }

    resultFile.close();

    return 0;
}

#include <iostream>
#include <fstream>
#include "interface_template.cpp"

int main() {
    PhoneBook phone_book;
    phone_book.readRecordsFromFile("Details_new.txt");

    std::vector<PhoneRecord*> initial_contacts = phone_book.fetchContacts(new std::string("Akshay Trivedi"));

    std::ofstream resultFile("test_results.txt", std::ios::app);

    if (!phone_book.deleteContact(new std::string("Akshay Trivedi"))) {
        std::vector<PhoneRecord*> contacts_after_delete = phone_book.fetchContacts(new std::string("Akshay Trivedi"));

        if (initial_contacts == contacts_after_delete) {
            std::cout << "test_delete_nonexistent_contact: Passed" << std::endl;
            resultFile << "passed, test_delete_nonexistent_contact" << std::endl;
        } else {
            std::cerr << "test_delete_nonexistent_contact: Failed" << std::endl;
            resultFile << "failed, test_delete_nonexistent_contact" << std::endl;
        }
    } else {
        std::cerr << "test_delete_nonexistent_contact: Failed" << std::endl;
        resultFile << "failed, test_delete_nonexistent_contact" << std::endl;
    }

    resultFile.close();

    return 0;
}

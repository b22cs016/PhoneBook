#include <iostream>
#include <fstream>
#include "interface_template.cpp"

int main() {
    PhoneBook phone_book;
    phone_book.readRecordsFromFile("Details_new.txt");

    std::vector<PhoneRecord*> contacts_gupta = phone_book.fetchContacts(new std::string("Ankush Gupta"));
    std::vector<PhoneRecord*> contacts_khanna = phone_book.fetchContacts(new std::string("Aarav Khanna"));

    std::ofstream resultFile("test_results.txt", std::ios::app);

    if (phone_book.deleteContact(new std::string("Ankush Gupta")) && phone_book.deleteContact(new std::string("Aarav Khanna"))) {
        std::vector<PhoneRecord*> contacts_gupta_after_delete = phone_book.fetchContacts(new std::string("Ankush Gupta"));
        std::vector<PhoneRecord*> contacts_khanna_after_delete = phone_book.fetchContacts(new std::string("Aarav Khanna"));

        if (!contacts_gupta_after_delete.empty() && contacts_khanna_after_delete.empty()) {
            std::vector<PhoneRecord*> contacts_sharma = phone_book.fetchContacts(new std::string("Sharma"));
            std::vector<PhoneRecord*> contacts_kumar = phone_book.fetchContacts(new std::string("Kumar"));

            if (contacts_sharma.size() >= 1 && contacts_kumar.size() >= 1) {
                std::cout << "test_delete_multiple_contacts: Passed" << std::endl;
                resultFile << "passed, test_delete_multiple_contacts" << std::endl;
            } else {
                std::cerr << "test_delete_multiple_contacts: Failed" << std::endl;
                resultFile << "failed, test_delete_multiple_contacts" << std::endl;
            }
        } else {
            std::cerr << "test_delete_multiple_contacts: Failed" << std::endl;
            resultFile << "failed, test_delete_multiple_contacts" << std::endl;
        }
    } else {
        std::cerr << "test_delete_multiple_contacts: Failed" << std::endl;
        resultFile << "failed, test_delete_multiple_contacts" << std::endl;
    }

    resultFile.close();

    return 0;
}

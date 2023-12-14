#include <iostream>
#include <fstream>
#include "interface_template.cpp"

int main() {
    PhoneBook phone_book;
    phone_book.readRecordsFromFile("Details_new.txt");

    std::vector<PhoneRecord> new_contacts = {
        PhoneRecord("John", "Benz", {"1111111111"}),
        PhoneRecord("Atreya", "Tata", {"2222222222"})
    };

    std::ofstream resultFile("test_results.txt", std::ios::app);

    for ( PhoneRecord& contact : new_contacts) {
        phone_book.addContact(&contact);
    }

    bool allAdded = true;

    for (const PhoneRecord& contact : new_contacts) {
        std::vector<PhoneRecord*> contacts = phone_book.fetchContacts(new std::string(contact.getName()));

        bool found = false;

        for (PhoneRecord* record : contacts) {
            if (record->getName() == contact.getName()) {
                found = true;
                break;
            }
        }

        if (!found) {
            allAdded = false;
            break;
        }
    }

    if (allAdded) {
        std::cout << "test_add_multiple_contacts: Passed" << std::endl;
        resultFile << "passed, test_add_multiple_contacts" << std::endl;
    } else {
        std::cerr << "test_add_multiple_contacts: Failed" << std::endl;
        resultFile << "failed, test_add_multiple_contacts" << std::endl;
    }

    resultFile.close();

    return 0;
}

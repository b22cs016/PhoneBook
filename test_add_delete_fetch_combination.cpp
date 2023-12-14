#include <iostream>
#include <fstream>
#include "interface_template.cpp"

int main() {
    PhoneBook phone_book;
    phone_book.readRecordsFromFile("Details_new.txt");

    PhoneRecord new_contact("Venkata Subramanian", "Microsoft", {"8056297058"});
    phone_book.addContact(&new_contact);

    std::ofstream resultFile("test_results.txt", std::ios::app);

    if (phone_book.deleteContact(new std::string("Venkata Subramanian"))) {
        std::vector<PhoneRecord*> contacts_after_delete = phone_book.fetchContacts(new std::string("Venkata Subramanian"));
        if (contacts_after_delete.empty()) {
            std::cout << "test_add_delete_fetch_combination: Passed" << std::endl;
            resultFile << "passed, test_add_delete_fetch_combination" << std::endl;
        } else {
            std::cerr << "test_add_delete_fetch_combination: Failed" << std::endl;
            resultFile << "failed, test_add_delete_fetch_combination" << std::endl;
        }
    } else {
        std::cerr << "test_add_delete_fetch_combination: Failed" << std::endl;
        resultFile << "failed, test_add_delete_fetch_combination" << std::endl;
    }

    resultFile.close();

    return 0;
}

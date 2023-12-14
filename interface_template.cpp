#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <fstream>
#include <sstream>
#include <map>
#include <math.h>
#include <bits/stdc++.h>
using namespace std;
class PhoneRecord
{
private:
    string name;
    string organisation;
    vector<string> phoneNumbers;

public:
    // Constructor
    PhoneRecord(const string &n, const string &org, const vector<string> &numbers)
        : name(n), organisation(org), phoneNumbers(numbers) {}

    // Getter methods
    string getName() const
    {
        return name;
    }

    string getOrganisation() const
    {
        return organisation;
    }

    vector<string> getPhoneNumbers() const
    {
        return phoneNumbers;
    }
};

class HashTableRecord
{
private:
    int key;
    PhoneRecord *element; // Pointer to PhoneRecord
    HashTableRecord *next;

public:
    // Constructor
    HashTableRecord(int k, PhoneRecord *rec)
        : key(k), element(rec), next(nullptr) {}

    // Getter methods
    int getKey() const
    {
        return key;
    }

    PhoneRecord *getRecord() const
    {
        return element;
    }

    HashTableRecord *getNext() const
    {
        return next;
    }

    void setNext(HashTableRecord *nxt)
    {
        next = nxt;
    }
};

class PhoneBook
{
private:
    static const int HASH_TABLE_SIZE = 263;
    HashTableRecord *hashTable[HASH_TABLE_SIZE];

public:
    // Constructor
    PhoneBook()
    {
        for (int i = 0; i < HASH_TABLE_SIZE; ++i)
        {
            hashTable[i] = nullptr;
        }
    };
    static bool compare(pair<PhoneRecord *, int> &p1,
                        pair<PhoneRecord *, int> &p2)
    {
        {
            // If frequencies are same, compare
            // values
            if (p1.second == p2.second)
                return p1.first < p2.first;
            return p1.second > p2.second;
        };
    };

    // Add your own implementation for hashing
    int computeHash(const string &str)
    {
        long long summation = 0;
        long long p = 1000000007;
        long long x = 263;
        for (int i = 0; i < str.size(); i++)
        {
            summation += static_cast<long>(int(str[i])) * static_cast<long>(pow(x, i)) % p;
        }
        long long hash_value = summation % static_cast<long>(HASH_TABLE_SIZE);
        return hash_value;
    };

    // Add your own implementation for adding a contact
    void addContact(PhoneRecord *record)
    {
        string name_str = record->getName();
        string token_string;
        stringstream string_stream_of_names(name_str);
        vector<string> vector_to_store_parts_of_name;
        while (getline(string_stream_of_names, token_string, ' '))
        {
            vector_to_store_parts_of_name.push_back(token_string);
        }
        for (int i = 0; i < vector_to_store_parts_of_name.size(); i++)
        {
            int hash_index = computeHash(vector_to_store_parts_of_name[i]);

            if (hashTable[hash_index] == nullptr)
            {
                HashTableRecord *temp = new HashTableRecord(hash_index, record);
                hashTable[hash_index] = temp;
            }
            else
            {
                HashTableRecord *new_node = new HashTableRecord(hash_index, record);
                HashTableRecord *temp = hashTable[hash_index];
                while (temp->getNext() != nullptr)
                {
                    temp = temp->getNext();
                }
                temp->setNext(new_node);
            }
        }
    };

    vector<PhoneRecord *> Sorted(vector<PhoneRecord *> a, int n)
    {
        // Store items and their frequencies
        map<PhoneRecord *, int> m;
        for (int i = 0; i < n; i++)
            m[a[i]]++;

        // no of distinct values in the array
        // is equal to size of map.
        int s = m.size();

        // an array of pairs
        pair<PhoneRecord *, int> p[s];

        // Fill (val, freq) pairs in an array
        // of pairs.
        int i = 0;
        for (auto it = m.begin(); it != m.end(); ++it)
            p[i++] = make_pair(it->first, it->second);

        // sort the array of pairs using above
        // compare function.
        sort(p, p + s, compare);
        vector<PhoneRecord *> updated_vector;
        for (int i = 0; i < s; i++)
        {
            int freq = p[i].second;
            while (freq--)
                updated_vector.push_back(p[i].first);
        }
        return updated_vector;
    }

    // Add your own implementation for deleting a contact
    bool deleteContact(const string *searchName)
    {
        int delete_flag = 0;
        vector<PhoneRecord *> vector_to_store_results_from_fetch;
        vector_to_store_results_from_fetch = fetchContacts(searchName);

        if (vector_to_store_results_from_fetch.size() == 0)
        {
            return 0;
        }
        PhoneRecord *ptr_to_phonerecord_we_want_to_delete = vector_to_store_results_from_fetch[0];
        string token_string;
        stringstream string_stream_of_name_of_record(ptr_to_phonerecord_we_want_to_delete->getName());
        vector<string> vector_to_store_parts_of_searchname;
        while (getline(string_stream_of_name_of_record, token_string, ' '))
        {
            vector_to_store_parts_of_searchname.push_back(token_string);
        }

        for (int i = 0; i < vector_to_store_parts_of_searchname.size(); i++)
        {
            int hash_value = computeHash(vector_to_store_parts_of_searchname[i]);
            HashTableRecord *temp = hashTable[hash_value];
            if (temp == nullptr)
            {
                continue;
            }
            if (temp->getRecord() == ptr_to_phonerecord_we_want_to_delete)
            {
                delete_flag = 1;
                hashTable[hash_value] = temp->getNext();
                free(temp);
                continue;
            }
            else
            {
                HashTableRecord *ptr_ahead_of_ptr_we_want_to_delete;
                while (temp->getNext() != nullptr)
                {
                    if (temp->getNext()->getRecord() == ptr_to_phonerecord_we_want_to_delete)
                    {
                        delete_flag = 1;
                        ptr_ahead_of_ptr_we_want_to_delete = temp->getNext()->getNext();
                        break;
                    }
                    temp = temp->getNext();
                }
                if (temp == nullptr || temp->getNext() == nullptr)
                {
                    continue;
                }
                temp->setNext(ptr_ahead_of_ptr_we_want_to_delete);
                free(temp->getNext());
            }
        }

        return delete_flag;
    };

    // Add your own implementation for fetching contacts
    vector<PhoneRecord *> fetchContacts(const string *query)
    {
        // fetch contacts function is wrong . It is storing all the phonerecords in that particular linked list
        vector<PhoneRecord *> query_vector;
        string token_string;
        stringstream string_stream_of_queries(*query);
        vector<string> vector_to_store_parts_of_queries;
        while (getline(string_stream_of_queries, token_string, ' '))
        {
            vector_to_store_parts_of_queries.push_back(token_string);
        }
        for (int i = 0; i < vector_to_store_parts_of_queries.size(); i++)
        {
            int hash_index = computeHash(vector_to_store_parts_of_queries[i]);
            HashTableRecord *temp = hashTable[hash_index];
            while (temp != nullptr)
            {
                bool isFound = temp->getRecord()->getName().find(vector_to_store_parts_of_queries[i]) != string::npos;
                if (isFound)
                {
                    query_vector.push_back(temp->getRecord());
                }
                temp = temp->getNext();
            }
        }
        int n = query_vector.size();
        query_vector = Sorted(query_vector, n);

        return query_vector;
    };
    // Add your own implementation for counting records pointing to a contact
    // I have defined other functions for countingRecords which do the same job as the one below
    int countRecordsPointingTo(const PhoneRecord *record) const;

    void readRecordsFromFile(const string &filename)
    {
        // Add your own implementation for reading records from a file
        ifstream file;
        string line;
        file.open(filename, ios::in);
        while (getline(file, line))
        {
            string parts_of_line;
            stringstream ss(line);
            vector<string> v;
            while (getline(ss, parts_of_line, ','))
            {
                v.push_back(parts_of_line);
            }
            vector<string> numbers;
            for (int i = 1; i < v.size() - 1; i++)
            {
                numbers.push_back(v[i]);
            }
            PhoneRecord *p = new PhoneRecord(v[0], v[v.size() - 1], numbers);
            addContact(p);
        }
    };
};

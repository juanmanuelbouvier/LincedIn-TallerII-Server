#include <iostream>
#include <sstream>
#include <string>

#include <leveldb/db.h>

#include "gtest/gtest.h"


using namespace std;


TEST(sample_test_case, sample_test) {
    // Set up database connection information and open database
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;

    leveldb::Status status = leveldb::DB::Open(options, "./testdb", &db);

    if (false == status.ok())
    {
        cerr << "Unable to open/create test database './testdb'" << endl;
        cerr << status.ToString() << endl;
    }
    
    // Add 256 values to the database
    leveldb::WriteOptions writeOptions;
    for (unsigned int i = 0; i < 256; ++i) {
        ostringstream keyStream;
        keyStream << "Key" << i;
        
        ostringstream valueStream;
        valueStream << "Test data value: " << i;
        
        db->Put(writeOptions, keyStream.str(), valueStream.str());
    }
    
    // Iterate over each item in the database and print them
    leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
    
    int i = 0;
    for (it->SeekToFirst(); it->Valid(); it->Next()) {
        string extraido = it->key().ToString() + " : " + it->value().ToString();
        string esperado = "Key" + to_string(i) + " : " + "Test data value: " + to_string(i);
        EXPECT_EQ(extraido,esperado);
        i++;
    }
    
    if (false == it->status().ok())
    {
        cerr << "An error was found during the scan" << endl;
        cerr << it->status().ToString() << endl; 
    }
    
    delete it;
    
    // Close the database
    delete db;
}

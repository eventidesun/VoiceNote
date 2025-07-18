#include <gtest/gtest.h>
#include "../storage_class/storage.h"
#include <vector>
#include <string>
#include <fstream>

// this is a helper function to create fake file data
// converts string into vector<char>
std::vector<char> makeData(const std::string& content) {
    return std::vector(content.begin(), content.end());
}

TEST(StorageTest, SaveAndLoadFile) {
    storage s;
    std::string fileName = "test_file.txt";
    std::vector<char> data = makeData("Hello World!");

    ASSERT_TRUE(s.saveFile(data, fileName));

    std::vector<char> loaded = s.loadFile(fileName);
    EXPECT_EQ(data, loaded);

    s.deleteFile(fileName);
}

TEST(StorageTest, DeleteFile) {
    storage s;
    std::string fileName = "delete_me.txt";
    std::vector<char> data = makeData("delete this");

    s.saveFile(data, fileName);
    ASSERT_TRUE(s.fileExists(fileName));
    ASSERT_TRUE(s.deleteFile(fileName));
    ASSERT_FALSE(s.fileExists(fileName));
}

TEST(StorageTest, FileExistsAndUsage) {
    storage s;
    std::string fileName = "usage_test.txt";
    std::vector<char> data = makeData("123456");

    s.saveFile(data, fileName);
    EXPECT_TRUE(s.fileExists(fileName));
    EXPECT_GE(s.getStorageUsage(), data.size());

    s.deleteFile(fileName);
}

TEST(StorageTest, LoadNonexistentFile) {
    storage s;
    std::vector<char> data = s.loadFile("nonexistent.txt");
    EXPECT_TRUE(data.empty());
}

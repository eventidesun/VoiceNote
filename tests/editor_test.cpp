#include "gtest/gtest.h"
#include "../editor_class/editor.h"
#include "../storage_class/storage.h"

TEST(EditorTest, LoadFile) {
    storage myStorage;
    std::vector<char> data = {'T', 'e', 's', 't'};
    myStorage.saveFile(data, "editor_test.txt");

    editor myEditor(myStorage);
    std::string content = myEditor.loadFile("editor_test.txt");
    EXPECT_EQ(content, "Test");
}

TEST(EditorTest, FindString) {
    storage myStorage;
    std::vector<char> data = {'H', 'e', 'l', 'l', 'o'};
    myStorage.saveFile(data, "find_test.txt");

    editor myEditor(myStorage);
    myEditor.loadFile("find_test.txt");
    EXPECT_TRUE(myEditor.findString("llo"));
    EXPECT_FALSE(myEditor.findString("world"));
}

TEST(EditorTest, ReplaceAndSave) {
    storage myStorage;
    std::vector<char> data = {'H', 'e', 'l', 'l', 'o'};
    myStorage.saveFile(data, "replace_test.txt");

    editor myEditor(myStorage);
    myEditor.loadFile("replace_test.txt");
    myEditor.findString("llo");
    myEditor.replaceString("y");
    myEditor.saveEdit();

    std::string updated = myEditor.loadFile("replace_test.txt");
    EXPECT_EQ(updated, "Hey");
}

TEST(EditorTest, DeleteFile) {
    storage myStorage;
    std::string testFile = "delete_me_temp.txt";
    std::vector<char> data = {'D', 'e', 'l', 'e', 't', 'e', 'M', 'e'};
    myStorage.saveFile(data, testFile);

    editor myEditor(myStorage);
    myEditor.deleteFile(testFile);

    EXPECT_FALSE(myStorage.fileExists(testFile));

    // Optional: try to clean it again just in case
    remove(testFile.c_str());
}

#include <QApplication>
#include "manage_recording_page/managerecordingpage.h"
#include "storage_class/storage.h"
#include "editor_class/editor.h"
#include "individual_recording_page/individualrecordingpage.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    storage sharedStorage;
    editor myEditor(sharedStorage);

    ManageRecordingPage window(nullptr, myEditor);
    window.show();

    return app.exec();
}
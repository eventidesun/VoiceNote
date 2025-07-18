#ifndef MANAGERECORDINGPAGE_H
#define MANAGERECORDINGPAGE_H

#include <QWidget>
#include <QListWidgetItem>
#include "../editor_class/editor.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class ManageRecordingPage;
}
QT_END_NAMESPACE

/**
 * @brief A class to display ui of all recorded transcripts
 *
 * @details
 * This class builds the graphics for the menu to see all the transcripts
 * This class uses QT objects for displays
 *
 * @author Vaishnavi Gudimella
 */
class ManageRecordingPage : public QWidget
{
    Q_OBJECT

public:

    /**
    * @brief Constructor of the class
    *
    * @details
    * Builds the ui for menu to see all transcripts.
    * Sets up buttons for user to select a certain transcript to view and edit
    *
    * @param parent A QWidget to render QObjects
    * @param editorObj An editor object used to interact with stored files
    *
    * @usage
    *
    */
    ManageRecordingPage(QWidget *parent, const editor& editorObj);

    /**
     * @brief Destructor of the class
     *
     * @details
     * Deletes the ui object
     */
    ~ManageRecordingPage();

private slots:
    /**
     * @brief Deletes a file
     *
     * @details
     * Allows users to delete notes from local storage.
     * Before file is deleted, a confirmation message appears
     *
     * @usage
     *
     */
    void onDeleteNote();

    /**
     * @brief Renames a file
     *
     * @details
     * Allows users to rename files from local storage
     *
     * @usage
     *
     */
    void onRenameNote();

    /**
     * @brief Goes to Individual Page
     *
     * @details
     * When a note is doubled clicked, this method sends the user to the Individual Page UI
     *
     * @param item The individual page
     *
     * @usage
     *
     */
    void onNoteDoubleCliked(QListWidgetItem *item);
private:

    /**
     * A private variable that contains the graphics of the UI
     */
    Ui::ManageRecordingPage *ui;

    /**
     * A private variable for storage object
     */
    editor m_editor;;

    /**
     * @brief Lists all files in storage
     *
     * @details
     * A private method that lets a list of filenames from editor and displays all files as a list
     *
     * @usage
     *
     */
    void populateRecordingsList();

protected:
    void showEvent(QShowEvent *event) override;
};
#endif // MANAGERECORDINGPAGE_H

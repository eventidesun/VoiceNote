#include "managerecordingpage.h"
#include "ui_managerecordingpage.h"
#include "../SpeechToText/speechtotext.h"
#include "../individual_recording_page/individualrecordingpage.h"
#include <QInputDialog>
#include <QMessageBox>
#include <filesystem>
#include <QShowEvent>
#include <QDebug>

// Constructor: Initializes the ManageRecordingPage UI and sets up event handlers.
ManageRecordingPage::ManageRecordingPage(QWidget *parent, const ::editor& editorObj)
	: QWidget(parent), ui(new Ui::ManageRecordingPage), m_editor(editorObj)
{
    ui->setupUi(this);

    // The "no recordings" label is hidden by default.
    ui->noRecordingsLabel->setVisible(false);

    // Populate the list with existing recordings.
    populateRecordingsList();

    // If there are no recordings, show the "no recordings" label.
    if (ui->recordingsList->count() == 0) {
        ui->noRecordingsLabel->setVisible(true);
    } else {
        ui->noRecordingsLabel->setVisible(false);
    }

    // Connects the "New Note" button to the SpeechToText window.
    connect(ui->new_note_button, &QPushButton::clicked, this, [this]() {
        auto *window = new SpeechToText();
        connect(window, &SpeechToText::transcriptSaved,
                this, &ManageRecordingPage::populateRecordingsList);
        window->show();
    });

    // Connects double-clicking a list item to opening the note.
    connect(ui->recordingsList, &QListWidget::itemDoubleClicked, this, &ManageRecordingPage::onNoteDoubleCliked);

    // Connects the "Delete Note" button to the deletion function.
    connect(ui->delete_note_button, &QPushButton::clicked, this, &ManageRecordingPage::onDeleteNote);

    // Connects the "Rename Note" button to the renaming function.
    connect(ui->rename_note_button, &QPushButton::clicked, this, &ManageRecordingPage::onRenameNote);
}

// Destructor: Cleans up the UI.
ManageRecordingPage::~ManageRecordingPage()
{
    delete ui;
}

// Populates the recordings list with filenames retrieved from the editor.
void ManageRecordingPage::populateRecordingsList() {
    // Clears the current list to avoid duplicates.
    ui->recordingsList->clear();

    // Retrieves the list of stored files.
    auto files = m_editor.getFileList();

    // Adds each file name to the UI list.
    for (const auto& file : files) {
        ui->recordingsList->addItem(QString::fromStdString(file));
    }

    ui->noRecordingsLabel->setVisible(ui->recordingsList->count() == 0);
}

// Handles deleting a selected note from the list.
void ManageRecordingPage::onDeleteNote() {
    // Gets the currently selected item.
    auto item = ui->recordingsList->currentItem();
    if (!item) return; // Exit if no item is selected.

    // Displays a confirmation dialog.
    QString name = item->text();
    auto reply = QMessageBox::question(this, "Delete Note",
        "Are you sure you want to delete '" + name + "'?",
        QMessageBox::Yes | QMessageBox::No);

    // If the user confirms, delete the file and refresh the list.
    if (reply == QMessageBox::Yes) {
        m_editor.deleteFile(name.toStdString());
        populateRecordingsList();
    }
}

// Handles renaming a selected note.
void ManageRecordingPage::onRenameNote() {
    // Gets the currently selected item.
    auto item = ui->recordingsList->currentItem();
    if (!item) return; // Exit if no item is selected.

    // Extracts the old file name.
    QString oldName = item->text();  // e.g. "test1.txt".

    // Prompts the user for a new file name.
    QString userInput = QInputDialog::getText(this, "Rename Note", "Enter new name:");

    // If the new name is valid, attempt renaming the file.
    if (!userInput.isEmpty()) {
        QString newName = userInput;

        // Only add ".txt" if it doesn't already end with ".txt"
        if (!newName.endsWith(".txt", Qt::CaseInsensitive)) {
            newName += ".txt";
        }

        try {
            // Rename using editor
            m_editor.changeName(newName.toStdString(), oldName.toStdString());
            populateRecordingsList();
        } catch (...) {
            QMessageBox::critical(this, "Error", "Something went wrong while renaming.");
        }
    }
}

// Handles double-clicking a note in the list to open it.
void ManageRecordingPage::onNoteDoubleCliked(QListWidgetItem *item) {
    if (!item) return; // Exit if no item is selected.

    // Retrieves the selected file name.
    QString selectedName = item->text();

    // Creates and shows the IndividualRecordingPage for the selected note.
    auto *window = new IndividualRecordingPage(nullptr, m_editor, selectedName.toStdString());
    window->show();
}

void ManageRecordingPage::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    populateRecordingsList();
}

#ifndef INDIVIDUALRECORDINGPAGE_H
#define INDIVIDUALRECORDINGPAGE_H

#include "../editor_class/editor.h"

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class IndividualRecordingPage; }
QT_END_NAMESPACE

/** @class IndividualRecordingPage
 *
 * @brief Displays UI for individual notes
 * 
 * @details
 * This class creates a display for viewing individual transcipts or notes using QT
 * This class also allows users to edit notes and/or transcripts 
 *
 * @author Vaishnavi Gudimella
 */
class IndividualRecordingPage : public QWidget
{
    /**
     * Q_Object to create graphics
     */
    Q_OBJECT

public:
    /**
     * @brief Constructor for class
     *
     * @details
     * This functions constructs an IndividualRecordingPage object to display a graphic with a preset UI.
     * This object displays a graphic for the front-end so users can view each of their recordings.
     *
     * @param parent (default: nullptr) The QWidget to render graphics
     *
     * @usage
     * 
     */
    IndividualRecordingPage(QWidget *parent, editor editorObj, const std::string& fileName);

    /**
     * @brief Destructor for class
     * 
     * @details
     * Deletes the ui object
     *
     * @usage
      
     */
    ~IndividualRecordingPage();

private slots:
    void onSaveTranscriptClicked();
    void onSummarizeClicked();

private:
    /**
     * A private variable that contains the graphics of the UI
     */
    Ui::IndividualRecordingPage *ui;
    editor m_editor;
    std::string m_fileName;
};
#endif // INDIVIDUALRECORDINGPAGE_H

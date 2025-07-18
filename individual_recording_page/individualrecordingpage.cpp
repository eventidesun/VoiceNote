#include "individualrecordingpage.h"
#include "./ui_individualrecordingpage.h"
#include "../editor_class/editor.h"
#include "../AI_Summarizer/src/llm/LLMInference.h"
#include "../AI_Summarizer/src/llm/AISummarizer.h"

#include <QMessageBox>

//#warning "Compiling individualrecordingpage.cpp"

IndividualRecordingPage::IndividualRecordingPage(QWidget *parent, editor editorObj, const std::string& fileName)
    : QWidget(parent)
    , ui(new Ui::IndividualRecordingPage)
    , m_editor(editorObj)
    , m_fileName(fileName)
{
    ui->setupUi(this);

    connect(ui->saveTranscript_button, &QPushButton::clicked, this, &IndividualRecordingPage::onSaveTranscriptClicked);
    connect(ui->summarize_button, &QPushButton::clicked, this, &IndividualRecordingPage::onSummarizeClicked);

    std::string contents = m_editor.loadFile(m_fileName);

    ui->plainTextEdit->setPlainText(QString::fromStdString(contents));
}

void IndividualRecordingPage::onSaveTranscriptClicked() {
    QString newText = ui->plainTextEdit->toPlainText();
    std::string content = newText.toStdString();

    // overwriting the file using saveFile
    std::vector<char> newData(content.begin(), content.end());
    m_editor.getStorage().saveFile(newData, m_fileName);

    QMessageBox::information(this, "Saved", "Your transcript has been saved successfully.");
}

void IndividualRecordingPage::onSummarizeClicked() {
    QString transcriptText = ui->plainTextEdit->toPlainText();

    QString outputPath = "../summary.txt";

    // Start summarize
    QString modelPath = QCoreApplication::applicationDirPath() + "/../AI_Summarizer/models/Llama-3.2-1B-Instruct-Q4_K_S.gguf";
    AISummarizer summarizer(modelPath.toStdString());

    // Output summary
    if (summarizer.summarizeFile(transcriptText.toStdString(), outputPath.toStdString())) {
        QString summary = QString::fromStdString(summarizer.getSummary());
        ui->outputTextEdit->setPlainText(summary);
        QMessageBox::information(this, "Summary Ready", "Your summary has been generated!");
    } else {
        ui->outputTextEdit->setPlainText("Failed to summarize.");
    }
}

IndividualRecordingPage::~IndividualRecordingPage()
{
    delete ui;
}

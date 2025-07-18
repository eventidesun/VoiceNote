#include "speechtotext.h"
#include "ui_speechtotext.h"

#include <QAudioRecorder>
#include <QMediaRecorder>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QCoreApplication>
#include <QDir>
#include <QProcess>
#include <QDebug>
#include <QInputDialog>

// The constructor initializes the SpeechToText UI and sets up the audio recorder and timer.
SpeechToText::SpeechToText(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SpeechToText)
    , audioRecorder(new QAudioRecorder(this))
    , recordingTimer(new QTimer(this))
    , recordingSeconds(0)
{
    // The UI elements are set up.
    ui->setupUi(this);

    // The recording, pause, stop, and transcription buttons are connected to their respective functions.
    connect(ui->btnRecord, &QPushButton::clicked, this, &SpeechToText::startRecording);
    connect(ui->btnPause, &QPushButton::clicked, this, &SpeechToText::pauseRecording);
    connect(ui->btnStop, &QPushButton::clicked, this, &SpeechToText::stopRecording);
    connect(ui->btnTranscribe, &QPushButton::clicked, this, &SpeechToText::transcribeAudio);
    connect(ui->btnSaveTranscript, &QPushButton::clicked, this, &SpeechToText::saveTranscript);

    // The recording timer is connected to update the UI every second.
    connect(recordingTimer, &QTimer::timeout, this, &SpeechToText::updateTimer);
}

// The destructor cleans up dynamically allocated memory.
SpeechToText::~SpeechToText()
{
    delete ui;
}

// Starts the audio recording process.
void SpeechToText::startRecording()
{
    // If the recording was previously paused, it resumes recording.
    if (audioRecorder->state() == QMediaRecorder::PausedState) {
        audioRecorder->record();
        ui->textEditOutput->setText("🎙️ Recording resumed...");
        recordingTimer->start(1000);  // The timer resumes counting.
        return;
    }

    // The recorded audio file path is set.
    recordedAudioPath = QCoreApplication::applicationDirPath() + "/recorded.wav";
    audioRecorder->setOutputLocation(QUrl::fromLocalFile(recordedAudioPath));

    // The default audio input device is selected.
    audioRecorder->setAudioInput(audioRecorder->defaultAudioInput());

    // Audio settings are configured for high-quality PCM encoding.
    QAudioEncoderSettings settings;
    settings.setCodec("audio/pcm");
    settings.setSampleRate(16000);
    settings.setQuality(QMultimedia::HighQuality);
    audioRecorder->setAudioSettings(settings);

    // The recording process starts.
    audioRecorder->record();
    ui->textEditOutput->setText("🎙️ Recording started...");

    // The recording duration is reset and the timer starts counting.
    recordingSeconds = 0;
    recordingTimer->start(1000);
}

// Pauses the ongoing recording.
void SpeechToText::pauseRecording()
{
    // If recording is active, it is paused and the timer is stopped.
    if (audioRecorder->state() == QMediaRecorder::RecordingState) {
        audioRecorder->pause();
        recordingTimer->stop();
        ui->textEditOutput->setText("⏸ Recording paused...");
    }
}

// Stops the recording process.
void SpeechToText::stopRecording()
{
    // The audio recording is stopped.
    audioRecorder->stop();

    // The recording timer is stopped.
    recordingTimer->stop();

    // The UI is updated to indicate that recording has stopped.
    ui->textEditOutput->setText("Recording stopped. Ready to transcribe.");
}

// Updates the recording timer in the UI.
void SpeechToText::updateTimer()
{
    // The recording duration is incremented by one second.
    recordingSeconds++;

    // The elapsed minutes and seconds are calculated.
    int minutes = recordingSeconds / 60;
    int seconds = recordingSeconds % 60;

    // The UI is updated to display the elapsed recording time.
    ui->textEditOutput->setText(QString("🎙️ Recording: %1:%2")
                                .arg(minutes, 2, 10, QChar('0'))
                                .arg(seconds, 2, 10, QChar('0')));
}

// Transcribes the recorded audio file.
void SpeechToText::transcribeAudio()
{
    // If no valid recording is found, an error message is displayed.
    if (recordedAudioPath.isEmpty() || !QFile::exists(recordedAudioPath)) {
        ui->textEditOutput->setText("No recording found. Please record audio first.");
        return;
    }

    // The project root directory is determined.
    QString projectRoot = QDir(QCoreApplication::applicationDirPath()).filePath("../../");

    // The Whisper CLI executable path is set.
    QString whisperCliPath = QDir::cleanPath(projectRoot + "./group08/whisper.cpp/build/bin/whisper-cli");

    // The model file path is set.
    QString modelPath = QDir::cleanPath(projectRoot + "./group08/whisper.cpp/models/ggml-base.en.bin");

    // If the model file does not exist, an error message is displayed.
    if (!QFile::exists(modelPath)) {
        ui->textEditOutput->setText("Model path not accessible: " + modelPath);
        return;
    }

    // The command-line arguments for transcription are prepared.
    QStringList arguments;
    arguments << "-m" << modelPath
              << "-f" << recordedAudioPath
              << "--output-txt";

    // A QProcess instance is created to execute the Whisper CLI.
    QProcess process;
    process.setWorkingDirectory(QFileInfo(whisperCliPath).absolutePath());
    process.start(whisperCliPath, arguments);

    // If the process fails to start or complete, an error message is displayed.
    if (!process.waitForFinished(-1)) {
        ui->textEditOutput->setText("Transcription process failed to start or finish.");
        qDebug() << "Whisper CLI path:" << whisperCliPath;
        qDebug() << "Model path:" << modelPath;
        return;
    }

    // The path of the generated transcription file is set.
    QString outputFilePath = recordedAudioPath + ".txt";

    // The transcription file is opened for reading.
    QFile outputFile(outputFilePath);
    if (outputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&outputFile);

        // The transcription text is read and displayed in the UI.
        QString transcription = in.readAll();
        ui->textEditOutput->setText(transcription.trimmed());

        // The file is closed.
        outputFile.close();
    } else {
        // If the transcription file could not be read, an error message is displayed.
        ui->textEditOutput->setText("Failed to read transcription output file: " + outputFilePath);
    }
}

void SpeechToText::saveTranscript()
{
    bool ok;
    QString fileName = QInputDialog::getText(this, "Save Transcript", "Enter file name:", QLineEdit::Normal, "", &ok);

    if (ok && !fileName.isEmpty()) {
        // Ensure only one .txt extension
        if (!fileName.endsWith(".txt")) {
            fileName += ".txt";
        }

        // Build the full path to the storage-notes folder
        QString savePath = QCoreApplication::applicationDirPath() + "/../storage-notes/" + fileName;

        QFile file(savePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << ui->textEditOutput->toPlainText();  // Save current transcript
            file.close();

            QMessageBox::information(this, "Saved", "Transcript saved to:\n" + savePath);
            emit transcriptSaved();
        } else {
            QMessageBox::warning(this, "Error", "Failed to save transcript.");
        }
    }
}

#ifndef SPEECHTOTEXT_H
#define SPEECHTOTEXT_H

#include <QMainWindow>
#include <QAudioRecorder>
#include <QTimer>
#include <QUrl>

QT_BEGIN_NAMESPACE
namespace Ui {
    class SpeechToText;
}
QT_END_NAMESPACE

/**
 * @class SpeechToText
 * @brief A class for recording and transcribing audio.
 *
 * @details
 * The SpeechToText class provides the application with functionality to record audio,
 * pause and stop recordings, track recording duration, and transcribe recorded audio
 * using an external Whisper model.
 *
 * @author Anya Liu
 */
class SpeechToText : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the SpeechToText class.
     *
     * @param parent The parent widget (default: nullptr).
     *
     * @usage
     * SpeechToText *stt = new SpeechToText(nullptr);
     */
    explicit SpeechToText(QWidget *parent = nullptr);

    /**
     * @brief Destructor for the SpeechToText class.
     */
    ~SpeechToText();

signals:
    void transcriptSaved();

private slots:
    /**
     * @brief Starts audio recording.
     *
     * If recording was previously paused, it resumes. Otherwise, it starts a new session.
     *
     * @usage
     * SpeechToText *stt = new SpeechToText(nullptr);
     * stt->startRecording();
     */
    void startRecording();

    /**
     * @brief Pauses an ongoing recording.
     *
     * @usage
     * stt->pauseRecording();
     */
    void pauseRecording();

    /**
     * @brief Stops the recording process.
     *
     * @usage
     * stt->stopRecording();
     */
    void stopRecording();

    /**
     * @brief Updates the recording timer display.
     *
     * This function is triggered every second while recording to update the UI.
     */
    void updateTimer();

    /**
     * @brief Transcribes the recorded audio using an external Whisper model.
     *
     * This function processes the recorded audio file and converts it into text using an external transcription model.
     *
     * @usage
     * stt->transcribeAudio();
     */
    void transcribeAudio();

    void saveTranscript();

private:
    //Pointer to the UI instance.
    Ui::SpeechToText *ui;
    //Audio recorder instance for capturing audio.
    QAudioRecorder *audioRecorder;
    //Path where the recorded audio file is saved.
    QString recordedAudioPath;
    //Timer instance for tracking recording duration.
    QTimer *recordingTimer;
    //Stores the elapsed recording time in seconds.
    int recordingSeconds;
};

#endif
#ifndef TEMPLATEGENERATOR_H
#define TEMPLATEGENERATOR_H

#include <QObject>

#include "core/templatecore.h"


/// \brief Generator responsible for generating APK mobile applications.
class TemplateGenerator : public QObject {
    Q_OBJECT

  public:
    // Constructors and destructors.
    explicit TemplateGenerator(QObject *parent = 0);
    virtual ~TemplateGenerator();

  public slots:
    /// \brief Generates new APK application using given core.
    /// \param core Used core.
    /// \warning State and progress of creating of application
    /// is reported via signalling. No return values are used.
    void generateMobileApplication(TemplateCore *core);

    /// \brief Cleans workspace used for generating applications.
    void cleanWorkspace();

    /// \brief Cleans and recreates base workspace path.
    void refreshWorkspace();

  signals:
    /// \brief Emitted if generating process is started.
    void generationStarted();

    /// \brief Emitted if generating process is finished.
    /// \param result_code Result code of generating process.
    /// \param output_file If generating succeeded, then this contains
    /// output APK file path.
    void generationFinished(TemplateCore::GenerationResult result_code, const QString &output_file = QString());

    /// \brief Emitted when there is some progress in generating
    /// APK application.
    /// \param progress Number of percent passed.
    /// \param message Progress message description.
    void generationProgress(int progress, const QString &message);
};

#endif // TEMPLATEGENERATOR_H

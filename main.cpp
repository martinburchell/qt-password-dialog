#include <QApplication>
#include <QDebug>
#include <QDialog>
#include <QDialogButtonBox>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QMainWindow>
#include <QScreen>
#include <QtSystemDetection>
#include <QVBoxLayout>

#if defined(Q_OS_IOS)
    const bool PLATFORM_FULL_SCREEN_DIALOGS = true;
#else
    const bool PLATFORM_FULL_SCREEN_DIALOGS = false;
#endif
const int MINIMUM_PASSWORD_LENGTH = 10;


class PasswordDialog : public QDialog
{
    Q_OBJECT
public:
    PasswordDialog(QWidget* parent) :  QDialog(parent)
    {
        auto mainlayout = new QVBoxLayout();
        if (PLATFORM_FULL_SCREEN_DIALOGS) {
            setWindowState(Qt::WindowFullScreen);
            mainlayout->addStretch(1);
        }

        auto prompt = new QLabel("Enter a new password for the application");
        mainlayout->addWidget(prompt);

        auto prompt_new1 = new QLabel("Enter new password:");
        mainlayout->addWidget(prompt_new1);
        auto editor_new1 = new QLineEdit();
        editor_new1->setEchoMode(QLineEdit::Password);
        editor_new1->setPlaceholderText(
            QString("Must be at least %1 characters").arg(MINIMUM_PASSWORD_LENGTH)
        );

        mainlayout->addWidget(editor_new1);

        auto prompt_new2 = new QLabel("Enter new password again for confirmation:");

        mainlayout->addWidget(prompt_new2);
        auto editor_new2 = new QLineEdit();
        editor_new2->setEchoMode(QLineEdit::Password);
        mainlayout->addWidget(editor_new2);

        auto buttonbox = new QDialogButtonBox(
            QDialogButtonBox::Ok | QDialogButtonBox::Cancel
        );
        mainlayout->addWidget(buttonbox);

        if (PLATFORM_FULL_SCREEN_DIALOGS) {
            prompt->setWordWrap(true);
            prompt_new1->setWordWrap(true);
            mainlayout->addStretch(1);
        }
        setLayout(mainlayout);
    }
};

int main(int argc, char* argv[]){
    QApplication app(argc, argv);

    auto main_window = new QMainWindow();
    main_window->showMaximized();
    PasswordDialog dialog(main_window);
    dialog.exec();

    return app.exec();
}

#include "main.moc"

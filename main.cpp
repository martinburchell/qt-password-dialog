#include <QApplication>
#include <QDebug>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFont>
#include <QFontMetrics>
#include <QGuiApplication>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QScreen>
#include <QtSystemDetection>
#include <QVBoxLayout>

#if defined(Q_OS_IOS)
    const bool PLATFORM_FULL_SCREEN_DIALOGS = true;
#else
    const bool PLATFORM_FULL_SCREEN_DIALOGS = false;
#endif

#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
    const bool PLATFORM_TABLET = true;
#else
    const bool PLATFORM_TABLET = false;
#endif


const int MINIMUM_PASSWORD_LENGTH = 10;

class PasswordDialog : public QDialog
{
    Q_OBJECT
public:
    PasswordDialog(QWidget* parent) :  QDialog(parent)
    {
        setWindowTitle("Enter a new password for the CamCOPS application");
        setMinimumSize(minimumSizeForTitle());
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

    QSize minimumSizeForTitle()
    {
        // +---------------------------------------------+
        // | ICON  TITLETEXT - APPTITLE    WINDOWBUTTONS |
        // |                                             |
        // | contents                                    |
        // +---------------------------------------------+

        // https://doc.qt.io/qt-6.5/qwidget.html#windowTitle-prop
        const QSize size_before = size();
        const QString window_title = windowTitle();
        const QString app_name = QApplication::applicationDisplayName();
        QString full_title = window_title;
        const QFont title_font = QApplication::font("QWorkspaceTitleBar");
        const QFontMetrics fm(title_font);
        const int title_w = fm.boundingRect(full_title).width();  // "_w" means width

        // dialog->ensurePolished();
        // const QSize frame_size = dialog->frameSize();
        // const QSize content_size = dialog->size();
        // ... problem was that both are QSize(640, 480) upon creation
        // ... even if ensurePolished() is called first
        // const QSize frame_extra = frame_size - content_size;

        // How to count the number of icons shown on a window? ***
        // - Android: 0
        // - Linux: presumably may vary with window manager, but 4 is typical under
        //   XFCE (1 icon on left, 3 [rollup/maximize/close] on right), but need a
        //   bit more for spacing; 6 works better (at 24 pixels width per icon)
        // - Windows: also 4 (icon left, minimize/maximize/close on right)
        const int n_icons = PLATFORM_TABLET ? 0 : 6;

        // How to read the size (esp. width) of a window icon? ***
        // const int icon_w = frame_extra.height();
        // ... on the basis that window icons are square!
        // ... but the problem is that frame size may as yet be zero
        const int icon_w = 24;

        const int final_w = title_w + n_icons * icon_w;
        const QSize dialog_min_size = minimumSize();
        QSize size(dialog_min_size);
        size.setWidth(qMax(size.width(), final_w));
        QRect screen_geometry = QGuiApplication::primaryScreen()->geometry();
        qDebug().nospace()
            << Q_FUNC_INFO
            << "window_title = " << window_title
            << ", app_name = " << app_name
            << ", full_title = " << full_title
            << ", title_font = " << title_font
            << ", title_w = " << title_w
            << ", n_icons = " << n_icons
            << ", icon_w = " << icon_w
            << ", size_before = " << size_before
            << ", screen_geometry = " << screen_geometry
            << ", dialog_min_size = " << dialog_min_size
            << ", size = " << size;
        return size;
    }

};

int main(int argc, char* argv[]){
    QApplication app(argc, argv);

    PasswordDialog dialog(nullptr);
    dialog.exec();

    return app.exec();
}

#include "main.moc"

#ifndef HELLOVULKANWIDGET_H
#define HELLOVULKANWIDGET_H

#include <QWidget>
#include <QLineEdit>
QT_FORWARD_DECLARE_CLASS(QTabWidget)
QT_FORWARD_DECLARE_CLASS(QPlainTextEdit)

//Forward declaration
class VulkanWindow;
class QMenu;
class QMenuBar;
class QAction;
class QDialogButtonBox;

//The class that holds the whole GUI of the application
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(VulkanWindow *vw, QPlainTextEdit *logWidget);

public slots:
    void onScreenGrabRequested();

private:
    VulkanWindow *mVulkanWindow{ nullptr };
    QTabWidget *mInfoTab{ nullptr };
    QPlainTextEdit *mLogWidget{ nullptr };

    QMenuBar* createMenu();

    QMenuBar* menuBar{ nullptr };
    QMenu* fileMenu{ nullptr };
    QAction* openFileAction{ nullptr };
    QAction* exitAction{ nullptr };
    //QAction*
    std::string mSelectedName;

    QLineEdit* x;
    float x_{0};
    float y_{0};
    float z_{0};
    bool x_made=false;
    bool y_made=false;
    bool z_made=false;

private slots:
    void openFile();
    void selectName();
    void setBALLposition(float x, float y, float z);
};

#endif // HELLOVULKANWIDGET_H

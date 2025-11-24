#include "MainWindow.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QTabWidget>
#include <QMenuBar>
#include <QInputDialog>
#include "VulkanWindow.h"
#include "Renderer.h"
#include "TriangleSurface.h"

MainWindow::MainWindow(VulkanWindow *vw, QPlainTextEdit *logWidget)
    : mVulkanWindow(vw)
{
    //Wraps the VulkanWindow inside a QWidget so we can place it together with other widgets
    QWidget *vulkanWindowWrapper = QWidget::createWindowContainer(vw);

    mLogWidget = logWidget;
    //Sets the colors in the log window
    mLogWidget->setStyleSheet("color: white ; background-color: #2f2f2f ;");

    //makes buttons
    QPushButton *grabButton = new QPushButton(tr("&Grab frame"));
    grabButton->setFocusPolicy(Qt::NoFocus);

    QPushButton *quitButton = new QPushButton(tr("&Quit"));
    quitButton->setFocusPolicy(Qt::NoFocus);

    QPushButton *nameButton = new QPushButton(tr("&Name")); // Dag 040225
    nameButton->setFocusPolicy(Qt::NoFocus);                // Dag 040225



    //connect push of grab button to screen grab function
    connect(grabButton, &QPushButton::clicked, this, &MainWindow::onScreenGrabRequested);
    //connect quit button to quit-function
    connect(quitButton, &QPushButton::clicked, qApp, &QCoreApplication::quit);
    //connect changes in our logger to trigger scroll to end of log window, using a lambda
    connect(mLogWidget, &QPlainTextEdit::textChanged, [logWidget]()
            { logWidget->moveCursor(QTextCursor::End); });
    //select file to import
    connect(nameButton, SIGNAL(clicked()), this, SLOT(selectName()));   // Dag 040225


    //Makes the layout of the program, adding items we have made
    QVBoxLayout *layout = new QVBoxLayout;
    QPushButton *changePosition = new QPushButton(tr("&Change start position"), this);

    x=new QLineEdit(vulkanWindowWrapper);
    x->setPlaceholderText("new x");
    connect(x, &QLineEdit::textChanged, this,[=](const QString& text){
        x_=text.toFloat();
        //x_made=true;
    });

    QLineEdit* y=new QLineEdit(vulkanWindowWrapper);
    y->setPlaceholderText("new y");
    connect(y, &QLineEdit::textChanged, this,[=](const QString& text){
        y_=text.toFloat();
        // y_made=true;
    });
    QLineEdit* z=new QLineEdit(vulkanWindowWrapper);
    z->setPlaceholderText("new z");
    connect(z, &QLineEdit::textChanged, this,[=](const QString& text){
        z_=text.toFloat();
        //z_made=true;
    });

    connect(changePosition, &QPushButton::clicked, this,[=](){
        setBALLposition(x_,y_,z_);
        // if(x_made && y_made && z_made){
        //     setBALLposition(x_,y_,z_);
        //     x_made=false;
        //     y_made=false;
        //     z_made=false;
        // }
    });

    layout->addWidget(x,1);
    layout->addWidget(y,2);
    layout->addWidget(z,3);
    layout->addWidget(changePosition,4);

    layout->setMenuBar(createMenu());
    layout->addWidget(vulkanWindowWrapper, 7);
    mInfoTab = new QTabWidget(this);
    mInfoTab->addTab(mLogWidget, tr("Debug Log"));
    layout->addWidget(mInfoTab, 2);
    QHBoxLayout *buttonLayout = new QHBoxLayout;



    buttonLayout->addWidget(nameButton, 1); // Dag 040225
    buttonLayout->addWidget(grabButton, 1);
    buttonLayout->addWidget(quitButton, 1);
    layout->addLayout(buttonLayout);

    setLayout(layout);

    //sets the keyboard input focus to the RenderWindow when program starts
    //(wrapped inside of this QWidget)
    // - can be deleted, but then you have to click inside the RenderWindow to get the focus
    vulkanWindowWrapper->setFocus();
}

//Makes the screen grab, and saves it to file
void MainWindow::onScreenGrabRequested()
{
    if (!mVulkanWindow->supportsGrab()) {
        QMessageBox::warning(this, tr("Cannot grab"), tr("This swapchain does not support readbacks."));
        return;
    }

    QImage img = mVulkanWindow->grab();

    // Our startNextFrame() implementation is synchronous so img is ready to be
    // used right here.

    QFileDialog fd(this);
    fd.setAcceptMode(QFileDialog::AcceptSave);
    fd.setDefaultSuffix("png");
    fd.selectFile("test.png");
    if (fd.exec() == QDialog::Accepted)
        img.save(fd.selectedFiles().first());


}

QMenuBar *MainWindow::createMenu()
{
    menuBar = new QMenuBar(this);
    fileMenu = new QMenu(tr("&File"), this);
    openFileAction = fileMenu->addAction(tr("&Open file..."));
    exitAction = fileMenu->addAction(tr("E&xit"));
    menuBar->addMenu(fileMenu);
    menuBar->setVisible(true);
    //
    connect(openFileAction, &QAction::triggered, this, &MainWindow::openFile);
    connect(exitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    return menuBar;
}
void MainWindow::openFile() // slot
{
    auto filnavn = QFileDialog::getOpenFileName(this);
    auto filnavn2 = QFileDialog::getOpenFileName(this);
    if (!filnavn.isEmpty())
    {
        TriangleSurface* surf = new TriangleSurface(filnavn.toStdString(),filnavn2.toStdString());
        auto rw = dynamic_cast<Renderer*>(mVulkanWindow->getRenderWindow());
        rw->getObjects().push_back(surf);
        rw->releaseResources();
        rw->initResources();
    }
}

void MainWindow::selectName()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("Object name:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty())
        mSelectedName = text.toStdString();

    auto rw = dynamic_cast<Renderer*>(mVulkanWindow->getRenderWindow());
    auto map = rw->getMap();
    auto visualObject = map[mSelectedName];
    if (visualObject != nullptr)
        mVulkanWindow->setSelectedObject(visualObject);
    else {
        QMessageBox msgBox;
        msgBox.setText("Finner ikke " + QString(mSelectedName.c_str()));
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setDefaultButton(QMessageBox::Close);
    }
}

void MainWindow::setBALLposition(float x, float y, float z)
{
    auto rw = dynamic_cast<Renderer*>(mVulkanWindow->getRenderWindow());
    for (std::vector<VisualObject*>::iterator it=rw->mObjects.begin(); it!=rw->mObjects.end(); it++){
        if((*it)->isBall && (*it)->isActive){
            (*it)->isActive=false;
        }
    }
    //rw->getObjects().at(1)->isActive=false;
    rw->activateBalls(x,y,z);
}

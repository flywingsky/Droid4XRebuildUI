#include "title.h"
#include "ui_title.h"

#include <windows.h>
#include <QDebug>
#include <QMouseEvent>
#include "framelessmove.h"
#include "mainpanel.h"


Title::Title(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Title),
    _frame(new FramelessMove(this)),
    _panel(NULL)
{
    ui->setupUi(this);

    connect(ui->btnMin, SIGNAL(clicked()), this, SIGNAL(MinWnd()));
    connect(ui->btnMax, SIGNAL(clicked()), this, SLOT(ReverseMaxStatus()));
    connect(ui->btnClose, SIGNAL(clicked()), this, SIGNAL(CloseWnd()));

    _frame->SetMonitor(this);
}

Title::~Title()
{
    delete ui;
}

bool Title::MaxWindow()
{
    return _panel->isMaximized();
}

void Title::setMaxWindow(bool max)
{
    if(max != MaxWindow())
    {
        _panel->setWindowState(max ? Qt::WindowMaximized : Qt::WindowNoState);
        if(max)
            emit MaxWnd();
        else
            emit NormalWnd();
    }
}

void Title::mouseDoubleClickEvent(QMouseEvent *event)
{
    ReverseMaxStatus();
    QWidget::mouseDoubleClickEvent(event);
}


bool Title::eventFilter(QObject *obj, QEvent *ev)
{
    if(obj == this)
    {
        if(ev->type() == QEvent::MouseMove)
        {
            if(DragTitle())
            {
                ev->accept();
                return true;
            }
        }
    }
    return QWidget::eventFilter(obj, ev);
}

void Title::ReverseMaxStatus()
{
    setMaxWindow(!MaxWindow());
}

bool Title::DragTitle()
{
    bool ret = false;
    if(MaxWindow())
    {
        ret = true;
        setMaxWindow(false);
    }
    return ret;
}

void Title::SetMoveTarget(QWidget *w)
{
    _frame->SetTarget(w);
    installEventFilter(this);
}

void Title::SetText(const QString &text)
{
    ui->labelText->setText(text);
}

void Title::SetMainPanel(MainPanel *p)
{
    _panel = p;
}

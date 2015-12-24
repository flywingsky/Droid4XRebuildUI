#include "itemwidget.h"
#include "ui_itemwidget.h"

#include <QMouseEvent>

ItemWidget::ItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemWidget)
{
    ui->setupUi(this);
    installEventFilter(this);
}

ItemWidget::~ItemWidget()
{
    delete ui;
}

void ItemWidget::SetNum(int num)
{
    ui->label->setText(QString::number(num));
}



bool ItemWidget::eventFilter(QObject *obj, QEvent *ev)
{
    if (obj == this)
    {
        static bool lButtonPress = false;
        static QPoint dragPosition;


        switch(ev->type())
        {
        case QEvent::MouseButtonPress:
        {
            QMouseEvent* event = (QMouseEvent*)ev;
            if(event->button() == Qt::LeftButton)
            {
                QWidget* p = (QWidget*)this;

                dragPosition  = event->globalPos() - p->frameGeometry().topLeft();
                lButtonPress = true;
                raise();

                //return true;
            }

            break;
        }
        case QEvent::MouseButtonRelease:
        {
            QMouseEvent* event = (QMouseEvent*)ev;
            if(event->button() == Qt::LeftButton && lButtonPress)
                lButtonPress  = false;

            break;
        }
        case QEvent::MouseMove:
        {
            if(lButtonPress)
            {
                QMouseEvent* event = (QMouseEvent*)ev;
                QWidget* p = (QWidget*)this;
                QPoint tl = event->globalPos() - dragPosition;
                tl.setX(x());

                p->move(tl);

                //return true;

            }
            break;
        }

        default:
            break;

        }
    }

    return QWidget::eventFilter(obj,ev);
}

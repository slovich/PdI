#ifndef FORMHISTOGRAMA_H
#define FORMHISTOGRAMA_H

#include <QDialog>
#include <QImage>

namespace Ui {
class FormHistograma;
}

class FormHistograma : public QDialog
{
    Q_OBJECT

public:
    explicit FormHistograma(QImage image1, QImage image2, QWidget *parent = nullptr);
    ~FormHistograma();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void setItensLayout();
    QImage getHistograma(QImage *img);

private:
    Ui::FormHistograma *ui;
};

#endif // FORMHISTOGRAMA_H

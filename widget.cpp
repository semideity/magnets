#include "widget.h"
#include "ui_widget.h"
#include "mag.h"
//#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    magnet_num = 0;
    xlh = 0;
    line_caled = false;
    plane_caled = false;
    point_caled = false;
    model_plot = false;
    line_checkbox_modified = false;
    point_checkbox_modified = false;
    ui->setupUi(this);
    connect(ui->tab_2, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(my_mouseMove(QMouseEvent*)));
    connect(ui->tab_3, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(my_mouseMove_2(QMouseEvent*)));
    connect(ui->tab_7, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(my_mouseMove_3(QMouseEvent*)));
    ui->tab_1->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tab_2->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tab_3->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tab_7->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tab_1, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(show_contextmenu_1(const QPoint&)));
    connect(ui->tab_2, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(show_contextmenu_2(const QPoint&)));
    connect(ui->tab_3, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(show_contextmenu_3(const QPoint&)));
    connect(ui->listWidget, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(show_contextmenu_4(const QPoint&)));
    connect(ui->tab_7, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(show_contextmenu_5(const QPoint&)));
    colorScale = new QCPColorScale(ui->tab_3);
}

Widget::~Widget()
{
    delete ui;
}

bool Widget::isNum(QString str)
{
    int i=0;
    // 第一位为数字或负号
    if (!(str[i]=='0' || str[i]=='1' || str[i]=='2' || str[i]=='3' || str[i]=='4' || str[i]=='5' || str[i]=='6' || str[i]=='7' || str[i]=='8' || str[i]=='9' || str[i]=='-')) {
        return false;
    }
    // 最后一位为数字
    i=str.length()-1;
    if (!(str[i]=='0' || str[i]=='1' || str[i]=='2' || str[i]=='3' || str[i]=='4' || str[i]=='5' || str[i]=='6' || str[i]=='7' || str[i]=='8' || str[i]=='9')) {
        return false;
    }
    if (str.length() > 2) {
        // 其它位为数字、负号、小数点、e或E
        for (i = 1; i < str.length(); i++) {
            if (!(str[i]=='0' || str[i]=='1' || str[i]=='2' || str[i]=='3' || str[i]=='4' || str[i]=='5' || str[i]=='6' || str[i]=='7' || str[i]=='8' || str[i]=='9' || str[i]=='e' || str[i]=='E' || str[i]=='-' || str[i]=='.')) {
                return false;
            }
        }
        // 除第一位外负号必须出现在e或E后面
        for (i = 1; i < str.length(); i++) {
            if (str[i]=='-' && !(str[i-1]=='e' || str[i-1]=='E')) {
                return false;
            }
        }
        // e或E只能出现1次
        int e_num=0;
        for (i = 0; i < str.length(); i++) {
            if (str[i]=='e' || str[i]=='E') {
                e_num++;
            }
        }
        if (e_num>1) {
            return false;
        }
    }

    return true;
}

void zm_rotate(int xzz, double xzjd, double x0, double y0, double z0, double xp, double yp, double zp, double *x1, double *y1, double *z1)
{
    /*
    xzz   旋转轴
    xzjd  旋转角度
    x0    原坐标x
    y0    原坐标y
    z0    原坐标z
    xp    旋转轴坐标x
    yp    旋转轴坐标y
    zp    旋转轴坐标z
    x1    变换后坐标x
    y1    变换后坐标y
    z1    变换后坐标z
    */
    double theta=-xzjd*M_PI/180.0;
    if (xzz == 0) { //x轴旋转
        *x1=x0;
        *y1=y0*cos(theta)-z0*sin(theta)+(1-cos(theta))*yp+sin(theta)*zp;
        *z1=y0*sin(theta)+z0*cos(theta)+(1-cos(theta))*zp-sin(theta)*yp;
    } else if (xzz == 1) { //y轴旋转
        *x1=z0*sin(theta)+x0*cos(theta)+(1-cos(theta))*xp-sin(theta)*zp;
        *y1=y0;
        *z1=z0*cos(theta)-x0*sin(theta)+(1-cos(theta))*zp+sin(theta)*xp;
    } else if (xzz == 2) { //z轴旋转
        *x1=x0*cos(theta)-y0*sin(theta)+(1-cos(theta))*xp+sin(theta)*yp;
        *y1=x0*sin(theta)+y0*cos(theta)+(1-cos(theta))*yp-sin(theta)*xp;
        *z1=z0;
    } else { //不旋转
        *x1=x0;
        *y1=y0;
        *z1=z0;
    }
}

void mag_rotate(int xzz, double xzjd, double Bx0, double By0, double Bz0, double *Bx1, double *By1, double *Bz1)
{
    /*
    xzz   旋转轴
    xzjd  旋转角度
    Bx0    原坐标Bx
    By0    原坐标By
    Bz0    原坐标Bz
    Bx1    变换后坐标Bx
    By1    变换后坐标By
    Bz1    变换后坐标Bz
    */
    double theta=xzjd*M_PI/180.0;
    if (xzz == 0) { //x轴旋转
        *Bx1=Bx0;
        *By1=By0*cos(theta)-Bz0*sin(theta);
        *Bz1=By0*sin(theta)+Bz0*cos(theta);
    } else if (xzz == 1) { //y轴旋转
        *Bx1=Bz0*sin(theta)+Bx0*cos(theta);
        *By1=By0;
        *Bz1=Bz0*cos(theta)-Bx0*sin(theta);
    } else if (xzz == 2) { //z轴旋转
        *Bx1=Bx0*cos(theta)-By0*sin(theta);
        *By1=Bx0*sin(theta)+By0*cos(theta);
        *Bz1=Bz0;
    } else { //不旋转
        *Bx1=Bx0;
        *By1=By0;
        *Bz1=Bz0;
    }
}

void Widget::on_add_magnet_clicked()
{
    // 增加磁铁
    magnet_num++;
    if (magnet_num > 100) {
        QMessageBox::critical(NULL,"错误","磁铁数达到上限。");
        magnet_num--;
    } else {
        xlh++;
        QString item_name="第 "+QString::number(xlh, 10)+" 号磁块";
        ui->listWidget->insertItem(magnet_num-1,item_name);
        para_x << 0; // x坐标
        para_y << 0; // y坐标
        para_z << 0; // z坐标
        para_a << 5; // x尺寸
        para_b << 5; // y尺寸
        para_c << 5; // z尺寸
        para_direction << 0; // 磁化方向
        para_m << 1000; // 磁化强度
        para_position << -1; // 开槽位置
        para_cao_h << 0; // 开槽深度
        para_cao_n << 0; // 负向边距
        para_cao_p << 0; // 正向边距
        para_axis << -1; // 旋转轴
        para_deg << 0; // 旋转角度
        move_list << 0; // 磁铁移动
    }
}

void Widget::on_cut_magnet_clicked()
{
    // 删减磁铁
    if (ui->listWidget->currentRow() >= 0) {
        para_x.remove(ui->listWidget->currentRow());
        para_y.remove(ui->listWidget->currentRow());
        para_z.remove(ui->listWidget->currentRow());
        para_a.remove(ui->listWidget->currentRow());
        para_b.remove(ui->listWidget->currentRow());
        para_c.remove(ui->listWidget->currentRow());
        para_direction.remove(ui->listWidget->currentRow());
        para_m.remove(ui->listWidget->currentRow());
        para_position.remove(ui->listWidget->currentRow());
        para_cao_h.remove(ui->listWidget->currentRow());
        para_cao_n.remove(ui->listWidget->currentRow());
        para_cao_p.remove(ui->listWidget->currentRow());
        para_axis.remove(ui->listWidget->currentRow());
        para_deg.remove(ui->listWidget->currentRow());
        move_list.remove(ui->listWidget->currentRow());

        magnet_num--;
        QListWidgetItem *item = ui->listWidget->takeItem(ui->listWidget->currentRow());
        delete item;
    }
}

void Widget::on_view_model_clicked()
{
    // 查看模型
    ui->tabWidget->setCurrentIndex(0);

    QVector<int> mag_d;
    for (int i = 0; i < magnet_num; i++) {
        if (para_m[i] > 0) { // 正向充磁
            if (para_direction[i] == 0) {
                mag_d << 11;
            } else if (para_direction[i] == 1) {
                mag_d << 21;
            } else {
                mag_d << 31;
            }
        } else { // 负向充磁
            if (para_direction[i] == 0) {
                mag_d << 12;
            }
            else if (para_direction[i] == 1) {
                mag_d << 22;
            }
            else {
                mag_d << 32;
            }
        }
    }

    ui->tab_1->setMagnetNum(magnet_num);
    ui->tab_1->setPara_x(para_x);
    ui->tab_1->setPara_y(para_y);
    ui->tab_1->setPara_z(para_z);
    ui->tab_1->setPara_a(para_a);
    ui->tab_1->setPara_b(para_b);
    ui->tab_1->setPara_c(para_c);
    ui->tab_1->setPara_direction(mag_d);
    ui->tab_1->setPara_m(para_m);
    ui->tab_1->setPara_position(para_position);
    ui->tab_1->setPara_cao_h(para_cao_h);
    ui->tab_1->setPara_cao_n(para_cao_n);
    ui->tab_1->setPara_cao_p(para_cao_p);
    ui->tab_1->setPara_axis(para_axis);
    ui->tab_1->setPara_deg(para_deg);

    ui->tab_1->plot=true;
    if (ui->cal_line->isChecked()) {
        ui->tab_1->cal_mode=1;
        ui->tab_1->l_start_x=ui->line_start_x->text().toDouble();
        ui->tab_1->l_start_y=ui->line_start_y->text().toDouble();
        ui->tab_1->l_start_z=ui->line_start_z->text().toDouble();
        ui->tab_1->l_stop_x=ui->line_stop_x->text().toDouble();
        ui->tab_1->l_stop_y=ui->line_stop_y->text().toDouble();
        ui->tab_1->l_stop_z=ui->line_stop_z->text().toDouble();
    } else if (ui->cal_plane->isChecked()) {
        ui->tab_1->cal_mode=2;
        ui->tab_1->z_pos=ui->plane_z->text().toDouble();
        ui->tab_1->px_start=ui->plane_x_start->text().toDouble();
        ui->tab_1->px_stop=ui->plane_x_stop->text().toDouble();
        ui->tab_1->py_start=ui->plane_y_start->text().toDouble();
        ui->tab_1->py_stop=ui->plane_y_stop->text().toDouble();
        ui->tab_1->cplane=ui->choose_plane->currentIndex();
    } else {
        ui->tab_1->cal_mode=3;
        ui->tab_1->p_x=ui->point_x->text().toDouble();
        ui->tab_1->p_y=ui->point_y->text().toDouble();
        ui->tab_1->p_z=ui->point_z->text().toDouble();
    }

    ui->tab_1->update();
}

void Widget::on_listWidget_clicked(const QModelIndex &index)
{
    // 点击显示磁铁参数
    ui->cx->setText(QString::number(para_x[index.row()])); // x坐标
    ui->cy->setText(QString::number(para_y[index.row()])); // y坐标
    ui->cz->setText(QString::number(para_z[index.row()])); // z坐标
    ui->a->setText(QString::number(para_a[index.row()])); // x尺寸
    ui->b->setText(QString::number(para_b[index.row()])); // y尺寸
    ui->c->setText(QString::number(para_c[index.row()])); // z尺寸
    ui->ccfx->setCurrentIndex(para_direction[index.row()]); // 磁化方向
    ui->chqd->setText(QString::number(para_m[index.row()])); // 磁化强度
    if (para_position[index.row()] == -1) { // 未开槽
        ui->kaicao->setChecked(false);
        ui->kaicaoweizhi->setEnabled(false);
        ui->cao_sd->setEnabled(false);
        ui->cao_zxbj->setEnabled(false);
        ui->cao_fxbj->setEnabled(false);
    } else {
        ui->kaicao->setChecked(true);
        ui->kaicaoweizhi->setEnabled(true);
        ui->cao_sd->setEnabled(true);
        ui->cao_zxbj->setEnabled(true);
        ui->cao_fxbj->setEnabled(true);
        ui->kaicaoweizhi->setCurrentIndex(para_position[index.row()]); // 开槽位置
        ui->cao_sd->setText(QString::number(para_cao_h[index.row()])); // 开槽深度
        ui->cao_fxbj->setText(QString::number(para_cao_n[index.row()])); // 负向边距
        ui->cao_zxbj->setText(QString::number(para_cao_p[index.row()])); // 正向边距
    }
    if (para_axis[index.row()] == -1) { // 未设置旋转
        ui->xz->setChecked(false);
        ui->xzz->setEnabled(false);
        ui->xzjd->setEnabled(false);
    } else {
        ui->xz->setChecked(true);
        ui->xzz->setEnabled(true);
        ui->xzjd->setEnabled(true);
        ui->xzz->setCurrentIndex(para_axis[index.row()]);
        ui->xzjd->setText(QString::number(para_deg[index.row()]));
    }
}

void Widget::on_kaicao_clicked(bool checked)
{
    // 是否开槽
    if (checked) {
        ui->kaicaoweizhi->setEnabled(true);
        ui->cao_sd->setEnabled(true);
        ui->cao_fxbj->setEnabled(true);
        ui->cao_zxbj->setEnabled(true);
        if (ui->listWidget->currentRow() >= 0) {
            para_position[ui->listWidget->currentRow()]=ui->kaicaoweizhi->currentIndex();
            para_cao_h[ui->listWidget->currentRow()]=ui->cao_sd->text().toDouble();
            para_cao_n[ui->listWidget->currentRow()]=ui->cao_fxbj->text().toDouble();
            para_cao_p[ui->listWidget->currentRow()]=ui->cao_zxbj->text().toDouble();
        }
    } else {
        ui->kaicaoweizhi->setEnabled(false);
        ui->cao_sd->setEnabled(false);
        ui->cao_fxbj->setEnabled(false);
        ui->cao_zxbj->setEnabled(false);
        if (ui->listWidget->currentRow() >= 0) {
            para_position[ui->listWidget->currentRow()]=-1;
            para_cao_h[ui->listWidget->currentRow()]=0;
            para_cao_n[ui->listWidget->currentRow()]=0;
            para_cao_p[ui->listWidget->currentRow()]=0;
        }
    }
}

void Widget::on_xz_clicked(bool checked)
{
    // 是否旋转
    if (checked) {
        ui->xzz->setEnabled(true);
        ui->xzjd->setEnabled(true);
        if (ui->listWidget->currentRow() >= 0) {
            para_axis[ui->listWidget->currentRow()]=ui->xzz->currentIndex();
            para_deg[ui->listWidget->currentRow()]=ui->xzjd->text().toDouble();
        }
    } else {
        ui->xzz->setEnabled(false);
        ui->xzjd->setEnabled(false);
        if (ui->listWidget->currentRow() >= 0) {
            para_axis[ui->listWidget->currentRow()]=-1;
            para_deg[ui->listWidget->currentRow()]=0;
        }
    }
}

void Widget::on_cx_editingFinished()
{
    // 设置中心坐标x
    QString tmp=ui->cx->text();
    if (tmp.length() > 0 && ui->listWidget->currentItem() != Q_NULLPTR && isNum(tmp)) {
        para_x[ui->listWidget->currentRow()]=tmp.toDouble();
    }
}

void Widget::on_cy_editingFinished()
{
    // 设置中心坐标y
    QString tmp=ui->cy->text();
    if (tmp.length() > 0 && ui->listWidget->currentItem() != Q_NULLPTR && isNum(tmp)) {
        para_y[ui->listWidget->currentRow()]=tmp.toDouble();
    }
}

void Widget::on_cz_editingFinished()
{
    // 设置中心坐标z
    QString tmp=ui->cz->text();
    if (tmp.length() > 0 && ui->listWidget->currentItem() != Q_NULLPTR && isNum(tmp)) {
        para_z[ui->listWidget->currentRow()]=tmp.toDouble();
    }
}

void Widget::on_a_editingFinished()
{
    // 设置尺寸a
    QString tmp=ui->a->text();
    if (tmp.length() > 0 && ui->listWidget->currentItem() != Q_NULLPTR && isNum(tmp)) {
        para_a[ui->listWidget->currentRow()]=tmp.toDouble();
    }
}

void Widget::on_b_editingFinished()
{
    // 设置尺寸b
    QString tmp=ui->b->text();
    if (tmp.length() > 0 && ui->listWidget->currentItem() != Q_NULLPTR && isNum(tmp)) {
        para_b[ui->listWidget->currentRow()]=tmp.toDouble();
    }
}

void Widget::on_c_editingFinished()
{
    // 设置尺寸c
    QString tmp=ui->c->text();
    if (tmp.length() > 0 && ui->listWidget->currentItem() != Q_NULLPTR && isNum(tmp)) {
        para_c[ui->listWidget->currentRow()]=tmp.toDouble();
    }
}

void Widget::on_ccfx_currentIndexChanged(int index)
{
    // 设置充磁方向
    para_direction[ui->listWidget->currentRow()]=index;
}

void Widget::on_chqd_editingFinished()
{
    // 设置磁化强度
    QString tmp=ui->chqd->text();
    if (tmp.length() > 0 && ui->listWidget->currentItem() != Q_NULLPTR && isNum(tmp)) {
        para_m[ui->listWidget->currentRow()]=tmp.toDouble();
    }
}

void Widget::on_kaicaoweizhi_currentIndexChanged(int index)
{
    // 设置开槽位置
    para_position[ui->listWidget->currentRow()]=index;
}

void Widget::on_cao_sd_editingFinished()
{
    // 设置开槽深度
    QString tmp=ui->cao_sd->text();
    if (tmp.length() > 0 && ui->listWidget->currentItem() != Q_NULLPTR && isNum(tmp)) {
        para_cao_h[ui->listWidget->currentRow()]=tmp.toDouble();
    }
}

void Widget::on_cao_fxbj_editingFinished()
{
    // 设置负向边距
    QString tmp=ui->cao_fxbj->text();
    if (tmp.length() > 0 && ui->listWidget->currentItem() != Q_NULLPTR && isNum(tmp)) {
        para_cao_n[ui->listWidget->currentRow()]=tmp.toDouble();
    }
}

void Widget::on_cao_zxbj_editingFinished()
{
    // 设置正向边距
    QString tmp=ui->cao_zxbj->text();
    if (tmp.length() > 0 && ui->listWidget->currentItem() != Q_NULLPTR && isNum(tmp)) {
        para_cao_p[ui->listWidget->currentRow()]=tmp.toDouble();
    }
}

void Widget::on_xzz_currentIndexChanged(int index)
{
    // 设置旋转轴
    para_axis[ui->listWidget->currentRow()]=index;
}

void Widget::on_xzjd_editingFinished()
{
    // 设置旋转角度
    QString tmp=ui->xzjd->text();
    if (tmp.length() > 0 && ui->listWidget->currentItem() != Q_NULLPTR && isNum(tmp)) {
        para_deg[ui->listWidget->currentRow()]=tmp.toDouble();
    }
}

void Widget::on_save_setting_clicked()
{
    // 保存设置
    QString filename = QFileDialog::getSaveFileName(this,"保存文件","/","TEXT FILE(*.txt)");
    QFile data(filename);
    if(data.open(QFile::WriteOnly|QFile::Truncate))
    {
        QTextStream out(&data);
        QString title="序号\tx(mm)\ty(mm)\tz(mm)\ta(mm)\tb(mm)\tc(mm)\t方向\tM(kA/m)\t开槽位置\t开槽深度(mm)\t负向边距(mm)\t正向边距(mm)\t旋转轴\t旋转角度(°)";
        out << title << "\r\n";
        for (int i = 0; i < ui->listWidget->count(); i++) {
            out << i+1 << "\t";
            out << QString::number(para_x[i],'f',4) << "\t";
            out << QString::number(para_y[i],'f',4) << "\t";
            out << QString::number(para_z[i],'f',4) << "\t";
            out << QString::number(para_a[i],'f',4) << "\t";
            out << QString::number(para_b[i],'f',4) << "\t";
            out << QString::number(para_c[i],'f',4) << "\t";
            out << para_direction[i] << "\t";
            out << QString::number(para_m[i],'f',4) << "\t";
            out << para_position[i] << "\t";
            out << QString::number(para_cao_h[i],'f',4) << "\t";
            out << QString::number(para_cao_n[i],'f',4) << "\t";
            out << QString::number(para_cao_p[i],'f',4) << "\t";
            out << para_axis[i] << "\t";
            out << QString::number(para_deg[i],'f',4) << "\r\n";
        }
        data.close();
    }

}

void Widget::on_import_setting_clicked()
{
    // 导入设置
    QString filename = QFileDialog::getOpenFileName(this,"打开文件","/","TEXT FILE(*.txt)");
    QFile data(filename);
    if(data.open(QIODevice::ReadOnly)) {
        para_x.clear();
        para_y.clear();
        para_z.clear();
        para_a.clear();
        para_b.clear();
        para_c.clear();
        para_direction.clear();
        para_m.clear();
        para_position.clear();
        para_cao_h.clear();
        para_cao_n.clear();
        para_cao_p.clear();
        para_axis.clear();
        para_deg.clear();
        move_list.clear();

        ui->listWidget->clear();

        QTextStream txtInput(&data);
        QString lineStr,item_name;
        QStringList myList;
        lineStr = txtInput.readLine();
        int i=0;
        while(!txtInput.atEnd())
        {
            lineStr = txtInput.readLine();
            myList = lineStr.split("\t");
            para_x << myList[1].toDouble();
            para_y << myList[2].toDouble();
            para_z << myList[3].toDouble();
            para_a << myList[4].toDouble();
            para_b << myList[5].toDouble();
            para_c << myList[6].toDouble();
            para_direction << myList[7].toInt();
            para_m << myList[8].toDouble();
            para_position << myList[9].toInt();
            para_cao_h << myList[10].toDouble();
            para_cao_n << myList[11].toDouble();
            para_cao_p << myList[12].toDouble();
            para_axis << myList[13].toInt();
            para_deg << myList[14].toDouble();
            move_list << 0;

            magnet_num=myList[0].toInt();
            xlh=i+1;
            item_name="第 "+QString::number(xlh, 10)+" 号磁块";
            ui->listWidget->insertItem(magnet_num-1,item_name);

            i++;
        }
        data.close();
    }
}

void Widget::on_cal_line_clicked()
{
    // 显示线计算标签
    ui->tabWidget_2->setCurrentIndex(0);
}

void Widget::on_cal_plane_clicked()
{
    // 显示面计算标签
    ui->tabWidget_2->setCurrentIndex(1);
}

void Widget::on_cal_point_clicked()
{
    // 显示磁铁移动标签
    ui->tabWidget_2->setCurrentIndex(2);
}

void Widget::on_calculate_clicked()
{
    // 计算磁场
    int i,j,k;
    double x,y,z,a,b,c,mB,m;
    double cao_x,cao_y,cao_z,cao_a,cao_b,cao_c;
    double tmp_Bx,tmp_By,tmp_Bz;
    double tmp2_Bx,tmp2_By,tmp2_Bz;
    double tmp_x,tmp_y,tmp_z;
    bool para_ok=true;
    int l_num,p_num;

    if (ui->cal_line->isChecked()) { // 计算磁场线分布
        double l_start_x=ui->line_start_x->text().toDouble();
        double l_start_y=ui->line_start_y->text().toDouble();
        double l_start_z=ui->line_start_z->text().toDouble();
        double l_stop_x=ui->line_stop_x->text().toDouble();
        double l_stop_y=ui->line_stop_y->text().toDouble();
        double l_stop_z=ui->line_stop_z->text().toDouble();
        l_num=ui->line_num->text().toInt();
        if ((l_start_x==l_stop_x) && (l_start_y==l_stop_y) && (l_start_z==l_stop_z)) {
            QMessageBox::critical(NULL,"错误","作图路径错误。");
            para_ok = false;
        }
        if (l_num < 2) {
            QMessageBox::critical(NULL,"错误","数据点数不能小于2。");
            para_ok = false;
        } else if (l_num>N_MAX_POINTS) {
            QMessageBox::critical(NULL,"错误","数据点数不能大于501。");
            para_ok = false;
        } else {
            //
        }

        if (para_ok) {
            // 参数填写正确，开始计算
            double length = sqrt((l_start_x - l_stop_x)*(l_start_x - l_stop_x) + (l_start_y - l_stop_y)*(l_start_y - l_stop_y) + (l_start_z - l_stop_z)*(l_start_z - l_stop_z));

            line_vBx.clear();
            line_vBy.clear();
            line_vBz.clear();

            line_rx.clear();
            line_ry.clear();
            line_rz.clear();

            line_x.clear();
            line_y.clear();
            line_z.clear();

            line_path.clear();

            for (j = 0; j < l_num; j++) {
                line_vBx << 0;
                line_vBy << 0;
                line_vBz << 0;

                line_rx << 0;
                line_ry << 0;
                line_rz << 0;

                line_x << l_start_x+j*(l_stop_x-l_start_x)/(l_num-1);
                line_y << l_start_y+j*(l_stop_y-l_start_y)/(l_num-1);
                line_z << l_start_z+j*(l_stop_z-l_start_z)/(l_num-1);
                line_path << j*length/(l_num-1);
            }

            for (i = 0; i < magnet_num; i++) {
                x = para_x[i];
                y = para_y[i];
                z = para_z[i];
                a = para_a[i];
                b = para_b[i];
                c = para_c[i];
                mB = para_direction[i];
                m = para_m[i];

                for (j = 0; j < l_num; j++) {
                    zm_rotate(para_axis[i], para_deg[i], line_x[j], line_y[j], line_z[j], x, y, z, &tmp_x, &tmp_y, &tmp_z);
                    line_rx[j]=tmp_x;
                    line_ry[j]=tmp_y;
                    line_rz[j]=tmp_z;
                }

                if (para_position[i] == -1) { // 不开槽
                    if (mB == 0) {	// x方向磁化
                        for (j = 0; j < l_num; j++) {
                            tmp_Bx=MxHx(m, a, b, c, x, y, z, line_rx[j] , line_ry[j] , line_rz[j]);
                            tmp_By=MxHy(m, a, b, c, x, y, z, line_rx[j] , line_ry[j] , line_rz[j]);
                            tmp_Bz=MxHz(m, a, b, c, x, y, z, line_rx[j] , line_ry[j] , line_rz[j]);
                            mag_rotate(para_axis[i], para_deg[i], tmp_Bx, tmp_By, tmp_Bz, &tmp2_Bx, &tmp2_By, &tmp2_Bz);
                            line_vBx[j] = line_vBx[j] + tmp2_Bx;
                            line_vBy[j] = line_vBy[j] + tmp2_By;
                            line_vBz[j] = line_vBz[j] + tmp2_Bz;
                        }
                    }
                    else if (mB == 1) {	// y方向磁化
                        for (j = 0; j < l_num; j++) {
                            tmp_Bx=MyHx(m, a, b, c, x, y, z, line_rx[j], line_ry[j], line_rz[j]);
                            tmp_By=MyHy(m, a, b, c, x, y, z, line_rx[j], line_ry[j], line_rz[j]);
                            tmp_Bz=MyHz(m, a, b, c, x, y, z, line_rx[j], line_ry[j], line_rz[j]);
                            mag_rotate(para_axis[i], para_deg[i], tmp_Bx, tmp_By, tmp_Bz, &tmp2_Bx, &tmp2_By, &tmp2_Bz);
                            line_vBx[j] = line_vBx[j] + tmp2_Bx;
                            line_vBy[j] = line_vBy[j] + tmp2_By;
                            line_vBz[j] = line_vBz[j] + tmp2_Bz;
                        }
                    }
                    else {	// z方向磁化
                        for (j = 0; j < l_num; j++) {
                            tmp_Bx=MzHx(m, a, b, c, x, y, z, line_rx[j], line_ry[j], line_rz[j]);
                            tmp_By=MzHy(m, a, b, c, x, y, z, line_rx[j], line_ry[j], line_rz[j]);
                            tmp_Bz=MzHz(m, a, b, c, x, y, z, line_rx[j], line_ry[j], line_rz[j]);
                            mag_rotate(para_axis[i], para_deg[i], tmp_Bx, tmp_By, tmp_Bz, &tmp2_Bx, &tmp2_By, &tmp2_Bz);
                            line_vBx[j] = line_vBx[j] + tmp2_Bx;
                            line_vBy[j] = line_vBy[j] + tmp2_By;
                            line_vBz[j] = line_vBz[j] + tmp2_Bz;
                        }
                    }
                }
                else { // 开槽
                    if (para_position[i] == 0) {
                        cao_a=a-para_cao_n[i]-para_cao_p[i];
                        cao_b=para_cao_h[i];
                        cao_c=c;
                        cao_x=x-a/2+para_cao_n[i]+cao_a/2;
                        cao_y=y-b/2+cao_b/2;
                        cao_z=z;
                    } else if (para_position[i] == 1) {
                        cao_a=a;
                        cao_b=para_cao_h[i];
                        cao_c=c-para_cao_n[i]-para_cao_p[i];
                        cao_x=x;
                        cao_y=y-b/2+cao_b/2;
                        cao_z=z-c/2+para_cao_n[i]+cao_c/2;
                    } else if (para_position[i] == 2) {
                        cao_a=a-para_cao_n[i]-para_cao_p[i];
                        cao_b=para_cao_h[i];
                        cao_c=c;
                        cao_x=x-a/2+para_cao_n[i]+cao_a/2;
                        cao_y=y+b/2-cao_b/2;
                        cao_z=z;
                    } else if (para_position[i] == 3) {
                        cao_a=a;
                        cao_b=para_cao_h[i];
                        cao_c=c-para_cao_n[i]-para_cao_p[i];
                        cao_x=x;
                        cao_y=y+b/2-cao_b/2;
                        cao_z=z-c/2+para_cao_n[i]+cao_c/2;
                    } else if (para_position[i] == 4) {
                        cao_a=a-para_cao_n[i]-para_cao_p[i];
                        cao_b=b;
                        cao_c=para_cao_h[i];
                        cao_x=x-a/2+para_cao_n[i]+cao_a/2;
                        cao_y=y;
                        cao_z=z+c/2-cao_c/2;
                    } else if (para_position[i] == 5) {
                        cao_a=a;
                        cao_b=b-para_cao_n[i]-para_cao_p[i];
                        cao_c=para_cao_h[i];
                        cao_x=x;
                        cao_y=y-b/2+para_cao_n[i]+cao_b/2;
                        cao_z=z+c/2-cao_c/2;
                    } else if (para_position[i] == 6) {
                        cao_a=a-para_cao_n[i]-para_cao_p[i];
                        cao_b=b;
                        cao_c=para_cao_h[i];
                        cao_x=x-a/2+para_cao_n[i]+cao_a/2;
                        cao_y=y;
                        cao_z=z-c/2+cao_c/2;
                    } else if (para_position[i] == 7) {
                        cao_a=a;
                        cao_b=b-para_cao_n[i]-para_cao_p[i];
                        cao_c=para_cao_h[i];
                        cao_x=x;
                        cao_y=y-b/2+para_cao_n[i]+cao_b/2;
                        cao_z=z-c/2+cao_c/2;
                    } else if (para_position[i] == 8) {
                        cao_a=para_cao_h[i];
                        cao_b=b;
                        cao_c=c-para_cao_n[i]-para_cao_p[i];
                        cao_x=x+a/2-cao_a/2;
                        cao_y=y;
                        cao_z=z-c/2+para_cao_n[i]+cao_c/2;
                    } else if (para_position[i] == 9) {
                        cao_a=para_cao_h[i];
                        cao_b=b-para_cao_n[i]-para_cao_p[i];
                        cao_c=c;
                        cao_x=x+a/2-cao_a/2;
                        cao_y=y-b/2+para_cao_n[i]+cao_b/2;
                        cao_z=z;
                    } else if (para_position[i] == 10) {
                        cao_a=para_cao_h[i];
                        cao_b=b;
                        cao_c=c-para_cao_n[i]-para_cao_p[i];
                        cao_x=x-a/2+cao_a/2;
                        cao_y=y;
                        cao_z=z-c/2+para_cao_n[i]+cao_c/2;
                    } else {
                        cao_a=para_cao_h[i];
                        cao_b=b-para_cao_n[i]-para_cao_p[i];
                        cao_c=c;
                        cao_x=x-a/2+cao_a/2;
                        cao_y=y-b/2+para_cao_n[i]+cao_b/2;
                        cao_z=z;
                    }

                    if (mB == 0) {	// x方向磁化
                        for (j = 0; j < l_num; j++) {
                            tmp_Bx=  MxHx(m, a, b, c, x, y, z, line_x[j], line_y[j], line_z[j])
                                   - MxHx(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, line_x[j], line_y[j], line_z[j]);
                            tmp_By=  MxHy(m, a, b, c, x, y, z, line_x[j], line_y[j], line_z[j])
                                   - MxHy(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, line_x[j], line_y[j], line_z[j]);
                            tmp_Bz=  MxHz(m, a, b, c, x, y, z, line_x[j], line_y[j], line_z[j])
                                   - MxHz(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, line_x[j], line_y[j], line_z[j]);
                            mag_rotate(para_axis[i], para_deg[i], tmp_Bx, tmp_By, tmp_Bz, &tmp2_Bx, &tmp2_By, &tmp2_Bz);
                            line_vBx[j] = line_vBx[j] + tmp2_Bx;
                            line_vBy[j] = line_vBy[j] + tmp2_By;
                            line_vBz[j] = line_vBz[j] + tmp2_Bz;
                        }
                    } else if (mB == 1) {	// y方向磁化
                        for (j = 0; j < l_num; j++) {
                            tmp_Bx=  MyHx(m, a, b, c, x, y, z, line_x[j], line_y[j], line_z[j])
                                   - MyHx(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, line_x[j], line_y[j], line_z[j]);
                            tmp_By=  MyHy(m, a, b, c, x, y, z, line_x[j], line_y[j], line_z[j])
                                   - MyHy(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, line_x[j], line_y[j], line_z[j]);
                            tmp_Bz=  MyHz(m, a, b, c, x, y, z, line_x[j], line_y[j], line_z[j])
                                   - MyHz(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, line_x[j], line_y[j], line_z[j]);
                            mag_rotate(para_axis[i], para_deg[i], tmp_Bx, tmp_By, tmp_Bz, &tmp2_Bx, &tmp2_By, &tmp2_Bz);
                            line_vBx[j] = line_vBx[j] + tmp2_Bx;
                            line_vBy[j] = line_vBy[j] + tmp2_By;
                            line_vBz[j] = line_vBz[j] + tmp2_Bz;
                        }
                    } else {	// z方向磁化
                        for (j = 0; j < l_num; j++) {
                            tmp_Bx=  MzHx(m, a, b, c, x, y, z, line_x[j], line_y[j], line_z[j])
                                   - MzHx(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, line_x[j], line_y[j], line_z[j]);
                            tmp_By=  MzHy(m, a, b, c, x, y, z, line_x[j], line_y[j], line_z[j])
                                   - MzHy(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, line_x[j], line_y[j], line_z[j]);
                            tmp_Bz=  MzHz(m, a, b, c, x, y, z, line_x[j], line_y[j], line_z[j])
                                   - MzHz(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, line_x[j], line_y[j], line_z[j]);
                            mag_rotate(para_axis[i], para_deg[i], tmp_Bx, tmp_By, tmp_Bz, &tmp2_Bx, &tmp2_By, &tmp2_Bz);
                            line_vBx[j] = line_vBx[j] + tmp2_Bx;
                            line_vBy[j] = line_vBy[j] + tmp2_By;
                            line_vBz[j] = line_vBz[j] + tmp2_Bz;
                        }
                    }
                }
            }

            // 画图
            print_line_plot();
        }
    } else if (ui->cal_plane->isChecked()) { // 计算磁场面分布
        double z_pos = ui->plane_z->text().toDouble(); // 平面坐标
        double px_start = ui->plane_x_start->text().toDouble();
        double px_stop = ui->plane_x_stop->text().toDouble();
        double py_start = ui->plane_y_start->text().toDouble();
        double py_stop = ui->plane_y_stop->text().toDouble();
        int px_num = ui->plane_x_num->text().toInt();
        int py_num = ui->plane_y_num->text().toInt();
        QVector<double> row_vector;

        if ((px_start>=px_stop) || (py_start>=py_stop)) {
            QMessageBox::critical(NULL,"错误","作图平面错误。");
            para_ok=false;
        }
        if (px_num < 2) {
            QMessageBox::critical(NULL,"错误","数据点数不能小于2。");
            para_ok=false;
        } else if (px_num>N_MAX_POINTS) {
            QMessageBox::critical(NULL,"错误","数据点数不能小于501。");
            para_ok=false;
        } else {
            //
        }
        if (py_num < 2) {
            QMessageBox::critical(NULL,"错误","数据点数不能小于2。");
            para_ok=false;
        } else if (py_num>N_MAX_POINTS) {
            QMessageBox::critical(NULL,"错误","数据点数不能小于501。");
            para_ok=false;
        } else {
            //
        }

        if (para_ok)
        {
            // 参数填写正确，开始计算
            plane_x.clear();
            plane_y.clear();
            plane_vBx.clear();
            plane_vBy.clear();
            plane_vBz.clear();
            for (i = 0; i < px_num; i++) {
                plane_x << px_start+i*(px_stop-px_start)/(px_num-1);
            }
            for (j = 0; j < py_num; j++) {
                plane_y << py_start+j*(py_stop-py_start)/(py_num-1);
            }

            row_vector.clear();
            for (j = 0; j < py_num; j++) {
                row_vector << 0;
            }
            for (i = 0; i < px_num; i++) {
                plane_vBx << row_vector;
                plane_vBy << row_vector;
                plane_vBz << row_vector;
            }

            if (ui->choose_plane->currentIndex() == 0) {
                // xy平面
                for (k = 0; k<magnet_num; k++) {
                    x = para_x[k];
                    y = para_y[k];
                    z = para_z[k];
                    a = para_a[k];
                    b = para_b[k];
                    c = para_c[k];
                    mB = para_direction[k];
                    m = para_m[k];

                    if (para_position[k] == -1) { // 不开槽
                        if (mB == 0) {	// x方向磁化
                            for (i = 0; i < px_num; i++) {
                                for (j = 0; j < py_num; j++) {
                                    zm_rotate(para_axis[k], para_deg[k], plane_x[i], plane_y[j], z_pos, x, y, z, &tmp_x, &tmp_y, &tmp_z);
                                    tmp_Bx=MxHx(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z);
                                    tmp_By=MxHy(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z);
                                    tmp_Bz=MxHz(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z);
                                    mag_rotate(para_axis[k], para_deg[k], tmp_Bx, tmp_By, tmp_Bz, &tmp2_Bx, &tmp2_By, &tmp2_Bz);
                                    plane_vBx[i][j]=plane_vBx[i][j]+tmp2_Bx;
                                    plane_vBy[i][j]=plane_vBy[i][j]+tmp2_By;
                                    plane_vBz[i][j]=plane_vBz[i][j]+tmp2_Bz;
                                }
                            }
                        } else if (mB == 1) { // y方向磁化
                            for (i = 0; i < px_num; i++) {
                                for (j = 0; j < py_num; j++) {
                                    zm_rotate(para_axis[k], para_deg[k], plane_x[i], plane_y[j], z_pos, x, y, z, &tmp_x, &tmp_y, &tmp_z);
                                    tmp_Bx=MyHx(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z);
                                    tmp_By=MyHy(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z);
                                    tmp_Bz=MyHz(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z);
                                    mag_rotate(para_axis[k], para_deg[k], tmp_Bx, tmp_By, tmp_Bz, &tmp2_Bx, &tmp2_By, &tmp2_Bz);
                                    plane_vBx[i][j]=plane_vBx[i][j]+tmp2_Bx;
                                    plane_vBy[i][j]=plane_vBy[i][j]+tmp2_By;
                                    plane_vBz[i][j]=plane_vBz[i][j]+tmp2_Bz;
                                }
                            }
                        } else { // z方向磁化
                            for (i = 0; i < px_num; i++) {
                                for (j = 0; j < py_num; j++) {
                                    zm_rotate(para_axis[k], para_deg[k], plane_x[i], plane_y[j], z_pos, x, y, z, &tmp_x, &tmp_y, &tmp_z);
                                    tmp_Bx=MzHx(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z);
                                    tmp_By=MzHy(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z);
                                    tmp_Bz=MzHz(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z);
                                    mag_rotate(para_axis[k], para_deg[k], tmp_Bx, tmp_By, tmp_Bz, &tmp2_Bx, &tmp2_By, &tmp2_Bz);
                                    plane_vBx[i][j]=plane_vBx[i][j]+tmp2_Bx;
                                    plane_vBy[i][j]=plane_vBy[i][j]+tmp2_By;
                                    plane_vBz[i][j]=plane_vBz[i][j]+tmp2_Bz;
                                }
                            }
                        }
                    }
                    else { // 开槽
                        if (para_position[k] == 0) {
                            cao_a=a-para_cao_n[k]-para_cao_p[k];
                            cao_b=para_cao_h[k];
                            cao_c=c;
                            cao_x=x-a/2+para_cao_n[k]+cao_a/2;
                            cao_y=y-b/2+cao_b/2;
                            cao_z=z;
                        } else if (para_position[k] == 1) {
                            cao_a=a;
                            cao_b=para_cao_h[k];
                            cao_c=c-para_cao_n[k]-para_cao_p[k];
                            cao_x=x;
                            cao_y=y-b/2+cao_b/2;
                            cao_z=z-c/2+para_cao_n[k]+cao_c/2;
                        } else if (para_position[k] == 2) {
                            cao_a=a-para_cao_n[k]-para_cao_p[k];
                            cao_b=para_cao_h[k];
                            cao_c=c;
                            cao_x=x-a/2+para_cao_n[k]+cao_a/2;
                            cao_y=y+b/2-cao_b/2;
                            cao_z=z;
                        } else if (para_position[k] == 3) {
                            cao_a=a;
                            cao_b=para_cao_h[k];
                            cao_c=c-para_cao_n[k]-para_cao_p[k];
                            cao_x=x;
                            cao_y=y+b/2-cao_b/2;
                            cao_z=z-c/2+para_cao_n[k]+cao_c/2;
                        } else if (para_position[k] == 4) {
                            cao_a=a-para_cao_n[k]-para_cao_p[k];
                            cao_b=b;
                            cao_c=para_cao_h[k];
                            cao_x=x-a/2+para_cao_n[k]+cao_a/2;
                            cao_y=y;
                            cao_z=z+c/2-cao_c/2;
                        } else if (para_position[k] == 5) {
                            cao_a=a;
                            cao_b=b-para_cao_n[k]-para_cao_p[k];
                            cao_c=para_cao_h[k];
                            cao_x=x;
                            cao_y=y-b/2+para_cao_n[k]+cao_b/2;
                            cao_z=z+c/2-cao_c/2;
                        } else if (para_position[k] == 6) {
                            cao_a=a-para_cao_n[k]-para_cao_p[k];
                            cao_b=b;
                            cao_c=para_cao_h[k];
                            cao_x=x-a/2+para_cao_n[k]+cao_a/2;
                            cao_y=y;
                            cao_z=z-c/2+cao_c/2;
                        } else if (para_position[k] == 7) {
                            cao_a=a;
                            cao_b=b-para_cao_n[k]-para_cao_p[k];
                            cao_c=para_cao_h[k];
                            cao_x=x;
                            cao_y=y-b/2+para_cao_n[k]+cao_b/2;
                            cao_z=z-c/2+cao_c/2;
                        } else if (para_position[k] == 8) {
                            cao_a=para_cao_h[k];
                            cao_b=b;
                            cao_c=c-para_cao_n[k]-para_cao_p[k];
                            cao_x=x+a/2-cao_a/2;
                            cao_y=y;
                            cao_z=z-c/2+para_cao_n[k]+cao_c/2;
                        } else if (para_position[k] == 9) {
                            cao_a=para_cao_h[k];
                            cao_b=b-para_cao_n[k]-para_cao_p[k];
                            cao_c=c;
                            cao_x=x+a/2-cao_a/2;
                            cao_y=y-b/2+para_cao_n[k]+cao_b/2;
                            cao_z=z;
                        } else if (para_position[k] == 10) {
                            cao_a=para_cao_h[k];
                            cao_b=b;
                            cao_c=c-para_cao_n[k]-para_cao_p[k];
                            cao_x=x-a/2+cao_a/2;
                            cao_y=y;
                            cao_z=z-c/2+para_cao_n[k]+cao_c/2;
                        } else {
                            cao_a=para_cao_h[k];
                            cao_b=b-para_cao_n[k]-para_cao_p[k];
                            cao_c=c;
                            cao_x=x-a/2+cao_a/2;
                            cao_y=y-b/2+para_cao_n[k]+cao_b/2;
                            cao_z=z;
                        }

                        if (mB == 0) {	// x方向磁化
                            for (i = 0; i < px_num; i++) {
                                for (j = 0; j < py_num; j++) {
                                    zm_rotate(para_axis[k], para_deg[k], plane_x[i], plane_y[j], z_pos, x, y, z, &tmp_x, &tmp_y, &tmp_z);
                                    tmp_Bx= MxHx(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z)
                                           -MxHx(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, tmp_x, tmp_y, tmp_z);
                                    tmp_By= MxHy(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z)
                                           -MxHy(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, tmp_x, tmp_y, tmp_z);
                                    tmp_Bz= MxHz(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z)
                                           -MxHz(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, tmp_x, tmp_y, tmp_z);
                                    mag_rotate(para_axis[k], para_deg[k], tmp_Bx, tmp_By, tmp_Bz, &tmp2_Bx, &tmp2_By, &tmp2_Bz);
                                    plane_vBx[i][j]=plane_vBx[i][j]+tmp2_Bx;
                                    plane_vBy[i][j]=plane_vBy[i][j]+tmp2_By;
                                    plane_vBz[i][j]=plane_vBz[i][j]+tmp2_Bz;
                                }
                            }
                        } else if (mB == 1) { // y方向磁化
                            for (i = 0; i < px_num; i++) {
                                for (j = 0; j < py_num; j++) {
                                    zm_rotate(para_axis[k], para_deg[k], plane_x[i], plane_y[j], z_pos, x, y, z, &tmp_x, &tmp_y, &tmp_z);
                                    tmp_Bx= MyHx(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z)
                                           -MyHx(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, tmp_x, tmp_y, tmp_z);
                                    tmp_By= MyHy(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z)
                                           -MyHy(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, tmp_x, tmp_y, tmp_z);
                                    tmp_Bz= MyHz(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z)
                                           -MyHz(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, tmp_x, tmp_y, tmp_z);
                                    mag_rotate(para_axis[k], para_deg[k], tmp_Bx, tmp_By, tmp_Bz, &tmp2_Bx, &tmp2_By, &tmp2_Bz);
                                    plane_vBx[i][j]=plane_vBx[i][j]+tmp2_Bx;
                                    plane_vBy[i][j]=plane_vBy[i][j]+tmp2_By;
                                    plane_vBz[i][j]=plane_vBz[i][j]+tmp2_Bz;
                                }
                            }
                        } else { // z方向磁化
                            for (i = 0; i < px_num; i++) {
                                for (j = 0; j < py_num; j++) {
                                    zm_rotate(para_axis[k], para_deg[k], plane_x[i], plane_y[j], z_pos, x, y, z, &tmp_x, &tmp_y, &tmp_z);
                                    tmp_Bx= MzHx(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z)
                                           -MzHx(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, tmp_x, tmp_y, tmp_z);
                                    tmp_By= MzHy(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z)
                                           -MzHy(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, tmp_x, tmp_y, tmp_z);
                                    tmp_Bz= MzHz(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z)
                                           -MzHz(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, tmp_x, tmp_y, tmp_z);
                                    mag_rotate(para_axis[k], para_deg[k], tmp_Bx, tmp_By, tmp_Bz, &tmp2_Bx, &tmp2_By, &tmp2_Bz);
                                    plane_vBx[i][j]=plane_vBx[i][j]+tmp2_Bx;
                                    plane_vBy[i][j]=plane_vBy[i][j]+tmp2_By;
                                    plane_vBz[i][j]=plane_vBz[i][j]+tmp2_Bz;
                                }
                            }
                        }
                    }
                }
            } else if (ui->choose_plane->currentIndex() == 1) {
                // xz平面
                for (k = 0; k<magnet_num; k++) {
                    x = para_x[k];
                    y = para_y[k];
                    z = para_z[k];
                    a = para_a[k];
                    b = para_b[k];
                    c = para_c[k];
                    mB = para_direction[k];
                    m = para_m[k];

                    if (para_position[k] == -1) { // 不开槽
                        if (mB == 0) {	// x方向磁化
                            for (i = 0; i < px_num; i++) {
                                for (j = 0; j < py_num; j++) {
                                    zm_rotate(para_axis[k], para_deg[k], plane_x[i], z_pos, plane_y[j], x, y, z, &tmp_x, &tmp_y, &tmp_z);
                                    tmp_Bx=MxHx(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z);
                                    tmp_By=MxHy(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z);
                                    tmp_Bz=MxHz(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z);
                                    mag_rotate(para_axis[k], para_deg[k], tmp_Bx, tmp_By, tmp_Bz, &tmp2_Bx, &tmp2_By, &tmp2_Bz);
                                    plane_vBx[i][j]=plane_vBx[i][j]+tmp2_Bx;
                                    plane_vBy[i][j]=plane_vBy[i][j]+tmp2_By;
                                    plane_vBz[i][j]=plane_vBz[i][j]+tmp2_Bz;
                                }
                            }
                        } else if (mB == 1) { // y方向磁化
                            for (i = 0; i < px_num; i++) {
                                for (j = 0; j < py_num; j++) {
                                    zm_rotate(para_axis[k], para_deg[k], plane_x[i], z_pos, plane_y[j], x, y, z, &tmp_x, &tmp_y, &tmp_z);
                                    tmp_Bx=MyHx(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z);
                                    tmp_By=MyHy(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z);
                                    tmp_Bz=MyHz(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z);
                                    mag_rotate(para_axis[k], para_deg[k], tmp_Bx, tmp_By, tmp_Bz, &tmp2_Bx, &tmp2_By, &tmp2_Bz);
                                    plane_vBx[i][j]=plane_vBx[i][j]+tmp2_Bx;
                                    plane_vBy[i][j]=plane_vBy[i][j]+tmp2_By;
                                    plane_vBz[i][j]=plane_vBz[i][j]+tmp2_Bz;
                                }
                            }
                        } else { // z方向磁化
                            for (i = 0; i < px_num; i++) {
                                for (j = 0; j < py_num; j++) {
                                    zm_rotate(para_axis[k], para_deg[k], plane_x[i], z_pos, plane_y[j], x, y, z, &tmp_x, &tmp_y, &tmp_z);
                                    tmp_Bx=MzHx(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z);
                                    tmp_By=MzHy(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z);
                                    tmp_Bz=MzHz(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z);
                                    mag_rotate(para_axis[k], para_deg[k], tmp_Bx, tmp_By, tmp_Bz, &tmp2_Bx, &tmp2_By, &tmp2_Bz);
                                    plane_vBx[i][j]=plane_vBx[i][j]+tmp2_Bx;
                                    plane_vBy[i][j]=plane_vBy[i][j]+tmp2_By;
                                    plane_vBz[i][j]=plane_vBz[i][j]+tmp2_Bz;
                                }
                            }
                        }
                    }
                    else { // 开槽
                        if (para_position[k] == 0) {
                            cao_a=a-para_cao_n[k]-para_cao_p[k];
                            cao_b=para_cao_h[k];
                            cao_c=c;
                            cao_x=x-a/2+para_cao_n[k]+cao_a/2;
                            cao_y=y-b/2+cao_b/2;
                            cao_z=z;
                        } else if (para_position[k] == 1) {
                            cao_a=a;
                            cao_b=para_cao_h[k];
                            cao_c=c-para_cao_n[k]-para_cao_p[k];
                            cao_x=x;
                            cao_y=y-b/2+cao_b/2;
                            cao_z=z-c/2+para_cao_n[k]+cao_c/2;
                        } else if (para_position[k] == 2) {
                            cao_a=a-para_cao_n[k]-para_cao_p[k];
                            cao_b=para_cao_h[k];
                            cao_c=c;
                            cao_x=x-a/2+para_cao_n[k]+cao_a/2;
                            cao_y=y+b/2-cao_b/2;
                            cao_z=z;
                        } else if (para_position[k] == 3) {
                            cao_a=a;
                            cao_b=para_cao_h[k];
                            cao_c=c-para_cao_n[k]-para_cao_p[k];
                            cao_x=x;
                            cao_y=y+b/2-cao_b/2;
                            cao_z=z-c/2+para_cao_n[k]+cao_c/2;
                        } else if (para_position[k] == 4) {
                            cao_a=a-para_cao_n[k]-para_cao_p[k];
                            cao_b=b;
                            cao_c=para_cao_h[k];
                            cao_x=x-a/2+para_cao_n[k]+cao_a/2;
                            cao_y=y;
                            cao_z=z-cao_c/2;
                        } else if (para_position[k] == 5) {
                            cao_a=a;
                            cao_b=b-para_cao_n[k]-para_cao_p[k];
                            cao_c=para_cao_h[k];
                            cao_x=x;
                            cao_y=y-b/2+para_cao_n[k]+cao_b/2;
                            cao_z=z-cao_c/2;
                        } else if (para_position[k] == 6) {
                            cao_a=a-para_cao_n[k]-para_cao_p[k];
                            cao_b=b;
                            cao_c=para_cao_h[k];
                            cao_x=x-a/2+para_cao_n[k]+cao_a/2;
                            cao_y=y;
                            cao_z=z-c/2+cao_c/2;
                        } else if (para_position[k] == 7) {
                            cao_a=a;
                            cao_b=b-para_cao_n[k]-para_cao_p[k];
                            cao_c=para_cao_h[k];
                            cao_x=x;
                            cao_y=y-b/2+para_cao_n[k]+cao_b/2;
                            cao_z=z-c/2+cao_c/2;
                        } else if (para_position[k] == 8) {
                            cao_a=para_cao_h[k];
                            cao_b=b;
                            cao_c=c-para_cao_n[k]-para_cao_p[k];
                            cao_x=x+a/2-cao_a/2;
                            cao_y=y;
                            cao_z=z-c/2+para_cao_n[k]+cao_c/2;
                        } else if (para_position[k] == 9) {
                            cao_a=para_cao_h[k];
                            cao_b=b-para_cao_n[k]-para_cao_p[k];
                            cao_c=c;
                            cao_x=x+a/2-cao_a/2;
                            cao_y=y;
                            cao_z=z-c/2+para_cao_n[k]+cao_c/2;
                        } else if (para_position[k] == 10) {
                            cao_a=para_cao_h[k];
                            cao_b=b;
                            cao_c=c-para_cao_n[k]-para_cao_p[k];
                            cao_x=x-a/2+cao_a/2;
                            cao_y=y;
                            cao_z=z-c/2+para_cao_n[k]+cao_c/2;
                        } else {
                            cao_a=para_cao_h[k];
                            cao_b=b-para_cao_n[k]-para_cao_p[k];
                            cao_c=c;
                            cao_x=x-a/2+cao_a/2;
                            cao_y=y;
                            cao_z=z-c/2+para_cao_n[k]+cao_c/2;
                        }

                        if (mB == 0) {	// x方向磁化
                            for (i = 0; i < px_num; i++) {
                                for (j = 0; j < py_num; j++) {
                                    zm_rotate(para_axis[k], para_deg[k], plane_x[i], z_pos, plane_y[j], x, y, z, &tmp_x, &tmp_y, &tmp_z);
                                    tmp_Bx= MxHx(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z)
                                           -MxHx(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, tmp_x, tmp_y, tmp_z);
                                    tmp_By= MxHy(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z)
                                           -MxHy(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, tmp_x, tmp_y, tmp_z);
                                    tmp_Bz= MxHz(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z)
                                           -MxHz(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, tmp_x, tmp_y, tmp_z);
                                    mag_rotate(para_axis[k], para_deg[k], tmp_Bx, tmp_By, tmp_Bz, &tmp2_Bx, &tmp2_By, &tmp2_Bz);
                                    plane_vBx[i][j]=plane_vBx[i][j]+tmp2_Bx;
                                    plane_vBy[i][j]=plane_vBy[i][j]+tmp2_By;
                                    plane_vBz[i][j]=plane_vBz[i][j]+tmp2_Bz;
                                }
                            }
                        } else if (mB == 1) { // y方向磁化
                            for (i = 0; i < px_num; i++) {
                                for (j = 0; j < py_num; j++) {
                                    zm_rotate(para_axis[k], para_deg[k], plane_x[i], z_pos, plane_y[j], x, y, z, &tmp_x, &tmp_y, &tmp_z);
                                    tmp_Bx= MyHx(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z)
                                           -MyHx(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, tmp_x, tmp_y, tmp_z);
                                    tmp_By= MyHy(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z)
                                           -MyHy(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, tmp_x, tmp_y, tmp_z);
                                    tmp_Bz= MyHz(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z)
                                           -MyHz(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, tmp_x, tmp_y, tmp_z);
                                    mag_rotate(para_axis[k], para_deg[k], tmp_Bx, tmp_By, tmp_Bz, &tmp2_Bx, &tmp2_By, &tmp2_Bz);
                                    plane_vBx[i][j]=plane_vBx[i][j]+tmp2_Bx;
                                    plane_vBy[i][j]=plane_vBy[i][j]+tmp2_By;
                                    plane_vBz[i][j]=plane_vBz[i][j]+tmp2_Bz;
                                }
                            }
                        } else { // z方向磁化
                            for (i = 0; i < px_num; i++) {
                                for (j = 0; j < py_num; j++) {
                                    zm_rotate(para_axis[k], para_deg[k], plane_x[i], z_pos, plane_y[j], x, y, z, &tmp_x, &tmp_y, &tmp_z);
                                    tmp_Bx= MzHx(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z)
                                           -MzHx(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, tmp_x, tmp_y, tmp_z);
                                    tmp_By= MzHy(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z)
                                           -MzHy(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, tmp_x, tmp_y, tmp_z);
                                    tmp_Bz= MzHz(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z)
                                           -MzHz(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, tmp_x, tmp_y, tmp_z);
                                    mag_rotate(para_axis[k], para_deg[k], tmp_Bx, tmp_By, tmp_Bz, &tmp2_Bx, &tmp2_By, &tmp2_Bz);
                                    plane_vBx[i][j]=plane_vBx[i][j]+tmp2_Bx;
                                    plane_vBy[i][j]=plane_vBy[i][j]+tmp2_By;
                                    plane_vBz[i][j]=plane_vBz[i][j]+tmp2_Bz;
                                }
                            }
                        }
                    }
                }
            } else {
                // yz平面
                for (k = 0; k<magnet_num; k++) {
                    x = para_x[k];
                    y = para_y[k];
                    z = para_z[k];
                    a = para_a[k];
                    b = para_b[k];
                    c = para_c[k];
                    mB = para_direction[k];
                    m = para_m[k];

                    if (para_position[k] == -1) { // 不开槽
                        if (mB == 0) {	// x方向磁化
                            for (i = 0; i < px_num; i++) {
                                for (j = 0; j < py_num; j++) {
                                    zm_rotate(para_axis[k], para_deg[k], z_pos, plane_x[i], plane_y[j], x, y, z, &tmp_x, &tmp_y, &tmp_z);
                                    tmp_Bx=MxHx(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z);
                                    tmp_By=MxHy(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z);
                                    tmp_Bz=MxHz(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z);
                                    mag_rotate(para_axis[k], para_deg[k], tmp_Bx, tmp_By, tmp_Bz, &tmp2_Bx, &tmp2_By, &tmp2_Bz);
                                    plane_vBx[i][j]=plane_vBx[i][j]+tmp2_Bx;
                                    plane_vBy[i][j]=plane_vBy[i][j]+tmp2_By;
                                    plane_vBz[i][j]=plane_vBz[i][j]+tmp2_Bz;
                                }
                            }
                        } else if (mB == 1) { // y方向磁化
                            for (i = 0; i < px_num; i++) {
                                for (j = 0; j < py_num; j++) {
                                    zm_rotate(para_axis[k], para_deg[k], z_pos, plane_x[i], plane_y[j], x, y, z, &tmp_x, &tmp_y, &tmp_z);
                                    tmp_Bx=MyHx(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z);
                                    tmp_By=MyHy(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z);
                                    tmp_Bz=MyHz(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z);
                                    mag_rotate(para_axis[k], para_deg[k], tmp_Bx, tmp_By, tmp_Bz, &tmp2_Bx, &tmp2_By, &tmp2_Bz);
                                    plane_vBx[i][j]=plane_vBx[i][j]+tmp2_Bx;
                                    plane_vBy[i][j]=plane_vBy[i][j]+tmp2_By;
                                    plane_vBz[i][j]=plane_vBz[i][j]+tmp2_Bz;
                                }
                            }
                        } else { // z方向磁化
                            for (i = 0; i < px_num; i++) {
                                for (j = 0; j < py_num; j++) {
                                    zm_rotate(para_axis[k], para_deg[k], z_pos, plane_x[i], plane_y[j], x, y, z, &tmp_x, &tmp_y, &tmp_z);
                                    tmp_Bx=MzHx(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z);
                                    tmp_By=MzHy(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z);
                                    tmp_Bz=MzHz(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z);
                                    mag_rotate(para_axis[k], para_deg[k], tmp_Bx, tmp_By, tmp_Bz, &tmp2_Bx, &tmp2_By, &tmp2_Bz);
                                    plane_vBx[i][j]=plane_vBx[i][j]+tmp2_Bx;
                                    plane_vBy[i][j]=plane_vBy[i][j]+tmp2_By;
                                    plane_vBz[i][j]=plane_vBz[i][j]+tmp2_Bz;
                                }
                            }
                        }
                    }
                    else { // 开槽
                        if (para_position[k] == 0) {
                            cao_a=a-para_cao_n[k]-para_cao_p[k];
                            cao_b=para_cao_h[k];
                            cao_c=c;
                            cao_x=x-a/2+para_cao_n[k]+cao_a/2;
                            cao_y=y-b/2+cao_b/2;
                            cao_z=z;
                        } else if (para_position[k] == 1) {
                            cao_a=a;
                            cao_b=para_cao_h[k];
                            cao_c=c-para_cao_n[k]-para_cao_p[k];
                            cao_x=x;
                            cao_y=y-b/2+cao_b/2;
                            cao_z=z-c/2+para_cao_n[k]+cao_c/2;
                        } else if (para_position[k] == 2) {
                            cao_a=a-para_cao_n[k]-para_cao_p[k];
                            cao_b=para_cao_h[k];
                            cao_c=c;
                            cao_x=x-a/2+para_cao_n[k]+cao_a/2;
                            cao_y=y+b/2-cao_b/2;
                            cao_z=z;
                        } else if (para_position[k] == 3) {
                            cao_a=a;
                            cao_b=para_cao_h[k];
                            cao_c=c-para_cao_n[k]-para_cao_p[k];
                            cao_x=x;
                            cao_y=y+b/2-cao_b/2;
                            cao_z=z-c/2+para_cao_n[k]+cao_c/2;
                        } else if (para_position[k] == 4) {
                            cao_a=a-para_cao_n[k]-para_cao_p[k];
                            cao_b=b;
                            cao_c=para_cao_h[k];
                            cao_x=x-a/2+para_cao_n[k]+cao_a/2;
                            cao_y=y;
                            cao_z=z-cao_c/2;
                        } else if (para_position[k] == 5) {
                            cao_a=a;
                            cao_b=b-para_cao_n[k]-para_cao_p[k];
                            cao_c=para_cao_h[k];
                            cao_x=x;
                            cao_y=y-b/2+para_cao_n[k]+cao_b/2;
                            cao_z=z-cao_c/2;
                        } else if (para_position[k] == 6) {
                            cao_a=a-para_cao_n[k]-para_cao_p[k];
                            cao_b=b;
                            cao_c=para_cao_h[k];
                            cao_x=x-a/2+para_cao_n[k]+cao_a/2;
                            cao_y=y;
                            cao_z=z-c/2+cao_c/2;
                        } else if (para_position[k] == 7) {
                            cao_a=a;
                            cao_b=b-para_cao_n[k]-para_cao_p[k];
                            cao_c=para_cao_h[k];
                            cao_x=x;
                            cao_y=y-b/2+para_cao_n[k]+cao_b/2;
                            cao_z=z-c/2+cao_c/2;
                        } else if (para_position[k] == 8) {
                            cao_a=para_cao_h[k];
                            cao_b=b;
                            cao_c=c-para_cao_n[k]-para_cao_p[k];
                            cao_x=x+a/2-cao_a/2;
                            cao_y=y;
                            cao_z=z-c/2+para_cao_n[k]+cao_c/2;
                        } else if (para_position[k] == 9) {
                            cao_a=para_cao_h[k];
                            cao_b=b-para_cao_n[k]-para_cao_p[k];
                            cao_c=c;
                            cao_x=x+a/2-cao_a/2;
                            cao_y=y;
                            cao_z=z-c/2+para_cao_n[k]+cao_c/2;
                        } else if (para_position[k] == 10) {
                            cao_a=para_cao_h[k];
                            cao_b=b;
                            cao_c=c-para_cao_n[k]-para_cao_p[k];
                            cao_x=x-a/2+cao_a/2;
                            cao_y=y;
                            cao_z=z-c/2+para_cao_n[k]+cao_c/2;
                        } else {
                            cao_a=para_cao_h[k];
                            cao_b=b-para_cao_n[k]-para_cao_p[k];
                            cao_c=c;
                            cao_x=x-a/2+cao_a/2;
                            cao_y=y;
                            cao_z=z-c/2+para_cao_n[k]+cao_c/2;
                        }

                        if (mB == 0) {	// x方向磁化
                            for (i = 0; i < px_num; i++) {
                                for (j = 0; j < py_num; j++) {
                                    zm_rotate(para_axis[k], para_deg[k], z_pos, plane_x[i], plane_y[j], x, y, z, &tmp_x, &tmp_y, &tmp_z);
                                    tmp_Bx= MxHx(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z)
                                           -MxHx(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, tmp_x, tmp_y, tmp_z);
                                    tmp_By= MxHy(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z)
                                           -MxHy(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, tmp_x, tmp_y, tmp_z);
                                    tmp_Bz= MxHz(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z)
                                           -MxHz(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, tmp_x, tmp_y, tmp_z);
                                    mag_rotate(para_axis[k], para_deg[k], tmp_Bx, tmp_By, tmp_Bz, &tmp2_Bx, &tmp2_By, &tmp2_Bz);
                                    plane_vBx[i][j]=plane_vBx[i][j]+tmp2_Bx;
                                    plane_vBy[i][j]=plane_vBy[i][j]+tmp2_By;
                                    plane_vBz[i][j]=plane_vBz[i][j]+tmp2_Bz;
                                }
                            }
                        } else if (mB == 1) { // y方向磁化
                            for (i = 0; i < px_num; i++) {
                                for (j = 0; j < py_num; j++) {
                                    zm_rotate(para_axis[k], para_deg[k], z_pos, plane_x[i], plane_y[j], x, y, z, &tmp_x, &tmp_y, &tmp_z);
                                    tmp_Bx= MyHx(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z)
                                           -MyHx(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, tmp_x, tmp_y, tmp_z);
                                    tmp_By= MyHy(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z)
                                           -MyHy(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, tmp_x, tmp_y, tmp_z);
                                    tmp_Bz= MyHz(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z)
                                           -MyHz(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, tmp_x, tmp_y, tmp_z);
                                    mag_rotate(para_axis[k], para_deg[k], tmp_Bx, tmp_By, tmp_Bz, &tmp2_Bx, &tmp2_By, &tmp2_Bz);
                                    plane_vBx[i][j]=plane_vBx[i][j]+tmp2_Bx;
                                    plane_vBy[i][j]=plane_vBy[i][j]+tmp2_By;
                                    plane_vBz[i][j]=plane_vBz[i][j]+tmp2_Bz;
                                }
                            }
                        } else { // z方向磁化
                            for (i = 0; i < px_num; i++) {
                                for (j = 0; j < py_num; j++) {
                                    zm_rotate(para_axis[k], para_deg[k], z_pos, plane_x[i], plane_y[j], x, y, z, &tmp_x, &tmp_y, &tmp_z);
                                    tmp_Bx= MzHx(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z)
                                           -MzHx(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, tmp_x, tmp_y, tmp_z);
                                    tmp_By= MzHy(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z)
                                           -MzHy(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, tmp_x, tmp_y, tmp_z);
                                    tmp_Bz= MzHz(m, a, b, c, x, y, z, tmp_x, tmp_y, tmp_z)
                                           -MzHz(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, tmp_x, tmp_y, tmp_z);
                                    mag_rotate(para_axis[k], para_deg[k], tmp_Bx, tmp_By, tmp_Bz, &tmp2_Bx, &tmp2_By, &tmp2_Bz);
                                    plane_vBx[i][j]=plane_vBx[i][j]+tmp2_Bx;
                                    plane_vBy[i][j]=plane_vBy[i][j]+tmp2_By;
                                    plane_vBz[i][j]=plane_vBz[i][j]+tmp2_Bz;
                                }
                            }
                        }
                    }
                }
            }
            // 画图
            print_plane_plot();
        }
    } else { // 计算磁铁移动
        double p_x=ui->point_x->text().toDouble();
        double p_y=ui->point_y->text().toDouble();
        double p_z=ui->point_z->text().toDouble();
        p_num=ui->point_num->text().toInt();

        if (p_num < 2) {
            QMessageBox::critical(NULL,"错误","数据点数不能小于2。");
            para_ok=false;
        } else if (p_num>N_MAX_POINTS) {
            QMessageBox::critical(NULL,"错误","数据点数不能小于501。");
            para_ok=false;
        } else {
            //
        }

        if (para_ok)
        {
            // 参数填写正确，开始计算
            double m_start=ui->move_start->text().toDouble();
            double m_stop=ui->move_stop->text().toDouble();
            double r_x=0,r_y=0,r_z=0;

            move_vBx.clear();
            move_vBy.clear();
            move_vBz.clear();
            move_path.clear();

            for (j = 0; j < p_num; j++) { // 磁铁移动
                move_vBx << 0;
                move_vBy << 0;
                move_vBz << 0;
                move_path << m_start+(double)j*(m_stop-m_start)/((double)p_num-1);
                for (i = 0; i < magnet_num; i++) { // 各块磁铁
                    x = para_x[i];
                    y = para_y[i];
                    z = para_z[i];
                    a = para_a[i];
                    b = para_b[i];
                    c = para_c[i];
                    mB = para_direction[i];
                    m = para_m[i];
                    if (ui->move_direction->currentIndex() == 0) { // x方向移动
                        x = para_x[i]+(double)move_list[i]*move_path[j];
                        y = para_y[i];
                        z = para_z[i];
                    } else if (ui->move_direction->currentIndex() == 1) { // y方向移动
                        x = para_x[i];
                        y = para_y[i]+(double)move_list[i]*move_path[j];
                        z = para_z[i];
                    } else { // z方向移动
                        x = para_x[i];
                        y = para_y[i];
                        z = para_z[i]+(double)move_list[i]*move_path[j];
                    }
                    zm_rotate((int)para_axis[i], para_deg[i], p_x, p_y, p_z, x, y, z, &r_x, &r_y, &r_z);

                    if (para_position[i] == -1) { // 不开槽
                        if (mB == 0) {	// x方向磁化
                            tmp_Bx=MxHx(m, a, b, c, x, y, z, r_x, r_y, r_z);
                            tmp_By=MxHy(m, a, b, c, x, y, z, r_x, r_y, r_z);
                            tmp_Bz=MxHz(m, a, b, c, x, y, z, r_x, r_y, r_z);
                            mag_rotate((int)para_axis[i], para_deg[i], tmp_Bx, tmp_By, tmp_Bz, &tmp2_Bx, &tmp2_By, &tmp2_Bz);
                            move_vBx[j] = move_vBx[j] + tmp2_Bx;
                            move_vBy[j] = move_vBy[j] + tmp2_By;
                            move_vBz[j] = move_vBz[j] + tmp2_Bz;
                        }
                        else if (mB == 1) {	// y方向磁化
                            tmp_Bx=MyHx(m, a, b, c, x, y, z, r_x, r_y, r_z);
                            tmp_By=MyHy(m, a, b, c, x, y, z, r_x, r_y, r_z);
                            tmp_Bz=MyHz(m, a, b, c, x, y, z, r_x, r_y, r_z);
                            mag_rotate((int)para_axis[i], para_deg[i], tmp_Bx, tmp_By, tmp_Bz, &tmp2_Bx, &tmp2_By, &tmp2_Bz);
                            move_vBx[j] = move_vBx[j] + tmp2_Bx;
                            move_vBy[j] = move_vBy[j] + tmp2_By;
                            move_vBz[j] = move_vBz[j] + tmp2_Bz;
                        }
                        else {	// z方向磁化
                            tmp_Bx=MzHx(m, a, b, c, x, y, z, r_x, r_y, r_z);
                            tmp_By=MzHy(m, a, b, c, x, y, z, r_x, r_y, r_z);
                            tmp_Bz=MzHz(m, a, b, c, x, y, z, r_x, r_y, r_z);
                            mag_rotate((int)para_axis[i], para_deg[i], tmp_Bx, tmp_By, tmp_Bz, &tmp2_Bx, &tmp2_By, &tmp2_Bz);
                            move_vBx[j] = move_vBx[j] + tmp2_Bx;
                            move_vBy[j] = move_vBy[j] + tmp2_By;
                            move_vBz[j] = move_vBz[j] + tmp2_Bz;
                        }
                    } else { // 开槽
                        if (para_position[i] == 0) {
                            cao_a=a-para_cao_n[i]-para_cao_p[i];
                            cao_b=para_cao_h[i];
                            cao_c=c;
                            cao_x=x-a/2+para_cao_n[i]+cao_a/2;
                            cao_y=y-b/2+cao_b/2;
                            cao_z=z;
                        } else if (para_position[i] == 1) {
                            cao_a=a;
                            cao_b=para_cao_h[i];
                            cao_c=c-para_cao_n[i]-para_cao_p[i];
                            cao_x=x;
                            cao_y=y-b/2+cao_b/2;
                            cao_z=z-c/2+para_cao_n[i]+cao_c/2;
                        } else if (para_position[i] == 2) {
                            cao_a=a-para_cao_n[i]-para_cao_p[i];
                            cao_b=para_cao_h[i];
                            cao_c=c;
                            cao_x=x-a/2+para_cao_n[i]+cao_a/2;
                            cao_y=y+b/2-cao_b/2;
                            cao_z=z;
                        } else if (para_position[i] == 3) {
                            cao_a=a;
                            cao_b=para_cao_h[i];
                            cao_c=c-para_cao_n[i]-para_cao_p[i];
                            cao_x=x;
                            cao_y=y+b/2-cao_b/2;
                            cao_z=z-c/2+para_cao_n[i]+cao_c/2;
                        } else if (para_position[i] == 4) {
                            cao_a=a-para_cao_n[i]-para_cao_p[i];
                            cao_b=b;
                            cao_c=para_cao_h[i];
                            cao_x=x-a/2+para_cao_n[i]+cao_a/2;
                            cao_y=y;
                            cao_z=z+c/2-cao_c/2;
                        } else if (para_position[i] == 5) {
                            cao_a=a;
                            cao_b=b-para_cao_n[i]-para_cao_p[i];
                            cao_c=para_cao_h[i];
                            cao_x=x;
                            cao_y=y-b/2+para_cao_n[i]+cao_b/2;
                            cao_z=z+c/2-cao_c/2;
                        } else if (para_position[i] == 6) {
                            cao_a=a-para_cao_n[i]-para_cao_p[i];
                            cao_b=b;
                            cao_c=para_cao_h[i];
                            cao_x=x-a/2+para_cao_n[i]+cao_a/2;
                            cao_y=y;
                            cao_z=z-c/2+cao_c/2;
                        } else if (para_position[i] == 7) {
                            cao_a=a;
                            cao_b=b-para_cao_n[i]-para_cao_p[i];
                            cao_c=para_cao_h[i];
                            cao_x=x;
                            cao_y=y-b/2+para_cao_n[i]+cao_b/2;
                            cao_z=z-c/2+cao_c/2;
                        } else if (para_position[i] == 8) {
                            cao_a=para_cao_h[i];
                            cao_b=b;
                            cao_c=c-para_cao_n[i]-para_cao_p[i];
                            cao_x=x+a/2-cao_a/2;
                            cao_y=y;
                            cao_z=z-c/2+para_cao_n[i]+cao_c/2;
                        } else if (para_position[i] == 9) {
                            cao_a=para_cao_h[i];
                            cao_b=b-para_cao_n[i]-para_cao_p[i];
                            cao_c=c;
                            cao_x=x+a/2-cao_a/2;
                            cao_y=y-b/2+para_cao_n[i]+cao_b/2;
                            cao_z=z;
                        } else if (para_position[i] == 10) {
                            cao_a=para_cao_h[i];
                            cao_b=b;
                            cao_c=c-para_cao_n[i]-para_cao_p[i];
                            cao_x=x-a/2+cao_a/2;
                            cao_y=y;
                            cao_z=z-c/2+para_cao_n[i]+cao_c/2;
                        } else {
                            cao_a=para_cao_h[i];
                            cao_b=b-para_cao_n[i]-para_cao_p[i];
                            cao_c=c;
                            cao_x=x-a/2+cao_a/2;
                            cao_y=y-b/2+para_cao_n[i]+cao_b/2;
                            cao_z=z;
                        }

                        if (mB == 0) {	// x方向磁化
                            tmp_Bx= MxHx(m, a, b, c, x, y, z, r_x, r_y, r_z)
                                   -MxHx(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, r_x, r_y, r_z);
                            tmp_By= MxHy(m, a, b, c, x, y, z, r_x, r_y, r_z)
                                   -MxHy(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, r_x, r_y, r_z);
                            tmp_Bz= MxHz(m, a, b, c, x, y, z, r_x, r_y, r_z)
                                   -MxHz(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, r_x, r_y, r_z);
                            mag_rotate((int)para_axis[i], para_deg[i], tmp_Bx, tmp_By, tmp_Bz, &tmp2_Bx, &tmp2_By, &tmp2_Bz);
                            move_vBx[j] = move_vBx[j] + tmp2_Bx;
                            move_vBy[j] = move_vBy[j] + tmp2_By;
                            move_vBz[j] = move_vBz[j] + tmp2_Bz;
                        }
                        else if (mB == 1) {	// y方向磁化
                            tmp_Bx= MyHx(m, a, b, c, x, y, z, r_x, r_y, r_z)
                                   -MyHx(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, r_x, r_y, r_z);
                            tmp_By= MyHy(m, a, b, c, x, y, z, r_x, r_y, r_z)
                                   -MyHy(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, r_x, r_y, r_z);
                            tmp_Bz= MyHz(m, a, b, c, x, y, z, r_x, r_y, r_z)
                                   -MyHz(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, r_x, r_y, r_z);
                            mag_rotate((int)para_axis[i], para_deg[i], tmp_Bx, tmp_By, tmp_Bz, &tmp2_Bx, &tmp2_By, &tmp2_Bz);
                            move_vBx[j] = move_vBx[j] + tmp2_Bx;
                            move_vBy[j] = move_vBy[j] + tmp2_By;
                            move_vBz[j] = move_vBz[j] + tmp2_Bz;
                        }
                        else {	// z方向磁化
                            tmp_Bx= MzHx(m, a, b, c, x, y, z, r_x, r_y, r_z)
                                   -MzHx(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, r_x, r_y, r_z);
                            tmp_By= MzHy(m, a, b, c, x, y, z, r_x, r_y, r_z)
                                   -MzHy(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, r_x, r_y, r_z);
                            tmp_Bz= MzHz(m, a, b, c, x, y, z, r_x, r_y, r_z)
                                   -MzHz(m, cao_a, cao_b, cao_c, cao_x, cao_y, cao_z, r_x, r_y, r_z);
                            mag_rotate((int)para_axis[i], para_deg[i], tmp_Bx, tmp_By, tmp_Bz, &tmp2_Bx, &tmp2_By, &tmp2_Bz);
                            move_vBx[j] = move_vBx[j] + tmp2_Bx;
                            move_vBy[j] = move_vBy[j] + tmp2_By;
                            move_vBz[j] = move_vBz[j] + tmp2_Bz;
                        }
                    } // 槽
                } // 各块磁铁
            } // 磁铁移动
        } // para_ok

        // 画图
        print_point_plot();
    }
}

void Widget::my_mouseMove(QMouseEvent* event)
{
    // 线分布鼠标捕捉
    if (!ui->show_cross->isChecked()) {
        QPoint mousepos = event->pos();
        if ( mousepos.rx() > 0 && mousepos.rx() < ui->tab_2->width()  && mousepos.ry() > 0 && mousepos.ry() < ui->tab_2->height() ) {
            ui->tab_2->setCursor(Qt::CrossCursor);
        } else {
            ui->tab_2->setCursor(Qt::ArrowCursor);      //范围之外变回原来形状
        }
    }

    if (line_caled) {
        // 获取曲线图鼠标坐标点
        int x_pos = event->pos().x();
        int y_pos = event->pos().y();

        // 把鼠标坐标点 转换为 QCustomPlot 内部坐标值 （pixelToCoord 函数）
        // coordToPixel 函数与之相反 是把内部坐标值 转换为外部坐标点
        double x_val = ui->tab_2->xAxis->pixelToCoord(x_pos);
        double y_val = ui->tab_2->yAxis->pixelToCoord(y_pos);

        double l_start_x=ui->line_start_x->text().toDouble();
        double l_start_y=ui->line_start_y->text().toDouble();
        double l_start_z=ui->line_start_z->text().toDouble();
        double l_stop_x=ui->line_stop_x->text().toDouble();
        double l_stop_y=ui->line_stop_y->text().toDouble();
        double l_stop_z=ui->line_stop_z->text().toDouble();
        double length=sqrt( (l_stop_x-l_start_x)*(l_stop_x-l_start_x)+(l_stop_y-l_start_y)*(l_stop_y-l_start_y)+(l_stop_z-l_start_z)*(l_stop_z-l_start_z) );

        // 打印在界面上
        if (l_start_x != l_stop_x && l_start_y == l_stop_y && l_start_z == l_stop_z) {
            if (x_val < l_start_x) {
                x_val = l_start_x;
            }
            if (x_val > l_stop_x) {
                x_val = l_stop_x;
            }
            ui->ox->setText(QString::number(x_val,'f',2));
            ui->oy->setText(QString::number(l_start_y));
            ui->oz->setText(QString::number(l_start_z));
        } else if (l_start_x == l_stop_x && l_start_y != l_stop_y && l_start_z == l_stop_z) {
            if (x_val < l_start_y) {
                x_val = l_start_y;
            }
            if (x_val > l_stop_y) {
                x_val = l_stop_y;
            }
            ui->ox->setText(QString::number(l_start_x));
            ui->oy->setText(QString::number(x_val,'f',2));
            ui->oz->setText(QString::number(l_start_z));
        } else if (l_start_x == l_stop_x && l_start_y == l_stop_y && l_start_z != l_stop_z) {
            if (x_val < l_start_z) {
                x_val = l_start_z;
            }
            if (x_val > l_stop_z) {
                x_val = l_stop_z;
            }
            ui->ox->setText(QString::number(l_start_x));
            ui->oy->setText(QString::number(l_start_y));
            ui->oz->setText(QString::number(x_val,'f',2));
        } else {
            if (l_start_x+(l_stop_x-l_start_x)*x_val/length < l_start_x) {
                ui->ox->setText(QString::number(l_start_x,'f',2));
            } else if (l_start_x+(l_stop_x-l_start_x)*x_val/length > l_stop_x) {
                ui->ox->setText(QString::number(l_stop_x,'f',2));
            } else {
                ui->ox->setText(QString::number(l_start_x+(l_stop_x-l_start_x)*x_val/length,'f',2));
            }
            if (l_start_y+(l_stop_y-l_start_y)*x_val/length < l_start_y) {
                ui->ox->setText(QString::number(l_start_y,'f',2));
            } else if (l_start_y+(l_stop_y-l_start_y)*x_val/length > l_stop_y) {
                ui->ox->setText(QString::number(l_stop_y,'f',2));
            } else {
                ui->ox->setText(QString::number(l_start_y+(l_stop_y-l_start_y)*x_val/length,'f',2));
            }
            if (l_start_z+(l_stop_z-l_start_z)*x_val/length < l_start_z) {
                ui->ox->setText(QString::number(l_start_z,'f',2));
            } else if (l_start_z+(l_stop_z-l_start_z)*x_val/length > l_stop_z) {
                ui->ox->setText(QString::number(l_stop_z,'f',2));
            } else {
                ui->ox->setText(QString::number(l_start_z+(l_stop_z-l_start_z)*x_val/length,'f',2));
            }
        }
        ui->ob->setText(QString::number(y_val,'f',3));

        if (!line_checkbox_modified) {
            int i=-1;
            if (ui->line_Bx->isChecked()) {
                i++;
            }
            if (ui->line_By->isChecked()) {
                i++;
            }
            if (ui->line_Bz->isChecked()) {
                i++;
            }
            // 画鼠标十字
            if (ui->tab_2->plotLayout()->rowCount() > 1 && ui->show_cross->isChecked()) {
                if (ui->tab_2->graphCount() == i+1) {
                    // 添加十字光标
                    ui->tab_2->addGraph();
                    ui->tab_2->addGraph();
                    ui->tab_2->graph(i+1)->removeFromLegend(); // 去掉图例
                    ui->tab_2->graph(i+2)->removeFromLegend(); // 去掉图例
                }
                QVector<double> vx,vy;
                vx << ui->tab_2->xAxis->range().lower << x_val << ui->tab_2->xAxis->range().upper;
                vy << y_val << y_val << y_val;
                ui->tab_2->graph(i+1)->setData(vx,vy);
                ui->tab_2->graph(i+1)->setPen(QPen(Qt::black));
                vx.clear();
                vy.clear();
                vx << x_val << x_val << x_val;
                vy << ui->tab_2->yAxis->range().lower << y_val << ui->tab_2->yAxis->range().upper;
                ui->tab_2->graph(i+2)->setData(vx,vy);
                ui->tab_2->graph(i+2)->setPen(QPen(Qt::black));
                ui->tab_2->replot();
            }
        }
    }
}

void Widget::my_mouseMove_2(QMouseEvent* event)
{
    // 面分布鼠标捕捉
    QPoint mousepos = event->pos();
    if ( mousepos.rx() > 0 && mousepos.rx() < ui->tab_3->width()  && mousepos.ry() > 0 && mousepos.ry() < ui->tab_3->height() ) {
        ui->tab_3->setCursor(Qt::CrossCursor);
    } else {
        ui->tab_3->setCursor(Qt::ArrowCursor);      //范围之外变回原来形状
    }

    if (plane_caled) {
        // 获取面分布图鼠标坐标点
        int x_pos = event->pos().x();
        int y_pos = event->pos().y();

        // 把鼠标坐标点 转换为 QCustomPlot 内部坐标值 （pixelToCoord 函数）
        // coordToPixel 函数与之相反 是把内部坐标值 转换为外部坐标点
        double x_val = ui->tab_3->xAxis->pixelToCoord(x_pos);
        double y_val = ui->tab_3->yAxis->pixelToCoord(y_pos);
        double z_val = ui->plane_z->text().toDouble();

        double x_start = ui->plane_x_start->text().toDouble();
        double x_stop = ui->plane_x_stop->text().toDouble();
        int x_num = ui->plane_x_num->text().toInt();
        double y_start = ui->plane_y_start->text().toDouble();
        double y_stop = ui->plane_y_stop->text().toDouble();
        int y_num = ui->plane_y_num->text().toInt();
        int xx = floor((x_val-x_start)/(x_stop-x_start)*x_num);
        int yy = floor((y_val-y_start)/(y_stop-y_start)*y_num);
        if (xx < 0) {
            xx = 0;
        }
        if (xx >= x_num) {
            xx = x_num-1;
        }
        if (yy < 0) {
            yy = 0;
        }
        if (yy >= y_num) {
            yy = y_num-1;
        }
        double b_val;
        if (ui->pBx->isChecked()) {
            b_val = plane_vBx[xx][yy];
        } else if (ui->pBy->isChecked()) {
            b_val = plane_vBy[xx][yy];
        } else {
            b_val = plane_vBz[xx][yy];
        }

        if (ui->choose_plane->currentIndex() == 0) { // xy平面
            if (x_val < x_start) {
                ui->ox->setText(QString::number(x_start,'f',2));
            } else if (x_val > x_stop) {
                ui->ox->setText(QString::number(x_stop,'f',2));
            } else {
                ui->ox->setText(QString::number(x_val,'f',2));
            }
            if (y_val < y_start) {
                ui->oy->setText(QString::number(y_start,'f',2));
            } else if (y_val > y_stop) {
                ui->oy->setText(QString::number(y_stop,'f',2));
            } else {
                ui->oy->setText(QString::number(y_val,'f',2));
            }
            ui->oz->setText(QString::number(z_val,'f',2));
            ui->ob->setText(QString::number(b_val,'f',3));
        } else if (ui->choose_plane->currentIndex() == 1) { // xz平面
            if (x_val < x_start) {
                ui->ox->setText(QString::number(x_start,'f',2));
            } else if (x_val > x_stop) {
                ui->ox->setText(QString::number(x_stop,'f',2));
            } else {
                ui->ox->setText(QString::number(x_val,'f',2));
            }
            if (y_val < y_start) {
                ui->oz->setText(QString::number(y_start,'f',2));
            } else if (y_val > y_stop) {
                ui->oz->setText(QString::number(y_stop,'f',2));
            } else {
                ui->oz->setText(QString::number(y_val,'f',2));
            }
            ui->oy->setText(QString::number(z_val,'f',2));
            ui->ob->setText(QString::number(b_val,'f',3));
        } else { // yz平面
            if (x_val < x_start) {
                ui->oy->setText(QString::number(x_start,'f',2));
            } else if (x_val > x_stop) {
                ui->oy->setText(QString::number(x_stop,'f',2));
            } else {
                ui->oy->setText(QString::number(x_val,'f',2));
            }
            if (y_val < y_start) {
                ui->oz->setText(QString::number(y_start,'f',2));
            } else if (y_val > y_stop) {
                ui->oz->setText(QString::number(y_stop,'f',2));
            } else {
                ui->oz->setText(QString::number(y_val,'f',2));
            }
            ui->ox->setText(QString::number(z_val,'f',2));
            ui->ob->setText(QString::number(b_val,'f',3));
        }
    }
}

void Widget::my_mouseMove_3(QMouseEvent* event)
{
    // 磁铁移动，鼠标捕捉
    QPoint mousepos = event->pos();
    if (!ui->show_cross->isChecked()) {
        if ( mousepos.rx() > 0 && mousepos.rx() < ui->tab_7->width()  && mousepos.ry() > 0 && mousepos.ry() < ui->tab_7->height() ) {
            ui->tab_7->setCursor(Qt::CrossCursor);
        } else {
            ui->tab_7->setCursor(Qt::ArrowCursor);      //范围之外变回原来形状
        }
    }

    if (point_caled) {
        // 获取标坐标点
        int x_pos = event->pos().x();
        int y_pos = event->pos().y();
        double x_val = ui->tab_7->xAxis->pixelToCoord(x_pos);
        double y_val = ui->tab_7->yAxis->pixelToCoord(y_pos);

        double p_x=ui->point_x->text().toDouble();
        double p_y=ui->point_y->text().toDouble();
        double p_z=ui->point_z->text().toDouble();
        double m_start=ui->move_start->text().toDouble();
        double m_stop=ui->move_stop->text().toDouble();

        if (x_val < m_start) {
            x_val = m_start;
        }
        if (x_val > m_stop) {
            x_val = m_stop;
        }

        if (ui->move_direction->currentIndex() == 0) { // x方向移动
            ui->ox->setText(QString::number(x_val,'f',2));
            ui->oy->setText(QString::number(p_y,'f',2));
            ui->oz->setText(QString::number(p_z,'f',2));
            ui->ob->setText(QString::number(y_val,'f',3));
        } else if (ui->move_direction->currentIndex() == 1) { // y方向移动
            ui->ox->setText(QString::number(p_x,'f',2));
            ui->oy->setText(QString::number(x_val,'f',2));
            ui->oz->setText(QString::number(p_z,'f',2));
            ui->ob->setText(QString::number(y_val,'f',3));
        } else { // z方向移动
            ui->ox->setText(QString::number(p_x,'f',2));
            ui->oy->setText(QString::number(p_y,'f',2));
            ui->oz->setText(QString::number(x_val,'f',2));
            ui->ob->setText(QString::number(y_val,'f',3));
        }

        if (!point_checkbox_modified) {
            int i=-1;
            if (ui->p_Bx->isChecked()) {
                i++;
            }
            if (ui->p_By->isChecked()) {
                i++;
            }
            if (ui->p_Bz->isChecked()) {
                i++;
            }
            // 画鼠标十字
            if (ui->tab_7->plotLayout()->rowCount() > 1 && ui->show_cross->isChecked()) {
                if (ui->tab_7->graphCount() == i+1) {
                    // 添加十字光标
                    ui->tab_7->addGraph();
                    ui->tab_7->addGraph();
                    ui->tab_7->graph(i+1)->removeFromLegend(); // 去掉图例
                    ui->tab_7->graph(i+2)->removeFromLegend(); // 去掉图例
                }
                QVector<double> vx,vy;
                vx << ui->tab_7->xAxis->range().lower << x_val << ui->tab_7->xAxis->range().upper;
                vy << y_val << y_val << y_val;
                ui->tab_7->graph(i+1)->setData(vx,vy);
                ui->tab_7->graph(i+1)->setPen(QPen(Qt::black));
                vx.clear();
                vy.clear();
                vx << x_val << x_val << x_val;
                vy << ui->tab_7->yAxis->range().lower << y_val << ui->tab_7->yAxis->range().upper;
                ui->tab_7->graph(i+2)->setData(vx,vy);
                ui->tab_7->graph(i+2)->setPen(QPen(Qt::black));
                ui->tab_7->replot();
            }
        }
    }
}

void Widget::show_contextmenu_1(const QPoint &pos)
{
    // 模型图右键菜单   
    if (ui->tab_1->m_pressPos == pos) {
        QMenu *cmenu = new QMenu(this);
        QAction *act1;
        if (ui->tab_1->show_axis == true) {
            act1 = cmenu->addAction("不显示坐标轴");
        } else {
            act1 = cmenu->addAction("显示坐标轴");
        }
        connect(act1, SIGNAL(triggered(bool)), this, SLOT(shift_axis()));
        QPoint globalPos = ui->tab_1->mapToGlobal(pos);
        cmenu->exec(globalPos);

        delete cmenu;
    }
}

void Widget::show_contextmenu_2(const QPoint &pos)
{
    // 磁场线分布图右键菜单
    QMenu *cmenu = new QMenu(this);
    QAction *act1 = cmenu->addAction("保存图片");
    QAction *act2 = cmenu->addAction("保存数据");
    connect(act1, SIGNAL(triggered(bool)), this, SLOT(save_pic()));
    connect(act2, SIGNAL(triggered(bool)), this, SLOT(save_data()));
    QPoint globalPos = ui->tab_2->mapToGlobal(pos);
    // cmenu->exec(QCursor::pos());//在当前鼠标位置显示
    cmenu->exec(globalPos);

    delete cmenu;
}

void Widget::show_contextmenu_3(const QPoint &pos)
{
    // 磁场面分布图右键菜单
    QMenu *cmenu = new QMenu(this);
    QAction *act1 = cmenu->addAction("保存图片");
    QAction *act2 = cmenu->addAction("保存数据");
    connect(act1, SIGNAL(triggered(bool)), this, SLOT(save_pic_2()));
    connect(act2, SIGNAL(triggered(bool)), this, SLOT(save_data_2()));
    QPoint globalPos = ui->tab_2->mapToGlobal(pos);
    // cmenu->exec(QCursor::pos());//在当前鼠标位置显示
    cmenu->exec(globalPos);

    delete cmenu;
}

void Widget::show_contextmenu_4(const QPoint &pos)
{
    // 设置磁铁移动右键菜单
    if(ui->listWidget->currentItem()!=Q_NULLPTR)
    {
        QMenu *cmenu = new QMenu(this);
        QAction *act1;
        if (move_list[ui->listWidget->currentRow()] == 0) {
            act1 = cmenu->addAction("标记为可移动");
        } else {
            act1 = cmenu->addAction("取消标记");
        }
        connect(act1, SIGNAL(triggered(bool)), this, SLOT(set_move()));
        QPoint globalPos = ui->listWidget->mapToGlobal(pos);
        cmenu->exec(globalPos);

        delete cmenu;
    }
}

void Widget::show_contextmenu_5(const QPoint &pos)
{
    // 磁铁移动图右键菜单
    QMenu *cmenu = new QMenu(this);
    QAction *act1 = cmenu->addAction("保存图片");
    QAction *act2 = cmenu->addAction("保存数据");
    connect(act1, SIGNAL(triggered(bool)), this, SLOT(save_pic_3()));
    connect(act2, SIGNAL(triggered(bool)), this, SLOT(save_data_3()));
    QPoint globalPos = ui->tab_7->mapToGlobal(pos);
    cmenu->exec(globalPos);

    delete cmenu;
}

void Widget::shift_axis()
{
    // 切换显示坐标轴
    if (ui->tab_1->show_axis == true) {
        ui->tab_1->show_axis = false;
    } else {
        ui->tab_1->show_axis = true;
    }
    on_view_model_clicked();
}

void Widget::save_pic()
{
    // 保存线分布图图片
    QString filename;
    filename=QFileDialog::getSaveFileName(this,"Save To BMP","/","Bit Map File(*.bmp)");
    ui->tab_2->saveBmp(filename,ui->tab_2->width(),ui->tab_2->height());
}

void Widget::save_pic_2()
{
    // 保存面分布图图片
    QString filename;
    filename=QFileDialog::getSaveFileName(this,"Save To BMP","/","Bit Map File(*.bmp)");
    ui->tab_3->saveBmp(filename,ui->tab_3->width(),ui->tab_3->height());
}

void Widget::save_pic_3()
{
    // 保存磁铁移动图图片
    QString filename;
    filename=QFileDialog::getSaveFileName(this,"Save To BMP","/","Bit Map File(*.bmp)");
    ui->tab_7->saveBmp(filename,ui->tab_7->width(),ui->tab_7->height());
}

void Widget::save_data()
{
    // 保存线分布图数据
    QString filename;
    filename=QFileDialog::getSaveFileName(this,"Save To TXT","/","Text File(*.txt)");
    QFile outfile(filename);
    if(outfile.open(QFile::WriteOnly|QFile::Truncate)) {
        QTextStream out(&outfile);
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");

        out << "x(mm)\ty(mm)\tz(mm)";
        if (ui->line_Bx->isChecked()) {
            out << codec->toUnicode("\t磁场Bx(Gs)");
        }
        if (ui->line_By->isChecked()) {
            out << codec->toUnicode("\t磁场By(Gs)");
        }
        if (ui->line_Bz->isChecked()) {
            out << codec->toUnicode("\t磁场Bz(Gs)");
        }
        out << "\r\n";

        int l_num=ui->line_num->text().toInt();
        for (int i = 0; i < l_num; ++i) {
            out << QString::number(line_x[i],'f',2) << "\t" << QString::number(line_y[i],'f',2) << "\t" << QString::number(line_z[i],'f',2);
            if (ui->line_Bx->isChecked()) {
                out << "\t" << QString::number(line_vBx[i],'f',4);
            }
            if (ui->line_By->isChecked()) {
                out << "\t" << QString::number(line_vBy[i],'f',4);
            }
            if (ui->line_Bz->isChecked()) {
                out << "\t" << QString::number(line_vBz[i],'f',4);
            }
            out << "\r\n";
        }
        outfile.close();
    }
}

void Widget::save_data_2()
{
    // 保存面分布图数据
    int px_num = ui->plane_x_num->text().toInt();
    int py_num = ui->plane_y_num->text().toInt();
    QString filename;
    filename=QFileDialog::getSaveFileName(this,"Save To TXT","/","Text File(*.txt)");
    QFile outfile(filename);
    if(outfile.open(QFile::WriteOnly|QFile::Truncate)) {
        QTextStream out(&outfile);
        for (int i = 0; i < px_num; ++i) {
            for (int j = 0; j < py_num; ++j) {
                if (ui->pBx->isChecked()) {
                    out << QString::number(plane_vBx[i][j],'f',4) << "\t" ;
                } else if (ui->pBy->isChecked()) {
                    out << QString::number(plane_vBy[i][j],'f',4) << "\t";
                } else {
                    out << QString::number(plane_vBz[i][j],'f',4) << "\t";
                }
            }
            out << "\r\n";
        }
        outfile.close();
    }
}

void Widget::save_data_3()
{
    // 保存磁铁移动图数据
    QString filename;
    filename=QFileDialog::getSaveFileName(this,"Save To TXT","/","Text File(*.txt)");
    QFile outfile(filename);
    if(outfile.open(QFile::WriteOnly|QFile::Truncate)) {
        QTextStream out(&outfile);
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");

        if (ui->move_direction->currentIndex() == 0) {
            out << "x(mm)";
        } else if (ui->move_direction->currentIndex() == 1) {
            out << "y(mm)";
        } else {
            out << "z(mm)";
        }
        if (ui->p_Bx->isChecked()) {
            out << codec->toUnicode("\t磁场Bx(Gs)");
        }
        if (ui->p_By->isChecked()) {
            out << codec->toUnicode("\t磁场By(Gs)");
        }
        if (ui->p_Bz->isChecked()) {
            out << codec->toUnicode("\t磁场Bz(Gs)");
        }
        out << "\r\n";

        int p_num=ui->point_num->text().toInt();
        for (int i = 0; i < p_num; ++i) {
            out << QString::number(move_path[i],'f',2);
            if (ui->p_Bx->isChecked()) {
                out << "\t" << QString::number(move_vBx[i],'f',4);
            }
            if (ui->p_By->isChecked()) {
                out << "\t" << QString::number(move_vBy[i],'f',4);
            }
            if (ui->p_Bz->isChecked()) {
                out << "\t" << QString::number(move_vBz[i],'f',4);
            }
            out << "\r\n";
        }
        outfile.close();
    }
}

void Widget::set_move()
{
    if(ui->listWidget->currentItem()!=Q_NULLPTR)
    {
        if (move_list[ui->listWidget->currentRow()] == 0) {
            ui->listWidget->currentItem()->setText(ui->listWidget->currentItem()->text() + "[移动]");
            move_list[ui->listWidget->currentRow()]=1;
        } else {
            ui->listWidget->currentItem()->setText(ui->listWidget->currentItem()->text().section('[',0,0).trimmed());
            move_list[ui->listWidget->currentRow()]=0;
        }
    }
}

void Widget::on_line_Bx_clicked()
{
    // 点击修改
    line_checkbox_modified = true;
}

void Widget::on_line_By_clicked()
{
    // 点击修改
    line_checkbox_modified = true;
}

void Widget::on_line_Bz_clicked()
{
    // 点击修改
    line_checkbox_modified = true;
}

void Widget::resizeEvent(QResizeEvent *event)
{
    // 自适应窗口大小
    // 获取当前宽度、高度
    int W = event->size().width();
    int H = event->size().height();
    int Wi=1107;
    int Hi=580;

    ui->tabWidget->setGeometry(420,20,681+(W-Wi),501+(H-Hi));
    ui->tabWidget_2->setGeometry(10,400+(H-Hi),401,171);
    ui->groupBox_2->setGeometry(420,530+(H-Hi),381,41);
    ui->groupBox_4->setGeometry(10,365+(H-Hi),401,31);
    ui->show_cross->setGeometry(820+(W-Wi),554+(H-Hi),95,16);
    ui->view_model->setGeometry(932+(W-Wi),542+(H-Hi),75,23);
    ui->calculate->setGeometry(1013+(W-Wi),542+(H-Hi),75,23);
    ui->label_19->setGeometry(821+(W-Wi),531+(H-Hi),48,16);
    ui->label_20->setGeometry(876+(W-Wi),532+(H-Hi),16,16);
    ui->label_21->setGeometry(888+(W-Wi),532+(H-Hi),16,16);
    ui->label_22->setGeometry(900+(W-Wi),532+(H-Hi),16,16);
}

void Widget::on_choose_plane_currentIndexChanged(int index)
{
    // 计算磁场面分布的平面选择
    switch (index) {
    case 0:
        ui->label_pos->setText("z坐标(mm) :");
        ui->label_x->setText("x坐标起止点(mm) :");
        ui->label_y->setText("y坐标起止点(mm) :");
        break;
    case 1:
        ui->label_pos->setText("y坐标(mm) :");
        ui->label_x->setText("x坐标起止点(mm) :");
        ui->label_y->setText("z坐标起止点(mm) :");
        break;
    case 2:
        ui->label_pos->setText("x坐标(mm) :");
        ui->label_x->setText("y坐标起止点(mm) :");
        ui->label_y->setText("z坐标起止点(mm) :");
        break;
    default:
        ;
    }
}

void Widget::on_tabWidget_2_currentChanged(int index)
{
    if (index == 0) {
        ui->cal_line->setChecked(true);
    } else if (index == 1) {
        ui->cal_plane->setChecked(true);
    } else {
        ui->cal_point->setChecked(true);
    }
}

void Widget::on_show_cross_clicked()
{
    // 更新线绘图
    if (line_caled) {
        print_line_plot();
    }
    if (point_caled) {
        print_point_plot();
    }

    if ( ui->show_cross->isChecked() ) {
        ui->tab_2->setCursor(Qt::ArrowCursor);
        ui->tab_7->setCursor(Qt::ArrowCursor);
    } else {
        ui->tab_2->setCursor(Qt::CrossCursor);
        ui->tab_7->setCursor(Qt::CrossCursor);
    }
}

void Widget::print_line_plot()
{
    // 画磁场线分布图
    int i,j;
    double l_start_x=ui->line_start_x->text().toDouble();
    double l_start_y=ui->line_start_y->text().toDouble();
    double l_start_z=ui->line_start_z->text().toDouble();
    double l_stop_x=ui->line_stop_x->text().toDouble();
    double l_stop_y=ui->line_stop_y->text().toDouble();
    double l_stop_z=ui->line_stop_z->text().toDouble();
    // 画图
    i=-1;
    ui->tab_2->clearGraphs();
    if (ui->line_Bx->isChecked()) {
        i++;
        ui->tab_2->addGraph(); // 添加一条曲线
        ui->tab_2->graph(i)->setName("磁场x分量"); // 曲线名称
        if (l_start_x != l_stop_x && l_start_y == l_stop_y && l_start_z == l_stop_z) {
            ui->tab_2->graph(i)->setData(line_x,line_vBx); // 设置曲线数据
        } else if (l_start_x == l_stop_x && l_start_y != l_stop_y && l_start_z == l_stop_z) {
            ui->tab_2->graph(i)->setData(line_y,line_vBx); // 设置曲线数据
        } else if (l_start_x == l_stop_x && l_start_y == l_stop_y && l_start_z != l_stop_z) {
            ui->tab_2->graph(i)->setData(line_z,line_vBx); // 设置曲线数据
        } else {
            ui->tab_2->graph(i)->setData(line_path,line_vBx); // 设置曲线数据
        }
        QPen pen0; // 画笔
        pen0.setWidth(2); // 线宽
        pen0.setColor(Qt::red); // 颜色
        ui->tab_2->graph(i)->setPen(pen0);
    }
    if (ui->line_By->isChecked()) {
        i++;
        ui->tab_2->addGraph(); // 添加一条曲线
        ui->tab_2->graph(i)->setName("磁场y分量"); // 曲线名称
        if (l_start_x != l_stop_x && l_start_y == l_stop_y && l_start_z == l_stop_z) {
            ui->tab_2->graph(i)->setData(line_x,line_vBy); // 设置曲线数据
        } else if (l_start_x == l_stop_x && l_start_y != l_stop_y && l_start_z == l_stop_z) {
            ui->tab_2->graph(i)->setData(line_y,line_vBy); // 设置曲线数据
        } else if (l_start_x == l_stop_x && l_start_y == l_stop_y && l_start_z != l_stop_z) {
            ui->tab_2->graph(i)->setData(line_z,line_vBy); // 设置曲线数据
        } else {
            ui->tab_2->graph(i)->setData(line_path,line_vBy); // 设置曲线数据
        }
        QPen pen1; // 画笔
        pen1.setWidth(2); // 线宽
        pen1.setColor(Qt::green); // 颜色
        ui->tab_2->graph(i)->setPen(pen1);
    }
    if (ui->line_Bz->isChecked()) {
        i++;
        ui->tab_2->addGraph(); // 添加一条曲线
        ui->tab_2->graph(i)->setName("磁场z分量"); // 曲线名称
        if (l_start_x != l_stop_x && l_start_y == l_stop_y && l_start_z == l_stop_z) {
            ui->tab_2->graph(i)->setData(line_x,line_vBz); // 设置曲线数据
        } else if (l_start_x == l_stop_x && l_start_y != l_stop_y && l_start_z == l_stop_z) {
            ui->tab_2->graph(i)->setData(line_y,line_vBz); // 设置曲线数据
        } else if (l_start_x == l_stop_x && l_start_y == l_stop_y && l_start_z != l_stop_z) {
            ui->tab_2->graph(i)->setData(line_z,line_vBz); // 设置曲线数据
        } else {
            ui->tab_2->graph(i)->setData(line_path,line_vBz); // 设置曲线数据
        }
        QPen pen2; // 画笔
        pen2.setWidth(2); // 线宽
        pen2.setColor(Qt::blue); // 颜色
        ui->tab_2->graph(i)->setPen(pen2);
    }
    if (l_start_x != l_stop_x && l_start_y == l_stop_y && l_start_z == l_stop_z) {
        ui->tab_2->xAxis->setLabel("x (mm)");
    } else if (l_start_x == l_stop_x && l_start_y != l_stop_y && l_start_z == l_stop_z) {
        ui->tab_2->xAxis->setLabel("y (mm)");
    } else if (l_start_x == l_stop_x && l_start_y == l_stop_y && l_start_z != l_stop_z) {
        ui->tab_2->xAxis->setLabel("z (mm)");
    } else {
        ui->tab_2->xAxis->setLabel("作图路径 (mm)");
    }
    ui->tab_2->yAxis->setLabel("磁场 (Gs)");
    ui->tab_2->legend->setVisible(true); // 显示图例
    // 设置坐标轴显示范围
    if (i >= 0) {
        for (j = 0; j <= i; j++) {
            if (j == 0) {
                ui->tab_2->graph(j)->rescaleAxes();
            } else {
                ui->tab_2->graph(j)->rescaleAxes(true);
            }
        }
    }

    // 设置标题
    if (ui->tab_2->plotLayout()->rowCount() < 2) { // 防止重复绘制标题
        ui->tab_2->plotLayout()->insertRow(0);
        ui->tab_2->plotLayout()->addElement(0, 0, new QCPTextElement(ui->tab_2, "磁场分布"));
    }

    // 重新绘图
    ui->tab_2->replot();
    ui->tabWidget->setCurrentIndex(1);

    line_caled=true;
    line_checkbox_modified=false;
}

void Widget::print_plane_plot()
{
    // 画磁场面分布图
    int i,j;
    double px_start = ui->plane_x_start->text().toDouble();
    double px_stop = ui->plane_x_stop->text().toDouble();
    double py_start = ui->plane_y_start->text().toDouble();
    double py_stop = ui->plane_y_stop->text().toDouble();
    int px_num = ui->plane_x_num->text().toInt();
    int py_num = ui->plane_y_num->text().toInt();

    ui->tab_3->clearGraphs();
    //ui->tab_3->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
    ui->tab_3->axisRect()->setupFullAxesBox(true);
    if (ui->choose_plane->currentIndex() == 0) { // xy平面
        ui->tab_3->xAxis->setLabel("x (mm)");
        ui->tab_3->yAxis->setLabel("y (mm)");
    } else if (ui->choose_plane->currentIndex() == 1) { // xz平面
        ui->tab_3->xAxis->setLabel("x (mm)");
        ui->tab_3->yAxis->setLabel("z (mm)");
    } else { // yz平面
        ui->tab_3->xAxis->setLabel("y (mm)");
        ui->tab_3->yAxis->setLabel("z (mm)");
    }
    QCPColorMap *colorMap = new QCPColorMap(ui->tab_3->xAxis,ui->tab_3->yAxis);
    colorMap->data()->setSize(px_num, py_num); // we want the color map to have nx * ny data points
    colorMap->data()->setRange(QCPRange(px_start, px_stop), QCPRange(py_start, py_stop));
    if (ui->pBx->isChecked()) {
        for (i = 0; i < px_num; i++) {
            for (j = 0; j < py_num; j++) {
                colorMap->data()->setCell(i, j, plane_vBx[i][j]);
            }
        }
    } else if (ui->pBy->isChecked()) {
        for (i = 0; i < px_num; i++) {
            for (j = 0; j < py_num; j++) {
                colorMap->data()->setCell(i, j, plane_vBy[i][j]);
            }
        }
    } else {
        for (i = 0; i < px_num; i++) {
            for (j = 0; j < py_num; j++) {
                colorMap->data()->setCell(i, j, plane_vBz[i][j]);
            }
        }
    }

    // 颜色图例
    if (!plane_caled) {
        ui->tab_3->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect
    }
    colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
    colorMap->setColorScale(colorScale); // associate the color map with the color scale
    colorScale->axis()->setLabel("磁场 (Gs)");
    // make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->tab_3);
    ui->tab_3->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);


    // 设置color map
    colorMap->setGradient(QCPColorGradient::gpJet);

    // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:
    colorMap->rescaleDataRange();

    // rescale the key (x) and value (y) axes so the whole color map is visible:
    ui->tab_3->rescaleAxes();


    // 重新绘图
    ui->tab_3->replot();

    // 完成
    ui->tabWidget->setCurrentIndex(2);
    plane_caled=true;
}

void Widget::print_point_plot()
{
    // 画磁铁移动图
    int i,j;
    // 画图
    i=-1;
    ui->tab_7->clearGraphs();
    if (ui->p_Bx->isChecked()) { // x方向移动
        i++;
        ui->tab_7->addGraph(); // 添加一条曲线
        ui->tab_7->graph(i)->setName("磁场x分量"); // 曲线名称
        ui->tab_7->graph(i)->setData(move_path,move_vBx); // 设置曲线数据

        QPen pen0; // 画笔
        pen0.setWidth(2); // 线宽
        pen0.setColor(Qt::red); // 颜色
        ui->tab_7->graph(i)->setPen(pen0);
    }
    if (ui->p_By->isChecked()) { // y方向移动
        i++;
        ui->tab_7->addGraph(); // 添加一条曲线
        ui->tab_7->graph(i)->setName("磁场y分量"); // 曲线名称
        ui->tab_7->graph(i)->setData(move_path,move_vBy); // 设置曲线数据

        QPen pen1; // 画笔
        pen1.setWidth(2); // 线宽
        pen1.setColor(Qt::green); // 颜色
        ui->tab_7->graph(i)->setPen(pen1);
    }
    if (ui->p_Bz->isChecked()) { // z方向移动
        i++;
        ui->tab_7->addGraph(); // 添加一条曲线
        ui->tab_7->graph(i)->setName("磁场z分量"); // 曲线名称
        ui->tab_7->graph(i)->setData(move_path,move_vBz); // 设置曲线数据

        QPen pen2; // 画笔
        pen2.setWidth(2); // 线宽
        pen2.setColor(Qt::blue); // 颜色
        ui->tab_7->graph(i)->setPen(pen2);
    }
    if (ui->move_direction->currentIndex() == 0) {
        ui->tab_7->xAxis->setLabel("x (mm)");
    } else if (ui->move_direction->currentIndex() == 1) {
        ui->tab_7->xAxis->setLabel("y (mm)");
    } else {
        ui->tab_7->xAxis->setLabel("z (mm)");
    }
    ui->tab_7->yAxis->setLabel("磁场 (Gs)");
    ui->tab_7->legend->setVisible(true); // 显示图例
    // 设置坐标轴显示范围
    if (i >= 0) {
        for (j = 0; j <= i; j++) {
            if (j == 0) {
                ui->tab_7->graph(j)->rescaleAxes();
            } else {
                ui->tab_7->graph(j)->rescaleAxes(true);
            }
        }
    }

    // 设置标题
    if (ui->tab_7->plotLayout()->rowCount() < 2) { // 防止重复绘制标题
        ui->tab_7->plotLayout()->insertRow(0);
        ui->tab_7->plotLayout()->addElement(0, 0, new QCPTextElement(ui->tab_7, "磁铁移动-磁场"));
    }

    // 重新绘图
    ui->tab_7->replot();
    ui->tabWidget->setCurrentIndex(3);

    point_checkbox_modified=false;
    point_caled=true;
}

void Widget::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasFormat("text/uri-list")) //只能打开文本文件
        event->acceptProposedAction(); //可以在这个窗口部件上拖放对象
}

void Widget::dropEvent(QDropEvent *event)
{
    //释放配置文件时，导入配置
    QList<QUrl> urls = event->mimeData()->urls();
    if(urls.isEmpty())
        return ;

    QString filename = urls.first().toLocalFile();
    QFile data(filename);
    if(data.open(QIODevice::ReadOnly)) {
        para_x.clear();
        para_y.clear();
        para_z.clear();
        para_a.clear();
        para_b.clear();
        para_c.clear();
        para_direction.clear();
        para_m.clear();
        para_position.clear();
        para_cao_h.clear();
        para_cao_n.clear();
        para_cao_p.clear();
        para_axis.clear();
        para_deg.clear();
        move_list.clear();

        ui->listWidget->clear();

        QTextStream txtInput(&data);
        QString lineStr;
        QStringList myList;
        lineStr = txtInput.readLine();
        int i=0;
        while(!txtInput.atEnd())
        {
            lineStr = txtInput.readLine();
            myList = lineStr.split("\t");
            para_x << myList[1].toDouble();
            para_y << myList[2].toDouble();
            para_z << myList[3].toDouble();
            para_a << myList[4].toDouble();
            para_b << myList[5].toDouble();
            para_c << myList[6].toDouble();
            para_direction << myList[7].toInt();
            para_m << myList[8].toDouble();
            para_position << myList[9].toInt();
            para_cao_h << myList[10].toDouble();
            para_cao_n << myList[11].toDouble();
            para_cao_p << myList[12].toDouble();
            para_axis << myList[13].toInt();
            para_deg << myList[14].toDouble();
            move_list << 0;

            magnet_num=myList[0].toInt();
            xlh=i+1;
            QString item_name="第 "+QString::number(xlh, 10)+" 号磁块";
            ui->listWidget->insertItem(magnet_num-1,item_name);

            i++;
        }
        data.close();
    }
}


void Widget::on_p_Bx_clicked()
{
    // 点击修改
    point_checkbox_modified = true;
}

void Widget::on_p_By_clicked()
{
    // 点击修改
    point_checkbox_modified = true;
}

void Widget::on_p_Bz_clicked()
{
    // 点击修改
    point_checkbox_modified = true;
}

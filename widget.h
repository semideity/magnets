#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QResizeEvent>
#include "qcustomplot.h"

#define N_MAX_POINTS 501

using namespace std;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_add_magnet_clicked();
    void on_cut_magnet_clicked();
    void on_view_model_clicked();
    void on_listWidget_clicked(const QModelIndex &index);
    void on_kaicao_clicked(bool checked);
    void on_xz_clicked(bool checked);
    void on_cx_editingFinished();
    void on_cy_editingFinished();
    void on_cz_editingFinished();
    void on_a_editingFinished();
    void on_b_editingFinished();
    void on_c_editingFinished();
    void on_ccfx_currentIndexChanged(int index);
    void on_chqd_editingFinished();
    void on_kaicaoweizhi_currentIndexChanged(int index);
    void on_cao_sd_editingFinished();
    void on_cao_fxbj_editingFinished();
    void on_cao_zxbj_editingFinished();
    void on_xzz_currentIndexChanged(int index);
    void on_xzjd_editingFinished();
    void on_save_setting_clicked();
    void on_import_setting_clicked();
    void on_cal_line_clicked();
    void on_cal_plane_clicked();
    void on_cal_point_clicked();
    void on_calculate_clicked();
    void my_mouseMove(QMouseEvent* event);
    void my_mouseMove_2(QMouseEvent* event);
    void my_mouseMove_3(QMouseEvent* event);
    void show_contextmenu_1(const QPoint& pos);
    void show_contextmenu_2(const QPoint& pos);
    void show_contextmenu_3(const QPoint& pos);
    void show_contextmenu_4(const QPoint& pos);
    void show_contextmenu_5(const QPoint& pos);
    void shift_axis();
    void save_pic();
    void save_data();
    void save_pic_2();
    void save_data_2();
    void save_pic_3();
    void save_data_3();
    void set_move();
    void on_line_Bx_clicked();
    void on_line_By_clicked();
    void on_line_Bz_clicked();
    void on_choose_plane_currentIndexChanged(int index);
    void on_tabWidget_2_currentChanged(int index);
    void on_show_cross_clicked();
    void on_p_Bx_clicked();
    void on_p_By_clicked();
    void on_p_Bz_clicked();

private:
    Ui::Widget *ui;

    bool isNum(QString str);
    int xlh; // 磁铁序号
    int magnet_num; // 磁块数量
    QCPColorScale *colorScale;

    // 磁铁参数
    QVector<double> para_x; // x坐标
    QVector<double> para_y; // y坐标
    QVector<double> para_z; // z坐标
    QVector<double> para_a; // x尺寸
    QVector<double> para_b; // y尺寸
    QVector<double> para_c; // z尺寸
    QVector<int> para_direction; // 磁化方向
    QVector<double> para_m; // 磁化强度
    QVector<int> para_position; // 开槽位置
    QVector<double> para_cao_h; // 开槽深度
    QVector<double> para_cao_n; // 负向边距
    QVector<double> para_cao_p; // 正向边距
    QVector<int> para_axis; // 旋转轴
    QVector<double> para_deg; // 旋转角度
    QVector<double> line_vBx; // 磁场值
    QVector<double> line_vBy; // 磁场值
    QVector<double> line_vBz; // 磁场值
    QVector<double> line_x; // 线计算路径
    QVector<double> line_y; // 线计算路径
    QVector<double> line_z; // 线计算路径
    QVector<double> line_rx; // 线计算路径旋转变换后
    QVector<double> line_ry; // 线计算路径旋转变换后
    QVector<double> line_rz; // 线计算路径旋转变换后
    QVector<double> line_path; // 线计算arc line
    QVector<double> move_vBx; // 磁铁移动磁场值
    QVector<double> move_vBy; // 磁铁移动磁场值
    QVector<double> move_vBz; // 磁铁移动磁场值
    QVector<double> move_path; // 磁铁移动位移
    QVector<double> plane_x; // 面计算坐标1
    QVector<double> plane_y; // 面计算坐标2
    QVector<QVector<double>> plane_vBx; // 磁场面分布计算值
    QVector<QVector<double>> plane_vBy; // 磁场面分布计算值
    QVector<QVector<double>> plane_vBz; // 磁场面分布计算值
    QVector<int> move_list; // 磁铁移动列表
    bool line_caled; // 线分布计算状态
    bool plane_caled; // 面分布计算状态
    bool point_caled; // 磁铁移动计算状态
    bool model_plot;
    bool line_checkbox_modified; // 是否修改了画线分布图选项
    bool point_checkbox_modified; // 是否修改了磁铁移动图选项
    void print_line_plot();
    void print_plane_plot();
    void print_point_plot();

protected:
    virtual void resizeEvent(QResizeEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
};

#endif // WIDGET_H

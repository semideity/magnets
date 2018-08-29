#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QMatrix4x4>
#include "draw.h"
#include "ArcBall.h"
#include "widget.h"

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = nullptr);

    // 绘图开关
    bool plot;
    int cal_mode;
    bool show_axis;
    double l_start_x;
    double l_stop_x;
    double l_start_y;
    double l_stop_y;
    double l_start_z;
    double l_stop_z;
    double z_pos;
    double px_start;
    double px_stop;
    double py_start;
    double py_stop;
    int cplane;
    double p_x,p_y,p_z;
    void setMagnetNum(int n);
    void setPara_x(QVector<double> vect);
    void setPara_y(QVector<double> vect);
    void setPara_z(QVector<double> vect);
    void setPara_a(QVector<double> vect);
    void setPara_b(QVector<double> vect);
    void setPara_c(QVector<double> vect);
    void setPara_direction(QVector<int> vect);
    void setPara_m(QVector<double> vect);
    void setPara_position(QVector<int> vect);
    void setPara_cao_h(QVector<double> vect);
    void setPara_cao_n(QVector<double> vect);
    void setPara_cao_p(QVector<double> vect);
    void setPara_axis(QVector<int> vect);
    void setPara_deg(QVector<double> vect);
    QPoint m_lastPos;
    QPoint m_pressPos;

private:
    int magnet_num;

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

    // 平移量
    float m_xMov;
    float m_yMov;
    float m_zMov;
    // 缩放比例
    float m_scale;

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event);

signals:

public slots:
};

#endif // GLWIDGET_H

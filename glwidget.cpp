#include "glwidget.h"

// ========== 初始化轨迹球操作矩阵 ==========
Matrix4fT   Transform   = {  1.0f,  0.0f,  0.0f,  0.0f,
0.0f,  1.0f,  0.0f,  0.0f,
0.0f,  0.0f,  1.0f,  0.0f,
0.0f,  0.0f,  0.0f,  1.0f };

Matrix3fT   LastRot     = {  1.0f,  0.0f,  0.0f,
0.0f,  1.0f,  0.0f,
0.0f,  0.0f,  1.0f };

Matrix3fT   ThisRot     = {  1.0f,  0.0f,  0.0f,
0.0f,  1.0f,  0.0f,
0.0f,  0.0f,  1.0f };

ArcBallT    ArcBall(2.0f, 2.0f);
ArcBallT*    arcBall =&ArcBall;
Point2fT    MousePt;
// ==========================================

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
    plot(false),
    cal_mode(1),
    show_axis(true),
    m_xMov(0),
    m_yMov(0),
    m_zMov(0),
    m_scale(1)
{

}

void GLWidget::initializeGL()
{
    SetupRC();
}

void GLWidget::paintGL()
{
    if (plot) {
        int width=this->width();
        int height=this->height();
        glViewport(0,0,width,height);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity(); // 重置为单位矩阵

        // 平移
        glTranslatef(m_xMov, m_yMov, m_zMov);
        // 旋转
        glMultMatrixf(Transform.M);
        // 缩放
        glScalef(m_scale, m_scale, m_scale);

        // 计算缩放
        double xn,xp,yn,yp,zn,zp;
        double smax=0;
        int i;
        for (i = 0; i < magnet_num; i++) {
            xn = para_x[i] - para_a[i] / 2;
            xp = para_x[i] + para_a[i] / 2;
            yn = para_y[i] - para_b[i] / 2;
            yp = para_y[i] + para_b[i] / 2;
            zn = para_z[i] - para_c[i] / 2;
            zp = para_z[i] + para_c[i] / 2;
            smax = (smax>fabs(xn)) ? smax : fabs(xn);
            smax = (smax>fabs(xp)) ? smax : fabs(xp);
            smax = (smax>fabs(yn)) ? smax : fabs(yn);
            smax = (smax>fabs(yp)) ? smax : fabs(yp);
            smax = (smax>fabs(zn)) ? smax : fabs(zn);
            smax = (smax>fabs(zp)) ? smax : fabs(zp);
        }
        if (cal_mode == 1) {
            smax = (smax>fabs(l_start_x)) ? smax : fabs(l_start_x);
            smax = (smax>fabs(l_start_y)) ? smax : fabs(l_start_y);
            smax = (smax>fabs(l_start_z)) ? smax : fabs(l_start_z);
            smax = (smax>fabs(l_stop_x)) ? smax : fabs(l_stop_x);
            smax = (smax>fabs(l_stop_y)) ? smax : fabs(l_stop_y);
            smax = (smax>fabs(l_stop_z)) ? smax : fabs(l_stop_z);
        } else if (cal_mode == 2) {
            smax = (smax>fabs(z_pos)) ? smax : fabs(z_pos);
            smax = (smax>fabs(px_start)) ? smax : fabs(px_start);
            smax = (smax>fabs(px_stop)) ? smax : fabs(px_stop);
            smax = (smax>fabs(py_start)) ? smax : fabs(py_start);
            smax = (smax>fabs(py_stop)) ? smax : fabs(py_stop);
        } else {
            smax = (smax>fabs(p_x)) ? smax : fabs(p_x);
            smax = (smax>fabs(p_y)) ? smax : fabs(p_y);
            smax = (smax>fabs(p_z)) ? smax : fabs(p_z);
        }
        if (smax == 0) {
            smax=1;
        } else {
            smax=1.4*smax;
        }

        // 画作图线 或 作图平面
        if (cal_mode == 1) {
            DrawLine(l_start_x/smax, l_start_y/smax, l_start_z/smax, l_stop_x/smax, l_stop_y/smax, l_stop_z/smax);
        } else if (cal_mode == 2) {
            DrawPlane(cplane, z_pos/smax, px_start/smax, px_stop/smax, py_start/smax, py_stop/smax);
        } else {
            DrawPoint(p_x/smax, p_y/smax, p_z/smax);
        }

        // 画坐标轴
        if (show_axis) {
            DrawAxis(0.5f);
        }

        // 画磁铁
        DrawBox(smax, para_x, para_y, para_z, para_a, para_b, para_c, para_direction, para_position, para_cao_h, para_cao_n, para_cao_p, para_axis, para_deg, magnet_num);
    }
}

void GLWidget::resizeGL(int w, int h)
{
    arcBall->setBounds((GLfloat)w, (GLfloat)h);//设置窗口边界，解决缩放后旋转问题
    glViewport(0,0,(GLsizei) w, (GLsizei) h);
    float nscale=1;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w<h) {
        glOrtho(-nscale,nscale,-nscale*h/w,nscale*h/w,-4*nscale,4*nscale);
    } else {
        glOrtho(-nscale*w/h,nscale*w/h,-nscale,nscale,-4*nscale,4*nscale);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    if (plot) {
        m_lastPos = event->pos();
        m_pressPos = event->pos();

        MousePt.s.X = m_lastPos.x();
        MousePt.s.Y = m_lastPos.y();
        LastRot = ThisRot;
        ArcBall.click(&MousePt);
    }
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (plot) {
        int dx = event->x() - m_lastPos.x();
        int dy = event->y() - m_lastPos.y();

        // 鼠标左键拖曳旋转
        if (event->buttons() & Qt::LeftButton) {
            MousePt.s.X = event->pos().x();
            MousePt.s.Y = event->pos().y();
            Quat4fT ThisQuat;

            ArcBall.drag(&MousePt, &ThisQuat);                        // Update End Vector And Get Rotation As Quaternion
            Matrix3fSetRotationFromQuat4f(&ThisRot, &ThisQuat);        // Convert Quaternion Into Matrix3fT
            Matrix3fMulMatrix3f(&ThisRot, &LastRot);                // Accumulate Last Rotation Into This One
            Matrix4fSetRotationFromMatrix3f(&Transform, &ThisRot);    // Set Our Final Transform's Rotation From This One
        }

        // 鼠标右键拖曳移动
        if (event->buttons() & Qt::RightButton) {
            m_xMov=m_xMov + (float)dx/qMin(width(),height())*2;
            m_yMov=m_yMov - (float)dy/qMin(width(),height())*2;
        }

        update();
        m_lastPos = event->pos();

        // 当前的模型矩阵
        GLdouble modelMatrix[16];
        glGetDoublev( GL_MODELVIEW_MATRIX , modelMatrix );
        // 当前的投影矩阵
        GLdouble projMatrix[16];
        glGetDoublev( GL_PROJECTION_MATRIX , projMatrix );
        // 当前的视口信息
        GLint viewport[4];
        glGetIntegerv( GL_VIEWPORT , viewport );
    }
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
    if (plot) {
        // 鼠标滚轮缩放大小
        if (event->delta() > 0)
        {
            m_scale+=0.1;
        } else {
            m_scale-=0.1;
        }
        if (m_scale < 0.1) {
            m_scale=0.1;
        }

        update();
    }
}

void GLWidget::setMagnetNum(int n)
{
    // 设置磁铁数量
    magnet_num=n;
}

void GLWidget::setPara_x(QVector<double> vect)
{
    // 设置磁铁参数
    para_x=vect;
}

void GLWidget::setPara_y(QVector<double> vect)
{
    // 设置磁铁参数
    para_y=vect;
}

void GLWidget::setPara_z(QVector<double> vect)
{
    // 设置磁铁参数
    para_z=vect;
}

void GLWidget::setPara_a(QVector<double> vect)
{
    // 设置磁铁参数
    para_a=vect;
}

void GLWidget::setPara_b(QVector<double> vect)
{
    // 设置磁铁参数
    para_b=vect;
}

void GLWidget::setPara_c(QVector<double> vect)
{
    // 设置磁铁参数
    para_c=vect;
}

void GLWidget::setPara_direction(QVector<int> vect)
{
    // 设置磁铁参数
    para_direction=vect;
}

void GLWidget::setPara_m(QVector<double> vect)
{
    // 设置磁铁参数
    para_m=vect;
}

void GLWidget::setPara_position(QVector<int> vect)
{
    // 设置磁铁参数
    para_position=vect;
}

void GLWidget::setPara_cao_h(QVector<double> vect)
{
    // 设置磁铁参数
    para_cao_h=vect;
}

void GLWidget::setPara_cao_n(QVector<double> vect)
{
    // 设置磁铁参数
    para_cao_n=vect;
}

void GLWidget::setPara_cao_p(QVector<double> vect)
{
    // 设置磁铁参数
    para_cao_p=vect;
}

void GLWidget::setPara_axis(QVector<int> vect)
{
    // 设置磁铁参数
    para_axis=vect;
}

void GLWidget::setPara_deg(QVector<double> vect)
{
    // 设置磁铁参数
    para_deg=vect;
}

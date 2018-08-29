#include <QOpenGLWidget>
#include <QVector>

void DrawAxis(GLfloat axis_length);
void DrawLine(GLfloat start_x, GLfloat start_y, GLfloat start_z, GLfloat stop_x, GLfloat stop_y, GLfloat stop_z);
void DrawPlane(GLint cplane, GLfloat zb, GLfloat start_1, GLfloat stop_1, GLfloat start_2, GLfloat stop_2);
void DrawPoint(GLfloat x, GLfloat y, GLfloat z);
void DrawBox(double index, QVector<double> cx, QVector<double> cy, QVector<double> cz, QVector<double> a, QVector<double> b, QVector<double> c, QVector<int> mag, QVector<int> cao_d, QVector<double> cao_h, QVector<double> cao_n, QVector<double> cao_p, QVector<int> xz_xzz, QVector<double> xz_xzjd, int total);
void SetupRC();

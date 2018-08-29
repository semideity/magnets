#include "draw.h"

// 绘制坐标系
void DrawAxis(GLfloat axis_length)
{
	//绘制x、y、z坐标轴

    glColor3f(1.0f, 0.0f, 0.0f);//指定线的颜色,红色
	glBegin(GL_LINES);
	{
        //axis_length=-axis_length;// 解决x坐标反向问题
		// x-axis
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(axis_length, 0.0f, 0.0f);

		// x-axis arrow
		glVertex3f(axis_length, 0.0f, 0.0f);
		glVertex3f(0.95*axis_length, 0.03*axis_length, 0.0f);
		glVertex3f(axis_length, 0.0f, 0.0f);
		glVertex3f(0.95*axis_length, -0.03*axis_length, 0.0f);
		glVertex3f(axis_length, 0.0f, 0.0f);
		glVertex3f(0.95*axis_length, 0.0f, 0.03*axis_length);
		glVertex3f(axis_length, 0.0f, 0.0f);
		glVertex3f(0.95*axis_length, 0.0f, -0.03*axis_length);
	}
	glEnd();

    glColor3f(0.0f, 1.0f, 0.0f);//指定线的颜色,绿色
	glBegin(GL_LINES);
	{
		//axis_length=-axis_length;// 解决y坐标反向问题
		// y-axis
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, axis_length, 0.0f);

		// y-axis arrow
		glVertex3f(0.0f, axis_length, 0.0f);
		glVertex3f(0.03*axis_length, 0.95*axis_length, 0.0f);
		glVertex3f(0.0f, axis_length, 0.0f);
		glVertex3f(-0.03*axis_length, 0.95*axis_length, 0.0f);
		glVertex3f(0.0f, axis_length, 0.0f);
		glVertex3f(0.0f, 0.95*axis_length, 0.03*axis_length);
		glVertex3f(0.0f, axis_length, 0.0f);
		glVertex3f(0.0f, 0.95*axis_length, -0.03*axis_length);
	}
	glEnd();

    glColor3f(0.0f, 0.0f, 1.0f);//指定线的颜色,蓝色
	glBegin(GL_LINES);
	{
		//axis_length=-axis_length;// 解决z坐标反向问题
		// z-axis
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, axis_length);

		// z-axis arrow
		glVertex3f(0.0f, 0.0f, axis_length);
		glVertex3f(0.0f, 0.03*axis_length, 0.95*axis_length);
		glVertex3f(0.0f, 0.0f, axis_length);
		glVertex3f(0.0f, -0.03*axis_length, 0.95*axis_length);
		glVertex3f(0.0f, 0.0f, axis_length);
		glVertex3f(0.03*axis_length, 0.0f, 0.95*axis_length);
		glVertex3f(0.0f, 0.0f, axis_length);
		glVertex3f(-0.03*axis_length, 0.0f, 0.95*axis_length);
	}
	glEnd();
}

// 绘制直线
void DrawLine(GLfloat start_x, GLfloat start_y, GLfloat start_z, GLfloat stop_x, GLfloat stop_y, GLfloat stop_z) {
	//绘制x、y、z坐标轴
    glColor3f(0.0f, 0.0f, 0.0f);//指定线的颜色
	glBegin(GL_LINES);
	{
		glVertex3f(start_x, start_y, start_z);
		glVertex3f(stop_x, stop_y, stop_z);
	}
	glEnd();
}

// 绘制平面
void DrawPlane(GLint cplane, GLfloat zb, GLfloat start_1, GLfloat stop_1, GLfloat start_2, GLfloat stop_2) {
    glColor3f(0.3f, 0.3f, 0.3f);
	if (cplane == 0) { // xy plane
		glBegin(GL_QUADS);
		{
			glVertex3f(start_1, start_2, zb);
			glVertex3f(stop_1, start_2, zb);
			glVertex3f(stop_1, stop_2, zb);
			glVertex3f(start_1, stop_2, zb);
		}
		glEnd();
	}
	else if (cplane == 1) { // xz plane
		glBegin(GL_QUADS);
		{
			glVertex3f(start_1, zb, start_2);
			glVertex3f(stop_1, zb, start_2);
			glVertex3f(stop_1, zb, stop_2);
			glVertex3f(start_1, zb, stop_2);
		}
		glEnd();
	}
	else { // yz plane
		glBegin(GL_QUADS);
		{
			glVertex3f(zb, start_1, start_2);
			glVertex3f(zb, stop_1, start_2);
			glVertex3f(zb, stop_1, stop_2);
			glVertex3f(zb, start_1, stop_2);
		}
		glEnd();
	}
}

// 绘制场点
void DrawPoint(GLfloat x, GLfloat y, GLfloat z)
{
    glPointSize(4);
    glColor3f(0.0f, 0.5f, 0.0f);
    glBegin(GL_POINTS);
    {
        glVertex3f(x, y, z);
    }
    glEnd();
}

// 绘制磁铁
void DrawBox(double index, QVector<double> cx, QVector<double> cy, QVector<double> cz, QVector<double> a, QVector<double> b, QVector<double> c, QVector<int> mag, QVector<int> cao_d, QVector<double> cao_h, QVector<double> cao_n, QVector<double> cao_p, QVector<int> xz_xzz, QVector<double> xz_xzjd, int total)
{
	//画长方体
    glScalef(1/index, 1/index, 1/index);
    for (int i = 0; i < total; i++) {
        glTranslatef(cx[i], cy[i], cz[i]);
        if (xz_xzz[i] == 0) {
            glRotatef(xz_xzjd[i],1.0f,0.0f,0.0f);
        } else if (xz_xzz[i] == 1) {
            glRotatef(xz_xzjd[i],0.0f,1.0f,0.0f);
        } else if (xz_xzz[i] == 2) {
            glRotatef(xz_xzjd[i],0.0f,0.0f,1.0f);
        } else {
            //
        }

        // 画面
        glEnable(GL_POLYGON_OFFSET_FILL);// 解决线框遮挡
        glPolygonOffset(1.0f, 1.0f);// 解决线框遮挡
        if (cao_h[i] == 0) {
            glBegin(GL_QUADS);
            {
                // 上面
                if (mag[i] == 31) { // z正向充磁
                    glColor3f(1.0f, 0.0f, 0.0f);
                }
                else if (mag[i] == 32) { // z反向充磁
                    glColor3f(0.0f, 0.0f, 1.0f);
                }
                else {
                    glColor3f(0.5f, 0.5f, 0.5f);
                }
                glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);
                glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);

                // 下面
                if (mag[i] == 32) { // z反向充磁
                    glColor3f(1.0f, 0.0f, 0.0f);
                }
                else if (mag[i] == 31) { // z正向充磁
                    glColor3f(0.0f, 0.0f, 1.0f);
                }
                else {
                    glColor3f(0.5f, 0.5f, 0.5f);
                }
                glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);
                glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);

                // 前面
                if (mag[i] == 21) { // y正向充磁
                    glColor3f(1.0f, 0.0f, 0.0f);
                }
                else if (mag[i] == 22) { // y反向充磁
                    glColor3f(0.0f, 0.0f, 1.0f);
                }
                else {
                    glColor3f(0.5f, 0.5f, 0.5f);
                }
                glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);
                glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);

                // 后面
                if (mag[i] == 22) { // y反向充磁
                    glColor3f(1.0f, 0.0f, 0.0f);
                }
                else if (mag[i] == 21) { // y正向充磁
                    glColor3f(0.0f, 0.0f, 1.0f);
                }
                else {
                    glColor3f(0.5f, 0.5f, 0.5f);
                }
                glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);

                // 右面
                if (mag[i] == 11) { // x正向充磁
                    glColor3f(1.0f, 0.0f, 0.0f);
                }
                else if (mag[i] == 12) { // x反向充磁
                    glColor3f(0.0f, 0.0f, 1.0f);
                }
                else {
                    glColor3f(0.5f, 0.5f, 0.5f);
                }
                glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);

                // 左面
                if (mag[i] == 12) { // x反向充磁
                    glColor3f(1.0f, 0.0f, 0.0f);
                }
                else if (mag[i] == 11) { // x正向充磁
                    glColor3f(0.0f, 0.0f, 1.0f);
                }
                else {
                    glColor3f(0.5f, 0.5f, 0.5f);
                }
                glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);
                glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
            }
            glEnd();
        }
        else {
            // 上面
            if (mag[i] == 31) { // z正向充磁
                glColor3f(1.0f, 0.0f, 0.0f);
            }
            else if (mag[i] == 32) { // z反向充磁
                glColor3f(0.0f, 0.0f, 1.0f);
            }
            else {
                glColor3f(0.5f, 0.5f, 0.5f);
            }

            if (cao_d[i] == 0) {// 后面上下
                glBegin(GL_QUADS);
                {
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i] + cao_h[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i] + cao_h[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i] + cao_h[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i] + cao_h[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i] + cao_h[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i] + cao_h[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                }
                glEnd();
            }
            else if (cao_d[i] == 2) {// 前面上下
                glBegin(GL_QUADS);
                {
                    glVertex3f(0.5*a[i], 0.5*b[i] - cao_h[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i] - cao_h[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i] - cao_h[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i] - cao_h[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i] - cao_h[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i] - cao_h[i], 0.5*c[i]);
                }
                glEnd();
            }
            else if (cao_d[i] == 4) {// 上面前后
                glBegin(GL_QUADS);
                {
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i], 0.5*c[i] - cao_h[i]);
                    glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i], 0.5*c[i] - cao_h[i]);
                    glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i], 0.5*c[i] - cao_h[i]);
                    glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i], 0.5*c[i] - cao_h[i]);

                    glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i], 0.5*c[i]);
                }
                glEnd();
            }
            else if (cao_d[i] == 5) {// 上面左右
                glBegin(GL_QUADS);
                {
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i] - cao_p[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i] - cao_p[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], 0.5*b[i] - cao_p[i], 0.5*c[i] - cao_h[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i] - cao_p[i], 0.5*c[i] - cao_h[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i] + cao_n[i], 0.5*c[i] - cao_h[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i] + cao_n[i], 0.5*c[i] - cao_h[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i] + cao_n[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i] + cao_n[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                }
                glEnd();
            }
            else if (cao_d[i] == 9) {// 右面上下
                glBegin(GL_QUADS);
                {
                    glVertex3f(0.5*a[i] - cao_h[i], 0.5*b[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i] - cao_h[i], -0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i] - cao_h[i], 0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i] - cao_h[i], 0.5*b[i] - cao_p[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i] - cao_p[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i] + cao_n[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i] - cao_h[i], -0.5*b[i] + cao_n[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i] - cao_h[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                }
                glEnd();
            }
            else if (cao_d[i] == 11) {// 左面上下
                glBegin(GL_QUADS);
                {
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i] + cao_h[i], 0.5*b[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i] + cao_h[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i] + cao_h[i], 0.5*b[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i] - cao_p[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i] + cao_h[i], 0.5*b[i] - cao_p[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i] + cao_h[i], -0.5*b[i] + cao_n[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i] + cao_n[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i] + cao_h[i], -0.5*b[i], 0.5*c[i]);
                }
                glEnd();
            }
            else {
                glBegin(GL_QUADS);
                {
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                }
                glEnd();
            }


            // 下面
            if (mag[i] == 32) { // z反向充磁
                glColor3f(1.0f, 0.0f, 0.0f);
            }
            else if (mag[i] == 31) { // z正向充磁
                glColor3f(0.0f, 0.0f, 1.0f);
            }
            else {
                glColor3f(0.5f, 0.5f, 0.5f);
            }

            if (cao_h[i] == 0) {
                glBegin(GL_QUADS);
                {
                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                }
                glEnd();
            }
            else {
                if (cao_d[i] == 0) {// 后面上下
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i] + cao_h[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i] + cao_h[i], -0.5*c[i]);

                        glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i] + cao_h[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i] + cao_h[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i], -0.5*c[i]);

                        glVertex3f(0.5*a[i], -0.5*b[i] + cao_h[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i] + cao_h[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    }
                    glEnd();
                }
                else if (cao_d[i] == 2) {// 前面上下
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(0.5*a[i], 0.5*b[i] - cao_h[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i] - cao_h[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);

                        glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i] - cao_h[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i] - cao_h[i], -0.5*c[i]);

                        glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i] - cao_h[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i] - cao_h[i], -0.5*c[i]);
                    }
                    glEnd();
                }
                else if (cao_d[i] == 6) {// 下面前后
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);

                        glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i], -0.5*c[i] + cao_h[i]);
                        glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i], -0.5*c[i] + cao_h[i]);
                        glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i], -0.5*c[i] + cao_h[i]);
                        glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i], -0.5*c[i] + cao_h[i]);

                        glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i], -0.5*c[i]);
                    }
                    glEnd();
                }
                else if (cao_d[i] == 7) {// 下面左右
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i] - cao_p[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i] - cao_p[i], -0.5*c[i]);

                        glVertex3f(0.5*a[i], 0.5*b[i] - cao_p[i], -0.5*c[i] + cao_h[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i] - cao_p[i], -0.5*c[i] + cao_h[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i] + cao_n[i], -0.5*c[i] + cao_h[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i] + cao_n[i], -0.5*c[i] + cao_h[i]);

                        glVertex3f(0.5*a[i], -0.5*b[i] + cao_n[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i] + cao_n[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    }
                    glEnd();
                }
                else if (cao_d[i] == 9) {// 右面上下
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(0.5*a[i] - cao_h[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_h[i], -0.5*b[i], -0.5*c[i]);

                        glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_h[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_h[i], 0.5*b[i] - cao_p[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i] - cao_p[i], -0.5*c[i]);

                        glVertex3f(0.5*a[i], -0.5*b[i] + cao_n[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_h[i], -0.5*b[i] + cao_n[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_h[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    }
                    glEnd();
                }
                else if (cao_d[i] == 11) {// 左面上下
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i] + cao_h[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i] + cao_h[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);

                        glVertex3f(-0.5*a[i] + cao_h[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i] - cao_p[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i] + cao_h[i], 0.5*b[i] - cao_p[i], -0.5*c[i]);

                        glVertex3f(-0.5*a[i] + cao_h[i], -0.5*b[i] + cao_n[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i] + cao_n[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i] + cao_h[i], -0.5*b[i], -0.5*c[i]);
                    }
                    glEnd();
                }
                else {
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    }
                    glEnd();
                }
            }

            // 前面
            if (mag[i] == 21) { // y正向充磁
                glColor3f(1.0f, 0.0f, 0.0f);
            }
            else if (mag[i] == 22) { // y反向充磁
                glColor3f(0.0f, 0.0f, 1.0f);
            }
            else {
                glColor3f(0.5f, 0.5f, 0.5f);
            }

            if (cao_h[i] == 0) {
                glBegin(GL_QUADS);
                {
                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                }
                glEnd();
            }
            else {
                if (cao_d[i] == 2) {// 前面上下
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i], -0.5*c[i]);

                        glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i] - cao_h[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i] - cao_h[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i] - cao_h[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i] - cao_h[i], -0.5*c[i]);

                        glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    }
                    glEnd();
                }
                else if (cao_d[i] == 3) {// 前面左右
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i] - cao_p[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i] - cao_p[i]);

                        glVertex3f(0.5*a[i], 0.5*b[i] - cao_h[i], 0.5*c[i] - cao_p[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i] - cao_h[i], 0.5*c[i] - cao_p[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i] - cao_h[i], -0.5*c[i] + cao_n[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i] - cao_h[i], -0.5*c[i] + cao_n[i]);

                        glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i] + cao_n[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i] + cao_n[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    }
                    glEnd();
                }
                else if (cao_d[i] == 4) {// 上面前后
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i] - cao_h[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i] - cao_h[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);

                        glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i] - cao_h[i]);
                        glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i], 0.5*c[i] - cao_h[i]);

                        glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i], 0.5*c[i] - cao_h[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i] - cao_h[i]);
                    }
                    glEnd();
                }
                else if (cao_d[i] == 6) {// 下面前后
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i] + cao_h[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i] + cao_h[i]);

                        glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i] + cao_h[i]);
                        glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i], -0.5*c[i] + cao_h[i]);

                        glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i], -0.5*c[i] + cao_h[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i] + cao_h[i]);
                    }
                    glEnd();
                }
                else if (cao_d[i] == 8) {// 右面前后
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(0.5*a[i] - cao_h[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_h[i], 0.5*b[i], -0.5*c[i]);

                        glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_h[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_h[i], 0.5*b[i], 0.5*c[i] - cao_p[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i] - cao_p[i]);

                        glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i] + cao_n[i]);
                        glVertex3f(0.5*a[i] - cao_h[i], 0.5*b[i], -0.5*c[i] + cao_n[i]);
                        glVertex3f(0.5*a[i] - cao_h[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    }
                    glEnd();
                }
                else if (cao_d[i] == 10) {// 左面前后
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i] + cao_h[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i] + cao_h[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);

                        glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i] + cao_h[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i] + cao_h[i], 0.5*b[i], 0.5*c[i] - cao_p[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i] - cao_p[i]);

                        glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i] + cao_n[i]);
                        glVertex3f(-0.5*a[i] + cao_h[i], 0.5*b[i], -0.5*c[i] + cao_n[i]);
                        glVertex3f(-0.5*a[i] + cao_h[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    }
                    glEnd();
                }
                else {
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    }
                    glEnd();
                }
            }

            // 后面
            if (mag[i] == 22) { // y反向充磁
                glColor3f(1.0f, 0.0f, 0.0f);
            }
            else if (mag[i] == 21) { // y正向充磁
                glColor3f(0.0f, 0.0f, 1.0f);
            }
            else {
                glColor3f(0.5f, 0.5f, 0.5f);
            }

            if (cao_h[i] == 0) {
                glBegin(GL_QUADS);
                {
                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                }
                glEnd();
            }
            else {
                if (cao_d[i] == 0) {// 后面上下
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i], -0.5*c[i]);

                        glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i] + cao_h[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i] + cao_h[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i] + cao_h[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i] + cao_h[i], -0.5*c[i]);

                        glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i], 0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    }
                    glEnd();
                }
                else if (cao_d[i] == 1) {// 后面左右
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i] - cao_p[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i] - cao_p[i]);

                        glVertex3f(0.5*a[i], -0.5*b[i] + cao_h[i], 0.5*c[i] - cao_p[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i] + cao_h[i], 0.5*c[i] - cao_p[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i] + cao_h[i], -0.5*c[i] + cao_n[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i] + cao_h[i], -0.5*c[i] + cao_n[i]);

                        glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i] + cao_n[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i] + cao_n[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    }
                    glEnd();
                }
                else if (cao_d[i] == 4) {// 上面前后
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i] - cao_h[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i] - cao_h[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);

                        glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i] - cao_h[i]);
                        glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i], 0.5*c[i] - cao_h[i]);

                        glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i], 0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i], 0.5*c[i] - cao_h[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i] - cao_h[i]);
                    }
                    glEnd();
                }
                else if (cao_d[i] == 6) {// 下面前后
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i] + cao_h[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i] + cao_h[i]);

                        glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i] + cao_h[i]);
                        glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i], -0.5*c[i] + cao_h[i]);

                        glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i], -0.5*c[i] + cao_h[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i] + cao_h[i]);
                    }
                    glEnd();
                }
                else if (cao_d[i] == 8) {// 右面前后
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(0.5*a[i] - cao_h[i], -0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_h[i], -0.5*b[i], -0.5*c[i]);

                        glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_h[i], -0.5*b[i], 0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_h[i], -0.5*b[i], 0.5*c[i] - cao_p[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i] - cao_p[i]);

                        glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i] + cao_n[i]);
                        glVertex3f(0.5*a[i] - cao_h[i], -0.5*b[i], -0.5*c[i] + cao_n[i]);
                        glVertex3f(0.5*a[i] - cao_h[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    }
                    glEnd();
                }
                else if (cao_d[i] == 10) {// 左面前后
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i] + cao_h[i], -0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i] + cao_h[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);

                        glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i] + cao_h[i], -0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i] + cao_h[i], -0.5*b[i], 0.5*c[i] - cao_p[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i] - cao_p[i]);

                        glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i] + cao_n[i]);
                        glVertex3f(-0.5*a[i] + cao_h[i], -0.5*b[i], -0.5*c[i] + cao_n[i]);
                        glVertex3f(-0.5*a[i] + cao_h[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    }
                    glEnd();
                }
                else {
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    }
                    glEnd();
                }
            }

            // 左面
            if (mag[i] == 12) { // x反向充磁
                glColor3f(1.0f, 0.0f, 0.0f);
            }
            else if (mag[i] == 11) { // x正向充磁
                glColor3f(0.0f, 0.0f, 1.0f);
            }
            else {
                glColor3f(0.5f, 0.5f, 0.5f);
            }

            if (cao_h[i] == 0) {
                glBegin(GL_QUADS);
                {
                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                }
                glEnd();
            }
            else {
                if (cao_d[i] == 1) {// 后面左右
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i] + cao_h[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i] + cao_h[i], 0.5*c[i]);

                        glVertex3f(-0.5*a[i], -0.5*b[i] + cao_h[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i] + cao_h[i], 0.5*c[i] - cao_p[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i] - cao_p[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);

                        glVertex3f(-0.5*a[i], -0.5*b[i] + cao_h[i], -0.5*c[i] + cao_n[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i] + cao_h[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i] + cao_n[i]);
                    }
                    glEnd();
                }
                else if (cao_d[i] == 3) {// 前面左右
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(-0.5*a[i], 0.5*b[i] - cao_h[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i] - cao_h[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);

                        glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i] - cao_p[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i] - cao_h[i], 0.5*c[i] - cao_p[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i] - cao_h[i], 0.5*c[i]);

                        glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i] + cao_n[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i] - cao_h[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i] - cao_h[i], -0.5*c[i] + cao_n[i]);
                    }
                    glEnd();
                }
                else if (cao_d[i] == 5) {// 上面左右
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i] - cao_h[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i] - cao_h[i]);

                        glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i] - cao_h[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i] - cao_p[i], 0.5*c[i] - cao_h[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i] - cao_p[i], 0.5*c[i]);

                        glVertex3f(-0.5*a[i], -0.5*b[i] + cao_n[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i] + cao_n[i], 0.5*c[i] - cao_h[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i] - cao_h[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    }
                    glEnd();
                }
                else if (cao_d[i] == 7) {// 下面左右
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i] + cao_h[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i] + cao_h[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);

                        glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i] + cao_h[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i] - cao_p[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i] - cao_p[i], -0.5*c[i] + cao_h[i]);

                        glVertex3f(-0.5*a[i], -0.5*b[i] + cao_n[i], -0.5*c[i] + cao_h[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i] + cao_n[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i] + cao_h[i]);
                    }
                    glEnd();
                }
                else if (cao_d[i] == 10) {// 左面前后
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i] - cao_p[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i] - cao_p[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);

                        glVertex3f(-0.5*a[i] + cao_h[i], 0.5*b[i], 0.5*c[i] - cao_p[i]);
                        glVertex3f(-0.5*a[i] + cao_h[i], 0.5*b[i], -0.5*c[i] + cao_n[i]);
                        glVertex3f(-0.5*a[i] + cao_h[i], -0.5*b[i], -0.5*c[i] + cao_n[i]);
                        glVertex3f(-0.5*a[i] + cao_h[i], -0.5*b[i], 0.5*c[i] - cao_p[i]);

                        glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i] + cao_n[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i] + cao_n[i]);
                    }
                    glEnd();
                }
                else if (cao_d[i] == 11) {// 左面上下
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i] - cao_p[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i] - cao_p[i], 0.5*c[i]);

                        glVertex3f(-0.5*a[i] + cao_h[i], 0.5*b[i] - cao_p[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i] + cao_h[i], 0.5*b[i] - cao_p[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i] + cao_h[i], -0.5*b[i] + cao_n[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i] + cao_h[i], -0.5*b[i] + cao_n[i], 0.5*c[i]);

                        glVertex3f(-0.5*a[i], -0.5*b[i] + cao_n[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i] + cao_n[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    }
                    glEnd();
                }
                else {
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    }
                    glEnd();
                }
            }

            // 右面
            if (mag[i] == 11) { // x正向充磁
                glColor3f(1.0f, 0.0f, 0.0f);
            }
            else if (mag[i] == 12) { // x反向充磁
                glColor3f(0.0f, 0.0f, 1.0f);
            }
            else {
                glColor3f(0.5f, 0.5f, 0.5f);
            }

            if (cao_h[i] == 0) {
                glBegin(GL_QUADS);
                {
                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                }
                glEnd();
            }
            else {
                if (cao_d[i] == 1) {// 后面左右
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i] + cao_h[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i] + cao_h[i], 0.5*c[i]);

                        glVertex3f(0.5*a[i], -0.5*b[i] + cao_h[i], 0.5*c[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i] + cao_h[i], 0.5*c[i] - cao_p[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i] - cao_p[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);

                        glVertex3f(0.5*a[i], -0.5*b[i] + cao_h[i], -0.5*c[i] + cao_n[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i] + cao_h[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i] + cao_n[i]);
                    }
                    glEnd();
                }
                else if (cao_d[i] == 3) {// 前面左右
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(0.5*a[i], 0.5*b[i] - cao_h[i], 0.5*c[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i] - cao_h[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);

                        glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i] - cao_p[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i] - cao_h[i], 0.5*c[i] - cao_p[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i] - cao_h[i], 0.5*c[i]);

                        glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i] + cao_n[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i] - cao_h[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i] - cao_h[i], -0.5*c[i] + cao_n[i]);
                    }
                    glEnd();
                }
                else if (cao_d[i] == 5) {// 上面左右
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i] - cao_h[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i] - cao_h[i]);

                        glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i] - cao_h[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i] - cao_p[i], 0.5*c[i] - cao_h[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i] - cao_p[i], 0.5*c[i]);

                        glVertex3f(0.5*a[i], -0.5*b[i] + cao_n[i], 0.5*c[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i] + cao_n[i], 0.5*c[i] - cao_h[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i] - cao_h[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    }
                    glEnd();
                }
                else if (cao_d[i] == 7) {// 下面左右
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i] + cao_h[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i] + cao_h[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);

                        glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i] + cao_h[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i] - cao_p[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i] - cao_p[i], -0.5*c[i] + cao_h[i]);

                        glVertex3f(0.5*a[i], -0.5*b[i] + cao_n[i], -0.5*c[i] + cao_h[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i] + cao_n[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i] + cao_h[i]);
                    }
                    glEnd();
                }
                else if (cao_d[i] == 8) {// 右面前后
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i] - cao_p[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i] - cao_p[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);

                        glVertex3f(0.5*a[i] - cao_h[i], 0.5*b[i], 0.5*c[i] - cao_p[i]);
                        glVertex3f(0.5*a[i] - cao_h[i], 0.5*b[i], -0.5*c[i] + cao_n[i]);
                        glVertex3f(0.5*a[i] - cao_h[i], -0.5*b[i], -0.5*c[i] + cao_n[i]);
                        glVertex3f(0.5*a[i] - cao_h[i], -0.5*b[i], 0.5*c[i] - cao_p[i]);

                        glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i] + cao_n[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i] + cao_n[i]);
                    }
                    glEnd();
                }
                else if (cao_d[i] == 9) {// 右面上下
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i] - cao_p[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i] - cao_p[i], 0.5*c[i]);

                        glVertex3f(0.5*a[i] - cao_h[i], 0.5*b[i] - cao_p[i], 0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_h[i], 0.5*b[i] - cao_p[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_h[i], -0.5*b[i] + cao_n[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_h[i], -0.5*b[i] + cao_n[i], 0.5*c[i]);

                        glVertex3f(0.5*a[i], -0.5*b[i] + cao_n[i], 0.5*c[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i] + cao_n[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    }
                    glEnd();
                }
                else {
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    }
                    glEnd();
                }
            }

            // 剩余的凹槽面
            glColor3f(0.5f, 0.5f, 0.5f);

            if (cao_h[i] != 0) {
                if (cao_d[i] == 0) {
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i] + cao_h[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i] + cao_h[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i], -0.5*c[i]);

                        glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i], 0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i] + cao_h[i], 0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i] + cao_h[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i], -0.5*c[i]);
                    }
                    glEnd();
                }
                else if (cao_d[i] == 1) {
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i] - cao_p[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i] - cao_p[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i] + cao_h[i], 0.5*c[i] - cao_p[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i] + cao_h[i], 0.5*c[i] - cao_p[i]);

                        glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i] + cao_n[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i] + cao_n[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i] + cao_h[i], -0.5*c[i] + cao_n[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i] + cao_h[i], -0.5*c[i] + cao_n[i]);
                    }
                    glEnd();
                }
                else if (cao_d[i] == 2) {
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i] - cao_h[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i] - cao_h[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i], -0.5*c[i]);

                        glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i] - cao_h[i], 0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i] - cao_h[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i], -0.5*c[i]);
                    }
                    glEnd();
                }
                else if (cao_d[i] == 3) {
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i] - cao_p[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i] - cao_p[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i] - cao_h[i], 0.5*c[i] - cao_p[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i] - cao_h[i], 0.5*c[i] - cao_p[i]);

                        glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i] + cao_n[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i] + cao_n[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i] - cao_h[i], -0.5*c[i] + cao_n[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i] - cao_h[i], -0.5*c[i] + cao_n[i]);
                    }
                    glEnd();
                }
                else if (cao_d[i] == 4) {
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i], 0.5*c[i] - cao_h[i]);
                        glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i], 0.5*c[i] - cao_h[i]);

                        glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i], 0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i], 0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i], 0.5*c[i] - cao_h[i]);
                        glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i], 0.5*c[i] - cao_h[i]);
                    }
                    glEnd();
                }
                else if (cao_d[i] == 5) {
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(0.5*a[i], 0.5*b[i] - cao_p[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i] - cao_p[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i] - cao_p[i], 0.5*c[i] - cao_h[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i] - cao_p[i], 0.5*c[i] - cao_h[i]);

                        glVertex3f(0.5*a[i], -0.5*b[i] + cao_n[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i] + cao_n[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i] + cao_n[i], 0.5*c[i] - cao_h[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i] + cao_n[i], 0.5*c[i] - cao_h[i]);
                    }
                    glEnd();
                }
                else if (cao_d[i] == 6) {
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i], -0.5*c[i] + cao_h[i]);
                        glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i], -0.5*c[i] + cao_h[i]);
                        glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i], -0.5*c[i]);

                        glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i], -0.5*c[i] + cao_h[i]);
                        glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i], -0.5*c[i] + cao_h[i]);
                        glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i], -0.5*c[i]);
                    }
                    glEnd();
                }
                else if (cao_d[i] == 7) {
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(0.5*a[i], 0.5*b[i] - cao_p[i], -0.5*c[i] + cao_h[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i] - cao_p[i], -0.5*c[i] + cao_h[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i] - cao_p[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i] - cao_p[i], -0.5*c[i]);

                        glVertex3f(0.5*a[i], -0.5*b[i] + cao_n[i], -0.5*c[i] + cao_h[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i] + cao_n[i], -0.5*c[i] + cao_h[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i] + cao_n[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i] + cao_n[i], -0.5*c[i]);
                    }
                    glEnd();
                }
                else if (cao_d[i] == 8) {
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i] + cao_n[i]);
                        glVertex3f(0.5*a[i] - cao_h[i], 0.5*b[i], -0.5*c[i] + cao_n[i]);
                        glVertex3f(0.5*a[i] - cao_h[i], -0.5*b[i], -0.5*c[i] + cao_n[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i] + cao_n[i]);

                        glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i] - cao_p[i]);
                        glVertex3f(0.5*a[i] - cao_h[i], 0.5*b[i], 0.5*c[i] - cao_p[i]);
                        glVertex3f(0.5*a[i] - cao_h[i], -0.5*b[i], 0.5*c[i] - cao_p[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i] - cao_p[i]);
                    }
                    glEnd();
                }
                else if (cao_d[i] == 9) {
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(0.5*a[i], -0.5*b[i] + cao_n[i], 0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_h[i], -0.5*b[i] + cao_n[i], 0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_h[i], -0.5*b[i] + cao_n[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], -0.5*b[i] + cao_n[i], -0.5*c[i]);

                        glVertex3f(0.5*a[i], 0.5*b[i] - cao_p[i], 0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_h[i], 0.5*b[i] - cao_p[i], 0.5*c[i]);
                        glVertex3f(0.5*a[i] - cao_h[i], 0.5*b[i] - cao_p[i], -0.5*c[i]);
                        glVertex3f(0.5*a[i], 0.5*b[i] - cao_p[i], -0.5*c[i]);
                    }
                    glEnd();
                }
                else if (cao_d[i] == 10) {
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(-0.5*a[i] + cao_h[i], 0.5*b[i], -0.5*c[i] + cao_n[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i] + cao_n[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i] + cao_n[i]);
                        glVertex3f(-0.5*a[i] + cao_h[i], -0.5*b[i], -0.5*c[i] + cao_n[i]);

                        glVertex3f(-0.5*a[i] + cao_h[i], 0.5*b[i], 0.5*c[i] - cao_p[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i] - cao_p[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i] - cao_p[i]);
                        glVertex3f(-0.5*a[i] + cao_h[i], -0.5*b[i], 0.5*c[i] - cao_p[i]);
                    }
                    glEnd();
                }
                else {
                    glBegin(GL_QUADS);
                    {
                        glVertex3f(-0.5*a[i] + cao_h[i], -0.5*b[i] + cao_n[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i] + cao_n[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], -0.5*b[i] + cao_n[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i] + cao_h[i], -0.5*b[i] + cao_n[i], -0.5*c[i]);

                        glVertex3f(-0.5*a[i] + cao_h[i], 0.5*b[i] - cao_p[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i] - cao_p[i], 0.5*c[i]);
                        glVertex3f(-0.5*a[i], 0.5*b[i] - cao_p[i], -0.5*c[i]);
                        glVertex3f(-0.5*a[i] + cao_h[i], 0.5*b[i] - cao_p[i], -0.5*c[i]);
                    }
                    glEnd();
                }
            }
        }

        //画线框
        glColor3f(0.0f, 0.0f, 0.0f);
        if (cao_h[i] == 0) {
            glBegin(GL_LINES);
            {
                glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);
                glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);

                glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);

                glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);

                glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);

                glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);

                glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);

                glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);

                glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);

                glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);
                glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);

                glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);

                glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);

                glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
            }
            glEnd();
        }
        else {
            if (cao_d[i] == 0) {
                glBegin(GL_LINES);
                {
                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i] + cao_h[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i] + cao_h[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i] + cao_h[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i] + cao_h[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i] + cao_h[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i] + cao_h[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i] + cao_h[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i] + cao_h[i], -0.5*c[i]);

                    glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i] + cao_h[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i] + cao_h[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i], -0.5*c[i]);

                    glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i] + cao_h[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i] + cao_h[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i], -0.5*c[i]);
                    //
                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    //
                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                }
                glEnd();
            }
            else if (cao_d[i] == 1) {
                glBegin(GL_LINES);
                {
                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i] + cao_n[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i] + cao_n[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i] - cao_p[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i] - cao_p[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i] + cao_h[i], -0.5*c[i] + cao_n[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i] + cao_h[i], -0.5*c[i] + cao_n[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i] + cao_h[i], 0.5*c[i] - cao_p[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i] + cao_h[i], 0.5*c[i] - cao_p[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i] + cao_h[i], -0.5*c[i] + cao_n[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i] + cao_n[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i] + cao_h[i], 0.5*c[i] - cao_p[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i] - cao_p[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i] + cao_h[i], -0.5*c[i] + cao_n[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i] + cao_n[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i] + cao_h[i], 0.5*c[i] - cao_p[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i] - cao_p[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i] + cao_n[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i] + cao_h[i], -0.5*c[i] + cao_n[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i] + cao_h[i], 0.5*c[i] - cao_p[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i] - cao_p[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i] + cao_n[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i] + cao_h[i], -0.5*c[i] + cao_n[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i] + cao_h[i], 0.5*c[i] - cao_p[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i] - cao_p[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    //
                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    //
                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                }
                glEnd();
            }
            else if (cao_d[i] == 2) {
                glBegin(GL_LINES);
                {
                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    //
                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    //
                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i] - cao_h[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i] - cao_h[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i] - cao_h[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i] - cao_h[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i] - cao_h[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i] - cao_h[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i] - cao_h[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i] - cao_h[i], -0.5*c[i]);

                    glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i] - cao_h[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i] - cao_h[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i] - cao_h[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i] - cao_h[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i], -0.5*c[i]);
                }
                glEnd();
            }
            else if (cao_d[i] == 3) {
                glBegin(GL_LINES);
                {
                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    //
                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    //
                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i] + cao_n[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i] + cao_n[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i] - cao_p[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i] - cao_p[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i] - cao_h[i], -0.5*c[i] + cao_n[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i] - cao_h[i], -0.5*c[i] + cao_n[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i] - cao_h[i], 0.5*c[i] - cao_p[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i] - cao_h[i], 0.5*c[i] - cao_p[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i] - cao_h[i], -0.5*c[i] + cao_n[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i] + cao_n[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i] - cao_h[i], 0.5*c[i] - cao_p[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i] - cao_p[i]);

                    glVertex3f(0.5*a[i], 0.5*b[i] - cao_h[i], -0.5*c[i] + cao_n[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i] + cao_n[i]);

                    glVertex3f(0.5*a[i], 0.5*b[i] - cao_h[i], 0.5*c[i] - cao_p[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i] - cao_p[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i] + cao_n[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i] - cao_h[i], -0.5*c[i] + cao_n[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i] - cao_h[i], 0.5*c[i] - cao_p[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i] - cao_p[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i] + cao_n[i]);

                    glVertex3f(0.5*a[i], 0.5*b[i] - cao_h[i], -0.5*c[i] + cao_n[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i] - cao_h[i], 0.5*c[i] - cao_p[i]);

                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i] - cao_p[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                }
                glEnd();
            }
            else if (cao_d[i] == 4) {
                glBegin(GL_LINES);
                {
                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i], 0.5*c[i] - cao_h[i]);
                    glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i], 0.5*c[i] - cao_h[i]);

                    glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    //
                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i], 0.5*c[i] - cao_h[i]);
                    glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i], 0.5*c[i] - cao_h[i]);

                    glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i], 0.5*c[i] - cao_h[i]);
                    glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i], 0.5*c[i] - cao_h[i]);
                    //
                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i], 0.5*c[i] - cao_h[i]);
                    glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i], 0.5*c[i] - cao_h[i]);

                    glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    //
                    glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i], 0.5*c[i] - cao_h[i]);
                    glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i], 0.5*c[i] - cao_h[i]);
                    glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i], 0.5*c[i] - cao_h[i]);
                    glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i], 0.5*c[i] - cao_h[i]);
                    glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i], 0.5*c[i]);
                }
                glEnd();
            }
            else if (cao_d[i] == 5) {
                glBegin(GL_LINES);
                {
                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    //
                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i] + cao_n[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i] + cao_n[i], 0.5*c[i] - cao_h[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i] - cao_p[i], 0.5*c[i] - cao_h[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i] - cao_p[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i] + cao_n[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i] + cao_n[i], 0.5*c[i] - cao_h[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i] - cao_p[i], 0.5*c[i] - cao_h[i]);

                    glVertex3f(0.5*a[i], 0.5*b[i] - cao_p[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    //
                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    //
                    glVertex3f(-0.5*a[i], -0.5*b[i] + cao_n[i], 0.5*c[i] - cao_h[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i] + cao_n[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i] - cao_p[i], 0.5*c[i] - cao_h[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i] - cao_p[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i] + cao_n[i], 0.5*c[i] - cao_h[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i] + cao_n[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], 0.5*b[i] - cao_p[i], 0.5*c[i] - cao_h[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i] - cao_p[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i] + cao_n[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i] + cao_n[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i] - cao_p[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i] - cao_p[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i] + cao_n[i], 0.5*c[i] - cao_h[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i] + cao_n[i], 0.5*c[i] - cao_h[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i] - cao_p[i], 0.5*c[i] - cao_h[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i] - cao_p[i], 0.5*c[i] - cao_h[i]);
                }
                glEnd();
            }
            else if (cao_d[i] == 6) {
                glBegin(GL_LINES);
                {
                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i], -0.5*c[i] + cao_h[i]);
                    glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i], -0.5*c[i] + cao_h[i]);

                    glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    //
                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i], -0.5*c[i] + cao_h[i]);
                    glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i], -0.5*c[i] + cao_h[i]);

                    glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i], -0.5*c[i] + cao_h[i]);
                    glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i], -0.5*c[i] + cao_h[i]);
                    //
                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i], -0.5*c[i] + cao_h[i]);
                    glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i], -0.5*c[i] + cao_h[i]);

                    glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    //
                    glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i], -0.5*c[i] + cao_h[i]);
                    glVertex3f(-0.5*a[i] + cao_n[i], -0.5*b[i], -0.5*c[i]);

                    glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i], -0.5*c[i] + cao_h[i]);
                    glVertex3f(0.5*a[i] - cao_p[i], -0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i], -0.5*c[i] + cao_h[i]);
                    glVertex3f(-0.5*a[i] + cao_n[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i], -0.5*c[i] + cao_h[i]);
                    glVertex3f(0.5*a[i] - cao_p[i], 0.5*b[i], -0.5*c[i]);
                }
                glEnd();
            }
            else if (cao_d[i] == 7) {
                glBegin(GL_LINES);
                {
                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    //
                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i] + cao_n[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i] + cao_n[i], -0.5*c[i] + cao_h[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i] - cao_p[i], -0.5*c[i] + cao_h[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i] - cao_p[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i] + cao_n[i], -0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i] + cao_n[i], -0.5*c[i] + cao_h[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i] - cao_p[i], -0.5*c[i] + cao_h[i]);

                    glVertex3f(0.5*a[i], 0.5*b[i] - cao_p[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    //
                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    //
                    glVertex3f(-0.5*a[i], -0.5*b[i] + cao_n[i], -0.5*c[i] + cao_h[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i] + cao_n[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i] - cao_p[i], -0.5*c[i] + cao_h[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i] - cao_p[i], -0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i] + cao_n[i], -0.5*c[i] + cao_h[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i] + cao_n[i], -0.5*c[i]);

                    glVertex3f(0.5*a[i], 0.5*b[i] - cao_p[i], -0.5*c[i] + cao_h[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i] - cao_p[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i] + cao_n[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i] + cao_n[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i] - cao_p[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i] - cao_p[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i] + cao_n[i], -0.5*c[i] + cao_h[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i] + cao_n[i], -0.5*c[i] + cao_h[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i] - cao_p[i], -0.5*c[i] + cao_h[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i] - cao_p[i], -0.5*c[i] + cao_h[i]);
                }
                glEnd();
            }
            else if (cao_d[i] == 8) {
                glBegin(GL_LINES);
                {
                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i] + cao_n[i]);

                    glVertex3f(0.5*a[i] - cao_h[i], -0.5*b[i], -0.5*c[i] + cao_n[i]);
                    glVertex3f(0.5*a[i] - cao_h[i], -0.5*b[i], 0.5*c[i] - cao_p[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i] - cao_p[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    //
                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i] + cao_n[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i] + cao_n[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i] - cao_p[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i] - cao_p[i]);

                    glVertex3f(0.5*a[i] - cao_h[i], -0.5*b[i], -0.5*c[i] + cao_n[i]);
                    glVertex3f(0.5*a[i] - cao_h[i], 0.5*b[i], -0.5*c[i] + cao_n[i]);

                    glVertex3f(0.5*a[i] - cao_h[i], -0.5*b[i], 0.5*c[i] - cao_p[i]);
                    glVertex3f(0.5*a[i] - cao_h[i], 0.5*b[i], 0.5*c[i] - cao_p[i]);
                    //
                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i] + cao_n[i]);

                    glVertex3f(0.5*a[i] - cao_h[i], 0.5*b[i], -0.5*c[i] + cao_n[i]);
                    glVertex3f(0.5*a[i] - cao_h[i], 0.5*b[i], 0.5*c[i] - cao_p[i]);

                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i] - cao_p[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    //
                    glVertex3f(0.5*a[i] - cao_h[i], -0.5*b[i], -0.5*c[i] + cao_n[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i] + cao_n[i]);

                    glVertex3f(0.5*a[i] - cao_h[i], -0.5*b[i], 0.5*c[i] - cao_p[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i] - cao_p[i]);

                    glVertex3f(0.5*a[i] - cao_h[i], 0.5*b[i], -0.5*c[i] + cao_n[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i] + cao_n[i]);

                    glVertex3f(0.5*a[i] - cao_h[i], 0.5*b[i], 0.5*c[i] - cao_p[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i] - cao_p[i]);
                }
                glEnd();
            }
            else if (cao_d[i] == 9) {
                glBegin(GL_LINES);
                {
                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    //
                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i] + cao_n[i], -0.5*c[i]);

                    glVertex3f(0.5*a[i] - cao_h[i], -0.5*b[i] + cao_n[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i] - cao_h[i], 0.5*b[i] - cao_p[i], -0.5*c[i]);

                    glVertex3f(0.5*a[i], 0.5*b[i] - cao_p[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i] + cao_n[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i] - cao_h[i], -0.5*b[i] + cao_n[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i] - cao_h[i], 0.5*b[i] - cao_p[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], 0.5*b[i] - cao_p[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    //
                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    //
                    glVertex3f(0.5*a[i], -0.5*b[i] + cao_n[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i] + cao_n[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], 0.5*b[i] - cao_p[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i] - cao_p[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i] - cao_h[i], -0.5*b[i] + cao_n[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i] - cao_h[i], -0.5*b[i] + cao_n[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i] - cao_h[i], 0.5*b[i] - cao_p[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i] - cao_h[i], 0.5*b[i] - cao_p[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i] - cao_h[i], -0.5*b[i] + cao_n[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i] + cao_n[i], -0.5*c[i]);

                    glVertex3f(0.5*a[i] - cao_h[i], 0.5*b[i] - cao_p[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i] - cao_p[i], -0.5*c[i]);

                    glVertex3f(0.5*a[i] - cao_h[i], -0.5*b[i] + cao_n[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i] + cao_n[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i] - cao_h[i], 0.5*b[i] - cao_p[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i] - cao_p[i], 0.5*c[i]);
                }
                glEnd();
            }
            else if (cao_d[i] == 10) {
                glBegin(GL_LINES);
                {
                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i] + cao_n[i]);

                    glVertex3f(-0.5*a[i] + cao_h[i], -0.5*b[i], -0.5*c[i] + cao_n[i]);
                    glVertex3f(-0.5*a[i] + cao_h[i], -0.5*b[i], 0.5*c[i] - cao_p[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i] - cao_p[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    //
                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i] + cao_n[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i] + cao_n[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i] - cao_p[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i] - cao_p[i]);

                    glVertex3f(-0.5*a[i] + cao_h[i], -0.5*b[i], -0.5*c[i] + cao_n[i]);
                    glVertex3f(-0.5*a[i] + cao_h[i], 0.5*b[i], -0.5*c[i] + cao_n[i]);

                    glVertex3f(-0.5*a[i] + cao_h[i], -0.5*b[i], 0.5*c[i] - cao_p[i]);
                    glVertex3f(-0.5*a[i] + cao_h[i], 0.5*b[i], 0.5*c[i] - cao_p[i]);
                    //
                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i] + cao_n[i]);

                    glVertex3f(-0.5*a[i] + cao_h[i], 0.5*b[i], -0.5*c[i] + cao_n[i]);
                    glVertex3f(-0.5*a[i] + cao_h[i], 0.5*b[i], 0.5*c[i] - cao_p[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i] - cao_p[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    //
                    glVertex3f(-0.5*a[i] + cao_h[i], -0.5*b[i], -0.5*c[i] + cao_n[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i] + cao_n[i]);

                    glVertex3f(-0.5*a[i] + cao_h[i], -0.5*b[i], 0.5*c[i] - cao_p[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i] - cao_p[i]);

                    glVertex3f(-0.5*a[i] + cao_h[i], 0.5*b[i], -0.5*c[i] + cao_n[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i] + cao_n[i]);

                    glVertex3f(-0.5*a[i] + cao_h[i], 0.5*b[i], 0.5*c[i] - cao_p[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i] - cao_p[i]);
                }
                glEnd();
            }
            else {
                glBegin(GL_LINES);
                {
                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    //
                    glVertex3f(-0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i] + cao_n[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i] + cao_h[i], -0.5*b[i] + cao_n[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i] + cao_h[i], 0.5*b[i] - cao_p[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i] - cao_p[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i] + cao_n[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i] + cao_h[i], -0.5*b[i] + cao_n[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i] + cao_h[i], 0.5*b[i] - cao_p[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i] - cao_p[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(0.5*a[i], -0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    //
                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i], -0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    glVertex3f(0.5*a[i], 0.5*b[i], 0.5*c[i]);
                    //
                    glVertex3f(-0.5*a[i], -0.5*b[i] + cao_n[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i] + cao_n[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i], 0.5*b[i] - cao_p[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i] - cao_p[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i] + cao_h[i], -0.5*b[i] + cao_n[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i] + cao_h[i], -0.5*b[i] + cao_n[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i] + cao_h[i], 0.5*b[i] - cao_p[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i] + cao_h[i], 0.5*b[i] - cao_p[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i] + cao_h[i], -0.5*b[i] + cao_n[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i] + cao_n[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i] + cao_h[i], 0.5*b[i] - cao_p[i], -0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i] - cao_p[i], -0.5*c[i]);

                    glVertex3f(-0.5*a[i] + cao_h[i], -0.5*b[i] + cao_n[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], -0.5*b[i] + cao_n[i], 0.5*c[i]);

                    glVertex3f(-0.5*a[i] + cao_h[i], 0.5*b[i] - cao_p[i], 0.5*c[i]);
                    glVertex3f(-0.5*a[i], 0.5*b[i] - cao_p[i], 0.5*c[i]);
                }
                glEnd();
            }
        }
        glDisable(GL_POLYGON_OFFSET_FILL);// 解决线框遮挡
        if (xz_xzz[i] == 0) {
            glRotatef(-xz_xzjd[i],1.0f,0.0f,0.0f);
        } else if (xz_xzz[i] == 1) {
            glRotatef(-xz_xzjd[i],0.0f,1.0f,0.0f);
        } else if (xz_xzz[i] == 2) {
            glRotatef(-xz_xzjd[i],0.0f,0.0f,1.0f);
        } else {
            //
        }
        glTranslatef(-cx[i], -cy[i], -cz[i]);
    }
}

// 绘图参数设置
void SetupRC()
{
    glClearColor(0.5,0.7,0.9,0.0); //指定背景颜色（依次为RGBA）
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glFlush();
    //glutSwapBuffers();
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);//被遮住的部分不绘制

	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
}



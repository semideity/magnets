#include <math.h>

double P(double p1, double p2, double p3, double c)
{
	double out;
	if (p2 == 0) {
		out=0;
	} else {
		out= atan(p1/p2*(p3-c)/sqrt(p1*p1+p2*p2+pow(p3-c,2)))
			-atan(p1/p2*(p3-0)/sqrt(p1*p1+p2*p2+pow(p3-0,2)));
	}
	return(out);
}

/*
符号    说明    	单位
------------------------
m		磁场强度    kA/m
a   	磁铁长  	mm
b   	磁铁宽  	mm
c   	磁铁高  	mm
x       磁铁x坐标   mm
y       磁铁y坐标   mm
z       磁铁z坐标   mm
fx   	场点x坐标   mm
fy   	场点y坐标   mm
fz   	场点z坐标   mm
H       磁场输出    Oe
------------------------
(以磁铁中心为坐标参考点)
*/

double MzHx(double m, double a, double b, double c, double x, double y, double z, double fx, double fy, double fz)
{
	double out=0;
	fx=fx-x+a/2;
	fy=fy-y+b/2;
	fz=fz-z+c/2;
	if (fx == 0 && fz == 0) {
		if (fy > b) {
			out=m/2*(
				-log((sqrt(pow(a-fx,2)+pow(b-fy,2)+pow(fz-c,2))-(b-fy))/(sqrt(pow(a-fx,2)+pow(b-fy,2)+pow(fz-c,2))+(b-fy)))
				+log((sqrt(pow(a-fx,2)+pow(b-fy,2)+pow(fz-0,2))-(b-fy))/(sqrt(pow(a-fx,2)+pow(b-fy,2)+pow(fz-0,2))+(b-fy)))

				-log((sqrt(pow(a-fx,2)+pow(fy,2)+pow(fz-c,2))-fy)/(sqrt(pow(a-fx,2)+pow(fy,2)+pow(fz-c,2))+fy))
				+log((sqrt(pow(a-fx,2)+pow(fy,2)+pow(fz-0,2))-fy)/(sqrt(pow(a-fx,2)+pow(fy,2)+pow(fz-0,2))+fy))

				+log((sqrt(pow(fx,2)+pow(b-fy,2)+pow(fz-c,2))-(b-fy))/(sqrt(pow(fx,2)+pow(b-fy,2)+pow(fz-c,2))+(b-fy)))
				//-log((sqrt(pow(fx,2)+pow(b-fy,2)+pow(fz-0,2))-(b-fy))/(sqrt(pow(fx,2)+pow(b-fy,2)+pow(fz-0,2))+(b-fy)))

				+log((sqrt(pow(fx,2)+pow(fy,2)+pow(fz-c,2))-fy)/(sqrt(pow(fx,2)+pow(fy,2)+pow(fz-c,2))+fy))
				//-log((sqrt(pow(fx,2)+pow(fy,2)+pow(fz-0,2))-fy)/(sqrt(pow(fx,2)+pow(fy,2)+pow(fz-0,2))+fy))

				-log((pow(b-fy,2)-(b-fy)*fabs(b-fy))/(pow(fy,2)+fy*fabs(fy)))
			);
		} else if (fy <= b && fy >=0) {
            // 无法排除的奇点
			out=0;
		} else { // fy < 0
            out=m/2*(
				-log((sqrt(pow(a-fx,2)+pow(b-fy,2)+pow(fz-c,2))-(b-fy))/(sqrt(pow(a-fx,2)+pow(b-fy,2)+pow(fz-c,2))+(b-fy)))
				+log((sqrt(pow(a-fx,2)+pow(b-fy,2)+pow(fz-0,2))-(b-fy))/(sqrt(pow(a-fx,2)+pow(b-fy,2)+pow(fz-0,2))+(b-fy)))

				-log((sqrt(pow(a-fx,2)+pow(fy,2)+pow(fz-c,2))-fy)/(sqrt(pow(a-fx,2)+pow(fy,2)+pow(fz-c,2))+fy))
				+log((sqrt(pow(a-fx,2)+pow(fy,2)+pow(fz-0,2))-fy)/(sqrt(pow(a-fx,2)+pow(fy,2)+pow(fz-0,2))+fy))

				+log((sqrt(pow(fx,2)+pow(b-fy,2)+pow(fz-c,2))-(b-fy))/(sqrt(pow(fx,2)+pow(b-fy,2)+pow(fz-c,2))+(b-fy)))
				//-log((sqrt(pow(fx,2)+pow(b-fy,2)+pow(fz-0,2))-(b-fy))/(sqrt(pow(fx,2)+pow(b-fy,2)+pow(fz-0,2))+(b-fy)))

				+log((sqrt(pow(fx,2)+pow(fy,2)+pow(fz-c,2))-fy)/(sqrt(pow(fx,2)+pow(fy,2)+pow(fz-c,2))+fy))
				//-log((sqrt(pow(fx,2)+pow(fy,2)+pow(fz-0,2))-fy)/(sqrt(pow(fx,2)+pow(fy,2)+pow(fz-0,2))+fy))

				-log((pow(fy,2)-fy*fabs(fy))/(pow(b-fy,2)+(b-fy)*fabs(b-fy)))
			);
		}
	} else if (fx == 0 && fz == c) {
		if (fy > b) {
            out=m/2*(
				-log((sqrt(pow(a-fx,2)+pow(b-fy,2)+pow(fz-c,2))-(b-fy))/(sqrt(pow(a-fx,2)+pow(b-fy,2)+pow(fz-c,2))+(b-fy)))
				+log((sqrt(pow(a-fx,2)+pow(b-fy,2)+pow(fz-0,2))-(b-fy))/(sqrt(pow(a-fx,2)+pow(b-fy,2)+pow(fz-0,2))+(b-fy)))

				-log((sqrt(pow(a-fx,2)+pow(fy,2)+pow(fz-c,2))-fy)/(sqrt(pow(a-fx,2)+pow(fy,2)+pow(fz-c,2))+fy))
				+log((sqrt(pow(a-fx,2)+pow(fy,2)+pow(fz-0,2))-fy)/(sqrt(pow(a-fx,2)+pow(fy,2)+pow(fz-0,2))+fy))

				//+log((sqrt(pow(fx,2)+pow(b-fy,2)+pow(fz-c,2))-(b-fy))/(sqrt(pow(fx,2)+pow(b-fy,2)+pow(fz-c,2))+(b-fy)))
				-log((sqrt(pow(fx,2)+pow(b-fy,2)+pow(fz-0,2))-(b-fy))/(sqrt(pow(fx,2)+pow(b-fy,2)+pow(fz-0,2))+(b-fy)))

				//+log((sqrt(pow(fx,2)+pow(fy,2)+pow(fz-c,2))-fy)/(sqrt(pow(fx,2)+pow(fy,2)+pow(fz-c,2))+fy))
				-log((sqrt(pow(fx,2)+pow(fy,2)+pow(fz-0,2))-fy)/(sqrt(pow(fx,2)+pow(fy,2)+pow(fz-0,2))+fy))

				+log((pow(b-fy,2)-(b-fy)*fabs(b-fy))/(pow(fy,2)+fy*fabs(fy)))
			);
		} else if (fy <= b && fy >=0) {
            // 无法排除的奇点
			out=0;
		} else { // fy < 0
            out=m/2*(
				-log((sqrt(pow(a-fx,2)+pow(b-fy,2)+pow(fz-c,2))-(b-fy))/(sqrt(pow(a-fx,2)+pow(b-fy,2)+pow(fz-c,2))+(b-fy)))
				+log((sqrt(pow(a-fx,2)+pow(b-fy,2)+pow(fz-0,2))-(b-fy))/(sqrt(pow(a-fx,2)+pow(b-fy,2)+pow(fz-0,2))+(b-fy)))

				-log((sqrt(pow(a-fx,2)+pow(fy,2)+pow(fz-c,2))-fy)/(sqrt(pow(a-fx,2)+pow(fy,2)+pow(fz-c,2))+fy))
				+log((sqrt(pow(a-fx,2)+pow(fy,2)+pow(fz-0,2))-fy)/(sqrt(pow(a-fx,2)+pow(fy,2)+pow(fz-0,2))+fy))

				//+log((sqrt(pow(fx,2)+pow(b-fy,2)+pow(fz-c,2))-(b-fy))/(sqrt(pow(fx,2)+pow(b-fy,2)+pow(fz-c,2))+(b-fy)))
				-log((sqrt(pow(fx,2)+pow(b-fy,2)+pow(fz-0,2))-(b-fy))/(sqrt(pow(fx,2)+pow(b-fy,2)+pow(fz-0,2))+(b-fy)))

				//+log((sqrt(pow(fx,2)+pow(fy,2)+pow(fz-c,2))-fy)/(sqrt(pow(fx,2)+pow(fy,2)+pow(fz-c,2))+fy))
				-log((sqrt(pow(fx,2)+pow(fy,2)+pow(fz-0,2))-fy)/(sqrt(pow(fx,2)+pow(fy,2)+pow(fz-0,2))+fy))

				+log((pow(fy,2)-fy*fabs(fy))/(pow(b-fy,2)+(b-fy)*fabs(b-fy)))
			);
        }
	} else if (fx == a && fz == 0) {
        if (fy > b) {
            out=m/2*(
				-log((sqrt(pow(a-fx,2)+pow(b-fy,2)+pow(fz-c,2))-(b-fy))/(sqrt(pow(a-fx,2)+pow(b-fy,2)+pow(fz-c,2))+(b-fy)))
				//+log((sqrt(pow(a-fx,2)+pow(b-fy,2)+pow(fz-0,2))-(b-fy))/(sqrt(pow(a-fx,2)+pow(b-fy,2)+pow(fz-0,2))+(b-fy)))

				-log((sqrt(pow(a-fx,2)+pow(fy,2)+pow(fz-c,2))-fy)/(sqrt(pow(a-fx,2)+pow(fy,2)+pow(fz-c,2))+fy))
				//+log((sqrt(pow(a-fx,2)+pow(fy,2)+pow(fz-0,2))-fy)/(sqrt(pow(a-fx,2)+pow(fy,2)+pow(fz-0,2))+fy))

				+log((sqrt(pow(fx,2)+pow(b-fy,2)+pow(fz-c,2))-(b-fy))/(sqrt(pow(fx,2)+pow(b-fy,2)+pow(fz-c,2))+(b-fy)))
				-log((sqrt(pow(fx,2)+pow(b-fy,2)+pow(fz-0,2))-(b-fy))/(sqrt(pow(fx,2)+pow(b-fy,2)+pow(fz-0,2))+(b-fy)))

				+log((sqrt(pow(fx,2)+pow(fy,2)+pow(fz-c,2))-fy)/(sqrt(pow(fx,2)+pow(fy,2)+pow(fz-c,2))+fy))
				-log((sqrt(pow(fx,2)+pow(fy,2)+pow(fz-0,2))-fy)/(sqrt(pow(fx,2)+pow(fy,2)+pow(fz-0,2))+fy))

				+log((pow(b-fy,2)-(b-fy)*fabs(b-fy))/(pow(fy,2)+fy*fabs(fy)))
			);
		} else if (fy <= b && fy >=0) {
            // 无法排除的奇点
			out=0;
		} else { // fy < 0
            out=m/2*(
				-log((sqrt(pow(a-fx,2)+pow(b-fy,2)+pow(fz-c,2))-(b-fy))/(sqrt(pow(a-fx,2)+pow(b-fy,2)+pow(fz-c,2))+(b-fy)))
				//+log((sqrt(pow(a-fx,2)+pow(b-fy,2)+pow(fz-0,2))-(b-fy))/(sqrt(pow(a-fx,2)+pow(b-fy,2)+pow(fz-0,2))+(b-fy)))

				-log((sqrt(pow(a-fx,2)+pow(fy,2)+pow(fz-c,2))-fy)/(sqrt(pow(a-fx,2)+pow(fy,2)+pow(fz-c,2))+fy))
				//+log((sqrt(pow(a-fx,2)+pow(fy,2)+pow(fz-0,2))-fy)/(sqrt(pow(a-fx,2)+pow(fy,2)+pow(fz-0,2))+fy))

				+log((sqrt(pow(fx,2)+pow(b-fy,2)+pow(fz-c,2))-(b-fy))/(sqrt(pow(fx,2)+pow(b-fy,2)+pow(fz-c,2))+(b-fy)))
				-log((sqrt(pow(fx,2)+pow(b-fy,2)+pow(fz-0,2))-(b-fy))/(sqrt(pow(fx,2)+pow(b-fy,2)+pow(fz-0,2))+(b-fy)))

				+log((sqrt(pow(fx,2)+pow(fy,2)+pow(fz-c,2))-fy)/(sqrt(pow(fx,2)+pow(fy,2)+pow(fz-c,2))+fy))
				-log((sqrt(pow(fx,2)+pow(fy,2)+pow(fz-0,2))-fy)/(sqrt(pow(fx,2)+pow(fy,2)+pow(fz-0,2))+fy))

				+log((pow(fy,2)-fy*fabs(fy))/(pow(b-fy,2)+(b-fy)*fabs(b-fy)))
			);
		}
	} else if (fx == a && fz == c) {
        if (fy > b) {
            out=m/2*(
				//-log((sqrt(pow(a-fx,2)+pow(b-fy,2)+pow(fz-c,2))-(b-fy))/(sqrt(pow(a-fx,2)+pow(b-fy,2)+pow(fz-c,2))+(b-fy)))
				+log((sqrt(pow(a-fx,2)+pow(b-fy,2)+pow(fz-0,2))-(b-fy))/(sqrt(pow(a-fx,2)+pow(b-fy,2)+pow(fz-0,2))+(b-fy)))

				//-log((sqrt(pow(a-fx,2)+pow(fy,2)+pow(fz-c,2))-fy)/(sqrt(pow(a-fx,2)+pow(fy,2)+pow(fz-c,2))+fy))
				+log((sqrt(pow(a-fx,2)+pow(fy,2)+pow(fz-0,2))-fy)/(sqrt(pow(a-fx,2)+pow(fy,2)+pow(fz-0,2))+fy))

				+log((sqrt(pow(fx,2)+pow(b-fy,2)+pow(fz-c,2))-(b-fy))/(sqrt(pow(fx,2)+pow(b-fy,2)+pow(fz-c,2))+(b-fy)))
				-log((sqrt(pow(fx,2)+pow(b-fy,2)+pow(fz-0,2))-(b-fy))/(sqrt(pow(fx,2)+pow(b-fy,2)+pow(fz-0,2))+(b-fy)))

				+log((sqrt(pow(fx,2)+pow(fy,2)+pow(fz-c,2))-fy)/(sqrt(pow(fx,2)+pow(fy,2)+pow(fz-c,2))+fy))
				-log((sqrt(pow(fx,2)+pow(fy,2)+pow(fz-0,2))-fy)/(sqrt(pow(fx,2)+pow(fy,2)+pow(fz-0,2))+fy))

				-log((pow(b-fy,2)-(b-fy)*fabs(b-fy))/(pow(fy,2)+fy*fabs(fy)))
			);
		} else if (fy <= b && fy >=0) {
			// 无法排除的奇点
			out=0;
		} else { // fy < 0
            out=m/2*(
				//-log((sqrt(pow(a-fx,2)+pow(b-fy,2)+pow(fz-c,2))-(b-fy))/(sqrt(pow(a-fx,2)+pow(b-fy,2)+pow(fz-c,2))+(b-fy)))
				+log((sqrt(pow(a-fx,2)+pow(b-fy,2)+pow(fz-0,2))-(b-fy))/(sqrt(pow(a-fx,2)+pow(b-fy,2)+pow(fz-0,2))+(b-fy)))

				//-log((sqrt(pow(a-fx,2)+pow(fy,2)+pow(fz-c,2))-fy)/(sqrt(pow(a-fx,2)+pow(fy,2)+pow(fz-c,2))+fy))
				+log((sqrt(pow(a-fx,2)+pow(fy,2)+pow(fz-0,2))-fy)/(sqrt(pow(a-fx,2)+pow(fy,2)+pow(fz-0,2))+fy))

				+log((sqrt(pow(fx,2)+pow(b-fy,2)+pow(fz-c,2))-(b-fy))/(sqrt(pow(fx,2)+pow(b-fy,2)+pow(fz-c,2))+(b-fy)))
				-log((sqrt(pow(fx,2)+pow(b-fy,2)+pow(fz-0,2))-(b-fy))/(sqrt(pow(fx,2)+pow(b-fy,2)+pow(fz-0,2))+(b-fy)))

				+log((sqrt(pow(fx,2)+pow(fy,2)+pow(fz-c,2))-fy)/(sqrt(pow(fx,2)+pow(fy,2)+pow(fz-c,2))+fy))
				-log((sqrt(pow(fx,2)+pow(fy,2)+pow(fz-0,2))-fy)/(sqrt(pow(fx,2)+pow(fy,2)+pow(fz-0,2))+fy))

				-log((pow(fy,2)-fy*fabs(fy))/(pow(b-fy,2)+(b-fy)*fabs(b-fy)))
			);
        }
	} else {
		out=m/2*(
			-log((sqrt(pow(a-fx,2)+pow(b-fy,2)+pow(fz-c,2))-(b-fy))/(sqrt(pow(a-fx,2)+pow(b-fy,2)+pow(fz-c,2))+(b-fy)))
			+log((sqrt(pow(a-fx,2)+pow(b-fy,2)+pow(fz-0,2))-(b-fy))/(sqrt(pow(a-fx,2)+pow(b-fy,2)+pow(fz-0,2))+(b-fy)))

			-log((sqrt(pow(a-fx,2)+pow(fy,2)+pow(fz-c,2))-fy)/(sqrt(pow(a-fx,2)+pow(fy,2)+pow(fz-c,2))+fy))
			+log((sqrt(pow(a-fx,2)+pow(fy,2)+pow(fz-0,2))-fy)/(sqrt(pow(a-fx,2)+pow(fy,2)+pow(fz-0,2))+fy))

			+log((sqrt(pow(fx,2)+pow(b-fy,2)+pow(fz-c,2))-(b-fy))/(sqrt(pow(fx,2)+pow(b-fy,2)+pow(fz-c,2))+(b-fy)))
			-log((sqrt(pow(fx,2)+pow(b-fy,2)+pow(fz-0,2))-(b-fy))/(sqrt(pow(fx,2)+pow(b-fy,2)+pow(fz-0,2))+(b-fy)))

			+log((sqrt(pow(fx,2)+pow(fy,2)+pow(fz-c,2))-fy)/(sqrt(pow(fx,2)+pow(fy,2)+pow(fz-c,2))+fy))
			-log((sqrt(pow(fx,2)+pow(fy,2)+pow(fz-0,2))-fy)/(sqrt(pow(fx,2)+pow(fy,2)+pow(fz-0,2))+fy))
		);
	}

	return(out);
}

double MzHy(double m, double a, double b, double c, double x, double y, double z, double fx, double fy, double fz)
{
	double out;
	fx=fx-x+a/2;
	fy=fy-y+b/2;
	fz=fz-z+c/2;
	if (fy == 0 && fz == 0) {
		if (fx > a) {
			out=m/2*(
				-log((sqrt(pow(b-fy,2)+pow(a-fx,2)+pow(fz-c,2))-(a-fx))/(sqrt(pow(b-fy,2)+pow(a-fx,2)+pow(fz-c,2))+(a-fx)))
				+log((sqrt(pow(b-fy,2)+pow(a-fx,2)+pow(fz-0,2))-(a-fx))/(sqrt(pow(b-fy,2)+pow(a-fx,2)+pow(fz-0,2))+(a-fx)))

				-log((sqrt(pow(b-fy,2)+pow(fx,2)+pow(fz-c,2))-fx)/(sqrt(pow(b-fy,2)+pow(fx,2)+pow(fz-c,2))+fx))
				+log((sqrt(pow(b-fy,2)+pow(fx,2)+pow(fz-0,2))-fx)/(sqrt(pow(b-fy,2)+pow(fx,2)+pow(fz-0,2))+fx))

				+log((sqrt(pow(fy,2)+pow(a-fx,2)+pow(fz-c,2))-(a-fx))/(sqrt(pow(fy,2)+pow(a-fx,2)+pow(fz-c,2))+(a-fx)))
				//-log((sqrt(pow(fy,2)+pow(a-fx,2)+pow(fz-0,2))-(a-fx))/(sqrt(pow(fy,2)+pow(a-fx,2)+pow(fz-0,2))+(a-fx)))

				+log((sqrt(pow(fy,2)+pow(fx,2)+pow(fz-c,2))-fx)/(sqrt(pow(fy,2)+pow(fx,2)+pow(fz-c,2))+fx))
				//-log((sqrt(pow(fy,2)+pow(fx,2)+pow(fz-0,2))-fx)/(sqrt(pow(fy,2)+pow(fx,2)+pow(fz-0,2))+fx))

				-log((pow(a-fx,2)-(a-fx)*fabs(a-fx))/(pow(fx,2)+fx*fabs(fx)))
			);
		} else if (fx <= b && fx >=0) {
			// 无法排除的奇点
			out=0;
		} else { // fx < 0
            out=m/2*(
				-log((sqrt(pow(b-fy,2)+pow(a-fx,2)+pow(fz-c,2))-(a-fx))/(sqrt(pow(b-fy,2)+pow(a-fx,2)+pow(fz-c,2))+(a-fx)))
				+log((sqrt(pow(b-fy,2)+pow(a-fx,2)+pow(fz-0,2))-(a-fx))/(sqrt(pow(b-fy,2)+pow(a-fx,2)+pow(fz-0,2))+(a-fx)))

				-log((sqrt(pow(b-fy,2)+pow(fx,2)+pow(fz-c,2))-fx)/(sqrt(pow(b-fy,2)+pow(fx,2)+pow(fz-c,2))+fx))
				+log((sqrt(pow(b-fy,2)+pow(fx,2)+pow(fz-0,2))-fx)/(sqrt(pow(b-fy,2)+pow(fx,2)+pow(fz-0,2))+fx))

				+log((sqrt(pow(fy,2)+pow(a-fx,2)+pow(fz-c,2))-(a-fx))/(sqrt(pow(fy,2)+pow(a-fx,2)+pow(fz-c,2))+(a-fx)))
				//-log((sqrt(pow(fy,2)+pow(a-fx,2)+pow(fz-0,2))-(a-fx))/(sqrt(pow(fy,2)+pow(a-fx,2)+pow(fz-0,2))+(a-fx)))

				+log((sqrt(pow(fy,2)+pow(fx,2)+pow(fz-c,2))-fx)/(sqrt(pow(fy,2)+pow(fx,2)+pow(fz-c,2))+fx))
				//-log((sqrt(pow(fy,2)+pow(fx,2)+pow(fz-0,2))-fx)/(sqrt(pow(fy,2)+pow(fx,2)+pow(fz-0,2))+fx))

				-log((pow(fx,2)-fx*fabs(fx))/(pow(a-fx,2)+(a-fx)*fabs(a-fx)))
			);
        }
	} else if (fy == 0 && fz == c) {
        if (fx > a) {
            out=m/2*(
				-log((sqrt(pow(b-fy,2)+pow(a-fx,2)+pow(fz-c,2))-(a-fx))/(sqrt(pow(b-fy,2)+pow(a-fx,2)+pow(fz-c,2))+(a-fx)))
				+log((sqrt(pow(b-fy,2)+pow(a-fx,2)+pow(fz-0,2))-(a-fx))/(sqrt(pow(b-fy,2)+pow(a-fx,2)+pow(fz-0,2))+(a-fx)))

				-log((sqrt(pow(b-fy,2)+pow(fx,2)+pow(fz-c,2))-fx)/(sqrt(pow(b-fy,2)+pow(fx,2)+pow(fz-c,2))+fx))
				+log((sqrt(pow(b-fy,2)+pow(fx,2)+pow(fz-0,2))-fx)/(sqrt(pow(b-fy,2)+pow(fx,2)+pow(fz-0,2))+fx))

				//+log((sqrt(pow(fy,2)+pow(a-fx,2)+pow(fz-c,2))-(a-fx))/(sqrt(pow(fy,2)+pow(a-fx,2)+pow(fz-c,2))+(a-fx)))
				-log((sqrt(pow(fy,2)+pow(a-fx,2)+pow(fz-0,2))-(a-fx))/(sqrt(pow(fy,2)+pow(a-fx,2)+pow(fz-0,2))+(a-fx)))

				//+log((sqrt(pow(fy,2)+pow(fx,2)+pow(fz-c,2))-fx)/(sqrt(pow(fy,2)+pow(fx,2)+pow(fz-c,2))+fx))
				-log((sqrt(pow(fy,2)+pow(fx,2)+pow(fz-0,2))-fx)/(sqrt(pow(fy,2)+pow(fx,2)+pow(fz-0,2))+fx))

				+log((pow(a-fx,2)-(a-fx)*fabs(a-fx))/(pow(fx,2)+fx*fabs(fx)))
			);
		} else if (fx <= b && fx >=0) {
			// 无法排除的奇点
			out=0;
		} else { // fx < 0
            out=m/2*(
				-log((sqrt(pow(b-fy,2)+pow(a-fx,2)+pow(fz-c,2))-(a-fx))/(sqrt(pow(b-fy,2)+pow(a-fx,2)+pow(fz-c,2))+(a-fx)))
				+log((sqrt(pow(b-fy,2)+pow(a-fx,2)+pow(fz-0,2))-(a-fx))/(sqrt(pow(b-fy,2)+pow(a-fx,2)+pow(fz-0,2))+(a-fx)))

				-log((sqrt(pow(b-fy,2)+pow(fx,2)+pow(fz-c,2))-fx)/(sqrt(pow(b-fy,2)+pow(fx,2)+pow(fz-c,2))+fx))
				+log((sqrt(pow(b-fy,2)+pow(fx,2)+pow(fz-0,2))-fx)/(sqrt(pow(b-fy,2)+pow(fx,2)+pow(fz-0,2))+fx))

				//+log((sqrt(pow(fy,2)+pow(a-fx,2)+pow(fz-c,2))-(a-fx))/(sqrt(pow(fy,2)+pow(a-fx,2)+pow(fz-c,2))+(a-fx)))
				-log((sqrt(pow(fy,2)+pow(a-fx,2)+pow(fz-0,2))-(a-fx))/(sqrt(pow(fy,2)+pow(a-fx,2)+pow(fz-0,2))+(a-fx)))

				//+log((sqrt(pow(fy,2)+pow(fx,2)+pow(fz-c,2))-fx)/(sqrt(pow(fy,2)+pow(fx,2)+pow(fz-c,2))+fx))
				-log((sqrt(pow(fy,2)+pow(fx,2)+pow(fz-0,2))-fx)/(sqrt(pow(fy,2)+pow(fx,2)+pow(fz-0,2))+fx))

				+log((pow(fx,2)-fx*fabs(fx))/(pow(a-fx,2)+(a-fx)*fabs(a-fx)))
			);
		}
	} else if (fy == b && fz == 0) {
        if (fx > a) {
			out=m/2*(
				-log((sqrt(pow(b-fy,2)+pow(a-fx,2)+pow(fz-c,2))-(a-fx))/(sqrt(pow(b-fy,2)+pow(a-fx,2)+pow(fz-c,2))+(a-fx)))
				//+log((sqrt(pow(b-fy,2)+pow(a-fx,2)+pow(fz-0,2))-(a-fx))/(sqrt(pow(b-fy,2)+pow(a-fx,2)+pow(fz-0,2))+(a-fx)))

				-log((sqrt(pow(b-fy,2)+pow(fx,2)+pow(fz-c,2))-fx)/(sqrt(pow(b-fy,2)+pow(fx,2)+pow(fz-c,2))+fx))
				//+log((sqrt(pow(b-fy,2)+pow(fx,2)+pow(fz-0,2))-fx)/(sqrt(pow(b-fy,2)+pow(fx,2)+pow(fz-0,2))+fx))

				+log((sqrt(pow(fy,2)+pow(a-fx,2)+pow(fz-c,2))-(a-fx))/(sqrt(pow(fy,2)+pow(a-fx,2)+pow(fz-c,2))+(a-fx)))
				-log((sqrt(pow(fy,2)+pow(a-fx,2)+pow(fz-0,2))-(a-fx))/(sqrt(pow(fy,2)+pow(a-fx,2)+pow(fz-0,2))+(a-fx)))

				+log((sqrt(pow(fy,2)+pow(fx,2)+pow(fz-c,2))-fx)/(sqrt(pow(fy,2)+pow(fx,2)+pow(fz-c,2))+fx))
				-log((sqrt(pow(fy,2)+pow(fx,2)+pow(fz-0,2))-fx)/(sqrt(pow(fy,2)+pow(fx,2)+pow(fz-0,2))+fx))

				+log((pow(a-fx,2)-(a-fx)*fabs(a-fx))/(pow(fx,2)+fx*fabs(fx)))
			);
		} else if (fx <= b && fx >=0) {
			// 无法排除的奇点
			out=0;
		} else { // fx < 0
            out=m/2*(
				-log((sqrt(pow(b-fy,2)+pow(a-fx,2)+pow(fz-c,2))-(a-fx))/(sqrt(pow(b-fy,2)+pow(a-fx,2)+pow(fz-c,2))+(a-fx)))
				//+log((sqrt(pow(b-fy,2)+pow(a-fx,2)+pow(fz-0,2))-(a-fx))/(sqrt(pow(b-fy,2)+pow(a-fx,2)+pow(fz-0,2))+(a-fx)))

				-log((sqrt(pow(b-fy,2)+pow(fx,2)+pow(fz-c,2))-fx)/(sqrt(pow(b-fy,2)+pow(fx,2)+pow(fz-c,2))+fx))
				//+log((sqrt(pow(b-fy,2)+pow(fx,2)+pow(fz-0,2))-fx)/(sqrt(pow(b-fy,2)+pow(fx,2)+pow(fz-0,2))+fx))

				+log((sqrt(pow(fy,2)+pow(a-fx,2)+pow(fz-c,2))-(a-fx))/(sqrt(pow(fy,2)+pow(a-fx,2)+pow(fz-c,2))+(a-fx)))
				-log((sqrt(pow(fy,2)+pow(a-fx,2)+pow(fz-0,2))-(a-fx))/(sqrt(pow(fy,2)+pow(a-fx,2)+pow(fz-0,2))+(a-fx)))

				+log((sqrt(pow(fy,2)+pow(fx,2)+pow(fz-c,2))-fx)/(sqrt(pow(fy,2)+pow(fx,2)+pow(fz-c,2))+fx))
				-log((sqrt(pow(fy,2)+pow(fx,2)+pow(fz-0,2))-fx)/(sqrt(pow(fy,2)+pow(fx,2)+pow(fz-0,2))+fx))

				+log((pow(fx,2)-fx*fabs(fx))/(pow(a-fx,2)+(a-fx)*fabs(a-fx)))
			);
		}
	} else if (fy == b && fz == c) {
        if (fx > a) {
            out=m/2*(
				//-log((sqrt(pow(b-fy,2)+pow(a-fx,2)+pow(fz-c,2))-(a-fx))/(sqrt(pow(b-fy,2)+pow(a-fx,2)+pow(fz-c,2))+(a-fx)))
				+log((sqrt(pow(b-fy,2)+pow(a-fx,2)+pow(fz-0,2))-(a-fx))/(sqrt(pow(b-fy,2)+pow(a-fx,2)+pow(fz-0,2))+(a-fx)))

				//-log((sqrt(pow(b-fy,2)+pow(fx,2)+pow(fz-c,2))-fx)/(sqrt(pow(b-fy,2)+pow(fx,2)+pow(fz-c,2))+fx))
				+log((sqrt(pow(b-fy,2)+pow(fx,2)+pow(fz-0,2))-fx)/(sqrt(pow(b-fy,2)+pow(fx,2)+pow(fz-0,2))+fx))

				+log((sqrt(pow(fy,2)+pow(a-fx,2)+pow(fz-c,2))-(a-fx))/(sqrt(pow(fy,2)+pow(a-fx,2)+pow(fz-c,2))+(a-fx)))
				-log((sqrt(pow(fy,2)+pow(a-fx,2)+pow(fz-0,2))-(a-fx))/(sqrt(pow(fy,2)+pow(a-fx,2)+pow(fz-0,2))+(a-fx)))

				+log((sqrt(pow(fy,2)+pow(fx,2)+pow(fz-c,2))-fx)/(sqrt(pow(fy,2)+pow(fx,2)+pow(fz-c,2))+fx))
				-log((sqrt(pow(fy,2)+pow(fx,2)+pow(fz-0,2))-fx)/(sqrt(pow(fy,2)+pow(fx,2)+pow(fz-0,2))+fx))

				-log((pow(a-fx,2)-(a-fx)*fabs(a-fx))/(pow(fx,2)+fx*fabs(fx)))
			);
		} else if (fx <= b && fx >=0) {
			// 无法排除的奇点
			out=0;
		} else { // fx < 0
            out=m/2*(
				//-log((sqrt(pow(b-fy,2)+pow(a-fx,2)+pow(fz-c,2))-(a-fx))/(sqrt(pow(b-fy,2)+pow(a-fx,2)+pow(fz-c,2))+(a-fx)))
				+log((sqrt(pow(b-fy,2)+pow(a-fx,2)+pow(fz-0,2))-(a-fx))/(sqrt(pow(b-fy,2)+pow(a-fx,2)+pow(fz-0,2))+(a-fx)))

				//-log((sqrt(pow(b-fy,2)+pow(fx,2)+pow(fz-c,2))-fx)/(sqrt(pow(b-fy,2)+pow(fx,2)+pow(fz-c,2))+fx))
				+log((sqrt(pow(b-fy,2)+pow(fx,2)+pow(fz-0,2))-fx)/(sqrt(pow(b-fy,2)+pow(fx,2)+pow(fz-0,2))+fx))

				+log((sqrt(pow(fy,2)+pow(a-fx,2)+pow(fz-c,2))-(a-fx))/(sqrt(pow(fy,2)+pow(a-fx,2)+pow(fz-c,2))+(a-fx)))
				-log((sqrt(pow(fy,2)+pow(a-fx,2)+pow(fz-0,2))-(a-fx))/(sqrt(pow(fy,2)+pow(a-fx,2)+pow(fz-0,2))+(a-fx)))

				+log((sqrt(pow(fy,2)+pow(fx,2)+pow(fz-c,2))-fx)/(sqrt(pow(fy,2)+pow(fx,2)+pow(fz-c,2))+fx))
				-log((sqrt(pow(fy,2)+pow(fx,2)+pow(fz-0,2))-fx)/(sqrt(pow(fy,2)+pow(fx,2)+pow(fz-0,2))+fx))

				-log((pow(fx,2)-fx*fabs(fx))/(pow(a-fx,2)+(a-fx)*fabs(a-fx)))
			);
        }
	} else {
		out=m/2*(
			-log((sqrt(pow(b-fy,2)+pow(a-fx,2)+pow(fz-c,2))-(a-fx))/(sqrt(pow(b-fy,2)+pow(a-fx,2)+pow(fz-c,2))+(a-fx)))
			+log((sqrt(pow(b-fy,2)+pow(a-fx,2)+pow(fz-0,2))-(a-fx))/(sqrt(pow(b-fy,2)+pow(a-fx,2)+pow(fz-0,2))+(a-fx)))

			-log((sqrt(pow(b-fy,2)+pow(fx,2)+pow(fz-c,2))-fx)/(sqrt(pow(b-fy,2)+pow(fx,2)+pow(fz-c,2))+fx))
			+log((sqrt(pow(b-fy,2)+pow(fx,2)+pow(fz-0,2))-fx)/(sqrt(pow(b-fy,2)+pow(fx,2)+pow(fz-0,2))+fx))

			+log((sqrt(pow(fy,2)+pow(a-fx,2)+pow(fz-c,2))-(a-fx))/(sqrt(pow(fy,2)+pow(a-fx,2)+pow(fz-c,2))+(a-fx)))
			-log((sqrt(pow(fy,2)+pow(a-fx,2)+pow(fz-0,2))-(a-fx))/(sqrt(pow(fy,2)+pow(a-fx,2)+pow(fz-0,2))+(a-fx)))

			+log((sqrt(pow(fy,2)+pow(fx,2)+pow(fz-c,2))-fx)/(sqrt(pow(fy,2)+pow(fx,2)+pow(fz-c,2))+fx))
			-log((sqrt(pow(fy,2)+pow(fx,2)+pow(fz-0,2))-fx)/(sqrt(pow(fy,2)+pow(fx,2)+pow(fz-0,2))+fx))
		);
    }
	return(out);
}

double MzHz(double m, double a, double b, double c, double x, double y, double z, double fx, double fy, double fz)
{
	double out;
	fx=fx-x+a/2;
	fy=fy-y+b/2;
	fz=fz-z+c/2;
	out=m*(-P(b-fy,a-fx,fz,c)-P(fy,a-fx,fz,c)-P(a-fx,b-fy,fz,c)-P(fx,b-fy,fz,c)-P(b-fy,fx,fz,c)-P(fy,fx,fz,c)-P(a-fx,fy,fz,c)-P(fx,fy,fz,c));
	return(out);
}

double MxHx(double m, double a, double b, double c, double x, double y, double z, double fx, double fy, double fz)
{
	double out;
	/* 转换关系
	x' -> y
	y' -> z
    z' -> x
	-------- */
	out=MzHz(m,b,c,a,y,z,x,fy,fz,fx);
	return(out);
}

double MxHy(double m, double a, double b, double c, double x, double y, double z, double fx, double fy, double fz)
{
	double out;
	/* 转换关系
	x' -> y
	y' -> z
	z' -> x
	-------- */
	out=MzHx(m,b,c,a,y,z,x,fy,fz,fx);
	return(out);
}

double MxHz(double m, double a, double b, double c, double x, double y, double z, double fx, double fy, double fz)
{
	double out;
    /* 转换关系
	x' -> y
	y' -> z
	z' -> x
	-------- */
	out=MzHy(m,b,c,a,y,z,x,fy,fz,fx);
	return(out);
}

double MyHx(double m, double a, double b, double c, double x, double y, double z, double fx, double fy, double fz)
{
	double out;
    /* 转换关系
	x' -> z
	y' -> x
	z' -> y
	-------- */
	out=MzHy(m,c,a,b,z,x,y,fz,fx,fy);
	return(out);
}

double MyHy(double m, double a, double b, double c, double x, double y, double z, double fx, double fy, double fz)
{
	double out;
    /* 转换关系
	x' -> z
	y' -> x
	z' -> y
	-------- */
	out=MzHz(m,c,a,b,z,x,y,fz,fx,fy);
	return(out);
}

double MyHz(double m, double a, double b, double c, double x, double y, double z, double fx, double fy, double fz)
{
	double out;
    /* 转换关系
	x' -> z
	y' -> x
	z' -> y
	-------- */
	out=MzHx(m,c,a,b,z,x,y,fz,fx,fy);
	return(out);
}

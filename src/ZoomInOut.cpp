//
// Created by ztftrue on 17-11-5.
//

#include "ZoomInOut.h"
#include <stdio.h>

ZoomInOut::ZoomInOut(int a) {
	ZoomInOut::a = a;
	printf("%d", a);
}

ZoomInOut::~ZoomInOut() {
}

void ZoomInOut::Method(Mat src) {
	printf("\n Zoom In-Out demo  \n ");
	printf("------------------ \n");
	printf(" * [u] -> Zoom in  \n");
	printf(" * [d] -> Zoom out \n");
	printf(" * [ESC] -> Close program \n \n");
	src = imread("picture.jpg"); // Loads the test image
	if (src.empty()) {
		printf(" No data! -- Exiting the program \n");
		exit(-1);
	}
	tmp = src;
	dst = tmp;
	imshow(window_name, dst);
	for (;;) {
		char c = (char) waitKey(0);
		if (c == 27) {
			break;
		}
		if (c == 'u') {
			pyrUp(tmp, dst, Size(tmp.cols * 2, tmp.rows * 2));
			printf("** Zoom In: Image x 2 \n");
		} else if (c == 'd') {
			pyrDown(tmp, dst, Size(tmp.cols / 2, tmp.rows / 2));
			printf("** Zoom Out: Image / 2 \n");
		}
		imshow(window_name, dst);
		tmp = dst;
	}
}


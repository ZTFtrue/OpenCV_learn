#include <iostream>
#include <gtk/gtk.h>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/imgproc.hpp>

#include "src/Lesson1AboutMat.h"
#include "src/Lesson2OperationsImages.h"
#include "src/LessonAFeaturesFramework.h"
#include "src/LessonA2FeaturesFramework.h"
#include "src/TemplateMatching.h"

using namespace std;
using namespace cv;

static void helloWorld(GtkWidget *wid, GtkWidget *win) {
	GtkWidget *dialog = NULL;
	dialog = gtk_message_dialog_new(GTK_WINDOW(win), GTK_DIALOG_MODAL,
			GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "Hello World!");
	gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}
static void showImage(GtkWidget *wid, GtkWidget *win) {
	// https://docs.opencv.org/master/d4/da8/group__imgcodecs.html#ga288b8b3da0892bd651fce07b3bbd3a56
	// 该函数通过内容而不是文件扩展名确定图像的类型
	// 标志 https://docs.opencv.org/master/d4/da8/group__imgcodecs.html#ga61d9b0126a3e57d9277ac48327799c80
	Mat img = imread("assets/a.jpg", cv::IMREAD_REDUCED_GRAYSCALE_8); // Loads the test image
	imwrite("output/abc1.jpg",img);
	cv: imshow("Hello World", img);
	Mat img2 = imread("assets/a.jpg", cv::IMREAD_UNCHANGED); // Loads the test image
	imshow("output/image2.png", img2);
	waitKey(0);
}
/**
 * How to scan images, lookup tables and time measurement with OpenCV
 * 裁剪绘制图像，画线
 * 使用cv :: imdecode和cv :: imencode从/向内存而不是文件读取和写入图像。
 *
 * AboutMat 包括 打印 遍历mat 保存图片
 * cvtColor( image, gray_image, COLOR_BGR2GRAY );
 * https://docs.opencv.org/4.0.1/db/da5/tutorial_how_to_scan_images.html
 */
static void lesson1_operatingMat(GtkWidget *wid, GtkWidget *win) {
	Lesson1AboutMat lesson1AboutMat;
	lesson1AboutMat.operatingMat();
}

static void sharpenFilter2d(GtkWidget *wid, GtkWidget *win) {
	Lesson2OperationsImages lesson2OperationsImages;
//	lesson2OperationsImages.sharpen();
//	lesson2OperationsImages.myFilter2d();
//	lesson2OperationsImages.acessingPixelIntensity();
//	lesson2OperationsImages.addBlendingImag();
//	lesson2OperationsImages.changingBrightness();
	lesson2OperationsImages.discreteFourierTransform();
}

static void featuresFramework2D(GtkWidget *wid, GtkWidget *win) {
	LessonAFeaturesFramework lesson;
	/*哈里斯角落探测器*/
//	lesson.harrisCornerDetector();
	/*Shi-Tomasi corner detector*/
//	lesson.shiTomasiCornerDetector();
	/*创建自己的角落探测器*/
//	lesson.yourOwnCornerDetector();
	/* surf*/
//	lesson.features2dDetection();
	LessonA2FeaturesFramework lessonA2;
	lessonA2.AKAZEandORBplanar();
//	lessonA2.AKAZEmatching();
}

static void TemplateMatch(GtkWidget *wid, GtkWidget *win) {
	TemplateMatching templateMatching;
	templateMatching.matching();
}

int main(int argc, char **argv) {


	GtkWidget *button = NULL;
	GtkWidget *win = NULL;
	GtkWidget *vbox = NULL;

	/* Initialize GTK+ */
	g_log_set_handler("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
	gtk_init(&argc, &argv);
	g_log_set_handler("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);

	/* Create the main window */
	win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_container_set_border_width(GTK_CONTAINER(win), 8);
	gtk_window_set_title(GTK_WINDOW(win), "Hello World");
	gtk_window_set_position(GTK_WINDOW(win), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(win), 300, 400); // 设置窗口大小

	gtk_widget_realize(win);
	g_signal_connect(win, "destroy", gtk_main_quit, NULL);

	/* Create a vertical box with buttons */
	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
	gtk_container_add(GTK_CONTAINER(win), vbox);

	button = gtk_button_new_with_label(GTK_STOCK_DIALOG_INFO);
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(helloWorld),
			(gpointer ) win);
	gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);

	button = gtk_button_new_with_label("显示图片");
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(showImage),
			(gpointer ) win);
	gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);

	button = gtk_button_new_with_label("操作图片，AboutMat");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(lesson1_operatingMat), (gpointer ) win);
	gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);

	button = gtk_button_new_with_label("Sharpen，AboutMat");
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(sharpenFilter2d),
			(gpointer ) win);
	gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);

	button = gtk_button_new_with_label("特征点检查");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(featuresFramework2D), (gpointer ) win);
	gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);

	button = gtk_button_new_with_label("模板匹配");
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(TemplateMatch),
			(gpointer ) win);
	gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);

	button = gtk_button_new_with_label(GTK_STOCK_CLOSE);
	g_signal_connect(button, "clicked", gtk_main_quit, NULL);
	gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);

	/* Enter the main loop */
	gtk_widget_show_all(win);
	gtk_main();

	return 0;
}

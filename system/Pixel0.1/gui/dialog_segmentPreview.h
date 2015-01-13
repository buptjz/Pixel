#ifndef DIALOG_SEGMENTPREVIEW_H
#define DIALOG_SEGMENTPREVIEW_H

#include <QWidget>
#include "ui_dialog_segmentPreview.h"
#include <originalImage.h>

class DialogSegmentPreview : public QWidget
{
	Q_OBJECT

public:
	DialogSegmentPreview(QWidget *parent = 0);
	~DialogSegmentPreview();

	Ui::DialogSegmentPreview ui;

	int expectedPatchesNum;
	static int connect_num;

	OriginalImage *segmentImage;
	vector<ImagePatch*> *segementedImagePatches = NULL;
	void setSegmentImage(OriginalImage* ori);
	void segmentImageForPreview(string segment_type);

signals:
	void sig(int);
public slots :
	void on_previewSegmentImageBtn_clicked();
	void on_oKSegmentPreviewImageBtn_clicked();
	
	
};


#endif

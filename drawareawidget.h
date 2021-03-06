﻿#ifndef DRAWAREAWIDGET_H
#define DRAWAREAWIDGET_H
 
#include <QWidget>
#include <QPainter>
 
#include "generalshape.h"
#include"facetool.h"
#include "curve.h"
#include "closecurve.h"
#include "circle.h"
#include "polyline.h"
#include "polygon.h"
#include "rect.h"
#include "ellipse.h"
#include "text.h"
#include <QList>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QScrollArea>
#include <QScrollBar>
#include "combo.h"
#include "addaction.h"
#include "deleteaction.h"
#include "editaction.h"
#include "combineaction.h"
#include "divideaction.h"
#include "topaction.h"
#include "bottomaction.h"
#include "setbrushaction.h"
#include"texteditaction.h"
#include"slightmoveaction.h"
#include <memory>
#include<QtPrintSupport/QPrinter>
#include<QtPrintSupport/QPrintDialog>
#include <QPrintPreviewDialog>
#include"codeeditdlg.h"
#include"setpenaction.h"
#include"hlineedit.h"
#include"mywidget.h"
#include"rotatewidget.h"
#include"curvelineinstrument.h"

enum MouseHanded {None, RotationPoint,ScalePoint};
enum Category {CurveCategory,CloseCurveCategory, PolylineCategory,PolygonCategory,PickCategory,CircleCategory,
               RectCategory,EllipseCategory,TextCategory,PalmCategory,ToolCategory};//Line, Rect, Text,
class AbstractInstrument;

class DrawAreaWidget : public QWidget
{
    Q_OBJECT
public:
    void setTool(Tool* tool);
    explicit DrawAreaWidget(QWidget *parent = 0);
    ~DrawAreaWidget();
    void init();
    void setCategory(Category c);
    void finishcurrentShape();
    QList<shared_ptr<GeneralShape>>  pickShape(QPointF point);
    QList<shared_ptr<GeneralShape>>  pickShape(QPointF p0, QPointF p1);
    //void  expand(QPoint point);
    void expand();
    void fitcanvas();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    //bool event(QEvent *event);
    bool inRange(QPointF Point,QList<shared_ptr<GeneralShape>> sps);

    void del(shared_ptr<GeneralShape> sp);
    //void pickedMove(qreal x,qreal y);
    void save();
    void saveAs();
    void open();
    //void add(QString line);
    void addfile();
    void opennew();
    bool maybeSave();
    void addshape(shared_ptr<GeneralShape> shape);
    void zoom(double ratio);
    //void rotate();
    bool isRotationHandlePoint(QPointF realPoint,shared_ptr<GeneralShape> pickedShape);
    bool isScaleHandlePoint(QPointF realPoint,shared_ptr<GeneralShape> pickedShape);
//    void openOldFileFormat();
//    void openold();
    void zoomone();
    void dozoom();
    void undo();
    void redo();
    void addaction(AbstractAction* act);
    void addaction(QList<AbstractAction*> alist);
    void openfile(QString file);

    void copyPaste();
    QList<shared_ptr<GeneralShape>> copy();
    QList<shared_ptr<GeneralShape>> cut();
    void paste(QList<shared_ptr<GeneralShape>> *copyShapes);
    void combination();
    void divide();
    void divide(shared_ptr<GeneralShape> shape);
    void divideToEnd();
    void divideToEnd(shared_ptr<GeneralShape> shape);
    void test();
    void print();
    void printPreview();
    shared_ptr<GeneralShape> newShape(Category c);
//    void getOutOfCombo(shared_ptr<GeneralShape> sp, shared_ptr<Combo> tmp);
//    void getIntoCombo(shared_ptr<GeneralShape> sp,shared_ptr<Combo> tmp);

    //void closeEvent(QCloseEvent *event);

    QScrollBar *hBar, *vBar;
    qreal zoomRatio,previouszoomRatio;
    double windowwidth,windowheight;
    //QList <AbstractAction*> actionList;
    //int actionindex;
    void setBrush(shared_ptr<GeneralShape> sp);
    QString filename;
    QUndoStack undoStack;

//private:
    static int numOfFiles;


public slots:
    void moveToTop();
    void moveToBottom();
    void setBrush();
    void setPen();
    void setPen(shared_ptr<GeneralShape> sp);
    void editText();
    void onPaintRequested(QPrinter* printer);
    void codeEdit();
    void contextMenuEvent( QContextMenuEvent * event );
    void currentTextChanged(QString text);
protected:
    void paintEvent(QPaintEvent *);
    //void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    //void clicke
    void leaveEvent(QEvent *event);
    void rightMousePressEvent(QMouseEvent *event);
signals:
    void categoryChanged();
    void statusChanged();
    void mouseMoved(QMouseEvent *event,QPointF realPoint);
    void mouseLeave();
     

public:
    QList<shared_ptr<GeneralShape> > shapes;
    shared_ptr<GeneralShape> currentShape;
    shared_ptr<Rect> pickRect;
    QList<shared_ptr<GeneralShape>> pickedShapes;
    QPointF startPoint,endPoint;
    QPoint startCursorPoint,endCursorPoint;
    Category currentCategory;
    Tool* currentTool;
    MouseHanded currentMouseHanded;
    bool isLeftMouseButtonPressed;
    int dx,dy;//坐标原点的画布位置
    //bool isScrolling;

    bool saved;
    bool openasadd;
    //bool changed;
    int saveIndex;
    qreal pickedShapestartsx,pickedShapestartsy;
    qreal pickedShapestartRotationangle;
    QColor backcolor;
    QAction*  actionMoveToTop;
    QAction* actionMoveToBottom;
    QAction* actionSetBrush,*actionEditText,*actionCodeEdit;
    QAction* actionSetPen;
    MyLineEdit* currentLine;
    RotateWidget* currentRotateLine;
    shared_ptr<Text> currentText;
    QSize realSize;
    QPoint realDp;
    bool needKeyboard;
    AbstractInstrument *mInstrumentHandler;
    //Combo* root;
};
 
#endif // DRAWAREAWIDGET_H

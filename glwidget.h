#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QGLShader>
#include <QTimer>
#include <QOpenGLVertexArrayObject>

#include "field.h"
#include "Player.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    QSize minimumSizeHint() const;
    QSize sizeHint() const;

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int, int) override;
    void keyPressEvent(QKeyEvent * event) override;
    void initTextures();
private:
    QMatrix4x4 projection;
    QMatrix4x4 view;
    QMatrix4x4 model;

    QTimer timer;

    GLuint texture;

    QGLShaderProgram * currentShader = nullptr;

    void loadShaderProgram(QGLShaderProgram * program, QString name);

    field mapField;
    player p;
};

#endif // GLWIDGET_H

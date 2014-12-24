#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QGLShader>
#include <QTimer>
#include <QOpenGLVertexArrayObject>
#include <QGLFunctions>

#include "Field.h"
#include "Player.h"

class GLWidget : public QGLWidget, protected QGLFunctions
{
    Q_OBJECT
public:
    explicit GLWidget(Field field, Player player, QWidget *parent = 0);
    QSize minimumSizeHint() const;
    QSize sizeHint() const;

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int, int) override;
    void keyPressEvent(QKeyEvent * event) override;
    void initTextures();
private:
    struct VertexData{
        QVector2D vertex;
        QVector2D textureCoord;
    };

    QMatrix4x4 projection;
    QMatrix4x4 view;
    QMatrix4x4 model;

    QTimer timer;

    GLuint texture[2];

    QGLShaderProgram * currentShader = nullptr;

    void loadShaderProgram(QGLShaderProgram * program, QString name);

    Field mapField;
    Player p;

    void paintMap();

    void paintPlayer();

    void initShaders();
};

#endif // GLWIDGET_H

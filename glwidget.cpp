#include <QtOpenGL>
#include <QFileInfo>
#include <QGLBuffer>
#include <QGLFunctions>
#include <math.h>

#include <fstream>
#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent):
    QGLWidget(parent),
    timer(this)
{
    timer.setSingleShot(false);
    std::ifstream map ("text_map.txt");
    mapField.read_field_from_file(map);
    p.initialize_coordinates(map);
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(500, 500);
}

QSize GLWidget::sizeHint() const
{
    return QSize(700, 700);
}

void GLWidget::initializeGL()
{
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    initTextures();

    projection.perspective(30.0f, 1.0f, 0.1f, 100.0f);
    view.lookAt(QVector3D(0.0f, 0.0f, 50.0f), QVector3D(0, 0, 0), QVector3D(-1, 0, 0));

    currentShader = new QGLShaderProgram();
    loadShaderProgram(currentShader, "1");
    currentShader->bind();

}

void GLWidget::loadShaderProgram(QGLShaderProgram * program, QString name){
    QFileInfo vshFile(name + ".vsh");
    if(vshFile.exists()){
        if(!program->addShaderFromSourceFile(QGLShader::Vertex, name + ".vsh")){
            qDebug() << "Can't load vertex shader " + name +":"<< program->log();
            close();
        }
    } else{
        qDebug() << "Can't find vsh file.";
        close();
    }

    QFileInfo fshFile(name + ".fsh");
    if(fshFile.exists()){
        if(!program->addShaderFromSourceFile(QGLShader::Fragment, name + ".fsh")){
            qDebug() << "Can't load fragment shader " + name +":"<< program->log();
            close();
        }
    } else{
        qDebug() << "Can't find fsh file.";
        close();
    }

    if(!program->link()){
        qDebug() << program->log();
        close();
    }
}

void GLWidget::initTextures()
{

    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    texture = bindTexture(QImage(":/brickwork-texture.jpg"));
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{

}

void GLWidget::paintGL()
{
    glClearColor(0, 0, 0, 1.0f);
    glClearDepth(1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    currentShader->setUniformValue("mvp", projection * view * model);
    currentShader->setUniformValue("number_of_squares", mapField.size);

    float sizeOfSquare = 0.3;
    QGLBuffer buffer (QGLBuffer::VertexBuffer);
    std::vector<float> vertices(8 * mapField.number_of_walls);
    int walls_done = 0;
    for (int i = 0; i < mapField.size; ++i)
    {
        for (int j = 0; j < mapField.size; ++j)
        {
            if (mapField.read_value(i, j) == field::type_of_place::WALL)
            {
                vertices[walls_done] = i;
                walls_done++;
                vertices[walls_done] = j;
                walls_done++;
                vertices[walls_done] = i + 1;
                walls_done++;
                vertices[walls_done] = j;
                walls_done++;
                vertices[walls_done] = i + 1;
                walls_done++;
                vertices[walls_done] = j + 1;
                walls_done++;
                vertices[walls_done] = i;
                walls_done++;
                vertices[walls_done] = j + 1;
                walls_done++;
            }
        }
    }

    buffer.create();
    buffer.setUsagePattern(QGLBuffer::StaticDraw);
    buffer.bind();
    buffer.allocate(vertices.data(), vertices.size() * sizeof(float));

    currentShader->setAttributeBuffer("vertex", GL_FLOAT, 0, 2);
    currentShader->enableAttributeArray("vertex");
    glDrawArrays(GL_QUADS, 0, 8 * mapField.number_of_walls);
    buffer.release();
    currentShader->disableAttributeArray("vertex");
}


void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}















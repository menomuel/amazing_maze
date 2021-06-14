#include "cubewidget.h"

#include <QMouseEvent>
#include <QColor>

#include <QtMath>
#include <cmath>

void CubeWidget::showPath(bool state)
{
    //build path before showing
    if(state)
    {
        double fractPart, intPart;
        QVector3D pos = godModeFlag ? historyCameraPos : camera.getCameraPos();

        fractPart = modf(pos.x()/scene->getCube()->getFacetSideLength(), &intPart);
        int row = fractPart < 0.5 ? int(intPart) : int(intPart) + 1;
        fractPart = modf(-pos.z()/scene->getCube()->getFacetSideLength(), &intPart);
        int col = fractPart < 0.5 ? int(intPart) : int(intPart) + 1;

        int row_to = scene->getFinish().row;
        int col_to = scene->getFinish().col;


        scene->setPath(PathFinder::findPath(scene->getData(), row, col, row_to, col_to));
    }

    scene->setShowPathFlag(state);

}

void CubeWidget::godMode(bool state)
{
    godModeFlag = state;

    if (godModeFlag)
    {
        historyCameraPos = camera.getCameraPos();
        historyCameraFront = camera.getCameraFront();
        historyCameraUp = camera.getCameraUp();
        historyYaw = camera.getYaw();
        historyPitch = camera.getPitch();
    } else
    {
        camera.setCameraPos(historyCameraPos);
        camera.setCameraFront(historyCameraFront);
        camera.setCameraUp(historyCameraUp);
        camera.setYaw(historyYaw);
        camera.setPitch(historyPitch);
    }
}

void CubeWidget::restartScene()
{
    scene->reload();
    scene->setShowPathFlag(false);
    godModeFlag = false;
    winFlag = false;
    winMusicFlag = false;

    player->stop();
    movie->stop();
    emit clearWinMovie();

    emit setShowPathFlag(false);
    emit setGodModeFlag(false);

    camera.setCameraPos(QVector3D(scene->getCube()->getFacetSideLength(), 0, -scene->getCube()->getFacetSideLength()));
    camera.setCameraFront({0.f, 0.f, -1.f});
    camera.setCameraUp({0.f, 1.f, 0.f});
    camera.setYaw(- M_PI / 2);
    camera.setPitch(0.f);
    historyCameraPos = camera.getCameraPos();
    historyCameraFront = camera.getCameraFront();
    historyCameraUp = camera.getCameraUp();
    historyYaw = camera.getYaw();
    historyPitch = camera.getPitch();

    timeRecord.restart();
}

void CubeWidget::resizeScene(int newSize)
{
    scene->init(newSize, std::time(nullptr));
    restartScene();
}

void CubeWidget::collisionDetection(int currRow, int currCol)
{
    auto maze = scene->getData();
    float side = scene->getCube()->getFacetSideLength();
    float walkingZone = side * 0.4;

    auto currPos = camera.getCameraPos();

    if(maze[currRow+1][currCol].cellType == WALL && currPos.x() > side * currRow + walkingZone)
        camera.setCameraPos(QVector3D(side * currRow + walkingZone, currPos.y(), currPos.z()));

    if(maze[currRow-1][currCol].cellType == WALL && currPos.x() < side * currRow - walkingZone)
        camera.setCameraPos(QVector3D(side * currRow - walkingZone, currPos.y(), currPos.z()));

    currPos = camera.getCameraPos();
    if(maze[currRow][currCol+1].cellType == WALL && currPos.z() < -side * currCol - walkingZone)
        camera.setCameraPos(QVector3D(currPos.x(), currPos.y(), -side * currCol - walkingZone));

    if(maze[currRow][currCol-1].cellType == WALL && currPos.z() > -side * currCol + walkingZone)
        camera.setCameraPos(QVector3D(currPos.x(), currPos.y(), -side * currCol + walkingZone));

}


void CubeWidget::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());

    if (e->buttons() & Qt::RightButton)
    {
        mouseLastPosition = QVector2D(e->pos());
    }
}

void CubeWidget::mouseReleaseEvent(QMouseEvent *e)
{
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;
}

void CubeWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() & Qt::RightButton)
    {
        QVector2D diff = QVector2D(e->pos()) - mouseLastPosition;
        diff *= 0.002f;
        camera.rotate(diff.x(), diff.y());
    }
    mouseLastPosition = QVector2D(e->pos());
}

void CubeWidget::timerEvent(QTimerEvent *)
{
    doMovement();
    update();

    if(!winFlag)
    {
        auto secElapsed = static_cast<int>(timeRecord.elapsed() / 1000);
        emit secsElapsed(secElapsed % 60);
        emit minsElapsed(secElapsed / 60);
    }  else if (!winMusicFlag)
    {
        movie->start();
        emit setWinMovie(movie.get());

        if(player->state() == QMediaPlayer::PlayingState)
            player->setPosition(0);
        else if(player->state() == QMediaPlayer::StoppedState)
            player->play();
        winMusicFlag = true;
    }
}

void CubeWidget::keyPressEvent(QKeyEvent *e)
{
    if(e->key() < 1024)
        keys[e->key()] = true;
}

void CubeWidget::keyReleaseEvent(QKeyEvent *e)
{
    if(e->key() < 1024)
        keys[e->key()] = false;
}

void CubeWidget::wheelEvent(QWheelEvent *e)
{
    fov += e->angleDelta().y() / 45.f;
}

void CubeWidget::doMovement()
{
    float length = cameraSpeed * deltaTimeMsec / 1000.f;

    if (keys[Qt::Key_W])
        camera.move(Camera::directions::FORWARD, length);
    if (keys[Qt::Key_S])
        camera.move(Camera::directions::BACKWARD, length);
    if (keys[Qt::Key_D])
        camera.move(Camera::directions::RIGHT, length);
    if (keys[Qt::Key_A])
        camera.move(Camera::directions::LEFT, length);
    if (keys[Qt::Key_Space])
        camera.move(Camera::directions::UP, length);
    if (keys[Qt::Key_Z])
        camera.move(Camera::directions::DOWN, length);

    double fractPart, intPart;
    fractPart = modf(camera.getCameraPos().x()/scene->getCube()->getFacetSideLength(), &intPart);
    int row = fractPart < 0.5 ? int(intPart) : int(intPart) + 1;

    fractPart = modf(-camera.getCameraPos().z()/scene->getCube()->getFacetSideLength(), &intPart);
    int col = fractPart < 0.5 ? int(intPart) : int(intPart) + 1;

    if(!godModeFlag)
    {
        camera.setCameraPos(QVector3D{camera.getCameraPos().x(), 0, camera.getCameraPos().z()});
        collisionDetection(row, col);
        scene->update(row, col);
        if (scene->getFinish().row == row && scene->getFinish().col == col)
            winFlag = true;
    }

}


void CubeWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.f, 0.f, 0.f, 1.f);

    initShaders();

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);

    scene = std::make_shared<Scene>();
    scene->init();

    arrow = std::make_shared<Arrow>();
    arrowTex = Texture::loadTexture(R"(:/textures/arrow.jpg)");

    camera.setZNear(zNear);
    camera.setZFar(zFar);
    camera.setCameraPos(QVector3D(scene->getCube()->getFacetSideLength(), 0, -scene->getCube()->getFacetSideLength()));

    player = std::make_shared<QMediaPlayer>();
    player->setMedia(QUrl("qrc:/sounds/win_theme.mp3"));
    movie = std::make_shared<QMovie>(R"(:/animation/win.gif)");

    glActiveTexture(GL_TEXTURE0);

    n = 0;
    // Use QBasicTimer because its faster than QTimer
    timer.start(deltaTimeMsec, this);
    timeRecord.start();
}

//! [3]
void CubeWidget::initShaders()
{
    // Compile vertex shader for objects
    if (!objectShader.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader for objects
    if (!objectShader.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!objectShader.link())
        close();

    // Bind shader pipeline for use
    if (!objectShader.bind())
        close();
}


void CubeWidget::resizeGL(int w, int h)
{
    camera.setAspectRatio(float(w) / float(h ? h : 1));
}


void CubeWidget::paintGL()
{
    auto start = stopwatch.currentTime();

    // Clear color and depth buffer
    glClearColor(127.0f/255, 199.0f/255, 255.0f/255, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    objectShader.bind();

    if(godModeFlag)
    {
        QMatrix4x4 mat;
        mat.translate(historyCameraPos);

        auto a = QVector3D{0.f, 0.f, -1.f};
        a.normalize();
        auto b = QVector3D{historyCameraFront.x(), 0.f, historyCameraFront.z()};
        b.normalize();

        auto dir = QVector3D::crossProduct(a, b);

        auto angle = qRadiansToDegrees(qAcos(QVector3D::dotProduct(a, b)));
        angle = dir.y() < 0 ? angle : -angle;

        mat.rotate(-angle, QVector3D{0.f, 1.f, 0.f});

        objectShader.setUniformValue(0, mat);
        arrowTex->bind();
        arrow->render(&objectShader);
    }

    camera.setFOV(fov);

    objectShader.bind();
    objectShader.setUniformValue(1, camera.getViewMatrix());
    objectShader.setUniformValue(2, camera.getProjectionMatrix());
    objectShader.setUniformValue(3, camera.getCameraPos());

    glActiveTexture(GL_TEXTURE0);

    // Draw cube geometry
    scene->drawScene(&objectShader);

    auto stop = stopwatch.currentTime();

    fps += 1.f / (start.msecsTo(stop));
    ++n;
    if (n >= 100) {
        n = 0;
        emit fpsChanged(static_cast<double>(1000 * fps / 100));
        fps = 0;
    }
}

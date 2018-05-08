#ifndef _GL_WIDGET_H
#define _GL_WIDGET_H 

#include <QOpenGLWidget> 
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QMatrix4x4>
#include <memory> 

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram);  

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
	Q_OBJECT

public:
	GLWidget(QWidget* parent = Q_NULLPTR);
	~GLWidget();

	void setClearColor(const QColor &color);
	void setFrameData(QOpenGLTexture::PixelFormat sourceFormat,
		QOpenGLTexture::PixelType sourceType, const void *data, int width, int height);

signals:
	void overlayChanged(const QString& overlayId, const QRect& rect);

protected:
	void initializeGL() Q_DECL_OVERRIDE;
	void paintGL() Q_DECL_OVERRIDE;
	void resizeGL(int width, int height) Q_DECL_OVERRIDE;

private:
	void makeObject();
	void createTexture(int width = 256, int height = 256);

private:
	QColor clearColor;
	QOpenGLTexture* texture;
	QOpenGLShaderProgram* program;
	QOpenGLBuffer vbo;
	QMatrix4x4 mModelView;
};
	 

#endif  // _GL_WIDGET_H

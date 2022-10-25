#include "OpenGLGraphics.h"
#include "gl/gl.h"
#include "gl/glu.h"
#include <strsafe.h>
int OpenGLGraphics::OpenGLInit(const HWND hWnd, const int width, const int height)
{
    m_DeviceContext = GetDC(hWnd);

    PIXELFORMATDESCRIPTOR pfDesc = { sizeof(PIXELFORMATDESCRIPTOR),   // size of this pfd 
            1,                     // version number 
            PFD_DRAW_TO_WINDOW |   // support window 
            PFD_SUPPORT_OPENGL |   // support OpenGL 
            PFD_DOUBLEBUFFER,      // double buffered 
            PFD_TYPE_RGBA,         // RGBA type 
            24,                    // 24-bit color depth 
            0, 0, 0, 0, 0, 0,      // color bits ignored 
            0,                     // no alpha buffer 
            0,                     // shift bit ignored 
            0,                     // no accumulation buffer 
            0, 0, 0, 0,            // accum bits ignored 
            32,                    // 32-bit z-buffer 
            0,                     // no stencil buffer 
            0,                     // no auxiliary buffer 
            PFD_MAIN_PLANE,        // main layer 
            0,                     // reserved 
            0, 0, 0 };              // layer masks ignored 

    int pixelformat = ChoosePixelFormat(m_DeviceContext, &pfDesc);
    if (pixelformat == 0)
    {
        return -1;
    }

    if (!SetPixelFormat(m_DeviceContext, pixelformat, &pfDesc))
    {
        return -1;
    }
    m_RenderingContext = wglCreateContext(m_DeviceContext);
    wglMakeCurrent(m_DeviceContext, m_RenderingContext);

    // 深度バッファ
    glEnable(GL_DEPTH_TEST);		// 深度テストON
    glDepthFunc(GL_LEQUAL);			// Z値がバッファの値、以下であれば上書き

    // ビューポートの設定
    glViewport(0, 0, width, height);



    glDisable(GL_STENCIL_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    return 0;
}

int OpenGLGraphics::OpenGLBeforeRender()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    return 0;
}

int OpenGLGraphics::OpenGLAfterRender()
{
    glFlush();				// コマンドのフラッシュ
    SwapBuffers(m_DeviceContext);
    return 0;
}

void OpenGLGraphics::CreateInstance()
{
    DeleteInstance();

    s_pInstance = new OpenGLGraphics();
}

void OpenGLGraphics::DeleteInstance()
{
    if (s_pInstance != nullptr)
    {
        delete s_pInstance;
        s_pInstance = nullptr;
    }
}

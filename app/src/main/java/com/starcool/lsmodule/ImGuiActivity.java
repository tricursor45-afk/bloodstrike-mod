package com.starcool.lsmodule;

import android.app.Activity;
import android.os.Bundle;
import android.opengl.GLSurfaceView;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class ImGuiActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        GLSurfaceView glView = new GLSurfaceView(this);
        glView.setEGLContextClientVersion(2);

        glView.setRenderer(new GLSurfaceView.Renderer() {
				@Override
				public void onSurfaceCreated(GL10 gl, EGLConfig config) {
					try {
						System.loadLibrary("star"); // libstar dari module
					} catch (UnsatisfiedLinkError e) {
						e.printStackTrace();
					}
					initImGui();
				}

				@Override
				public void onSurfaceChanged(GL10 gl, int width, int height) {}

				@Override
				public void onDrawFrame(GL10 gl) {
					renderImGui();
				}
			});

        setContentView(glView);
    }

    private native void initImGui();
    private native void renderImGui();
}

package com.starcool.lsmodule;

import android.app.Activity;
import android.os.Bundle;
import android.opengl.GLSurfaceView;
import android.widget.Toast;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class StandaloneImGuiActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        GLSurfaceView glView = new GLSurfaceView(this);

        try {
            glView.setEGLContextClientVersion(2);

            glView.setRenderer(new GLSurfaceView.Renderer() {
					@Override
					public void onSurfaceCreated(GL10 gl, EGLConfig config) {
						try {
							System.loadLibrary("star"); // pastikan libstar.so ada di module
						} catch (UnsatisfiedLinkError e) {
							e.printStackTrace();
							Toast.makeText(StandaloneImGuiActivity.this,
										   "Gagal load libstar.so", Toast.LENGTH_SHORT).show();
							finish();
							return;
						}

						try {
							initImGui();
						} catch (Exception e) {
							e.printStackTrace();
							Toast.makeText(StandaloneImGuiActivity.this,
										   "Gagal init ImGui", Toast.LENGTH_SHORT).show();
							finish();
						}
					}

					@Override
					public void onSurfaceChanged(GL10 gl, int width, int height) {}

					@Override
					public void onDrawFrame(GL10 gl) {
						try {
							renderImGui();
						} catch (Exception e) {
							e.printStackTrace();
						}
					}
				});

            setContentView(glView);
        } catch (Exception e) {
            e.printStackTrace();
            Toast.makeText(this, "Gagal buat GLSurfaceView", Toast.LENGTH_SHORT).show();
            finish();
        }
    }

    private native void initImGui();
    private native void renderImGui();
}

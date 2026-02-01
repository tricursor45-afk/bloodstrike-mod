

/*


package com.starcool.lsmodule;

import android.app.Application;
import android.content.Context;

import de.robv.android.xposed.IXposedHookLoadPackage;
import de.robv.android.xposed.XposedBridge;
import de.robv.android.xposed.XposedHelpers;
import de.robv.android.xposed.callbacks.XC_LoadPackage;

public class HookEntry implements IXposedHookLoadPackage {

    private static final String TARGET_GAME = "com.tencent.stc.cfl";

    @Override
    public void handleLoadPackage(XC_LoadPackage.LoadPackageParam lpparam) throws Throwable {

        if (!lpparam.packageName.equals(TARGET_GAME))
            return;

        XposedBridge.log("LSPosed -> Game Loaded");

        // Hook Application.attach (INI PALING STABIL)
        XposedHelpers.findAndHookMethod(
			Application.class,
			"attach",
			Context.class,
			new de.robv.android.xposed.XC_MethodHook() {
				@Override
				protected void afterHookedMethod(MethodHookParam param) {
					Context ctx = (Context) param.args[0];

					try {
						// Load lib dari APK module
						String libPath = ctx.getApplicationInfo().nativeLibraryDir + "/libstar.so";
						System.load(libPath);

						XposedBridge.log("Inject lib success: " + libPath);
					} catch (Throwable t) {
						XposedBridge.log("Inject lib failed: " + t);
					}
				}
			}
        );
    }
}


*/
package com.starcool.lsmodule;

import android.app.Application;
import android.content.Context;

import de.robv.android.xposed.IXposedHookLoadPackage;
import de.robv.android.xposed.XC_MethodHook;
import de.robv.android.xposed.XposedBridge;
import de.robv.android.xposed.XposedHelpers;
import de.robv.android.xposed.callbacks.XC_LoadPackage;

public class HookEntry implements IXposedHookLoadPackage {

    private static final String TARGET_GAME = "com.netease.newspike";
    private static final String MODULE_PKG  = "com.starcool.lsmodule";

    @Override
    public void handleLoadPackage(XC_LoadPackage.LoadPackageParam lpparam) throws Throwable {

        if (!lpparam.packageName.equals(TARGET_GAME))
            return;

        XposedBridge.log("LSPosed -> Target Game Loaded");

        XposedHelpers.findAndHookMethod(
			Application.class,
			"attach",
			Context.class,
			new XC_MethodHook() {

				@Override
				protected void afterHookedMethod(MethodHookParam param) {

					Context gameCtx = (Context) param.args[0];

					try {
						// Ambil context MODULE
						Context moduleCtx = gameCtx.createPackageContext(
							MODULE_PKG,
							Context.CONTEXT_IGNORE_SECURITY
						);

						// Path lib dari APK MODULE
						String libPath =
							moduleCtx.getApplicationInfo().nativeLibraryDir
							+ "/libstar.so";

						System.load(libPath);

						XposedBridge.log("Inject lib MODULE SUCCESS: " + libPath);

					} catch (Throwable t) {
						XposedBridge.log("Inject lib MODULE FAILED: " + t);
					}
				}
			}
        );
    }
}

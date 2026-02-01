package com.starcool.lsmodule;

import android.app.Activity;
import android.content.Intent;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.graphics.Color;
import android.graphics.drawable.Drawable;
import android.graphics.drawable.GradientDrawable;
import android.net.Uri;
import android.content.Intent;
import android.os.Bundle;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.View;         
import android.widget.Button;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;
import android.graphics.PorterDuff;

public class MainActivity extends Activity {

    private static final String TARGET_GAME = "com.netease.newspike";

    ImageView homeIcon;
    ImageView settingsIcon;
    LinearLayout topBar;
    Button btn;
    LinearLayout settingsMenu;

    private int dp(int v) {
        return (int) TypedValue.applyDimension(
			TypedValue.COMPLEX_UNIT_DIP,
			v,
			getResources().getDisplayMetrics());
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        PackageManager pm = getPackageManager();
        boolean installed = isInstalled(pm);
        String versionName = installed ? getVersion(pm) : "—";

        LinearLayout root = new LinearLayout(this);
        root.setOrientation(LinearLayout.VERTICAL);
        root.setBackgroundColor(Color.parseColor("#121212"));
        root.setPadding(24, 24, 24, 24);

        topBar = new LinearLayout(this);
        topBar.setOrientation(LinearLayout.VERTICAL);
        topBar.setPadding(32, 32, 32, 32);

        GradientDrawable barBg = new GradientDrawable();
        barBg.setColor(Color.parseColor("#1E1E1E"));
        barBg.setCornerRadius(32);
        topBar.setBackground(barBg);

        LinearLayout rowTop = new LinearLayout(this);
        rowTop.setOrientation(LinearLayout.HORIZONTAL);
        rowTop.setGravity(Gravity.CENTER_VERTICAL);

        ImageView logo = new ImageView(this);
        LinearLayout.LayoutParams logoLp = new LinearLayout.LayoutParams(96, 96);
        logoLp.setMarginEnd(24);
        logo.setLayoutParams(logoLp);

        try {
            ApplicationInfo appInfo = pm.getApplicationInfo(TARGET_GAME, 0);
            Drawable icon = pm.getApplicationIcon(appInfo);
            logo.setImageDrawable(icon);
        } catch (PackageManager.NameNotFoundException e) {
            logo.setImageResource(android.R.drawable.sym_def_app_icon);
        }

        TextView tvPkg = new TextView(this);
        tvPkg.setText(TARGET_GAME);
        tvPkg.setTextColor(Color.WHITE);
        tvPkg.setTextSize(TypedValue.COMPLEX_UNIT_SP, 14);
        tvPkg.setLayoutParams(new LinearLayout.LayoutParams(
								  0, LinearLayout.LayoutParams.WRAP_CONTENT, 1));

        TextView tvStatus = new TextView(this);
        tvStatus.setText(installed ? "INSTALLED" : "NOT INSTALLED");
        tvStatus.setTextColor(installed
							  ? Color.parseColor("#4CAF50")
							  : Color.parseColor("#F44336"));
        tvStatus.setTextSize(12);

        rowTop.addView(logo);
        rowTop.addView(tvPkg);
        rowTop.addView(tvStatus);

        TextView tvVersion = new TextView(this);
        tvVersion.setText("Version: " + versionName);
        tvVersion.setTextColor(Color.LTGRAY);
        tvVersion.setTextSize(12);
        tvVersion.setPadding(120, 12, 0, 0);

        topBar.addView(rowTop);
        topBar.addView(tvVersion);

        btn = new Button(this);
        btn.setText("START GAME");
        btn.setTextColor(Color.WHITE);
        btn.setAllCaps(false);

        GradientDrawable btnBg = new GradientDrawable();
        btnBg.setColor(Color.parseColor("#2E7DFF"));
        btnBg.setCornerRadius(48);
        btn.setBackground(btnBg);

        LinearLayout.LayoutParams btnLp = new LinearLayout.LayoutParams(
			LinearLayout.LayoutParams.MATCH_PARENT,
			LinearLayout.LayoutParams.WRAP_CONTENT);
        btnLp.setMargins(0, 48, 0, 0);
        btn.setLayoutParams(btnLp);

        btn.setOnClickListener(new View.OnClickListener() {
				@Override
				public void onClick(View v) {
					openGame();
				}
			});

		
			
        root.addView(topBar);
        root.addView(btn);

        settingsMenu = new LinearLayout(this);
		settingsMenu.setOrientation(LinearLayout.VERTICAL);
		settingsMenu.setVisibility(View.GONE);

		int iconSize = (int) TypedValue.applyDimension(
			TypedValue.COMPLEX_UNIT_DIP,
			96,
			getResources().getDisplayMetrics()
		);

		LinearLayout devBar = new LinearLayout(this);
		devBar.setOrientation(LinearLayout.HORIZONTAL);
		devBar.setGravity(Gravity.CENTER_VERTICAL);
		devBar.setPadding(32, 32, 32, 32);

		GradientDrawable devBg = new GradientDrawable();
		devBg.setColor(Color.parseColor("#1E1E1E"));
		devBg.setCornerRadius(32);
		devBar.setBackground(devBg);

// Icon Developer di res/drawable
		ImageView devIcon = new ImageView(this);
		LinearLayout.LayoutParams devIconLp = new LinearLayout.LayoutParams(iconSize, iconSize);
		devIconLp.setMarginEnd((int) TypedValue.applyDimension(
								   TypedValue.COMPLEX_UNIT_DIP, 24, getResources().getDisplayMetrics()
							   ));
		devIcon.setLayoutParams(devIconLp);
		devIcon.setImageResource(R.drawable.ic_developer);
		devIcon.setScaleType(ImageView.ScaleType.CENTER_INSIDE);

		LinearLayout devTextContainer = new LinearLayout(this);
		devTextContainer.setOrientation(LinearLayout.VERTICAL);

		TextView devTitle = new TextView(this);
		devTitle.setText("DEVELOPER");
		devTitle.setTextColor(Color.WHITE);
		devTitle.setTextSize(16);

		TextView devDesc = new TextView(this);
		devDesc.setText("@EXSTARCOOL");
		devDesc.setTextColor(Color.LTGRAY);
		devDesc.setTextSize(13);
		devDesc.setPadding(0, 8, 0, 0);

		devTextContainer.addView(devTitle);
		devTextContainer.addView(devDesc);

		devBar.addView(devIcon);
		devBar.addView(devTextContainer);

		settingsMenu.addView(devBar);

// === GRUP TELEGRAM ===
		LinearLayout tgGroupBar = new LinearLayout(this);
		tgGroupBar.setOrientation(LinearLayout.HORIZONTAL);
		tgGroupBar.setGravity(Gravity.CENTER_VERTICAL);
		tgGroupBar.setPadding(32, 32, 32, 32);

		GradientDrawable tgGroupBg = new GradientDrawable();
		tgGroupBg.setColor(Color.parseColor("#1E1E1E"));
		tgGroupBg.setCornerRadius(32);
		tgGroupBar.setBackground(tgGroupBg);

		LinearLayout.LayoutParams tgGroupLp = new LinearLayout.LayoutParams(
			LinearLayout.LayoutParams.MATCH_PARENT,
			LinearLayout.LayoutParams.WRAP_CONTENT);
		tgGroupLp.setMargins(0, 16, 0, 0);
		tgGroupBar.setLayoutParams(tgGroupLp);

		ImageView tgGroupIcon = new ImageView(this);
		LinearLayout.LayoutParams tgGroupIconLp = new LinearLayout.LayoutParams(72, 72);
		tgGroupIconLp.setMarginEnd(24);
		tgGroupIcon.setLayoutParams(tgGroupIconLp);

		try {
			ApplicationInfo tgInfo = getPackageManager().getApplicationInfo("org.telegram.messenger", 0);
			tgGroupIcon.setImageDrawable(getPackageManager().getApplicationIcon(tgInfo));
		} catch (PackageManager.NameNotFoundException e) {
			tgGroupIcon.setImageResource(android.R.drawable.sym_def_app_icon);
		}

		TextView tgGroupText = new TextView(this);
		tgGroupText.setText("Grup Telegram");
		tgGroupText.setTextColor(Color.WHITE);
		tgGroupText.setTextSize(14);

		tgGroupBar.addView(tgGroupIcon);
		tgGroupBar.addView(tgGroupText);

		tgGroupBar.setOnClickListener(new View.OnClickListener() {
				@Override
				public void onClick(View v) {
					try {
						Intent tgIntent = new Intent(Intent.ACTION_VIEW, Uri.parse("https://t.me/Ngulikers"));
						startActivity(tgIntent);
					} catch (Exception e) {
						Toast.makeText(MainActivity.this, "Telegram belum terinstall", Toast.LENGTH_SHORT).show();
					}
				}
			});

		settingsMenu.addView(tgGroupBar);

// === CHANNEL TELEGRAM ===
		LinearLayout tgChannelBar = new LinearLayout(this);
		tgChannelBar.setOrientation(LinearLayout.HORIZONTAL);
		tgChannelBar.setGravity(Gravity.CENTER_VERTICAL);
		tgChannelBar.setPadding(32, 32, 32, 32);

		GradientDrawable tgChannelBg = new GradientDrawable();
		tgChannelBg.setColor(Color.parseColor("#1E1E1E"));
		tgChannelBg.setCornerRadius(32);
		tgChannelBar.setBackground(tgChannelBg);

		LinearLayout.LayoutParams tgChannelLp = new LinearLayout.LayoutParams(
			LinearLayout.LayoutParams.MATCH_PARENT,
			LinearLayout.LayoutParams.WRAP_CONTENT);
		tgChannelLp.setMargins(0, 16, 0, 0);
		tgChannelBar.setLayoutParams(tgChannelLp);

		ImageView tgChannelIcon = new ImageView(this);
		LinearLayout.LayoutParams tgChannelIconLp = new LinearLayout.LayoutParams(72, 72);
		tgChannelIconLp.setMarginEnd(24);
		tgChannelIcon.setLayoutParams(tgChannelIconLp);

		try {
			ApplicationInfo tgInfo = getPackageManager().getApplicationInfo("org.telegram.messenger", 0);
			tgChannelIcon.setImageDrawable(getPackageManager().getApplicationIcon(tgInfo));
		} catch (PackageManager.NameNotFoundException e) {
			tgChannelIcon.setImageResource(android.R.drawable.sym_def_app_icon);
		}

		TextView tgChannelText = new TextView(this);
		tgChannelText.setText("Channel Telegram");
		tgChannelText.setTextColor(Color.WHITE);
		tgChannelText.setTextSize(14);

		tgChannelBar.addView(tgChannelIcon);
		tgChannelBar.addView(tgChannelText);

		tgChannelBar.setOnClickListener(new View.OnClickListener() {
				@Override
				public void onClick(View v) {
					try {
						Intent tgIntent = new Intent(Intent.ACTION_VIEW, Uri.parse("https://t.me/NAMA_CHANNEL_KAMU"));
						startActivity(tgIntent);
					} catch (Exception e) {
						Toast.makeText(MainActivity.this, "Telegram belum terinstall", Toast.LENGTH_SHORT).show();
					}
				}
			});

		settingsMenu.addView(tgChannelBar);

// === OWNER TELEGRAM ===
		LinearLayout tgOwnerBar = new LinearLayout(this);
		tgOwnerBar.setOrientation(LinearLayout.HORIZONTAL);
		tgOwnerBar.setGravity(Gravity.CENTER_VERTICAL);
		tgOwnerBar.setPadding(32, 32, 32, 32);

		GradientDrawable tgOwnerBg = new GradientDrawable();
		tgOwnerBg.setColor(Color.parseColor("#1E1E1E"));
		tgOwnerBg.setCornerRadius(32);
		tgOwnerBar.setBackground(tgOwnerBg);

		LinearLayout.LayoutParams tgOwnerLp = new LinearLayout.LayoutParams(
			LinearLayout.LayoutParams.MATCH_PARENT,
			LinearLayout.LayoutParams.WRAP_CONTENT);
		tgOwnerLp.setMargins(0, 16, 0, 0);
		tgOwnerBar.setLayoutParams(tgOwnerLp);

		ImageView tgOwnerIcon = new ImageView(this);
		LinearLayout.LayoutParams tgOwnerIconLp = new LinearLayout.LayoutParams(72, 72);
		tgOwnerIconLp.setMarginEnd(24);
		tgOwnerIcon.setLayoutParams(tgOwnerIconLp);

		try {
			ApplicationInfo tgInfo = getPackageManager().getApplicationInfo("org.telegram.messenger", 0);
			tgOwnerIcon.setImageDrawable(getPackageManager().getApplicationIcon(tgInfo));
		} catch (PackageManager.NameNotFoundException e) {
			tgOwnerIcon.setImageResource(android.R.drawable.sym_def_app_icon);
		}

		TextView tgOwnerText = new TextView(this);
		tgOwnerText.setText("Owner Telegram");
		tgOwnerText.setTextColor(Color.WHITE);
		tgOwnerText.setTextSize(14);

		tgOwnerBar.addView(tgOwnerIcon);
		tgOwnerBar.addView(tgOwnerText);

		tgOwnerBar.setOnClickListener(new View.OnClickListener() {
				@Override
				public void onClick(View v) {
					try {
						Intent tgIntent = new Intent(Intent.ACTION_VIEW, Uri.parse("https://t.me/NAMA_OWNER_KAMU"));
						startActivity(tgIntent);
					} catch (Exception e) {
						Toast.makeText(MainActivity.this, "Telegram belum terinstall", Toast.LENGTH_SHORT).show();
					}
				}
			});

		settingsMenu.addView(tgOwnerBar);

		root.addView(settingsMenu, 2);

		View spacer = new View(this);
		LinearLayout.LayoutParams spacerLp = new LinearLayout.LayoutParams(
			LinearLayout.LayoutParams.MATCH_PARENT,
			0,
			1f);
		spacer.setLayoutParams(spacerLp);
		root.addView(spacer);

        LinearLayout bottomBar = new LinearLayout(this);
        bottomBar.setOrientation(LinearLayout.HORIZONTAL);
        bottomBar.setPadding(32, 24, 32, 24);

        GradientDrawable bottomBg = new GradientDrawable();
        bottomBg.setColor(Color.parseColor("#1A1A1A"));
        bottomBg.setCornerRadius(40);
        bottomBar.setBackground(bottomBg);

        LinearLayout.LayoutParams bottomLp = new LinearLayout.LayoutParams(
			LinearLayout.LayoutParams.MATCH_PARENT,
			LinearLayout.LayoutParams.WRAP_CONTENT);
        bottomLp.setMargins(0, 48, 0, 0);
        bottomBar.setLayoutParams(bottomLp);

        homeIcon = new ImageView(this);
        homeIcon.setImageResource(R.drawable.ic_home);
        homeIcon.setColorFilter(Color.WHITE);
        homeIcon.setScaleType(ImageView.ScaleType.CENTER_INSIDE);
        homeIcon.setLayoutParams(new LinearLayout.LayoutParams(72, 72, 1));

        settingsIcon = new ImageView(this);
        settingsIcon.setImageResource(R.drawable.ic_settings);
        settingsIcon.setColorFilter(Color.LTGRAY);
        settingsIcon.setScaleType(ImageView.ScaleType.CENTER_INSIDE);
        settingsIcon.setLayoutParams(new LinearLayout.LayoutParams(72, 72, 1));

        homeIcon.setOnClickListener(new View.OnClickListener() {
				@Override
				public void onClick(View v) {
					topBar.setVisibility(View.VISIBLE);
					btn.setVisibility(View.VISIBLE);
					settingsMenu.setVisibility(View.GONE);
				}
			});

        settingsIcon.setOnClickListener(new View.OnClickListener() {
				@Override
				public void onClick(View v) {
					topBar.setVisibility(View.GONE);
					btn.setVisibility(View.GONE);
					settingsMenu.setVisibility(View.VISIBLE);
				}
			});

        bottomBar.addView(homeIcon);
        bottomBar.addView(settingsIcon);
        root.addView(bottomBar);

        setContentView(root);
    }

    private boolean isInstalled(PackageManager pm) {
        try {
            pm.getPackageInfo(TARGET_GAME, 0);
            return true;
        } catch (PackageManager.NameNotFoundException e) {
            return false;
        }
    }

    private String getVersion(PackageManager pm) {
        try {
            PackageInfo pi = pm.getPackageInfo(TARGET_GAME, 0);
            return pi.versionName;
        } catch (Exception e) {
            return "—";
        }
    }

    private void openGame() {
        Intent intent = getPackageManager()
			.getLaunchIntentForPackage(TARGET_GAME);

        if (intent != null) {
            startActivity(intent);
        } else {
            Toast.makeText(this,
						   "Game belum terinstall",
						   Toast.LENGTH_SHORT).show();
        }
    }
}

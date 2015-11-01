package com.application.android.esgi.ozma.wars.activities;

import android.os.Bundle;
import android.os.Build;
import android.app.Activity;
import android.content.SharedPreferences;
import android.app.Fragment;
import android.app.FragmentTransaction;
import android.util.Log;
import android.view.KeyEvent;
import android.view.Display;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.graphics.Point;
import java.lang.Runnable;
import com.squareup.picasso.Picasso;

import com.application.android.esgi.ozma.wars.R;
import com.application.android.esgi.ozma.wars.utils.OzmaUtils;
import com.application.android.esgi.ozma.wars.fragments.FragmentStart;

/**
  * ---- OzmaWarsActivity
  * Object: Handle and display specific fragments
  * Used by: Application
  *
  * @author Pierre (Pierre Flauder) &amp; Fllo (Florent Blot)
**/
public class OzmaWarsActivity extends Activity {

    private static final String DEBUG_TAG = "//-- OzmaWarsActivity";
    private SharedPreferences prefs;
    private FrameLayout frame;
    private int introStep,
                imageSize;

    // Setup
    @Override
    protected void onCreate(Bundle inState) {
        Log.v(DEBUG_TAG, "onCreate()");
        super.onCreate(inState);
        setContentView(R.layout.ozma_activity);

        // Get preferences
        prefs = getSharedPreferences(OzmaUtils.PREFS, Activity.MODE_PRIVATE);

        // If user already started a game
        if ( prefs.getBoolean(OzmaUtils.P__INTRO, false) && inState == null ) {
        //     // Display Start fragment
        //     getFragmentManager().beginTransaction()
        //             .add(R.id.main_frame, FragmentStart.newInstance(), OzmaUtils.START_TAG)
        //             .commit();
        // } else {
            // Prepare the animation
            Runnable introRunnable = new Runnable() {
                @Override
                public void run() {
                    playIntroduction(introStep);
                    introStep++;

                    if (introStep > 2) {
                        frame.removeCallbacks(this);
                        return;
                    }

                    // Loop
                    frame.postDelayed(this, 6000);
                }
            };
            // Call the introduction
            frame = (FrameLayout) findViewById(R.id.main_frame);
            frame.postDelayed(introRunnable, 1000);
            // Save the state introduction
            SharedPreferences.Editor editor = prefs.edit();
            editor.putBoolean(OzmaUtils.P__INTRO, true);
            editor.apply();
        }
    }

    // Fragments handler method
    public void handleFragment(Fragment fragment, String tag, boolean addToBackStack) {
        if (fragment == null) return;

        FragmentTransaction transaction = getFragmentManager().beginTransaction();
        transaction.replace(R.id.main_frame, fragment, tag);
        if (addToBackStack) transaction.addToBackStack(tag);
        transaction.commit();
    }

    // OnBackPressed method
    @Override
    public void onBackPressed() {
        if (getFragmentManager().getBackStackEntryCount() > 0) {
            getFragmentManager().popBackStack();
        } else {
            super.onBackPressed();
            finish();
        }
    }

    // Introduction
    private void playIntroduction(int i) {
        // Show images and text
        ImageView screen = new ImageView(this);
        frame.addView(screen);

        // Get images
        int idImage;
        switch(i) {
            case 0: default:
                idImage = R.drawable.cinematic_details;
                break;
            case 1:
                idImage = R.drawable.cinematic_pilot;
                break;
            case 2:
                idImage = R.drawable.cinematic_final;
                break;
        }

        // Prepare image sizes
        if (imageSize == 0) {
            final Point displySize = getDisplaySize(getWindowManager().getDefaultDisplay());
            imageSize = (int) Math.ceil(Math.sqrt(displySize.x * displySize.y));
        }

        // Show images
        Picasso.with(this)
                .load(idImage)
                .resize(imageSize, imageSize)
                .centerCrop()
                .into(screen);
        // Preparation de l'animation
        // ...
    }

    public Point getDisplaySize(Display display) {
        Point size = new Point();

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB_MR2) {
            display.getSize(size);
        } else {
            int width = display.getWidth();
            int height = display.getHeight();
            size = new Point(width, height);
        }

        return size;
    }
}

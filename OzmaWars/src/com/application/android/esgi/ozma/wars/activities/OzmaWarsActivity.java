package com.application.android.esgi.ozma.wars.activities;

import android.os.Bundle;
import android.os.Build;
import android.app.Activity;
import android.content.SharedPreferences;
import android.app.Fragment;
import android.app.FragmentManager;
import android.app.FragmentTransaction;
import android.util.Log;
import android.view.KeyEvent;
import android.view.Display;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.graphics.Point;
import java.lang.Runnable;
import com.squareup.picasso.Picasso;

import com.application.android.esgi.ozma.wars.R;
import com.application.android.esgi.ozma.wars.utils.OzmaUtils;
import com.application.android.esgi.ozma.wars.fragments.HomeFragment;
import com.application.android.esgi.ozma.wars.fragments.IntroductionFragment;


/**
  * ---- OzmaWarsActivity
  * Object: Handle and display specific fragments
  * Used by: Application
  *
  * @author Pierre (Pierre Flauder) &amp; Fllo (Florent Blot)
**/
public class OzmaWarsActivity extends Activity {

    private static final String DEBUG_TAG = "//-- OzmaWarsActivity";
    private IntroductionFragment mIntroductionFrag;
    private SharedPreferences prefs;

    // Setup
    @Override
    protected void onCreate(Bundle inState) {
        Log.v(DEBUG_TAG, "onCreate()");
        super.onCreate(inState);
        setContentView(R.layout.ozma_activity);

        // Get preferences
        prefs = getSharedPreferences(OzmaUtils.PREFS, Activity.MODE_PRIVATE);

        // Get fragment introduction
        FragmentManager fragmentManager = getFragmentManager();
        mIntroductionFrag = (IntroductionFragment) fragmentManager.findFragmentByTag(OzmaUtils.INTRO_TAG);

        // If user already started a game
        if ( prefs.getBoolean(OzmaUtils.P__INTRO, false) && mIntroductionFrag == null ) {
            // Display Start fragment
            getFragmentManager().beginTransaction()
                    .add(R.id.main_frame, HomeFragment.newInstance(), OzmaUtils.HOME_FRAG)
                    .commit();
        } else {
            // Display Intro cinematic fragment
            mIntroductionFrag = IntroductionFragment.newInstance();
            fragmentManager.beginTransaction()
                    .add(R.id.main_frame, mIntroductionFrag, OzmaUtils.INTRO_TAG)
                    .commit();
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
}

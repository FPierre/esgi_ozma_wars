package com.application.android.esgi.ozma.wars;

import android.os.Bundle;
import android.app.Activity;
import android.app.Fragment;
import android.app.FragmentTransaction;
import android.util.Log;
import android.view.KeyEvent;
import android.widget.FrameLayout;

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

    // Main components
    private FrameLayout mFrame;

    // Setup
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        Log.v(DEBUG_TAG, "onCreate()");
        super.onCreate(savedInstanceState);
        setContentView(R.layout.ozma_activity);

        mFrame = (FrameLayout) findViewById(R.id.main_frame);

        // Display Start fragment
        if (savedInstanceState == null)
        	handleFragment(FragmentStart.newInstance(), OzmaUtils.FRAG_START_TAG, false);
    }

    // Fragments handler method
    public void handleFragment(Fragment fragment, String tag, boolean addToBackStack) {
        if (fragment == null) return;

        FragmentTransaction transaction = getFragmentManager().beginTransaction();
        transaction.replace(R.id.main_frame, fragment, tag);
        if (addToBackStack) transaction.addToBackStack(tag);
        transaction.commit();
    }

    @Override
    public boolean dispatchKeyEvent(KeyEvent event) {
        int keyCode = event.getKeyCode();
        // Ignore certain special keys so they're handled by Android
        if (keyCode == KeyEvent.KEYCODE_VOLUME_DOWN ||
            keyCode == KeyEvent.KEYCODE_VOLUME_UP ||
            keyCode == KeyEvent.KEYCODE_CAMERA ||
            keyCode == 168 || /* API 11: KeyEvent.KEYCODE_ZOOM_IN */
            keyCode == 169 /* API 11: KeyEvent.KEYCODE_ZOOM_OUT */ ) {
            return false;
        }
        return super.dispatchKeyEvent(event);
    }

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
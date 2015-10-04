package com.application.android.esgi.ozma.wars.activities;

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

    // Setup
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        Log.v(DEBUG_TAG, "onCreate()");
        super.onCreate(savedInstanceState);
        setContentView(R.layout.ozma_activity);

        // Display Start fragment
        if (savedInstanceState == null) {
            getFragmentManager().beginTransaction()
                    .add(R.id.main_frame, FragmentStart.newInstance(), OzmaUtils.START_TAG)
                    .commit();
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

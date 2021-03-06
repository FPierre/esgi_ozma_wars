package com.application.android.esgi.ozma.wars.fragments;

import android.app.Activity;
import android.app.Fragment;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.application.android.esgi.ozma.wars.R;
import com.application.android.esgi.ozma.wars.utils.OzmaUtils;
import com.application.android.esgi.ozma.wars.activities.OzmaWarsActivity;


/**
  * ---- SettingsFragment
  * Object: User settings (sounds, vibrate, score, etc)
  * Used by: OzmaWarsActivity
  *
  * @author Pierre (Pierre Flauder) &amp; Fllo (Florent Blot)
**/
public class SettingsFragment extends Fragment {
	
    // Debug
    private static final String DEBUG_TAG = "//-- SettingsFragment";

    // Context
    private Activity activity;

    public SettingsFragment() { }

    public static SettingsFragment newInstance() {
    	SettingsFragment frag = new SettingsFragment();
    	return frag;
    }

    @Override
    public void onAttach(Activity activity_) {
        super.onAttach(activity_);
        this.activity = activity_;
    }

    @Override
    public void onStart() {
        super.onStart();
    }

    @Override
    public void onResume() {
        super.onResume();
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View v = inflater.inflate(R.layout.fragment_settings, container, false);

        TextView btnClearScore = (TextView) v.findViewById(R.id.button_clear_score);
        // Display a new game
        btnClearScore.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                activity.getFragmentManager().popBackStack();
            }
        });

        TextView btnSeeIntro = (TextView) v.findViewById(R.id.button_see_intro);
        // Display intro cinematic
        btnSeeIntro.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                ((OzmaWarsActivity) activity).handleFragment(
                    IntroductionFragment.newInstance(), OzmaUtils.INTRO_TAG, true);
            }
        });

        return v;
    }

    @Override
    public void onPause() {
        super.onPause();
    }

    @Override
    public void onDetach() {
        super.onDetach();
    }
}
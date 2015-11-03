package com.application.android.esgi.ozma.wars.fragments;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import com.application.android.esgi.ozma.wars.R;
import com.application.android.esgi.ozma.wars.utils.OzmaUtils;
import com.application.android.esgi.ozma.wars.activities.OzmaWarsActivity;
import com.application.android.esgi.ozma.wars.activities.GameActivity;


/**
  * ---- FragmentStart
  * Object: Start/Continue a game
  * Used by: OzmaWarsActivity
  *
  * @author Pierre (Pierre Flauder) &amp; Fllo (Florent Blot)
**/
public class FragmentStart extends Fragment {
	
    // Debug
    private static final String DEBUG_TAG = "//-- FragmentStart";

    // Context
    private Activity activity;

    public FragmentStart() { }

    public static FragmentStart newInstance() {
    	FragmentStart frag = new FragmentStart();
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
        View v = inflater.inflate(R.layout.fragment_start, container, false);

        TextView textHighScore = (TextView) v.findViewById(R.id.text_highscore);
        ImageView btnSettings = (ImageView) v.findViewById(R.id.button_settings);
        TextView btnNewGame = (TextView) v.findViewById(R.id.button_new_game);
        TextView btnContinueGame = (TextView) v.findViewById(R.id.button_continue_game);

        // Open settings fragment
        btnSettings.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                ((OzmaWarsActivity) activity).handleFragment(FragmentSettings.newInstance(),  OzmaUtils.SETTINGS_TAG, true);
            }
        });
        // Display a new game
        btnNewGame.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent i = new Intent(activity, GameActivity.class);
                activity.startActivity(i);
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
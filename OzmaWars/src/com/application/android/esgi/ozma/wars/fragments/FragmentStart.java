package com.application.android.esgi.ozma.wars.fragments;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.application.android.esgi.ozma.wars.R;
import com.application.android.esgi.ozma.wars.OzmaWarsActivity;

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

    public FragmentStart() { }

    public static FragmentStart newInstance() {
    	FragmentStart frag = new FragmentStart();
    	return frag;
    }

    @Override
    public void onAttach(Activity activity) {
        super.onAttach(activity);
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
package com.application.android.esgi.ozma.wars.activities;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.Build;
import android.app.Fragment;
import android.view.LayoutInflater;
import android.view.Display;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.graphics.Point;
import java.lang.Runnable;
import com.squareup.picasso.Picasso;
import android.widget.TextView;

import com.application.android.esgi.ozma.wars.R;
import com.application.android.esgi.ozma.wars.utils.OzmaUtils;
import com.application.android.esgi.ozma.wars.activities.OzmaWarsActivity;

/**
  * ---- FragmentCinematicIntro
  * Object: Handle and display specific fragments
  * Used by: OzmaWarsActivity, FragmentSettings
  *
  * @author Pierre (Pierre Flauder) &amp; Fllo (Florent Blot)
**/
public class FragmentCinematicIntro extends Fragment {

	// Debug
    private static final String DEBUG_TAG = "//-- FragmentCinematicIntro";

    // Context
    private Activity activity;
    private ImageView screen;
    private int introStep,
                imageSize;

    public FragmentCinematicIntro() { }

    public static FragmentCinematicIntro newInstance() {
    	FragmentCinematicIntro frag = new FragmentCinematicIntro();
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
        View v = inflater.inflate(R.layout.fragment_cinematic, container, false);
        // Prepare views
        screen = (ImageView) v.findViewById(R.id.cinematic_image);
        // Prepare the animation
        Runnable introRunnable = new Runnable() {
            @Override
            public void run() {
                playIntroduction(introStep);
                introStep++;

                if (introStep > 2) {
                    screen.removeCallbacks(this);
                    return;
                }

                // Loop
                screen.postDelayed(this, 8000);
            }
        };
        // Call the introduction
        screen.post(introRunnable);

        return v;
    }

    // Introduction
    private void playIntroduction(int i) {
        // Prepare texts

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
            final Point displySize = getDisplaySize(activity.getWindowManager().getDefaultDisplay());
            imageSize = (int) Math.ceil(Math.sqrt(displySize.x * displySize.y));
        }

        // Show images
        Picasso.with(activity)
                .load(idImage)
                .resize(imageSize + (imageSize/2), imageSize)
                // .centerInside()
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
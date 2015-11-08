package com.application.android.esgi.ozma.wars.fragments;

import java.lang.Runnable;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.Build;
import android.app.Fragment;
import android.graphics.drawable.Drawable;
import android.graphics.Bitmap;
import android.graphics.Point;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.view.LayoutInflater;
import android.view.Display;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;
import android.util.Log;

import com.squareup.picasso.Picasso;
import com.squareup.picasso.Callback;

import com.application.android.esgi.ozma.wars.R;
import com.application.android.esgi.ozma.wars.utils.OzmaUtils;
import com.application.android.esgi.ozma.wars.utils.AnimatePicasso;
import com.application.android.esgi.ozma.wars.activities.OzmaWarsActivity;

/**
  * ---- IntroductionFragment
  * Object: Handle and display specific fragments
  * Used by: OzmaWarsActivity, FragmentSettings
  *
  * @author Pierre (Pierre Flauder) &amp; Fllo (Florent Blot)
**/
public class IntroductionFragment extends Fragment {

	// Debug
    private static final String DEBUG_TAG = "//-- Introduction";

    // Context
    private Activity 	activity;
    private ImageView 	screen;
    private TextView 	legend,
                        play;
    private int 		introStep,
                		imageSize;

    public IntroductionFragment() { }

    public static IntroductionFragment newInstance() {
    	IntroductionFragment frag = new IntroductionFragment();
        Log.v(DEBUG_TAG, "fragment.newInstance()");
    	return frag;
    }

    // public interface IntroState() {
    //     public void getFragmentState();
    //     public void getImageAnimation();
    // }

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
        Log.v(DEBUG_TAG, "fragment.onResume()");
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setRetainInstance(true);
        Log.v(DEBUG_TAG, "fragment.onCreate()");
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View v = inflater.inflate(R.layout.fragment_cinematic, container, false);
        Log.v(DEBUG_TAG, "fragment.onCreateView()");
        // Prepare views
        screen = (ImageView) v.findViewById(R.id.cinematic_image);
        legend = (TextView)  v.findViewById(R.id.cinematic_legends);
        play   = (TextView)  v.findViewById(R.id.cinematic_button_game);
        legend.setText(activity.getResources().getString(R.string.cinematic_presents));
        // Prepare the animation
        Runnable introRunnable = new Runnable() {
            @Override
            public void run() {
                Log.v(DEBUG_TAG, "fragment.new Runnable()");
                playIntroduction(introStep);
                introStep++;

                if (introStep > 2) {
                    screen.removeCallbacks(this);
                    return;
                }

                // Loop
                screen.postDelayed(this, 4600);
            }
        };
        // Call the introduction
        screen.postDelayed(introRunnable, 3600);

        // Hide the 1st text after 3sec
        legend.postDelayed(new Runnable() {
            @Override
            public void run() {
                Animation a_out  = AnimationUtils.loadAnimation(activity, R.anim.fade_text_out);
                a_out.setFillAfter(true);
                legend.startAnimation(a_out);
            }
        }, 3000);

        return v;
    }

    // Introduction
    private void playIntroduction(final int i) {
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

        // Show images with animation
        Picasso.with(activity)
        		.load(idImage)
        		.resize(imageSize + (imageSize/2), imageSize)
        		.into(screen,  new Callback() {
		            @Override
		            public void onSuccess() {
				        AnimatePicasso.init(activity)
				        			  .on(screen)
				        			  .with(legend)
				        			  .animate(i, callback);
		            }
		            @Override
		            public void onError() { }
		        });
    }

    // Callback when cinematic animation ends
    private AnimatePicasso.AnimateCallbacks callback = new AnimatePicasso.AnimateCallbacks() {
        @Override
        public void end() {
            play.setVisibility(View.VISIBLE);
            // Go to start fragment
            play.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    launchStartFragment();
                }
            });
        }
    };

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

    // Start fragment transisition
    private void launchStartFragment() {
        play.setVisibility(View.GONE);
        Log.v(DEBUG_TAG, "fragment.launchStartFragment()");

        Animation a_img  = AnimationUtils.loadAnimation(activity, R.anim.slide_image_t_to_b_out);
        a_img.setFillAfter(true);
        a_img.setAnimationListener(new Animation.AnimationListener() {
            @Override
            public void onAnimationStart(Animation animation) { }
            @Override
            public void onAnimationEnd(Animation animation) {
                Log.v(DEBUG_TAG, "fragment.onAnimationEnd()");
                ((OzmaWarsActivity) activity).handleFragment(
                    FragmentStart.newInstance(), OzmaUtils.START_TAG, false);
            }
            @Override
            public void onAnimationRepeat(Animation animation) { }
        });
        screen.startAnimation(a_img);
    }
}
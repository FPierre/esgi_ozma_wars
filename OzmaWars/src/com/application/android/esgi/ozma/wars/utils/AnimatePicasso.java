package com.application.android.esgi.ozma.wars.utils;

// import android.app.Activity;
import android.content.Context;
// import android.app.Fragment;
// import android.os.Bundle;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
// import android.view.LayoutInflater;
// import android.view.View;
// import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import com.application.android.esgi.ozma.wars.R;


/**
  * ---- AnimatePicasso
  * Object: Custom class to animate Picasso ImageView
  * 
  * @author Pierre (Pierre Flauder) &amp; Fllo (Florent Blot)
**/
public class AnimatePicasso {
	
    // Debug
    private static final String DEBUG_TAG = "//-- AnimatePicasso";

    // Context
    private static AnimatePicasso _instance;
    private Context 			  _context;
    private ImageView 			  _target;
    private TextView 			  _legend;

    public static AnimatePicasso init(Context _context) {
    	if (_instance == null) {
	      	synchronized (AnimatePicasso.class) {
	        	if (_instance == null) {
	          		_instance = new AnimatePicasso();
	          		_instance._context = _context;
	        	}
	      	}
	    }
	    return _instance;
    }

	// Get the imageview
	public AnimatePicasso on(ImageView _target) {
		if (_target != null) {
			this._target = _target;
		}
	    return _instance;
	}

	// Get the textview
	public AnimatePicasso with(TextView _legend) {
		if (_legend != null) {
			this._legend = _legend;
		}
	    return _instance;
	}

	// Get the aimation
	public void animate(int _transform) {
		if (_target != null && _legend != null) {
    		translate(_transform);
		}
	}

    // Transformation of imageview
    private void translate(int _transform) {
    	Animation a_img = null, a_text = null;

        switch (_transform) {
        	case 0:
        		a_img = AnimationUtils.loadAnimation(_context, R.anim.slide_in_right);
        		a_text = AnimationUtils.loadAnimation(_context, R.anim.slide_text_in_left);
        		_legend.setText(_context.getResources().getString(R.string.cinematic_context));
        		break;
        	case 1:
        		a_img = AnimationUtils.loadAnimation(_context, R.anim.slide_in_left);
        		a_text = AnimationUtils.loadAnimation(_context, R.anim.slide_text_in_right);
        		_legend.setText(_context.getResources().getString(R.string.cinematic_heros));
        		break;
        	case 2:
        		a_img = AnimationUtils.loadAnimation(_context, R.anim.slide_in_top);
        		_legend.setText(_context.getResources().getString(R.string.cinematic_revenge));
        		a_img.setFillAfter(true);
        		break;
        }

        if (a_img==null || _target==null) return;
        _target.startAnimation(a_img);

        if (a_text!=null && _legend!=null)
        	_legend.startAnimation(a_text);
    }
}
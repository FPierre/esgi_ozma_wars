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
// import android.widget.TextView;

import com.application.android.esgi.ozma.wars.R;


/**
  * ---- TransformPicasso
  * Object: Custom class extending by Picasso lib (Square)
  * 
  * @author Pierre (Pierre Flauder) &amp; Fllo (Florent Blot)
**/
public class TransformPicasso {
	
    // Debug
    private static final String DEBUG_TAG = "//-- TransformPicasso";

    // Context
    private static TransformPicasso _instance;
    private Context 				_context;
    private ImageView 				_target;

    public static TransformPicasso with(Context _context) {
    	if (_instance == null) {
	      	synchronized (TransformPicasso.class) {
	        	if (_instance == null) {
	          		_instance = new TransformPicasso();
	          		_instance._context = _context;
	        	}
	      	}
	    }
	    return _instance;
    }

	// Get the imageview
	public void animate(ImageView _target, int _transform) {
		if (_target != null) {
			this._target = _target;
    		translate(_transform);
		}
	}

    // Transformation of imageview
    private void translate(int _transform) {
    	Animation a = null;

        switch (_transform) {
        	case 0:
        		a = AnimationUtils.loadAnimation(_context, R.anim.slide_in_right);
        		break;
        	case 1:
        		a = AnimationUtils.loadAnimation(_context, R.anim.slide_in_left);
        		break;
        	case 2:
        		a = AnimationUtils.loadAnimation(_context, R.anim.slide_in_top);
        		a.setFillAfter(true);
        		break;
        }

        if (a==null) return;
        _target.startAnimation(a);
    }
}
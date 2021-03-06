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
    private AnimateCallbacks      _callbacks;

    public interface AnimateCallbacks {
        void end();
    }

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
	public void animate(int _transform, AnimateCallbacks _callbacks) {
		if (_target != null && _legend != null) {
            this._callbacks = _callbacks;
    		translate(_transform);
		}
	}

    // Transformation of imageview
    private void translate(int _transform) {
    	Animation a_img = null, a_text = null;

        switch (_transform) {
        	case 0:
        		a_img  = AnimationUtils.loadAnimation(_context, R.anim.slide_image_r_to_l);
        		a_text = AnimationUtils.loadAnimation(_context, R.anim.slide_text_l_to_r);
        		_legend.setText(_context.getResources().getString(R.string.cinematic_context));
        		break;
        	case 1:
        		a_img  = AnimationUtils.loadAnimation(_context, R.anim.slide_image_l_to_r);
        		a_text = AnimationUtils.loadAnimation(_context, R.anim.slide_text_r_to_l);
        		_legend.setText(_context.getResources().getString(R.string.cinematic_heros));
        		break;
        	case 2:
        		a_img  = AnimationUtils.loadAnimation(_context, R.anim.slide_image_t_to_b);
        		a_text = AnimationUtils.loadAnimation(_context, R.anim.fade_text_in);
        		_legend.setText(_context.getResources().getString(R.string.cinematic_revenge));
                
                a_img.setAnimationListener(new Animation.AnimationListener() {
                    @Override
                    public void onAnimationStart(Animation animation) { }
                    @Override
                    public void onAnimationEnd(Animation animation) {
                        Animation end_text = AnimationUtils.loadAnimation(_context, R.anim.fade_text_out);
                        end_text.setFillAfter(true);
                        
                        _legend.startAnimation(end_text);
                        _callbacks.end();
                    }
                    @Override
                    public void onAnimationRepeat(Animation animation) { }
                });
        		break;
        }

        a_img.setFillAfter(true);
        a_text.setFillAfter(true);

        if (a_img==null || _target==null) return;
        _target.startAnimation(a_img);

        if (a_text!=null && _legend!=null)
        	_legend.startAnimation(a_text);
    }
}
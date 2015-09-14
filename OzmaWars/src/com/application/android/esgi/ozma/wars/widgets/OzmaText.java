package com.application.android.esgi.ozma.wars.widgets;

import android.content.Context;
import android.graphics.Typeface;
import android.util.AttributeSet;
import android.widget.TextView;

/**
  * OzmaText: custom widget with external fonts (UpperCase default)
**/
public class OzmaText extends TextView {

    public OzmaText(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);
        init();
    }

    public OzmaText(Context context, AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    public OzmaText(Context context) {
        super(context);
        init();
    }

    public void init() {
        Typeface tf = Typeface.createFromAsset(getContext().getAssets(), "fonts/consola.ttf");
        setTypeface(tf, 1);
    }

    @Override
    public void setText(CharSequence text, BufferType type) {
        super.setText(text.toString().toUpperCase(), type);
    }
}
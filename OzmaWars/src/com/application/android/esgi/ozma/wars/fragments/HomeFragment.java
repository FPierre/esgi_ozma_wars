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

import java.lang.Thread;
import java.lang.Runnable;
import android.os.Handler;

import com.application.android.esgi.ozma.wars.R;
import com.application.android.esgi.ozma.wars.utils.OzmaUtils;
import com.application.android.esgi.ozma.wars.activities.OzmaWarsActivity;
import com.application.android.esgi.ozma.wars.activities.GameActivity;
import com.application.android.esgi.ozma.wars.database.GameModel;
import com.application.android.esgi.ozma.wars.database.OzmaDatabase;


/**
  * ---- HomeFragment
  * Object: Start/Continue a game
  * Used by: OzmaWarsActivity
  *
  * @author Pierre (Pierre Flauder) &amp; Fllo (Florent Blot)
**/
public class HomeFragment extends Fragment {
	
    // Debug
    private static final String DEBUG_TAG = "//-- HomeFragment";

    // Contexte
    private Activity activity;
    private OzmaDatabase database;
    private GameModel lastGame;

    public HomeFragment() { }

    public static HomeFragment newInstance() {
    	HomeFragment frag = new HomeFragment();
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

        // Initialise la SQLite database
        database = new OzmaDatabase(getActivity());
        // Récupère le dernier jeu
        lastGame = database.getLastGame();
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View v = inflater.inflate(R.layout.fragment_home, container, false);

        final TextView textHighScore = (TextView) v.findViewById(R.id.text_highscore);
        final TextView btnNewGame = (TextView) v.findViewById(R.id.button_new_game);
        final TextView btnContinueGame = (TextView) v.findViewById(R.id.button_continue_game);
        ImageView btnSettings = (ImageView) v.findViewById(R.id.button_settings);

        // Affiche l'écran de préférences
        btnSettings.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                ((OzmaWarsActivity) activity).handleFragment(
                    SettingsFragment.newInstance(), OzmaUtils.SETTINGS_TAG, true);
            }
        });

        // Commence un nouveau jeu
        btnNewGame.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent i = new Intent(activity, GameActivity.class);
                activity.startActivity(i);
            }
        });

        // Commence un jeu en cours
        btnContinueGame.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent i = new Intent(activity, GameActivity.class);
                if (lastGame != null && lastGame.getStatus() > 0) {
                    i.putExtra("id", lastGame.getId());
                    i.putExtra("score", lastGame.getScore());
                    i.putExtra("life", lastGame.getLife());
                    i.putExtra("level", lastGame.getLevel());
                }
                activity.startActivity(i);
            }
        });

        // Récupère et affiche les dernières données d'un jeu
        v.post(new Runnable() {
            @Override
            public void run() {
                lastGame = database.getLastGame();
                int highScore = database.getHighScore();

                if (highScore > 0) {
                    textHighScore.setText( String.valueOf(highScore) );
                }

                if (lastGame != null && lastGame.getStatus() > 0) {
                    btnContinueGame.setTextColor( getActivity().getResources().getColor(R.color.white) );
                    btnContinueGame.setBackgroundDrawable( getActivity().getResources().getDrawable(R.drawable.border_white) );
                    btnContinueGame.setEnabled(true);
                } else {
                    btnContinueGame.setEnabled(false);
                }
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
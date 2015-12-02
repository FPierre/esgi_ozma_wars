package com.application.android.esgi.ozma.wars.database;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.util.Log;

import java.util.ArrayList;

import com.application.android.esgi.ozma.wars.database.GameModel;

/**
  * ---- OzmaDatabase
  * Object: SQLite database
  * Used by: OzmaWarsActivity, GameActivity
  *
  * @author Pierre (Pierre Flauder) &amp; Fllo (Florent Blot)
**/
public class OzmaDatabase extends SQLiteOpenHelper {

	private static final String DEBUG_DB = "//-- OzmaDatabase";

    private static final int DATABASE_VERSION 	= 1;
    private static final String DATABASE_NAME 	= "OzmaDatabase";
    private static final String TABLE_GAME_NAME = "OzmaGame";

    private static final String KEY_GAME_ID 	= "game_id";
    private static final String KEY_GAME_SCORE 	= "game_score";
    private static final String KEY_GAME_LIFE 	= "game_life";
    private static final String KEY_GAME_LEVEL  = "game_level";
    private static final String KEY_GAME_STATE  = "game_state";

    private static final String[] COLUMNS = {   
                                                KEY_GAME_ID,
                                                KEY_GAME_SCORE,
                                                KEY_GAME_LIFE,
                                                KEY_GAME_LEVEL,
                                                KEY_GAME_STATE
                                            };

    /**
     * @param context to use to open or create the database
     * - "name" of the database file, or null for an in-memory database
     * - "factory" to use for creating cursor objects, or null for the default
     * - "version" number of the database (starting at 1); if the database is older,
     *     {@link #onUpgrade} will be used to upgrade the database; if the database is
     *     newer, {@link #onDowngrade} will be used to downgrade the database
     **/
    public OzmaDatabase(Context context) {
        super(context, DATABASE_NAME, null, 1);
        Log.i(DEBUG_DB, "Constructor");
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        String CREATE_TABLE = "CREATE TABLE " + TABLE_GAME_NAME
                + " ( game_id INTEGER PRIMARY KEY AUTOINCREMENT, "
                + "game_score INTEGER, "
                + "game_life INTEGER, "
                + "game_level INTEGER, "
                + "game_state INTEGER )";

        db.execSQL(CREATE_TABLE);
        Log.i(DEBUG_DB, "onCreate()");
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_GAME_NAME);
        this.onCreate(db);
        Log.i(DEBUG_DB, "onUpgrade()");
    }

    public long addGame(GameModel game) {
        SQLiteDatabase db = this.getWritableDatabase();
        ContentValues values = new ContentValues();
        values.put(KEY_GAME_SCORE, 	game.getScore());
        values.put(KEY_GAME_LIFE, 	game.getLife());
        values.put(KEY_GAME_LEVEL, 	game.getLevel());
        values.put(KEY_GAME_STATE,  game.getStatus());

        long res = db.insert(TABLE_GAME_NAME, null, values);
        db.close();
        Log.i(DEBUG_DB, "addGame() with \"game_id\": " + res);
        return res;
    }

    public GameModel getGame(int id) {
        SQLiteDatabase db = this.getReadableDatabase();
        Cursor cursor = db.query(TABLE_GAME_NAME, COLUMNS,
                " game_id = ?",
                new String[] { String.valueOf(id) },
                null,   // Group by
                null,   // Having
                null,   // Order by
                null);  // Limit

        GameModel game = null;
        if (cursor != null && cursor.moveToFirst()) {

            game = new GameModel();
            game.setId(Integer.parseInt(cursor.getString(cursor.getColumnIndex(KEY_GAME_ID))));
            game.setScore(Integer.parseInt(cursor.getString(cursor.getColumnIndex(KEY_GAME_SCORE))));
            game.setLife(Integer.parseInt(cursor.getString(cursor.getColumnIndex(KEY_GAME_LIFE))));
            game.setLevel(Integer.parseInt(cursor.getString(cursor.getColumnIndex(KEY_GAME_LEVEL))));
            game.setStatus(Integer.parseInt(cursor.getString(cursor.getColumnIndex(KEY_GAME_STATE))));

        }

        if (!cursor.isClosed())
            cursor.close();

        Log.i(DEBUG_DB, "getGame() with \"game_id\": " + id);
        return game;
    }

    public GameModel getLastGame() {
        SQLiteDatabase db = this.getReadableDatabase();
        Cursor cursor = db.query(TABLE_GAME_NAME, COLUMNS,
                null,
                null,
                null,   // Group by
                null,   // Having
                KEY_GAME_ID + " DESC",   // Order by
                "1");  // Limit

        GameModel game = null;
        if (cursor != null && cursor.moveToFirst()) {

            game = new GameModel();
            game.setId(Integer.parseInt(cursor.getString(cursor.getColumnIndex(KEY_GAME_ID))));
            game.setScore(Integer.parseInt(cursor.getString(cursor.getColumnIndex(KEY_GAME_SCORE))));
            game.setLife(Integer.parseInt(cursor.getString(cursor.getColumnIndex(KEY_GAME_LIFE))));
            game.setLevel(Integer.parseInt(cursor.getString(cursor.getColumnIndex(KEY_GAME_LEVEL))));
            game.setStatus(Integer.parseInt(cursor.getString(cursor.getColumnIndex(KEY_GAME_STATE))));

        }

        if (!cursor.isClosed())
            cursor.close();

        Log.i(DEBUG_DB, "getLastGame() with \"game_id\": " + game.getId());
        return game;
    }

    public int getHighScore() {
        SQLiteDatabase db = this.getReadableDatabase();
        Cursor cursor = db.query(TABLE_GAME_NAME, COLUMNS,
                null,
                null,
                null,   // Group by
                null,   // Having
                KEY_GAME_SCORE + " DESC",   // Order by
                "1");  // Limit

        int score = 0;
        if (cursor != null && cursor.moveToFirst()) {
            score = Integer.parseInt(cursor.getString(cursor.getColumnIndex(KEY_GAME_SCORE)));
        }

        if (!cursor.isClosed())
            cursor.close();

        Log.i(DEBUG_DB, "getHighScore() : " + score);
        return score;
    }

    public ArrayList<Integer> getAllGameScores() {
        ArrayList<Integer> scores = new ArrayList<Integer>();
        String query = "SELECT * FROM " + TABLE_GAME_NAME;
        SQLiteDatabase db = this.getReadableDatabase();
        Cursor cursor = db.rawQuery(query, null);
        int score = 0;
        if (cursor != null && cursor.moveToFirst()) {
            do {
                score = Integer.parseInt(cursor.getString(cursor.getColumnIndex(KEY_GAME_SCORE)));
                scores.add(score);
            } while (cursor.moveToNext());
        }

        if (cursor != null && !cursor.isClosed())
            cursor.close();

        Log.i(DEBUG_DB, "getAllGameScores() (list contains " + scores.size() + " scores)");
        return scores;
    }

    public int updateGame(GameModel game) {
        SQLiteDatabase db = this.getWritableDatabase();
        ContentValues values = new ContentValues();
        values.put(KEY_GAME_ID, 	game.getId());
        values.put(KEY_GAME_SCORE, 	game.getScore());
        values.put(KEY_GAME_LIFE, 	game.getLife());
        values.put(KEY_GAME_LEVEL, 	game.getLevel());
        values.put(KEY_GAME_STATE,  game.getStatus());

        int res = db.update(TABLE_GAME_NAME, values, "game_id = ?",
                new String[]{String.valueOf(game.getId())});
        db.close();
        Log.i(DEBUG_DB, "updateGame() with \"id\": " + game.getId());
        return res;
    }

    public int deleteGame(int id) {
        Log.i(DEBUG_DB, "deleteGame() with \"game_id\": " + id);
        SQLiteDatabase db = this.getWritableDatabase();
        int res = db.delete(TABLE_GAME_NAME, " game_id = ?", new String[]{String.valueOf(id)});
        db.close();
        return res;
    }

    public int deleteGameScore(GameModel game) {
        SQLiteDatabase db = this.getWritableDatabase();
        ContentValues values = new ContentValues();
        values.put(KEY_GAME_SCORE, 0);

        int res = db.update(TABLE_GAME_NAME, values, "game_id = ?",
                new String[]{String.valueOf(game.getId())});
        db.close();
        Log.i(DEBUG_DB, "deleteGameScore() with \"game_id\": " + game.getId());
        return res;
    }
}

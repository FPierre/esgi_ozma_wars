// package com.application.android.esgi.ozma.wars.database;

// import android.content.ContentValues;
// import android.content.Context;
// import android.database.Cursor;
// import android.database.sqlite.SQLiteDatabase;
// import android.database.sqlite.SQLiteOpenHelper;
// import android.util.Log;

// // import models;

// import java.util.ArrayList;

// /**
//   * ---- SQLiteHandler
//   * Object: SQLite database
//   * Used by: OzmaWarsActivity
//   *
//   * @author Pierre (Pierre Flauder) &amp; Fllo (Florent Blot)
// **/
// public class SQLiteHandler extends SQLiteOpenHelper {

//     private static final int DATABASE_VERSION = 1;
//     private static final String DATABASE_NAME = "OzmaDatabase";
//     private static final String TABLE_GAME_NAME = "OzmaGame";

//     private static final String KEY_DB_ID = "id";

//     private static final String[] COLUMNS = {   
//                                                 KEY_GAME_ID
//                                                 // ...
//                                             };

//     /**
//      * @param context to use to open or create the database
//      * - "name" of the database file, or null for an in-memory database
//      * - "factory" to use for creating cursor objects, or null for the default
//      * - "version" number of the database (starting at 1); if the database is older,
//      *     {@link #onUpgrade} will be used to upgrade the database; if the database is
//      *     newer, {@link #onDowngrade} will be used to downgrade the database
//      **/
//     public SQLiteHandler(Context context) {
//         super(context, DATABASE_NAME, null, 1);
//         Log.i("//-- SQLITE:", "SQLiteHandler.Constructor");
//     }

//     @Override
//     public void onCreate(SQLiteDatabase db) {
//         String CREATE_TABLE = "CREATE TABLE " + TABLE_GAME_NAME
//                 + " ( id INTEGER PRIMARY KEY AUTOINCREMENT, ";    // Id auto-increment (Integer)
//                 // ...

//         db.execSQL(CREATE_TABLE);
//         Log.i("//-- METHOD SQLITE:", "SQLiteHandler.onCreate()");
//     }

//     @Override
//     public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
//         db.execSQL("DROP TABLE IF EXISTS " + TABLE_GAME_NAME);
//         this.onCreate(db);
//         Log.i("//-- METHOD SQLITE:", "SQLiteHandler.onUpgrade()");
//     }

//     public long addSpaceShip(SpaceShip spaceship) {
//         SQLiteDatabase db = this.getWritableDatabase();
//         ContentValues values = new ContentValues();
//         values.put(KEY_GAME_ID, spaceship.getId());
//         // ...

//         long res = db.insert(TABLE_GAME_NAME, null, values);
//         db.close();
//         Log.i("///-- METHOD SQLITE:", "SQLiteHandler.addSpaceShip() with \"id\": " + spaceship.getId());
//         return res;
//     }

//     public SpaceShip selectSpaceShip(int id) {
//         SQLiteDatabase db = this.getReadableDatabase();
//         Cursor cursor = db.query(TABLE_GAME_NAME, COLUMNS,
//                 " shapship_id = ?",
//                 new String[] { String.valueOf(id) },
//                 null,   // Group by
//                 null,   // Having
//                 null,   // Order by
//                 null);  // Limit
//         if (cursor != null)
//             cursor.moveToFirst();
//         SpaceShip spaceship = new SpaceShip();
//         spaceship.setId(Integer.parseInt(cursor.getString(cursor.getColumnIndex(KEY_GAME_ID))));
//         // ...

//         if (!cursor.isClosed())
//             cursor.close();

//         Log.i("///-- METHOD SQLITE:", "SQLiteHandler.selectSpaceShip() with \"spaceship_id\": " + id);
//         return spaceship;
//     }

//     public int updateSpaceShip(SpaceShip spaceship) {
//         SQLiteDatabase db = this.getWritableDatabase();
//         ContentValues values = new ContentValues();
//         values.put(KEY_GAME_ID, spaceship.getId());
//         // ...

//         int res = db.update(TABLE_GAME_NAME, values, "spaceship_id = ?",
//                 new String[]{String.valueOf(spaceship.getId())});
//         db.close();
//         Log.i("///-- METHOD SQLITE:", "SQLiteHandler.updateSpaceShip() with \"id\": " + spaceship.getId());
//         return res;
//     }

//     public ArrayList<SpaceShip> getSpaceShips() {
//         ArrayList<SpaceShip> spaceship = new ArrayList<SpaceShip>();
//         String query = "SELECT  * FROM " + TABLE_GAME_NAME;
//         SQLiteDatabase db = this.getReadableDatabase();
//         Cursor cursor = db.rawQuery(query, null);
//         SpaceShip spaceship = null;
//         if (cursor.spaceship()) {
//             do {
//                 spaceship = new SpaceShip();
//                 spaceship.setId(Integer.parseInt(cursor.getString(cursor.getColumnIndex(KEY_GAME_ID))));
//                 // ...
//                 spaceship.add(spaceship);
//             } while (cursor.moveToNext());
//         }

//         if (cursor != null && !cursor.isClosed())
//             cursor.close();

//         Log.i("///-- METHOD SQLITE:", "SQLiteHandler.getSpaceShips() (list contains " + movies.size() + " movies)");
//         return movies;
//     }

//     public int deleteSpaceShip(int id) {
//         Log.i("///-- METHOD SQLITE:", "SQLiteHandler.deleteSpaceShip() with \"spaceship_id\": " + id);
//         SQLiteDatabase db = this.getWritableDatabase();
//         int res = db.delete(TABLE_GAME_NAME, " spaceship_id = ?", new String[]{String.valueOf(id)});
//         db.close();
//         return res;
//     }
// }

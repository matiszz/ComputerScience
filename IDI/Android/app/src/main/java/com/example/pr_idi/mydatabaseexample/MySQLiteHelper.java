package com.example.pr_idi.mydatabaseexample;

/**
 * MySQLiteHelper
 * Created by pr_idi on 10/11/16.
 */
import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.util.Log;

public class MySQLiteHelper extends SQLiteOpenHelper {

    public static final String TABLE_COINS = "coins";
    public static final String COLUMN_ID = "_id";
    public static final String COLUMN_CURRENCY = "currency";
    public static final String COLUMN_VALUE = "value";
    public static final String COLUMN_YEAR = "year";
    public static final String COLUMN_COUNTRY = "country";
    public static final String COLUMN_DESCRIPTION = "description";


    private static final String DATABASE_NAME = "coins.db";
    private static final int DATABASE_VERSION = 1;

    // Database creation sql statement
    private static final String DATABASE_CREATE = "create table " + TABLE_COINS + "( "
            + COLUMN_ID + " integer primary key autoincrement, "
            + COLUMN_CURRENCY + " text not null, "
            + COLUMN_VALUE + " real not null, "
            + COLUMN_YEAR + " integer, "
            + COLUMN_COUNTRY + " text not null, "
            + COLUMN_DESCRIPTION + " text"
            + ");";

    public MySQLiteHelper(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }

    @Override
    public void onCreate(SQLiteDatabase database) {
        database.execSQL(DATABASE_CREATE);
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        Log.w(MySQLiteHelper.class.getName(),
                "Upgrading database from version " + oldVersion + " to "
                        + newVersion + ", which will destroy all old data");
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_COINS);
        onCreate(db);
    }

}
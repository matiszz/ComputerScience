package com.example.pr_idi.mydatabaseexample;


import java.util.List;
import java.util.Random;

import android.app.ListActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;

public class MainActivity extends ListActivity {
    private CoinData coinData;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        coinData = new CoinData(this);
        coinData.open();

        List<Coin> values = coinData.getAllCoins();

        // use the SimpleCursorAdapter to show the
        // elements in a ListView
        ArrayAdapter<Coin> adapter = new ArrayAdapter<>(this,
                android.R.layout.simple_list_item_1, values);
        setListAdapter(adapter);
    }

    // Basic method to add pseudo-random list of books so that
    // you have an example of insertion and deletion

    // Will be called via the onClick attribute
    // of the buttons in main.xml
    public void onClick(View view) {
        @SuppressWarnings("unchecked")
        ArrayAdapter<Coin> adapter = (ArrayAdapter<Coin>) getListAdapter();
        Coin coin;
        switch (view.getId()) {
            case R.id.add:
                String[] newCoins = new String[] { "Euro", "Dòlar", "Ien", "Lliura esterlina"};
                double[] newValues = new double[] { 0.01, 0.05, 0.10, 0.50, 1 };

                int c = new Random().nextInt(4);
                int v = new Random().nextInt(5);

                // save the new book to the database
                if (c == 2) {
                    coin = coinData.createCoin(newCoins[c], newValues[v]*100);
                }
                else {
                    coin = coinData.createCoin(newCoins[c], newValues[v]);
                }

                // After I get the book data, I add it to the adapter
                adapter.add(coin);
                break;
            case R.id.delete:
                if (getListAdapter().getCount() > 0) {
                    coin = (Coin) getListAdapter().getItem(0);
                    coinData.deleteCoin(coin);
                    adapter.remove(coin);
                }
                break;
        }
        adapter.notifyDataSetChanged();
    }

    // Life cycle methods. Check whether it is necessary to reimplement them

    @Override
    protected void onResume() {
        coinData.open();
        super.onResume();
    }

    // Life cycle methods. Check whether it is necessary to reimplement them

    @Override
    protected void onPause() {
        coinData.close();
        super.onPause();
    }

}
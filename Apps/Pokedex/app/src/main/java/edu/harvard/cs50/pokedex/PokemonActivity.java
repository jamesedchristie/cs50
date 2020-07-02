package edu.harvard.cs50.pokedex;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.Volley;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.net.URL;

public class PokemonActivity extends AppCompatActivity {
    private TextView nameTextView;
    private TextView numberTextView;
    private TextView type1TextView;
    private TextView type2TextView;
    private TextView descriptionTextView;
    private String url;
    private String descriptionUrl;
    private String name;
    public static int ident;
    private RequestQueue requestQueue;
    private Button catch_button;
    private ImageView imageView;



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_pokemon);

        requestQueue = Volley.newRequestQueue(getApplicationContext());
        url = getIntent().getStringExtra("url");
        name = getIntent().getStringExtra("name");
        nameTextView = findViewById(R.id.pokemon_name);
        numberTextView = findViewById(R.id.pokemon_number);
        type1TextView = findViewById(R.id.pokemon_type1);
        type2TextView = findViewById(R.id.pokemon_type2);
        catch_button = findViewById(R.id.catch_button);
        imageView = findViewById(R.id.picture);
        descriptionTextView = findViewById(R.id.pokemon_description);

        load();
    }

    public void load() {
        type1TextView.setText("");
        type2TextView.setText("");

        if (getPreferences(Context.MODE_PRIVATE).getBoolean(name, false)) {
            catch_button.setText("Release");
        }
        else {
            catch_button.setText("Catch");
        }

        JsonObjectRequest request = new JsonObjectRequest(Request.Method.GET, url, null, new Response.Listener<JSONObject>() {
            @Override
            public void onResponse(JSONObject response) {
                try {
                    ident = response.getInt("id");
                    String baseUrl = "https://pokeapi.co/api/v2/pokemon-species/";
                    descriptionUrl = baseUrl + ident + "/";

                    final JsonObjectRequest request2 = new JsonObjectRequest(Request.Method.GET, descriptionUrl, null, new Response.Listener<JSONObject>() {
                        @Override
                        public void onResponse(JSONObject response) {
                            try {
                                JSONArray flavorEntries = response.getJSONArray("flavor_text_entries");
                                JSONObject red_entry = flavorEntries.getJSONObject(0);
                                String entry = red_entry.getString("flavor_text");

                                descriptionTextView.setText(entry);
                            } catch (JSONException e) {
                                Log.e("cs50", "Pokemon json error", e);
                            }
                        }
                    }, new Response.ErrorListener() {
                        @Override
                        public void onErrorResponse(VolleyError error) {
                            Log.e("cs50", "Pokemon details error", error);
                        }
                    });

                    requestQueue.add(request2);

                    String name = response.getString("name");
                    nameTextView.setText(name.substring(0, 1).toUpperCase() + name.substring(1));
                    numberTextView.setText(String.format("#%03d", response.getInt("id")));

                    JSONObject pictures = response.getJSONObject("sprites");
                    String image_url = pictures.getString("front_default");
                    new DownloadSpriteTask().execute(image_url);


                    JSONArray typeEntries = response.getJSONArray("types");
                    for (int i = 0; i < typeEntries.length(); i++) {
                        JSONObject typeEntry = typeEntries.getJSONObject(i);
                        int slot = typeEntry.getInt("slot");
                        String type = typeEntry.getJSONObject("type").getString("name");

                        if (slot == 1) {
                            type1TextView.setText(type);
                        }
                        else if (slot == 2) {
                            type2TextView.setText(type);
                        }
                    }
                } catch (JSONException e) {
                    Log.e("cs50", "Pokemon json error", e);
                }
            }
        }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                Log.e("cs50", "Pokemon details error", error);
            }
        });

        requestQueue.add(request);
    }

    public void toggleCatch(View view) {
        if (getPreferences(Context.MODE_PRIVATE).getBoolean(name, false)) {
            getPreferences(Context.MODE_PRIVATE).edit().putBoolean(name, false).apply();;
        }
        else {
            getPreferences(Context.MODE_PRIVATE).edit().putBoolean(name, true).apply();;
        }
        load();
    }

    private class DownloadSpriteTask extends AsyncTask<String, Void, Bitmap> {
        @Override
        protected Bitmap doInBackground(String... strings) {
            try {
                URL url = new URL(strings[0]);
                return BitmapFactory.decodeStream(url.openStream());
            }
            catch (IOException e) {
                Log.e("cs50", "Download sprite error", e);
                return null;
            }
        }

        @Override
        protected void onPostExecute(Bitmap bitmap) {
            imageView.setImageBitmap(Bitmap.createScaledBitmap(bitmap, 500, 500, false));
        }
    }
}

package com.lab.zongjx.projmid;

import android.content.ContentValues;
import android.content.Intent;
import android.database.sqlite.SQLiteDatabase;
import android.graphics.BitmapFactory;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.EventLog;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.sackcentury.shinebuttonlib.ShineButton;

import org.greenrobot.eventbus.EventBus;

public class InfoActivity extends AppCompatActivity {
    private Intent intent;
    private Bundle extras;
    private TextView namea;
    private TextView nameb;
    private TextView namez;
    private TextView sex;
    private TextView major;
    private TextView jiguan;
    private TextView bd;
    private TextView info;
    private ImageView back;
    private ImageView photo;
    private TextView modify;
    private ShineButton like;
    private MyDatabase myDatabase;
    private byte[] in;
    public boolean on;
    public static InfoActivity instance = null;

    @Override
    protected void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        setContentView(R.layout.character_info);
        instance = this;
        on = true;


        namea = (TextView) findViewById(R.id.namea);
        nameb = (TextView) findViewById(R.id.nameb);
        namez = (TextView) findViewById(R.id.namez);
        sex = (TextView) findViewById(R.id.sex);
        major = (TextView) findViewById(R.id.major);
        jiguan = (TextView) findViewById(R.id.jiguan);
        bd = (TextView) findViewById(R.id.bd);
        info = (TextView) findViewById(R.id.info);

        photo = (ImageView) findViewById(R.id.photo);
        back = (ImageView) findViewById(R.id.back1);
        modify = (TextView) findViewById(R.id.modify);
        like = (ShineButton) findViewById(R.id.like);

        intent = this.getIntent();
        extras = intent.getExtras();

        in = extras.getByteArray("bitmap");
        namea.setText(extras.getString("c_name"));
        nameb.setText(extras.getString("c_name"));
        namez.setText(extras.getString("c_sname"));
        sex.setText(extras.getString("c_sex"));
        major.setText(extras.getString("c_major"));
        jiguan.setText(extras.getString("c_jiguan"));
        bd.setText(extras.getString("c_bd"));
        info.setText(extras.getString("c_info"));
        if(extras.getInt("c_photoid") == -1){
            photo.setImageBitmap(BitmapFactory.decodeByteArray(in, 0, in.length));
        }
        else {
            photo.setImageResource(extras.getInt("c_photoid"));
        }

        if(extras.getInt("like") == 1){
            like.setChecked(true);
        }
        else{
            like.setChecked(false);
        }

        back.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                finish();
            }
        });

        myDatabase = new MyDatabase(this,"Character.db",null,1);
        final SQLiteDatabase db = myDatabase.getWritableDatabase();
        like.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ContentValues values = new ContentValues();
                if(like.isChecked()){
                    values.put("like",1);
                }
                else{
                    values.put("like",0);
                }
                db.update("character",values,"name = ?",new String[]{ extras.getString("c_name") });
                EventBus.getDefault().post(new MessageEvent());
            }
        });

        modify.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intentm = new Intent(InfoActivity.this, ModifyActivity.class);
                Bundle extrasm = new Bundle();
                extrasm.putString("c_name",extras.getString("c_name"));
                extrasm.putString("c_sname",extras.getString("c_sname"));
                extrasm.putString("c_sex",extras.getString("c_sex"));
                extrasm.putString("c_major",extras.getString("c_major"));
                extrasm.putString("c_jiguan",extras.getString("c_jiguan"));
                extrasm.putString("c_bd",extras.getString("c_bd"));
                extrasm.putString("c_info",extras.getString("c_info"));
                extrasm.putInt("c_photoid",extras.getInt("c_photoid"));
                extrasm.putInt("index",extras.getInt("index"));
                extrasm.putByteArray("bitmap",in);
                intentm.putExtras(extrasm);
                startActivity(intentm);
            }
        });


    }

    @Override
    public void onStop(){
        super.onStop();
        on = false;
        if(MainActivity.instance.bgm_switch.isChecked()){
            if(ModifyActivity.instance != null){
                if(!ModifyActivity.instance.on){
                    MainActivity.instance.mp.pause();
                }
            }
            else if(SearchResult.instance != null){
                if(!SearchResult.instance.on){
                    MainActivity.instance.mp.pause();
                }
            }
            else if(MainActivity.instance != null){
                if(!MainActivity.instance.on){
                    MainActivity.instance.mp.pause();
                }
            }
            else{
                MainActivity.instance.mp.pause();
            }
        }
    }

    @Override
    public void onPause(){
        super.onPause();
    }

    @Override
    public void  onRestart(){
        super.onRestart();
        on = true;
        if(MainActivity.instance.bgm_switch.isChecked()){
            MainActivity.instance.mp.start();
        }
    }

    @Override
    public void onDestroy(){
        super.onDestroy();
        instance = null;
        on = false;
    }

    @Override
    public void onBackPressed(){
        super.onBackPressed();
        finish();
    }
}

package com.lab.zongjx.projmid;

import android.content.ContentResolver;
import android.content.DialogInterface;
import android.content.Intent;
import android.database.CharArrayBuffer;
import android.database.ContentObserver;
import android.database.Cursor;
import android.database.DataSetObserver;
import android.database.sqlite.SQLiteDatabase;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.view.View;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import org.greenrobot.eventbus.Subscribe;
import org.greenrobot.eventbus.ThreadMode;

import java.util.ArrayList;
import java.util.List;

public class SearchResult extends AppCompatActivity{
    private ImageView close;
    private RecyclerView resultlist;
    private List<MyCharacter> characters;
    private MyAdapter<MyCharacter> myAdapter;
    private MyDatabase myDatabase;
    private Intent intent;
    private Handler mHandler;
    private WebView webView;
    private byte[] in;
    public boolean on;
    public static SearchResult instance = null;


    @Override
    protected void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        setContentView(R.layout.result_layout);
        intent = this.getIntent();
        instance = this;
        on = true;


        close = (ImageView) findViewById(R.id.close);
        close.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                finish();
            }
        });
        myDatabase = new MyDatabase(this,"Character.db",null,1);
        final SQLiteDatabase db = myDatabase.getWritableDatabase();
        resultlist = (RecyclerView) findViewById(R.id.res_list);
        resultlist.setLayoutManager(new LinearLayoutManager(this));
        characters = new ArrayList<MyCharacter>(){{
            Cursor cursor = db.query("character",null,"name LIKE '%"+ intent.getExtras().getString("key") +"%'",null,null,null,null);
            if(cursor.moveToFirst()){
                do {
                    in = cursor.getBlob(cursor.getColumnIndex("bitmap"));
                    add(new MyCharacter(cursor.getString(cursor.getColumnIndex("name"))
                            ,cursor.getString(cursor.getColumnIndex("sex"))
                            ,cursor.getString(cursor.getColumnIndex("sname"))
                            ,cursor.getString(cursor.getColumnIndex("bd"))
                            ,cursor.getString(cursor.getColumnIndex("jiguan"))
                            ,cursor.getString(cursor.getColumnIndex("major"))
                            ,cursor.getInt(cursor.getColumnIndex("photoid"))
                            ,cursor.getString(cursor.getColumnIndex("info"))
                            ,cursor.getInt(cursor.getColumnIndex("like"))
                            ,BitmapFactory.decodeByteArray(in, 0, in.length)));
                } while(cursor.moveToNext());
            }
            else{
                Toast.makeText(getApplicationContext(),"无结果",Toast.LENGTH_SHORT).show();
            }
            cursor.close();
        }};

        myAdapter = new MyAdapter<MyCharacter>(this, R.layout.list_layout, characters) {
            @Override
            public void convert(MyViewHolder holder, MyCharacter myCharacter) {
                TextView name = holder.getView(R.id.list_name);
                name.setText(myCharacter.getC_name());
                TextView major = holder.getView(R.id.list_major);
                major.setText(myCharacter.getC_major());
                ImageView photo = holder.getView(R.id.list_photo);
                if(myCharacter.getC_photoid() == -1){
                    photo.setImageBitmap(myCharacter.getC_bitmap());
                }
                else {
                    photo.setImageResource(myCharacter.getC_photoid());
                }
            }
        };

        resultlist.setAdapter(myAdapter);

        final AlertDialog.Builder alertdialog = new AlertDialog.Builder(this);
        final AlertDialog.Builder alertdialog1 = new AlertDialog.Builder(this);
        final CharSequence[] choice={"取消","查看更多信息"};


        myAdapter.setOnItemClickListener(new MyAdapter.OnItemClickListener() {
            @Override
            public void onClick(int position) {
                Intent intent = new Intent(SearchResult.this, InfoActivity.class);
                Bundle extras = new Bundle();
                extras.putString("c_name",myAdapter.getItem(position).getC_name());
                extras.putString("c_sname",myAdapter.getItem(position).getC_sname());
                extras.putString("c_sex",myAdapter.getItem(position).getC_sex());
                extras.putString("c_major",myAdapter.getItem(position).getC_major());
                extras.putString("c_jiguan",myAdapter.getItem(position).getC_jiguan());
                extras.putString("c_bd",myAdapter.getItem(position).getC_bd());
                extras.putString("c_info",myAdapter.getItem(position).getC_info());
                extras.putInt("c_photoid",myAdapter.getItem(position).getC_photoid());
                extras.putInt("like",myAdapter.getItem(position).getC_like());
                extras.putByteArray("bitmap",in);
                extras.putInt("index",position);
                intent.putExtras(extras);
                startActivity(intent);
            }

            @Override
            public void onLongClick(final int position) {
                alertdialog1.setItems(choice,
                        new DialogInterface.OnClickListener(){
                            @Override
                            public void onClick(DialogInterface dialogInterface, int i) {
                                switch(i){
                                    case 0:

                                        break;
                                    case 1:
                                        Uri uri_info = Uri.parse("https://m.baidu.com/s?wd=" + myAdapter.getItem(position).getC_name());
                                        Intent intent = new Intent(Intent.ACTION_VIEW, uri_info);
                                        startActivity(intent);
                                }
                            }
                        })
                        .create()
                        .show();

            }

            @Override
            public void onItemClick(final int position,View view){

            }
        });

        mHandler = new Handler(){
            @Override
            public void handleMessage(Message msg){
                super.handleMessage(msg);
                switch (msg.what) {
                    case 123: {
                        characters = new ArrayList<MyCharacter>(){{
                            SQLiteDatabase db = myDatabase.getWritableDatabase();
                            Cursor cursor = db.query("character",null,"name LIKE '%"+ intent.getExtras().getString("key") +"%'",null,null,null,null);
                            if(cursor.moveToFirst()){
                                do {
                                   in = cursor.getBlob(cursor.getColumnIndex("bitmap"));
                                    add(new MyCharacter(cursor.getString(cursor.getColumnIndex("name"))
                                            ,cursor.getString(cursor.getColumnIndex("sex"))
                                            ,cursor.getString(cursor.getColumnIndex("sname"))
                                            ,cursor.getString(cursor.getColumnIndex("bd"))
                                            ,cursor.getString(cursor.getColumnIndex("jiguan"))
                                            ,cursor.getString(cursor.getColumnIndex("major"))
                                            ,cursor.getInt(cursor.getColumnIndex("photoid"))
                                            ,cursor.getString(cursor.getColumnIndex("info"))
                                            ,cursor.getInt(cursor.getColumnIndex("like"))
                                            , BitmapFactory.decodeByteArray(in, 0, in.length)));
                                } while(cursor.moveToNext());
                            }
                            cursor.close();
                        }};

                        myAdapter = new MyAdapter<MyCharacter>(getBaseContext(), R.layout.list_layout, characters) {
                            @Override
                            public void convert(MyViewHolder holder, MyCharacter myCharacter) {
                                TextView name = holder.getView(R.id.list_name);
                                name.setText(myCharacter.getC_name());
                                TextView major = holder.getView(R.id.list_major);
                                major.setText(myCharacter.getC_major());
                                ImageView photo = holder.getView(R.id.list_photo);
                                if(myCharacter.getC_photoid() == -1){
                                    photo.setImageBitmap(myCharacter.getC_bitmap());
                                }
                                else {
                                    photo.setImageResource(myCharacter.getC_photoid());
                                }
                            }
                        };

                        myAdapter.setOnItemClickListener(new MyAdapter.OnItemClickListener() {
                            @Override
                            public void onClick(int position) {
                                Intent intent = new Intent(SearchResult.this, InfoActivity.class);
                                Bundle extras = new Bundle();
                                extras.putString("c_name",myAdapter.getItem(position).getC_name());
                                extras.putString("c_sname",myAdapter.getItem(position).getC_sname());
                                extras.putString("c_sex",myAdapter.getItem(position).getC_sex());
                                extras.putString("c_major",myAdapter.getItem(position).getC_major());
                                extras.putString("c_jiguan",myAdapter.getItem(position).getC_jiguan());
                                extras.putString("c_bd",myAdapter.getItem(position).getC_bd());
                                extras.putString("c_info",myAdapter.getItem(position).getC_info());
                                extras.putInt("c_photoid",myAdapter.getItem(position).getC_photoid());
                                extras.putInt("like",myAdapter.getItem(position).getC_like());
                                extras.putByteArray("bitmap",in);
                                extras.putInt("index",position);
                                intent.putExtras(extras);
                                startActivity(intent);
                            }

                            @Override
                            public void onLongClick(final int position) {
                                alertdialog1.setItems(choice,
                                        new DialogInterface.OnClickListener(){
                                            @Override
                                            public void onClick(DialogInterface dialogInterface, int i) {
                                                switch(i){
                                                    case 0:

                                                        break;
                                                    case 1:
                                                        Uri uri_info = Uri.parse("https://m.baidu.com/s?wd=" + myAdapter.getItem(position).getC_name());
                                                        Intent intent = new Intent(Intent.ACTION_VIEW, uri_info);
                                                        startActivity(intent);
                                                }
                                            }
                                        })
                                        .create()
                                        .show();

                            }

                            @Override
                            public void onItemClick(final int position,View view){

                            }
                        });

                        resultlist.setAdapter(myAdapter);
                        break;
                    }
                }
            }
        };


    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onMessageEvent(MessageEvent event){
        Toast.makeText(getApplicationContext(),"操作成功",Toast.LENGTH_SHORT).show();
        mHandler.obtainMessage(123).sendToTarget();
    }


    @Override
    public void onStop(){
        super.onStop();
        on = false;
        if(MainActivity.instance.bgm_switch.isChecked()){
            if(InfoActivity.instance != null) {
                if (!InfoActivity.instance.on) {
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

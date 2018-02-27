package com.lab.zongjx.projmid;

import android.app.Dialog;
import android.content.ContentValues;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.database.sqlite.SQLiteDatabase;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.media.MediaPlayer;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.provider.ContactsContract;
import android.provider.MediaStore;
import android.support.constraint.ConstraintLayout;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.inputmethod.InputMethodManager;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.ListAdapter;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.TextView;
import android.widget.Toast;

import org.greenrobot.eventbus.EventBus;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;

public class ModifyActivity extends AppCompatActivity {

    private ConstraintLayout constraintLayout;
    private ImageView back;
    private ImageView m_photo;
    private EditText name;
    private EditText sname;
    private EditText jiguan;
    private EditText bd;
    private EditText info;
    private RadioGroup sex;
    private RadioGroup exist;
    private RadioGroup major;
    private TextView confirm;
    private Intent intent;
    private MyDatabase myDatabase;
    private boolean isCreate;
    private int index;
    private String NAME;
    private int photoid;
    public boolean on;
    private Uri imageUri;
    private byte[] in;
    public static final int CROP_PHOTO = 2;
    public static ModifyActivity instance = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.modify_info);
        instance = this;
        on = true;
        in  = null;

        myDatabase = new MyDatabase(this,"Character.db",null,1);
        final SQLiteDatabase db = myDatabase.getWritableDatabase();

        constraintLayout = (ConstraintLayout) findViewById(R.id.free_space2);
        intent = this.getIntent();


        photoid = R.mipmap.noone;
        back = (ImageView) findViewById(R.id.back2);
        confirm = (TextView) findViewById(R.id.confirm);
        m_photo = (ImageView) findViewById(R.id.mod_photo);
        name = (EditText) findViewById(R.id.mod_editname);
        sname = (EditText) findViewById(R.id.mod_editsname);
        jiguan = (EditText) findViewById(R.id.mod_editjiguan);
        bd = (EditText) findViewById(R.id.mod_editshenzu);
        info = (EditText) findViewById(R.id.mod_editjianjie);
        sex = (RadioGroup) findViewById(R.id.mod_editsex);
        exist = (RadioGroup) findViewById(R.id.mod_editexist);
        major = (RadioGroup) findViewById(R.id.mod_editzhenying);

        m_photo.requestFocus();

        constraintLayout.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                constraintLayout.setFocusable(true);
                constraintLayout.setFocusableInTouchMode(true);
                constraintLayout.requestFocus();
                InputMethodManager imm = (InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE);
                imm.hideSoftInputFromWindow(constraintLayout.getWindowToken(), 0);
                return false;
            }
        });

        back.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                finish();
            }
        });


        final AlertDialog.Builder alertdialog = new AlertDialog.Builder(this);
        final CharSequence[] choice={"从内置图片库选择","从相册选择"};
        final Dialog dialog = new Dialog(this);
        final View dialog_view = LayoutInflater.from(this).inflate(R.layout.dialog_layout,null);
        m_photo.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                alertdialog.setItems(choice,
                        new DialogInterface.OnClickListener(){
                            @Override
                            public void onClick(DialogInterface dialogInterface, int i) {
                                switch(i){
                                    case 0:
                                        dialog.setContentView(dialog_view);
                                        dialog.setTitle("选择图片");
                                        dialog.show();
                                        final ImageView img1 = (ImageView) dialog_view.findViewById(R.id.img1);
                                        final ImageView img2 = (ImageView) dialog_view.findViewById(R.id.img2);
                                        final ImageView img3 = (ImageView) dialog_view.findViewById(R.id.img3);
                                        final ImageView img4 = (ImageView) dialog_view.findViewById(R.id.img4);
                                        final ImageView img5 = (ImageView) dialog_view.findViewById(R.id.img5);
                                        final ImageView img6 = (ImageView) dialog_view.findViewById(R.id.img6);
                                        final ImageView img7 = (ImageView) dialog_view.findViewById(R.id.img7);
                                        final ImageView img8 = (ImageView) dialog_view.findViewById(R.id.img8);
                                        final ImageView img9 = (ImageView) dialog_view.findViewById(R.id.img9);
                                        img1.setOnClickListener(new View.OnClickListener() {
                                            @Override
                                            public void onClick(View v) {
                                                dialog.dismiss();
                                                m_photo.setImageResource(R.mipmap.nan);
                                                photoid = R.mipmap.nan;
                                            }
                                        });
                                        img2.setOnClickListener(new View.OnClickListener() {
                                            @Override
                                            public void onClick(View v) {
                                                dialog.dismiss();
                                                m_photo.setImageResource(R.mipmap.noone);
                                                photoid = R.mipmap.noone;
                                            }
                                        });
                                        img3.setOnClickListener(new View.OnClickListener() {
                                            @Override
                                            public void onClick(View v) {
                                                dialog.dismiss();
                                                m_photo.setImageResource(R.mipmap.nv);
                                                photoid = R.mipmap.nv;
                                            }
                                        });
                                        img4.setOnClickListener(new View.OnClickListener() {
                                            @Override
                                            public void onClick(View v) {
                                                dialog.dismiss();
                                                m_photo.setImageResource(R.mipmap.liubei);
                                                photoid = R.mipmap.liubei;
                                            }
                                        });
                                        img5.setOnClickListener(new View.OnClickListener() {
                                            @Override
                                            public void onClick(View v) {
                                                dialog.dismiss();
                                                m_photo.setImageResource(R.mipmap.caocao);
                                                photoid = R.mipmap.caocao;
                                            }
                                        });
                                        img6.setOnClickListener(new View.OnClickListener() {
                                            @Override
                                            public void onClick(View v) {
                                                dialog.dismiss();
                                                m_photo.setImageResource(R.mipmap.daqiao);
                                                photoid = R.mipmap.daqiao;
                                            }
                                        });
                                        img7.setOnClickListener(new View.OnClickListener() {
                                            @Override
                                            public void onClick(View v) {
                                                dialog.dismiss();
                                                m_photo.setImageResource(R.mipmap.sunce);
                                                photoid = R.mipmap.sunce;
                                            }
                                        });
                                        img8.setOnClickListener(new View.OnClickListener() {
                                            @Override
                                            public void onClick(View v) {
                                                dialog.dismiss();
                                                m_photo.setImageResource(R.mipmap.diaochan);
                                                photoid = R.mipmap.diaochan;
                                            }
                                        });
                                        img9.setOnClickListener(new View.OnClickListener() {
                                            @Override
                                            public void onClick(View v) {
                                                dialog.dismiss();
                                                m_photo.setImageResource(R.mipmap.xiaoqiao);
                                                photoid = R.mipmap.xiaoqiao;
                                            }
                                        });
                                        break;
                                    case 1:
                                        File outputImage = new File(Environment.
                                                getExternalStorageDirectory(), "output_image.jpg");
                                        try {
                                            if (outputImage.exists()) {
                                                outputImage.delete();
                                            }
                                            outputImage.createNewFile();
                                        } catch (IOException e) {
                                            e.printStackTrace();
                                        }
                                        imageUri = Uri.fromFile(outputImage);
                                        Intent intent = new Intent("android.intent.action.GET_CONTENT");
                                        intent.setType("image/*");
                                        intent.putExtra("crop", true);
                                        intent.putExtra("scale", true);
                                        intent.putExtra(MediaStore.EXTRA_OUTPUT, imageUri);
                                        startActivityForResult(intent,CROP_PHOTO);
                                        break;
                                }
                            }
                        })
                        .create()
                        .show();
            }
        });



        if(intent.getExtras() == null){
            isCreate = true;
            Toast.makeText(getApplicationContext(),"创建新词条",Toast.LENGTH_SHORT).show();
        }
        else{
            Bundle extras = intent.getExtras();
            in = extras.getByteArray("bitmap");
            NAME = extras.getString("c_name");
            index = extras.getInt("index");
            isCreate = false;
            if(extras.getInt("c_photoid") == -1){
                m_photo.setImageBitmap(BitmapFactory.decodeByteArray(in, 0, in.length));
            }
            else{
                m_photo.setImageResource(extras.getInt("c_photoid"));
            }
            name.setText(extras.getString("c_name"));
            sname.setText(extras.getString("c_sname"));
            jiguan.setText(extras.getString("c_jiguan"));
            bd.setText(extras.getString("c_bd"));
            info.setText(extras.getString("c_info"));
            if(extras.getString("c_sex") != null){
                switch (extras.getString("c_sex").charAt(0)){
                    case '男':{
                        sex.check(R.id.btn1);
                        break;
                    }
                    case '女':{
                        sex.check(R.id.btn2);
                        break;
                    }
                    default:{
                        break;
                    }
                }
                switch (extras.getString("c_sex").charAt(3)){
                    case '史':{
                        exist.check(R.id.btn3);
                        break;
                    }
                    case '虚':{
                        exist.check(R.id.btn4);
                        break;
                    }
                    default:{
                        break;
                    }
                }
            }
            if(extras.getString("c_major") != null){
                switch (extras.getString("c_major").charAt(0)){
                    case '蜀':{
                        major.check(R.id.btn5);
                        break;
                    }
                    case '魏':{
                        major.check(R.id.btn6);
                        break;
                    }
                    case '吴':{
                        major.check(R.id.btn7);
                        break;
                    }
                    case '群':{
                        major.check(R.id.btn8);
                        break;
                    }
                    default:{
                        break;
                    }
                }
            }

        }

        confirm.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(name.getText().toString().isEmpty()){
                    Toast.makeText(getApplicationContext(),"姓名不能为空！",Toast.LENGTH_SHORT).show();
                }
                else{
                    ContentValues values = new ContentValues();
                    values.put("name",name.getText().toString());
                    values.put("sname",sname.getText().toString());
                    values.put("jiguan",jiguan.getText().toString());
                    values.put("bd",bd.getText().toString());
                    values.put("info",info.getText().toString());
                    String sexandexist = "";
                    String majorfor = "";
                    switch (sex.getCheckedRadioButtonId()){
                        case R.id.btn1:{
                            sexandexist = sexandexist + "男  ";
                            break;
                        }
                        case R.id.btn2:{
                            sexandexist = sexandexist + "女  ";
                            break;
                        }
                        default:{
                            sexandexist = sexandexist + "   ";
                            break;
                        }
                    }
                    switch (exist.getCheckedRadioButtonId()){
                        case R.id.btn3:{
                            sexandexist = sexandexist + "史实人物";
                            break;
                        }
                        case R.id.btn4:{
                            sexandexist = sexandexist + "虚构人物";
                            break;
                        }
                        default:{
                            sexandexist = sexandexist + "    ";
                            break;
                        }
                    }
                    switch (major.getCheckedRadioButtonId()){
                        case R.id.btn5:{
                            majorfor = majorfor + "蜀";
                            break;
                        }
                        case R.id.btn6:{
                            majorfor = majorfor + "魏";
                            break;
                        }
                        case R.id.btn7:{
                            majorfor = majorfor + "吴";
                            break;
                        }
                        case R.id.btn8:{
                            majorfor = majorfor + "群";
                            break;
                        }
                        default:{
                            majorfor = majorfor + " ";
                            break;
                        }
                    }
                    if(isCreate){
                        values.put("photoid",photoid);
                        values.put("bitmap","0".getBytes());
                    }
                    values.put("photoid",photoid);
                    if(!isCreate){
                        values.put("bitmap",in);
                    }
                    values.put("sex",sexandexist);
                    values.put("major",majorfor);

                    //////////////////////////////////////////////////////
                    if(!isCreate){                                                              //not create
//                        EventBus.getDefault().post(new MessageEvent(name.getText().toString()
//                                ,sexandexist
//                                ,sname.getText().toString()
//                                ,bd.getText().toString()
//                                ,jiguan.getText().toString()
//                                ,majorfor
//                                ,photoid
//                                ,info.getText().toString()
//                                ,false
//                                ,index));
                        EventBus.getDefault().post(new MessageEvent());
                        db.update("character",values,"name = ?",new String[]{ NAME });
                        InfoActivity.instance.finish();
                    }
                    else{                                                                       //create
//                        EventBus.getDefault().post(new MessageEvent(name.getText().toString()
//                                ,sexandexist
//                                ,sname.getText().toString()
//                                ,bd.getText().toString()
//                                ,jiguan.getText().toString()
//                                ,majorfor
//                                ,photoid
//                                ,info.getText().toString()
//                                ,true
//                                ,-1));
                        EventBus.getDefault().post(new MessageEvent());
                        db.insert("character",null,values);
                    }
                    Toast.makeText(getApplicationContext(),"操作成功",Toast.LENGTH_SHORT).show();
                    finish();
                }
            }
        });


    }

    @Override
    public void onStop(){
        super.onStop();
        if(MainActivity.instance.bgm_switch.isChecked()){
            if(InfoActivity.instance != null){
                if(!InfoActivity.instance.on){
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

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if(requestCode == CROP_PHOTO){
                if (resultCode == RESULT_OK) {
                    try {
                        if(data != null){
                            imageUri = data.getData();
                            Bitmap bitmap = BitmapFactory.decodeStream(getContentResolver().openInputStream(imageUri));
                            m_photo.setImageBitmap(bitmap); // 将裁剪后的照片显示出来
                            photoid = -1;
                            ByteArrayOutputStream baos = new ByteArrayOutputStream();
                            bitmap.compress(Bitmap.CompressFormat.PNG, 100, baos);
                            in = baos.toByteArray();
                        }
                    } catch (FileNotFoundException e) {
                        e.printStackTrace();
                    }
                }
        }
    }
}

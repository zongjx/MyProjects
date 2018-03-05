package com.lab.zongjx.projmid;

import android.graphics.Bitmap;
import android.renderscript.Allocation;
import android.util.SparseArray;
import android.widget.ImageView;

public class MyCharacter {
    private String c_name;
    private String c_sex;
    private String c_sname;
    private String c_major;
    private String c_jiguan;
    private String c_bd;
    private String c_info;
    private Bitmap c_bitmap;
    private int c_like;
    private int c_photoid;

    public MyCharacter(String c_name, String c_sex, String c_sname, String c_bd, String c_jiguan, String c_major, int c_photoid, String c_info, int c_like, Bitmap c_bitmap){
        this.c_name = c_name;
        this.c_sex = c_sex;
        this.c_sname = c_sname;
        this.c_major = c_major;
        this.c_jiguan = c_jiguan;
        this.c_bd = c_bd;
        this.c_photoid = c_photoid;
        this.c_info = c_info;
        this.c_like = c_like;
        this.c_bitmap = c_bitmap;
    }

    public String getC_name(){return c_name;}
    public void setC_name(String c_name) {this.c_name = c_name;}

    public String getC_sex() {return c_sex;}
    public void setC_sex(String c_sex) {this.c_sex = c_sex;}

    public String getC_sname() {return c_sname;}
    public void setC_sname(String c_sname) {this.c_sname = c_sname;}

    public String getC_major() {return c_major;}
    public void setC_major(String c_major) {this.c_major = c_major;}

    public String getC_jiguan() {return c_jiguan;}
    public void setC_jiguan(String c_jiguan) {this.c_jiguan = c_jiguan;}

    public String getC_bd() {return c_bd;}
    public void setC_bd(String c_bd) {this.c_bd = c_bd;}

    public String getC_info() {return c_info;}
    public void setC_info(String c_info) {this.c_info = c_info;}

    public int getC_photoid() {return c_photoid;}
    public void setC_photoid(int c_photoid) {this.c_photoid = c_photoid;}

    public int getC_like() {return c_like;}
    public void setC_like(int c_like) {this.c_like = c_like;}

    public Bitmap getC_bitmap() {return c_bitmap;}
    public void setC_bitmap(Bitmap c_bitmap) {this.c_bitmap = c_bitmap;}

}

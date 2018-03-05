package com.lab.zongjx.projmid;

import android.app.Activity;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.view.animation.AlphaAnimation;
import android.view.animation.Animation;
import android.view.animation.AnimationSet;
import android.view.animation.ScaleAnimation;
import android.view.animation.TranslateAnimation;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import java.security.Principal;

public class AnimationActivity extends Activity {
    private ImageView image1;
    private ImageView image2;
    private ImageView image3;
    private Button button;
    private TextView textView;
    private boolean flag;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_start);
        flag = false;
        image1 = (ImageView) findViewById(R.id.image1);
        image2 = (ImageView) findViewById(R.id.image2);
        image3 = (ImageView) findViewById(R.id.image3);
        button = (Button) findViewById(R.id.button);
        textView = (TextView) findViewById(R.id.text);


        AnimationSet animationSet2 = new AnimationSet(true);
        AnimationSet animationSet3 = new AnimationSet(true);
        AnimationSet animationSet4 = new AnimationSet(true);
        final AlphaAnimation alphaAnimation2 = new AlphaAnimation(0,1);
        final AlphaAnimation alphaAnimation3 = new AlphaAnimation(0,1);
        final AlphaAnimation alphaAnimation4 = new AlphaAnimation(0,1);
        final AlphaAnimation alphaAnimation5 = new AlphaAnimation(0,0);
        alphaAnimation2.setDuration(4000);
        alphaAnimation3.setDuration(4000);
        alphaAnimation4.setDuration(4000);
        alphaAnimation5.setDuration(4000);
        final TranslateAnimation translateAnimation2 = new TranslateAnimation(Animation.RELATIVE_TO_SELF,0f,Animation.RELATIVE_TO_SELF,0f,Animation.RELATIVE_TO_SELF,-2f,Animation.RELATIVE_TO_SELF,0f);
        final TranslateAnimation translateAnimation3 = new TranslateAnimation(Animation.RELATIVE_TO_SELF,1f,Animation.RELATIVE_TO_SELF,0f,Animation.RELATIVE_TO_SELF,1f,Animation.RELATIVE_TO_SELF,0f);
        final TranslateAnimation translateAnimation4 = new TranslateAnimation(Animation.RELATIVE_TO_SELF,-1f,Animation.RELATIVE_TO_SELF,0f,Animation.RELATIVE_TO_SELF,1f,Animation.RELATIVE_TO_SELF,0f);
        translateAnimation2.setDuration(4000);
        translateAnimation3.setDuration(4000);
        translateAnimation4.setDuration(4000);
        animationSet2.addAnimation(alphaAnimation2);
        animationSet2.addAnimation(translateAnimation2);
        animationSet3.addAnimation(alphaAnimation2);
        animationSet3.addAnimation(translateAnimation3);
        animationSet4.addAnimation(alphaAnimation2);
        animationSet4.addAnimation(translateAnimation4);
        animationSet2.setFillAfter(true);
        animationSet3.setFillAfter(true);
        animationSet4.setFillAfter(true);
        image1.startAnimation(animationSet2);
        image2.startAnimation(animationSet3);
        image3.startAnimation(animationSet4);
        textView.startAnimation(alphaAnimation5);
        button.startAnimation(alphaAnimation5);

        animationSet2.setAnimationListener(new Animation.AnimationListener() {
            @Override
            public void onAnimationStart(Animation animation) {

            }

            @Override
            public void onAnimationEnd(Animation animation) {
                final AnimationSet animationSet1 = new AnimationSet(true);
                final AlphaAnimation alphaAnimation1 = new AlphaAnimation(0,1);
                alphaAnimation1.setDuration(2000);
                final TranslateAnimation translateAnimation1 = new TranslateAnimation(Animation.RELATIVE_TO_SELF,0f,Animation.RELATIVE_TO_SELF,0f,Animation.RELATIVE_TO_SELF,1f,Animation.RELATIVE_TO_SELF,0f);
                translateAnimation1.setDuration(2000);
                animationSet1.addAnimation(alphaAnimation1);
                animationSet1.addAnimation(translateAnimation1);
                animationSet1.setFillAfter(true);
                textView.startAnimation(animationSet1);
                button.startAnimation(animationSet1);
            }

            @Override
            public void onAnimationRepeat(Animation animation) {

            }
        });

        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(AnimationActivity.this,MainActivity.class);
                startActivity(intent);
                finish();
            }
        });

    }

    @Override
    public void onDestroy(){
        super.onDestroy();
    }
}

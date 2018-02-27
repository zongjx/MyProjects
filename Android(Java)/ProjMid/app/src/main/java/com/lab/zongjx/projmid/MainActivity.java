package com.lab.zongjx.projmid;

import android.annotation.SuppressLint;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.graphics.BitmapFactory;
import android.media.MediaPlayer;
import android.media.SoundPool;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.provider.ContactsContract;
import android.support.annotation.NonNull;
import android.support.constraint.ConstraintLayout;
import android.support.design.widget.BottomNavigationView;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.NavigationView;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.view.WindowManager;
import android.view.inputmethod.InputMethodManager;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.SearchView;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;

import com.getbase.floatingactionbutton.FloatingActionsMenu;

import org.greenrobot.eventbus.EventBus;
import org.greenrobot.eventbus.Subscribe;
import org.greenrobot.eventbus.ThreadMode;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class MainActivity extends AppCompatActivity {

    private ConstraintLayout constraintLayout;
    private FrameLayout layout_search;
    private FrameLayout layout_dictionary;
    private FrameLayout layout_setting;
    private FrameLayout layout_favorites;
    private List<MyCharacter> characters;
    private List<MyCharacter> favorites;
    private MyAdapter<MyCharacter> myAdapter;
    private MyAdapter<MyCharacter> myAdapter_f;
    private RecyclerView diclist;
    private RecyclerView favoriteslist;
    private android.widget.SearchView searchView;
    private MyDatabase myDatabase;
    private ImageView delete;
    private ImageView create;
    private TextView showscore;
    private ListView lv;
    private ArrayList<String> arrayList;
    public MediaPlayer mp;
    public CheckBox bgm_switch;
    public CheckBox game_switch;
    private ImageView liubei;
    private ImageView start_game;
    private boolean isGamePlaying;
    private ImageView stop;
    private com.getbase.floatingactionbutton.FloatingActionButton sort_quan;
    private com.getbase.floatingactionbutton.FloatingActionButton sort_shu;
    private com.getbase.floatingactionbutton.FloatingActionButton sort_wei;
    private com.getbase.floatingactionbutton.FloatingActionButton sort_wu;
    private com.getbase.floatingactionbutton.FloatingActionButton sort_qun;
    private int sort_mode;
    private SeekBar speed;
    public Handler mHandler;
    public boolean on;
    public boolean on_delete;
    private boolean game_dis;
    private SoundPool soundPool;//声明一个SoundPool
    private int soundID;//创建某个声音对应的音频ID
    private ConstraintLayout free_space4;
    private int score;
    private byte[] in;
    private WebView webView;
    public static MainActivity instance = null;

    private BottomNavigationView.OnNavigationItemSelectedListener mOnNavigationItemSelectedListener
            = new BottomNavigationView.OnNavigationItemSelectedListener() {

        @Override
        public boolean onNavigationItemSelected(@NonNull MenuItem item) {
            switch (item.getItemId()) {
                case R.id.navigation_home:{
                    layout_search.setVisibility(View.VISIBLE);
                    layout_dictionary.setVisibility(View.GONE);
                    layout_favorites.setVisibility(View.GONE);
                    layout_setting.setVisibility(View.GONE);
                    return true;
                }
                case R.id.navigation_dashboard:
                    layout_search.setVisibility(View.GONE);
                    layout_dictionary.setVisibility(View.VISIBLE);
                    layout_favorites.setVisibility(View.GONE);
                    layout_setting.setVisibility(View.GONE);
                    return true;
                case R.id.navigation_favorites:
                    layout_search.setVisibility(View.GONE);
                    layout_dictionary.setVisibility(View.GONE);
                    layout_favorites.setVisibility(View.VISIBLE);
                    layout_setting.setVisibility(View.GONE);
                    return true;
                case R.id.navigation_notifications:
                    layout_search.setVisibility(View.GONE);
                    layout_dictionary.setVisibility(View.GONE);
                    layout_favorites.setVisibility(View.GONE);
                    layout_setting.setVisibility(View.VISIBLE);
                    return true;
            }
            return false;
        }

    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        instance = this;
        on = true;
        on_delete = false;
        sort_mode = 1;
        game_dis = true;
        initSound();

        layout_search = (FrameLayout) findViewById(R.id.search);
        layout_dictionary = (FrameLayout) findViewById(R.id.dictionary);
        layout_setting = (FrameLayout) findViewById(R.id.setting);
        layout_favorites = (FrameLayout) findViewById(R.id.favorites);
        free_space4 = (ConstraintLayout) findViewById(R.id.free_space4);
        final BottomNavigationView navigation = (BottomNavigationView) findViewById(R.id.navigation);
        navigation.setOnNavigationItemSelectedListener(mOnNavigationItemSelectedListener);

        myDatabase = new MyDatabase(this,"Character.db",null,1);
        final SQLiteDatabase db = myDatabase.getWritableDatabase();


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        constraintLayout = (ConstraintLayout) findViewById(R.id.free_space);
        searchView = (SearchView) findViewById(R.id.searchview);
        searchView.setSubmitButtonEnabled(true);
        searchView.setQueryHint("请输入关键字");
        arrayList = new ArrayList<String>();
        lv = (ListView) findViewById(R.id.search_hint);
        lv.setAdapter(new ArrayAdapter<String>(this,android.R.layout.simple_list_item_1,arrayList));

        searchView.setOnQueryTextListener(new SearchView.OnQueryTextListener() {
            @Override
            public boolean onQueryTextSubmit(String query) {
                if (searchView != null) {
                    // 得到输入管理对象
                    InputMethodManager imm = (InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE);
                    if (imm != null) {
                        // 这将让键盘在所有的情况下都被隐藏，但是一般我们在点击搜索按钮后，输入法都会乖乖的自动隐藏的。
                        imm.hideSoftInputFromWindow(searchView.getWindowToken(), 0); // 输入法如果是显示状态，那么就隐藏输入法
                        Intent intent = new Intent(MainActivity.this,SearchResult.class);
                        Bundle extras = new Bundle();
                        extras.putString("key",searchView.getQuery().toString());
                        intent.putExtras(extras);
                        startActivity(intent);
                    }
                    searchView.clearFocus(); // 不获取焦点
                }
                return true;
            }

            @Override
            public boolean onQueryTextChange(String newText) {
                if(!newText.isEmpty()){
                    lv.setVisibility(View.VISIBLE);
                    free_space4.setVisibility(View.GONE);
                }
                else {
                    lv.setVisibility(View.GONE);
                    if(game_dis){
                        free_space4.setVisibility(View.VISIBLE);
                    }
                }
                arrayList = new ArrayList<String>();
                Cursor cursor = db.query("character",null,"name LIKE '%"+ newText +"%'",null,null,null,null);
                if(cursor.moveToFirst()){
                    do{
                        arrayList.add(cursor.getString(cursor.getColumnIndex("name")));
                    } while(cursor.moveToNext());
                }
                cursor.close();
                lv.setAdapter(new ArrayAdapter<String>(getBaseContext(),android.R.layout.simple_list_item_1,arrayList));
                lv.setOnItemClickListener(new AdapterView.OnItemClickListener() {
                    @Override
                    public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                        searchView.setQuery(lv.getAdapter().getItem(position).toString(),true);
                    }
                });
                return false;
            }
        });


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


        final TextView intro1 = (TextView) findViewById(R.id.intro1);
        final TextView intro2 = (TextView) findViewById(R.id.intro2);
        WindowManager wm = this.getWindowManager();

        final int width = wm.getDefaultDisplay().getWidth();
        final int height = wm.getDefaultDisplay().getHeight();
        score = 0;

        isGamePlaying = false;
        start_game = (ImageView) findViewById(R.id.game_start);
        stop = (ImageView) findViewById(R.id.game_stop);
        speed =  (SeekBar) findViewById(R.id.sudu);
        showscore = (TextView) findViewById(R.id.defen);
        liubei = (ImageView) findViewById(R.id.liubei);
        liubei.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(isGamePlaying){
                    score = score + 1;
                    String ss = String.valueOf(score);
                    showscore.setText(ss);
                    playSound();
                }
            }
        });

        start_game.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(isGamePlaying){
                    start_game.setImageResource(R.drawable.ic_play_circle_filled_black_24dp);
                    intro1.setVisibility(View.VISIBLE);
                    intro2.setVisibility(View.VISIBLE);
                    liubei.setVisibility(View.GONE);
                    isGamePlaying = false;
                }
                else{
                    start_game.setImageResource(R.drawable.ic_pause_circle_filled_black_24dp);
                    intro1.setVisibility(View.GONE);
                    intro2.setVisibility(View.GONE);
                    liubei.setVisibility(View.VISIBLE);
                    isGamePlaying = true;
                }
            }
        });

        stop.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                score = 0;
                showscore.setText("0");
                start_game.setImageResource(R.drawable.ic_play_circle_filled_black_24dp);
                intro1.setVisibility(View.VISIBLE);
                intro2.setVisibility(View.VISIBLE);
                liubei.setVisibility(View.GONE);
                isGamePlaying = false;
            }
        });

        final Handler mgame = new Handler() {
            @Override
            public void handleMessage(Message msg) {
                super.handleMessage(msg);
                switch (msg.what) {
                    case 1: {
                        Random random = new Random();
                        int randomnumx = random.nextInt(width-160);
                        int randomnumy = random.nextInt(width-160);
                        liubei.setX(randomnumx);
                        liubei.setY(randomnumy);
                        break;
                    }
                }
            }
        };

        Thread mThread = new Thread() {
            @Override
            public void run() {
                while (true) {
                    try {
                        Thread.sleep(1000-speed.getProgress());
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                    if (true) {
                        mgame.obtainMessage(1).sendToTarget();
                    }
                }
            }
        };
        mThread.start();
























///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////









///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        sort_quan = (com.getbase.floatingactionbutton.FloatingActionButton) findViewById(R.id.sort_quan);
        sort_shu = (com.getbase.floatingactionbutton.FloatingActionButton) findViewById(R.id.sort_shu);
        sort_wei = (com.getbase.floatingactionbutton.FloatingActionButton) findViewById(R.id.sort_wei);
        sort_wu = (com.getbase.floatingactionbutton.FloatingActionButton) findViewById(R.id.sort_wu);
        sort_qun = (com.getbase.floatingactionbutton.FloatingActionButton) findViewById(R.id.sort_qun);


        sort_quan.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                sort_mode = 1;
                mHandler.obtainMessage(123).sendToTarget();
            }
        });

        sort_shu.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                sort_mode = 2;
                mHandler.obtainMessage(123).sendToTarget();
            }
        });

        sort_wei.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                sort_mode = 3;
                mHandler.obtainMessage(123).sendToTarget();
            }
        });

        sort_wu.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                sort_mode = 4;
                mHandler.obtainMessage(123).sendToTarget();
            }
        });

        sort_qun.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                sort_mode = 5;
                mHandler.obtainMessage(123).sendToTarget();
            }
        });

        EventBus.getDefault().register(this);
        create = (ImageView) findViewById(R.id.create);
        delete = (ImageView) findViewById(R.id.delete);
        diclist = (RecyclerView) findViewById(R.id.dic_list);
        diclist.setLayoutManager(new LinearLayoutManager(this));

        characters = new ArrayList<MyCharacter>(){{

            Cursor cursor;
            switch(sort_mode){
                case 1: {
                    cursor = db.query("character",null,null,null,null,null,null);
                    break;
                }
                case 2: {
                    cursor = db.query("character",null,"major = ?",new String[]{ "蜀" },null,null,null);
                    break;
                }
                case 3: {
                    cursor = db.query("character",null,"major = ?",new String[]{ "魏" },null,null,null);
                    break;
                }
                case 4: {
                    cursor = db.query("character",null,"major = ?",new String[]{ "吴" },null,null,null);
                    break;
                }
                case 5: {
                    cursor = db.query("character",null,"major = ?",new String[]{ "群" },null,null,null);
                    break;
                }
                default: {
                    cursor = db.query("character",null,null,null,null,null,null);
                    break;
                }
            }
//            add(new MyCharacter("劉備", "男  史实人物", "字：玄德", "生卒（161 - 223）", "籍贯：幽州涿郡涿（河北保定市涿州）", "蜀", getResource("liubei"), "　　刘备，蜀汉的开国皇帝，汉景帝之子中山靖王刘胜的后代。刘备少年孤贫，以贩鞋织草席为生。黄巾起义时，刘备与关羽、张飞桃园结义，成为异姓兄弟，一同剿除黄巾，有功，任安喜县尉，不久辞官；董卓乱政之际，刘备随公孙瓒讨伐董卓，三人在虎牢关战败吕布。后诸侯割据，刘备势力弱小，经常寄人篱下，先后投靠过公孙瓒、曹操、袁绍、刘表等人，几经波折，却仍无自己的地盘。赤壁之战前夕，刘备在荆州三顾茅庐，请诸葛亮出山辅助，在赤壁之战中，联合孙权打败曹操，奠定了三分天下的基础。刘备在诸葛亮的帮助下占领荆州，不久又进兵益州，夺取汉中，建立了横跨荆益两州的政权。后关羽战死，荆州被孙权夺取，刘备大怒，于称帝后伐吴，在夷陵之战中为陆逊用火攻打得大败，不久病逝于白帝城，临终托孤于诸葛亮" ));
//            add(new MyCharacter("曹操","男  史实人物","字：孟德","生卒（155 - 220）","籍贯：豫州沛国谯（安徽亳州市亳县）","魏", getResource("caocao"),"    曹操是西园八校尉之一，曾只身行刺董卓，失败后和袁绍共同联合天下诸侯讨伐董卓，后独自发展自身势力，一生中先后战胜了袁术、吕布、张绣、袁绍、刘表、张鲁、马超等割据势力，统一了北方。但是在南下讨伐江东的战役中，曹操在赤壁惨败。后来在和蜀汉的汉中争夺战中，曹操再次无功而返。曹操一生未称帝，他病死后，曹丕继位后不久称帝，追封曹操为魏武皇帝。"));
//            add(new MyCharacter("關羽","男  史实人物","字：云长","生卒（？ - 219）","籍贯：司隶河东郡解（山西运城市临猗县西南）","蜀", getResource("guanyu"),"    因本处势豪倚势凌人，关羽杀之而逃难江湖。闻涿县招军破贼，特来应募。与刘备、张飞桃园结义，羽居其次。使八十二斤青龙偃月刀随刘备东征西讨。虎牢关温酒斩华雄，屯土山降汉不降曹。为报恩斩颜良、诛文丑，解曹操白马之围。后得知刘备音信，过五关斩六将，千里寻兄。刘备平定益州后，封关羽为五虎大将之首，督荆州事。羽起军攻曹，放水淹七军，威震华夏。围樊城右臂中箭，幸得华佗医治，刮骨疗伤。但未曾提防东吴袭荆州，关羽父子败走麦城，突围中被捕，不屈遭害。"));
//            add(new MyCharacter("張飛","男  史实人物","字：益德","生卒（？ - 221）","籍贯：幽州涿郡（河北保定市涿州）","蜀", getResource("zhangfei"),"　　与刘备和关羽桃园结义，张飞居第三。随刘备征讨黄巾，刘备终因功被朝廷受予平原相，后张飞鞭挞欲受赂的督邮。十八路诸侯讨董时，三英战吕布，其勇为世人所知。曹操以二虎竞食之计迫刘备讨袁术，刘备以张飞守徐州，诫禁酒，但还是因此而鞭打曹豹招致吕布东袭。刘备反曹后，反用劫寨计擒曹将刘岱，为刘备所赞。徐州终为曹操所破，张飞与刘备失散，占据古城。误以为降汉的关羽投敌，差点一矛将其杀掉。曹操降荊州后引骑追击，刘备败逃，张飞引二十余骑，立马于长阪桥，吓退曹军数十里。庞统死后刘备召其入蜀，张飞率军沿江而上，智擒巴郡太守严颜并生获之，张飞壮而释放。于葭萌关和马超战至夜间，双方点灯，终大战数百回合。瓦口关之战时扮作醉酒，智破张郃。后封为蜀汉五虎大将。及关羽卒，张飞悲痛万分，每日饮酒鞭打部下，导致为帐下将张达、范强所杀，他们持其首顺流而奔孙权。"));
//            add(new MyCharacter("曹丕","男  史实人物","字：子桓","生卒（187 - 226）","籍贯：豫州沛国谯（安徽亳州市亳县）","魏", getResource("caopi"),"　　在争夺继承权问题上处心积虑，战胜了文才更胜一筹的弟弟曹植，被立为王世子。曹操逝世后，曹丕继位成为魏王，以不参加葬礼之罪逼弟弟曹植写下七步诗，险些将其杀害，又顺利夺下弟弟曹彰的兵权，坐稳了魏王之位。不久，曹丕逼汉献帝让位，代汉称帝，为魏国开国皇帝。刘备伐吴时，曹丕看出刘备要失败，但不听谋士之言，偏要坐山观虎斗，事后又起兵伐吴，结果被徐盛火攻击败。回洛阳后，曹丕大病，临终前托付曹睿给曹真、司马懿等人，终年四十岁。"));
//            add(new MyCharacter("夏侯惇","男  史实人物","字：元让","生卒（？ - 220）","籍贯：豫州沛国谯（安徽亳州市亳县）","魏", getResource("xiahoudun"),"　　曹操从弟。少习枪棒，武艺过人。曹操起兵，夏侯惇率众来投，自此随之征战。曹操讨吕布，惇为布将曹性射其左目，惇拨矢啖睛，杀性，两军无不骇然。后惇常为先锋，杀敌破阵，冲锋在前，立功无数。曹操病笃，惇往见之，于宫门处遇鬼惊倒，自此染病。及曹丕称帝，以惇为大将军。旋之，卒。曹丕为之挂孝。"));
//            add(new MyCharacter("孫策","男  史实人物","字：伯符","生卒（175 - 200）","籍贯：扬州吴郡富春（浙江杭州市富阳）","吴", getResource("sunce"),"　　父坚与荆州牧刘表攻，策时十七，与之相从。策箭射表将陈生。后坚为表将乱箭射死，策回到汉水，闻父尸在彼，乃用俘虏黄祖换之。后往淮南投袁术，深为术所爱。后策图自强，以父所留传国玉玺换术兵，术表策为折冲校尉、殄寇将军。策自此荡平东南，威震三江。破刘繇，挟死一将、喝死一将，人皆呼之为「小霸王」。又匹马于神亭与繇将太史慈酣战数百合，为众人所惊。后策平江东，迁讨逆将军，领会稽太守，封吴侯。曹公惮其强，与之结亲以安其心。后曹公与袁绍相拒于官渡，策阴欲袭许。先是，吴郡太守许贡暗发书与曹公，教徐图策，策知之，杀贡。一日，策行猎，为贡门客所刺，创甚。后又斩杀道士于吉而受其诅咒，伤重而亡，寿仅二十六岁。权称尊号，追谥策曰长沙桓王。"));
//            add(new MyCharacter("周瑜","男  史实人物","字：公瑾","生卒（175 - 210）","籍贯：扬州庐江郡舒（安徽合肥市庐江县西南）","吴", getResource("zhouyu"),"　　偏将军、南郡太守。自幼与孙策交好，策离袁术讨江东，瑜引兵从之。为中郎将，孙策相待甚厚，又同娶二乔。策临终，嘱弟权曰：“外事不决，可问周瑜”。瑜奔丧还吴，与张昭共佐权，并荐鲁肃等，掌军政大事。赤壁战前，瑜自鄱阳归。力主战曹，后于群英会戏蒋干、怒打黄盖行诈降计、后火烧曹军，大败之。后下南郡与曹仁相持，中箭负伤，与诸葛亮较智斗，定假涂灭虢等计，皆为亮破，后气死于巴陵，年三十六岁。临终，上书荐鲁肃代其位，权为其素服吊丧。"));
//            add(new MyCharacter("呂布","男  史实人物","字：奉先","生卒（？ - 198）","籍贯：并州五原郡九原（内蒙古包头市九原区麻池镇西北古城遗址）","群", getResource("lvbu"),"　　吕布是骁勇善战的汉末诸侯，先后跟随丁原、董卓作战，并最终杀死了丁原和董卓。成为独立势力后，吕布与曹操为敌，和刘备、袁术等诸侯时敌时友，最终不敌曹操和刘备的联军，兵败人亡。吕布虽然勇猛，但是少有计策，为人反复无常，唯利是图。在演义中，吕布是天下无双的超一流武将，曾在虎牢关大战刘备、关羽、张飞三人联手，曾一人独斗曹操军六员大将，武艺可谓公认的演义第一。著名的美女貂蝉上演连环计后，成为吕布的妻室。"));
//            add(new MyCharacter("张角","男  史实人物"," ","生卒（？ - 184）","籍贯：冀州巨鹿郡（河北邢台市平乡县）","群", getResource("zhangjiao"),"　　原是个不第的秀才，在山中采药时遇南华老仙，得天书三卷，名为《太平要术》。张角依此书所传道术，开始散施符水，为人治病，徒众发展到数十万。张角遂起了夺取天下得野心，与兄弟张宝、张梁一起起兵造反，声势浩大，但最终被朝廷和各路豪杰镇压。张角病死，黄巾军主力随即覆灭，但仍有很多残党在各地活动。"));
//            add(new MyCharacter("貂蟬","女  虚构人物", " ", "生卒（？ - ？）", "籍贯：？","群", getResource("diaochan"),"　　舍身报国的可敬女子，她为了挽救天下黎民，为了推翻权臣董卓的荒淫统治，受王允所托，上演了可歌可泣的连环计（连环美人计），周旋于两个男人之间，成功的离间了董卓和吕布，最终吕布将董卓杀死，结束了董卓专权的黑暗时期。"));
//            add(new MyCharacter("大喬","女  史实人物"," ","生卒（？ - ？）","籍贯：扬州庐江郡皖（安徽安庆市潜山县）","吴", getResource("daqiao"),"　　江东乔国老有二女，大乔和小乔。大乔有沉鱼落雁之资，倾国倾城之容。孙策征讨江东，攻取皖城，娶大乔为妻。自古美女配英雄，伯符大乔堪绝配。曹操赤壁鏖兵，虎视江东，曾有揽二乔娱暮年，还足平生之愿。"));
//            add(new MyCharacter("小喬","女  史实人物"," ","生卒（？ - ？）","籍贯：扬州庐江郡皖（安徽安庆市潜山县）","吴", getResource("xiaoqiao"),"　　庐江皖县桥国老次女，秀美绝伦，貌压群芳，又琴棋书画无所不通周瑜攻取皖城，迎娶小乔为妻。周郎小乔英雄美女、郎才女貌 ，被流传为千古佳话。"));
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

                ImageView de = holder.getView(R.id.delete_item);
                if(on_delete){
                    de.setVisibility(View.VISIBLE);
                }
                else {
                    de.setVisibility(View.GONE);
                }
            }
        };

        diclist.setAdapter(myAdapter);

        final AlertDialog.Builder alertdialog = new AlertDialog.Builder(this);
        final AlertDialog.Builder alertdialog1 = new AlertDialog.Builder(this);
        final CharSequence[] choice={"删除词条","查看更多信息"};
        final CharSequence[] choice1={"取消","查看更多信息"};


        myAdapter.setOnItemClickListener(new MyAdapter.OnItemClickListener() {

            @Override
            public void onClick(int position) {
                Intent intent = new Intent(MainActivity.this, InfoActivity.class);
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
                                        alertdialog.setTitle("删除词条")
                                                .setMessage("是否要删除词条"+myAdapter.getItem(position).getC_name())
                                                .setPositiveButton("确认"
                                                        , new DialogInterface.OnClickListener() {
                                                            @Override
                                                            public void onClick(DialogInterface dialog, int which) {

                                                                SQLiteDatabase db = myDatabase.getWritableDatabase();
                                                                db.delete("character", "name = ?", new String[] { myAdapter.getItem(position).getC_name() });

                                                                myAdapter.removeItem(position);
                                                                Toast.makeText(getApplicationContext(),
                                                                        "已移除词条",Toast.LENGTH_SHORT).show();
                                                                mHandler.obtainMessage(123).sendToTarget();
                                                            }
                                                        })
                                                .setNegativeButton("取消", new DialogInterface.OnClickListener() {
                                                    @Override
                                                    public void onClick(DialogInterface dialog, int which) {

                                                    }
                                                })
                                                .create();
                                        alertdialog.show();
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
                if(view.getId() == R.id.delete_item){
                    alertdialog.setTitle("删除词条")
                            .setMessage("是否要删除词条"+myAdapter.getItem(position).getC_name())
                            .setPositiveButton("确认"
                                    , new DialogInterface.OnClickListener() {
                                        @Override
                                        public void onClick(DialogInterface dialog, int which) {

                                            SQLiteDatabase db = myDatabase.getWritableDatabase();
                                            db.delete("character", "name = ?", new String[] { myAdapter.getItem(position).getC_name() });

                                            myAdapter.removeItem(position);
                                            Toast.makeText(getApplicationContext(),
                                                    "已移除词条",Toast.LENGTH_SHORT).show();
                                            mHandler.obtainMessage(123).sendToTarget();
                                        }
                                    })
                            .setNegativeButton("取消", new DialogInterface.OnClickListener() {
                                @Override
                                public void onClick(DialogInterface dialog, int which) {

                                }
                            })
                            .create();
                    alertdialog.show();
                }
            }
        });


        delete.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(!on_delete){
                    ImageView delete_item = (ImageView) findViewById(R.id.delete_item);
                    delete_item.setVisibility(View.VISIBLE);
                    myAdapter.notifyDataSetChanged();
                    delete.setImageResource(R.drawable.ic_cancel_white_24dp);
                    on_delete = true;
                }
                else{
                    ImageView delete_item = (ImageView) findViewById(R.id.delete_item);
                    delete_item.setVisibility(View.GONE);
                    myAdapter.notifyDataSetChanged();
                    delete.setImageResource(R.drawable.ic_delete_white_24dp);
                    on_delete = false;
                }
            }
        });

        create.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this,ModifyActivity.class);
                startActivity(intent);
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
                            Cursor cursor;
                            switch(sort_mode){
                                case 1: {
                                    cursor = db.query("character",null,null,null,null,null,null);
                                    break;
                                }
                                case 2: {
                                    cursor = db.query("character",null,"major = ?",new String[]{ "蜀" },null,null,null);
                                    break;
                                }
                                case 3: {
                                    cursor = db.query("character",null,"major = ?",new String[]{ "魏" },null,null,null);
                                    break;
                                }
                                case 4: {
                                    cursor = db.query("character",null,"major = ?",new String[]{ "吴" },null,null,null);
                                    break;
                                }
                                case 5: {
                                    cursor = db.query("character",null,"major = ?",new String[]{ "群" },null,null,null);
                                    break;
                                }
                                default: {
                                    cursor = db.query("character",null,null,null,null,null,null);
                                    break;
                                }
                            }
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

                                ImageView de = holder.getView(R.id.delete_item);
                                if(on_delete){
                                    de.setVisibility(View.VISIBLE);
                                }
                                else {
                                    de.setVisibility(View.GONE);
                                }
                            }
                        };

                        myAdapter.setOnItemClickListener(new MyAdapter.OnItemClickListener() {
                            @Override
                            public void onClick(int position) {
                                Intent intent = new Intent(MainActivity.this, InfoActivity.class);
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
                                                        alertdialog.setTitle("删除词条")
                                                                .setMessage("是否要删除词条"+myAdapter.getItem(position).getC_name())
                                                                .setPositiveButton("确认"
                                                                        , new DialogInterface.OnClickListener() {
                                                                            @Override
                                                                            public void onClick(DialogInterface dialog, int which) {

                                                                                SQLiteDatabase db = myDatabase.getWritableDatabase();
                                                                                db.delete("character", "name = ?", new String[] { myAdapter.getItem(position).getC_name() });

                                                                                myAdapter.removeItem(position);
                                                                                Toast.makeText(getApplicationContext(),
                                                                                        "已移除词条",Toast.LENGTH_SHORT).show();
                                                                                mHandler.obtainMessage(123).sendToTarget();
                                                                            }
                                                                        })
                                                                .setNegativeButton("取消", new DialogInterface.OnClickListener() {
                                                                    @Override
                                                                    public void onClick(DialogInterface dialog, int which) {

                                                                    }
                                                                })
                                                                .create();
                                                        alertdialog.show();
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
                                if(view.getId() == R.id.delete_item){
                                    alertdialog.setTitle("删除词条")
                                            .setMessage("是否要删除词条"+myAdapter.getItem(position).getC_name())
                                            .setPositiveButton("确认"
                                                    , new DialogInterface.OnClickListener() {
                                                        @Override
                                                        public void onClick(DialogInterface dialog, int which) {

                                                            SQLiteDatabase db = myDatabase.getWritableDatabase();
                                                            db.delete("character", "name = ?", new String[] { myAdapter.getItem(position).getC_name() });

                                                            myAdapter.removeItem(position);
                                                            Toast.makeText(getApplicationContext(),
                                                                    "已移除词条",Toast.LENGTH_SHORT).show();
                                                            mHandler.obtainMessage(123).sendToTarget();
                                                        }
                                                    })
                                            .setNegativeButton("取消", new DialogInterface.OnClickListener() {
                                                @Override
                                                public void onClick(DialogInterface dialog, int which) {

                                                }
                                            })
                                            .create();
                                    alertdialog.show();
                                }
                            }
                        });

                        diclist.setAdapter(myAdapter);


                        favorites = new ArrayList<MyCharacter>(){{
                            Cursor cursor = db.query("character",null,"like = ?",new String[]{ "1" },null,null,null);
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
                            cursor.close();
                        }};

                        myAdapter_f = new MyAdapter<MyCharacter>(getBaseContext(), R.layout.list_layout, favorites) {
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

                        myAdapter_f.setOnItemClickListener(new MyAdapter.OnItemClickListener() {
                            @Override
                            public void onClick(int position) {
                                Intent intent = new Intent(MainActivity.this, InfoActivity.class);
                                Bundle extras = new Bundle();
                                extras.putString("c_name",myAdapter_f.getItem(position).getC_name());
                                extras.putString("c_sname",myAdapter_f.getItem(position).getC_sname());
                                extras.putString("c_sex",myAdapter_f.getItem(position).getC_sex());
                                extras.putString("c_major",myAdapter_f.getItem(position).getC_major());
                                extras.putString("c_jiguan",myAdapter_f.getItem(position).getC_jiguan());
                                extras.putString("c_bd",myAdapter_f.getItem(position).getC_bd());
                                extras.putString("c_info",myAdapter_f.getItem(position).getC_info());
                                extras.putInt("c_photoid",myAdapter_f.getItem(position).getC_photoid());
                                extras.putInt("like",myAdapter_f.getItem(position).getC_like());
                                extras.putByteArray("bitmap",in);
                                extras.putInt("index",position);
                                intent.putExtras(extras);
                                startActivity(intent);
                            }

                            @Override
                            public void onLongClick(final int position) {
                                alertdialog1.setItems(choice1,
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

                        favoriteslist.setAdapter(myAdapter_f);


                        break;
                    }
                }
            }
        };
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////









///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        favoriteslist = (RecyclerView) findViewById(R.id.favorites_list);
        favoriteslist.setLayoutManager(new LinearLayoutManager(this));

        favorites = new ArrayList<MyCharacter>(){{
            Cursor cursor = db.query("character",null,"like = ?",new String[]{ "1" },null,null,null);
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
            cursor.close();
        }};

        myAdapter_f = new MyAdapter<MyCharacter>(this, R.layout.list_layout, favorites) {
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

        myAdapter_f.setOnItemClickListener(new MyAdapter.OnItemClickListener() {
            @Override
            public void onClick(int position) {
                Intent intent = new Intent(MainActivity.this, InfoActivity.class);
                Bundle extras = new Bundle();
                extras.putString("c_name",myAdapter_f.getItem(position).getC_name());
                extras.putString("c_sname",myAdapter_f.getItem(position).getC_sname());
                extras.putString("c_sex",myAdapter_f.getItem(position).getC_sex());
                extras.putString("c_major",myAdapter_f.getItem(position).getC_major());
                extras.putString("c_jiguan",myAdapter_f.getItem(position).getC_jiguan());
                extras.putString("c_bd",myAdapter_f.getItem(position).getC_bd());
                extras.putString("c_info",myAdapter_f.getItem(position).getC_info());
                extras.putInt("c_photoid",myAdapter_f.getItem(position).getC_photoid());
                extras.putInt("like",myAdapter_f.getItem(position).getC_like());
                extras.putByteArray("bitmap",in);
                extras.putInt("index",position);
                intent.putExtras(extras);
                startActivity(intent);
            }

            @Override
            public void onLongClick(final int position) {
                alertdialog1.setItems(choice1,
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

        favoriteslist.setAdapter(myAdapter_f);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bgm_switch = (CheckBox) findViewById(R.id.bgm_switch);
        game_switch = (CheckBox) findViewById(R.id.game_switch);
        mp = new MediaPlayer();
        mp = MediaPlayer.create(this,R.raw.bgm);
        mp.setLooping(true);
        mp.start();
        bgm_switch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if(isChecked){
                    if(!mp.isPlaying()){
                        mp.start();
                    }
                }
                else {
                    if(mp.isPlaying()){
                        mp.pause();
                    }
                }
            }
        });

        game_switch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if(isChecked){
                    free_space4.setVisibility(View.VISIBLE);
                    game_dis = true;
                }
                else {
                    free_space4.setVisibility(View.GONE);
                    game_dis = false;
                }
            }
        });


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    }

    @SuppressLint("NewApi")
    private void initSound() {
        soundPool = new SoundPool.Builder().build();
        soundID = soundPool.load(this, R.raw.oh, 1);
    }

    private void playSound() {
        soundPool.play(
                soundID,
                1f,   //左耳道音量【0~1】
                1f,   //右耳道音量【0~1】
                0,     //播放优先级【0表示最低优先级】
                1,     //循环模式【0表示循环一次，-1表示一直循环，其他表示数字+1表示当前数字对应的循环次数】
                1     //播放速度【1是正常，范围从0~2】
        );
    }

    public int getResource(String imageName){
        Context ctx=getBaseContext();
        int resId = getResources().getIdentifier(imageName, "mipmap", ctx.getPackageName());
        //如果没有在"mipmap"下找到imageName,将会返回0
        return resId;
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onMessageEvent(MessageEvent event){
        mHandler.obtainMessage(123).sendToTarget();
    }

    @Override
    public void onStop(){
        super.onStop();
        on = false;
        if(bgm_switch.isChecked()){
            if(InfoActivity.instance != null){
                if(!InfoActivity.instance.on){
                    mp.pause();
                }
            }
            else if(ModifyActivity.instance != null){
                if(!ModifyActivity.instance.on){
                    mp.pause();
                }
            }
            else if(SearchResult.instance != null){
                if(!SearchResult.instance.on){
                    mp.pause();
                }
            }
            else{
                mp.pause();
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
        if(bgm_switch.isChecked()){
            mp.start();
        }
    }

    @Override
    public void onDestroy(){
        super.onDestroy();
        EventBus.getDefault().unregister(this);
    }



}

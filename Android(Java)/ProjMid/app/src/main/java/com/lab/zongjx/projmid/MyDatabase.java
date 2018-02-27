package com.lab.zongjx.projmid;

import android.content.ContentValues;
import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.graphics.Bitmap;
import android.widget.Toast;

import java.sql.Blob;

public class MyDatabase extends SQLiteOpenHelper {
    public static final String CREATE_BOOK = "create table character ("
            + "id integer primary key autoincrement, "
            + "name text, "
            + "sex text, "
            + "sname text, "
            + "major text, "
            + "jiguan text, "
            + "bd text, "
            + "info text, "
            + "photoid integet, "
            + "like integer, "
            + "bitmap blob )";

    private Context mContext;
    public MyDatabase(Context context, String name, SQLiteDatabase.CursorFactory
            factory, int version) {
        super(context, name, factory, version);
        mContext = context;
    }
    @Override
    public void onCreate(SQLiteDatabase db) {
        db.execSQL(CREATE_BOOK);
        ContentValues values = new ContentValues();
        values.put("name","刘备");
        values.put("sex","男  史实人物");
        values.put("sname","字：玄德");
        values.put("major","蜀");
        values.put("jiguan","籍贯：幽州涿郡涿（河北保定市涿州）");
        values.put("bd","生卒（161 - 223）");
        values.put("info","　　刘备，蜀汉的开国皇帝，汉景帝之子中山靖王刘胜的后代。刘备少年孤贫，以贩鞋织草席为生。黄巾起义时，刘备与关羽、张飞桃园结义，成为异姓兄弟，一同剿除黄巾，有功，任安喜县尉，不久辞官；董卓乱政之际，刘备随公孙瓒讨伐董卓，三人在虎牢关战败吕布。后诸侯割据，刘备势力弱小，经常寄人篱下，先后投靠过公孙瓒、曹操、袁绍、刘表等人，几经波折，却仍无自己的地盘。赤壁之战前夕，刘备在荆州三顾茅庐，请诸葛亮出山辅助，在赤壁之战中，联合孙权打败曹操，奠定了三分天下的基础。刘备在诸葛亮的帮助下占领荆州，不久又进兵益州，夺取汉中，建立了横跨荆益两州的政权。后关羽战死，荆州被孙权夺取，刘备大怒，于称帝后伐吴，在夷陵之战中为陆逊用火攻打得大败，不久病逝于白帝城，临终托孤于诸葛亮");
        values.put("photoid",R.mipmap.liubei);
        values.put("like",0);
        values.put("bitmap","0".getBytes());
        db.insert("character",null,values);
        values.clear();

        values.put("name","关羽");
        values.put("sex","男  史实人物");
        values.put("sname","字：云长");
        values.put("major","蜀");
        values.put("jiguan","籍贯：司隶河东郡解（山西运城市临猗县西南）");
        values.put("bd","生卒（？ - 219）");
        values.put("info","    因本处势豪倚势凌人，关羽杀之而逃难江湖。闻涿县招军破贼，特来应募。与刘备、张飞桃园结义，羽居其次。使八十二斤青龙偃月刀随刘备东征西讨。虎牢关温酒斩华雄，屯土山降汉不降曹。为报恩斩颜良、诛文丑，解曹操白马之围。后得知刘备音信，过五关斩六将，千里寻兄。刘备平定益州后，封关羽为五虎大将之首，督荆州事。羽起军攻曹，放水淹七军，威震华夏。围樊城右臂中箭，幸得华佗医治，刮骨疗伤。但未曾提防东吴袭荆州，关羽父子败走麦城，突围中被捕，不屈遭害。\n");
        values.put("photoid",R.mipmap.guanyu);
        values.put("like",0);
        values.put("bitmap","0".getBytes());
        db.insert("character",null,values);
        values.clear();

        values.put("name","张飞");
        values.put("sex","男  史实人物");
        values.put("sname","字：益德");
        values.put("major","蜀");
        values.put("jiguan","籍贯：幽州涿郡（河北保定市涿州）");
        values.put("bd","生卒（？ - 221）");
        values.put("info","　　与刘备和关羽桃园结义，张飞居第三。随刘备征讨黄巾，刘备终因功被朝廷受予平原相，后张飞鞭挞欲受赂的督邮。十八路诸侯讨董时，三英战吕布，其勇为世人所知。曹操以二虎竞食之计迫刘备讨袁术，刘备以张飞守徐州，诫禁酒，但还是因此而鞭打曹豹招致吕布东袭。刘备反曹后，反用劫寨计擒曹将刘岱，为刘备所赞。徐州终为曹操所破，张飞与刘备失散，占据古城。误以为降汉的关羽投敌，差点一矛将其杀掉。曹操降荊州后引骑追击，刘备败逃，张飞引二十余骑，立马于长阪桥，吓退曹军数十里。庞统死后刘备召其入蜀，张飞率军沿江而上，智擒巴郡太守严颜并生获之，张飞壮而释放。于葭萌关和马超战至夜间，双方点灯，终大战数百回合。瓦口关之战时扮作醉酒，智破张郃。后封为蜀汉五虎大将。及关羽卒，张飞悲痛万分，每日饮酒鞭打部下，导致为帐下将张达、范强所杀，他们持其首顺流而奔孙权。");
        values.put("photoid",R.mipmap.zhangfei);
        values.put("like",0);
        values.put("bitmap","0".getBytes());
        db.insert("character",null,values);
        values.clear();

        values.put("name","曹操");
        values.put("sex","男  史实人物");
        values.put("sname","字：孟德");
        values.put("major","魏");
        values.put("jiguan","籍贯：豫州沛国谯（安徽亳州市亳县）");
        values.put("bd","生卒（155 - 220）");
        values.put("info","　　曹操是西园八校尉之一，曾只身行刺董卓，失败后和袁绍共同联合天下诸侯讨伐董卓，后独自发展自身势力，一生中先后战胜了袁术、吕布、张绣、袁绍、刘表、张鲁、马超等割据势力，统一了北方。但是在南下讨伐江东的战役中，曹操在赤壁惨败。后来在和蜀汉的汉中争夺战中，曹操再次无功而返。曹操一生未称帝，他病死后，曹丕继位后不久称帝，追封曹操为魏武皇帝。");
        values.put("photoid",R.mipmap.caocao);
        values.put("like",0);
        values.put("bitmap","0".getBytes());
        db.insert("character",null,values);
        values.clear();

        values.put("name","曹丕");
        values.put("sex","男  史实人物");
        values.put("sname","字：子桓");
        values.put("major","魏");
        values.put("jiguan","籍贯：豫州沛国谯（安徽亳州市亳县）");
        values.put("bd","生卒（187 - 226）");
        values.put("info","　　在争夺继承权问题上处心积虑，战胜了文才更胜一筹的弟弟曹植，被立为王世子。曹操逝世后，曹丕继位成为魏王，以不参加葬礼之罪逼弟弟曹植写下七步诗，险些将其杀害，又顺利夺下弟弟曹彰的兵权，坐稳了魏王之位。不久，曹丕逼汉献帝让位，代汉称帝，为魏国开国皇帝。刘备伐吴时，曹丕看出刘备要失败，但不听谋士之言，偏要坐山观虎斗，事后又起兵伐吴，结果被徐盛火攻击败。回洛阳后，曹丕大病，临终前托付曹睿给曹真、司马懿等人，终年四十岁。");
        values.put("photoid",R.mipmap.caopi);
        values.put("like",0);
        values.put("bitmap","0".getBytes());
        db.insert("character",null,values);
        values.clear();

        values.put("name","夏侯惇");
        values.put("sex","男  史实人物");
        values.put("sname","字：元让");
        values.put("major","魏");
        values.put("jiguan","籍贯：豫州沛国谯（安徽亳州市亳县）");
        values.put("bd","生卒（？ - 220）");
        values.put("info","　　曹操从弟。少习枪棒，武艺过人。曹操起兵，夏侯惇率众来投，自此随之征战。曹操讨吕布，惇为布将曹性射其左目，惇拨矢啖睛，杀性，两军无不骇然。后惇常为先锋，杀敌破阵，冲锋在前，立功无数。曹操病笃，惇往见之，于宫门处遇鬼惊倒，自此染病。及曹丕称帝，以惇为大将军。旋之，卒。曹丕为之挂孝。");
        values.put("photoid",R.mipmap.xiahoudun);
        values.put("like",0);
        values.put("bitmap","0".getBytes());
        db.insert("character",null,values);
        values.clear();

        values.put("name","孙策");
        values.put("sex","男  史实人物");
        values.put("sname","字：伯符");
        values.put("major","吴");
        values.put("jiguan","籍贯：扬州吴郡富春（浙江杭州市富阳）");
        values.put("bd","生卒（175 - 200）");
        values.put("info","　　父坚与荆州牧刘表攻，策时十七，与之相从。策箭射表将陈生。后坚为表将乱箭射死，策回到汉水，闻父尸在彼，乃用俘虏黄祖换之。后往淮南投袁术，深为术所爱。后策图自强，以父所留传国玉玺换术兵，术表策为折冲校尉、殄寇将军。策自此荡平东南，威震三江。破刘繇，挟死一将、喝死一将，人皆呼之为「小霸王」。又匹马于神亭与繇将太史慈酣战数百合，为众人所惊。后策平江东，迁讨逆将军，领会稽太守，封吴侯。曹公惮其强，与之结亲以安其心。后曹公与袁绍相拒于官渡，策阴欲袭许。先是，吴郡太守许贡暗发书与曹公，教徐图策，策知之，杀贡。一日，策行猎，为贡门客所刺，创甚。后又斩杀道士于吉而受其诅咒，伤重而亡，寿仅二十六岁。权称尊号，追谥策曰长沙桓王。");
        values.put("photoid",R.mipmap.sunce);
        values.put("like",0);
        values.put("bitmap","0".getBytes());
        db.insert("character",null,values);
        values.clear();

        values.put("name","周瑜");
        values.put("sex","男  史实人物");
        values.put("sname","字：公瑾");
        values.put("major","吴");
        values.put("jiguan","籍贯：扬州庐江郡舒（安徽合肥市庐江县西南）");
        values.put("bd","生卒（175 - 210）");
        values.put("info","　　偏将军、南郡太守。自幼与孙策交好，策离袁术讨江东，瑜引兵从之。为中郎将，孙策相待甚厚，又同娶二乔。策临终，嘱弟权曰：“外事不决，可问周瑜”。瑜奔丧还吴，与张昭共佐权，并荐鲁肃等，掌军政大事。赤壁战前，瑜自鄱阳归。力主战曹，后于群英会戏蒋干、怒打黄盖行诈降计、后火烧曹军，大败之。后下南郡与曹仁相持，中箭负伤，与诸葛亮较智斗，定假涂灭虢等计，皆为亮破，后气死于巴陵，年三十六岁。临终，上书荐鲁肃代其位，权为其素服吊丧。");
        values.put("photoid",R.mipmap.zhouyu);
        values.put("like",0);
        values.put("bitmap","0".getBytes());
        db.insert("character",null,values);
        values.clear();

        values.put("name","吕布");
        values.put("sex","男  史实人物");
        values.put("sname","字：奉先");
        values.put("major","群");
        values.put("jiguan","籍贯：并州五原郡九原（内蒙古包头市九原区麻池镇西北古城遗址）");
        values.put("bd","生卒（？ - 198）");
        values.put("info","　　吕布是骁勇善战的汉末诸侯，先后跟随丁原、董卓作战，并最终杀死了丁原和董卓。成为独立势力后，吕布与曹操为敌，和刘备、袁术等诸侯时敌时友，最终不敌曹操和刘备的联军，兵败人亡。吕布虽然勇猛，但是少有计策，为人反复无常，唯利是图。在演义中，吕布是天下无双的超一流武将，曾在虎牢关大战刘备、关羽、张飞三人联手，曾一人独斗曹操军六员大将，武艺可谓公认的演义第一。著名的美女貂蝉上演连环计后，成为吕布的妻室。");
        values.put("photoid",R.mipmap.lvbu);
        values.put("like",0);
        values.put("bitmap","0".getBytes());
        db.insert("character",null,values);
        values.clear();

        values.put("name","张角");
        values.put("sex","男  史实人物");
        values.put("sname"," ");
        values.put("major","群");
        values.put("jiguan","籍贯：冀州巨鹿郡（河北邢台市平乡县）");
        values.put("bd","生卒（？ - 184）");
        values.put("info","　　原是个不第的秀才，在山中采药时遇南华老仙，得天书三卷，名为《太平要术》。张角依此书所传道术，开始散施符水，为人治病，徒众发展到数十万。张角遂起了夺取天下得野心，与兄弟张宝、张梁一起起兵造反，声势浩大，但最终被朝廷和各路豪杰镇压。张角病死，黄巾军主力随即覆灭，但仍有很多残党在各地活动。");
        values.put("photoid",R.mipmap.zhangjiao);
        values.put("like",0);
        values.put("bitmap","0".getBytes());
        db.insert("character",null,values);
        values.clear();

        values.put("name","貂蝉");
        values.put("sex","女  虚构人物");
        values.put("sname"," ");
        values.put("major","群");
        values.put("jiguan","籍贯：？");
        values.put("bd"," ");
        values.put("info","　　舍身报国的可敬女子，她为了挽救天下黎民，为了推翻权臣董卓的荒淫统治，受王允所托，上演了可歌可泣的连环计（连环美人计），周旋于两个男人之间，成功的离间了董卓和吕布，最终吕布将董卓杀死，结束了董卓专权的黑暗时期。");
        values.put("photoid",R.mipmap.diaochan);
        values.put("like",0);
        values.put("bitmap","0".getBytes());
        db.insert("character",null,values);
        values.clear();

        values.put("name","大乔");
        values.put("sex","女  史实人物");
        values.put("sname"," ");
        values.put("major","吴");
        values.put("jiguan","籍贯：扬州庐江郡皖（安徽安庆市潜山县）");
        values.put("bd","生卒（？ - ？）");
        values.put("info","　　江东乔国老有二女，大乔和小乔。大乔有沉鱼落雁之资，倾国倾城之容。孙策征讨江东，攻取皖城，娶大乔为妻。自古美女配英雄，伯符大乔堪绝配。曹操赤壁鏖兵，虎视江东，曾有揽二乔娱暮年，还足平生之愿。");
        values.put("photoid",R.mipmap.daqiao);
        values.put("like",0);
        values.put("bitmap","0".getBytes());
        db.insert("character",null,values);
        values.clear();

        values.put("name","小乔");
        values.put("sex","女  史实人物");
        values.put("sname"," ");
        values.put("major","吴");
        values.put("jiguan","籍贯：扬州庐江郡皖（安徽安庆市潜山县）");
        values.put("bd","生卒（？ - ？）");
        values.put("info","　　庐江皖县桥国老次女，秀美绝伦，貌压群芳，又琴棋书画无所不通周瑜攻取皖城，迎娶小乔为妻。周郎小乔英雄美女、郎才女貌 ，被流传为千古佳话。\n");
        values.put("photoid",R.mipmap.xiaoqiao);
        values.put("like",0);
        values.put("bitmap","0".getBytes());
        db.insert("character",null,values);
        values.clear();

        Toast.makeText(mContext, "Create succeeded", Toast.LENGTH_SHORT).show();
    }
    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
    }

}
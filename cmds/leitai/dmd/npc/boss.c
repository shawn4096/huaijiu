// Modify By Ilovemin@SJ 

inherit NPC;
inherit F_UNIQUE;
inherit F_SAVE;

#include <ansi.h>

void checkfight();
int do_copy(object target);

void create()
{
        string weapon = "null" , menpai;

	set_name("倭寇头目",({ "wokou boss" }));
	set("title", HIR"倭寇头目"NOR);
        set("gender", "男性");
        set("age", 20 + random(40));
        set("no_get", "倭寇头目对你而言太重了。\n");
        set("long", "这是位倭寇的头目，身形萎缩，一看就不是什么好东西！\n");

        set("combat_exp", 5000000);
        set("meitude","peaceful");
        set("str", 20+random(15));
        set("int", 20+random(10));
        set("con", 25+random(10));
        set("dex", 25+random(10));
        set("max_qi", 20000);
        set("max_jing", 20000);
        set("max_neili", 5000);
        set("max_neili", 20000);
        set("neili", 20000);
        set_temp("apply/armor", 100);
        set("eff_jing", 20000);
        set("eff_jingli", 20000);
        set("jingli", 20000);
        set("max_jingli", 20000);

        set("no_ansuan",1);
        set("no_bark", 1);
        set_skill("strike", 500);
        set_skill("cuff", 500);
        set_skill("hand", 500);
        set_skill("dodge", 500);
        set_skill("sword", 500);
        set_skill("force", 500);
        set_skill("parry", 500);
        set_skill("blade", 500);
        set_skill("hammer", 500);
        set_skill("stick", 500);
        set_skill("club", 500);
        set_skill("staff", 500);
        set_skill("literate", 500);
        set_skill("whip", 500);
        set_skill("dagger", 500);

        switch( random(22) ) {
                case 0:  // wd1
                        set_skill("yinyun-ziqi", 500);
                        set_skill("tiyunzong", 500);
                        set_skill("taiji-jian", 500);
                        set_skill("taiji-quan", 500);
                        map_skill("force", "yinyun-ziqi");
                        map_skill("dodge", "tiyunzong");
                        map_skill("sword", "taiji-jian");
                        map_skill("parry", "taiji-quan");
                        map_skill("cuff", "taiji-quan");
                        prepare_skill("cuff", "taiji-quan");         
                        set("chat_chance_combat", 40);
                        set("chat_msg_combat", ({
                                (: exert_function, "taiji" :),
                                (: perform_action, "cuff.dongjing" :), 
                                (: perform_action, "cuff.gangrou" :),
                                (: perform_action, "cuff.luanhuan" :), 
                        }));
                        menpai = "武当";
                        break;
                case 1:  // wd2
                        set_skill("yinyun-ziqi", 500);
                        set_skill("tiyunzong", 500);
                        set_skill("taiji-jian", 500);
                        set_skill("taiji-quan", 500);
                        map_skill("force", "yinyun-ziqi");
                        map_skill("dodge", "tiyunzong");
                        map_skill("sword", "taiji-jian");
                        map_skill("parry", "taiji-jian");
                        map_skill("cuff", "taiji-quan");
                        prepare_skill("cuff", "taiji-quan");         
                        set("chat_chance_combat", 40);
                        set("chat_msg_combat", ({
                                (: perform_action, "dodge.zong" :),
                                (: perform_action, "sword.sanhuan" :), 
                                (: perform_action, "sword.lian" :), 
                        }));
                        weapon = "sword";
                        menpai = "武当";
                        break;
                case 2:  // sl1
                        set_skill("yijin-jing", 500);
                        set_skill("shaolin-shenfa", 500);
                        set_skill("riyue-bian", 500);
                        set_skill("yizhi-chan", 500);
                        map_skill("force", "yijin-jing");
                        map_skill("dodge", "shaolin-shenfa");
                        map_skill("whip", "riyue-bian");
                        map_skill("parry", "riyue-bian");
                        map_skill("finger", "yizhi-chan");
                        prepare_skill("finger", "yizhi-chan");         
                        set("chat_chance_combat", 40);
                        set("chat_msg_combat", ({
                                (: exert_function, "jingang" :),
                                (: perform_action, "whip.chanrao" :), 
                                (: perform_action, "whip.fumoquan" :), 
                        }));
                        weapon = "whip";
                        menpai = "少林";
                        break;
                case 3:  // sl2
                        set_skill("yijin-jing", 500);
                        set_skill("shaolin-shenfa", 500);
                        set_skill("ranmu-daofa", 500);
                        set_skill("yizhi-chan", 500);
                        map_skill("force", "yijin-jing");
                        map_skill("dodge", "shaolin-shenfa");
                        map_skill("blade", "ranmu-daofa");
                        map_skill("parry", "ranmu-daofa");
                        map_skill("finger", "yizhi-chan");
                        prepare_skill("finger", "yizhi-chan");         
                        set("chat_chance_combat", 40);
                        set("chat_msg_combat", ({
                                (: exert_function, "jingang" :),
                                (: perform_action, "blade.fenwo" :), 
                        }));
                        weapon = "blade";
                        menpai = "少林";
                        break;
                case 4:  // sl3
                        set_skill("yijin-jing", 500);
                        set_skill("shaolin-shenfa", 500);
                        set_skill("yizhi-chan", 500);
                        map_skill("force", "yijin-jing");
                        map_skill("dodge", "shaolin-shenfa");
                        map_skill("parry", "yizhi-chan");
                        map_skill("finger", "yizhi-chan");
                        prepare_skill("finger", "yizhi-chan");         
                        set("chat_chance_combat", 40);
                        set("chat_msg_combat", ({
                                (: exert_function, "jingang" :),
                                (: perform_action, "finger.wofo" :), 
                                (: perform_action, "finger.qiankun" :), 
                        }));
                        menpai = "少林";
                        break;
                case 5:  // hs1
                        set_skill("zixia-gong", 500);
                        set_skill("huashan-shenfa", 500);
                        set_skill("huashan-jianfa", 500);
                        set_skill("hunyuan-zhang", 500);
                        map_skill("force", "zixia-gong");
                        map_skill("dodge", "huashan-shenfa");
                        map_skill("sword", "huashan-jianfa");
                        map_skill("parry", "huashan-jianfa");
                        map_skill("strike", "hunyuan-zhang");
                        prepare_skill("strike", "hunyuan-zhang");         
                        set("chat_chance_combat", 40);
                        set("chat_msg_combat", ({
                                (: exert_function, "zixia" :),
                                (: perform_action, "sword.lianhuan" :), 
                        }));
                        weapon = "sword";
                        menpai = "华山";
                        break;
                case 6:  // hs2
                        set_skill("zixia-gong", 500);
                        set_skill("huashan-shenfa", 500);
                        set_skill("fanliangyi-dao", 500);
                        set_skill("poyu-quan", 500);
                        map_skill("force", "zixia-gong");
                        map_skill("dodge", "huashan-shenfa");
                        map_skill("blade", "fanliangyi-dao");
                        map_skill("parry", "fanliangyi-dao");
                        map_skill("cuff", "poyu-quan");
                        prepare_skill("cuff", "poyu-quan");         
                        set("chat_chance_combat", 40);
                        set("chat_msg_combat", ({
                                (: exert_function, "zixia" :),
                                (: perform_action, "blade.sanshenfeng" :), 
                        }));
                        weapon = "blade";
                        menpai = "华山";
                        break;
                case 7:  // gb1
                        set_skill("huntian-qigong", 500);
                        set_skill("bangjue", 500);
                        set_skill("xiaoyaoyou", 500);
                        set_skill("dagou-bang", 500);
                        set_skill("xianglong-zhang", 500);
                        map_skill("force", "huntian-qigong");
                        map_skill("dodge", "xiaoyaoyou");
                        map_skill("stick", "dagou-bang");
                        map_skill("parry", "dagou-bang");
                        map_skill("strike", "xianglong-zhang");
                        prepare_skill("strike", "xianglong-zhang");         
                        set("chat_chance_combat", 40);
                        set("chat_msg_combat", ({
                                (: exert_function, "powerup" :),
                                (: perform_action, "stick.shuangjue" :), 
                                (: perform_action, "stick.chuo" :), 
                        }));
                        weapon = "stick";
                        menpai = "丐帮";
                        break;
                case 8:  // gb2
                        set_skill("huntian-qigong", 500);
                        set_skill("bangjue", 500);
                        set_skill("xiaoyaoyou", 500);
                        set_skill("dagou-bang", 500);
                        set_skill("xianglong-zhang", 500);
                        map_skill("force", "huntian-qigong");
                        map_skill("dodge", "xiaoyaoyou");
                        map_skill("stick", "dagou-bang");
                        map_skill("parry", "xianglong-zhang");
                        map_skill("strike", "xianglong-zhang");
                        prepare_skill("strike", "xianglong-zhang");         
                        set("chat_chance_combat", 40);
                        set("chat_msg_combat", ({
                                (: exert_function, "powerup" :),                                
                                (: perform_action, "strike.paiyun" :), 
                        }));
                        menpai = "丐帮";
                        break;
                case 9:  // thd1
                        set_skill("bihai-chaosheng", 500);
                        set_skill("qimen-bagua", 500);
                        set_skill("suibo-zhuliu", 500);
                        set_skill("yuxiao-jian", 500);
                        set_skill("tanzhi-shentong", 500);
                        set_skill("lanhua-shou", 500);
                        set_skill("luoying-zhang", 500);
                        set_skill("xuanfeng-tui", 500);
                        map_skill("force", "    bihai-chaosheng");
                        map_skill("dodge", "suibo-zhuliu");
                        map_skill("sword", "yuxiao-jian");
                        map_skill("parry", "yuxiao-jian");
                        map_skill("finger", "tanzhi-shentong");
                        map_skill("hand", "lanhua-shou");
                        map_skill("strike", "luoying-zhang");
                        map_skill("leg", "xunfeng-tui");
                        prepare_skill("finger", "tanzhi-shentong");         
                        set("chat_chance_combat", 40);
                        set("chat_msg_combat", ({
                                (: exert_function, "maze" :),
                                (: perform_action, "sword.qimen" :), 
                                (: perform_action, "sword.feiying" :), 
                        }));
                        set("thd/perform",999);
                        weapon = "xiao";
                        menpai = "桃花岛";
                        break;
                case 10: // thd2
                        set_skill("bihai-chaosheng", 500);
                        set_skill("qimen-bagua", 500);
                        set_skill("suibo-zhuliu", 500);
                        set_skill("yuxiao-jian", 500);
                        set_skill("tanzhi-shentong", 500);
                        map_skill("force", "bihai-chaosheng");
                        map_skill("dodge", "suibo-zhuliu");
                        map_skill("sword", "yuxiao-jian");
                        map_skill("parry", "tanzhi-shentong");
                        map_skill("finger", "tanzhi-shentong");
                        prepare_skill("finger", "tanzhi-shentong");         
                        set("chat_chance_combat", 40);
                        set("chat_msg_combat", ({
                                (: exert_function, "maze" :),
                                (: perform_action, "finger.huayu" :), 
                                (: perform_action, "finger.shentong" :), 
                        }));
                        set("thd/perform",999);
                        menpai = "桃花岛";
                        break;
                case 11: // mr1
                        set_skill("shenyuan-gong", 500);
                        set_skill("douzhuan-xingyi", 500);
                        set_skill("yanling-shenfa", 500);
                        set_skill("murong-jianfa", 500);
                        set_skill("canhe-zhi", 500);
                        map_skill("force", "shenyuan-gong");
                        map_skill("dodge", "yanling-shenfa");
                        map_skill("sword", "murong-jianfa");
                        map_skill("parry", "douzhuan-xingyi");
                        map_skill("finger", "canhe-zhi");
                        prepare_skill("finger", "canhe-zhi");         
                        set("chat_chance_combat", 40);
                        set("chat_msg_combat", ({
                                (: exert_function, "shenyuan" :),
                                (: perform_action, "sword.sanhua" :), 
                                (: perform_action, "sword.lianhuan" :),                           
                        }));
                        weapon = "sword";
                        menpai = "姑苏慕容";
                        break;
                case 12: // gumu1
                        set_skill("yunu-xinjing", 500);
                        set_skill("yunu-shenfa", 500);
                        set_skill("xuantie-jianfa", 500);
                        set_skill("anran-zhang", 500);
                        map_skill("force", "    yunu-xinjing");
                        map_skill("dodge", "yunu-shenfa");
                        map_skill("sword", "xuantie-jianfa");
                        map_skill("parry", "xuantie-jianfa");
                        map_skill("strike", "anran-zhang");
                        prepare_skill("strike", "anran-zhang");         
                        set("chat_chance_combat", 40);
                        set("chat_msg_combat", ({
                                (: perform_action, "sword.haichao" :), 
                        }));
                        weapon = "sword";
                        menpai = "古墓";
         if (random(2)) set("env/玄铁剑法","海潮");
                     else set("env/玄铁剑法","汹涌");
                        break;
                case 13: // emei1
                        set_skill("linji-zhuang", 500);
                        set_skill("anying-fuxiang", 500);
                        set_skill("huifeng-jian", 500);
                        set_skill("sixiang-zhang", 500);
                        map_skill("force", "linji-zhuang");
                        map_skill("dodge", "anying-fuxiang");
                        map_skill("sword", "huifeng-jian");
                        map_skill("parry", "huifeng-jian");
                        map_skill("strike", "sixiang-zhang");
                        prepare_skill("strike", "sixiang-zhang");         
                        set("chat_chance_combat", 40);
                        set("chat_msg_combat", ({
                                (: exert_function, "wuwo" :),
                                (: perform_action, "sword.mie" :), 
                                (: perform_action, "sword.jue" :),
                                (: perform_action, "sword.liaoyuan" :),  
                        }));
                        weapon = "sword";
                        menpai = "娥眉";
                        break;
                case 14: // emei2
                        set_skill("linji-zhuang", 500);
                        set_skill("anying-fuxiang", 500);
                        set_skill("yanxing-daofa", 500);
                        set_skill("sixiang-zhang", 500);
                        map_skill("force", "linji-zhuang");
                        map_skill("dodge", "anying-fuxiang");
                        map_skill("blade", "yanxing-daofa");
                        map_skill("parry", "yanxing-daofa");
                        map_skill("strike", "sixiang-zhang");
                        prepare_skill("strike", "sixiang-zhang");         
                        set("chat_chance_combat", 40);
                        set("chat_msg_combat", ({
                                (: exert_function, "wuwo" :),
                                (: perform_action, "blade.huanying" :), 
                        }));
                        weapon = "blade";
                        menpai = "娥眉";
                        break;
                case 15: // mj1
                        set_skill("shenghuo-shengong", 500);
                        set_skill("qiankun-danuoyi", 500);
                        set_skill("piaoyi-shenfa", 500);
                        set_skill("shenghuo-lingfa", 500);
                        set_skill("hanbing-mianzhang", 500);
                        map_skill("force", "shenghuo-shengong");
                        map_skill("dodge", "piaoyi-shenfa");
                        map_skill("dagger", "shenghuo-lingfa");
                        map_skill("parry", "qiankun-danuoyi");
                        map_skill("cuff", "shenghuo-lingfa");
                        prepare_skill("cuff", "shenghuo-lingfa");         
                        set("chat_chance_combat", 40);
                        set("chat_msg_combat", ({
                                (: exert_function, "yinfeng" :),
                                (: perform_action, "dagger.xinmo" :), 
                                (: perform_action, "blade.tisha" :), 
                        }));
                        weapon = "tieling";
                        menpai = "明教";
                        break;
                case 16: // mj2
                        set_skill("shenghuo-shengong", 500);
                        set_skill("qiankun-danuoyi", 500);
                        set_skill("piaoyi-shenfa", 500);
                        set_skill("shenghuo-lingfa", 500);
                        set_skill("hanbing-mianzhang", 500);
                        map_skill("force", "shenghuo-shengong");
                        map_skill("dodge", "piaoyi-shenfa");
                        map_skill("dagger", "shenghuo-lingfa");
                        map_skill("parry", "hanbing-mianzhang");
                        map_skill("strike", "hanbing-mianzhang");
                        prepare_skill("strike", "hanbing-mianzhang");         
                        set("chat_chance_combat", 40);
                        set("chat_msg_combat", ({
                                (: exert_function, "yinfeng" :),
                                (: perform_action, "strike.xixue" :), 
                        }));
                        menpai = "明教";
                case 17: // dali1
                        set_skill("qiantian-yiyang", 500);
                        set_skill("tianlong-xiang", 500);
                        set_skill("duanjia-jianfa", 500);
                        set_skill("qingyan-zhang", 500);
                        map_skill("force", "qiantian-yiyang");
                        map_skill("dodge", "tianlong-xiang");
                        map_skill("sword", "duanjia-jianfa");
                        map_skill("parry", "qingyan-zhang");
                        map_skill("strike", "qingyan-zhang");
                        prepare_skill("strike", "qingyan-zhang");         
                        set("chat_chance_combat", 40);
                        set("chat_msg_combat", ({
                                (: exert_function, "xinjing" :),
                                (: perform_action, "sword.fenglei" :), 
                        }));
                        weapon = "sword";
                        menpai = "天南大理";
                        break;
                case 18: // tls
                        set_skill("kurong-changong", 500);
                        set_skill("tianlong-xiang", 500);
                        set_skill("yiyang-zhi", 500);
                        map_skill("force", "kurong-changong");
                        map_skill("dodge", "tianlong-xiang");
                        map_skill("parry", "yiyang-zhi");
                        map_skill("finger", "yiyang-zhi");
                        prepare_skill("finger","yiyang-zhi");    
                        set("chat_chance_combat", 40);
                        set("chat_msg_combat", ({
                               (: perform_action, "finger.yizhisanmai" :), 
                        }));
                        menpai = "大理天龙寺";
                        break;
                case 19: // gumu2
                        set_skill("yinsuo-jinling", 500);
                        set_skill("yunu-jianfa", 500);
                        set_skill("yunu-shenfa", 500);
                        set_skill("meinu-quanfa", 500);
                        set_skill("yunu-xinjing", 500);
                        map_skill("force", "yunu-xinjing");
                        map_skill("dodge", "yunu-shenfa");
                        map_skill("sword", "yunu-jianfa");
                        map_skill("whip", "yinsuo-jinling");
                        map_skill("parry", "yinsuo-jinling");
                        map_skill("cuff", "meinu-quanfa"); 
                        prepare_skill("cuff", "meinu-quanfa");         
                        set("chat_chance_combat", 40);
                        set("chat_msg_combat", ({
                                (: perform_action, "whip.yueyin" :), 
                                (: perform_action, "whip.yufeng" :), 
                        }));
                        weapon = "whip";
                        menpai = "古墓派";
                        break;
                case 20: //gumu3 
                        set_skill("anran-zhang", 500);
                        set_skill("yunu-xinjing", 500);
                        set_skill("yunu-shenfa", 500);
                        map_skill("force", "yunu-xinjing");
                        map_skill("dodge", "yunu-shenfa");
                        map_skill("parry", "anran-zhang");
                        map_skill("strike", "anran-zhang"); 
                        prepare_skill("strike", "anran-zhang");       
                        set("chat_chance_combat", 40);
                        set("chat_msg_combat", ({
                                (: perform_action, "strike.xiaohun" :), 
                                (: perform_action, "strike.anran" :), 
                        }));
                        menpai = "古墓派";
                        break;
             
                 case 21: // tls3
                        set_skill("kurong-changong", 500);
                        set_skill("tianlong-xiang", 500);
                        set_skill("yiyang-zhi", 500);
                        map_skill("force", "kurong-changong");
                        map_skill("dodge", "tianlong-xiang");
                        map_skill("parry", "yiyang-zhi");
                        map_skill("strike", "kurong-changong");
                        prepare_skill("strike", "kurong-changong");         
                        set("chat_chance_combat", 40);
                        set("chat_msg_combat", ({
                                (: perform_action, "strike.jiuchong" :),               
                        }));                           
                        menpai = "大理天龙寺";
                        break;
                        

                default: // others      BUG!!!
                        set("long","武功设置错误，BUG！！！");
        }
        set("long" , query("long") + sprintf("这位倭寇头目似乎曾经偷师%s。\n",menpai) );
        set("weapon" , weapon);

        set_temp("no_return",1);
        setup();
        if( weapon!="null" ) carry_object(BINGQI_D(weapon))->wield();
        carry_object(ARMOR_D("cloth"))->wear();
        add_money("gold", 50+random(50));

}       

void die(object ob)
{
        object ob1;
        int k;
        k = random(4);
        switch(k){
		case 1:	ob1 = new("/clone/gift/book.c");
			break;
		case 2:	ob1 = new("/clone/gift/kuangshi.c");
			break;
		case 3:	ob1 = new("/clone/gift/imbue.c");
			break;
		default: break;
	}

        if(objectp(ob = query_temp("last_damage_from")) ){
                ob1->move(ob);
                ob->add("sj_credit",5);
	        message_vision("\n$N从倭寇头目身上搜出一件物品。\n", ob, ob1);
                message_vision( sprintf(HIW "你趁着混乱冲出了倭寇巢穴，向着渡口飞奔而去。\n" NOR),ob);
                ob->move("/cmds/leitai/dmd/dukou");
	        }
        
        ::die();
}

int do_copy(object target)
{
        mapping skills;
        string *sk;
        object me,ob; 
        int lv,exp,i,t;

        me = this_object();
        ob = target;
        t  = 10+random(2);
        lv = ob->query("max_pot") -100;
        lv = lv * t/10;
        exp = ob->query("combat_exp");
        exp = exp * (100+random(6))/100;

        me->set("max_qi", (int)ob->query("max_qi")*10/10*t/10 );
        me->set("eff_qi", (int)ob->query("max_qi")*10/10*t/10 );
        me->set("qi", (int)ob->query("max_qi")*10/10*t/10 );    
        me->set("max_jing",(int)ob->query("max_jing"));
        me->set("eff_jing",(int)ob->query("max_jing"));
        me->set("jing",(int)ob->query("max_jing"));
        me->set("max_neili",(int)ob->query("max_neili") );
        me->set("neili",(int)ob->query("neili")*t/10 );
        if( me->query("neili") < me->query("max_neili") )
                me->set("neili",(int)me->query("max_neili") );
        me->set("max_jingli",(int)ob->query("max_jingli"));
        me->set("eff_jingli",(int)ob->query("eff_jingli"));
        me->set("jingli",(int)ob->query("jingli"));
        if( me->query("jingli") < me->query("eff_jingli") )
                me->set("jingli",(int)me->query("eff_jingli") );        
        me->set("combat_exp",exp );     

        skills = me->query_skills();
        if (mapp(skills)) {
                sk = keys(skills);
                for (i=0;i<sizeof(sk);i++)
                        skills[sk[i]] = lv;
        }
        me->set("jiali",(int)me->query_skill("force")/6);       
}

void init()
{
	object ob;       

	::init();
	if (interactive(ob = this_player())
	&& query_temp("target") == ob->query("id")) {
		remove_call_out("greeting");
		call_out("greeting", 0, ob);
	}
}

void greeting(object ob)
{
        object me = this_object();
	if (!ob || !present(ob) || query_temp("target") != ob->query("id"))  return;

        me->set("eff_jing",me->query("max_jing"));
        me->set("jing",me->query("max_jing"));
        me->set("eff_qi",me->query("max_qi"));
        me->set("qi",me->query("max_qi"));
	ob->add_busy(1);
	me->add_busy(1);
	me->set_leader(ob);
        command("say 大胆狂徒，竟敢闯到钓鱼岛来放肆！！！\n");
        remove_call_out("kill_ob");
        call_out("kill_ob", 0, ob); 
}

void dest()
{
        destruct(this_object());
}

void kill_ob(object ob)
{
        if (ob->query("id") != query_temp("target")) {
		ob->remove_enemy(this_object());
		ob->remove_killer(this_object());
		this_object()->remove_enemy(ob );
		this_object()->remove_killer(ob );
		tell_object(ob, "这个倭寇不是你的目标，小心行事吧。\n");
		return;
	}
        
        ::kill_ob(ob);

        call_out("checkfight",2);
}

void checkfight()
{
        object me = this_object() , w;
        string weapon;

        if( !objectp(me) || !living(me) || !me->is_fighting() )
                return;

        weapon = me->query("weapon");
        if( stringp(weapon) && weapon!="" && weapon!="null" && !me->query_temp("weapon") ) {
                command("emote 又拿出把兵器。");
                w = new(BINGQI_D(weapon));
                w->move(me);
                w->wield(me);
        }       
        call_out("checkfight",4);
}

void heart_beat()
{
	object env, target , ob = this_object();

	::heart_beat();

	if (! ob || !environment(ob) ) return;

	target = find_player(query_temp("target"));

	if ( !target || (target && target->is_ghost())) {
		remove_call_out("dest");
		call_out("dest", 0, ob);
		return;
	}

	if ( ob->is_fighting()
	 && query("cure") < 3
	 && query("qi") < query("max_qi")/5*4
	 && query("combat_exp") > 5000000 ){
		receive_curing("qi", query("max_qi")/15);
		add("qi", query("max_qi")/5);
		add("cure", 1);
		if (! ob->is_busy())
			tell_room(environment(ob), ob->name()+"暗运真气，脸色顿时好了许多。\n", ({ ob }) ); 
	}
}

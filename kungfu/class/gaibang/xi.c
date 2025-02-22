// Modify by Looklove@sj 2000/9/19

inherit NPC;
inherit F_MASTER;

string ask_yao();
string ask_dan();

void create()
{
        set_name("奚长老", ({"xi zhanglao", "xi", "zhanglao"}));
        set("title", "丐帮九袋长老");
        set("gender", "男性");
        set("age", 60);
        set("long","他乃丐帮六大长老之一,一根钢杖使得出神入话。\n");
        set("attitude", "peaceful");
        set("unique", 1);
        set("str", 25);
        set("int", 18);
        set("con", 20);
        set("dex", 20);
        set("apprentice",1);
        set("qi", 1000);
        set("max_qi", 1000);
        set("jing", 600);
        set("max_jing", 600);
        set("neili", 1400);
        set("max_neili", 1400);
        set("jiali", 100);
        
        set("yao_count",5);
        set("combat_exp", 500000);
        
        set_skill("force", 120); // 基本内功
        set_skill("huntian-qigong", 120); // 混天气功
        set_skill("dodge", 120); // 基本躲闪
        set_skill("xiaoyaoyou", 120); // 千里行乞 
        set_skill("parry", 120); // 基本招架
        set_skill("staff", 140);
        set_skill("fengmo-zhang",150);
        set_skill("lianhua-zhang",120);
        set_skill("strike",120);
        set_skill("begging", 90);
        map_skill("force", "huntian-qigong");
        map_skill("parry","fengmo-zhang");
        map_skill("staff","fengmo-zhang");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("strike", "lianhua-zhang");
        prepare_skill("strike", "lianhua-zhang");
        
        create_family("丐帮", 18, "九袋长老");

        set("inquiry", ([
                "丐帮" : "我们丐帮是天下第一大帮！\n",
                "乔峰" : "唉。。。乔。。。他小以前还跟过我学掌法呢。\n",
                "萧峰" : "他不就是乔峰，我们的前任帮主。\n",
                "学掌法" : "那都是很多年前的事了，他那时常到附近的一个小岛\n"
                           "上埋头苦练。\n",
                "小岛" : "我老了，以前的事也不记得太清楚了，好象是在泉洲附近吧。\n",
                "伤药" : (: ask_yao :),
                "解毒" : (: ask_dan :), 
                "百草丹" : (: ask_dan :), 
 
        ]));
        setup();
        carry_object(__DIR__"obj/bainayi")->wear();
        carry_object(__DIR__"obj/gb_budai9")->wear();
        carry_object(__DIR__"obj/gangzhang")->wield();
}
void init()
{
	::init();
        add_action("do_kill", "kill");
        add_action("do_kill", "tk");
        add_action("do_kill", "teamkill");
        add_action("do_kill", "hit");
}
void attempt_apprentice(object ob)
{
        if (ob->query("family/family_name")
        && ob->query("family/family_name") != "丐帮") {
                command("say 你还是去别的门派看看吧。");
                return;
        }
        if ((int)ob->query("gb_bags") >= 2 
        && ob->query("family/family_name") != "丐帮" ) {
                command("say 丐帮可容不下你这种背信弃义的小人！");
                command("kill "+ob->query("id"));
                return;
        }

        command("say 好吧，希望" + RANK_D->query_respect(ob) +
        "能好好学习本门武功，将来在江湖中闯出一番作为。");
        if (ob->query("gb_bags")<1) ob->set("gb_bags", 1);
        command("recruit " + ob->query("id"));
        ob->set("title",sprintf("丐帮大勇分舵%s袋弟子",
                chinese_number(ob->query("gb_bags"))) );
        ob->set("gb/fenduo","大勇分舵");
        ob->set("gb/alloted",1);
        ob->set("class","beggar");
}
string ask_yao()
{
        object me;
        me = this_player();       
   
        if ( me->query("family/family_name") != "丐帮")
                return RANK_D->query_respect(me) + 
                "非我丐帮好汉，不知此话从何谈起？";

        if ((int)me->query("max_neili" ) < 100)
                return RANK_D->query_respect(me) + 
                "目前武功还没有根基，伤药留给更需要它的帮中兄弟吧。";
        
        if ((int)me->query("eff_qi",1)==(int)me->query("max_qi",1))
               return RANK_D->query_respect(me) + 
                "并没有受伤，伤药留给受了伤的帮中兄弟吧。";
        
        if (  present("gaibang shangyao", me) )
                return RANK_D->query_respect(me) + 
                "伤药很珍贵，你身上还有，还是留一些给其他帮中兄弟吧，丐帮弟子最讲义气。！";
        
        if (query("yao_count") < 1) return "目前伤药没有了，等会吧";
         
        new("/d/gb/npc/obj/yao")->move(me);
        add("yao_count", -1);

        message_vision("$N获得一包丐帮伤药。\n",me);
        return "我这里有一包丐帮伤药，功效显著，你拿去护身吧。";
}
string ask_dan()
{
        mapping fam = this_player()->query("family");
        object ob;
        
        if(!fam || fam["family_name"] != "丐帮")
                return "快去找医生吧，我可没办法！";
        
        if((int)this_player()->query("eff_jing",1)==(int)this_player()->query("max_jing",1))
                return "你好象没有中毒嘛，来找我做什么？";
        
        if(query("yao_count") < 1)
                return "你来晚了，百草丹全部发完了，快去自己找大夫吧。";
        
        if (present("bai caodan", this_player()) )
                return RANK_D->query_respect(this_player()) + 
                "百草丹很珍贵，你身上还有，还是留一些给其他帮中兄弟吧，丐帮弟子最讲义气。！";
        
        add("yao_count", -1);
        ob = new("/d/gb/npc/obj/bcd");
        ob->move(this_player());
        return "我这里有一包百草丹，善解蛇虫杂毒，不知是否对你症况。";
}
int do_kill(string arg)
{
        object ob,ob2; 
        object me = this_player();
        ob2 = this_object();

        if (!arg) return 0;
        ob = present(arg, environment(me));
        if (ob == this_object() || ob == me) return 0;
        if (!ob || !ob->is_character()) return 0;
 
        
        if (userp(ob) && ob->query("family/family_name") == "丐帮") {
                if (me->query("family/family_name") == "丐帮") { 
                message_vision(ob2->name()+"对$N叫道：你居然杀自己的同门？我宰了你！\n", me);
                kill_ob(me);
                }
                else {
                        message_vision(ob2->name()+"对$N喝道：大胆，居然敢在我分舵里撒野！\n", me);
                        kill_ob(me);
                }
                return 1;
        }
        return 0;
}

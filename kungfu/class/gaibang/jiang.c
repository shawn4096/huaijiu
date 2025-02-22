// jiang.c 蒋舵主
// update by looklove 2000,7,3
// Modify By Looklove 2000/10/21
// Modified by looklove 2001/5/24 for xlz quest

inherit NPC;
inherit __DIR__"gb_up.c";
int action_1();
int action_2();
int action_3();
string ask_fenduo();
string ask_zeizi();

void create()
{
        set_name("蒋舵主", ({"jiang duozhu", "jiang" }));
        set("title", "丐帮八袋舵主");
        set("gender", "男性");
        set("age", 47);
        set("long",
       		"他是八袋舵主，掌管大义分舵。\n");
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 25);
        set("int", 20);
        set("con", 25);
        set("dex", 25);
        set("unique", 1);

        set("qi", 700);
        set("max_qi", 700);
        set("jing", 500);
        set("max_jing", 500);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 100);

        set("combat_exp", 120000);

        set_skill("force", 100); // 基本内功
        set_skill("huntian-qigong", 100); // 混天气功
        set_skill("strike", 100); // 基本拳脚
        set_skill("blade",90);
        set_skill("liuhe-daofa",90);
        set_skill("dodge", 90); // 基本躲闪
        set_skill("xiaoyaoyou", 90); // 千里行乞
        set_skill("parry", 90); // 基本招架
        set_skill("xianglong-zhang",90);
        map_skill("parry","liuhe-daofa");
        map_skill("strike","xianglong-zhang");
        map_skill("blade","liuhe-daofa");
        map_skill("force", "huntian-qigong");
        map_skill("dodge", "xiaoyaoyou");

        create_family("丐帮", 19, "八袋弟子");
        set("chat_chance", 1);
        set("chat_msg", ({
                "蒋舵主叹道:真怀念以前和乔帮主一起饮酒的日子啊。\n",
        }) );
        set("inquiry", ([
                "丐帮" : "我们丐帮是天下第一大帮！\n",
                "升袋" : (: ask_me :),
                "乔帮主" : (: action_1 :),
                "喝酒" : (: action_2 :),
                "小岛" : (: action_3 :),
                "分舵事务":(: ask_fenduo :),
                "贼人" : (: ask_zeizi :),
                "贼子" : (: ask_zeizi :),
                "萧峰" : "不管怎样，他永远是我的乔帮主。\n",
        ]));
        setup();
        carry_object(__DIR__"obj/gb_budai8")->wear();
        carry_object(__DIR__"obj/bainayi")->wear();
        carry_object(BINGQI_D("blade"))->wield();
}

void init()
{
        add_action("do_kill", "kill");
        add_action("do_kill", "tk");
        add_action("do_kill", "teamkill");
        add_action("do_kill", "hit");

        ::init();
        add_action("action_4", "han");
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
                message_vision(ob2->name()+"对$N叫道：你居然杀自己的同门？我宰了你！"+ob->name()+"快走！\n", me);
                kill_ob(me);
                }
                else {
                        message_vision(ob2->name()+"对$N喝道：大胆，居然敢在我面前撒野！"+ob->name()+"快走，让我来！\n", me);
                        kill_ob(me);
                }
                return 1;
        }
        return 0;
}

void dest(object ob)
{
    	if (ob) destruct(ob);
}

int get_object(object ob)
{
        if(userp(ob)) return 1;

        return 0;
}
int accept_object(object who, object ob)
{
    	if (promotion_checking(who,ob)) {
        	call_out("dest", 1, ob);
        	return 1;
    	}
    	return 0;
}

int action_1()
{
        object who = this_player();
        who->set_temp("mark/乔1", 1);

        command("say 啊，原来这位" + RANK_D->query_respect(who) +
                "也听过我们帮主的大名。想当初，帮主天天和我们喝酒" +
                "一点都没有帮主的架子。");
        return 1;
}

int action_2()
{
        object who = this_player();
        if (!who->query_temp("mark/乔1") ) {
                command("say 喝酒，喝酒。。。");
                return 1;
        }
        else {
                who->set_temp("mark/乔2", 1);
                command("say 哈哈，原来" + RANK_D->query_respect(who) +
                        "也是性情中人！当年，帮主他每天都要和我们喝上一轮" +
                        "才到不远处的一个小岛上练掌。");
                return 1;
        }
}

int action_3()
{
        object who = this_player();
        if ( !who->query_temp("mark/乔2")
	|| who->query("family/family_name") != "丐帮"
	|| who->query_condition("killer")) {
                command("say 什么小岛，鸟岛，我又不是打鱼的。");
                return 1;
        }
        else {
                command("say 这位" + RANK_D->query_respect(who) +
                        "想到那看看吗？以前都是我送乔帮主去的。" +
                        "要去喊(han)我一声就行了。");
                command("hehehe");
                who->set_temp("mark/乔3", 1);
                return 1;
        }
}

int action_4()
{
        object who = this_player();
        object *inv = deep_inventory(who);
        object *obj;
        if ( !who->query_temp("mark/乔3") ) {
                command("say 没事你乱嚷嚷什么！");
                return 1;
        }
        obj = filter_array(inv,(:get_object:));
        if(sizeof(obj)) {
                command("say 你身上背的是谁啊，怎么还捎带一个？");
                return 1;
        }
        else {
        command("say 好，我这就带你去。");
        message_vision("$N解开舢板的绳索，挟着$n跳了上去，然后竹篙" +
                       "一撑，就不见了。\n", this_object(),who);
        who->move("/d/gb/island1");
        tell_object(who,"舢板在渔船中穿来插去，不一会儿来到了一孤岛上。\n");
        tell_object(who,"蒋舵主对着你说：这就是以前帮主练功的小岛。\n");
        tell_object(who,"蒋舵主说：好了，我先回去，你在这自己呆一会吧。\n");
        tell_object(who,"蒋舵主对着你挥了挥手。\n");
        return 1;
        }
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
        command("recruit " + ob->query("id"));
        if (ob->query("gb_bags")<1) ob->set("gb_bags", 1);
        ob->set("title",sprintf("丐帮大信分舵%s袋弟子",
                chinese_number(ob->query("gb_bags"))) );
        ob->set("gb/fenduo","大信分舵");
        ob->set("gb/alloted",1);
        ob->set("class","beggar");
}
string ask_fenduo()
{
	object me = this_player();
	object ob = this_object();
	int x = me->query("sl_job");

        if ( me->query("family/family_name") != "丐帮")
                return RANK_D->query_respect(me) + "非我丐帮好汉，不知此话从何谈起？";
        if(!me->query_temp("h7g/fenduo"))
        	return "最近日子很平淡，没什么大不了的事儿。";
        if (me->query_temp("h7g/fenduo")!=1)
        	return "最近我这里没什么事情，多谢费心。";
        if (me->query("h7g/xlz_job")||ob->query("h7g/xlz_jobt"))
                return "最近没什么事情，多谢费心。";
        me->set_temp("h7g/xlz_joba",x+1);
        me->set_temp("h7g/xlz_job",1);
        ob->set("h7g/xlz_jobt",me->query("id"));
        return "少林方丈前日来信：最近有若干贼子准备攻打恒山。帮主吩咐着你护送少林大师前往救援，以十次以上为好";
}
string ask_zeizi()
{
	object me = this_player();
	object ob = this_object();
	int x = me->query("sl_job");
	int y = me->query_temp("h7g/xlz_joba");

        if (!y||(string)ob->query("h7g/xlz_jobt")!=(string)me->query("id"))
        	return "少林方丈前日来信：最近有若干贼子准备攻打恒山。";
        if (y<(x+10))
        	return "帮主吩咐，早日将任务完成。";

        me->set_temp("h7g/xlz_jobv",1);
        return "帮主吩咐，请你去总舵一趟。";
}

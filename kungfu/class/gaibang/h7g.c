// modified by explorer, 3/9/97
// cool 99/2/9
// Looklove 2000/8/25
// Looklove Modify at 2001/1/19
// Looklove Modify at 2001/4/7
// Looklove Modify at 2001/5/3

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
int ask_ji();
int ask_bag();
int ask_up();

void consider();
int pass_chuanwei(object me, object ob);


void create()
{
    	object ob;

    	set_name("洪七公", ({"hong qigong", "hong", "qigong"}));
    	set("nickname", HIY"九指神丐"NOR);
    	set("gender", "男性");
    	set("age", 65);
    	set("per",24);
    	set("long", "他就是丐帮第十七任帮主，号称“北丐”的洪七公老爷子。\n");
    	set("attitude", "friendly");
        set("no_bark",1);
        set("dgb/wugou",6);
        set("str", 30);
        set("con", 30);
        set("dex", 30);
    	set("int", 22);
    	set("max_qi", 8800);
    	set("max_jing", 3600);
    	set("neili", 24000);
    	set("max_neili", 13000);
    	set("jiali", 200);
    	set("eff_jingli",4000);
    	set("combat_exp", 5400000);

    	set_skill("force", 300);
    	set_skill("huntian-qigong", 300);    // 混天气功
    	set_skill("strike", 300);            // 基本掌法
    	set_skill("xianglong-zhang", 300);   // 降龙十八掌
        set_skill("literate",150);           // 读写
    	set_skill("dodge", 300);             // 基本躲闪
    	set_skill("xiaoyaoyou", 300);        // 逍遥游
    	set_skill("parry", 300);             // 基本招架
    	set_skill("stick", 300);             // 基本棍杖
    	set_skill("dagou-bang", 300);        // 打狗棒法
    	set_skill("begging", 200);           // 叫化绝活
    	set_skill("checking", 200);          // 道听途说
    	set_skill("bangjue",200);            // 棒决
    	set_skill("dagou-zhen",200);	     // 打狗阵
        set_skill("lianhua-zhang",300);      // 莲花掌
        set_skill("stealing",200);           // hehe

    	map_skill("force", "huntian-qigong");
    	map_skill("strike", "xianglong-zhang");
    	map_skill("dodge", "xiaoyaoyou");
    	map_skill("parry", "dagou-bang");
    	map_skill("stick", "dagou-bang");
    	prepare_skill("strike", "xianglong-zhang");

    	set("chat_chance_combat", 100);
    	set("chat_msg_combat", ({
        	(: perform_action, "strike.xiao" :),
        	(: perform_action, "stick.chan" :),
        	(: perform_action, "stick.ban" :),
        	(: perform_action, "stick.yin" :),
        	(: perform_action, "stick.pi" :),
        	(: perform_action, "stick.shuangjue" :),
        	(: exert_function, "powerup" :),
        	(: perform_action, "strike.paiyun" :),
        	(: perform_action, "strike.kanglong" :),
		(: perform_action, "strike.xiao" :),
        }));

    	set("chat_chance", 1);
    	set("chat_msg", ({
        	"洪七公叹了口气道：“唉……何时能再吃到蓉儿做的「叫化鸡」啊……”\n",
        	"洪七公说道：“老毒物的功夫日见精进，看来我得想点办法对付他。”\n",
        	"洪七公喃喃道：“我们丐帮的「降龙十八掌」是天下最霸道的掌法。”\n",
        	}));

    	set("inquiry", ([
        	"老毒物" : "老毒物就是我的死对头，江湖上人称西毒的欧阳峰。\n",
        	"欧阳峰" : "他是我的死对头，江湖上人称西毒。\n",
        	"西毒" : "这个...这个...\n",
        	"rumors" : "最近没听说什么消息。\n",
        	"郭靖" : "那是我的好徒儿，就是人笨了点。\n",
        	"黄蓉" : "那小丫头可是个机灵鬼，菜做的可真不赖。\n",
        	"黄药师" : "他啊，够博学多才，不过我还是更喜欢他那个小丫头。\n",
        	"东邪" : "他啊，够博学多才，不过我还是更喜欢他那个小丫头。\n",
        	"南帝" : "大理皇族，不敢高攀。\n",
        	"王重阳" : "那可是个武学奇才，老叫化可不想和他打架。\n",
        	"中神通" : "江湖上现在很多人自命不凡，都以为自己是王重阳，哈哈！\n",
        	"丐帮" : "连我丐帮都不知道，我看你有点秀斗了！\n",
        	"打狗棒" : "这个...这个...你想如何？\n",
        	"降龙掌" : "没事别乱打听，小心我一掌拍死你。\n",
        	"亢龙有悔" : "没事别乱打听，小心我一掌拍死你。\n",
        	"莲花掌" : "没事别乱打听，小心我一掌拍死你。\n",
        	"叫化鸡" : (: ask_ji :),
        	"升袋":    (: ask_bag :),
        	"传位":    (: ask_up :),
        	]));

    	create_family("丐帮", 17, "帮主");
        set_temp("apply/damage", 70);
        set_temp("apply/dodge", 80);
        set_temp("apply/attack", 80);
        set_temp("apply/armor", 70);

    	setup();

    	if (clonep())
    	{
        	ob = unew(BINGQI_D("yuzhu_bang"));
        	if (!ob) ob = unew(BINGQI_D("zhubang"));
        	ob->move(this_object());
        	ob->wield();
        	carry_object(__DIR__"obj/bainayi")->wear();
        	carry_object(__DIR__"obj/gb_budai10")->wear();
    	}
}

void attempt_apprentice(object ob)
{
    	if ((int)ob->query("gb_job",1) < 400)
    	{
        	command("say  做我的弟子要为丐帮出生入死，" + RANK_D->query_respect(ob) + "在帮中的积功似乎还少了一些。\n");
        	return;
    	}
    	if ((string)ob->query("family/family_name") != "" &&
        (string)ob->query("family/family_name") != "丐帮")
    	{
        	command("say " + RANK_D->query_respect(ob) + "既然已有名师指点，何必又来拜老叫化呢？\n");
        	return;
    	}
    	if ((int)ob->query("gb_bags")<6)
    	{
        	command("say " + RANK_D->query_respect(ob) + "在帮中职位太低，先加油升袋吧。\n");
        	return;
    	}
    	command("chat 哈哈哈，老叫化入土之前还能找到"+RANK_D->query_respect(ob)+"这样一个可造之才,丐帮后继有人了。\n");
    	command("recruit " + ob->query("id"));

        ob->set("title",sprintf("丐帮总舵%s袋弟子",
                chinese_number(ob->query("gb_bags"))));
    	ob->set("class", "beggar");
        ob->set("gb/fenduo","总舵");
        ob->set("gb/alloted",1);
    	return;
}

void init()
{
        add_action("do_kill", "kill");
        add_action("do_kill", "tk");
        add_action("do_kill", "teamkill");
        add_action("do_kill", "hit");
}
int ask_bag()
{
    	object me=this_player();
    	int bag = me->query("gb_bags");
    	int lvl = bag-5;
    	mapping skl;
    	string *sname;
    	int i;
    	string *skilllimit = ({
        	"begging","bangjue","checking","dagou-zhen","literate",
        	});
    	int *lvllimit = ({
        	200,200,200,200,300,
        	});


    	if( me->query("family/family_name")!="丐帮" )
    	{
        	command("say " + RANK_D->query_respect(me) + "与我丐帮素无来往，此话不知从何说起。\n");
        	return 1;
    	}
    	if (bag<6)
    	{
        	command("say " + RANK_D->query_respect(me) + "在帮中职位太低，先加油升袋吧。\n");
        	return 1;
    	}
    	if( bag==9)
    	{
        	command("say " + RANK_D->query_respect(me) + "在帮中已是九袋长老，还想升到哪里去？\n");
        	command("sneer "+me->query("id"));
        	me->set("title","丐帮九袋长老");
        	return 1;
    	}
    	if ((int)me->query("shen") < 400000*lvl)
    	{
        	command("say 我丐帮乃堂堂名门正派，"+RANK_D->query_respect(me)
            	+"是否应该多做点侠义之事。");
        	return 1;
    	}

    	if( me->query("gb_job2") < 100*lvl)
    	{
        	command("say 我丐帮乃堂堂名门正派，"+RANK_D->query_respect(me)
            	+"应该为国为民多做点贡献才好。");
        	return 1;
    	}

    	skl = me->query_skills();
    	if (mapp(skl)) sname = keys(skl);

    	for(i=0; i<sizeof(skl); i++)
    	{
        	me->set_skill(sname[i],skl[sname[i]]+lvl);
    	}

    	for(i=0; i<sizeof(skilllimit); i++)
    	{
        	if( me->query_skill(skilllimit[i])>lvllimit[i] )
            	me->set_skill(skilllimit[i],lvllimit[i] );
    	}

    	me->add("gb_bags",1);
    	bag=bag+1;
    	me->add("max_neili",10*(bag-3));
    	command("applaud " + me->query("id"));
    	if( bag==7)
    	{
        	command("say 干得好！从今天开始，你就是丐帮" +
            	chinese_number(bag) +
            		"袋弟子，好好干！\n");
        	me->set("title",sprintf("丐帮总舵%s袋弟子",
            		chinese_number(bag)) );
    	}
    	else if(bag==8)
    	{
        	command("say 干得好！从今天开始，你就是丐帮" +
            	chinese_number(bag) +
            	"袋舵主，好好干！\n");
        	me->set("title",sprintf("丐帮%s袋舵主",
            	chinese_number(bag)) );
    	}
    	else if(bag==9)
    	{
        	command("say 干得好！从今天开始，你就是丐帮" +
            	chinese_number(bag) +
            	"袋长老，好好干！\n");
        	me->set("title",sprintf("丐帮%s袋长老",
            	chinese_number(bag)) );
    	}
    	return 1;
}

int filldata(object obj1)
{
        if(wiz_level(obj1)) return 0;
        if(!environment(obj1)) return 0;
        else return 1;
}



int ask_up()
{
    	object me=this_player(),ob=this_object();
    	int skill, bag = me->query("gb_bags");
    	string *applied_id;

    	mixed *ob_list;
    	int max,i;
    	object obj1;

    	skill = me->query_skill("xianglong-zhang",1);
    	if( me->query("family/family_name")!="丐帮" )
    	{
        	command("say " + RANK_D->query_respect(me) + "与我丐帮素无来往，此话不知从何说起。\n");
        	return 1;
    	}
    	if( bag<9)
    	{
        	command("say " + RANK_D->query_respect(me) + "在帮中地位太低，传位给你恐怕无法说服众弟子。\n");
        	return 1;
    	}
    	if ((int)me->query("gb_job",1) < 1000)
    	{
        	command("say " + RANK_D->query_respect(me) + "在帮中的积功似乎还少了一些，恐怕难以折服众弟子。\n");
        	return 1;
    	}
    	if( me->query("shen")<1500000)
    	{
        	command("say " + RANK_D->query_respect(me) + "的侠义正气，恐怕无力领导丐帮数万弟子。\n");
        	return 1;
    	}

    	if(me->query("xy/job")+me->query("gb_job2")<500)
    	{
        	command("say 我丐帮乃堂堂名门正派，"+RANK_D->query_respect(me)
            	+"应该为国为民多做点贡献才好。");
        	return 1;
    	}
    	if( me->query_temp("gb_chuanwei") )
    	{
        	command("say " + RANK_D->query_respect(me) + "已经是丐帮帮主，何苦又来找我开玩笑。\n");
        	return 1;
    	}
    	if( me->query_skill("dagou-bang",1)<280 || me->query_skill("xianglong-zhang",1)<280 )
    	{
        	command("say 打狗棒法和降龙十八掌乃我丐帮祖传绝技，" + RANK_D->query_respect(me) + "在这方面的修为是否稍差了一点。\n");
        	return 1;
    	}

    	if( !present("yuzhu bang",ob) )
    	{
        	command("say 我的玉竹棒跑哪里去了？糟了，这下可没办法传位了。");
        	return 1;
    	}

    	ob_list = users();
    	ob_list = filter_array(ob_list, (: filldata :));
    	max=sizeof(ob_list);
    	for (i=0;i<max;i++)
    	{
        	obj1 = ob_list[i];
        	if (obj1->query_temp("gb_chuanwei") )
        	{
            	command( "say 我已经把帮主之位传给" + obj1->query("name") +"了。\n" ) ;
            	return 1;
        	}

    	}

    	command("look "+me->query("id"));
    	command( "say 欲受我衣钵，先考考你的武功。" );

    	if ( !pass_chuanwei(me, ob ) ) return 1;
    	if ( !pass_chuanwei(me, ob ) ) return 1;
    	if ( !pass_chuanwei(me, ob ) ) return 1;
    	if ( !pass_chuanwei(me, ob ) ) return 1;
    	if ( !pass_chuanwei(me, ob ) ) return 1;
    	if ( !pass_chuanwei(me, ob ) ) return 1;
    	if ( !pass_chuanwei(me, ob ) ) return 1;

    	if( pointerp(applied_id = me->query_temp("apply/id"))
        	 && sizeof(applied_id) )
        	me->set_temp("apply/short",
             ({"丐帮第十八代帮主"+" "+me->name()+"("+applied_id[0]+")"}));
    	else
        {
        	me->set_temp("apply/long",
            	({"丐帮第十八代帮主"+" "+me->name()+"("+me->query("id")+")"}));
        	me->set_temp("apply/short",
            	({"丐帮第十八代帮主"+" "+me->name()+"("+me->query("id")+")"}));
        }
	me->add_temp("apply/strength", skill/10);
    	command("chat 老叫化今日将丐帮帮主之位传给"+me->query("name")+"，哈哈，丐帮后继有人了。");
    	message_vision("洪七公交给$N一根玉竹棒。\n",me);

    	me->set_temp("gb_chuanwei",1);
    	present("yuzhu bang",ob)->move(me);

    	return 1;
}

int pass_chuanwei(object me, object ob)
{
    	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);

    	if (!present(me,environment(ob)) || me->query("qi") <= 0
        	|| me->query("jing") <= 0 || me->query("jingli") <= 0)
    	{
        	command("say 武功如此之差，如何传我衣钵？！");
        	ob->reincarnate();
        	return 0;
    	}
    	return 1;
}

int accept_object(object who, object ob)
{
    	object ob_yzz, me = this_object();

    	if (ob->query("food_supply") <= 0)
        	return 0;
    	if ((string)ob->query("name") != "叫化鸡" ||
        	who->query_temp("marks/get-ji"))
    	{
        	command("say 老叫化对" + (string)ob->query("name") + "没什么兴趣……");
        	return 0;
    	}

    	if (query("food") >= max_food_capacity() - ob->query("food_supply"))
    	{
        	command("say 老叫化现在饱得很。");
        	return 0;
    	}

    	command("say 啊……这正是我想吃的叫化鸡呀！");
    	command("eat ji");
    	command("say 想不到你小小年纪，心思却很细，就跟当年的蓉儿一样！");
        call_out("dest", 1, ob);

    	if ((string)who->query("family/family_name") != "丐帮")
    	{
        	command("say " + RANK_D->query_respect(who) + "你还呆在这里干什么？");
        	return 1;
    	}

    	if( ob_yzz = present("yuzhu bang", me) )
    	{
        	ob_yzz->move(who);
        	write("这根竹棒跟随我多年了，就送给你作见面礼吧。");
        	return 1;
    	}
    	else
    	{
        if((time()-who->query("gb/jitime"))>=100) {
        	who->add("combat_exp",random(200));
        	who->add("potential",random(100));
        	if(who->query("potential")>who->query("max_pot"))
        	who->set("potential",who->query("max_pot"));
        	who->set("gb/jitime",time());
        }
        if(random(150) == 50 && who->query("family")
             && who->query("family/family_name") == "丐帮"
             && who->query_skill("xianglong-zhang", 1) > 200
             && !who->query("xlz/hang")
             && !who->query_temp("xlz/hang"))
             call_out("kanglong", 10, who, this_object());
             	return 1;
    	}
	return 1;
}

void dest(object obj)
{
            if(!obj) return;
            destruct(obj);
}

int ask_ji()
{
    	object ob;
    	ob=this_player();

    	if (!ob->query_temp("marks/jiaohua-ji"))
    	{
        	command("haha");
        	command("say "+RANK_D->query_respect(ob)+",我告诉你吧,这普天下最好吃的叫化鸡就是蓉儿那个小丫头做的!\n");
        	command("say 修文这笨小子也不知道跑哪玩去了?叫他去襄阳找蓉儿给我带只鸡,几个月也不回来.\n");
        	ob->set_temp("marks/jiaohua-ji",1);
        	return 1;
    	}
    	else
    	{
        	command("say 你也想吃吗?");
        	return 1;
    	}
}

int kanglong(object me, object ob)
{
    	if(!ob || !me || !living(ob) || !living(me)
        	|| environment(ob) != environment(me)
        	|| ob->is_fighting() || me->is_fighting())
        	return 0;

    	command("consider");
    	command("say 你这娃娃真是不赖，能做出和黄丫头同样好的美味来。");
        if ( me->query("combat_exp") > 2000000 && random((int)me->query_con())>10){
  		command("say 我也不能白吃了你的菜，这样吧。");
    		command("whisper "+me->query("id")+" 你去西域"YEL"鸣沙山"NOR"住上一阵子，有没有造化就看你自己了。");
    		me->set_temp("xlz/hang", 1);
		return 1;
        }
        else
        command("say 看你资质不错，等以后功夫练好了来找我吧。");
        command("whisper "+me->query("id")+" 到时候记得再给我带几只叫化鸡。味道不错，hoho。");
        return 1;
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
                        message_vision(ob2->name()+"对$N喝道：大胆，居然敢在我面前撒野！\n", me);
                        kill_ob(me);
                }
                return 1;
        }
        return 0;
}

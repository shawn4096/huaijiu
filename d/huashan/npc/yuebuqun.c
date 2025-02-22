// NPC: /d/huashan/npc/yuebuqun.c
// Date: Look 99/03/25
// Modify by Looklove 2000,12,15

inherit NPC;
inherit F_MASTER;

#include <ansi.h>
string ask_zhengqi();
string ask_zixia();
string ask_me1();
string ask_me2();
string ask_pay();

string ask_fail();

void create()
{
        set_name("岳不群",({"yue buqun", "yue", "buqun" }));
        set("title","华山派第十三代掌门人");
        set("nickname","君子剑");
        set("long", "这就是在江湖中侠名远播，疾恶如仇，华山派掌门人。\n");
        set("age", 40);
        set("attitude", "peaceful");
        set("no_bark",1);
        set("shen_type", 1);
        set("per",25);
        set("pur",10);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        
        set("max_qi",3800);
        set("qi", 3800);
        set("max_jing", 2400);
        set("jing",2400);
        set("eff_jingli", 2700);
        set("jingli", 2700);
        set("max_neili", 5500);
        set("neili", 5500);
        set("jiali", 50);
        set("combat_exp", 2400000);
        set("score", 30000);
        set("chat_chance_combat",30);
        set("chat_msg_combat", ({
        (: perform_action, "sword.sanqingfeng" :),
        }));
// 48          set_skill("strike", 180);
// 49          set_skill("hunyuan-zhang", 180);
        set_skill("poyu-quan", 180);
        set_skill("cuff", 180);
        set_skill("sword",  180);
        set_skill("dodge",  180);
        set_skill("force",  180);
        set_skill("parry",  180);
        set_skill("literate",100);
        set_skill("zixia-gong", 180);
        set_skill("huashan-jianfa",  180);
        set_skill("huashan-shenfa",  180);
        set_skill("zhengqi-jue", 180);

        map_skill("dodge", "huashan-shenfa");
        map_skill("force","zixia-gong");
        map_skill("sword","huashan-jianfa");
        map_skill("parry","huashan-jianfa");
// 66          map_skill("strike","hunyuan-zhang");
        map_skill("cuff","poyu-quan");
// 68          prepare_skill("strike","hunyuan-zhang");
        prepare_skill("cuff","poyu-quan");
        create_family("华山派",13,"掌门");

        set("inquiry", ([
              "紫霞秘籍" : (: ask_zixia :),
              "失败" : (: ask_fail :),
              "惩恶扬善" : (: ask_me1 :),
              "复命" : (: ask_me2 :),
              "正气诀" : (: ask_zhengqi :),                        
//		"补偿" : (: ask_pay :),
        ]));

        setup();
        carry_object(BINGQI_D("sword/sword"))->wield();
        carry_object(ARMOR_D("armor/cloth"))->wear();
}

void heart_beat()
{
	::heart_beat();

	clear_conditions_by_type("poison");
	if( !is_fighting() && living(this_object()))
		reincarnate();
}

void init()
{
        object me, ob;
        ::init();
        ob = this_player();
        me = this_object();
        if (interactive(ob = this_player()) && !is_fighting()) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }       
     
}

void greeting(object me)
{
        int shen;
         if(!me) return;
        shen = me->query("shen");
        if(shen <= -200000 && me->query("family/family_name") == "华山派"){
        	command("chat* slap "+me->query("id"));
        	command("slap "+me->query("id"));
        	command("say 你满眼瘴气，身带邪气，从今天起你不再是华山弟子了！");
        	command("expell " + me->query("id"));
	}
	if(shen <0 && shen > -200000 && me->query("family/family_name") == "华山派"){
		command("sigh "+me->query("id"));
		command("say 我看你满眼瘴气，身带邪气，最近是不是在外面做了什么坏事？");
		command("say 如果被我查到你做过有辱我华山声名的事，我定不饶你！");
	}
}


string ask_pay()
{
        object me = this_player();
        mapping fam;

        fam = me->query("family");
        if (!fam || fam["family_name"] !="华山派")
           return RANK_D->query_respect(me)+"不会是想转派吧？BBB 可是不会准许的。\n";
        if( me->query("hs/rec") )
           return RANK_D->query_respect(me)+"还想要补偿？这个一人只能要一次。\n";

           me->set_skill("force", me->query("max_pot") - 100);
           me->set_skill("sword", me->query("max_pot") - 100);
           me->set("hs/rec", 1);

        return  "好了，你的基本内功、剑法都给你升到目前经验上限了，别再去烦 hunthu 跟 darken 了。\n" ;
}


void attempt_apprentice(object ob)
{
        mapping fam;
        if ( mapp(fam=ob->query("family"))
         && (string)fam["family_name"] != "华山派"  
         && (int)ob->query("is/huashan")==1 ) {
              message_vision(CYN "$N！你这个华山派的叛徒还回来干什么 ？？？\n"NOR, ob );
              command("slap "+ob->query("id"));
              return;
        }
        if ( ob->query("gender") != "男性" ){
              command("say 我只收男徒，" + RANK_D->query_respect(ob) + "请回吧。");
              return;
        }
        if ((int)ob->query("shen") < 0) {
              command("say 我华山派乃是堂堂名门正派，对弟子要求极严。");
              command("say 在德行方面，" + RANK_D->query_respect(ob) + "是否还做得不够？");
              return;
        }
        command("say 好吧，我就收下你了,你可要为我们华山派争口气。");
        ob->set("is/huashan",1);
        command("recruit " + ob->query("id"));
}

string ask_me1()
{
        int i;
        object ob, me, name1, ling;
        me=this_player();
        ob = this_object();
        ling = present("ling pai", me);
        name1 = me->query("id");
        i = me->query("shen");

        if (me->query("shen") < 10000)
           return "你眼露凶光, 还想去惩恶扬善? "; 

        if (me->query_temp("hs/jobji"))
           return "你不能光说呀，倒是做出点成绩给我看看！\n";

        if ((int)me->query("combat_exp") < 100000)
           return "你武功未成，这么危险的任务还是别做了！\n";

        if (me->query("job_name") == "惩恶扬善")
           return "现在没有听说有恶人为害百姓，你自己去修习武功去吧！";

        if(me->query_condition("job_busy"))
           return "你现在正忙着做其他任务呢！";

        ob=new(__DIR__"obj/ling");
        ob->set("owner",getuid(me));
        me->set_temp("hs/jobji",1);
        command("nod "+me->query("id"));
        ob->move(me);
        ob->set_temp("hsjob", name1);
        ob->set_temp("job_busy",me->query_condition("hs_job"));
        me->set("job_name","惩恶扬善");
        me->apply_condition("hs_job",25 + random(5));
        me->apply_condition("job_busy", 10);
        tell_object(me, HIC"岳不群给你一只令牌。\n");
        return "听说现在华山附近经常出现一些恶贼，骚扰百姓，你去巡视一下，遇到恶人不可手软。\n";
}

string ask_zhengqi()
{
        mapping fam;
        object me, ob;
        int shen, exp, i;
        me = this_player();
        ob = this_object();
        shen = (int)me->query("shen", 1);
        exp = (int)me->query("combat_exp", 1);
        i = (shen - exp);
        fam = me->query("family");
        if (!fam || fam["family_name"] !="华山派")
           return RANK_D->query_respect(me)+"与本派素无来往，不知此话从何谈起？\n";
        if( i < 1000 )
           return "你的侠义之气不够，如何叫我指点你的正气诀？\n";
        if( (int)me->query_skill("zhengqi-jue", 1) < 150 )
           return "你的正气诀未到火候，恐怕我无法指点你。\n";
        if( (int)me->query_skill("zhengqi-jue", 1) > 200 )
           return "你的正气诀已到火候，恐怕我无法指点你。"; 
        if( (int)me->query("jing", 1) < 100 )
           return "你现在身体状况太差了，你无法领悟正气诀的绝妙之处。\n";
        if( (int)me->query("potential", 1) < 2 )
           return "你现在潜能不足，我无法指点你关于正气诀。\n";
        me->improve_skill("zhengqi-jue", 100 + random(100));
        me->add("shen", -1000);
        me->add("potential", -1);
        me->receive_damage("jing", random(100));
        tell_object(me, HIC"你感到心中激荡着侠义正气。\n"NOR);
        return  "好吧，既然你问起我正气诀，我就指点你一下。\n" ;
}

string ask_me2()
{
        return "你的令牌呢？\n";
}
        
int accept_object(object me, object ling)
{
        object name1;
        int exp,pot,getshen,job_busy,total_job_times;
        name1 = me->query("id");

	if( ling->query("id") != "ling pai")
              return notify_fail("岳不群说道：惭愧呀，华山派居然出了你这样的骗子！\n");
        if( ling->query_temp("mmr") != name1 ){
                command("hmm "+ me->query("id"));
                me->add("shen", -(int)me->query("hs_job",1));
                me->delete_temp("hs/jobji");
                call_out("destroying", 1, ling);
                return notify_fail("岳不群说道：你怎么这么没用？没敢去找到恶贼？\n");
        }
        if( ling->query_temp("hsjob") != name1 ) {
                command("hmm "+ me->query("id"));
                me->add("shen", -(int)me->query("hs_job",1) * 5);
                me->delete_temp("hs/jobji");
                call_out("destroying", 1, ling);
                return notify_fail("岳不群说道：这是你的令牌么？\n");
        }
        if( (int)ling->query_temp("done", 1) < 2)
              return notify_fail("岳不群说道：你还没完成师傅的任务呢。\n");
        if ( !me->query_temp("hs/jobji"))
                {
                command("hmm "+ me->query("id"));
                me->add("shen", -(int)me->query("hs_job",1) * 5);
                me->delete_temp("hs/jobji");
                call_out("destroying", 1, ling);
                return notify_fail("岳不群说道：你的令牌从哪里偷来的？\n");
                }
        if ( !me->query_condition("hs_job")){
                command("hmm "+ me->query("id"));
                me->add("shen", -(int)me->query("hs_job",1) * 5);
                me->delete_temp("hs/jobji");
                call_out("destroying", 1, ling);
                return notify_fail("岳不群说道：你怎么去了这么长时间？\n");
         } 
        write("岳不群看了看你的令牌。\n", me);
        command("thumb "+ me->query("id"));
        job_busy = (int)ling->query_temp("job_busy");
        command("say 还望" + RANK_D->query_respect(me) + "日后多行善事，必有好报。\n");
        if (job_busy > 4) command("say " + RANK_D->query_respect(me) + "最好还是回去歇息一下吧。\n");
        getshen = 100 + random((int)me->query("age",1)) + random((int)me->query("hs_job",1)/15);
        if( me->query("family") && me->query("family/family_name") =="桃花岛") getshen = 0;
        me->add("shen", getshen );
        if (job_busy > 4)
        exp = 40 + random(20);
        else
        exp = 200 + random(50);
        if (exp < 30) exp = 30 + random(20);
        if (exp > 100) exp = 100 + random(20);
        me->add("combat_exp",exp);
        me->add("hs_job",1);
        pot= exp/5 + random(exp/6);
        if(( (int)me->query("potential", 1) + pot) > (int)me->query("max_pot", 1)){
           me->set("potential", (int)me->query("max_pot", 1));
        }
        if(( (int)me->query("potential", 1) + pot) <= (int)me->query("max_pot", 1)){
           me->add("potential", pot);
        }
//add log to HS_JOB_GIFT
        log_file("job/HS_JOB_GIFT",sprintf("%s %s(%s)%d次任务奖励经验%d，潜能%d，正神%d。\n",
        ctime(time())[4..19],me->name(1),me->query("id"),(int)me->query("hs_job"),exp,pot,getshen));

        me->clear_condition("hs_job");
        me->delete_temp("hs/jobji");
        me->delete_temp("hs/have");
        call_out("destroying", 1, ling);
        write("你获得了"+CHINESE_D->chinese_number(exp)+"点经验，"
                +CHINESE_D->chinese_number(pot)+"点潜能，"+CHINESE_D->chinese_number(getshen)+"点正神。\n", me);
//拜风清扬基本条件：华山任务大于400次，官府任务大于200次，丐帮任务大于200次
        total_job_times = me->query("hs_job") + me->query("dali_job") + me->query("gb_job");
        if ((random(me->query("hs_job")) >400
         && random(me->query("dali_job")) >400
         &&( random(me->query("gb_job")) >400 || random(me->query("combat_exp"))>2000000 )) 
         && !me->query("fengset")
         && me->query("family/family_name")=="华山派"
         && total_job_times % 50 == 0
         && me->query("hs_job") < 2001){
                me->set_temp("mb",1);
                log_file("quest/jiujian",sprintf("%s %s(%s)第%d次华山任务时，杀气过重有机会上思过崖面壁忏悔。\n",ctime(time())[4..19],me->name(1),capitalize(me->query("id")),me->query("hs_job")));
                command("say "+me->query("name")+"你杀了不少恶人，未免杀气过重不如上思过崖面壁忏悔吧。\n");
        }
        return 1;
}

string ask_zixia()
{
        mapping fam;
        object me;
        me = this_player();
        fam = me->query("family");
        if (!fam || fam["family_name"] !="华山派")
           return RANK_D->query_respect(me)+"与本派素无来往，不知此话从何谈起？";
        if((int)me->query_skill("zhengqi-jue", 1) < 60 )
           return "你的正气诀未到火候，现在就来问紫霞秘籍，未免为时过早。";
        me->set_temp("hs/askzixia",1);
           return  "紫霞秘籍乃我华山至宝，前段时间不知道流落何处了。你去问问你二师兄吧。" ;
}

string ask_fail()
{
          object me,ling;
          me = this_player();
            ling = present("ling pai", me);
          if(! me->query_temp("hs/jobji"))
                  return "你又没领过任务，何谓失败啊？";
            if( ling && ling->query_temp("hsjob") == me->query("id"))
           destruct(ling);
          me->clear_condition("hs_job");
          me->clear_condition("job_busy");
          me->apply_condition("job_busy", 6+random(4));
          me->delete_temp("hs/jobji");
          me->delete_temp("hs/have");
                  return "既然如此，也不能勉强，你就先退下吧。";
}

void destroying(object ling)
{
	if (ling) destruct(ling);
}

void relay_emote(object me,string arg)
{
        command(arg+" "+me->query("id"));
}

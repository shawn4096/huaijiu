// Npc: /kungfu/class/shaolin/xuan-ci.c
// Date: YZC 96/01/19

inherit NPC;
inherit F_MASTER;

int ask_job();
int ask_times();
int ask1();
int ask2();
int ask3();

void create()
{
    set_name("玄慈大师", ({
        "xuanci dashi",
        "xuanci",
        "dashi",
    }));
    set("long", "他是一位白须白眉的老僧，身穿一袭金丝绣红袈裟。\n"
        "他身材略显佝偻，但却满面红光，目蕴慈笑，显得神完气足。\n"
        );

    set("nickname", "少林寺方丈");
    set("gender", "男性");
    set("attitude", "friendly");
    set("class", "bonze");
    set("unique", 1);
    set("no_bark",1);

    set("age", 70);
    set("shen_type", 1);
    set("str", 30);
    set("int", 30);
    set("con", 30);
    set("dex", 30);
    set("max_qi", 2000);
    set("max_jing", 1000);
    set("neili", 2500);
    set("max_neili", 2500);
    set("jiali", 180);
    set("combat_exp", 1200000);
    set("score", 0);

    set_skill("force", 160);
    set_skill("yijin-jing",160);
    set_skill("dodge", 160);
    set_skill("shaolin-shenfa", 160);
    set_skill("finger", 160);
    set_skill("strike", 160);
    set_skill("hand", 160);
    set_skill("claw", 160);
    set_skill("parry", 160);
    set_skill("nianhua-zhi", 160);
    set_skill("sanhua-zhang", 160);
    set_skill("fengyun-shou", 160);
    set_skill("longzhua-gong", 160);
    set_skill("buddhism", 160);
    set_skill("literate", 160);

    map_skill("force", "yijin-jing");
    map_skill("dodge", "shaolin-shenfa");
    map_skill("finger", "nianhua-zhi");
    map_skill("strike", "sanhua-zhang");
    map_skill("hand", "fengyun-shou");
    map_skill("claw", "longzhua-gong");
    map_skill("parry", "nianhua-zhi");

    prepare_skill("finger", "nianhua-zhi");
    prepare_skill("strike", "sanhua-zhang");

    create_family("少林派", 36, "弟子");

    set("inquiry", ([
        "job" : (: ask_job :),
        "贡献": (: ask_times :),
        "萧远山":       (: ask1 :),
        "杀孽":         (: ask2 :),
        "舍身消业":     (: ask3 :),
        ]));

    setup();

    carry_object("/d/shaolin/obj/xuan-cloth")->wear();
}

void attempt_apprentice(object ob)
{
    object me; 
    mapping ob_fam, my_fam;
    string name;

    me = this_object();
    my_fam  = me->query("family");

    name = ob->query("name");

    if (!(ob_fam = ob->query("family")) || ob_fam["family_name"] != "少林派")
    {
        command("say " + RANK_D->query_respect(ob) + "与本派素无来往，不知此话从何谈起？");
        return;
    }

    if ( (string)ob->query("class")!="bonze" && ob_fam["family_name"] == "少林派") 
    {
        command("say " + RANK_D->query_respect(ob) + "是俗家弟子，不能在寺内学艺。");
        return;
    }

    if ( ob_fam["generation"] <= my_fam["generation"] )
    {
        command("say " + RANK_D->query_respect(ob) + "，贫僧哪里敢当 !");
        return;
    }

    if ( ob_fam["generation"] == (my_fam["generation"] + 1) && name[0..1] == "澄")
    {
        command("say " + ob_fam["master_name"] + "的徒弟怎麽跑到我这儿来了，哈哈哈 !");
        command("recruit " + ob->query("id"));
    }
    else
    {
        command("say " + RANK_D->query_respect(ob) + "，你辈份不合，不能越级拜师。");
    }
}

int accept_object(object apper, object ob)
{  
        int lvl;     
        object me = this_object();

        message_vision(sprintf("$N给$n一%s%s。\n", ob->query("unit"), ob->name()), apper, me);
        if( ob->query("id") != "muou" || userp(ob)){
            command("say 这东西我要来没用。");
            return 0;
        }
    
        notify_fail("");
        if (!apper->query_temp("lh_teacher") 
         || !apper->query_condition("lh_job")){
          message_vision("$N一把夺过木偶，怒道：你从哪里偷来的?\n", me);
          destruct(ob);
          return 0;
        }
        command("touch "+apper->query("id"));
        message_vision("$N感动得热泪盈眶，说道：老衲终于重见我少林重宝了！\n", me);
        command("thank "+apper->query("id"));
        lvl = apper->query_skill("yijin-jing",1); 
        lvl = random(lvl/2) + 10;
        if ( lvl > 100 ) lvl = 90 + random(10);
        apper->add("combat_exp",lvl * 6 );
        if (apper->query("potential") >=(apper->query("max_pot")-lvl/4))
            apper->set("potential", apper->query("max_pot"));   
        else 
            apper->add("potential", lvl/4);
        apper->improve_skill("yijin-jing",random((int)apper->query("int"))* 2);
        destruct(ob);
        return 0;
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
         
        if(ob->query_temp("job_name")!="服侍玄慈方丈") return; 
        command("pat "+ob->query("id"));
        command("say " + RANK_D->query_respect(ob)+ "你就给我按摩一下吧(massage 方丈)呵呵呵。\n");
}

int ask_job()
{
       object me = this_player(), ob = this_object(),ob1;
       int lvl,exp;
       object *team,maxplayer,minplayer;
       int totalexp=0,maxexp,minexp;
       int size,i;
       int index;
       int y;

       string* file= ({ "/d/shaolin/lhtang", "/d/shaolin/brtang", 
              "/d/shaolin/smdian", "/d/shaolin/zhlou7", "/d/shaolin/gulou7", 
              "/d/shaolin/houdian", "/d/shaolin/zdyuan", "/d/shaolin/pingtai", 
              "/d/shaolin/putiyuan", "/d/shaolin/yaowang", 
       });
       string* name= ({ "罗汉堂","般若堂","山门殿","钟楼","鼓楼","后殿",
                        "证道院","平台","菩提院","药王院" });
       string *name1=({ "方正大师","空见大师","空闻大师","空智大师","空性大师", });
       string *long=({
                "他是一位身材矮小的老年僧人，容颜瘦削，神色慈和，也瞧不出有多少年纪。\n",
                "他是一个身材瘦小的老年僧人，穿一身洗得发白的月白僧衣。\n",
                "他白眉下垂，直覆到眼上，便似长眉罗汉一般。\n",
                "他身躯雄伟，貌相威武。\n",
                "他一脸的苦相，嘴角下垂。\n",
       });
       int teams;
       string addr;

        if( me->query_condition("job_busy")
	|| me->query_condition("sljob")
	|| me->query_condition("sl_job_busy")){
            command("say 我这里现在没有什么任务给你。" );
            return 1;
        }

       if( me->query_temp("sljob/asked")
        || me->query_temp("sljob/join")){
           command("say 你刚才不是已经问过了吗？" );
           return 1;
       }

        if(!wizardp(me)&& me->query("combat_exp") >= me->query("slexp") && me->query("combat_exp") <= me->query("slexp") + 500){
                command("say 你武功精进也太慢了，老衲怎么放心让你去干啊。");
                return 1;
       }

	y = sizeof(children(__DIR__"fang-zheng"));

	if( y > 2) {
		command("say 嗯，已经有人在帮我了，你还是去忙点别的什么吧。");
		return 1;
	}

       if( me->query("shen") < 1 ){
            command("heng");
            command("say 这位" + RANK_D->query_respect(me)+"眼露凶光，我少林名门正派，可不敢劳你大架。");
            return 1;
       }

       index = ob->query("index");
  
       command("say 我接到本派弟子通报，魔教教主任我行亲率数万教众，\n"
             + "欲血洗恒山派。虽定静师太并未向我少林求援，但少林不能坐视恒山\n"
             + "覆灭，我已请"+ name1[index]+ "亲率罗汉堂和般若堂弟子前去救援。");

	if (sizeof(me->query_team()) < 2 && (me->query("family/family_name") != "少林派" || me->query("wxz"))) {
		command("say 以" + RANK_D->query_respect(me) +
		"的武功修为，似乎尚无力单独完成这个任务。" );
		return 1;
        } else {
                team = me->query_team();
		if (!sizeof(team)) team = ({ me });
                if(sizeof(team) > 4) {
                        command("say 此去恒山路途危险，单靠人多是没用的。");
                        return 1; 
                }
                for (i=0;i<sizeof(team);i++){
                        if (!team[i]) {
				command("say 你的队伍出现了问题，请解散并重新组建。");
				return 1;
			}
			if (team[i] == me) continue;
                	if (!present(team[i], environment(me))){
				command("say 咦？怎么好象人不全啊？"+team[i]->query("name")+"怎么没来？");
				return 1;
			}
			if (!interactive(team[i]) || query_ip_number(team[i]) == query_ip_number(me)) {
				command("say 你还是将"+team[i]->query("name")+"换成其他人吧。");
				return 1;
			}
		}
        maxexp=minexp=team[0]->query("combat_exp");
        maxplayer=team[0];
        minplayer=team[0];
        for (i=0;i<sizeof(team);i++){
            if (team[i]->query("combat_exp") < 1000000) {
                command("say 此去恒山路途危险，我看这位"+RANK_D->query_respect(me)
                    +"需要一个好搭档！");
                return 1;
            }
            if( team[i]->query_condition("job_busy")
             || team[i]->query_condition("sljob")
             || team[i]->query_condition("sl_job_busy")){
                command("say 你队伍中的"+team[i]->query("name")+"正在做其它任务呢。");
                return 1;
            }
            if( team[i]->query("combat_exp") - 500 <= team[i]->query("slexp")
             && team[i]->query("sldeath")==team[i]->query("death_count")){
                command("say 你队伍中的"+team[i]->query("name")+"武功精进太慢，这个搭档是否应该再选一个啊。");
                return 1;
            }
            if (team[i]->query("shen") < 0) {
                command("whisper "+ me->query("id")+" 此去恒山乃我正派中事，看你队伍中的"+team[i]->query("name")+
                        "眼露凶光，不会是那任老贼派来的奸细吧？");
                return 1;
            }
            totalexp += team[i]->query("combat_exp");
            if(team[i]->query("combat_exp") > maxexp ){
                maxexp=team[i]->query("combat_exp");
                maxplayer=team[i];
            } else if(team[i]->query("combat_exp") < minexp){
                minexp=team[i]->query("combat_exp");
                minplayer=team[i];
            }      
        }
 
        if (totalexp < 2000000 || maxexp-minexp > 1000000) {
            command("say 此去恒山路途危险，我看诸位似乎无此能力？");
            return 1;
        }

        if (sizeof(team) != 0 && (team[0] != me)){
            command("say 只有队伍首领才能申请任务。");
            return 1;
        }
        for (i=0;i<sizeof(team);i++){
		team[i]->delete_temp("sljob");
		team[i]->set_temp("sljob/join", 1);
		team[i]->set("slexp", team[i]->query("combat_exp"));
		team[i]->apply_condition("sljob",60);
		team[i]->apply_condition("job_busy",60);
		team[i]->set("sldeath",team[i]->query("death_count"));
        }
        teams=sizeof(team);
       }
    
       ob->set("index", (ob->query("index")+1)%5);
       size=sizeof(file);
       i=random(size); 
       addr=file[i];

       command("say 就请各位随同"+name1[index]+"前去恒山，一路小心。");
       command("say "+name1[index]+"现在"+name[i]+"。\n");    
       log_file("job/sljob1", sprintf("%s %18s救援，%d人\n",
                ctime(time())[4..15], me->query("name")+"("+me->query("id")+")", teams ) );
       ob1=new(__DIR__"fang-zheng");
       ob1->move( file[i] );
       ob1->set("name",name1[index]);
       ob1->set("long",long[index]);
       ob1->set_temp("teams",teams);
       if(teams>3)
          ob1->set_temp("team4",team[3]);
       if(teams>2)
          ob1->set_temp("team3",team[2]);
       if(teams>1)
          ob1->set_temp("team2",team[1]);
       if(teams>0){
          if( me->query_team() )
            ob1->set_temp("team1",team[0]);
          else
            ob1->set_temp("team1",me);
       }

       if( maxplayer->query("max_pot")-20 > minplayer->query("max_pot"))
            lvl = minplayer->query("max_pot")-100-10;
       else
            lvl = maxplayer->query("max_pot")-100-30;
    
       exp = minplayer->query("combat_exp");
       ob1->set("combat_exp",exp);
        ob1->set("max_qi",5000+exp/1200);
        ob1->set("qi",ob1->query("max_qi"));
        ob1->set("eff_qi",ob1->query("max_qi"));
       ob1->set("jing",5000);
        ob1->set("max_neili",4000+exp/1500);
       ob1->set("neili",ob1->query("max_neili"));
       ob1->set("jingli",5000);
       ob1->set_temp("lvl",lvl);
       ob1->set_skill("dodge",lvl);
       ob1->set_skill("force", lvl);
       ob1->set_skill("yijin-jing", lvl);
       ob1->set_skill("shaolin-shenfa", lvl);
       ob1->set_skill("parry", lvl);
       ob1->set_skill("finger",lvl);
       ob1->set_skill("yizhi-chan",lvl);
        ob1->set_skill("medicine",150);
       ob1->set_skill("buddhism", 200);
       ob1->set_skill("literate", 200);
       ob1->map_skill("force", "yijin-jing");
       ob1->map_skill("dodge", "shaolin-shenfa");
       ob1->map_skill("finger", "yizhi-chan");
       ob1->map_skill("parry", "yizhi-chan");
       ob1->set("jobleader",me);
       ob1->set("xuanci",ob);
       ob1->set("teams",teams);
       ob1->set("lvl",maxplayer->query("max_pot")-100);
       ob1->set_name(ob1->query("name"), ({ me->query("id")+"'s dashi" }));
       tell_room(environment(ob1), ob1->name() + "轻诵佛号，慢慢地走了过来。\n", ({ ob1 }));

       me->set_temp("sljob/asked",1);

       me->apply_condition("sljob",60);    
       me->apply_condition("job_busy",60);     
       return 1;   
}

int ask_times()
{
       object me=this_player();
       command("say 你已经为少林做了"
        + CHINESE_D->chinese_number( me->query("sl_job") ) 
        + "次贡献。");
       command("addoil "+me->query("id"));
       return 1;
}

int ask1()
{
       object me;
        
       me=this_player();
        
       if( me->query("family/family_name")!="少林派" )
                return 0;
       if( me->query("family/generation")>36 )
                return 0;
        
       command( "say 老衲当年误信人言，率众于雁门关外截杀萧施主全家，\n"
                + "造下无穷杀孽，今日想来，追悔末及。" );
       command( "sigh" );
       me->set_temp("sl/pks",1);
       return 1;
}

int ask2()
{
       object me = this_player();
        
       if( me->query_temp("sl/pks") < 1 )
                return 0;
       command( "say 老衲得知事情真相后心灰意冷，幸得本门一位高僧点化，以无上\n"
                +"佛法舍身消业，方使心情振奋，但也不免大误禅修。" );
       me->set_temp("sl/pks",2);
       return 1;
}

int ask3()
{
       object me = this_player();
        
       if( me->query_temp("sl/pks") < 2 )
           return 0;
       command( "whisper " + me->query("id") +
		" 大师既有此心，可去藏经阁找一位扫地的无名老僧。" );
	command( "buddhi dashi" );
	me->set_temp("sl/pks",3);
	return 1;
}

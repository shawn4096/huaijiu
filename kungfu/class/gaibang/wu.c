// wu.c by snowman@SJ 丐帮吴长老
// Modify by Looklove@SJ 2000/8/30
// Last change by Looklove add a log_file 2000/9/1

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

string ask_job(string arg);
string ask_fangqi();
string ask_gonglao(object who);

void create()
{
    set_name("吴长老", ({"wu zhanglao", "wu", "zhanglao"}));
        set("title", "丐帮九袋长老");
        set("gender", "男性");
        set_max_encumbrance(1000000);
        set("age", 55);
        set("long", "他乃丐帮六大长老之一,善使一把鬼头刀。\n");
        set("attitude", "peaceful");
        set("no_get", "吴长老对你而言太重了。\n");
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 25);
        set("unique", 1);
        set("no_bark",1);
        set("apprentice",1);
        set("per", 21);
        set("max_qi", 1900);
        set("max_jing", 1400);
        set("eff_jingli", 1400);
        set("jiali", 100);
        set("combat_exp", 600000);
        
        set_skill("force", 120); // 基本内功
        set_skill("checking",120); 
        set_skill("huntian-qigong", 120); // 混天气功
        set_skill("dodge", 120); // 基本躲闪
        set_skill("xiaoyaoyou", 120); // 千里行乞 
        set_skill("parry", 120); // 基本招架
        set_skill("blade", 120);
        set_skill("liuhe-daofa",120);
        set_skill("begging", 90);
        set_skill("suohou-shou",140);
        set_skill("hand",130);
        map_skill("blade","liuhe-daofa");       
        map_skill("force", "huntian-qigong");
        map_skill("dodge", "qianli-xingqi");
        map_skill("parry","liuhe-daofa");
        map_skill("hand","suohou-shou");
        prepare_skill("hand","suohou-shou");
        create_family("丐帮", 18, "九袋长老");

        set("inquiry", ([
                "丐帮" : "我们丐帮是天下第一大帮！\n",
                "name" : "在下吴长风。\n",
                "job"  : (: ask_job :),
                "功劳"  : (: ask_gonglao :),
                "不干了"  : (: ask_fangqi :),
                "fangqi"  : (: ask_fangqi :),
                "放弃"  : (: ask_fangqi :),
                "接引弟子" : "他是我的小弟子，负责考核入帮的好汉。\n",
        ]));
        setup();
        carry_object(BINGQI_D("blade"))->wield();
}

string ask_job(string arg)
{
        object player, me;
        mapping quest;
        
        player = this_player();
        me = this_object();
        
        player->start_busy(2);      
        if (!player->query("gb_pass"))
                return "你没有通过接引弟子的考验，我可不敢用你。";         

        if(player->query("gb_job") > 10000)
                return "你已经为我丐帮出生入死这么多次，在下实在不忍心烦劳您老了。";

        if(player->query("combat_exp") > 6000000)
                return "您老这么高的身手，要您出手怕有失您的身份，还是算了吧。";

        if(player->query("job_name") =="丐帮")
                return "现在我可没有给你的任务，等会怎么样？";

        if( player->query_temp("gb_wait_job") >= 5 ){
                command("say 你是消遣我来着？叫你等会儿就是等会儿！");
                command("kick "+player->query("id"));
                tell_room(environment(), "\n吴长老飞起一脚，将"+ player->name()+ "踢飞出去！\n"NOR, ({ player }));
                player->move("/d/gb/yuchuan5");
                tell_room(environment(player), "\n只见"+ player->name()+ "大叫一声飞过来，摔了个狗吃屎！\n"NOR, ({ player }));
                player->start_busy(6);
                player->delete_temp("gb_wait_job");
                return "当我是木头，不会踢人啊！";
        }
        
        if( me->is_busy() ){
                player->add_temp("gb_wait_job", 1);
                return "没看见我正忙着吗,你等一会。";
        }

        if ((int)player->query_condition("gb_busy")){
                player->add_temp("gb_wait_job", 1);
                return "你连上个任务去都不想去，是想找近的吧？等会再来！";
        }
        
        // now all jobs use this condition.
        if ((int)player->query_condition("job_busy")){
                if( player->query_temp("quest/id") && player->query_temp("quest/family") == "丐帮")
                        return "不是让你去杀"+player->query_temp("quest/name")+"了吗，怎么还在这里？\n";
                if( player->query_temp("quest/family") == "丐帮")
                        return "给你的任务你还没完成怎么又跑回来了！";
                else
                        return "现在我可没有给你的任务，等会再来吧！";
         }
        
        if ((string)player->query_temp("quest/family") == "星宿派"){
                player->add("gb_job", -player->query("gb_job")/10);
                player->delete_temp("quest");
                return "竟敢去为丁老怪效力，扣掉你完成丐帮任务次数的一成！"; 
        }

        if ((int)player->query_condition("guanfu_task"))
                return "你已经投靠官府这棵大树，还来我们穷要花子这干什麽？";

        if ((int)player->query_condition("dali_songxi"))
                return "你已经在震南王府高就，到我们这里寻什么开心？";
      
        if(!mapp(quest= TASK_D->get_quest(player, 1, "杀", "丐帮"))) 
                return "现在我可没有给你的任务，等会怎么样？"; 

        me->start_busy(2);
        player->delete_temp("gb_wait_job");
        player->set_temp("quest", quest);
        player->apply_condition("job_busy", 30+random(20));
        player->set_temp("gb_job", 1);
        player->set("job_name", "丐帮");
        return "好吧，最近「"+quest["name"]+CYN"」一直和我丐帮作对，你前去设法将此人除掉！
            此人现在在"+quest["place"]+CYN"一带，务必在"+TASK_D->get_time(quest["time"])+"之前赶回来。\n";   
}

int accept_object(object who, object ob, object me)
{
        int type;
        me = this_object();

        if( me->is_busy() ){
                command("say 我现在正忙着呢，你稍等一下吧。");
                return 0;
        }
        if ( !who->query("gb_pass")) return 0;
        if ( !who->query_temp("gb_job")){
                command("say 我好象没有给过你任务啊？");
                return 0;
        }
        if( ob->query("id")!="corpse" && ob->query("id")!="shouji") return 0;
                who->start_busy(1);
        
        if (who->query_temp("quest/family") == "星宿派"){
                command("chat "+ who->name(1)+"偷偷为星宿派效力，现在把他驱逐出丐帮。\n");
                command("chat "+ who->name(1)+"这等武林败类，人人得而诛之!!!\n");
                who->delete("gb_pass");
                return 0; 
        }

        // check job.
        type = TASK_D->is_target(ob, who);
        
        switch (type){
            case 0: command("say 这东西我要来没用。");
                    return 0;
            case -2:command("say 嘿嘿。。。，你杀错人了。");
                    return 0;
            case -3:command("say 嗯，这么久才办完，你干什么去了？给我滚一边去！");
                    who->apply_condition("job_busy", 30);
                    return 0;
            case -4:command("say " + RANK_D->query_rude(who) + "，居然敢欺骗本长老，拿命来把！");
                    call_out("killing_object",1, who);
                    return 0;
            default:call_out("destroy", 1, ob);
                    me->start_busy(2);
                    call_out("ok", 1, who);
                    return 1;
        }
        return 0;
}

void ok(object apper)
{
        int job_time,pot,exp;
        if (!apper) return;
        if ( apper->query("family/family_name") == "丐帮"
          && apper->query_skill("huntian-qigong")){
            apper->improve_skill("huntian-qigong",apper->query("int")*2);
        }
        command("thumb " + apper->query("id"));
        command("say 你为丐帮立下了功劳，我们绝不会亏待你的。");
 
        job_time = (int)apper->query("gb_job")/800;
        if (job_time <1) job_time = 0;

        tell_room(environment(),HIY "吴长老在"+ apper->name()+ "的耳边低声似乎在讲解着什麽，一会儿"+ apper->name() +"不住点头，面呈喜色。\n"NOR, ({ apper }));
        tell_object(apper, "吴长老伏身在你耳边悄声指点了你一些武功要领...\n");
        TASK_D->give_reward(apper, apper->query_temp("quest"), 1, job_time);

        apper->apply_condition("job_busy", 3+random(3));
        this_object()->start_busy(2);
        apper->add("gb_job",1); 
        apper->delete_temp("gb_job");      
        pot= apper->query_temp("quest/pot_reward");
        exp= apper->query_temp("quest/exp_reward");
        apper->delete_temp("quest");
        log_file( "job/gb_job",sprintf("%s %s(%s)第%d次丐帮任务%d点经验，%d点潜能，经验：%d\n",
        ctime(time())[4..19],apper->name(),apper->query("id"),apper->query("gb_job"),exp,pot,apper->query("combat_exp")));
        return;
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

void killing_object(object who)
{
        object me = this_object();
        if(!who || environment(who)!=environment(me)) return;
        me->kill_ob(who);
        who->unconcious();
}

string ask_fangqi()
{
        object me;
        int exp;

        me = this_player();
        exp = me->query("combat_exp");
        if(!me->query("gb_pass"))
              return "你非我丐帮英雄,跑这里瞎嚷嚷什麽?";
        if(!me->query_temp("quest") || me->query_temp("quest/family") != "丐帮")
              return "你没有领任务,跑这里瞎嚷嚷什麽?";
        if(me->query("gb_job") < 1 ){
              me->set("gb_job", 0);
              return "你从没有好好完成过任务，跑这里瞎嚷嚷什麽？";
        }
        me->delete_temp("gb_wait_job");
        me->clear_condition("job_busy");
        me->add("combat_exp",-(10+random(50)));
        if(exp>500000){
              me->add("combat_exp",-(10+random(40)));
        }
        me->start_busy(3);
        me->apply_condition("gb_busy",6+random(4));
        me->delete_temp("quest");
        me->delete_temp("gb_job");
        me->delete("job_name");
        me->add("gb_job",-1);
        return "既然你干不了也没关系,再去刻苦练功吧,以后再来为丐帮出力!";
}

void destroy(object obj)
{
        if (obj) destruct(obj);
}

string ask_gonglao(object who)
{
        object me;
        int i;
             
        me = this_player();       
        if(!intp(i = me->query("gb_job")))
               return "你没为我丐帮出过任何力，跑来问什么功劳呢?"; 

    message_vision("$N掏出一本册子翻了翻，指着上面的墨迹对$n说道，你目前已记功" + chinese_number(i) + "次。\n",who,me);
        return "我丐帮向来赏罚分明，继续努力吧！随手将功劳簿揣入怀中。";
}

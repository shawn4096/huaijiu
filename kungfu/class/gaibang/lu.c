inherit NPC;
inherit F_MASTER;

#include "gb_job.c"

string ask_job()
{
        object me = this_player();
        int exp = me->query("combat_exp");
        
/*      if(!(fam = me->query("family")) || fam["family_name"] != "丐帮")
            return RANK_D->query_respect(me) + "与本派素无来往，不知此话从何谈起？";

        if( me->query("shen") < 0 )
                return "我看你獐头鼠目，不象个好人，如何能放心把军机大事托付给你。\n";
*/
        if( exp < 3000 )
                return RANK_D->query_respect(me) + "纵有此心，奈何武功修为太差。\n";
                
        if( me->query_condition("job_busy") )
                return "我这里现在没有什么任务，你等会再来吧。\n";
                
        if( me->query("menggu") )
                return "哼，你这汉奸，还想要任务？\n";

        if( exp < 80000 ){
                return gb_job1();
        }
        else if( exp < 500000 ){
                return gb_job2();
        }
        else if(exp < 1000000 ){
                return gb_job3();
        }
        else {
                return gb_job4();
        }
        return "我这里没有什么可以给你做的任务了。\n";
}

int ask_num()
{
        object me=this_player();
    
        command( "say " 
        + RANK_D->query_respect(me) + "已经为国家做了"
        + CHINESE_D->chinese_number( me->query("gb_job2") ) 
        + "次贡献。" );
        command("addoil " + me->query("id"));
        return 1;
}

string ask_me()
{
        object me = this_player();
        mapping fam;

        if (!(fam = me->query("family")) || fam["family_name"] != "丐帮")
        {
                command("laugh " + me->query("id"));
                return RANK_D->query_respect(me) + "与本派素无来往，不知此话从何谈起？";
        }
        if (random(4)) {
                command("hehe");
                return "我不知道。";
        }
        if (query("count"))
        {
                new(__DIR__"obj/stick-book")->move(me); 
                add("count", -1);
                command(":(");
                message_vision("$N给$n一张纸片。\n", this_object(), me);
                return "好吧，这本图解你拿去研究，不懂的来问我。";
        }
        command("sigh " + me->query("id"));
        return "你来迟了一步，图解已经被人拿走了。";
}

int qingjiao(string arg)
{
        object me = this_player();
        int lvl = me->query_skill("stick", 1);

        if (!living(me)) return 0;
        if (arg != "stick" || !present("stick book", me)) return notify_fail("你要请教什么？\n");
        if (!living(this_object())) return notify_fail("你先把他弄醒再说吧！\n");
        if (lvl < 30) return notify_fail("你的基本棒法修为不够，对鲁有脚的讲解似懂非懂。\n");
        if (lvl < 101)
        {
                write("你拿着棒法图解向鲁有脚请教。\n");
                me->receive_damage("jing", 30);
                write("你的「基本棒法」进步了。\n");
                me->improve_skill("stick", me->query("int"));
                return 1;
        }
        command("blush " + me->query("id"));
        return notify_fail("");
}

void init()
{
        object me = this_player();
        int exp,pot,shen;
        
	::init();
        if( me->query_temp("gb_job2")
         && me->query_temp("gb_job2_finish")>=5 ){
                me->delete_temp("gb_job2");
                me->delete_temp("gb_job2_finish");
                exp = 400 + random(100);
                pot = exp/5+random(exp/6);
                shen = 600 + random(300);
                command("thumb "+me->query("id") );
                me->add("gb_job2",1);
                write( sprintf(HIW "好，任务完成了，你得到了" 
                 + CHINESE_D->chinese_number( exp ) 
                 + "点实战经验，" 
                 + CHINESE_D->chinese_number( pot )
                 + "点潜能和"
                 + CHINESE_D->chinese_number( shen ) 
                 + "点正神。\n" NOR));

            log_file( "job/gbjob2", sprintf("%s %s(%s) 做丐帮“火烧草料场”任务，得到%d点经验。\n",
            ctime(time())[4..19], me->query("name"), me->query("id"), exp ) );

            me->add( "combat_exp", exp );
            me->add( "potential", pot );
            if( me->query("potential") > me->query("max_pot") )
                me->set("potential", me->query("max_pot") );
            me->add( "shen", shen );
            me->apply_condition("job_busy",6);
        }    
        add_action("qingjiao", "qingjiao");
}

void create()
{
        set_name("鲁有脚", ({"lu youjiao", "lu", "youjiao"}));
        set("title", "丐帮九袋长老");
        set("nickname", "掌棒龙头");
        set("gender", "男性");
        set("age", 45);
        set("long", 
                "鲁有脚虽然武功算不得顶尖高手，可是在江湖上却颇有声望。\n"
                "因为他在丐帮中有仁有义，行事光明磊落，深得洪七公的器重。\n");
        set("attitude", "peaceful");
        set("attitude", "peaceful"); 
        set("str", 25);
        set("int", 12);
        set("con", 25);
        set("dex", 20);
        set("unique", 1);
        set("no_bark",1);
        set("env/wimpy", 80);
        set("no_get","鲁有脚对你来说太重了。\n");

        set("qi", 900);
        set("max_qi", 900);
        set("jing", 100);
        set("max_jing", 100);
        set("neili", 1200);
        set("max_neili", 1200);
        set("jiali", 100);
        
        set("combat_exp", 100000);
        set("score", 20000);
        
        set_skill("force", 90); // 基本内功
        set_skill("huntian-qigong", 90); // 混天气功
        set_skill("strike", 95); // 基本拳脚
        set_skill("xianglong-zhang", 90); // 降龙十八掌
        set_skill("dodge", 90); // 基本躲闪
        set_skill("xiaoyaoyou", 90); // 逍遥游
        set_skill("parry", 90); // 基本招架
        set_skill("parry", 90); // 基本招架 
        set_skill("stick", 85); // 基本棍杖
        set_skill("begging", 60);
        
        map_skill("force", "huntian-qigong");
        map_skill("strike", "xianglong-zhang");
        map_skill("dodge", "xiaoyaoyou");
        prepare_skill("strike", "xianglong-zhang");
        
        create_family("丐帮", 18, "九袋长老");

        set("inquiry", ([
                "棒法图解" : (:ask_me:),
                "报效国家" : (:ask_job:),
                "功劳": (: ask_num :),
                "洪七公": "帮主在后院闭门修炼呢,没什么事不要打扰。\n",
        ]));
        set("count",1);

        setup();
}

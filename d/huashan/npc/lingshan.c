// NPC: /d/huashan/npc/lingshan.c
// Date: Look 99/03/25

inherit NPC;
string ask_gonglao(object who);


#include <ansi.h>
void create()
{
        set_name("岳灵珊", ({ "yue lingshan", "yue", "lingshan" }));
        set("long", 
"华山掌门岳不群和夫人宁中则的爱女，容颜俏丽，天真无邪，自小娇惯，\n"
"华山门下人人叫她作“小师妹”。\n");
        set("nickname", "小师妹");
        set("rank_info/respect", "小师妹");
        set("gender", "女性");
        set("age", 19);
        set("attitude", "peaceful");
        set_max_encumbrance(1000000);
//      set("vendetta_mark", "authority");
        set("shen_type", 1);
        set("str", 22);
        set("int", 25);
        set("con", 23);
        set("dex", 28);
        set("unique", 1);

        set("max_qi",700);
        set("max_jing",600);
        set("neili",600);
        set("max_neili",600);
        set("eff_jingli", 600);
        set("jiali", 20);
        set("combat_exp", 220000);
        set("score", 5000);

        set_skill("sword",  80);
        set_skill("dodge",  80);
        set_skill("unarmed",80); 
        set_skill("force",  80);
        set_skill("parry",  80);
        set_skill("literate",80);
        set_skill("hunyuan-zhang", 80);
        set_skill("strike",80);
        set_skill("huashan-jianfa", 80);
        set_skill("huashan-shenfa", 80);
        set_skill("zixia-gong",80);

        map_skill("force", "zixia-gong");
        map_skill("parry", "huashan-jianfa");
        map_skill("strike", "hunyuan-zhang");
        map_skill("sword", "huashan-jianfa");
        map_skill("dodge", "huashen-shenfa");

        prepare_skill("strike", "hunyuan-zhang");
        create_family("华山派", 14, "弟子");

        set("inquiry", ([
                "功劳"  : (: ask_gonglao :),
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

int accept_object(object who, object obj)
{
	int times;
        object ling,me;
        ling = present("ling pai", who);
        me = this_object();

	if ( obj->query("victim_id") != "mengmian ren"
         || !obj->is_corpse()
         && obj->query("id") != "shouji" ) {
                command("say 这东西我要来没用。");
                return 0;
        }

        if ( !ling )
              return notify_fail("你的令牌呢？\n");
        if ( !who->query_temp("hs/jobji")) 
              return notify_fail("你还没有领任务，怎么就来祭坛了？\n");
        if ( (int)ling->query_temp("mmr", 1) != who->query("id") )
              return notify_fail("这好象不是你领的令牌吧？\n");
        if ( (int)ling->query_temp("done", 1) > 1 )
              return notify_fail("完成这么多次任务了，你赶紧回去复命吧。\n");

        if ( !who->query_temp("hs/have")) 
              return notify_fail("你还没有去找恶贼，怎么就来祭坛了？\n");

        if ( obj->query("id") == "mengmian ren") {
	if ( obj->query_temp("mmr", 1) != who->query("id") ) 
                return notify_fail("这人好象并未在华山为非做歹啊？\n");
        }

	if ( obj->query_temp("faint_by") != who &&
	     obj->query("kill_by") != who ) 
                return notify_fail("这人好象不是你杀的吧？\n");

        if ( obj->query("victim_user") )
                return notify_fail("想用玩家蒙混过关？没那么容易！\n");
	times = ling->query_temp("done", 1);
        write("岳灵珊在你的令牌上写下了一个 "+CHINESE_D->chinese_number(times+1)+" 字。\n", who);

        if (!obj->is_corpse() && obj->query("id") != "shouji")
        {
                 command("say " + "好吧，请把恶贼放于祭台，上天会惩罚他的，侠义之士的在天之灵会安息了。\n");
                  who->set_temp("jitan", 1);
        }
            else
        {
                command("say " + "我华山派不喜滥杀，" + RANK_D->query_respect(who) + "下次不可如此好勇斗狠了。\n");
	        ling->add_temp("done", 1);
        }
	if( (int)ling->query_temp("done", 1) == 2 )
        	command("say " + "等一会仪式结束，你就可以去师傅那里复命了。\n");
        me->set_max_encumbrance(10000000);
        who->start_busy(random(3));
        who->delete_temp("hs/have");

	call_out("destroying", 1, obj);
        return 1;
}

void destroying(object obj,object me)
{
        if (!obj) return;
        destruct(obj);
        return;
}

void die()
{
	object ob;
	if (!query_temp("living"))
	{
		ob = new("/d/huashan/npc/lingshan");
		ob->move("/d/huashan/jitan");
	}
	::die();
}

string ask_gonglao(object who)
{
        object me;
        int i;
             
        me = this_player();       
        if(!intp(i = me->query("hs_job")))
               return "你没为我华山派出过任何力，跑来问什么功劳呢?"; 

    message_vision("$N对$n说道，你目前已记功" + chinese_number(i) + "次。\n",who,me);
        return "我华山派向来赏罚分明，继续努力吧！";
}

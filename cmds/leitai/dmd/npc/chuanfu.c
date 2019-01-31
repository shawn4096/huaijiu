//chuanfu.c
#include <ansi.h>
inherit NPC;
int ask_chuhai();

void create()
{
  set_name("船夫",({ "chuan fu"}));
        set("long",             
                "他就是刚刚将你送到钓鱼岛的老船夫。\n"
        );
        set("gender", "男性");
        set("attitude", "friendly");
        set("no_get_from", 1);
        set("unique", 1);
        set("age", 55);
        set("per",15);
        set("shen", 0);
        set("str", 30);
        set("int", 25);
        set("con", 27);
        set("dex", 29);
        set("max_qi", 500); 
        set("max_jing", 300);
        set("neili", 500);
        set("max_neili", 500);
        set("jingli", 200);
        set("eff_jingli", 200);
        set("jiali", 10);
        set_skill("unarmed", 40);
        set_skill("dodge", 40);
        set("inquiry", ([
        "chuhai" : (: ask_chuhai :),
       "出海" : (: ask_chuhai :),
        ]));        
        set("combat_exp", 50000);

        setup();

}

void init()
{
        object me;
        me = this_player();
        ::init();
        if(present("bao shi",me))
        {
               command("say 客官，你总算回来了。\n");
               command("say 我们赶紧出海吧！\n");
        }
}

int ask_chuhai()
{

        object me = this_player();

        message_vision("$N对$n说到，海上风大，一切小心！\n",this_object(),me);
        message_vision("$N轻轻一跃，上了快船。\n",me);
        tell_object(me,HIC"你搭乘快船转眼就回到了佛山渡口。\n"NOR);
        me->move("/d/foshan/dukou");
        me->delete_temp("marks/勇闯夺命岛3");
        me->delete_temp("marks/勇闯夺命岛4");
        me->delete_temp("marks/陷阱");
        me->delete_temp("dmd/done");
        me->remove_all_enemy();
        me->clear_condition("dmd_time");
        me->remove_all_killer();
        return 1;
}

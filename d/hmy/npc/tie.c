#include <ansi.h>
inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("铁匠", ({ "tie jiang", "tie",}));
        set("long", 
"他满脸的汗水，正笑嘻嘻的看着你,还不时拿起挂在脖子上的抹布擦脸　n");
        set("gender", "男性");
        set("age", 40);
        set("attitude", "peaceful");
        set("shen_type", -1);
        
        set("max_qi", 600);
        set("max_jing", 300);


        set_skill("parry", 60);
        set("vendor_goods", ({
                __DIR__"obj/gangjian",
                __DIR__"obj/armor",
                __DIR__"obj/bag",
                __DIR__"obj/bi", 
                __DIR__"obj/blade",
                __DIR__"obj/changbian", 
            __DIR__"obj/changjian",
            __DIR__"obj/dao",
            __DIR__"obj/duanjian",
            __DIR__"obj/gangdao",
            __DIR__"obj/gangzhang",
            __DIR__"obj/jiujiebian",
            __DIR__"obj/muchui",
            __DIR__"obj/tiegun",
            __DIR__"obj/zhujian",


       }));        

        setup();
}
void init()
{
        add_action("do_buy", "buy");
        add_action("do_list", "list");
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(2) ) {
                case 0:
                        say( "铁匠笑咪咪地说道：这位" + RANK_D->query_respect(ob)
                                + "，进来挑几件兵器用吧。\n");
                        break;
                case 1:
                        say( "铁匠用脖子上的毛巾抹了抹手，说道：这位" + RANK_D->query_respect(ob)
                                + "，请进请进。\n");
                        break;
        }
}
// xiaoer2.c 酒店小二

inherit NPC;
inherit F_VENDOR;

void create()
{
        set_name("跑堂", ({ "paotang", "waiter" }) );
        set("gender", "男性" );
        set("age", 22);
        set("long",
                "这位跑堂正笑咪咪地忙着，还不时拿起挂在脖子上的抹布擦脸。\n");
        set("combat_exp", 100);
        set("attitude", "friendly");
        set("rank_info/respect", "伙计");
        set("vendor_goods", ([
                "/d/city/obj/jitui":11,
                "/d/city/obj/jiudai":11,
                "/d/city/obj/baozi":11,
                "/d/city/obj/hdjiudai":11,
                "/d/city/obj/kaoya":11,
        ]));
        setup();
}

void init()
{       
        object ob; 
        mapping myfam; 

        ob = this_player();

        ::init();
        if (base_name(environment()) != query("startroom")) return;
        if( interactive(ob) && visible(ob) && !is_fighting() ) {
                if ( (myfam = ob->query("family")) 
                && myfam["family_name"] == "丐帮" 
                && ob->query_skill("begging",1) > 10 )
                {
                        remove_call_out("saying");
                        call_out("saying", 0, ob);
                }
                else
                { 
                        remove_call_out("greeting");
                        call_out("greeting", 1, ob);
                }
        }

        add_action("do_buy", "buy");
        add_action("do_list", "list");
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() || is_fighting(ob)) return;
        switch( random(2) ) {
                case 0:
                        say( "跑堂笑咪咪地说道：这位" + RANK_D->query_respect(ob)
                                + "，进来喝杯茶，歇歇腿吧。\n");
                        break;
                case 1:
                        say( "跑堂用脖子上的毛巾抹了抹手，说道：这位" + RANK_D->query_respect(ob)
                                + "，请进请进。\n");
                        break;
        }
}

void saying(object ob)
{
        if (!ob || environment(ob) != environment() || is_fighting(ob)) return;

        say("\n跑堂大喝一声：你这臭要饭的进来干什么？ 给我滚出去！\n\n");
        remove_call_out("kicking");
        call_out("kicking", 1, ob);
        
}

void kicking(object ob)
{
        if (!ob || environment(ob) != environment()) return;

        ob->move("/d/city/beidajie1");
        message("vision","只听“乒”地一声，" +  ob->query("name") +
          "被人从小吃店里一脚踢了出来，狼狈万状的逃开了。\n", environment(ob), ob);
}


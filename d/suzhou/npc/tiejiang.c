// tiejiang.c 铁匠

inherit NPC;
inherit F_VENDOR;
int ask_me(); 
//int ask_yiechu();
 
void create()
{
        set_name("铁匠", ({ "tie jiang", "tie", "jiang" }) );
        set("gender", "男性" );
        set("age", 34);
        set("long",
                "这是一位位正在抡着大铁锤，叮叮当当的打铁的铁匠。\n");
        set("combat_exp", 300);
        set("attitude", "peaceful");
        set("rank_info/respect", "铁匠");
        set("vendor_goods", ({
           (["name":__DIR__"obj/changjian","number":15]),
           (["name":__DIR__"obj/gangjian","number":20]),
           (["name":__DIR__"obj/gangdao","number":15]),
           (["name":__DIR__"obj/caidao","number":10]),
           (["name":__DIR__"obj/tiechui","number":10]),
           (["name":__DIR__"obj/bishou","number":10])
        }));
        set("inquiry", ([
                "name" : "本人姓王，打小就住在苏州城，你想问啥？\n",
                "rumors" : "我爹被朝廷拉去修运河，他老人家身子骨不好，前些天不幸逝去了。\n",
                "here" : "这里是城里唯一的打铁铺了，什么人都到我这里来打东西。\n",
                "铁锄": (: ask_me :),
                "锄头": "锄头... 抱歉，锄头已经卖光了...", 
 
                 
        ]) );
        setup();
}

void init()
{       
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_buy", "buy");
        add_action("do_list", "list");
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(2) ) {
                case 0:
                        say( "铁匠笑咪咪地说道：这位" + RANK_D->query_respect(ob)
                                + "，这里只要是铁的家伙，应有尽有。\n");
                        break;
                case 1:
                        say( "铁匠笑呵呵地说：这位" + RANK_D->query_respect(ob)
                                + "，您想要点什么？\n");
                        break;
        }
}

int ask_me()
{
        object chu, me, ob;

        me = this_object();
        ob = this_player();
        
        if ( present("tie chu", ob) )
        {
                command("say 你不是有了吗，还想要什麽？\n");
                return 1;
        }
        command("look " + ob->query("id")); 
        command("say 这里正好有一把铁锄没什麽用，你要就拿去吧。\n");
	chu = new("/d/huashan/jinshe/obj/tiechu");
        chu->move(ob);
        message_vision("$N给了$n一把铁锄。\n", me, ob);
        return 1;
}


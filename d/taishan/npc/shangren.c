// yang.c 杨老板 

inherit NPC;
inherit F_VENDOR;


void create()
{
        set_name("商人", ({ "shang ren", "ren" }));
        set("shen_type", 1);
        set("gender", "男性");
        set("age", 25);
        set("long",
                "他穿的很朴素，在这附近做了几年的生意，也没赚到多少钱。\n");
        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_temp("apply/damage", 15);

        set("combat_exp", 40000);
        set("attitude", "friendly");
        set("vendor_goods", ([
//                  "/d/sld/obj/shengzi" : 5,
             "/d/taishan/obj/yangjing_wan" : 2,
                "/clone/misc/fire":10,

        ]));
        
        set("chat_chance", 3);
        set("chat_msg", ({
        "商人叹惜的说道：东边的树林，快给人砍光了，今后怎么让人活啊。\n",
        "商人说道：最近出现了一群怪人，身上都带蛇，奇毒无比，太可怕了。\n",
        (: command("fear") :),
        }) ); 


        setup();
        carry_object("/clone/misc/cloth")->wear();
//      add_money("silver",1);
}

void init()
{
//         add_action("do_list", "list");
//         add_action("do_buy", "buy");
}

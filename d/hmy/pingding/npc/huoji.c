// huoji. 药铺伙计

inherit NPC;
inherit F_VENDOR;

void create()
{
        set_name("药铺伙计", ({ "yaopu huoji", "huoji" }));
        set("str", 20);
        set("gender", "男性");
        set("age", 18);
        set("long", "他是平神医从乡下招来帮忙的。\n");
        set("combat_exp", 250);
        set("attitude", "friendly");
        set("vendor_goods", ([
                __DIR__"obj/jinchuang":20,
           "/clone/medicine/m-book1":5,
                __DIR__"obj/yangjing":20,
              "/clone/medicine/badou" :12,
              "/clone/medicine/baiwei" :8,
              "/clone/medicine/baizhi" :9,
        ]));

        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}


inherit NPC;

inherit F_DEALER;

void create()
{
	set_name("药师", ({ "yao shi", "yao",}));
        set("long", 
"这是一位经验丰富的药师，任何药物一经他手马上可以辨识出是何成份制作的。\n");
        set("gender", "男性");
        set("age", 50);
        set("str", 20);
        set("qi", 1000);
        set("max_qi", 1000);
        set("jing", 1000);
        set("max_jing", 1000);
        set("shen_type", 1);        
        set("combat_exp", 250);
        set("attitude", "friendly");
        set("vendor_goods", ({
                __DIR__"obj/xiaojindan",
                __DIR__"obj/jindan",
                __DIR__"obj/yangjing",
                __DIR__"obj/xiaohuandan",
                __DIR__"obj/dahuan-dan",
        }));

        setup();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}



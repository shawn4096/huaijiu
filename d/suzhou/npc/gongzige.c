// gongzige.c

inherit NPC;

void create()
{
        set_name("公子哥", ({"gongzi"}) );
        set("gender", "男性" );
        set("age", 20);
        set("long", "这是一个游手好闲的公子哥，一副谁都瞧不起的样子。\n");

        set_temp("apply/attack", 15);
        set_temp("apply/defense", 15);
        set("combat_exp", 750);
//	set("shen", -150);
	set("shen_type", -1);
        set("str", 25);
        set("dex", 20);
        set("con", 18);
        set("int", 15);
        set("attitude","heroism");
        setup();
        carry_object(__DIR__"obj/cloth")->wear();
	add_money("silver", 2);
}


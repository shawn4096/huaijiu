// little_monkey.c

inherit NPC;

void create()
{
	set_name("小猴",({ "xiao hou","xiao" }) );
        set("gender", "男性" );
        set("age", 4);
        set("long", "这是一只调皮的小猴子，虽是畜牲，却喜欢模仿人样。\n");
        set("combat_exp", 50);
	set("str", 11);
	set("dex", 11);
	set("con", 11);
	set("int", 11);
       set("attitude", "peaceful");

	set("chat_chance", 20);
	set("chat_msg", ({
		(: random_move :)
	}) );
        setup();
}

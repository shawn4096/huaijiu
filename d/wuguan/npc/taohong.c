// taohong.c

inherit NPC;

void create()
{
	set_name("中年乞妇", ({ "zhongnian qifu","qifu","zhongnian" }) ); 
	set("gender", "女性" );
	set("age", 33);
	set("long", "一个中年乞妇，低头弓背，披头散发，衣服污秽破烂。\n"); 
	set("combat_exp", 1000);
 
	setup();

	set("chat_chance", 3);
	set("chat_msg", ({
		"中年乞妇喃喃地道：老爷晚上见鬼，要砌墙，怎么怪得我？又....又不是我瞎说。\n",
		"中年乞妇惊恐万分：除了这里，我什么地方都不认得，叫我到哪里去？\n",
		"中年乞妇道：老爷又不是不信，可是...可是....我又没说，老爷却赶了我出来。\n",	 
	}));

        carry_object(ARMOR_D("cloth"))->wear();
}

// Room: /d/shaolin/jianyu.c
// Date: YZC 96/02/06
// Modify by looklove 2000/8/25 about water& food

#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "监狱");
	set("long", @LONG
这里黑沉沉的，即无一丝光亮，也无半分声息。黑暗中依稀可以看到身
边似乎有几个人影，看到你转过头去，他们立刻屏住呼吸，紧张地瞪着你。
四壁摸上去冰凉，且极硬，似乎都是钢铁铸成，只有南北面各有一道小门，
门上开了个巴掌大的洞，象是送饭用的。脚边有一堆东西踢上去克剌剌地散
了开来，细看却是一具白得发亮的枯骨。
LONG
	);

	set("no_update", 1);
	set("valid_startroom",1);
	set("objects",([
		CLASS_D("shaolin") + "/qing-yuan" : 1,
		"/d/shaolin/obj/fojing1"+random(2) : 1,
	]));
	setup();

}

void init()
{       
	object ob = this_player();
        ob->set("water",500);
        ob->set("food",500);

	if(userp(ob))
	{
		message("vision",
			HIY "只听牢房铁门匡地一响，一个昏昏沉沉的家伙被扔了进来！\n\n" NOR, 
			environment(ob), ob);
		tell_object(ob, "狱卒嘿嘿地笑着：今儿个你可落在我手里了...！\n");
		ob->set("startroom", "/d/shaolin/jianyu");
		if (!ob->query_condition("bonze_jail")) ob->apply_condition("bonze_jail", 60);
	}
}

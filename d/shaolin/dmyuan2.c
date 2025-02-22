// Room: /d/shaolin/dmyuan2.c
// Date: YZC 96/01/19

inherit ROOM;

void init()
{
	add_action("lingwu","lingwu");
}


void create()
{
	set("short", "达摩院后殿");
	set("long", @LONG
这是一座古朴的殿堂。西首的墙上挂满了各类武功图谱，不少白须白眉
的老僧们正端坐在图谱画轴之前，似乎在苦苦思索。南北山墙是高及屋顶的
大书架，走近细看，它们是各门各派的武功秘笈，屋正中摆着几张矮几诃和
几个蒲团，几位老僧正在入定中。
LONG
);

	set("no_fight", 1);
	set("exits", ([
		"south" : __DIR__"dmyuan",
	]));

	
	set("coor/x",20);
	set("coor/y",440);
	set("coor/z",130);
	setup();
}

int lingwu(string arg)
{
	object me=this_player();
	string special;
	int bl,sl,i;

	if (!me->query("luohan_winner")) {
		write("你级别不够，不能在此领悟。\n");
		return 1;
	}
	if (!arg) {
		write("你要领悟什么？\n");
		return 1;
	}
	if (!me->query_skill(arg,1)) {
		write("你不会这种技能。\n");
		return 1;
	}
	if (me->is_busy() || me->is_fighting()) {
		write("你正忙着呢。\n");
		return 1;
	}
	if (arg == "force" && me->query_skill("force",1)<200) {
		write("以你现在的基本内功修为，尚无法领悟基本内功。\n");
		return 1;
	}
	if((int)me->query("potential") < 1 ) {
		write("你从实战中得到的潜能已经用完了。\n");
		return 1;
	}
	if (!(special=me->query_skill_mapped(arg))) {
		write("你只能从特殊技能中领悟。\n");
		return 1;
	}
	bl=me->query_skill(arg,1);
	if (bl > me->query("jing") || me->query("jing")*100/me->query("max_jing") < 50) {
		me->receive_damage("jing",bl/5);
		write("你没办法集中精神。\n");
		return 1;
	}
	sl=me->query_skill(special,1);
	if (bl > sl) {
		write("你的"+to_chinese(special)+"造诣不够，无法领悟更深一层的"+to_chinese(arg)+"。\n");
		return 1;
	}
	write("你瞑思苦想，对"+to_chinese(arg)+"的体会又深了一层。\n");
	i =me->query_int() + me->query_skill("literate", 1)/10;
	if (me->query("combat_exp",1) >850000){
		me->receive_damage("jing",bl/5*3);
		me->add("potential",-random(2));
		me->improve_skill(arg, i*5/3);
		if(me->query("age")<30)me->improve_skill(arg,30-me->query("age"));
		if(me->query("age")>60)me->improve_skill(arg,me->query("age")-60);
		return 1;
	}
	me->receive_damage("jing",bl/5*2);
	me->add("potential", -random(2));
	me->improve_skill(arg, i*3/2);
	return 1;
}

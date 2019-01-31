// Room: /d/dzd/shidong1.c

inherit ROOM;
void create()
{
	set("short","钟乳石洞");
	set("long",@LONG
这是一个天然形成的钟乳石洞，洞中有的地段很直；有的地段又很弯；有的地段曲如园中的九曲回
廊；漫步前进，自有车到山前必有路之奇；更有的地段曲如林中幽径，漫步游览，自有柳
暗花明又一村之感。洞中光线阴暗，隐隐有腥风吹过。
LONG
	);
	set("exits",([
		"northeast" : __DIR__"shidong4",
		"east" : __DIR__"shidong2",
		"southeast" : __DIR__"rukou",
	]));
	setup();
}

int valid_leave(object me, string dir)
{
	object ob;
	string name;
	me = this_player();
	name = me->query("id")+"'s boss";

	ob = present(name,environment(me) );
	if(ob)  return notify_fail(ob->query("name")+"一把将你拦住：哪里跑！\n" );
	return ::valid_leave(me, dir);
}
